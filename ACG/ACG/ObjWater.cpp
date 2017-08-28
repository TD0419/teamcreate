//使用するヘッダーファイル　

#include "GameHead.h"
#include "ObjWater.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWater::CObjWater(float x, float y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjWater::Init()
{
}

//アクション
void CObjWater::Action()
{
}

//ドロー
void CObjWater::Draw()
{
}