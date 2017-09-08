#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHero::CObjHero(int x, int y)
{
	m_px = x * HERO_SIZE_WIDTH;
	m_py = y * HERO_SIZE_HEIGHT;
}

//イニシャライズ
void CObjHero::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //右向き0.0f 左向き1.0f
	m_r = 0.0f;

	m_bullet_control = false;	//弾丸発射制御用
	
	m_rope_control = false;		//ロープ発射制御用
	m_ani_time = 0;
	m_ani_frame = 1;			//静止フレームを初期にする
	m_ani_max_time = 6;			//アニメーション間隔幅

	//ブロックとの衝突した状態(場所)確認用
	m_hit_up	= false;
	m_hit_left  = false;
	m_hit_right = false;
	m_hit_down  = false;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//マップオブジェクトを持ってくる
	CObjMap* obj_map = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//落下にリスタート----------------------------------
	//m_pyが1000以下ならリスタートする
	if (m_py > 1000.0f)
	{
		//場外に出たらリスタート
		Scene::SetScene(new CSceneMain());
	}
	
	//ブロックオブジェクトを持ってくる
	CObjBlock* obj_b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	LandingCheck();//着地フラグの更新

	//はしご-------------------------------------------------
	//はしごと接触しているかどうかを調べる
	//プレイヤーの位置をマップの要素番号に直す
	int map_num_x = (int)((m_px + BLOCK_SIZE / 2) / BLOCK_SIZE);//中央を基準に調べる
	int map_num_y = (int)(m_py / BLOCK_SIZE);	//主人公の上端を基準で調べる

	int map_num_up = obj_map->GetMap(map_num_x, map_num_y);//主人公（上半分）のマップの値を持って来る

	map_num_y = (int)((m_py) / BLOCK_SIZE) + 1;//主人公の中央を基準に調べる
	int map_num_center = obj_map->GetMap(map_num_x, map_num_y);//主人公（上半分）のマップの値を持って来る	

	map_num_y = (int)((m_py + BLOCK_SIZE) / BLOCK_SIZE) + 1;//主人公の下端を基準に調べる
	int map_num_down = obj_map->GetMap(map_num_x, map_num_y);//主人公（上半分）のマップの値を持って来る	

	//マップの値がはしごなら
	if (map_num_up == MAP_LADDERS || map_num_center == MAP_LADDERS || map_num_down == MAP_LADDERS)
	{
		//yの移動方向を初期化
		m_vy = 0.0f;

		//Wキーがおされたとき 上るとき
 		if (Input::GetVKey('W') == true)
		{
   			m_vy = -2.0f;
			m_hit_down = true;//着地状態にする
		}
		
		//Sキーがおされたとき　下るとき
		if (Input::GetVKey('S') == true)
		{
			m_vy = 2.0f;
			m_hit_down = true;//着地状態にする

		}	

	}
	else
	{
		//ブロックとの当たり判定
		obj_b->BlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
	}
	
	//はしご終了---------------------------------------------

	

	//移動ーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	//Aキーがおされたとき：右移動
	if (Input::GetVKey('D') == true)
	{
		m_vx += 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 0.0f;		//主人公の向き
		m_ani_time += 1;
	}
	//Dキーがおされたとき：左移動
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 1.0f;		//主人公の向き
		m_ani_time += 1;
	}
	else
	{
		m_ani_frame_stop = 1;	//キー入力が無い時は1を入れる
		m_ani_frame = 1;		//キー入力が無い場合は静止フレームにする
		m_ani_time = 0;
	}

	//アニメーションの感覚管理
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//最後までアニメーションが進むと最初に戻る
	if (m_ani_frame == 3)
	{
		m_ani_frame = 0;
	}
	
	

	//ジャンプ--------------------------------------------------------------------

	if (Input::GetVKey(VK_SPACE) == true)
	{
		if (m_hit_down == true)
		{
			m_vy = -20.0f;
		}
	}

	//ジャンプ終了-------------------------------------------------------------------------------------


	//↓キーがおされたとき：下に下がる（デバッグ）
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy = 20.0f;
	}
	//↑キーがおされたとき：上に下がる（デバッグ）
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vy = -20.0f;
	}

	//摩擦
	m_vx += -(m_vx * 0.098);
	
	//自由落下運動
	if(m_hit_down==false)//着地していなければ
		m_vy += 9.8 / (16.0f);
	

	Scroll();	//スクロール処理をおこなう
	//ブロックとの当たり判定
	obj_b->BlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
					&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	Scroll();	//スクロール処理をおこなう
	m_px += m_vx;
	m_py += m_vy;

	//移動ベクトルを初期化
	
	//m_vx = 0.0f;
	//m_vy = 0.0f;

	//移動終わり-----------------------------------------

	//発砲---------------------------------------------------
	//左クリックを押したら
	if (Input::GetMouButtonL() == true)
	{
		//マップオブジェクトの呼び出し
		CObjMap* obj_map = (CObjMap*)Objs::GetObj(OBJ_MAP);

		//マウスの位置情報取得
		float mous_x = Input::GetPosX();
		//マウスの位置がプレイヤーから見てどの方向か調べるための変数
		float mous_way = 0.0f;//右：0.0ｆ　左：1.0ｆ 右向きで初期化

		if ( (mous_x - ( m_px - obj_map->GetScrollX() ) ) < 0)//主人公より左をクリックしたとき
			mous_way = 1.0f;

		if (m_bullet_control == true)
		{
			//向いている方向とクリックしている方向が同じなら
			if (m_posture == mous_way)
			{
				if (m_posture == 0.0f)//主人公が右を向いているとき右側から発射
				{
					//弾丸作成
					CObjBullet* Objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
					Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
					m_bullet_control = false; //弾丸を出ないフラグにする。
				}
				else//主人公が左を向いているとき右側から発射
				{
					//弾丸作成
					CObjBullet* Objbullet = new CObjBullet(m_px - 16.0f, m_py + 50.0f);
					Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
					m_bullet_control = false; //弾丸を出ないフラグにする。
				}
			}
		}
	}
	else
		m_bullet_control = true; //左クリックしてなければ弾丸をでるフラグにする。

	//発砲終了-----------------------------------------------


	//ロープ射出---------------------------------------------
	//右クリックを押したら
	if (Input::GetMouButtonR() == true)
	{
		if (m_rope_control == true)
		{
			//ロープ作成
			CObjRope* Objrope = new CObjRope(m_px, m_py);
			Objs::InsertObj(Objrope, OBJ_ROPE, 10);
			m_rope_control = false;
		}
	}
	else
		m_rope_control = true; //右クリックを押していなければロープが出るフラグを立てる。
	//射出終了------------------------------------------------

	//水オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//自身を削除
		Hits::DeleteHitBox(this);	//ヒットボックスを削除

		//メインへ移行
		Scene::SetScene(new CSceneMain());
		return;
	}

	//敵オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr) //仮です。敵が多いようならElementに変えます
	{
		this->SetStatus(false);		//自身を削除
		Hits::DeleteHitBox(this);	//ヒットボックスを削除

		//メインへ移行
		Scene::SetScene(new CSceneMain());
		return;
	}

	//木オブジェクトと衝突してれば
	if (hit->CheckObjNameHit(OBJ_WOOD) != nullptr)
	{
		
	}



	////水オブジェクトと衝突していれば
	//if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	//{
	//	this->SetStatus(false);		//自身を削除
	//	Hits::DeleteHitBox(this);	//ヒットボックスを削除

	//								//メインへ移行
	//	Scene::SetScene(new CSceneMain());
	//}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//スクロール処理の関数
