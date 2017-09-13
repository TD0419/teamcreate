
#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：砲台
class CObjCannon :public CObj
{
public:
	CObjCannon(float x,float y); 	//コンストラクタ
	~CObjCannon() {};			//デストラクタ
	void Init();				//イニシャライズ
	void Action();				//アクション
	void Draw();				//ドロー
private:
	float m_x;	//X座標
	float m_y;	//Y座標
	float m_r;  //砲台の回転角度
	float m_rec;	//弾丸リキャスト
};