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
	
	//文字のグラフィック作成
	Font::SetStrTex(L"GAME OVER");
	Audio::Start(GAMEOVER);
}

//アクション
void CObjGameOver::Action()
{
	//エンターキーが押された時
	if (Input::GetVKey(VK_RETURN) == true)
	{
		//シーンタイトルに移動
		Scene::SetScene(new CSceneTitle());
		return;
	}
}

//ドロー
void CObjGameOver::Draw()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置
	

	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	////表示位置設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 1024.0f;
	dst.m_bottom =1024.0f;

	//描画
	Draw::Draw(GRA_GAME_OVER, &src, &dst, color, 0.0f);
	//メニュー描画
	Font::StrDraw(L"GAME OVER", 270.0f, 46.0f, 105.0f, color);
	Font::StrDraw(L"TITLE:PUSH ENTERKEY", 580.0f, 710.0f, 45.0f, color);
}