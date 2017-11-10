#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_mode = 0;				//モード選択変数の初期化
	m_keypush_flag = true;	//キーフラグの初期化

	//文字のグラフィック作成
	Font::SetStrTex(L"Start");	//スタート
	Font::SetStrTex(L"Option");	//オプション
	Font::SetStrTex(L"Exit");	//終了

	//デバッグ用
	Font::SetStrTex(L"→");	//→
}

//アクション
void CObjTitle::Action()
{

	//↑キーが押された時
	if (Input::GetVKey(VK_UP) == true)
	{
		//1以上　且つ　キーフラグがtrue　なら
		if (m_mode >= 1 && m_keypush_flag == true)
		{
			m_mode--;	//モード番号を1減らす
			m_keypush_flag = false;	//キーフラグをオフにする
		}
	}
	//↓キーが押された時
	else if (Input::GetVKey(VK_DOWN) == true)
	{
		//1以下　且つ　キーフラグがtrue　なら
		if (m_mode <= 1 && m_keypush_flag == true)
		{
			m_mode++;	//モード番号を1増やす
			m_keypush_flag = false;	//キーフラグをオフにする
		}
	}
	//↑と↓が押されてないとき
	else
		m_keypush_flag = true;//キーフラグをオンにする
		
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
				//オプション
				break;
			}
			case 2:
			{
				//ゲーム終了
				break;
			}
		}
	}

}

//ドロー
void CObjTitle::Draw()
{
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };	//描画の色

	//メニュー描画
	Font::StrDraw(L"Start"	, WINDOW_SIZE_W - 300.0f, WINDOW_SIZE_H/2.0f			, CHAR_SIZE, color);
	Font::StrDraw(L"Option"	, WINDOW_SIZE_W - 300.0f, WINDOW_SIZE_H/2.0f +  80.0f	, CHAR_SIZE, color);
	Font::StrDraw(L"Exit"	, WINDOW_SIZE_W - 300.0f, WINDOW_SIZE_H/2.0f + 160.0f	, CHAR_SIZE, color);


	//デバッグ用に→を表示
	Font::StrDraw(L"→"		, WINDOW_SIZE_W - 350.0f, WINDOW_SIZE_H / 2.0f + 80.0f * m_mode , CHAR_SIZE, color);
}