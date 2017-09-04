#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ブロック＆背景
class CObjDownDrawBlock : public CObj
{
public:
	CObjDownDrawBlock(int x, int y);
	~CObjDownDrawBlock() {};

	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }
	
private:

	float m_scroll; //左右スクリーン用
	float m_px;     //ブロック位置X
	float m_py;     //ブロック位置Y


};