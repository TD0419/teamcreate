#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "Function.h"

#include "GameHead.h"
#include "ObjRope.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//引数1,2	:主人公の腕の位置
//引数3,4	:マウスの位置
CObjRope::CObjRope(float arm_x, float arm_y,float mous_x,float mous_y)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//ロープの初期位置を決める
	m_px = arm_x;
	m_py = arm_y;

	//速さを決める
	m_speed = 6.5f;
	
	//Rを押した時のマウスの位置を保存
	m_moux = mous_x; 
	m_mouy = mous_y; 

	//主人公の腕の(スクロールを考慮した画面上での)位置を保存
	m_hero_arm_x = arm_x - objmap->GetScrollX();
	m_hero_arm_y = arm_y - objmap->GetScrollY();

	//主人公の腕からマウスへのベクトル情報取得
	float vector_x = m_moux - m_hero_arm_x;
	float vector_y = m_mouy - m_hero_arm_y;

	//斜辺取得
	float hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//斜辺の大きさを1にした時のベクトルを求める
	vector_x /= hypotenuse;
	vector_y /= hypotenuse;

	//スピードをかけて移動ベクトルを設定する
	m_vx = vector_x * m_speed;
	m_vy = vector_y * m_speed;
}

//イニシャライズ
void CObjRope::Init()
{
	m_caught_flag = false;//false = フラグOFF true = フラグON
	m_r_key_flag = false;
	m_tarzan_point_flag = false;
	
	//ブロックとの当たり判定フラグの初期化
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
						  
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, ROPE_SIZE, ROPE_SIZE, ELEMENT_PLAYER, OBJ_ROPE, 1);
}

//アクション
void CObjRope::Action()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//主人公のオブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//回転ブロックのスイッチのオブジェクトを持ってくる
	CObjRollBlockSwitch* objrolls = (CObjRollBlockSwitch*)Objs::GetObj(OBJ_ROLL_BLOCK_SWITCH);

	//画面外にいれば
	if(WindowCheck(m_px,m_py,ROPE_SIZE, ROPE_SIZE) == false)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//ロープが所持するHitBoxを除去。
		return;
	}
	
	//HitBoxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//ロープの削除条件を調べる
	RopeDelete();

	//ロープスイッチと当たってないならRキーを押せる
	if (m_caught_flag == false)
	{
		if (Input::GetMouButtonR() == true)
		{
			m_r_key_flag = true; //ロープをRキーで消せないようにする
		}
	}

	//ロープスイッチと衝突したとき、ロープが引っかかるようにする
	if (hit->CheckObjNameHit(OBJ_ROPE_SWITCH) != nullptr)
	{
		m_vx = 0.0f; //ロープ本体の移動速度を0にしてロープを動かないようにする
		m_vy = 0.0f;

		objhero->SetVecX(0.0f);

		m_caught_flag = true;		//ロープ引っかかりフラグをONにする

		if (Input::GetMouButtonR() == false)//　Rキーを押してないならロープをRキーで消せるようにする
		{
			m_r_key_flag = false;
		}
	}

	//ターザンポイントと衝突したとき、ロープが引っかかるようにする
	if(hit->CheckObjNameHit(OBJ_TARZAN_POINT)!=nullptr)
	{
		//ロープスイッチと接触すると、ロープが引っかかる(動きが止まる)
		/*m_px -= m_vx ;
		m_py -= m_vy */;
		m_caught_flag = true;		//ロープ引っかかりフラグをONにする

		//ターザンポイントオブジェクトと当たっていた時、vxが５以上、vyが-6.2以下じゃないとき
		if (hit->CheckObjNameHit(OBJ_TARZAN_POINT) != nullptr&&m_vx <= 5.0f&&m_vy >= -6.2f)
		{
			m_tarzan_point_flag = true;//フラグをONにする
									   //今主人公が持っているm_vxを0にする。それだけではまだ動くので下の処理をする
			objhero->SetVecX(0.0f);
		}
		else
		{
			m_tarzan_point_flag = false;		//ターザン引っ掛かりフラグをOFFにする
			this->SetStatus(false);		//自身に消去命令を出す。
			Hits::DeleteHitBox(this);	//ロープが所持するHitBoxを除去。
		}
		if (Input::GetMouButtonR() == false)//　Rキーを押してないならロープをRキーで消せるようにする
		{
			m_r_key_flag = false;
		}
	}	
	else
	{
		//移動
		m_px += m_vx;
		m_py += m_vy;
	}

	//バグがおきたので上とわけました
	//回転床用のスイッチと衝突したとき、ロープが引っかかるようにする
	if (hit->CheckObjNameHit(OBJ_ROLL_BLOCK_SWITCH) != nullptr)
	{
		//　ステージ５の回転ブロックスイッチが動いてる時はRキーを押してもロープが消えないようにする
		if (objrolls->GetKeyFlag() == true)
		{
			m_r_key_flag = true;
		}
		else if (objrolls->GetKeyFlag() == false && Input::GetMouButtonR() == false)
		{
			m_caught_flag = true;
			m_r_key_flag = false;
		}
		//　ステージ5の回転ブロックスイッチが最後まで行った時ロープを自動的に消すようにする
		if (objrolls->GetLastRoll() == true)
		{
			this->SetStatus(false);		//自身に消去命令を出す
			Hits::DeleteHitBox(this);	//ロープが所持するHitBoxを除去。
			return;
		}
	}

	//回転ブロックのスイッチと当たっている場合
	if (hit->CheckObjNameHit(OBJ_ROLL_BLOCK_SWITCH) != nullptr)
	{
		m_vx = 0.0f; //ロープ本体の移動速度を0にしてロープと回転ブロックのスイッチを離れさせないようにする
		m_vy = 0.0f;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(hit, m_px, m_py);
	
	//主人公の腕の位置を更新
	//主人公が右を向いているときの位置
	if (objhero->GetPosture() == 0.0f)
	{
		m_hero_arm_x = objhero->GetPosX() + 64.0f - objmap->GetScrollX();
		m_hero_arm_y = objhero->GetPosY() + 80.0f - objmap->GetScrollY();
	}
	//主人公が左と向いているときの位置
	else
	{
		m_hero_arm_x = objhero->GetPosX() - objmap->GetScrollX();
		m_hero_arm_y = objhero->GetPosY() + 80.0f - objmap->GetScrollY();
	}
}

