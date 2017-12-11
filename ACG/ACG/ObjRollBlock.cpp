//使用するヘッダー
#include "GameHead.h"
#include "ObjRollBlock.h"
#include "Function.h"
#include"GameL\Audio.h"
#include "GameL\HitBoxManager.h"

//コンストラクタ
//引数1,2	mapの要素番号
CObjRollBlock::CObjRollBlock(int x,int y,int pattan)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_pattan = pattan;
	m_map_x = x;
	m_map_y = y;
}

//イニシャライズ
void CObjRollBlock::Init()
{
	m_count = 0;//カウンターの初期化
	m_r = 0.0f;	//角度初期化

	m_roll_flag = false;//回転のフラグを初期化
	m_pos_adjustment_flag = false;

	m_audio_time = 29;//音楽制御用のタイム初期化

	switch (m_pattan)
	{
		case 1:	//90fごとに回転
		{	
			//横向きからスタート
			m_situation_width_flag = true;

			//回転の中心位置を求める
			m_center_x = m_px + ROLL_BLOCK_SIZE_WIDTH / 2.0f;
			m_center_y = m_py + ROLL_BLOCK_SIZE_HEIGHT / 2.0f;

			//回転後のポジションと中心位置の差分
			m_difference_x = ROLL_BLOCK_SIZE_HEIGHT / 2.0f;
			m_difference_y = ROLL_BLOCK_SIZE_WIDTH / 2.0f;

			//当たり判定セット
			Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
			break;
		}
		case 2:	//引っ張ったときに一度のみ回転
		{
			//縦向きからスタート
			m_situation_width_flag = false;

			//回転用のスイッチを作成
			CObjRollBlockSwitch* objrollblockswitch = new CObjRollBlockSwitch(m_px - ROLL_BLOCK_SWITCH_SIZE_WIDTH, m_py,(CObjRollBlock*)this);
			Objs::InsertObj(objrollblockswitch, OBJ_ROLL_BLOCK_SWITCH,10);

			//縦と横を入れ替えて当たり判定セット
			Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
			break;
		}
	}

	
}

//アクション
void CObjRollBlock::Action()
{
	
	//HitBoxのポインタを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);
	
	switch (m_pattan)
	{
		case 1:	//90fごとに回転
		{

			if (m_count <= 90)//90以下なら
				m_count++;//カウントを増やす

			//90fになったら
			if (m_count == 90)
			{
				m_roll_flag = true;//回転のフラグをオンにする
			}

			if (m_roll_flag == true)//回転したとき
			{
				m_r += 90.0f;	//角度を加算

				//向きを変える
				m_situation_width_flag = !(m_situation_width_flag);

				if (m_r >= 360.0f)	//360度以上にならないようにする
					m_r = 0.0f;

				//回転後のポジションを入れる
				m_px = m_center_x - m_difference_x;
				m_py = m_center_y - m_difference_y;

				//差分の更新（xとyの入れ替え）をする
				float tmp = m_difference_x;
				m_difference_x = m_difference_y;
				m_difference_y = tmp;

				m_roll_flag = false;	//フラグをオフにする
				m_count = 0;			//カウントを0で初期化する
			}
			break;

		}
		case 2:	//引っ張ったときに一度のみ回転
		{
			if (m_roll_flag == true)//回転のフラグがオンになっていれば
			{
				m_audio_time+=1;//音楽制御のために1ずつプラスしていく
				if (m_audio_time % 40 == 0)
				{
					Audio::Start(ROLLBLOCK);
				}
				m_r += 2.0f;//まわす
			}
			if (m_r > 90.0f)
			{
				m_r = 90.0f;//90を超えないようにする
				m_situation_width_flag = true; //横向きにする
				Audio::Stop (ROLLBLOCK);
			}
			break;
		}
	}
	
	//ヒーローオブジェクトと当たっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();//衝突処理をするをする
	}

	switch (m_pattan)
	{
		case 1:
		{
			if ( m_situation_width_flag == true)	//横向きなら
			{
				//高さと幅をそのままで当たり判定の更新
				HitBoxUpData(hit, m_px, m_py, ROLL_BLOCK_SIZE_WIDTH,ROLL_BLOCK_SIZE_HEIGHT);
			}
			else 	//縦向きなら
			{
				//高さと幅を逆にしてあたり判定の更新
				HitBoxUpData(hit, m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH);
			}
			break;
		}
		case 2:
		{
			if (m_situation_width_flag == true)	//横向き（回転終了後
			{
				//最初の一度のみ位置の更新をする
				if (m_pos_adjustment_flag == false)
				{
					m_px -= ROLL_BLOCK_SIZE_WIDTH;
					m_py += (ROLL_BLOCK_SIZE_WIDTH - ROLL_BLOCK_SIZE_HEIGHT);
					m_pos_adjustment_flag = true;
				}
				//高さと幅をそのままで当たり判定の更新
				HitBoxUpData(hit, m_px , m_py , ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT);
			}
			else 	//縦向きなら
			{
				//高さと幅を逆にしてあたり判定の更新
				HitBoxUpData(hit, m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH);
			}

		}
	}
}

