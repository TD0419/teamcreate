#pragma once
//使用するヘッダー
#include "GameL\SceneManager.h"

//落ちるブロックの当たり判定がなくなる位置
#define PERDECISION_CLEAR_POINT (1700.0f) 

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

	bool GetScreenOut() { return m_screen_out; }//画面外にブロックが出た情報を入れる
private:

	float m_px;			//落ちるブロックX座標
	float m_py;			//落ちるブロックY座標
	int   m_falling_time;//ブロックが落ちるまでの時間
	bool m_fallint_start_flag;//ブロックを落下させるかどうかのフラグ

	float m_return_block_y;	//ブロックを元の位置に戻すための変数
	bool m_screen_out;		//ブロックが画面外に出ているかを調べる
};
