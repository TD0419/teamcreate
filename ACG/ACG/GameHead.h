#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_BUTTON,
	OBJ_HERO,
	OBJ_ROCK,
    OBJ_BOSS_ENEMY,
	OBJ_TITLE,
	OBJ_BLOCK,
	OBJ_LIFT,
	OBJ_GAME_OVER,
	OBJ_MAP,
    OBJ_WOOD,
    OBJ_ROPE_SWITCH,
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
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
#define WINDOW_SIZE_W	(1024)
#define WINDOW_SIZE_H	(768)
//解像度サイズ
#define PIXEL_SIZE_W	(1024)
#define PIXEL_SIZE_H	(768)

//マップサイズ
#define MAP_X 10
#define MAP_Y 10

//オブジェクトのサイズ
#define HERO_SIZE 64.0f

//スクロールのライン
#define SCROLL_LINE_LEFT	(480.0f)
#define SCROLL_LINE_RIGHT	(WINDOW_SIZE_W - SCROLL_LINE_LEFT)
#define SCROLL_LINE_UP		(250.0f)
#define SCROLL_LINE_DOWN	(WINDOW_SIZE_H - SCROLL_LINE_UP)

//------------------------------------------------
//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ-----------------
#include "ObjButton.h"
#include "ObjHero.h"
#include "ObjRock.h"
#include "ObjBossEnemy.h"
#include "ObjTitle.h"
#include "ObjBlock.h"
#include "ObjLift.h"
#include "ObjLadders.h"
#include "ObjMap.h"
#include "ObjWood.h"
#include "ObjRopeSwitch.h"
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"
//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneMain
//-----------------------------------------------