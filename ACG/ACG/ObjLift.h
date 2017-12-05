#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//リフトのスピードマクロ
//テスト用
#define SPEED (1.5f)


//オブジェクト：リフト
class CObjLift :public CObj
{
public:
	CObjLift(int px, int py, int direction, float width_max, int mode);
	~CObjLift() {};			// デストラクタ
	void Init();			// イニシャライズ
	void Action();			// アクション
	void Draw();			// ドロー
	void HeroRide();		//　主人公が乗っているときの処理
	//アクセサ-----------------------------------------
	float GetVecX() { return m_vx; }	//移動ベクトルXを返す
	float GetVecY() { return m_vy; }	//移動ベクトルYを返す

private:
	float m_px;		// リフトX座標
	float m_py;		// リフトY座標
	float m_vx;		// リフトの移動ベクトルX
	float m_vy;		// リフトの移動ベクトルY
	float m_width_max;	//左右の最大移動量
	float m_length_max;	//上下の最大移動量
	
	//現在の移動方向
	//０＝右：１＝左：２＝上：３＝下
	int m_direction;

	//初期の移動方向
	//０＝右：１＝左：２＝上：３＝下
	//リフトの動きモードが０のときこの変数は初期の移動方向を指す(引っ張られていない時の移動方向)
	int m_initial_direction;

	float m_move_x;//初期位置から動いた距離X
	float m_move_y;//初期位置から動いた距離Y

	//リフトの動きモード
	//０＝手動モード(縄を紐スイッチに当てて移動するモード)
	//１＝自由移動モード(初期位置Xから最大X位置の間を自動移動)
	//２＝無限移動モード(上または下に行き画面外に行くと上なら下から、下なら上から出てくる)
	int m_move_mode;	

	//音を制御するための変数 移動する時にカウントを増やし、一秒ごとに音を鳴らす
	int m_lift_audio_count;

	//各移動モード(m_move_mode)による移動関数
	void ModeMove();
};
