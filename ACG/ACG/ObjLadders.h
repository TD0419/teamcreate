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
	CObjLadders(int x,int y);
	~CObjLadders() {};	//デストラクタ
	void Init();	    //イニシャライズ
	void Action();	    //アクション
	void Draw();	    //ドロー

private:
	float m_px; //ハシゴX座標
	float m_py; //ハシゴY座標
};
