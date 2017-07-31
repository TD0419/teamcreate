#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//使用するネームスペース
using namespace GameL;

//オブジェト：弾丸
class CObjAngleBullet : public CObj
{
public :
	CObjAngleBullet(float x,float y,float r,float speed);	//コンストラクタ
	~CObjAngleBullet(){};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_x;	//オブジェクトのｘ方向
	float m_y;	//オブジェクトのｙ方向
	float m_vx;	//オブジェクトの移動ベクトルX
	float m_vy; //オブジェクトの移動ベクトルY
	float m_r;	//移動する角度
	float m_speed;//速度

	int	m_ani;		//着弾アニメーション用
	int m_ani_time;//着弾アニメーション間隔タイム
	bool m_del;		//消去チェック
	RECT_F m_eff;	//着弾エフェクト描画用

};
