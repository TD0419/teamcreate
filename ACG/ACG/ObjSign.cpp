#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjSign.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjSign::CObjSign(int x, int y)
{
	m_px = x;
	m_py = y;
}

//イニシャライズ
void CObjSign::Init()
{
	
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, SIGN_SIZE, SIGN_SIZE, ELEMENT_GIMMICK, OBJ_SIGN, 1);
}

//アクション
void CObjSign::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//主人公とあたっていれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		wchar_t* str
	}
}

//ドロー
void CObjSign::Draw()
{
}