void CObjHero::Scroll()
{
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//右にスクロールです
	//原点を右にする
	if ((m_px + HERO_SIZE_WIDTH) - obj_m->GetScrollX() > SCROLL_LINE_RIGHT)
	{
		//差分を調べる
		float scroll =  ((m_px + HERO_SIZE_WIDTH) - obj_m->GetScrollX())-SCROLL_LINE_RIGHT;
		//スクロールに影響を与える
		obj_m->SetScrollX(scroll);
	}
	//左にスクロールです
	if (m_px - obj_m->GetScrollX() < SCROLL_LINE_LEFT &&
		obj_m->GetScrollX() > 0)
	{
		//差分を調べる
		float scroll = SCROLL_LINE_LEFT - (m_px - obj_m->GetScrollX());
		//スクロールに影響を与える
		obj_m->SetScrollX(-scroll);
	}

	//上にスクロールです
	if (m_py - obj_m->GetScrollY() < SCROLL_LINE_UP)
	{
		//差分を調べる
		float scroll = (m_py - obj_m->GetScrollY()) - SCROLL_LINE_UP;
		//スクロールに影響を与える
		obj_m->SetScrollY(scroll);
	}
	
	//下にスクロールです
	//原点を下にする
	if ((m_py + HERO_SIZE_HEIGHT) - obj_m->GetScrollY() > SCROLL_LINE_DOWN &&
		obj_m->GetScrollY() < 0)
	{
		//差分を調べる
		float scroll = SCROLL_LINE_DOWN - ((m_py + HERO_SIZE_HEIGHT) - obj_m->GetScrollY());
		//スクロールに影響を与える
		obj_m->SetScrollY(-scroll);
	}
}

