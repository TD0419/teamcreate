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
	m_button_x = x;
	m_button_y = y;
}

//イニシャライズ
void CObjButton::Init()
{
	m_trick_flag = false;
}

//アクション
void CObjButton::Action()
{
	////弾と接触しているかどうかを調べる
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	m_trick_flag = true; //弾とあたっているならtrueを入れる
	//}
}

//ドロー
void CObjButton::Draw()
{

}