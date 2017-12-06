#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"
#include <math.h>

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//モード0,1専用
//引数1		int px			:マップの数値(X位置)
//引数2		int py			:マップの数値(Y位置)
//引数3		int direction	:移動方向(モードが手動のときは自動で動く方向)　０＝右：１＝左：２＝上：３＝下
//引数4		int	width_max	:	X方向への最大移動量(初期位置～最大移動量分動きます。)
//引数5		int mode			:リフトの動きモード
//			０＝手動モード(縄を紐スイッチに当てて移動するモード)
//			１＝自由移動モード(初期位置Xから最大X位置の間を自動移動)
//			２＝無限移動モード(上または下に行き画面外に行くと上なら下から、下なら上から出てくる)
CObjLift::CObjLift(int px,int py,int direction,float width_max,int mode)
{
	//初期位置を決める
 	m_px = (float)px * BLOCK_SIZE;
	m_py = (float)py * BLOCK_SIZE;
	
	//移動方向と初期移動方向を決める
	m_direction = direction;
	m_initial_direction = direction;

	//最大移動量を決める
	//値が負の数なら正の数にする
	if (width_max < 0)
		width_max *= -1;

	//X方向の最大移動量をセット
	m_width_max = width_max;

	//移動モードを決める
	m_move_mode = mode;

	//マップ情報を取得
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//何個めのブロックの位置までを移動区間とするかの個数
	int block_count = 0;
	int block_max_count = (int)(LIFT_SIZE_WIDTH / BLOCK_SIZE);//MAX値

	//移動方向と初期移動方向と最大移動量を決める
	//マップの位置(リフト)の左下が空気なら初期移動方向は右
	if (objmap->GetMap(px - 1, py + 1)== MAP_SPACE)
	{
		if (mode == 0)
		{
			//移動方向と初期移動方向を決める
			m_direction = 0;
			m_initial_direction = 0;
		}
		else
		{
			//移動方向と初期移動方向を決める
			m_direction = 1;
			m_initial_direction = 1;
		}
		//最大移動量を決める
		for (int i = px-1; i >= 0; i--)
		{
			//マップの位置(リフト)左下から左を近いほうから調べていき
			//リフトの幅/BLOCK_SIZE個めにあるブロック位置までを移動区間とする
			if (objmap->GetMap(i, py + 1) == MAP_BLOCK)
			{
				//カウントを進める
				block_count++;
				if (block_count >= block_max_count)
				{
					m_width_max = (px * BLOCK_SIZE) - (i*BLOCK_SIZE);
					break;
				}
			}
		}
	}
	//マップの位置(リフト)の右下が空気なので初期移動方向が左
	else
	{
		if (mode == 0)
		{
			//移動方向と初期移動方向を決める
			m_direction = 1;
			m_initial_direction = 1;
		}
		else
		{
			//移動方向と初期移動方向を決める
			m_direction = 0;
			m_initial_direction = 0;
		}
		//最大移動量を決める
		for (int i = px + block_max_count; i < MAP_X_MAX; i++)
		{
			//マップの位置(リフト)右にblock_max_count,下に1から右を近いほうから調べていき
			//リフトの幅/BLOCK_SIZE個めにあるブロック位置までを移動区間とする
			if (objmap->GetMap(i, py + 1)== MAP_BLOCK)
			{
				//カウントを進める
				block_count++;
					
				m_width_max = (i*BLOCK_SIZE) - (px * BLOCK_SIZE);
				break;
			}
		}
	}
	
}

