#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：クリア
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};		//コンストラクタ
	~CObjGameClear() {};	//デクスラクタ
	void Init();			//イニシャライズ
	void Action();			//アクション
	void Draw();			//ドロー

private:
	int m_time;				//時間管理
	int m_bouns;			//クリアボーナス
	bool m_key_flag;		//キー制御フラグ
	int m_audio_se;			//SEの音楽の管理
};