#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン：タイトル
class CSceneTitle :public CScene
{
public:
	CSceneTitle() {};
	~CSceneTitle() {};
	void InitScene();		//初期化メソッド
	void Scene();			//実行中メソッド
	void ImageDataLoading();//画像データ読み込み関数
	void AudioDataLoading();//音楽データ読み込み関数
private:
};