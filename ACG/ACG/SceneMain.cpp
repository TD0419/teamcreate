//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"


//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"

//コントラスト
CSceneMain::CSceneMain()
{

}
//デストラスト
CSceneMain::~CSceneMain()
{

}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//マップ情報格納用変数テスト用
	int map[10][10] = { 0 };
	MapDataLoading(map);



}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}
//マップデータ読み込み関数
void CSceneMain::MapDataLoading(int map[10][10])
{
	//外部データの読み込み（ステージ情報）
	unique_ptr<wchar_t> p;//ステージ情報ポインター
	int size;				//ステージ情報の大きさ

	p = Save::ExternalDataOpen(L"testomap.csv", &size);//外部データ読み込み

	if (p == nullptr)
	{
		MessageBox(0, L"マップデータが見つかりませんでした。", L"エラーコッチャ", MB_OK);
		return;
	}

	int count = 1;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			
			map[i][j] = w;

			while (w/10 != 0)
			{
				count++;
				w /= 10;
			}
			
			count += 2;
		}
	}
}

//画像データ読み込み関数
void CSceneMain::InageDataLoading()
{
	//画像登録ID
	int id = 0;
	//グラフィック読み込み
	//Draw::LoadImageW(L"", id++, TEX_SIZE_???);
}

//音楽データ読み込み関数
void CSceneMain::AudioDataLoading()
{
	//音楽登録ID
	int id = 0;

	//Audio::LoadAudio(id++, L"", ? ? ? ? );
	
}