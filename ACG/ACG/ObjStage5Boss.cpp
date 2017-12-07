#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"
#include "ObjStage5Boss.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStage5Boss::CObjStage5Boss(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //第5ボスのＨＰ(仮にＨＰを[100]と設定)

	//音楽
	//Audio::Start(BOSS);
	//Audio::Stop(STAGE);

	//ライトアームの描画
	CObjStage5BossArms* objstage5_boss_arm_right = new CObjStage5BossArms(m_px - 370, m_py - 166, 1);
	Objs::InsertObj(objstage5_boss_arm_right, OBJ_STAGE5_BOSS_ARMS, 10);
	//レフトアームの描画
	CObjStage5BossArms* objstage5_boss_arm_left = new CObjStage5BossArms(m_px + 156, m_py - 166, 2);
	Objs::InsertObj(objstage5_boss_arm_left, OBJ_STAGE5_BOSS_ARMS, 10);

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BODY_SIZE, STAGE5_BOSS_BODY_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
}

//アクション
void CObjStage5Boss::Action()
{

	//当たり判定更新
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjStage5Boss::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//胴腕接続電気-------------------------------
	//左腕部分
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()  + ELECTRIC_L_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() - ELECTRIC_L_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);

	//右腕部分
	//切り取り位置
	src.m_top = STAGE5_BOSS_ELECTRIC_HEIGHT;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

	//描画位置
	dst.m_top =  m_py - objmap->GetScrollY() + ELECTRIC_R_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() + ELECTRIC_R_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);

	//胴体--------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_BODY_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_BODY_SIZE;
	
	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = STAGE5_BOSS_BODY_SIZE + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_BODY, &src, &dst, color, 0.0f);


	//眼球---------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_EYE_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_EYE_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()  + EYE_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() + EYE_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_EYE_SIZE;	
	dst.m_bottom = dst.m_top + STAGE5_BOSS_EYE_SIZE;
	//描画
	Draw::Draw(GRA_STAGE5_BOSS_EYE, &src, &dst, color, 0.0f);
	

}