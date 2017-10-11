#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
}

//アクション
void CObjTitle::Action()
{
	if (Input::GetVKey(VK_RETURN) == true)
	{
		//シーンメインに移動
		Scene::SetScene(new CSceneMain);
	}
}

//ドロー
void CObjTitle::Draw()
{
}