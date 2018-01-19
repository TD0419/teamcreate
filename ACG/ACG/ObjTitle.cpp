#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_mode = 0;				//モード選択変数の初期化
	m_keypush_flag = true;	//キーフラグの初期化
	m_enter_key_flag = true;
	
	//文字のグラフィック作成
	Font::SetStrTex(L"Start");	//スタート
	Font::SetStrTex(L"Exit");	//終了

	//ステージ1からスタートさせる
	((UserData*)Save::GetData())->stagenum = 1;

	Audio::Start(TITLE);
}

//アクション
void CObjTitle::Action()
{
	
	//Wキー　又は　↑キーが押された時
	if (Input::GetVKey('W') == true || Input::GetVKey(VK_UP) == true)
	{
		//1以上　且つ　キーフラグがtrue　なら
		if (m_mode >= 1 && m_keypush_flag == true)
		{
			m_mode-=1;	//モード番号を1減らす
			m_keypush_flag = false;	//キーフラグをオフにする	
		}
	}
	//Sキー　又は　↓キーが押された時
	else if (Input::GetVKey('S') == true || Input::GetVKey(VK_DOWN) == true)
	{
		//1以下　且つ　キーフラグがtrue　なら
		if (m_mode <= 0 && m_keypush_flag == true)
		{
			m_mode+=1;	//モード番号を1増やす
			m_keypush_flag = false;	//キーフラグをオフにする
			
		}
	}
	//W、S、↑、↓が押されてないとき
	else
		m_keypush_flag = true;//キーフラグをオンにする

	if (Input::GetVKey(VK_RETURN) == false) //　Enterキーが押されてなかったらメインに移行できるようにする
	{
		m_enter_key_flag = false;
	}

	if (m_enter_key_flag == false) // ゲームオーバーからすぐにメインに飛んでしまうので長押ししてもメインに飛ばされないようにした。
	{
		//エンターキーが押された時
		if (Input::GetVKey(VK_RETURN) == true)
		{
			switch (m_mode)
			{
				case 0:
				{
					//シーンメインに移動
					Scene::SetScene(new CSceneMain);
					break;
				}
				case 1:
				{
					//ゲーム終了
					exit(0);
					break;
				}
			}
		}
	}
}

//ドロー
void CObjTitle::Draw()
{
	
	float color_white[4] = { 1.0f,1.0f,1.0f,1.0f }; //白色、基本色
	float color_yellow[4] = { 1.0f,1.0f,0.0f,1.0f };//黄色
	RECT_F src, dst;

	//切り取り位置
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = src.m_left + 1024.0f;
	src.m_bottom = src.m_top  +  767.0f;

	//描画位置
	dst.m_top    = 0.0f;
	dst.m_left   = 0.0f;
	dst.m_right  = dst.m_left + 1024.0f;
	dst.m_bottom = dst.m_top + 767.0f;

	//描画
	Draw::Draw(GRA_TITLE, &src, &dst, color_white, 0.0f);

	//メニュー描画
	//→がStartを指している場合は、Startの文字を黄色にする。Exitの文字は白色。
	if( m_mode == 0 )
	{
		Font::StrDraw(L"Start"	, WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H/2.0f + 40.0f    , FONT_SIZE_TITLE, color_yellow);
		Font::StrDraw(L"Exit"	, WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H/2.0f + 118.0f	, FONT_SIZE_TITLE - 10.0f, color_white);

	}
	
	//→がExitを指している場合は、Exitの文字を黄色にする。Startの文字は白色。
	else if ( m_mode == 1 )
	{
		Font::StrDraw(L"Start", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H / 2.0f + 40.0f, FONT_SIZE_TITLE -10.0f, color_white);
		Font::StrDraw(L"Exit", WINDOW_SIZE_W - 250.0f, WINDOW_SIZE_H / 2.0f + 118.0f, FONT_SIZE_TITLE, color_yellow);
	}
}