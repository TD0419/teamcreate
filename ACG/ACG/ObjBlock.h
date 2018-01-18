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

	void Init() {};			//イニシャライズ
	void Action();			//アクション
	void Draw();			//ドロー
	
	//通常ブロックとの当たり判定
	void BlockHit(
		float* x, float* y, float width, float height,
		bool*up, bool* down, bool* left, bool* right,
		float* vx, float*vy
	);

	// 全てのブロックとの当たり判定
	void AllBlockHit(
		float* x, float* y, float width, float height,
		bool*up, bool* down, bool* left, bool* right,
		float* vx, float*vy
	);
		
private:
	//マップ上の位置（要素数）
	int m_map_x;	
	int m_map_y;
	//ブロックの位置
	float m_px;		
	float m_py;		
};