//ドロー
void CObjRollBlock::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);


	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	
	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left= m_px - objmap->GetScrollX();

	switch (m_pattan)
	{
		case 1:
		{
			//切り取り位置の設定
			src.m_right = ROLL_BLOCK_SIZE_WIDTH;
			src.m_bottom = ROLL_BLOCK_SIZE_HEIGHT;

			if ( m_situation_width_flag == true)	//横向き
			{
				//描画位置の設定
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
			}
			else//縦向き
			{
				//描画位置の設定
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_HEIGHT;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_WIDTH;
			}

			//描画
			Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, m_r,-0.5f,-0.5f);
			break;
		}
		case 2:
		{
			if (m_situation_width_flag == true) //横向き（回転終了後なら）
			{
				// 切り取り位置の設定
				src.m_right = ROLL_BLOCK_SIZE_HEIGHT;
				src.m_bottom = ROLL_BLOCK_SIZE_WIDTH;

				//描画位置の設定
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;

				//描画
				Draw::Draw(GRA_ROLL_BLOCK2, &src, &dst, color, m_r);
			}
			else 
			{
				 //切り取り位置の設定
				src.m_right = ROLL_BLOCK_SIZE_WIDTH;
				src.m_bottom = ROLL_BLOCK_SIZE_WIDTH;

				//描画位置の設定
				dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
				dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_WIDTH;

				//描画
				Draw::Draw(GRA_ROLL_BLOCK2, &src, &dst, color, m_r,0.0f,-1.0f);
			}
			break;
		}
	}
}

//ヒーローが当たったときの処理
void CObjRollBlock::HeroHit()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//衝突の情報をhit_dataに入れる

	for (int i = 0; i < hit->GetCount(); i++)
	{
		if (hit_data[i] != nullptr)//ヒットデータがあれば
		{
			float r = hit_data[i]->r;//あたっている角度を持ってくる

			//主人公オブジェクトを持ってくる
			CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			//横向きのときの当たり判定
			if (m_situation_width_flag == true)
			{
				//上側があたっていれば
				if (35.0f < r && r < 145.0f)
				{
					objhero->SetHitDown(true);//主人公が乗っていたらm_hit_downにtrueを返す

					 //乗せる処理
					objhero->SetPosY(m_py - 126.0f);//ブロックの上側に調節する

					//主人公の移動ベクトルが下向きなら
					if (objhero->GetVecY() > 0.0f)
						objhero->SetVecY(0.0f);//主人公のY方向の移動を0にする
				}
				//左側が当たっていれば
				else if (145.0f <= r && r <= 210.0f)
				{
					//左に反発する処理
					//リフトにのめりこまないようにする処理
					if (objhero->GetPosture() == 0.0f)//右向き
					{
						objhero->SetPosX(m_px - 48.5f);//主人公の位置をブロックの左にする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
					else
					{
						objhero->SetPosX(m_px - 60.5f);//主人公の位置をブロックの左にする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
				}
				//右側が当たっていれば
				else if (0.0f <= r && r <= 35.0f || 360.0f > r && 340.0f < r)
				{
					//右に反発する処理
					//リフトにのめりこまないようにする処理
					if (objhero->GetPosture() == 0.0f)//右向き
					{
						objhero->SetPosX(m_px + 190.5f);//主人公の位置をブロックの左にする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
					else
					{
						objhero->SetPosX(m_px + 180.5f);//主人公の位置をブロックの左にする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
				}

				//下側があたっていれば
				else if (180.0f < r && r < 340.0f)
				{
					//下に反発する処理
					objhero->SetPosY(m_py + ROLL_BLOCK_SIZE_HEIGHT);//主人公の位置をブロックの下にする
					objhero->SetVecY(objhero->GetVecY());//主人公のY方向の移動量を反転する
				}
			}
			//縦向きのときの当たり判定
			else
			{
				//上側があたっていれば
				if (68.0f < r && r < 112.0f)
				{
					objhero->SetHitDown(true);//主人公が乗っていたらm_hit_downにtrueを返す
					//乗せる処理
					objhero->SetPosY(m_py - 126.0f);//ブロックの上側に調節する

					//主人公の移動ベクトルが下向きなら
					if (objhero->GetVecY() > 0.0f)
						objhero->SetVecY(0.0f);//主人公のY方向の移動を0にする
				}
				//左側が当たっていれば
				else if (112.0f <= r && r <= 250.0f)
				{
					//リフトにのめりこまないようにする処理
					if (objhero->GetPosture() == 0.0f)//右向き
					{
						objhero->SetPosX(m_px - 48.5f);//主人公をリフトの左に行くようにする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
					else//左向き
					{
						//めり込み防止のため左向きのときは-64.0fにする
						//左に反発する処理
						objhero->SetPosX(m_px - 60.5f);//主人公の位置をブロックの左にする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
				}
				//右側が当たっていれば
				else if (0.0f < r && r < 68.0f || 290.0f < r && r < 360.0f)
				{
					//縦向きなら
					//リフトにのめりこまないようにする処理
					if (objhero->GetPosture() == 0.0f)//右向き
					{
						objhero->SetPosX(m_px + 60.5);//主人公の位置をブロックの右にする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
					else//左向き
					{
						objhero->SetPosX(m_px + 48.5f);//主人公の位置をブロックの右にする
						objhero->SetVecX(objhero->GetVecX());//主人公のX方向の移動量を反転する
					}
				}

				//下側があたっていれば
				if (250.0f < r && r < 290.0f)
				{
					
					//縦向きなら
					objhero->SetPosY(m_py + ROLL_BLOCK_SIZE_WIDTH);//主人公の位置をブロックの下にする
					objhero->SetVecY(objhero->GetVecY());//主人公のY方向の移動量を反転する
				}
			}
		}

	}
}