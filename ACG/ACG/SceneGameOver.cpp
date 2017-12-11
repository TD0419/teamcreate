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
	
	//ゲームオーバー画像読み込み
	Draw::LoadImageW(L"Image\\BackGround\\Scene_Game_Over.png", GRA_GAME_OVER, TEX_SIZE_1024);

	//音楽情報の読み込み
	//BGM－－－－
	Audio::LoadAudio(GAMEOVER, L"BGM\\GameOver.wav", BACK_MUSIC);	//ゲームオーバー音
	//																

	//SE－－－－－

	//Audio::LoadAudio(1, L".wav", EFFECT);			//決定音
																
	//ゲームオーバーオブジェクト作成
	CObjGameOver* objgame_over = new CObjGameOver();
	Objs::InsertObj(objgame_over, OBJ_GAME_OVER, 10);
}

//実行中メソッド
void CSceneGameOver::Scene()
{

}