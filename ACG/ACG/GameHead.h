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
	OBJ_STAGE5_BOSS,	//第五ステージボス
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
	OBJ_TIME,			//タイム
	OBJ_ROLL_BLOCK,		//回転するブロック
	OBJ_ROLL_BLOCK_SWITCH,//回転するブロック用のスイッチ
	OBJ_NEEDLE,			  //針
	OBJ_NEEDLE_STAND,	  //針の土台
	OBJ_TARZAN_POINT,	  //ロープでぶら下がることができるギミック
	OBJ_DIFFUSION_CANNON, //ステージ５の拡散弾キャノン
	OBJ_DIFFUSION_BULLET, //ステージ５の拡散弾
	OBJ_FALLING_LIFT,	  //乗ると落ちるリフト
	OBJ_FALLING_BLOCK,	  //ステージ5ボス戦専用落ちるブロック
	OBJ_STAGE5_BOSS_ARMS, //ステージ5ボスの腕
	OBJ_WIRE_MESH,		  //ステージ5の金網
	OBJ_DIFFUSION_SOURCE, //拡散弾の源
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
	int stagenum;	//ステージ番号
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
#define MAP_X_MAX (111)	//mapの最大値X←ステージによって変動するようにする必要がある
#define MAP_Y_MAX (24)	//mapの最大値Y
#define MAP_WINDOW_MAX_X (int)( WINDOW_SIZE_W/ BLOCK_SIZE )	//画面内に収まるmapの最大値X(16)
#define MAP_WINDOW_MAX_Y (int)( WINDOW_SIZE_H/ BLOCK_SIZE )	//画面内に収まるmapの最大値Y(12)

//マップの番号とオブジェクトの対応　（仮）
enum MAP_BER
{
	//全ステージ共通オブジェクト描画番号
	MAP_SPACE				, 			//何もない場所
	MAP_HERO_START			,			//heroのスタート位置(マップが届いたらこのコメントをはずす)
	MAP_BLOCK				,			//ブロック(ノーマル)

	//複数のステージで使用されるオブジェクト描画番号
	MAP_LADDERS				,			//はしご
	MAP_ROPE_SWITCH			,			//ロープスイッチ
	MAP_LEVER_SWICH			,			//レバースイッチ
	MAP_ROCK				,			//岩
	MAP_SIGN				,			//看板
	MAP_GOAL_DOOR			,			//ゴール用ドア
	MAP_LIFT_TYPE_MANUAL	,			//手動リフト(通常時は動かない。ギミックの過程で引っ張ると動かせる)
    MAP_LIFT_TYPE_AUTO_WIDTH	 ,		//自動横移動リフト(自動で左右に動く)	
	MAP_LIFT_TYPE_AUTO_LENGTH	 ,		//自動下移動リフト(自動で下方向に動く)
	MAP_ENEMY				,			//敵
	MAP_LAST_WALL			,			//次ステージへの入り口(最後の壁)
	
	//ステージ1のみに使用するオブジェクト描画番号
	MAP_WOOD				,			//木

	//ステージ2のみに使用するオブジェクト描画番号
	MAP_NO_LOOK_LADDERS		,			//見えないハシゴ
	MAP_BUTTON				,			//ボタン
	MAP_WATER				,			//水
	MAP_THROUGH_BLOCK		,			//通り抜けれるブロック
	MAP_BOSS				,			//ステージ２のボス

	//ステージ3のみに使用するオブジェクト描画番号
	MAP_FALLING_WALLS		,			//落下壁
	MAP_CANNON				,			//砲台
	MAP_REFLECT_BLOCK		,			//反射ブロック
	MAP_STAGE3_BOSS			,			//ステージ３のボス
	MAP_ENDLESS_SPRING		,			//敵自動生成ギミック
	MAP_OPEN_DOOR_SWITCH    ,			//シャッター開く用スイッチ	

