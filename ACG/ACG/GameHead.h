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
	OBJ_LIFT_MOVE,      //動くリフト
	OBJ_MAP,			//マップ
    OBJ_WOOD,			//木
	OBJ_WATER,			//水
    OBJ_ROPE_SWITCH,	//ロープスイッチ
	OBJ_LADDERS,		//梯子
	OBJ_SIGN,			//看板
	OBJ_ROPE,           //縄（スイッチに引っ掛ける縄）
	OBJ_ENEMY,			//敵
	OBJ_BOSS,			//ボス
	OBJ_STAGE3_BOSS,	//第三ステージボス
	OBJ_BOSS_DROP_KEY,	//ボスが落とす鍵
	OBJ_TITLE,			//タイトル
	OBJ_GAME_OVER,		//ゲームオーバー
	OBJ_GAME_CLEAR,		//ゲームクリア
	OBJ_ENDLESS_SPRING, //敵生成システム(エンドレス沸き)
	OBJ_LEVER_SWICH,    //レバースイッチ
	OBJ_DOOR,           //ドア
	OBJ_THROUGHT_BLOCK,	//スルーブロック
	OBJ_FALLING_WALLS,  //落下壁
	OBJ_BACKGROUND,		//バッググラウンド(背景)
	OBJ_CANNON,		    //砲台
	OBJ_LAST_WALL,		//最後の壁
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
enum MAP_BER
{
	MAP_SPACE		 , 	//何もない場所
	MAP_BLOCK		 ,	//ブロック(ノーマル)
	MAP_LADDERS		 ,	//はしご
	MAP_BUTTON		 ,	//ボタン
	MAP_ROPE_SWITCH	 ,	//ロープスイッチ
	MAP_LIFT		 ,	//リフト
	MAP_ROCK		 ,	//岩
	MAP_WOOD		 ,	//木
	MAP_WATER		 ,	//水
	MAP_ENEMY		 ,	//敵
	MAP_BOSS		 ,	//ボス
	MAP_STAGE3_BOSS  ,	//ステージ３のボス
	MAP_BLOCK2		 ,	//
	MAP_THROUGH_BLOCK,	//
	MAP_REFLECT_BLOCK,	//反射ブロック
	MAP_SIGN		 ,	//
	MAP_DOOR		 ,	//ドア
	MAP_LEVER_SWICH	 ,	//レバースイッチ
	MAP_FALLING_WALLS,  //落下壁
	MAP_LIFT_MOVE    ,  //動くリフト
};

//オブジェクトのサイズ
#define HERO_SIZE_WIDTH	      (64.0f)		//主人公の横サイズ	
#define HERO_SIZE_HEIGHT	  (128.0f)		//主人公の縦サイズ	
#define ENEMY_SIZE			  (64.0f)		//敵のサイズ(仮)
#define BULLET_SIZE			  (20.0f)		//弾丸サイズ（仮）
#define ROPE_SIZE			  (5.0f)		//ロープサイズ（仮）
#define BLOCK_SIZE			  (64.0f)		//ブロックのサイズ（仮）	
#define WATER_SIZE_WIDTH	  (64.0f)		//水の横サイズ
#define WATER_SIZE_HEIGHT	  (64.0f)       //水の縦サイズ
#define LADDERS_SIZE		  (64.0f)		//はしごのサイズ
#define BUTTON_SIZE			  (64.0f)		//ボタンサイズ（仮）
#define SIGN_SIZE			  (32.0f)		//看板のサイズ（仮）
#define LEVER_SWITCH_SIZE	  (64.0f)	    //レバースイッチのサイズ
#define ROPE_SWITCH_SIZE	  (64.0f)	    //ロープスイッチのサイズ
#define LIFT_SIZE_WIDTH		  (128.0f)		//リフトサイズ横サイズ
#define LIFT_SIZE_HEIGHT	  (32.0f)		//リフトサイズ縦サイズ
#define LIFT_MOVE_SIZE_WIDTH  (128.0f)      //動くリフトサイズ横サイズ
#define LIFT_MOVE_SIZE_HEIGHT (32.0f)       //動くリフトサイズ縦サイズ
#define ROCK_SIZE_WIDTH		  (170.0f)		//岩の横サイズ（仮
#define ROCK_SIZE_HEIGHT	  (240.0f)		//岩の縦サイズ（仮
#define WOOD_SIZE			  (320.0f)		//木のサイズ(仮)
#define BOSS_SIZE			  (170.0f)		//BOSSサイズ(仮)
#define BOSS_DORP_KEY_SIZE	  (32.0f)	    //ボスドロップキーサイズ(仮)
#define DOOR_SIZE_WIDTH		  (32.0f)		//ドアの横サイズ(仮)
#define DOOR_SIZE_HEIGHT	  (128.0f)		//ドアの縦サイズ(仮)
#define SIGN_SIZE			  (32.0f)		//看板サイズ(仮)
//#define BOSS_CORRECTION (90.0f)	    //ボスサイズ補正(仮)
#define THROUGHT_BLOCK_SIZE	 (64.0f)	    //スルーブロックサイズ（仮）
#define FALLING_WALLS_SAIZE  (64.0f)		//落下壁サイズ(仮)
#define CANNON_SIZE_WIDTH	 (64.0f)		//砲台の横サイズ(仮)
#define CANNON_SIZE_HEIGHT	 (32.0f)		//砲台の縦サイズ(仮)

