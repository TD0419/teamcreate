#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public:
	CObjBlock(int x, int y);
	~CObjBlock() {};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	////マップ変更用関数
	//void MapChange(int map[MAP_Y_MAX][MAP_X_MAX]);

	////ブロックとの当たり判定
	//void BlockHit(
	//	float *x, float *y, bool scroll_on,
	//	bool*up, bool* down, bool* left, bool* right,
	//	float* vx, float*vy, int* bt
	//);

private:
	
	int m_map[MAP_Y_MAX][MAP_X_MAX]; //マップ情報

	float m_scroll; //左右スクリーン用
	float m_px;     //ブロック位置X
	float m_py;     //ブロック位置Y
};
