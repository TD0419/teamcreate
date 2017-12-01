#pragma once
//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ステージ5ボス戦専用落ちるブロック
class CObjFallingBlock :public CObj
{
public:
	CObjFallingBlock(int x, int y); 	//コンストラクタ
	~CObjFallingBlock() {};				//デストラクタ
	void Init();						//イニシャライズ
	void Action();						//アクション
	void Draw();						//ドロー
	void HeroHit();						//主人公との当たり判定を処理する

	//マップ上の位置（要素数）
	int m_map_x;//X
	int m_map_y;//Y
private:
	
	float m_px;			//落ちるブロックX座標
	float m_py;			//落ちるブロックY座標
	int   m_falling_time;//ブロックが落ちるまでの時間
};
