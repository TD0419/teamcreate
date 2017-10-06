//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjButton.h"
#include "Function.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjButton::CObjButton(int x, int y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjButton::Init()
{
	m_trick_flag = false;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, BUTTON_SIZE, BUTTON_SIZE, ELEMENT_GIMMICK, OBJ_BUTTON, 1);

}

//アクション
void CObjButton::Action()
{
	
	////弾と接触しているかどうかを調べる
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	m_trick_flag = true; //弾とあたっているならtrueを入れる
	//}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjButton::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = BUTTON_SIZE;
	src.m_bottom = BUTTON_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BUTTON_SIZE;
	dst.m_bottom = dst.m_top + BUTTON_SIZE;

	//描画
	Draw::Draw(20, &src, &dst, color, 0.0f);
}