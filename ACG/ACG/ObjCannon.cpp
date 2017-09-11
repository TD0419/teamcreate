#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjCannon.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjCannon::CObjCannon(float x, float y)
{
	m_x = x * CANNON_SIZE_HEIGHT;
	m_y = y * CANNON_SIZE_WIDTH;
}

//イニシャライズ
void CObjCannon::Init()
{

	m_x = 100.0f;
	m_y = 100.0f;
	m_r = 0.0f;
	
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, CANNON_SIZE_WIDTH, CANNON_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_CANNON, 1);

}

//アクション
void CObjCannon::Action()
{
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);

}

//ドロー
void CObjCannon::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top	 = 0.0f;
	src.m_left	 = 0.0f;
	src.m_right	 = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = 0.0f + m_y - obj_m->GetScrollY();
	dst.m_left = 0.0f + m_x - obj_m->GetScrollX();
	dst.m_right = dst.m_left + CANNON_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + CANNON_SIZE_HEIGHT;

	//描画
	Draw::Draw(14, &src, &dst, color, m_r);

}