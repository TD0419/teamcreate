#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjTime.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTime::Init()
{
	//時間(フレーム数)を０に設定
	m_time = 0;

	m_px = 900;
	m_py = 20;
}

//アクション
void CObjTime::Action()
{
	//時間(フレーム数)
	m_time++;

}

//ドロー
void CObjTime::Draw()
{
	//色情報　RGB
	float color[4] = {1.0f,1.0f,1.0f,1.0f};
	//時間を表示させる文字列
	wchar_t str[256];

	//秒が10未満なら０を前に付ける
	if(m_time / 60 % 60 < 10)
		swprintf_s(str, L"%d:0%d", m_time / 60 / 60,m_time / 60 % 60);
	//そのまま
	else
		swprintf_s(str, L"%d:%d", m_time / 60 / 60, m_time / 60 % 60);
	//時間を表示
	Font::StrDraw(str, m_px, m_py, 50, color);
}