#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ドア
class CObjDoor :public CObj
{
public:
	CObjDoor(int x, int y); // コンストラクタ
	~CObjDoor() {};			// デストラクタ
	void Init();			// イニシャライズ
	void Action();			// アクション
	void Draw();			// ドロー

private:
	float m_px;	// ドアX座標
	float m_py; // ドアY座標
	bool m_unlock_flag;		//ボス死亡フラグ
	bool m_boss_save;		//ボスの情報保存
	//アニメーション関連
	int m_ani_door_time; //アニメーションフレーム動作感覚
	int m_ani_door_frame;//描画フレーム
	float m_ani_door_time_max;//アニメーション動作間隔最大値
	
	//ステージによってのドアの種類変更
	//1=エネミー撃破で開錠　2,5＝ボス撃破で開錠
	int m_door_type;
	
	bool m_goal_flag; // ゴールフラグ(ゴールの初期化を一回だけにする用) true:ゴールした false:ゴールしていない
};
