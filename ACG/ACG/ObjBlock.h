#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public:
	CObjBlock(float x,float y);
	~CObjBlock() {};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_px;		//位置X
	float m_py;		//位置Y
};
