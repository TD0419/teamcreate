#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_HERO,			//主人公
	OBJ_BUTTON,			//ボタン
    OBJ_BULLET,			//弾丸(主人公用)
	OBJ_ENEMY_BULLET,	//弾丸(敵用)
	OBJ_ROCK,			//岩
    OBJ_BLOCK,			//ブロック
	OBJ_REFLECT_BLOCK,	//弾を反射するブロック
	OBJ_LIFT,			//リフト
	OBJ_MAP,			//マップ
    OBJ_WOOD,			//木
	OBJ_WATER,			//水
    OBJ_ROPE_SWITCH,	//ロープスイッチ
	OBJ_LADDERS,		//梯子
	OBJ_SIGN,			//看板
	OBJ_ROPE,           //縄（スイッチに引っ掛ける縄）
	OBJ_ENEMY,			//敵
	OBJ_BOSS_ENEMY,		//ボス
	OBJ_STAGE3_BOSS,	//第三ステージボス
	OBJ_TITLE,			//タイトル
	OBJ_GAME_OVER,		//ゲームオーバー
	OBJ_GAME_CLEAR,		//ゲームクリア
	OBJ_ENDLESS_SPRING,//敵生成システム(エンドレス沸き)
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,		//プレイヤー
	ELEMENT_ENEMY,		//敵
	ELEMETN_ITEM,		//アイテム
	ELEMENT_GIMMICK,	//ギミック
	ELEMENT_BLOCK,		//ブロック
};
//------------------------------------------------

//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	
};
//------------------------------------------------


//ゲーム内で使用されるグローバル変数・定数・列挙--

//ウィンドウサイズ
#define WINDOW_SIZE_W	(1024)	//横
#define WINDOW_SIZE_H	(768)	//縦
//解像度サイズ
#define PIXEL_SIZE_W	(1024)	//横
#define PIXEL_SIZE_H	(768)	//縦

//マップサイズ
#define MAP_X_MAX (100)	//mapの最大値X
#define MAP_Y_MAX (10)	//mapの最大値Y
#define MAP_WINDOW_MAX_X (int)( WINDOW_SIZE_W/ BLOCK_SIZE )	//画面内に収まるmapの最大値X
#define MAP_WINDOW_MAX_Y (int)( WINDOW_SIZE_H/ BLOCK_SIZE )	//画面内に収まるmapの最大値Y

//マップの番号とオブジェクトの対応　（仮）
#define MAP_SPACE	(0)		//何もない場所
#define MAP_BLOCK	(1)		//ブロック(ノーマル)
#define MAP_LADDERS	(2)		//はしご
#define MAP_BUTTON	(3)		//ボタン
#define MAP_ROPE_SWITCH	(4) //ロープスイッチ
#define MAP_LIFT	(5)		//リフト
#define MAP_ROCK	(6)		//岩
#define MAP_WOOD	(7)		//木
#define MAP_WATER	(8)		//水
#define MAP_ENEMY	(9)		//敵
#define MAP_BOSS	(10)	//ボス

//オブジェクトのサイズ
#define HERO_SIZE_X (64.0f)	//主人公の横サイズ	
#define HERO_SIZE_Y (128.0f)//主人公の縦サイズ	
#define ENEMY_SIZE	(64.0f) //敵のサイズ(仮)
#define BULLET_SIZE (20.0f)	//弾丸サイズ（仮）
#define BLOCK_SIZE	(32.0f) //ブロックのサイズ（仮）	
#define WATER_SIZE	(32.0f) //水のサイズ（仮）
#define LADDERS_SIZE (32.0f)//はしごのサイズ（仮）
#define BUTTON_SIZE	(32.0f)//ボタンサイズ（仮）
#define ROPE_SWITCH_SIZE	(32.0f)	//ロープスイッチのサイズ（仮）
#define LIFT_SIZE	(32.0f)//リフトサイズ(仮)
#define ROCK_SIZE	(32.0f)//岩サイズ（仮）
#define WOOD_SIZE	(32.0f)//木サイズ(仮)
#define BOSS_SIZE	(32.0f)//BOSSサイズ(仮)


//スクロールのライン　（要調整）
#define SCROLL_LINE_LEFT	(480.0f)							//左
#define SCROLL_LINE_RIGHT	(WINDOW_SIZE_W - SCROLL_LINE_LEFT)	//右
#define SCROLL_LINE_UP		(250.0f)							//上
#define SCROLL_LINE_DOWN	(WINDOW_SIZE_H - SCROLL_LINE_UP)	//下

//オブジェクトの生成ライン（要調整）
#define CREATE_LINE_LEFT	(1)														//左
#define CREATE_LINE_RIGHT	( (int)(WINDOW_SIZE_W / BLOCK_SIZE) - CREATE_LINE_LEFT)	//右
#define CREATE_LINE_UP		(1)														//上	
#define CREATE_LINE_DOWN	( (int)(WINDOW_SIZE_H / BLOCK_SIZE) - CREATE_LINE_UP)	//下

//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ-----------------
#include "ObjHero.h"		//主人公
#include "ObjButton.h"		//ボタン
#include "ObjBullet.h"		//弾丸(主人公用)
#include "ObjEnemyBullet.h"	//弾丸(敵用)
#include "ObjRock.h"		//岩
#include "ObjBlock.h"		//ブロック
#include "ObjReflectBlock.h"//弾を反射するブロック
#include "ObjLift.h"		//リフト
#include "ObjLadders.h"		//梯子
#include "ObjMap.h"			//マップ
#include "ObjWood.h"		//木	
#include "ObjWater.h"		//水
#include "ObjRopeSwitch.h"	//ロープスイッチ
#include "ObjEnemy.h"		//敵
#include "ObjBossEnemy.h"	//ボス
#include "ObjStage3Boss.h"  //第三ステージボス
#include "ObjTitle.h"		//タイトル
#include "ObjSign.h"		//看板
#include "ObjRope.h"        //縄（スイッチに引っ掛ける縄）
#include "ObjGameClear.h"	//クリア
#include "ObjGameOver.h"	//ゲームオーバー
#include "ObjEndlessSpring.h"//敵生成システム(エンドレス沸き)
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"		//メイン
#include "SceneTitle.h"		//タイトル
#include "SceneGameOver.h"	//ゲームオーバー
#include "SceneGameClear.h"	//クリア
//-----------------------------------------------


//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneMain
//-----------------------------------------------