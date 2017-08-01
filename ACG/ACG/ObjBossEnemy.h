#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ボス
class CObjBossEnemy :public CObj
{
public:
    CObjBossEnemy();        //コンストラクタ
    ~CObjBossEnemy() {};	//デストラクタ
    void Init();	        //イニシャライズ
    void Action();	        //アクション
    void Draw();	        //ドロー
private:
    float m_x;	//X座標
    float m_y;	//Y座標
    float m_vx;	//X軸方向のベクトル
    float m_vy;	//Y軸方向のベクトル

    int m_hp;   //ボスのＨＰ

};
