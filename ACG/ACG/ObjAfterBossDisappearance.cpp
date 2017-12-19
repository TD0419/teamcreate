#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

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

//アクション
void CObjAfterBossDisappearance::Action()
{
	
}

//ドロー
void CObjAfterBossDisappearance::Draw()
{
	
}