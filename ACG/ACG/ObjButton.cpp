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

}