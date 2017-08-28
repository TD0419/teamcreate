#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[MAP_X][MAP_Y]);
	~CObjBlock() {};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	//マップ変更用関数
	void MapChange(int map[MAP_Y][MAP_X]);

	//ブロックとの当たり判定
	void BlockHit(
		float *x, float *y, bool scroll_on,
		bool*up, bool* down, bool* left, bool* right,
		float* vx, float*vy, int* bt
	);

private:
	
	int m_map[MAP_Y][MAP_X]; //マップ情報

	float m_scroll;		//左右スクリーン用
	
};
