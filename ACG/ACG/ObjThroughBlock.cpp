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
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//アクション
void CObjThroughBlock::Action()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//画面内か調べる
	bool wincheck_flag = WindowCheck(m_px, m_py, BLOCK_SIZE, BLOCK_SIZE);

	//画面外なら
	if (wincheck_flag == false)
	{
		//削除するので次に来たときに生成するようにフラグをオンにする
		objmap->SetMapCreate(m_map_x, m_map_y, true);
		this->SetStatus(false);		//自身を削除
	}
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
	Draw::Draw(GRA_THROUGH_BLOCK, &src, &dst, color, 0.0f);
}