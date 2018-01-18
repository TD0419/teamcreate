#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneMain:public CScene
{
public:
	CSceneMain() ;		//コンストラクタ
	CSceneMain::CSceneMain(int n);//コンストラクタ(リスタート用)
	~CSceneMain() {};	//デストラクタ
	void InitScene();	//ゲームメイン初期化メソッド
	void Scene() {};		//ゲームメインの実行中メソッド
private:
	int m_map[MAP_Y_MAX][MAP_X_MAX];//マップ格納用変数
	void MapDataLoading(int map[MAP_Y_MAX][MAP_X_MAX]);//マップデータ読み込み関数　引数は仮
	void ImageDataLoading();	//画像データ読み込み関数
	void AudioDataLoading();	//音楽データ読み込み関数
};

