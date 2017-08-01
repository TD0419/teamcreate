#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：ゲームメイン
class CSceneMain:public CScene
{
public:
	CSceneMain();
	~CSceneMain();
	void InitScene();//ゲームメイン初期化メソッド
	void Scene();   //ゲームメインの実行中メソッド
	void MapDataLoading(int map[10][10]);//マップデータ読み込み関数　引数は仮
	void InageDataLoading();//画像データ読み込み関数
	void AudioDataLoading();//音楽データ読み込み関数
private:
};