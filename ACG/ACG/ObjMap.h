#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト:マップ
class CObjMap :public CObj
{
public:
	CObjMap(int map[MAP_Y_MAX][MAP_X_MAX],int remaining); 	//コンストラクタ
	~CObjMap() {};	//デストラクタ
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	//スクロール関連--------------------------------------------------
	float GetScrollX() { return m_scroll_x; }		//X方向のスクロール値を返す関数
	float GetScrollY() { return m_scroll_y; }		//Y方向のスクロール値を返す関数
	void SetScrollX(float x) { m_scroll_x += x; }	//X方向のスクロール値をセットする関数
	void SetScrollY(float y) { m_scroll_y += y; }	//Y方向のスクロール値をセットする関数
	
	//マップ情報を返す
	int  GetMap(int x, int y);

	//マップのフラグを更新する
	void SetMapCreate(int x, int y, bool f) { m_map[y][x].create = f; }

	//マップをもとにしたオブジェクトの生成関連----------------------------------
	void CreateObj(int x, int y);//オブジェクトの生成を行う
	void ScrollCreateObj(int scroll_block_num_x, int scroll_block_num_y);//スクロール量をもとにオブジェクトの生成を行う
	void CreateFallingBloack();//落ちるブロックだけを生成する（ボス戦用）

	//ーーーーーーーーーーーーアクセサーーーーーーーーーーーーーーーーー

	//m_map[y][x]　のところにidを入れる
	void SetMap(int x, int y, int id) { m_map[y][x].num = id; }	
	//------------------------------------------------------------------
	
private:
	float m_scroll_x;	//X軸のスクロール値
	float m_scroll_y;	//Y軸のスクロール値

	//マップの構造体
	struct Map
	{
		int num;		//マップの数値
		bool create;	//生成するかのフラグ
	};

	Map m_map[MAP_Y_MAX][MAP_X_MAX];	//マップ用配列	←マップができたらこの配列に入れる
	int m_remaining;					// プレイヤーの残機数
};