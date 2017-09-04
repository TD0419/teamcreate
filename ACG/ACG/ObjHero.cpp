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
	m_px = x * HERO_SIZE_X;
	m_py = y * HERO_SIZE_Y;
}

//イニシャライズ
void CObjHero::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f; //右向き0.0f 左向き1.0f
	m_r = 0.0f;

	m_f  = false;
	m_rf = false;
	m_jf = false;//ジャンプ制御

	bu = false;
	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 6; //アニメーション間隔幅

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE_X, HERO_SIZE_Y, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//落下にリスタート----------------------------------
	//m_pyが1000以下ならリスタートする
	if (m_py > 1000.0f)
	{
		//場外に出たらリスタート
		Scene::SetScene(new CSceneMain());
	}

	//移動ーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	//Aキーがおされたとき：右移動
	if (Input::GetVKey('D') == true)
	{
		m_vx += 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 0.0f;//主人公の向き
		m_ani_time += 1;
	}
	//Dキーがおされたとき：左移動
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= 0.5f;
		m_ani_frame_stop = 0;
		m_posture = 1.0f;//主人公の向き
		m_ani_time += 1;
	}
	else
	{
		m_ani_frame_stop = 1; //キー入力が無い時は1を入れる
		m_ani_frame = 1; //キー入力が無い場合は静止フレームにする
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
	CObjBlock* obj_b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ジャンプ--------------------------------------------------------------------------------
	//SPACEキーがおされたとき：ジャンプ
	if (/*bu == true&&*/Input::GetVKey(VK_SPACE)==true&&m_vy==0)
	{
		if (m_jf == true)
		{
			m_vy = -20.0f;
			m_jf = false;
		}
	}
	else
		m_jf = true; //スペース押してなければジャンプでるフラグにする。

	//↓キーがおされたとき：下に下がる（デバッグ）
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy = 20.0f;
	}

	//はしご-------------------------------------------------
	////はしごと接触しているかどうかを調べる
	if (hit->CheckObjNameHit(OBJ_LADDERS) != nullptr)
	{
		//Wキーがおされたとき 上るとき
		if (Input::GetVKey('W') == true)
		{
			m_vy = -2.0f;
		}

		//Sキーがおされたとき　下るとき
		if (Input::GetVKey('S') == true)
		{
			m_vy = 2.0f;
		}
	}
	//はしご終了---------------------------------------------
	

	//摩擦
	m_vx += -(m_vx * 0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);  //ブロックに着地できるようになったらはずしてください

	//Scroll();	//スクロール処理をおこなう

	//移動ベクトルをポジションに加算
	m_px += m_vx;
	m_py += m_vy;

	////移動ベクトルを初期化
	//m_vx = 0.0f;
	//m_vy = 0.0f;

	//移動終わり-----------------------------------------



	//発砲---------------------------------------------------
	//左クリックを押したら
	if (Input::GetMouButtonL() == true)
	{
		if (m_f == true)
		{
			if (m_posture == 0)//主人公が右を向いているとき右側から発射
			{
				//弾丸作成
				CObjBullet* Objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
				Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
				m_f = false; //弾丸を出ないフラグにする。
			}
			else//主人公が左を向いているとき右側から発射
			{
				//弾丸作成
				CObjBullet* Objbullet = new CObjBullet(m_px - 16.0f, m_py + 50.0f);
				Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
				m_f = false; //弾丸を出ないフラグにする。
			}
		}
	}
	else
		m_f = true; //左クリックしてなければ弾丸をでるフラグにする。

	//発砲終了-----------------------------------------------


	//ロープ射出---------------------------------------------
	//右クリックを押したら
	if (Input::GetMouButtonR() == true)
	{
		if (m_rf == true)
		{
			//ロープ作成
			CObjRope* Objrope = new CObjRope(m_px, m_py);
			Objs::InsertObj(Objrope, OBJ_ROPE, 10);
			m_rf = false;
		}
	}
	else
		m_rf = true; //右クリックを押していなければロープが出るフラグを立てる。
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

	//主人公が左または右のスクロールラインを超えそうなら
	if ((m_px + m_vx) < SCROLL_LINE_LEFT || (m_px + m_vx) > SCROLL_LINE_RIGHT)
	{
		obj_m->SetScrollX(m_vx);	//移動量をスクロールにセット
	}

	//主人公が上または下のスクロールラインを超えそうなら
	if ((m_py + m_vy) < SCROLL_LINE_UP || (m_py + m_vy) > SCROLL_LINE_DOWN) 
	{
		obj_m->SetScrollY(m_vy);	//移動量をスクロールにセット
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
	dst.m_left		= (HERO_SIZE_X * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_right	    = (HERO_SIZE_X - HERO_SIZE_X * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_bottom	= dst.m_top  + HERO_SIZE_Y;

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



