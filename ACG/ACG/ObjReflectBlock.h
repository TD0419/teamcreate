#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：反射ブロック
class CObjReflectBlock : public CObj
{
public:
	CObjReflectBlock(int x, int y);
	~CObjReflectBlock() {};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー


private:

	float m_x;     //ブロック位置X
	float m_y;     //ブロック位置Y
};
