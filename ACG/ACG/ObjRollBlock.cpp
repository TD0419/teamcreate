//使用するヘッダー
#include "GameHead.h"
#include "ObjRollBlock.h"
#include "Function.h"

#include "GameL\HitBoxManager.h"

////コンストラクタ
////引数1,2	mapの要素番号
//CObjRollBlock::CObjRollBlock(int x,int y,int)
//{
//	m_px = (float)x * BLOCK_SIZE;
//	m_py = (float)y * BLOCK_SIZE;
//}
//
////イニシャライズ
//void CObjRollBlock::Init()
//{
//	m_r = 0.0f;	//角度初期化
//	m_count = 0;//カウンターの初期化
//
//	m_roll_flag = false;//回転のフラグを初期化
//
//	//当たり判定セット
//	Hits::SetHitBox(this,m_px, m_py,ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
//}
//
////アクション
//void CObjRollBlock::Action()
//{
//	if(m_count<=90)//90以下なら
//		m_count++;//カウントを増やす
//
//
//}
//
////ドロー
//void CObjRollBlock::Draw()
//{
//	//描画カラー
//	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
//
//	RECT_F src, dst;
//
//	//マップオブジェクトを持ってくる
//	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
//
//	//切り取り位置
//	src.m_top = 0.0f;
//	src.m_left = 0.0f;
//	src.m_right = ROLL_BLOCK_SIZE_WIDTH;
//	src.m_bottom = ROLL_BLOCK_SIZE_HEIGHT;
//
//	//描画位置
//	dst.m_top = m_py - objmap->GetScrollY();
//	dst.m_left =m_px - objmap->GetScrollX();
//	dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
//	dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
//
//	//描画
//	Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, m_r);
//}
