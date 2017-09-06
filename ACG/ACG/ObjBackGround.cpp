#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBackGround.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBackGround::CObjBackGround(int x, int y)
{

}

//イニシャライズ
void CObjBackGround::Init()
{
	 m_x=0;	// 背景X座標
	 m_y=0;	// 背景Y座標
}

//アクション
void CObjBackGround::Action()
{
	
}

//ドロー
void CObjBackGround::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	
}