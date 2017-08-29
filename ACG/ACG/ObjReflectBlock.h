#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjReflectBlock : public CObj
{
public:
	CObjReflectBlock(int x, int y);
	~CObjReflectBlock() {};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー


private:

	float m_px;     //ブロック位置X
	float m_py;     //ブロック位置Y
};
