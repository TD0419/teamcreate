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
	CObjLadders(float x, float y);
	~CObjLadders() {};	//デストラクタ
	void Init();	    //イニシャライズ
	void Action();	    //アクション
	void Draw();	    //ドロー

private:
	float m_ladders_x; //ハシゴX座標
	float m_ladders_y; //ハシゴY座標
};
