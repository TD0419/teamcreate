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
	//マップ情報格納用変数テスト用
	int map[MAP_Y_MAX][MAP_X_MAX] = { 0 };

	MapDataLoading(map);//マップ情報を読み込み
	ImageDataLoading();//画像データ読み込み関数
	AudioDataLoading();//音楽データ読み込み関数

    //Mapオブジェクトを作成する
	CObjMap* objmap = new CObjMap(map);
	Objs::InsertObj(objmap, OBJ_MAP, 10);

	//主人公オブジェクトを作成する
	CObjHero* objhero = new CObjHero();
	Objs::InsertObj(objhero, OBJ_HERO, 10);

	//Doorオブジェクトを作成する
	CObjDoor* objdoor = new CObjDoor(3, 0);
	Objs::InsertObj(objdoor, OBJ_DOOR, 10);

	//敵オブジェクトを作成する
	CObjEnemy* objenemy = new CObjEnemy(10,7);
	Objs::InsertObj(objenemy, OBJ_ENEMY, 11);

	//リフトオブジェクトを作成する
	CObjLift* objlift = new CObjLift(6, 5);
	Objs::InsertObj(objlift, OBJ_LIFT, 10);

	//看板オブジェクトを作成する
	CObjSign* objsign = new CObjSign(14, 7);
	Objs::InsertObj(objsign, OBJ_SIGN, 10);

	//レバースイッチオブジェクトを作成する
	CObjLeverSwich* objlever_swich = new CObjLeverSwich(7, 7);
	Objs::InsertObj(objlever_swich, OBJ_LEVER_SWICH, 10);

	////水ブジェクトを作成する
	//CObjWater* objwater = new CObjWater(8, 9);
	//Objs::InsertObj(objwater, OBJ_WATER, 10);

	//ロープスイッチオブジェクトを作成する
	CObjRopeSwitch* objrope_switch = new CObjRopeSwitch(7, 5);
	Objs::InsertObj(objrope_switch, OBJ_ROPE_SWITCH, 10);

	//testはしごオブジェクトを作成する（デバック用）
	/*CObjLadders* objladders = new CObjLadders(6, 3);
	Objs::InsertObj(objladders, OBJ_LADDERS, 10);
	CObjLadders* objladders2 = new CObjLadders(6, 2);
	Objs::InsertObj(objladders2, OBJ_LADDERS, 10);
	CObjLadders* objladders3 = new CObjLadders(6, 1);
	Objs::InsertObj(objladders3, OBJ_LADDERS, 10);*/

	//test砲台オブジェクトを作成する
	CObjCannon* objcannon = new CObjCannon(10, 5);
	Objs::InsertObj(objcannon, OBJ_CANNON, 10);

	//テストボタン
	CObjButton*objbutton = new CObjButton(5, 3);
	Objs::InsertObj(objbutton, OBJ_BUTTON, 10);

	//テスト壁
	CObjLastWall*objlastwall = new CObjLastWall(15, -2);
	Objs::InsertObj(objlastwall, OBJ_LAST_WALL, 10);

	//壁テストのためboss
	CObjBoss*objboss = new CObjBoss(10, 5);
	Objs::InsertObj(objboss, OBJ_BOSS, 10);

	//背景オブジェクトを作成する
	CObjBackGround* objback_ground = new CObjBackGround();
	Objs::InsertObj(objback_ground, OBJ_BACKGROUND, 1);

	//debug敵弾丸作成
	//CObjEnemyBullet* objenemy_bullet = new CObjEnemyBullet(64.0,  50.0, 0);
	//Objs::InsertObj(objenemy_bullet, OBJ_ENEMY_BULLET, 10);
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

	p = Save::ExternalDataOpen(L"Stage01.csv", &size);//外部データ読み込み
	
	//p = Save::ExternalDataOpen(L"testwater.csv", &size);//ボス描画を確認したい方は、こちらを読み込んでください
	
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
	
	//debug用hero画像
	//Draw::LoadImageW(L"image.jpg",0, TEX_SIZE_512);
	//debug用enemy画像
	//Draw::LoadImageW(L"image2.jpg", 1, TEX_SIZE_512);
	// debug用block画像
	//Draw::LoadImageW(L"testblock.png", 2, TEX_SIZE_512);

	// block画像
	Draw::LoadImageW(L"block.png", 2, TEX_SIZE_128);

	//hero画像
	Draw::LoadImageW(L"Hero.png", 3, TEX_SIZE_1024);

	//debug用Boss画像
	Draw::LoadImageW(L"image.png", 4, TEX_SIZE_1024);

	//Ladders画像
	Draw::LoadImageW(L"Ladders.png", 5, TEX_SIZE_64);

	//Door & Padlock画像
	Draw::LoadImageW(L"Door & Padlock.png", 6, TEX_SIZE_128);

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
	//水の下部分
	//Draw::LoadImageW(L"WaterUnder.png", 12, TEX_SIZE_64);

	//Waterテスト画像
	Draw::LoadImageW(L"WaterBlock.png", 12, TEX_SIZE_64);
	
	//RopeSwitch画像
	Draw::LoadImageW(L"RopeSwitch.png", 13, TEX_SIZE_64);

	//大砲
	Draw::LoadImageW(L"image4.png", 14, TEX_SIZE_64);
	
	//背景画像
	Draw::LoadImageW(L"background.png" ,15, TEX_SIZE_1536);

	//木画像
	Draw::LoadImageW(L"woodtst.png", 16, TEX_SIZE_128);

	//看板
	Draw::LoadImageW(L"Sign.png", 17, TEX_SIZE_256);
	//debug用敵弾丸画像
	Draw::LoadImageW(L"bomb.png",18,TEX_SIZE_64);

	//testhero
	Draw::LoadImageW(L"Hero2.png", 19, TEX_SIZE_1024);

	//ボタン
	Draw::LoadImageW(L"button.png", 20, TEX_SIZE_64);

	//lastwall(仮)
	Draw::LoadImageW(L"Lastwall.png", 21, TEX_SIZE_256);//上
	Draw::LoadImageW(L"Openwall.png", 22, TEX_SIZE_512);//下
}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{
	//音楽登録ID
	int id = 0;
	//Audio::LoadAudio(id++, L"", ? ? ? ? );
}