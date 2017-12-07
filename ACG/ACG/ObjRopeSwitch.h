#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ロープスイッチ
class CObjRopeSwitch :public CObj
{
public:
    CObjRopeSwitch(int x, int y);       //コンストラクタ
    ~CObjRopeSwitch() {};
	//デストラクタ
    void Init();	         //イニシャライズ
    void Action();	         //アクション
    void Draw();	         //ドロー

	//アクセサ-----------------------------------------
	bool GetRopeFlag() { return m_rope_flag; }//ロープが当たったときの状態を返す

private:
    float m_px;	 // ロープスイッチX座標
    float m_py;	 // ロープスイッチY座標
	//マップの要素数
	int m_map_x;
	int m_map_y;

	bool m_rope_flag; //ロープがあったとき記憶する用
};