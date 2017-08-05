//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

CObjBlock::CObjBlock(int map[MAP_Y][MAP_X])
{
	//マップデータコピー
	//memcpy(m_map,map,sizeof(int) * (MAP_Y*MAP_X));

}
//マップ変更用
void CObjBlock::MapChange(int map[MAP_Y][MAP_X])
{
	//マップデータコピー
	//memcpy(m_map,map,sizeof(int) * (MAP_Y*MAP_X));
}

//イニシャライズ
void CObjBlock::Init()
{
	m_scroll = 0.0f;
}


//アクション
void CObjBlock::Action()
{
}
//ドロー
void CObjBlock::Draw()
{
	
}