#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ハシゴ
class CObjLadders :public CObj
{
public:
	CObjLadders(int x,int y);	//コンストラクタ
	~CObjLadders() {};			//デストラクタ
	void Init();				//イニシャライズ
	void Action();				//アクション
	void Draw();				//ドロー
	void HeroHit(float px, float py);//プレイヤーがあたったときの処理

private:
	float m_px;					//ハシゴX座標
	float m_py;					//ハシゴY座標
								//マップ上の位置（要素数）
};
