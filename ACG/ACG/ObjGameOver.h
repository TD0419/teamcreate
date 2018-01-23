#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define FONT_SIZE_GO (46.0f)	//文字のサイズ(ゲームオーバー用)

//オブジェクト：ゲームオーバー
class CObjGameOver : public CObj
{
public:
	CObjGameOver() {};
	~CObjGameOver() {};
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	int m_mode;				//モードの選択用変数(0～2)
	bool m_keypush_flag;	//キーのトリガー処理用フラグ
	bool m_enter_key_flag;  //すぐに飛んでしまうんでそれを制御する変数
};