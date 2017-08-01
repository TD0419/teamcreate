#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjLadders.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLadders::CObjLadders(float x,float y)
{
	 m_x = x;		
	 m_y = y;
}

//イニシャライズ
void CObjLadders::Init()
{
	//Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_GREEN, OBJ_LADDEERS, 1);
}

//アクション
void CObjLadders::Action()
{
	;
}

//ドロー
void CObjLadders::Draw()
{
	//描画カラー情報　R=RED G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //切り取り位置の設定
	RECT_F dst; //描画先表示位置

	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 64.0f;
	//src.m_bottom = 256.0f;

	//dst.m_top = 0.0f + m_y;
	//dst.m_left = 0.0f + m_x;
	//dst.m_right = 64.0f + m_x;
	//dst.m_bottom = 64.0f + m_y;

	////10番目に登録したグラフィックをstc・dst・cの情報を元に描画
	//Draw::Draw(10, &src, &dst, c, 0.0f);

}