//コンストラクタ
//モード２専用
//引数1		int px			:マップの数値(X位置)
//引数2		int py			:マップの数値(Y位置)
//引数3		int direction	:移動方向(モードが手動のときは自動で動く方向)　０＝右：１＝左：２＝上：３＝下
CObjLift::CObjLift(int px, int py, int direction)
{
	//初期位置を決める
	m_px = (float)px * BLOCK_SIZE;
	m_py = (float)py * BLOCK_SIZE;

	//移動方向と初期移動方向を決める
	m_direction = direction;
	m_initial_direction = direction;

	//移動モードセット
	m_move_mode = 2;

	//モード２のときは使わないけど初期化しておく
	m_width_max = 0.0f;
}
//イニシャライズ
void CObjLift::Init()
{
	//移動量を0にする
	m_move_x = 0.0f;
	m_move_y = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	
	//リフトのカウント初期化
	m_lift_audio_count = 47;

	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 1:
		case 2:
		{
			//当たり判定
			Hits::SetHitBox(this, m_px, m_py, LIFT_SIZE_WIDTH, LIFT_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT, 1);
			break;
			
		}
		case 5:
		{
			//当たり判定
			Hits::SetHitBox(this, m_px, m_py, STAGE5_LIFT_SIZE_WIDTH, STAGE5_LIFT_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_LIFT, 1);
			break;
		}
	}

	
}

//アクション
void CObjLift::Action()
{
	
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);
	
	//主人公が当たっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroRide();//主人公を乗せる処理をする
	}

	//各移動モード(m_move_mode)による移動
	ModeMove();
	
	//位置情報を更新
	m_px += m_vx;
	m_py += m_vy;

	//HitBoxの位置を更新する
	HitBoxUpData(hit, m_px, m_py);
}

//ドロー
void CObjLift::Draw()
{	
	//mapオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画色を決める
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src, dst;

	
	
	//描画の位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();

	switch (((UserData*)Save::GetData())->stagenum)
	{
		case 1:
		case 2:
		{
			//切り取り
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 32.0f;

			//描画
			dst.m_right = dst.m_left + LIFT_SIZE_WIDTH;
			dst.m_bottom = dst.m_top + LIFT_SIZE_HEIGHT;

			break;
		}
		case 5:
		{
			//切り取り
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 320.0f;
			src.m_bottom = 16.0f;

			//描画
			dst.m_right = dst.m_left + STAGE5_LIFT_SIZE_WIDTH;
			dst.m_bottom = dst.m_top + STAGE5_LIFT_SIZE_HEIGHT;

			break;
		}
	}
	
	//リフトの描画
	Draw::Draw(GRA_LIFT, &src, &dst, color, 0.0f);
}

//主人公を乗せる処理をする
void CObjLift::HeroRide()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);
	//主人公オブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float h_px = objhero->GetPosX();//主人公の位置Xを持ってくる

	HIT_DATA** hit_data;	//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//衝突の情報をhit_dataに入れる

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//あたっている角度を持ってくる

			//上側があたっていればで
			if (30.0f <= r && r <= 155.0f)
			{
				objhero->SetHitDown(true);//リフトの上に主人公が乗っていたらm_hit_downにtrueを返す

				//リフトに乗せる処理
				objhero->SetVecY(0.0f);//主人公のY方向の移動を0にする
				objhero->SetPosX(h_px + m_vx);//主人公の位置をもともと主人公が居た位置＋リフトの移動量にする
				objhero->SetPosY(m_py - HERO_SIZE_HEIGHT + 2.5f + m_vy);//主人公のポジションをリフトの上にする
			}
			//右側があたっていればで
			if (0.0f <= r && r < 30.0f)
			{
				switch (((UserData*)Save::GetData())->stagenum)
				{
				case 1:
				case 2:
				{
					if (objhero->GetPosture() == 1.0f)//左向き
					{
						//リフトにのめりこまないようにする処理
						objhero->SetPosX(m_px + LIFT_SIZE_WIDTH - 14.5f);//主人公をリフトの右に行くようにする
						objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
						break;
					}
					else//右向き
					{
						//当たり判定のずれから振り向いたらめり込んでしまうので、-14.5fを削除
						objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
						objhero->SetPosX(m_px + LIFT_SIZE_WIDTH);
						break;
					}
				}
				case 5:
				{
					
					break;
				}
				}
			}
			//左側があたっていればで
			if (155.0f < r && r < 180.0f)
			{
				switch (((UserData*)Save::GetData())->stagenum)
				{
					case 1:
					case 2:
						//リフトにのめりこまないようにする処理
						if (objhero->GetPosture() == 0.0f)//右向き
						{
							objhero->SetPosX(m_px - 48.5f);//主人公をリフトの左に行くようにする
						}
						else//左向き
						{
							//めり込み防止のため左向きのときは-64.0fにする
							objhero->SetPosX(m_px - 64.0f);//主人公をリフトの左に行くようにする
						}
					case 5:
					{
						break;
					}
				}
			}
		}
	}
}

