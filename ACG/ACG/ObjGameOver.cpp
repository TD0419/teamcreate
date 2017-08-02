#pragma once
//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGameOver.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameOver::Init()
{
	m_key_flag = false;
	m_audio_se = 0;//SEの音楽の管理
	m_time = 0;

	////値交換用
	//int w;

	////スコアをランキングの最後に入れる
	//((UserData*)Save::GetData())->m_ranking[RANKING_MAX_COUNT - 1] = ((UserData*)Save::GetData())->m_point;

	////ランキング変動確認
	////バブルソート
	//for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
	//{
	//	for (int j = i + 1; j < RANKING_MAX_COUNT; j++)
	//	{
	//		if (((UserData*)Save::GetData())->m_ranking[i] < ((UserData*)Save::GetData())->m_ranking[j])
	//		{
	//			//値の変更
	//			w = ((UserData*)Save::GetData())->m_ranking[i];
	//			((UserData*)Save::GetData())->m_ranking[i] = ((UserData*)Save::GetData())->m_ranking[j];
	//			((UserData*)Save::GetData())->m_ranking[j] = w;
	//		}
	//	}
	//}

	////ステージ1で初期化する
	//((UserData*)Save::GetData())->m_stage_count = 1;

	//セーブ
	Save::Seve();
}

//アクション
void CObjGameOver::Action()
{
	m_time++;

	//if (m_time > 400)
	//{
	//	//Aを押したら、メニュー画面へ
	//	if (Input::GetVKey('Q') == true)
	//	{
	//		if (m_key_flag == true)
	//		{
	//			//ランキングに反映したスコアを初期化する
	//			((UserData*)Save::GetData())->m_point = 0;
	//		}
	//	}
	//	else
	//	{
	//		m_key_flag = true;
	//		Scene::SetScene(new CSceneMenu());//メニュー画面へ
	//		
	//	}
	//}
}

//ドロー
void CObjGameOver::Draw()
{
	//float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//RECT_F src;	//描画先切り取り位置
	//RECT_F dst;	//描画先表示位置

	//			//背景--------------------------------
	//			//切り取り位置設定
	//src.m_top = 0.0f;
	//src.m_left = 0.0f;
	//src.m_right = 512.0f;
	//src.m_bottom = 512.0f;

	////表示位置設定
	//dst.m_top = 0.0f;
	//dst.m_left = 0.0f;
	//dst.m_right = 800.0f;
	//dst.m_bottom = 600.0f;

	////描画
	//Draw::Draw(7, &src, &dst, c, 0.0f);
}