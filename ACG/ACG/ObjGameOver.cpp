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
	m_mode = 0;				//モード選択変数の初期化
	m_keypush_flag = true;	//キーフラグの初期化
	m_enter_key_flag = true;
	m_text_color = false;	//false…白色の文字  ture…黄色の文字

	//文字のグラフィック作成
	Font::SetStrTex(L"GAME OVER");
	Font::SetStrTex(L"Title");
	Font::SetStrTex(L"Continue");
	Font::SetStrTex(L"→");
	Audio::Start(GAMEOVER);	//BGMをならす

	((UserData*)Save::GetData())->stagenum = 1;//ステージを１から始めるようにする
}

//アクション
void CObjGameOver::Action()
{

	//Wキー　又は　↑キーが押された時
	if (Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true)
	{
		//1以上　且つ　キーフラグがtrue　なら
		if (m_mode >= 1 && m_keypush_flag == true)
		{
			m_mode--;	//モード番号を1減らす
			m_keypush_flag = false;	//キーフラグをオフにする
			m_text_color = false;//文字を白色にする
		}
	}
	//Sキー　又は　↓キーが押された時
	else if (Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true)
	{
		//1以下　且つ　キーフラグがtrue　なら
		if (m_mode <= 0 && m_keypush_flag == true)
		{
			m_mode++;	//モード番号を1増やす
			m_keypush_flag = false;	//キーフラグをオフにする
			m_text_color = true;//文字を黄色にする
		}
	}
	//W、S、↑、↓が押されてないとき
	else
		m_keypush_flag = true;//キーフラグをオンにする

	if (Input::GetVKey(VK_RETURN) == false)
	{
		m_enter_key_flag = false;
	}

	if (m_enter_key_flag == false) //長押ししても各種シーンにすぐ移動できないようにする処理。
	{
		//エンターキーが押された時
		if (Input::GetVKey(VK_RETURN) == true)
		{
			switch (m_mode)
			{
				case 0:
				{
					//シーンメインに移動
					Scene::SetScene(new CSceneMain());
					break;
				}
				case 1:
				{
					//シーンタイトルに移動
					Scene::SetScene(new CSceneTitle());
					break;
				}

			}
		}
	}

}

//ドロー
void CObjGameOver::Draw()
{
	float color_white[4] = { 1.0f,1.0f,1.0f,1.0f }; //白色、基本色
	float color_yellow[4] = { 1.0f,1.0f,0.0f,1.0f };//黄色

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
	Draw::Draw(GRA_GAME_OVER, &src, &dst, color_white, 0.0f);
	//文字描画
	Font::StrDraw(L"GAME OVER", 270.0f, 46.0f, 105.0f, color_white);
	
	//→がContinueを指している場合は、Continueの文字を黄色にする。Titleの文字は白色。
	if (m_text_color==false)
	{
		Font::StrDraw(L"Continue", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H - 200.0f + 38.0f, TEXT_SIZE, color_yellow);
		Font::StrDraw(L"Title", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H - 200.0f + 108.0f, TEXT_SIZE, color_white);
	}
	//→がTitleを指している場合は、Titleの文字を黄色にする。Continueの文字は白色。
	else if (m_text_color == true)
	{
		Font::StrDraw(L"Continue", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H - 200.0f + 38.0f, TEXT_SIZE, color_white);
		Font::StrDraw(L"Title", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H - 200.0f + 108.0f, TEXT_SIZE, color_yellow);

	}
	//→を表示
	//					 x位置				     y位置(→の位置)   →の移動間隔	   文字サイズ
	Font::StrDraw(L"→", WINDOW_SIZE_W - 350.0f, 1210.0f / 2.0f  + 70.0f * m_mode, TEXT_SIZE, color_yellow);

}