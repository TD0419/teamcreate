//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjButton.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjButton::CObjButton(float x, float y)
{
	m_Button_x = x;
	m_Button_y = y;
}

//イニシャライズ
void CObjButton::Init()
{
	m_door_flag = false;

	//blockとの衝突状態確認用
	/*m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;*/

	//Hits::SetHitBox(this, m_x, m_y, 64, 12, ELEMENT_GREEN, OBJ_BUTTON, 1);
}

//アクション
void CObjButton::Action()
{
	////ブロックタイプ検知用の変数がないためのダミー
	//int d;

	////ブロックとの当たり判定実行
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//block->BlockHit(&m_x, &m_y, false,
	//	&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
	//	&d, OBJ_LIFT
	//);

	////弾と接触しているかどうかを調べる
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	m_door_flag = true; //弾とあたっているならtrueを入れる
	//}

	////HitBoxの位置の変更
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_x + block->GetScroll(), m_y + 2);
}

//ドロー
void CObjButton::Draw()
{
	////アニメーション情報を登録
	//int AniData[2] =
	//{
	//	0 , 1
	//};

	////描画カラー情報
	//float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//RECT_F src; //描画元切り取り位置
	//RECT_F dst; //描画先表示位置

	//			//切り取り位置の設定
	//src.m_top = 0.0f;
	//src.m_left = AniData[m_ani_frame] * 64.0f;
	//src.m_right = src.m_left + 64.0f;
	//src.m_bottom = 64.0f;

	////ブロック情報を持ってくる
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	////表示位置の設定
	//dst.m_top = -16.0f + m_y;
	//dst.m_left = -12.0f + m_x + block->GetScroll();
	//dst.m_right = 78.0f + m_x + block->GetScroll();
	//dst.m_bottom = 50.0f + m_y;

	////描画
	//Draw::Draw(28, &src, &dst, c, 0.0f);
}