	//ステージ5のみに使用するオブジェクト描画番号
	MAP_ROLL_BLOCK_TYPE_AUTO	,		//自動式回転するブロック
	MAP_ROLL_BLOCK_TYPE_MANUAL	,		//手動式90度回転するブロック
	MAP_TARZAN_POINT			,		//ロープでぶら下がれるギミック
	MAP_NEEDLE					,		//針
	MAP_NEEDLE_STAND			,		//針の土台
	MAP_DIFFUSION_CANNON		,		//拡散弾発射ギミック
	MAP_FALLING_LIFT			,		//乗ると落ちるリフト
	MAP_LIFT_TYPE_AUTO_UP		,		//自動上移動リフト(自動で上方向に動く)
	MAP_WIRE_MESH_FLOOR			,		//金網床
	MAP_FALLING_BLOCK           ,		//ボスステージ用落ちるブロック
	MAP_STAGE5_BOSS             ,		//ステージ5のボス
	MAP_BOSS_TARZAN_POINT		,		//ボス戦時に出現するロープでぶら下がれるギミック
};

//グラフィックID
enum GRAPHIC_ID
{
	GRA_BACKGROUND,		//背景
	GRA_HERO,			//プレイヤー
	GRA_HERO_BULLET,    //プレイヤーの弾
	GRA_BLOCK,			//ブロック
	GRA_THROUGH_BLOCK,  //すり抜けるブロック
	GRA_BOSS,			//ボス
	GRA_LADDERS,		//はしご
	GRA_LIFT,			//リフト
	GRA_DOOR,			//ドア
	GRA_WOOD,			//木
	GRA_ENEMY,			//敵
	GRA_LEVER_SWICH,	//レバースイッチ
	GRA_ROCK,			//岩
	GRA_AQUATIC,		//水上(波がある)
	GRA_UNDER_WATER,	//水中(波がない)
	GRA_ROPE_SWITCH,	//ロープスイッチ
	GRA_CANNON,			//砲台
	GRA_SIGN_FRAME,		//看板の枠組み
	GRA_BUTTON,			//ボタン
	GRA_LAST_WALL,		//壁(上部分の鉄部分)
	GRA_OPEN_WALL,		//開閉するシャッター(最後の壁用)
	GRA_LAST_WALL3,		//壁(上部分の鉄部分)
	GRA_OPEN_WALL3,		//開閉するシャッター(最後の壁用)
	GRA_LIFE,			//ライフ
	GRA_SIGN,			//看板
	GRA_ROLL_BLOCK,		//回転ブロック
	GRA_ROLL_BLOCK2,	//回転ブロック（パターン2）
	GRA_TITLE,			//タイトル
	GRA_GAME_OVER,		//ゲームオーバー
	GRA_GAME_CLEAR,		//ゲームクリア
	GRA_COCONUT,		//ココナッツ
	GRA_NEEDLE,         //針
	GRA_NEEDLE_STAND,   //針の土台
	GRA_TARZAN_POINT,	//ロープでぶら下がれるギミック

	GRA_BLACK_BALL,			//回転ブロックの仕掛けのスイッチ
	GRA_CANNON_BEAM,		//ステージ5の拡散弾
	GRA_WIRE_MASH,			//ステージ5の金網
	GRA_STAGE5_BOSS_ELECTRIC,	 	//ステージ5のボス胴腕接続電気
	GRA_STAGE5_BOSS_BODY,	//ステージ5のボス胴体
	GRA_STAGE5_BOSS_EYE,	//ステージ5のボス眼球
	GRA_STAGE5_BOSS_ARMS_ALL,      	//ステージ5のボス腕(左右腕)
	GRA_FALLING_LIFT,	//落ちるリフト
	GRA_HAND_LIFT,//手動で引っ張るリフト
	GRA_DIFFUSION_SOURCE,//拡散弾を撃つ弾
	GRA_BOSS_DIFFUSION,//ボスの発射する拡散弾
	GRA_STAGE5_BOSS_BULLET,//ボスの発射する弾
};

