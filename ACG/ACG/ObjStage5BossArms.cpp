#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"

#include "ObjStage5BossArms.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStage5BossArms::CObjStage5BossArms(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;

}

//イニシャライズ
void CObjStage5BossArms::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 10; //第5ボス腕のＨＰ(仮にＨＰを[10]と設定)

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px + 160.0f, m_py + 138.0f, STAGE5_BOSS_ARMS_WIDTH_SIZE - 360.0f, STAGE5_BOSS_ARMS_HEIGHT_SIZE - 225.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
	
}

//アクション
void CObjStage5BossArms::Action()
{

	//当たり判定更新
	HitBoxUpData(Hits::GetHitBox(this), m_px+160.0f, m_py + 138.0f);
	
}

//ドロー
void CObjStage5BossArms::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//左腕---------------------------------------
	//切り取り位置
	src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY() ;
	dst.m_left = m_px - objmap->GetScrollX() ;
	dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);

	//右腕---------------------------------------
	//切り取り位置
	src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE;
	src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE + m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);

}