//ドロー
void CObjHero::Draw()
{
	//画像の切り取り配列
	int AniData[3] =
	{
		0  , 1 , 2
	};

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	//止まっている時
	if (m_ani_frame_stop == 1)  //仮
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 128.0f;
	}
	else//動いているとき
	{
		src.m_top = 128.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64;
		src.m_bottom = 256.0f;
	}

	//描画位置
	dst.m_top		= 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left		= (HERO_SIZE_WIDTH * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_right	    = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_bottom	= dst.m_top  + HERO_SIZE_HEIGHT;

	//描画
	Draw::Draw(3, &src, &dst, color, m_r);

	////画面全体を暗くするです。
	//Draw::SetFill(true);
	////画面全体をこの色にする
	////staticなのは消すかもしれないから
	//static float col[4] = { 0.0f };
	//col[0] -= 0.01f;
	//col[1] -= 0.01f;
	//col[2] -= 0.01f;
	//Draw::SetColor(col);
}

//着地できてるかどうかを調べる関数
void CObjHero::LandingCheck()
{
	bool c1,c2;//チェック結果を保存するための変数:チェック項目を増やすたびに数を増やす必要がある
	
	c1=HitUpCheck(OBJ_LIFT); //リフトとの着地チェック
	c2 = HitUpCheck(OBJ_WOOD); //木との着地チェック
								 
	//チェック項目のどれか一つでもtrueなら
	if (c1 == true||c2 ==true)
		m_hit_down = true;//着地フラグをオンにする

}

//指定したオブジェクトの上側に当たっているかしらべる
//引数　調べたいオブジェクトネーム
//戻り値　着地していれば:true　していなければ:false
bool CObjHero::HitUpCheck(int obj_name)
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);
	
	//引数で持ってきたオブジェクトとあたっているか調べる
	if (hit->CheckObjNameHit(obj_name) != nullptr)
	{
		HIT_DATA** hit_data;	//衝突の情報を入れる構造体
		hit_data = hit->SearchObjNameHit(obj_name);//衝突の情報をhit_dataに入れる

		//あたっている数分調べる
		for (int i = 0; i < hit->GetCount(); i++)
		{
			//データがあれば
  			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;//あたっている角度をもってくる

				 //Heroの下側があたっていれば
				if (225.0f < r && r < 315.0f)
				{
					return true;//着地している
				}
			}
		}
	}
	return false;//着地していない
}