//音楽(BGM)
enum MUSIC
{
//BGM--------------------
	STAGE,      //ステージ
	BOSS,       //ボス
	GAMEOVER,	//ゲームオーバー
	TITLE,		//タイトル
	CLEAR,		//クリア
//SE---------------------
	FIRING		,//弾の発射
	ROPE		,//ロープの打ち出し
	ROCK		,//岩の爆発
	WALL		,//壁の開閉
	TREE		,//木の転倒
	DOOR		,//出口開閉
	LANDING		,//敵に着弾
	LEVER		,//レバー
	BUTTON		,//ボタン
	ENEMYFIR	,//敵の弾発射
	PULLLIFT	,//リフト(引っ張る)
	RELEASELIFT	,//リフト(離れる)
	WAVE		,//水の流れ
	GORILLATHROW,//ゴリラの投擲音
	ROLLBLOCK,	 //回転ブロック
	BOSSPOP,	 //ボスが撃つ弾が弾ける音(ボス拡散弾がでる時の音)
	BOSSLASER,	 //ボスのレーザービームの音
	GROUND,		 //地面が落ちる音
	DIFFUSION,	 //ステージ5の拡散弾
};

//オブジェクトのサイズ
#define HERO_SIZE_WIDTH	      (64.0f)		//主人公の横サイズ	
#define HERO_SIZE_HEIGHT	  (128.0f)		//主人公の縦サイズ	
#define ENEMY_SIZE			  (64.0f)		//敵のサイズ(仮)
#define BULLET_SIZE			  (20.0f)		//弾丸サイズ（仮）
#define ROPE_SIZE			  (5.0f)		//ロープサイズ（仮）
#define BLOCK_SIZE			  (64.0f)		//ブロックのサイズ（仮）	
#define WATER_SIZE_WIDTH	  (640.0f)		//水の横サイズ
#define WATER_SIZE_HEIGHT	  (192.0f)       //水の縦サイズ
#define LADDERS_SIZE		  (64.0f)		//はしごのサイズ
#define BUTTON_SIZE			  (64.0f)		//ボタンサイズ（仮）
#define SIGN_SIZE			  (32.0f)		//看板のサイズ（仮）
#define SIGN_FRAME_WIDTH	  (192.0f)		//看板の枠サイズ（横）


#define LEVER_SWITCH_SIZE	  (64.0f)	    //レバースイッチのサイズ
#define ROPE_SWITCH_SIZE	  (64.0f)	    //ロープスイッチのサイズ

#define LIFT_SIZE_WIDTH		  (128.0f)		//リフトサイズ横サイズ
#define LIFT_SIZE_HEIGHT	  (32.0f)		//リフトサイズ縦サイズ
#define STAGE5_LIFT_SIZE_WIDTH (320.0f)		//ステージ5のリフトサイズ
#define STAGE5_LIFT_SIZE_HEIGHT (16.0f)		//ステージ5のリフトサイズ

