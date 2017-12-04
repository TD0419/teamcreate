#pragma once
//使用するヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ハシゴ
class CObjLadders :public CObj
{
public:
	CObjLadders(int x,int y,bool look);	//コンストラクタ
	~CObjLadders() {};					//デストラクタ
	void Init();						//イニシャライズ
	void Action();						//アクション
	void Draw();						//ドロー
	void HeroHit(float px, float py);//プレイヤーがあたったときの処理
	bool GetHeroJumpCon() { return m_hero_jump_con; } //主人公が無駄にジャンプするのを制御する変数を返す
private:
	float m_px;					//ハシゴX座標
	float m_py;					//ハシゴY座標
	int m_map_x;				//マップ要素数X
	int m_map_y;				//マップ要素数Y
	float m_up_and_down_speed;  //ハシゴの上り下り時の速度
	bool  m_obj_look_f;			//ハシゴが見えるかどうか false:見えない true:見える
	bool  m_side_block_flag;	//サイドにブロックがあるかを確認する
	bool  m_side_through_block_flag;	//サイドにスルーブロックがあるかを確認する
	bool  m_hero_jump_con;      //主人公が無駄にジャンプするのを制御
};
