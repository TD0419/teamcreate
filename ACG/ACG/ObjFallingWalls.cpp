//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjFallingWalls.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjFallingWalls::CObjFallingWalls(int x, int y)
{
	m_px = (float)x * FALLING_WALLS_SAIZE;
	m_py = (float)y * FALLING_WALLS_SAIZE;
}

//イニシャライズ
void CObjFallingWalls::Init()
{
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, FALLING_WALLS_SAIZE, FALLING_WALLS_SAIZE, ELEMENT_GIMMICK, OBJ_FALLING_WALLS, 1);
}

//アクション
void CObjFallingWalls::Action()
{
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjFallingWalls::Draw()
{
	
}