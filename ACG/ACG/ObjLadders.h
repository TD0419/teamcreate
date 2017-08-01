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
	float m_x;		//X座標
	float m_y;      //Y座標
};
