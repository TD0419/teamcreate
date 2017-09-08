#pragma once
//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//マクロ
#define TIME (1.0)

//オブジェクト：敵生成システム(エンドレス沸き)
class CObjEndlessSpring :public CObj
{
public:
	CObjEndlessSpring();        //コンストラクタ
	~CObjEndlessSpring() {};	//デストラクタ
	void Init();				//イニシャライズ
	void Action();				//アクション
	void Draw();				//ドロー
private:
	float m_x;			 // 敵生成システムX座標
	float m_y;			 // 敵生成システムY座標

	float m_timelag;	 //敵生成までの間隔処理
	

};