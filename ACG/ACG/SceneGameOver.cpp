//STGデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneGameOver.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameOver::CSceneGameOver()
{

}

//デストラクタ
CSceneGameOver::~CSceneGameOver()
{
	
}

//初期化メソッド
void CSceneGameOver::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録(1024×1024ピクセル)
	//Draw::LoadImageW(L"", 0, TEX_SIZE_1024);

	//png",10, TEX_SIZE_512);

	////音楽情報の読み込み
	////BGM－－－－
	//Audio::LoadAudio(0, L".wav", BACK_MUSIC);	//ゲームオーバー音
	//																
	////０番の音楽スタート
	//Audio::Start(0);

	////SE－－－－－
	//Audio::LoadAudio(1, L".wav", EFFECT);			//決定音

	//																	
	////ゲームオーバーオブジェクト作成
	//CObjGameOver* obj = new CObjGameOver();
	//Objs::InsertObj(obj, OBJ_GAME_OVER, 10);
}

//実行中メソッド
void CSceneGameOver::Scene()
{

}