//各移動モード(m_move_mode)による移動関数
void CObjLift::ModeMove()
{
	//各移動モードによる移動
	switch (m_move_mode)
	{
		//------------------------------縄を紐スイッチに当てて移動するモード------------------------------
	case 0:
		//ロープオブジェクトを持ってくる
		CObjRopeSwitch* objrope_switch;
		objrope_switch = (CObjRopeSwitch*)Objs::GetObj(OBJ_ROPE_SWITCH);
		//ロープスイッチ情報があるかつ
		//ロープとロープスイッチがあたっているとき
		if (objrope_switch != nullptr && objrope_switch->GetRopeFlag() == true)
		{
			//Aキーが押されたら
			if (Input::GetVKey('A'))
			{
				//初期位置から動いた距離がMAX未満だったら移動
				if (m_move_x < m_width_max)
				{
					//初期位置から動いた距離を増やす
					m_move_x += SPEED;
					//初期の移動方向が右のとき
					if (m_initial_direction == 0)
					{
						//左に進む
						m_vx = -SPEED;
						m_lift_audio_count++;
						if (m_lift_audio_count % 50 == 0)
						{
							Audio::Start(PULLLIFT);
						}
					}
					//初期の移動方向が左のとき
					else
					{
						//右に進む
						m_vx = SPEED;
					}

				}
			}
			//Aキーが押されていないならX移動０
			else
			{
				m_vx = 0.0f;
			}
		}
		else//ロープとロープスイッチがあたっていないとき
		{
			//初期位置から動いた距離が０を超えていたら移動
			if (m_move_x > 0)
			{
				//初期位置に近づくので減算
				m_move_x -= SPEED;

				//初期の移動方向が右だったら
				if (m_initial_direction == 0)
				{
					//右に移動
					m_vx = SPEED;
					m_lift_audio_count++;
					if (m_lift_audio_count % 50 == 0)
					{
						Audio::Start(RELEASELIFT);
					}
				}
				//初期の移動方向は左だったら
				else
				{
					//左に移動
					m_vx = -SPEED;
				}
			}
		}

		//初期位置から動いた距離が最大量を超えると
		if (m_move_x > m_width_max)
		{
			//初期の移動方向が右だったら
			if (m_initial_direction == 0)
			{
				//行き過ぎた分を計算
				m_vx = m_move_x - m_width_max;
			}
			//初期の移動方向が左だったら
			else
			{
				//行き過ぎた分を計算
				m_vx = m_move_x - m_width_max;
			}
			m_move_x = m_width_max;//移動量の初期化
		}
		//初期位置から動いた距離が０未満だったら
		if (m_move_x < 0)
		{
			//初期の移動方向が右だったら
			if (m_initial_direction == 0)
			{
				//行き過ぎた分を計算
				m_vx = m_move_x;
			}
			//初期の移動方向が左だったら
			else
			{
				//行き過ぎた分を計算
				m_vx = m_move_x;
			}
			m_move_x = 0;
		}

		//初期位置から動いた距離が０またはMAXなら移動ベクトルを０にする
		if (m_move_x == 0 || m_move_x == m_width_max)
			m_vx = 0.0f;
		break;
		//------------------------------自由移動モード(最大右X位置から最大値左X位置の間を自動移動)---------------
	case 1:
		//移動方向が右の時
		if (m_direction == 0)
		{
			//移動ベクトルXを加算
			m_vx = SPEED;
			//初期移動方向が右なら
			if (m_initial_direction == 0)
				m_move_x += SPEED;//初期位置に近づくので加算
								  //初期移動方向が左なら
			else
				m_move_x -= SPEED;//初期位置から離れるので減算
		}
		//移動方向が左の時
		else
		{
			//移動ベクトルXを減算
			m_vx = -SPEED;
			//初期移動方向が右なら
			if (m_initial_direction == 0)
				m_move_x -= SPEED;//初期位置から離れるので減算
								  //初期移動方向が左なら
			else
				m_move_x += SPEED;//初期位置に近づくので加算
		}

		//初期位置から動いた距離が０またはMAX値だったら
		//現在の移動方向を左右逆にする
		if (m_move_x == 0 || m_move_x == m_width_max)
		{
			//現在の移動方向が右なら左に
			if (m_direction == 0)
				m_direction = 1;
			//左なら右にする
			else
				m_direction = 0;
		}

		//初期位置から動いた距離がMAX越えまたは０以下だったら
		//行き過ぎた分を調整して現在の移動方向を左右逆にする
		else if (m_move_x > m_width_max || m_move_x < 0)
		{
			//行き過ぎた分
			//初期位置から動いた距離がMAX越えなら
			if (m_move_x > m_width_max) 
			{
				//現在の移動方向が右
				if (m_direction == 0)
				{
					//まず初期位置から動いた距離がMAXになる位置まで進める
					m_vx = m_width_max - (m_move_x - SPEED);
					//超えた分を移動させる
					m_vx -= m_move_x - m_width_max;
				}
				//現在の移動方向が左
				else
				{
					//まず初期位置から動いた距離がMAXになる位置まで進める
					m_vx = (m_width_max - (m_move_x - SPEED))*-1;
					//超えた分を移動させる
					m_vx += m_move_x - m_width_max;

				}
				//初期位置から動いた距離を計算
				m_move_x -= (m_move_x - m_width_max) * 2;
			}
			//初期位置から動いた距離が０未満なら
			else
			{
				//現在の移動方向が右
				if (m_direction == 0)
				{
					//まず初期位置から動いた距離が０のときの位置まで進める
					m_vx = m_move_x + SPEED;
					//超えた分を移動させる
					m_vx += m_move_x;
				}
				//現在の移動方向が左
				else
				{
					//まず初期位置から動いた距離が０のときの位置まで進める
					m_vx = (m_move_x + SPEED)*-1;
					//超えた分を移動させる
					m_vx += m_move_x*-1;
				}
				////初期位置から動いた距離を計算
				m_move_x *= -1;
			}
			//現在の移動方向を左右逆にする
			if (m_direction == 0)
				m_direction = 1;
			else
				m_direction = 0;
		}
		break;
		//--------------------無限移動モード(上または下に行き画面外に行くと上なら下から、下なら上から出てくる)--------
	case 2:
		//上の限界Y位置
		//この値より上に行ったら下の限界Y位置から出てくる
		float up_limti;
		up_limti = (MAP_Y_MAX - 12)*BLOCK_SIZE - LIFT_SIZE_HEIGHT;
		//下の限界Y位置
		//この値より下に行ったら上の限界Y位置から出てくる
		float down_limti;
		down_limti = MAP_Y_MAX*BLOCK_SIZE;
		//現在の移動方向による移動
		if (m_direction == 2)
		{
			m_vy = -SPEED;
		}
		else
		{
			m_vy = SPEED;
		}
		//上の限界Y位置より上だったら
		if (m_py < up_limti)
		{
			//現在の移動方向が上だったら
			//意味無いかもだけど一応条件文をはさむ
			if (m_direction == 2)
			{
				//行き過ぎた分をvyに入れる
				m_vy = m_py - up_limti;
				//Y位置を下の限界Y位置にする
				m_py = down_limti;
			}
		}
		//下の限界Y位置より下だったら
		if (m_py > down_limti)
		{
			//現在の移動方向が下だったら
			//意味無いかもだけど一応条件文をはさむ
			if (m_direction == 3)
			{
				//行き過ぎた分をvyに入れる
				m_vy = m_py - down_limti;
				//Y位置を上の限界Y位置にする
				m_py = up_limti;
			}
		}
		break;
	default:
		break;
	}
}