//ドロー
void CObjRope::Draw()
{
	float color[4] = {1.0f,0.6f,0.0f,1.0f};

	//主人公オブジェクト情報を取得
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公が存在していたら
	if (objhero != nullptr)
	{
		RopeDraw(color);//ロープの描画
	}
}

// ロープの描画関数
//引数1	描画色の配列
void CObjRope::RopeDraw(float color[])				
{
	//マップオブジェクト情報を取得
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//描画の太さ
	float drow_size = 2;

	//点を打つ位置と主人公の腕の距離
	float drow_px = 0.0f;
	float drow_py = 0.0f;

	//点を打つ位置の移動量用変数
	float drow_vx;
	float drow_vy;

	//変化量を求める	(ロープの先端 - 主人公の腕の位置)
	float change_x = (m_px - objmap->GetScrollX()) - m_hero_arm_x;
	float change_y = (m_py - objmap->GetScrollY()) - m_hero_arm_y;

	//描画の方向を調べる-------------------------------------------
	int pattan;//描画方向の保存用変数（1右上:2右下:3左上:4左下）

	if (change_x >= 0.0f)//Xの変化量が正
	{
		if (change_y >= 0.0f)	//Yの変化量が正
			pattan = 2;//右下
		else					//Yの変化量が負
			pattan = 1;//右上
	}
	else //Xの変化量が負
	{
		if (change_y >= 0.0f)	//Yの変化量が正
			pattan = 4;//左下
		else					//Yの変化量が負
			pattan = 3;//左上
	}
	//描画の方向を調べる 終わり-------------------------------------------

	//Xの変化量がYの変化量より大きい場合
	if (abs(change_x) > abs(change_y))
	{
		//Xを基準に線を引く

		//描画方向をもとに点を打つ位置の移動量を求める----------------------
		switch (pattan)
		{
			case 1://右上
			case 2://右下
			{
				drow_vx = 1.0f;							//Xは右に１ずつ動かす
				drow_vy = change_y / change_x;			//Yは傾き分ずつ動かす
				break;
			}
			case 3://左上
			case 4://左下
			{
				drow_vx = -1.0f;						//Xは左に１ずつ動かす
				drow_vy = -1.0f*(change_y / change_x);	//Yは(-1*傾き)分ずつ動かす
				break;
			}
		}
		//描画方向をもとに点を打つ位置の移動量を求める 終わり----------------------

		while (abs(drow_px) <= abs(change_x)) //点を打つ位置と主人公の腕の距離X　が　変化量Xになるまでループ
		{
			//点を描画する
			Draw::DrawHitBox(m_hero_arm_x + drow_px, m_hero_arm_y + drow_py, drow_size, drow_size, color);

			//点の打つ位置の更新
			drow_px += drow_vx;
			drow_py += drow_vy;
		}
	}
	//Yの変化量がXの変化量より大きい場合
	else
	{
		//Yを基準に線を引く

		//描画方向をもとに点を打つ位置の移動量を求める----------------------
		switch (pattan)
		{
			case 1://右上
			case 3://左上
			{
				drow_vy = -1.0f;						//Yは上に１ずつ動かす
				drow_vx = -1.0f*(change_x / change_y);	//Xは(-1*傾き)分ずつ動かす
				break;
			}
			case 2://右下
			case 4://左下
			{
				drow_vy = 1.0f;							//Yは下に１ずつ動かす
				drow_vx = change_x / change_y;			//Xは傾き分ずつ動かす
				break;
			}
		}
		//描画方向をもとに点を打つ位置の移動量を求める 終わり----------------------

		while (abs(drow_py) <= abs(change_y)) //点を打つ位置と主人公の腕の距離Y　が　変化量Yになるまでループ
		{
			//点を描画する
			Draw::DrawHitBox(m_hero_arm_x + drow_px, m_hero_arm_y + drow_py, drow_size, drow_size, color);

			//点の打つ位置の更新
			drow_px += drow_vx;
			drow_py += drow_vy;
		}
	}
}