//スクロールのライン　（要調整）
#define SCROLL_LINE_LEFT	(464.0f)	//左
#define SCROLL_LINE_RIGHT	(560.0f)	//右
#define SCROLL_LINE_UP		(276.0f)	//上
#define SCROLL_LINE_DOWN	(400.0f)	//下

//オブジェクトの生成ライン（要調整）
#define CREATE_LINE_LEFT	(1)														//左
#define CREATE_LINE_RIGHT	( (int)(WINDOW_SIZE_W / BLOCK_SIZE) - CREATE_LINE_LEFT)	//右
#define CREATE_LINE_UP		(1)														//上	
#define CREATE_LINE_DOWN	( (int)(WINDOW_SIZE_H / BLOCK_SIZE) - CREATE_LINE_UP)	//下
//------------------------------------------------

//ゲーム内で使用するクラスヘッダ------------------
//------------------------------------------------

//ゲームシーンオブジェクトヘッダ-----------------
#include "ObjHero.h"			//主人公
#include "ObjButton.h"			//ボタン
#include "ObjBullet.h"			//弾丸(主人公用)
#include "ObjEnemyBullet.h"		//弾丸(敵用)
#include "ObjRock.h"			//岩
#include "ObjBlock.h"			//ブロック
#include "ObjReflectBlock.h"	//弾を反射するブロック
#include "ObjLift.h"			//リフト
#include "ObjLiftMove.h"        //動くリフト
#include "ObjLadders.h"			//はしご
#include "ObjMap.h"				//マップ
#include "ObjWood.h"			//木	
#include "ObjWater.h"			//水
#include "ObjRopeSwitch.h"		//ロープスイッチ
#include "ObjEnemy.h"			//敵
#include "ObjBoss.h"			//ボス
#include "ObjStage3Boss.h"		//第三ステージボス
#include "ObjBossDropKey.h"		//ボスが落とす鍵
#include "ObjTitle.h"			//タイトル
#include "ObjSign.h"			//看板
#include "ObjRope.h"			//縄（スイッチに引っ掛ける縄）
#include "ObjGameClear.h"		//クリア
#include "ObjGameOver.h"		//ゲームオーバー
#include "ObjEndlessSpring.h"	//敵生成システム(エンドレス沸き)
#include "ObjLeverSwich.h"		//レバースイッチ
#include "ObjDoor.h"			//ドア
#include "ObjThroughBlock.h"	//スルーブロック
#include "ObjFallingWalls.h"	//落下壁
#include "ObjBackGround.h"		//バッググラウンド(背景)
#include "ObjCannon.h"			//砲台
#include "ObjLastWall.h"		//最後の壁
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