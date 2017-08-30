#pragma once

//使用するヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ボス
class CObjBoss :public CObj
{
public:
    CObjBoss(int x,int y);        //コンストラクタ
    ~CObjBoss() {};	//デストラクタ
    void Init();	        //イニシャライズ
    void Action();	        //アクション
    void Draw();	        //ドロー
private:
    float m_px;	 // ボスX座標
    float m_py;	 // ボスY座標
    float m_vx; // ボスX軸方向のベクトル
    float m_vy; // ボスY軸方向のベクトル

    int m_hp;   // ボスのＨＰ

};
