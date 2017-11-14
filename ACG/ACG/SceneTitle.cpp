//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneTitle.h"
#include "GameHead.h"

//初期化メソッド
void CSceneTitle::InitScene()
{
	InageDataLoading();
	//オブジェクトを作成する
	CObjTitle* objtitle = new CObjTitle();
	Objs::InsertObj(objtitle, OBJ_TITLE, 10);
}

//実行中メソッド
void CSceneTitle::Scene()
{
	
}

//画像データ読み込み関数
void CSceneTitle::InageDataLoading()
{
	//タイトル画像読み込み
	Draw::LoadImageW(L"Image\\BackGround\\Scene_Title.png", GRA_TITLE, TEX_SIZE_1024);
}

//音楽データ読み込み関数
void CSceneTitle::AudioDataLoading()
{
}

