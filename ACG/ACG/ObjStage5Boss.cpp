#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "Function.h"
#include "ObjStage5Boss.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjStage5Boss::CObjStage5Boss(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //第5ボスのＨＰ(仮にＨＰを[100]と設定)

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
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

}