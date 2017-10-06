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

	void Init();			//イニシャライズ
	void Action();			//アクション
	void Draw();			//ドロー
	void HeroHit();			//主人公との当たり判定を処理する
	void BossHit();			//ボスとの当たり判定を見る

	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	//オブジェクト
	void BlockHit(
		float* x, float* y, float width, float height,
		bool*up, bool* down, bool* left, bool* right,
		float* vx, float*vy
	);

	bool jump;//ジャンプ用
	//マップ上の位置（要素数）
	int m_map_x;//X
	int m_map_y;//Y
private:
	
	int m_map[10][10];	//マップ情報（仮）

	float m_scroll;		//左右スクリーン用
	float m_px;			//ブロック位置X
	float m_py;			//ブロック位置Y

	
};