//ロープの消える条件を調べる
void CObjRope::RopeDelete()
{
	//HitBoxの情報を持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公のオブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	// ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブロックとの当たり判定
	objblock->AllBlockHit(&m_px, &m_py, ROPE_SIZE, ROPE_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//ブロックとあたっていれば削除する
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//岩に当たった場合ロープを消す
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROCK))
	{
		return;
	}

	//リフトに当たった場合ロープを消す
	if (DeleteCheckObjNameHit(hit, this, OBJ_LIFT))
	{
		return;
	}

	//木に当たった場合ロープを消す
	if (DeleteCheckObjNameHit(hit, this, OBJ_WOOD))
	{
		return;
	}

	//水に当たった場合ロープを消す
	if (DeleteCheckObjNameHit(hit, this, OBJ_WATER))
	{
		return;
	}

	//Lastwall(壁)にあたったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_LAST_WALL))
	{
		return;
	}
	//金網と当たったら消去
	if (DeleteCheckObjNameHit(hit, this, OBJ_WIRE_MESH))
	{
		return;
	}
	//回転ブロックと当たったら削除
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROLL_BLOCK))
	{
		return;
	}
	
	//ロープが消していいかどうかを調べる
	bool rope_delete_r_key = objhero->GetRopeDeleteRKey();

	//ロープ引っかかり判定がONの時、Rが押されたらロープを削除
	if (Input::GetMouButtonR() == true && m_r_key_flag == false && m_caught_flag == true && rope_delete_r_key == true)
	{
		m_caught_flag = false;		//ロープ引っかかりフラグをOFFにする
		m_tarzan_point_flag = false;		//ターザン引っ掛かりフラグをOFFにする
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//ロープが所持するHitBoxを除去。
		return;
	}
}