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

	AudioDataLoading();//音楽データ読み込み関数
	MapDataLoading(m_map);//マップ情報を読み込み
	ImageDataLoading();//画像データ読み込み関数
	
	
    //Mapオブジェクトを作成する
	CObjMap* objmap = new CObjMap(m_map,g_remaining);
	Objs::InsertObj(objmap, OBJ_MAP, 10);

	//背景オブジェクトを作成する
	CObjBackGround* objback_ground = new CObjBackGround();
	Objs::InsertObj(objback_ground, OBJ_BACKGROUND, 1);

	//タイム
	CObjTime* objtime = new CObjTime();
	Objs::InsertObj(objtime, OBJ_TIME, 100);

	//デバッグ　”使い終わったら消してください！”----------------
	
	//要らんの--------------------------------------------------
	//要るの--------------------------------------------------

	//回転床テスト用----------
	//当たり判定のバグがあったので残しています。バグが取れたら消してください

	//CObjRollBlock* objrollblock = new CObjRollBlock(18,20,2);
	//Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 10);

	//objrollblock = new CObjRollBlock(10, 15, 1);
	//Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 10);
	//------------------------------

	//ステージ５のボス(デバッグ中。消さないで)
	//CObjStage5Boss* objstage5_boss = new CObjStage5Boss(10,14);
	//Objs::InsertObj(objstage5_boss, OBJ_STAGE5_BOSS, 9);


	//デバッグ--------------------------------------------------


	//BGM再生
	/*
	
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

	////デバッグ用ステージ番号調整用
	//UserData* s = (UserData*)Save::GetData();
	//s->stagenum = 2;
	////----------------

	//ステージ番号ごとにステージ読み込み
	switch (((UserData*)Save::GetData())->stagenum )
	{
	case 1:
		Audio::Start(STAGE);
		p = Save::ExternalDataOpen(L"stage1.csv", &size);//外部データ読み込み
		break;
	case 2:
		Audio::Start(STAGE);
		p = Save::ExternalDataOpen(L"stage2.csv", &size);//外部データ読み込み
		break;
	case 3:
		p = Save::ExternalDataOpen(L"stage3.csv", &size);//外部データ読み込み
		break;
	case 5:
		Audio::Start(STAGE);
		p=Save::ExternalDataOpen(L"stage5.csv", &size);//外部データ読み込み
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
		//Water画像読み込み
		Draw::LoadImageW(L"Image\\Water.png", GRA_AQUATIC, TEX_SIZE_1024);
		//すり抜けるブロック画像読み込み
		Draw::LoadImageW(L"Image\\Throughblock.png", GRA_THROUGH_BLOCK, TEX_SIZE_64);
		//ボス画像読み込み
		Draw::LoadImageW(L"Image\\Gorira.png", GRA_BOSS, TEX_SIZE_1024);
		//ゴリラの投擲物読み込み
		Draw::LoadImageW(L"Image\\Coconut.png", GRA_COCONUT, TEX_SIZE_32);
		break;
	//ステージ３
	case 3:
		//リフト画像読み込み
		Draw::LoadImageW(L"Image\\Lift\\Stage3.png", GRA_LIFT, TEX_SIZE_128);
		//ブロック画像読み込み
		Draw::LoadImageW(L"Image\\Block\\Stage3.png", GRA_BLOCK, TEX_SIZE_128);
		//キャノンの読み込み
		Draw::LoadImageW(L"Image\\Cannon.png", GRA_CANNON, TEX_SIZE_64);
		//lastwall3画像の読み込み
		Draw::LoadImageW(L"Image\\Lastwall3.png", GRA_LAST_WALL, TEX_SIZE_256);//上
		Draw::LoadImageW(L"Image\\Openwall3.png", GRA_OPEN_WALL, TEX_SIZE_512);//下
		break;
	//ステージ４
	case 4:
	//ステージ５
	case 5:
		//ステージ５の背景画像の読み込み
		Draw::LoadImageW(L"Image\\BackGround\\Stage5.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//ブロック画像読み込み
		Draw::LoadImageW(L"Image\\Block\\Stage5.png", GRA_BLOCK, TEX_SIZE_128);
		//回転ブロックの画像読み込み
		Draw::LoadImageW(L"Image\\RollBlock.png", GRA_ROLL_BLOCK, TEX_SIZE_256);
		Draw::LoadImageW(L"Image\\Rotate_Block2.png", GRA_ROLL_BLOCK2, TEX_SIZE_256);
		//金網ブロックの読み込み
		Draw::LoadImageW(L"Image\\Block\\Buttery_Upper_Floor.png", GRA_ROLL_BLOCK, TEX_SIZE_256);
		//ステージ5の大砲
		Draw::LoadImageW(L"Image\\Stage5Cannon.png", GRA_CANNON, TEX_SIZE_128);
		//ステージ5の大砲の弾
		Draw::LoadImageW(L"Image\\Cannon_Laser_Beam.png", GRA_CANNON_BEAM, TEX_SIZE_16);
		//回転ブロックの仕掛けのスイッチの画像読み込み
		Draw::LoadImageW(L"Image\\Vis_Blackball.png", GRA_BLACK_BALL, TEX_SIZE_16);
		//針の読み込み
		Draw::LoadImageW(L"Image\\Needle.png", GRA_NEEDLE, TEX_SIZE_32);
		//針の土台の読み込み
		Draw::LoadImageW(L"Image\\Needle stand.png", GRA_NEEDLE_STAND, TEX_SIZE_64);
		//ロープでぶら下がることができるギミック
		Draw::LoadImageW(L"Image\\Vis_Blackball2.png", GRA_TARZAN_POINT, TEX_SIZE_16);
		
		break;

	//画像が用意されていない場合
	default:
		//背景画像読み込み
		Draw::LoadImageW(L"Image\\BackGround\\Stage1.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//リフト画像読み込み
		Draw::LoadImageW(L"Image\\Lift\\Stage1.png", GRA_LIFT, TEX_SIZE_128);
		//ブロック画像読み込み
		Draw::LoadImageW(L"Image\\Block\\Stage1.png", GRA_BLOCK, TEX_SIZE_128);

		//ドア & 錠画像読み込み
		Draw::LoadImageW(L"Image\\Door.png", GRA_DOOR, TEX_SIZE_256);
		break;
	}
	
	//プレイヤー画像読み込み
	Draw::LoadImageW(L"Image\\Hero.png", GRA_HERO, TEX_SIZE_1024);

	//主人公の弾画像読み込み
	Draw::LoadImageW(L"Image\\Hero_bullet.png", GRA_HERO_BULLET, TEX_SIZE_64);
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

	//ロープスイッチ画像読み込み
	Draw::LoadImageW(L"Image\\RopeSwitch.png", GRA_ROPE_SWITCH, TEX_SIZE_64);
	
	//看板の枠線画像読み込み
	Draw::LoadImageW(L"Image\\Sign.png", GRA_SIGN_FRAME, TEX_SIZE_256);
	
	//看板の読み込み
	Draw::LoadImageW(L"Image\\Billboard_stage1.png", GRA_SIGN, TEX_SIZE_64);

	//ボタン読み込み
	Draw::LoadImageW(L"Image\\button.png", GRA_BUTTON, TEX_SIZE_128);

	//lastwall画像読み込み
	Draw::LoadImageW(L"Image\\Lastwall.png", GRA_LAST_WALL, TEX_SIZE_256);//上
	Draw::LoadImageW(L"Image\\Openwall.png", GRA_OPEN_WALL, TEX_SIZE_512);//下

	//ライフ(仮)画像読み込み
	Draw::LoadImageW(L"Image\\zanki.png", GRA_LIFE, TEX_SIZE_64);
	
	//回転ブロックのスイッチ
	Draw::LoadImageW(L"Image\\Vis_Blackball.png", GRA_ROLL_BLOCK_SWITCH, TEX_SIZE_16);

	//ステージ５ボス胴腕接続電気
	Draw::LoadImageW(L"Image\\Lastboss_Electric.png", GRA_STAGE5_BOSS_ELECTRIC, TEX_SIZE_512);
	//ステージ５ボス胴体
	Draw::LoadImageW(L"Image\\Lastboss_Body.png", GRA_STAGE5_BOSS_BODY, TEX_SIZE_256);
	//ステージ５ボス眼球
	Draw::LoadImageW(L"Image\\Lastboss_Eye.png", GRA_STAGE5_BOSS_EYE, TEX_SIZE_256);
	//ステージ５ボス腕
	Draw::LoadImageW(L"Image\\Lastboss_Arms.png", GRA_STAGE5_BOSS_ARMS_ALL, TEX_SIZE_2048);
	

}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{
	//ステージ別の画像読み込み
	switch (((UserData*)Save::GetData())->stagenum)
	{
		//ステージ１
	case 1:
		//BGM---------------------------------------------------------
		Audio::LoadAudio(STAGE, L"BGM\\Grassland6.wav", BACK_MUSIC);
		//SE----------------------------------------------------------
		//木の転倒
		Audio::LoadAudio(TREE, L"SE\\Tree3.wav", EFFECT);
		//リフト(引っ張る)
		Audio::LoadAudio(PULLLIFT, L"SE\\LiftTrickPull.wav", EFFECT);
		//リフト(離す)
		Audio::LoadAudio(RELEASELIFT, L"SE\\LiftTrickRelease.wav", EFFECT);
		break;

	case 2:
		//ステージ2
		//BGM---------------------------------------------------------
		Audio::LoadAudio(STAGE, L"BGM\\Jangle.wav", BACK_MUSIC);
		//ステージ2_BOSS
		Audio::LoadAudio(BOSS, L"BGM\\Boss2.wav", BACK_MUSIC);
		//SE----------------------------------------------------------
		//ボタン
		Audio::LoadAudio(BUTTON, L"SE\\Switch2.wav", EFFECT);
		//水の流れる音
		Audio::LoadAudio(WAVE, L"SE\\Wave.wav", EFFECT);
		//ゴリラの投擲音
		Audio::LoadAudio(GORILLATHROW, L"SE\\Gorilla_Throw.wav", EFFECT);
		break;

	case 5:
		//ステージ5
		//BGM----------------------------------------------------------
		Audio::LoadAudio(STAGE, L"BGM\\Temple1.wav", BACK_MUSIC);
		Audio::LoadAudio(BOSS, L"BGM\\LastBoss.wav", BACK_MUSIC);
		//SE-----------------------------------------------------------
		//回転ブロックの音
		Audio::LoadAudio(ROLLBLOCK, L"SE\\BlockRocate.wav", EFFECT);
		//ボスの拡散弾が出現するときの音
		Audio::LoadAudio(BOSSPOP, L"SE\\BossPop.wav", EFFECT);
		//ボスのレーザーが出現するときの音
		Audio::LoadAudio(BOSSLASER, L"SE\\BossLaser.wav", EFFECT);
		//地面が落ちる音
		Audio::LoadAudio(GROUND, L"SE\\Ground.wav", EFFECT);
		//大砲の拡散弾の音
		Audio::LoadAudio(DIFFUSION, L"SE\\Diffusion.wav", EFFECT);
		break;
	}
	//共通SE--------------------------------------------------------------
	//弾の発射
	Audio::LoadAudio(FIRING, L"SE\\Firing1.wav", EFFECT);

	//縄の打ち出し
	Audio::LoadAudio(ROPE, L"SE\\Rope2.wav", EFFECT);

	//岩の爆発
	Audio::LoadAudio(ROCK, L"SE\\Rock2.wav", EFFECT);

	//最後の壁の開閉
	Audio::LoadAudio(WALL, L"SE\\Door1.wav", EFFECT);

	//木のドアの開錠
	Audio::LoadAudio(DOOR, L"SE\\Wood Door.wav", EFFECT);

	//敵に着弾
	Audio::LoadAudio(LANDING, L"SE\\Landing1.wav", EFFECT);

	//レバースイッチ
	Audio::LoadAudio(LEVER, L"SE\\Lever1.wav", EFFECT);

	//敵の弾丸
	Audio::LoadAudio(ENEMYFIR, L"SE\\Enemy Fir3.wav", EFFECT);
	//------------------------------------------------------------
}