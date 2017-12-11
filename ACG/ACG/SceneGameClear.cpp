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
#include "SceneGameClear.h"
#include "GameHead.h"

//初期化メソッド
void CSceneGameClear::InitScene()
{
	//外部グラフィックファイルを読み込み0番に登録
	Draw::LoadImageW(L"Image\\BackGround\\Ending.png", GRA_GAME_CLEAR, TEX_SIZE_1024);
	
	//BGM----------------------------------
	//音楽読み込み
	Audio::LoadAudio(CLEAR, L"BGM\\Clear.wav", BACK_MUSIC);

	//SE------------------------------
	//Audio::LoadAudio(1, L".wav", EFFECT);			//決定音

	//ゲームクリアオブジェクト作成
	CObjGameClear* objgame_clear = new CObjGameClear();	
	Objs::InsertObj(objgame_clear, OBJ_GAME_CLEAR, 10);	//クリアオブジェクト登録
}

//実行中メソッド
void CSceneGameClear::Scene()
{

}