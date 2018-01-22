#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//ステージクリアの（文字をだす）クラス
class CObjStageClear : public CObj
{
public:
	CObjStageClear(int x,int y);
	~CObjStageClear() {};
	void Init();
	void Action();
	void Draw();
private:
	//描画の位置
	float m_px;
	float m_py;
	float m_scroll_x;
	float m_scroll_y;
};
