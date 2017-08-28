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
    float m_boss_x;	 // ボスX座標
    float m_boss_y;	 // ボスY座標
    float m_boss_vx; // ボスX軸方向のベクトル
    float m_boss_vy; // ボスY軸方向のベクトル

    int m_boss_hp;   // ボスのＨＰ

};
