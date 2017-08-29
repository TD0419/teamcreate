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

	//test敵オブジェクトを作成する
	CObjEnemy* ObjEnemy = new CObjEnemy(10,10);
	Objs::InsertObj(ObjEnemy, OBJ_ENEMY, 11);

	//blockオブジェクト作成
	CObjBlock* obj_block = new CObjBlock();
	Objs::InsertObj(obj_block, OBJ_BLOCK, 9);
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

	p = Save::ExternalDataOpen(L"Stage01.csv", &size);//外部データ読み込み

	
	if (p == nullptr)
	{
		MessageBox(0, L"マップデータが見つかりませんでした。", L"エラーコッチャ", MB_OK);
		return;
	}

	int count = 1;

	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			
			map[i][j] = w;

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
	Draw::LoadImageW(L"image2.jpg", 1, TEX_SIZE_512);
	// debug用block画像
	Draw::LoadImageW(L"testblock.png", 2, TEX_SIZE_512);

	//hero画像
	Draw::LoadImageW(L"Hero.png", 3, TEX_SIZE_256);

}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{
	//音楽登録ID
	int id = 0;

	//Audio::LoadAudio(id++, L"", ? ? ? ? );
	
}