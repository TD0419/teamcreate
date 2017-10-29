//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjThroughBlock.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjThroughBlock::CObjThroughBlock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjThroughBlock::Init()
{
}

//アクション
void CObjThroughBlock::Action()
{
}

//ドロー
void CObjThroughBlock::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);


	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//描画
	Draw::Draw(2, &src, &dst, color, 0.0f);
}