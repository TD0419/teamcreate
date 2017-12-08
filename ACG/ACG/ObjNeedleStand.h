#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：トゲ
class CObjNeedleStand :public CObj
{
public:
	CObjNeedleStand(int x, int y);	// コンストラクタ
	~CObjNeedleStand() {};			// デストラクタ
	void Init();				// イニシャライズ
	void Action();				// アクション
	void Draw();				// ドロー
	void HeroHit();	//主人公との当たり判定
private:
	//mapの要素数
	int m_map_x;
	int m_map_y;
	float m_px;		//位置X
	float m_py;		//位置Y
};
