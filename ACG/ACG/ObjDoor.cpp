#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjDoor.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDoor::CObjDoor(int x, int y)
{
	m_px = x * DOOR_SIZE;
	m_py = y * DOOR_SIZE;
}

//イニシャライズ
void CObjDoor::Init()
{
	//m_px = 100.0f;//ドアX座標
	//m_py = 384.0f;//ドアY座標
}

//アクション
void CObjDoor::Action()
{
	//恐らくボス情報使うので
	CObjBoss* objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
}

//ドロー
void CObjDoor::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 64.0f;
	src.m_right = src.m_left+128.0f;
	src.m_bottom = src.m_top+128.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + DOOR_SIZE;
	dst.m_bottom = dst.m_top + DOOR_SIZE;

	//描画
	Draw::Draw(6, &src, &dst, color, 0.0f);
}