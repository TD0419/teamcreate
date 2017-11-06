#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ドアという名の
class CObjDoor :public CObj
{
public:
	CObjDoor(int x, int y); // コンストラクタ
	~CObjDoor() {};			// デストラクタ
	void Init();			// イニシャライズ
	void Action();			// アクション
	void Draw();			// ドロー

	bool m_unlock_flag;		//ボス死亡フラグ
private:
	float m_px;	// ドアX座標
	float m_py; // ドアY座標

	//アニメーション関連
	int m_ani_door_time; //アニメーションフレーム動作感覚
	int m_ani_door_frame;//描画フレーム
	float m_ani_door_time_max;//アニメーション動作間隔最大値
	
};
