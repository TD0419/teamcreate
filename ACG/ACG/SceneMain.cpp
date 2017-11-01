//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"


//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	MapDataLoading(map);//マップ情報を読み込み
	ImageDataLoading();//画像データ読み込み関数
	AudioDataLoading();//音楽データ読み込み関数

    //Mapオブジェクトを作成する
	CObjMap* objmap = new CObjMap(map);
	Objs::InsertObj(objmap, OBJ_MAP, 10);

	//主人公オブジェクトを作成する
	CObjHero* objhero = new CObjHero(0,0);
	Objs::InsertObj(objhero, OBJ_HERO, 10);

	//背景オブジェクトを作成する
	CObjBackGround* objback_ground = new CObjBackGround();
	Objs::InsertObj(objback_ground, OBJ_BACKGROUND, 1);

//デバッグ　”使い終わったら消してください！”----------------
	//Doorオブジェクトを作成する
	CObjDoor* objdoor = new CObjDoor(3, 3);
	Objs::InsertObj(objdoor, OBJ_DOOR, 10);

	//看板オブジェクトを作成する
	CObjSign* objsign = new CObjSign(14, 7);
	Objs::InsertObj(objsign, OBJ_SIGN, 10);

	//ロープスイッチオブジェクトを作成する
	CObjRopeSwitch* objrope_switch = new CObjRopeSwitch(7, 5);
	Objs::InsertObj(objrope_switch, OBJ_ROPE_SWITCH, 10);

	//test砲台オブジェクトを作成する
	CObjCannon* objcannon = new CObjCannon(10, 5);
	Objs::InsertObj(objcannon, OBJ_CANNON, 10);


//デバッグ-----------------------------------------------
}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}

//マップデータ読み込み関数
void CSceneMain::MapDataLoading(int map[MAP_Y_MAX][MAP_X_MAX])
{
	//外部データの読み込み（ステージ情報）
	unique_ptr<wchar_t> p;	//ステージ情報ポインター
	int size;				//ステージ情報の大きさ

	//Stage01のテストプレイ中のためStage02.csvの読み込みを変更しています

	p = Save::ExternalDataOpen(L"Stage01a.csv", &size);//外部データ読み込み
	
	if (p == nullptr)
	{
		MessageBox(0, L"マップデータが見つかりませんでした。", L"エラーコッチャ", MB_OK);
		return;
	}

	//外部のマップ情報ずらすやつ
	int count = 1;

	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//マップ情報を入れる
			int w = 0;
			//マップ情報取得
			swscanf_s(&p.get()[count], L"%d", &w);
			
			//マップ情報を代入
			map[i][j] = w;

			//-1桁数分ずらす
			while (w/10 != 0)
			{
				count++;
				w /= 10;
			}
			count += 2;
		}
	}
}

//画像データ読み込み関数
void CSceneMain::ImageDataLoading()
{
	//画像登録ID
	//int id = 0;
	//グラフィック読み込み
	//Draw::LoadImageW(L"", id++, TEX_SIZE_???);
	
	// block画像
	Draw::LoadImageW(L"block.png", 2, TEX_SIZE_128);

	//hero画像
	Draw::LoadImageW(L"Hero.png", 3, TEX_SIZE_1024);

	//debug用Boss画像
	Draw::LoadImageW(L"image.png", 4, TEX_SIZE_1024);

	//Ladders画像
	Draw::LoadImageW(L"Ladders.png", 5, TEX_SIZE_64);

	//Door & Padlock画像
	Draw::LoadImageW(L"Door.png", 6, TEX_SIZE_128);

	//Wood画像
	Draw::LoadImageW(L"Wood.png", 7, TEX_SIZE_128);
	
	//Enemy画像
	Draw::LoadImageW(L"Snake.png", 8, TEX_SIZE_256);

	//Lever画像
	Draw::LoadImageW(L"Lever.png", 9, TEX_SIZE_128);

	//rock画像
	Draw::LoadImageW(L"rock.png", 10, TEX_SIZE_256);

	//Water画像
	Draw::LoadImageW(L"Water.png", 11, TEX_SIZE_256);

	//Water波なし画像  消しちゃだめ。いります！
	Draw::LoadImageW(L"WaterBlock.png", 12, TEX_SIZE_256);
	
	//RopeSwitch画像
	Draw::LoadImageW(L"RopeSwitch.png", 13, TEX_SIZE_64);

	//大砲
	Draw::LoadImageW(L"image4.png", 14, TEX_SIZE_64);
	
	//背景画像
	Draw::LoadImageW(L"background.png" ,15, TEX_SIZE_1536);

	//木画像
	Draw::LoadImageW(L"woodtst.png", 16, TEX_SIZE_128);

	//看板の枠線
	Draw::LoadImageW(L"Sign.png", 17, TEX_SIZE_256);
	
	//ボタン
	Draw::LoadImageW(L"button.png", 20, TEX_SIZE_128);

	//lastwall(仮)
	Draw::LoadImageW(L"Lastwall.png", 21, TEX_SIZE_256);//上
	Draw::LoadImageW(L"Openwall.png", 22, TEX_SIZE_512);//下

	//zanki(仮)
	Draw::LoadImageW(L"zanki.png", 23, TEX_SIZE_64);
	
	//リフト
	Draw::LoadImageW(L"Lift.png", 24, TEX_SIZE_128);

	//看板
	//Draw::LoadImageW(L"", 25, TEX_SIZE_256);イラスト決まってから読み込んでください


}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{
	//音楽登録ID
	int id = 0;
	//Audio::LoadAudio(id++, L"", ? ? ? ? );
}