#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRopeSwitch.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRopeSwitch::CObjRopeSwitch(int x, int y)
{
	m_px = x * ROPE_SWITCH_SIZE;
	m_py = y * ROPE_SWITCH_SIZE;

}

//イニシャライズ
void CObjRopeSwitch::Init()
{

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, ROPE_SWITCH_SIZE, ROPE_SWITCH_SIZE, ELEMENT_GIMMICK, OBJ_ROPE_SWITCH, 1);

}

//アクション
void CObjRopeSwitch::Action()
{

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjRopeSwitch::Draw()
{

}