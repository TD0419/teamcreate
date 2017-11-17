#pragma once

//使用するヘッダー
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

#define CHAR_SIZE (32.0f)	//文字のサイズ

//オブジェクト：タイトル
class CObjTitle :public CObj
{
public:
	CObjTitle() {}; 	//コンストラクタ
	~CObjTitle() {};	//デストラクタ
	void Init();		//イニシャライズ
	void Action();		//アクション
	void Draw();		//ドロー
private:
	int m_mode;				//モードの選択用変数(0～2)
	bool m_keypush_flag;	//キーのトリガー処理用フラグ
	int m_time;             //ゲームオーバーからくるとすぐに飛んでしまうんでそれを制御する変数
};
