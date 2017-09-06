//使用するヘッダーファイル　
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBossDropKey.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBossDropKey::CObjBossDropKey(int x, int y)
{
	m_x = x * BOSS_DORP_KEY_SIZE;
	m_y = y * BOSS_DORP_KEY_SIZE;
}

//イニシャライズ
void CObjBossDropKey::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_x, m_y, BOSS_DORP_KEY_SIZE, BOSS_DORP_KEY_SIZE, ELEMETN_ITEM, OBJ_BOSS_DROP_KEY, 1);
}

//アクション
void CObjBossDropKey::Action()
{
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_x, m_y);
}

//ドロー
void CObjBossDropKey::Draw()
{

}