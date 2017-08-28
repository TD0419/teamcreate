#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHero::CObjHero()
{

}

//イニシャライズ
void CObjHero::Init()
{
	m_px = WINDOW_SIZE_W/2.0f;
	m_py = WINDOW_SIZE_H / 2.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;
	m_mouse_angle = 0.0f;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE, HERO_SIZE, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//落下にリスタート----------------------------------
	//m_pyが1000以下ならリスタートする
	//if (m_py > 1000.0f)
	//{
	//	//場外に出たらリスタート
	//	Scene::SetScene(new CSceneMain());
	//}

	//移動ーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	//Aキーがおされたとき：左移動
	if (Input::GetVKey('A') == true)
	{
		m_vx -= 3.0f;
	}

	//Dキーがおされたとき：右移動
	if (Input::GetVKey('D') == true)
	{
		m_vx += 3.0f;
	}
	//SPACEキーがおされたとき：ジャンプ
	if (Input::GetVKey(VK_SPACE) == true)
	{
		m_vy -= 3.0f;
	}

	//摩擦
	m_vx += -(m_vx * 0.098);

	//自由落下運動
	//m_vy += 9.8 / (16.0f);

	//Scroll();	//スクロール処理をおこなう

	//移動ベクトルをポジションに加算
	m_px += m_vx;
	m_py += m_vy;

	//移動ベクトルを初期化
	m_vx = 0.0f;
	m_vy = 0.0f;

	//移動終わり-----------------------------------------

	//マウスの位置と主人公の位置からマウスの角度を求める------
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//マウスの位置情報取得
	double mous_x = Input::GetPosX();
	double mous_y = Input::GetPosY();

	//主人公の位置からマウスの位置のベクトル情報取得
	double vector_x = mous_x - m_px - obj_m->GetScrollX();
	double vector_y = mous_y - m_py - obj_m->GetScrollY();

	//斜辺取得
	double hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//角度を求める
	m_mouse_angle = acos(vector_x / hypotenuse) * 180.0/3.14;

	//マウスのY位置が主人公のY位置より下だったら
	if (mous_y > m_py - obj_m->GetScrollY())
	{
		//180°～360°の値にする
		m_mouse_angle = 360 - abs(m_mouse_angle);
	}
	//-------------------------------------------------------

	//はしご-------------------------------------------------

	////はしごと接触しているかどうかを調べる
	//if (hit->CheckObjNameHit(OBJ_LADDERS) != nullptr)
	//{
	//	//Wキーがおされたとき
	//	if (Input::GetVKey('W') == true)
	//	{
	//		m_vy -= 3.0f;
	//	}

	//	//Sキーがおされたとき
	//	if (Input::GetVKey('S') == true)
	//	{
	//		m_vy += 3.0f;
	//	}
	//}

	//はしご終了---------------------------------------------

	//発砲---------------------------------------------------
	//左クリックを押したら
	if (Input::GetMouButtonL() == true)
	{
		//弾丸作成
		CObjBullet* Objbullet = new CObjBullet(m_px,m_py,m_mouse_angle);
		Objs::InsertObj(Objbullet, OBJ_BULLET, 10);
	}
	//発砲終了-----------------------------------------------

	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//水オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//自身を削除
		Hits::DeleteHitBox(this);	//ヒットボックスを削除

		//メインへ移行
		Scene::SetScene(new CSceneMain());
	}

	//HitBoxの位置情報の変更
	hit->SetPos(m_px, m_py);

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
	
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top		= 0.0f;
	src.m_left		= 0.0f;
	src.m_right		= 512.0f;
	src.m_bottom	= 512.0f;

	//描画位置
	dst.m_top		= 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left		= 0.0f + m_px - obj_m->GetScrollX();
	dst.m_right		= dst.m_left + HERO_SIZE;
	dst.m_bottom	= dst.m_top + HERO_SIZE;

	//描画
	Draw::Draw(0, &src, &dst, color, m_r);

}