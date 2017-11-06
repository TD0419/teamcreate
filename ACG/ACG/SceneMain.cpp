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
	MapDataLoading(m_map);//マップ情報を読み込み
	ImageDataLoading();//画像データ読み込み関数
	AudioDataLoading();//音楽データ読み込み関数

    //Mapオブジェクトを作成する
	CObjMap* objmap = new CObjMap(m_map);
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


	//テスト壁
	CObjLastWall*objlastwall = new CObjLastWall(15, -2);
	Objs::InsertObj(objlastwall, OBJ_LAST_WALL, 10);

	//壁テストのためboss
	CObjBoss*objboss = new CObjBoss(10, 5);
	Objs::InsertObj(objboss, OBJ_BOSS, 10);

	//テストタイム
	CObjTime* objtime = new CObjTime();
	Objs::InsertObj(objtime, OBJ_TIME, 100);

	//テストボタン
	CObjButton* objbuttn = new CObjButton(5, 5);
	Objs::InsertObj(objbuttn, OBJ_BUTTON, 10);
	//デバッグ--------------------------------------------



	//BGM再生
	//Audio::Start(STAGE1);

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

	p = Save::ExternalDataOpen(L"Stage02.csv", &size);//外部データ読み込み
	
	if (p == nullptr)
	{
		MessageBox(0, L"マップデータが見つかりませんでした。", NULL, MB_OK);
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

	
	//背景画像読み込み
	Draw::LoadImageW(L"background.png", GRA_BACKGROUND, TEX_SIZE_1536);

	//プレイヤー画像読み込み
	Draw::LoadImageW(L"Hero.png", GRA_HERO, TEX_SIZE_1024);

	//主人公の弾画像読み込み
	Draw::LoadImageW(L"Hero_bullet.png", GRA_HERO_BULLET, TEX_SIZE_64);

	//ブロック画像読み込み
	Draw::LoadImageW(L"block.png", GRA_BLOCK, TEX_SIZE_128);

	//リフト画像読み込み
	Draw::LoadImageW(L"Lift.png", GRA_LIFT, TEX_SIZE_128);

	//ボス画像読み込み
	Draw::LoadImageW(L"image.png", GRA_BOSS, TEX_SIZE_1024);

	//ハシゴ画像読み込み
	Draw::LoadImageW(L"Ladders.png", GRA_LADDERS, TEX_SIZE_64);

	//ドア & 錠画像読み込み
	Draw::LoadImageW(L"Door.png", GRA_DOOR, TEX_SIZE_128);

	//木(ギミック)画像読み込み
	Draw::LoadImageW(L"Wood.png", GRA_WOOD, TEX_SIZE_128);
	
	//敵画像読み込み
	Draw::LoadImageW(L"Snake.png", GRA_ENEMY, TEX_SIZE_256);

	//レバースイッチ画像読み込み
	Draw::LoadImageW(L"Lever.png", GRA_LEVER_SWICH, TEX_SIZE_128);

	//岩画像読み込み
	Draw::LoadImageW(L"rock.png", GRA_ROCK, TEX_SIZE_256);

	//Water(水上)画像読み込み
	Draw::LoadImageW(L"Water.png", GRA_AQUATIC, TEX_SIZE_256);

	//Water波なし(水中)画像読み込み  消去禁止。いります！
	Draw::LoadImageW(L"WaterBlock.png", GRA_UNDER_WATER, TEX_SIZE_256);
	
	//ロープスイッチ画像読み込み
	Draw::LoadImageW(L"RopeSwitch.png", GRA_ROPE_SWITCH, TEX_SIZE_64);

	//大砲画像読み込み
	Draw::LoadImageW(L"image4.png", GRA_CANNON, TEX_SIZE_64);
	
	//看板の枠線画像読み込み
	Draw::LoadImageW(L"Sign.png", GRA_SIGN_FRAME, TEX_SIZE_256);
	
	//ボタン読み込み
	Draw::LoadImageW(L"button.png", GRA_BUTTON, TEX_SIZE_128);

	//lastwall(仮)画像読み込み
	Draw::LoadImageW(L"Lastwall.png", GRA_LAST_WALL, TEX_SIZE_256);//上
	Draw::LoadImageW(L"Openwall.png", GRA_OPEN_WALL, TEX_SIZE_512);//下

	//ライフ(仮)画像読み込み
	Draw::LoadImageW(L"zanki.png", GRA_LIFE, TEX_SIZE_64);
	

	//看板(本体)画像読み込み
	//Draw::LoadImageW(L"", GRA_SIGN_MAIN, TEX_SIZE_256);イラスト決まってから読み込んでください
	
}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{


//BGM--------------------------------------------------------

	//ステージ1
	Audio::LoadAudio(STAGE1, L"Grassland1.wav",SOUND_TYPE::BACK_MUSIC);

//------------------------------------------------------------

//SE--------------------------------------------------------
	
	//弾の発射
	Audio::LoadAudio(FIRING, L"Firing1.wav", SOUND_TYPE::EFFECT);

	//縄の打ち出し
	Audio::LoadAudio(ROPE, L"Rope1.wav", SOUND_TYPE::EFFECT);

	//岩の爆発
	Audio::LoadAudio(ROCK, L"Rock1.wav", SOUND_TYPE::EFFECT);

	//扉の開閉
	Audio::LoadAudio(DOOR, L"Door1.wav", SOUND_TYPE::EFFECT);

	//木の転倒
	Audio::LoadAudio(TREE, L"Tree1.wav", SOUND_TYPE::EFFECT);

//------------------------------------------------------------


}