#define ROCK_SIZE_WIDTH		  (170.0f)		//岩の横サイズ（仮
#define ROCK_SIZE_HEIGHT	  (240.0f)		//岩の縦サイズ（仮
#define WOOD_SIZE			  (320.0f)		//木のサイズ(仮)
#define BOSS_SIZE_WIDTH		  (192.0f)		//BOSS横幅(仮)
#define BOSS_SIZE_HEIGHT	  (256.0f)		//BOSS縦幅(仮)
#define BOSS_DORP_KEY_SIZE	  (32.0f)	    //ボスドロップキーサイズ(仮)
#define DOOR_SIZE			  (128.0f)		//ドアのサイズ(仮)
#define THROUGHT_BLOCK_SIZE	  (64.0f)	    //スルーブロックサイズ（仮）
#define FALLING_WALLS_SAIZE   (64.0f)		//落下壁サイズ(仮)
#define CANNON_SIZE_WIDTH	  (64.0f)		//砲台の横サイズ(仮)
#define CANNON_SIZE_HEIGHT	  (32.0f)		//砲台の縦サイズ(仮)
#define ROLL_BLOCK_SIZE_WIDTH	(192.0f)	//回転するブロックの横サイズ
#define ROLL_BLOCK_SIZE_HEIGHT	(64.0f)		//回転するブロックの縦サイズ
#define NEEDLE_SIZE_WIDTH     (64.0f)		//針の横のサイズ
#define NEEDLE_SIZE_HEIGHT    (32.0f)		//針の縦のサイズ
#define NEEDLE_STAND_SIZE     (64.0f)		//針の土台のサイズ
#define TARZAN_POINT_WIDTH	  (16.0f)		//ロープでぶら下がれるギミック横サイズ
#define TARZAN_POINT_HEIGHT	  (16.0f)		//ロープでぶら下がれるギミック縦サイズ
#define ROLL_BLOCK_SWITCH_SIZE_WIDTH  (16.0f)	//回転するブロックをまわすスイッチの横サイズ
#define ROLL_BLOCK_SWITCH_SIZE_HEIGHT (16.0f)	//回転するブロックをまわすスイッチの縦サイズ
#define DIFFUSION_CANNON_SIZE	      (64.0f)   //ステージ5の拡散するキャノンのサイズ
#define STAGE5_BOSS_BODY_SIZE	     (256.0f)	//ステージ5のボス胴体サイズ
#define STAGE5_BOSS_EYE_SIZE	     (133.0f)	//ステージ5のボス眼球サイズ
#define STAGE5_BOSS_ARMS_WIDTH_SIZE       (175.0f)	//ステージ5のボス腕サイズ(横)
#define STAGE5_BOSS_ARMS_HEIGHT_SIZE      (577.0f)	//ステージ5のボス腕サイズ(縦)
#define STAGE5_BOSS_ELECTRIC_WIDTH	 (300.0f)	//ステージ5のボス胴腕接続電気サイズ(横)
#define STAGE5_BOSS_ELECTRIC_HEIGHT	 (256.0f)	//ステージ5のボス胴腕接続電気サイズ(縦)
#define WIRE_MESH_SIZE_WIDTH	(640.0f) //金網の横サイズ
#define WIRE_MESH_SIZE_HEIGHT	(64.0f) //金網の縦サイズ
#define DIFFUSION_SOURCE_SIZE	(32.0f)//拡散弾を撃つ弾のサイズ
#define STAGE5_BOSS_BULLET_SIZE (32.0f)//ステージ５のボスが打つ弾のサイズ

//スクロールのライン　（要調整）
#define SCROLL_LINE_LEFT	(464.0f)	//左
#define SCROLL_LINE_RIGHT	(560.0f)	//右
#define SCROLL_LINE_UP		(276.0f)	//上
#define SCROLL_LINE_DOWN	(400.0f)	//下

//オブジェクトの生成ライン（要調整）
#define CREATE_LINE_LEFT	(1)						//左
#define CREATE_LINE_RIGHT	( MAP_WINDOW_MAX_X )	//右
#define CREATE_LINE_UP		(1)						//上	
#define CREATE_LINE_DOWN	( MAP_WINDOW_MAX_Y )	//下
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
#include "ObjLadders.h"			//はしご
#include "ObjMap.h"				//マップ
#include "ObjWood.h"			//木	
#include "ObjWater.h"			//水
#include "ObjRopeSwitch.h"		//ロープスイッチ
#include "ObjEnemy.h"			//敵
#include "ObjBoss.h"			//ボス
#include "ObjStage3Boss.h"		//第三ステージボス
#include "ObjStage5Boss.h"		//第五ステージボス
#include "ObjStage5BossArms.h"	//第五ステージボスの腕
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
#include "ObjTime.h"			//タイム
#include "ObjNeedle.h"			//針
#include "ObjNeedleStand.h"     //針の土台
#include "ObjDiffusionCannon.h" //拡散弾発射装置
#include "ObjRollBlock.h"		//回転ブロック
#include "ObjTarzanPoint.h"		//ロープでぶら下がることができるギミック
#include "ObjRollBlockSwitch.h"	//回転ブロック用のスイッチ
#include "ObjDiffusionBullet.h" //拡散弾
#include "ObjFallingLift.h"		//乗ると落ちるリフト
#include "ObjFallingBlock.h"	//ステージ5ボス戦専用落ちるブロック
#include "ObjWireMesh.h"			//ステージ5の金網
#include "ObjDiffusionSource.h"	//ステージ５ボスの拡散弾のソース
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"		//メイン
#include "SceneTitle.h"		//タイトル
#include "SceneGameOver.h"	//ゲームオーバー
#include "SceneGameClear.h"	//クリア
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録

#define SET_GAME_START CSceneTitle //タイトル画面
//-----------------------------------------------