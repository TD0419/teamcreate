#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjWireMesh.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjWireMesh::CObjWireMesh(float x, float y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjWireMesh::Init()
{
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, WIRE_MESH_SIZE_WIDTH, WIRE_MESH_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_WIRE_MESH, 1);
}

//アクション
void CObjWireMesh::Action()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjWireMesh::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 640.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画位置
	dst.m_top =  m_py - objmap->GetScrollY() ;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + WIRE_MESH_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + WIRE_MESH_SIZE_HEIGHT;

	//描画
	Draw::Draw(GRA_WIRE_MASH, &src, &dst, color, 0.0f);
	//-------------------------------------------------------
}