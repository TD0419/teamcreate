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

//コントラスト
CSceneMain::CSceneMain()
{

}
//デストラスト
CSceneMain::~CSceneMain()
{

}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//マップ情報格納用変数テスト用
	int map[MAP_Y_MAX][MAP_X_MAX] = { 0 };

	//マップ情報を読み込み
	MapDataLoading(map);

	ImageDataLoading();//画像データ読み込み関数
	AudioDataLoading();//音楽データ読み込み関数

    //Mapオブジェクトを作成する
	CObjMap* ObjMap = new CObjMap(map);
	Objs::InsertObj(ObjMap, OBJ_MAP, 10);

	//主人公オブジェクトを作成する
	CObjHero* ObjHero = new CObjHero(3,5);
	Objs::InsertObj(ObjHero, OBJ_HERO, 10);

	//Doorオブジェクトを作成する
	CObjDoor* ObjDoor = new CObjDoor(3, 0);
	Objs::InsertObj(ObjDoor, OBJ_DOOR, 10);

	//敵オブジェクトを作成する
	CObjEnemy* ObjEnemy = new CObjEnemy(10,10);
	Objs::InsertObj(ObjEnemy, OBJ_ENEMY, 11);

	//testボスオブジェクトを作成する
	//CObjBoss* ObjBoss = new CObjBoss(10,15);
	//Objs::InsertObj(ObjBoss, OBJ_BOSS, 11);

	//リフトオブジェクトを作成する
	CObjLift* Obj_lift = new CObjLift(6, 5);
	Objs::InsertObj(Obj_lift, OBJ_LIFT, 10);

	//看板オブジェクトを作成する
	CObjSign* Obj_sign = new CObjSign(6, 7);
	Objs::InsertObj(Obj_sign, OBJ_SIGN, 10);

	//レバースイッチオブジェクトを作成する
	CObjLeverSwich* ObjLeverSwich = new CObjLeverSwich(7, 7);
	Objs::InsertObj(ObjLeverSwich, OBJ_LEVER_SWICH, 10);

	//testはしごオブジェクトを作成する（デバック用）
	/*CObjLadders* ObjLadders = new CObjLadders(6, 3);
	Objs::InsertObj(ObjLadders, OBJ_LADDERS, 10);
	CObjLadders* ObjLadders2 = new CObjLadders(6, 2);
	Objs::InsertObj(ObjLadders2, OBJ_LADDERS, 10);
	CObjLadders* ObjLadder3 = new CObjLadders(6, 1);
	Objs::InsertObj(ObjLadder3, OBJ_LADDERS, 10);*/

	////木のテストオブジェクト
	//CObjWood* ObjWood = new CObjWood(12, 0);
	//Objs::InsertObj(ObjWood, OBJ_WOOD, 10);

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

	//p = Save::ExternalDataOpen(L"Stage01.csv", &size);//外部データ読み込み

	p = Save::ExternalDataOpen(L"Stage01.csv", &size);//ボス描画を確認したい方は、こちらを読み込んでください
	
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
	int a = 0;
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
	Draw::LoadImageW(L"Hero.png", 3, TEX_SIZE_256);

	//debug用Boss画像
	Draw::LoadImageW(L"image3.png", 4, TEX_SIZE_512);
	//Draw::LoadImageW(L"image3.jpg", 4, TEX_SIZE_512);

	//Ladders画像
	Draw::LoadImageW(L"Ladders.png", 5, TEX_SIZE_64);

	//Door & Padlock画像
	Draw::LoadImageW(L"Door & Padlock.png", 6, TEX_SIZE_256);

	//Wood画像
	Draw::LoadImageW(L"Wood.png", 7, TEX_SIZE_64);

	//Enemy画像
	Draw::LoadImageW(L"Snake.png", 8, TEX_SIZE_128);

	//Lever画像
	Draw::LoadImageW(L"Lever.png", 9, TEX_SIZE_128);
}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{
	//音楽登録ID
	int id = 0;

	//Audio::LoadAudio(id++, L"", ? ? ? ? );
	
}