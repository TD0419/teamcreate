#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLift.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLift::CObjLift(int x, int y)
{
	m_px = x * LIFT_SIZE;
	m_py = y * LIFT_SIZE;
}

//イニシャライズ
void CObjLift::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, LADDERS_SIZE, LADDERS_SIZE, ELEMENT_GIMMICK, OBJ_LADDERS, 1);

}

//アクション
void CObjLift::Action()
{
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjLift::Draw()
{
}