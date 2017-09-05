//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjThroughBlock.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjThroughBlock::CObjThroughBlock(int x, int y)
{
	m_px = x * ROCK_SIZE;
	m_py = y * ROCK_SIZE;
}

//イニシャライズ
void CObjThroughBlock::Init()
{
}

//アクション
void CObjThroughBlock::Action()
{
	
}

//ドロー
void CObjThroughBlock::Draw()
{

}