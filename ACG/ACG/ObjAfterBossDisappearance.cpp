#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjAfterBossDisappearance.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjAfterBossDisappearance::Init()
{
	//マップ情報を取得
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//マップ情報にドアを追加
	objmap->SetMap(108,18, MAP_GOAL_DOOR);

	//ドアを作成
	CObjDoor* objDoor = new CObjDoor(108, 18);
	Objs::InsertObj(objDoor, OBJ_DOOR, 9);
}

//ドロー
void CObjAfterBossDisappearance::Draw()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"GAME CLEAR", 150.0f, 120.0f, 150.0f, color);
}