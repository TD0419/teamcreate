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

int g_remaining;//残機管理用変数

//コンストラクタ
CSceneMain::CSceneMain()
{
	g_remaining = 3;
}

//コンストラクタ(リスタート用)
//引数：変動させる量
CSceneMain::CSceneMain(int n)
{
	g_remaining += n;
}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//残機が０未満になったらGameOver画面へ移動する
	if (g_remaining < 0)
	{
		Scene::SetScene(new CSceneGameOver());
		return;
	}

	MapDataLoading(m_map);//マップ情報を読み込み
	ImageDataLoading();//画像データ読み込み関数
	AudioDataLoading();//音楽データ読み込み関数
	
    //Mapオブジェクトを作成する
	CObjMap* objmap = new CObjMap(m_map);
	Objs::InsertObj(objmap, OBJ_MAP, 10);

	//主人公オブジェクトを作成する
	CObjHero* objhero = new CObjHero(0,0,g_remaining);
	Objs::InsertObj(objhero, OBJ_HERO, 10);

	//背景オブジェクトを作成する
	CObjBackGround* objback_ground = new CObjBackGround();
	Objs::InsertObj(objback_ground, OBJ_BACKGROUND, 1);

	//タイム
	CObjTime* objtime = new CObjTime();
	Objs::InsertObj(objtime, OBJ_TIME, 100);

	//デバッグ　”使い終わったら消してください！”----------------
	//要らんの--------------------------------------------------



	//要るの-----------------------------------------------

	//テスト用回転床パターン1
	CObjRollBlock* p = new CObjRollBlock(10, 20,1);
	Objs::InsertObj(p, OBJ_ROLL_BLOCK, 10);

	//デバッグ--------------------------------------------

	//BGM再生
	Audio::Start(STAGE1);
	/*Audio::Start(STAGE2);
	Audio::Start(STAGE5);*/

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
	
	//初期化をどこかでしないといけないけど初期化の場所を指定されていなかったので一応ここで初期化をする
	

	//ステージ番号ごとにステージ読み込み
	switch (((UserData*)Save::GetData())->stagenum)
	{
		
	case 1:
		p = Save::ExternalDataOpen(L"stage1.csv", &size);//外部データ読み込み
		break;
	case 2:
		p = Save::ExternalDataOpen(L"stage2.csv", &size);//外部データ読み込み
		break;
	case 3:
		p = Save::ExternalDataOpen(L"StageA.csv", &size);//外部データ読み込み
		break;
	default:
		break;
	}
	
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
	//ステージ別の画像読み込み
	switch (((UserData*)Save::GetData())->stagenum)
	{
	//ステージ１
	case 1:
		//背景画像読み込み
		Draw::LoadImageW(L"Image\\BackGround\\Stage1.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//リフト画像読み込み
		Draw::LoadImageW(L"Image\\Lift\\Stage1.png", GRA_LIFT, TEX_SIZE_128);
		//ブロック画像読み込み
		Draw::LoadImageW(L"Image\\Block\\Stage1.png", GRA_BLOCK, TEX_SIZE_128);
		break;
	//ステージ２
	case 2:
		//背景画像読み込み
		Draw::LoadImageW(L"Image\\BackGround\\Stage2.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//リフト画像読み込み
		Draw::LoadImageW(L"Image\\Lift\\Stage2.png", GRA_LIFT, TEX_SIZE_128);
		//ブロック画像読み込み
		Draw::LoadImageW(L"Image\\Block\\Stage2.png", GRA_BLOCK, TEX_SIZE_128);
		break;
	//ステージ３
	case 3:
	//ステージ４
	case 4:
	//ステージ５
	case 5:
	//画像が用意されていない場合
	default:
		//背景画像読み込み
		Draw::LoadImageW(L"Image\\BackGround\\Stage1.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//リフト画像読み込み
		Draw::LoadImageW(L"Image\\Lift\\Stage1.png", GRA_LIFT, TEX_SIZE_128);
		//ブロック画像読み込み
		Draw::LoadImageW(L"Image\\Block\\Stage1.png", GRA_BLOCK, TEX_SIZE_128);
		break;
	}
	
	//プレイヤー画像読み込み
	Draw::LoadImageW(L"Image\\Hero.png", GRA_HERO, TEX_SIZE_1024);

	//主人公の弾画像読み込み
	Draw::LoadImageW(L"Image\\Hero_bullet.png", GRA_HERO_BULLET, TEX_SIZE_64);

	//すり抜けるブロック画像読み込み
	Draw::LoadImageW(L"Image\\Throughblock.png", GRA_THROUGH_BLOCK, TEX_SIZE_64);

	//ボス画像読み込み
	Draw::LoadImageW(L"Image\\image.png", GRA_BOSS, TEX_SIZE_1024);

	//ハシゴ画像読み込み
	Draw::LoadImageW(L"Image\\Ladders.png", GRA_LADDERS, TEX_SIZE_64);

	//ドア & 錠画像読み込み
	Draw::LoadImageW(L"Image\\Door.png", GRA_DOOR, TEX_SIZE_256);

	//木(ギミック)画像読み込み
	Draw::LoadImageW(L"Image\\Wood.png", GRA_WOOD, TEX_SIZE_512);
	
	//敵画像読み込み
	Draw::LoadImageW(L"Image\\Snake.png", GRA_ENEMY, TEX_SIZE_256);

	//レバースイッチ画像読み込み
	Draw::LoadImageW(L"Image\\Lever.png", GRA_LEVER_SWICH, TEX_SIZE_128);

	//岩画像読み込み
	Draw::LoadImageW(L"Image\\rock.png", GRA_ROCK, TEX_SIZE_512);

	//Water(水上)画像読み込み
	Draw::LoadImageW(L"Image\\Water.png", GRA_AQUATIC, TEX_SIZE_256);

	//Water波なし(水中)画像読み込み  消去禁止。いります！
	Draw::LoadImageW(L"Image\\WaterBlock.png", GRA_UNDER_WATER, TEX_SIZE_256);
	
	//ロープスイッチ画像読み込み
	Draw::LoadImageW(L"Image\\RopeSwitch.png", GRA_ROPE_SWITCH, TEX_SIZE_64);

	//大砲画像読み込み
	Draw::LoadImageW(L"Image\\image4.png", GRA_CANNON, TEX_SIZE_64);
	
	//看板の枠線画像読み込み
	Draw::LoadImageW(L"Image\\Sign.png", GRA_SIGN_FRAME, TEX_SIZE_256);
	
	//看板の読み込み
	Draw::LoadImageW(L"Image\\Billboard_stage1.png", GRA_SIGN, TEX_SIZE_64);

	//ボタン読み込み
	Draw::LoadImageW(L"Image\\button.png", GRA_BUTTON, TEX_SIZE_128);

	//lastwall画像読み込み
	Draw::LoadImageW(L"Image\\Lastwall.png", GRA_LAST_WALL, TEX_SIZE_256);//上
	Draw::LoadImageW(L"Image\\Openwall.png", GRA_OPEN_WALL, TEX_SIZE_512);//下

	//lastwall3画像の読み込み
	Draw::LoadImageW(L"Image\\Lastwall3.png", GRA_LAST_WALL3, TEX_SIZE_256);//上
	Draw::LoadImageW(L"Image\\Openwall3.png", GRA_OPEN_WALL3, TEX_SIZE_512);//下

	//ライフ(仮)画像読み込み
	Draw::LoadImageW(L"Image\\zanki.png", GRA_LIFE, TEX_SIZE_64);
	
	//看板(本体)画像読み込み
	//Draw::LoadImageW(L"", GRA_SIGN_MAIN, TEX_SIZE_256);イラスト決まってから読み込んでください

	//回転ブロックの画像読み込み
	Draw::LoadImageW(L"Image\\RollBlock.png", GRA_ROLL_BLOCK, TEX_SIZE_256);

	//ゴリラの投擲物読み込み
	Draw::LoadImageW(L"Image\\Coconut.png", GRA_COCONUT, TEX_SIZE_32);
}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{
//BGM--------------------------------------------------------

	//ステージ1
	Audio::LoadAudio(STAGE1, L"Grassland2.wav",SOUND_TYPE::BACK_MUSIC);
	//ステージ2
	Audio::LoadAudio(STAGE2, L"Jangle1.wav", SOUND_TYPE::BACK_MUSIC);

	//ステージ2_BOSS
	Audio::LoadAudio(STAGE2_BOSS, L"BOSS1.wav", SOUND_TYPE::BACK_MUSIC);

	//ステージ5
	Audio::LoadAudio(STAGE5, L"Temple1.wav", SOUND_TYPE::BACK_MUSIC);
//------------------------------------------------------------

//SE--------------------------------------------------------
	//弾の発射
	Audio::LoadAudio(FIRING, L"Firing1.wav", SOUND_TYPE::EFFECT);

	//縄の打ち出し
	Audio::LoadAudio(ROPE, L"Rope2.wav", SOUND_TYPE::EFFECT);

	//岩の爆発
	Audio::LoadAudio(ROCK, L"Rock1.wav", SOUND_TYPE::EFFECT);

	//最後の壁の開閉
	Audio::LoadAudio(WALL, L"Door1.wav", SOUND_TYPE::EFFECT);

	//木の転倒
	Audio::LoadAudio(TREE, L"Tree1.wav", SOUND_TYPE::EFFECT);

	//ドアの開錠
	Audio::LoadAudio(DOOR, L"Wood Door.wav", SOUND_TYPE::EFFECT);

	//敵に着弾
	Audio::LoadAudio(LANDING, L"Landing1.wav", SOUND_TYPE::EFFECT);

	//レバースイッチ
	Audio::LoadAudio(LEVER, L"Lever1.wav", SOUND_TYPE::EFFECT);

	//ボタン
	Audio::LoadAudio(BUTTON, L"Switch3.wav", SOUND_TYPE::EFFECT);

	//木の転倒
	Audio::LoadAudio(ENEMYFIR, L"Enemy Fir1.wav", SOUND_TYPE::EFFECT);

	//リフト
	Audio::LoadAudio(LIFT, L"Lift Trick Pull", SOUND_TYPE::EFFECT);

	
//------------------------------------------------------------

}