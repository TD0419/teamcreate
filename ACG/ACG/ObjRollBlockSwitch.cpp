//使用するヘッダー
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "ObjRollBlockSwitch.h"
#include "Function.h"

#include "GameL\HitBoxManager.h"

//コンストラクタ
CObjRollBlockSwitch::CObjRollBlockSwitch(float x, float y, CObjRollBlock* p)
{
	//位置を設定する
	m_px = x ;
	m_py = y ;

	//ブロックの位置の保存
	m_base_block_px = x;
	m_base_block_py = y;

	//基盤のポインタを保存
	mp_base_block = p;
}

//イニシャライズ
void CObjRollBlockSwitch::Init()
{
	m_pull_flag = false;
	m_r = 0.0f;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, ROLL_BLOCK_SWITCH_SIZE_WIDTH, ROLL_BLOCK_SWITCH_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_ROLL_BLOCK_SWITCH, 1);
}

//アクション
void CObjRollBlockSwitch::Action()
{
	//HitBoxのポインタを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//mapオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//引っ張りをオフにする
	m_pull_flag = false;

	//ロープと当たっていれば
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		//左移動していれば
		if (Input::GetVKey('A') == true)
		{
			m_r += 2.0f;//角度の加算

			//sin値　cos値を求める
			float m_sin = sinf(m_r * 3.14f / 180.0f);
			float m_cos = cosf(m_r * 3.14f / 180.0f);

			//角度を元に位置を調節する
			m_px = m_base_block_px - m_sin * ROLL_BLOCK_SIZE_WIDTH;
			m_py = m_base_block_py + ROLL_BLOCK_SIZE_WIDTH - m_cos * ROLL_BLOCK_SIZE_WIDTH;
			
			//引っ張りのフラグをオンにする
			m_pull_flag=true;
		}
	}

	//フラグを入れる
	mp_base_block->SetRollFlag(m_pull_flag);

	//hitBox更新
	HitBoxUpData(hit, m_px, m_py);
}

//ドロー
void CObjRollBlockSwitch::Draw()
{
	//mapオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	float color[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = ROLL_BLOCK_SWITCH_SIZE_WIDTH;
	src.m_bottom = ROLL_BLOCK_SWITCH_SIZE_HEIGHT;

	//描画の位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROLL_BLOCK_SWITCH_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROLL_BLOCK_SWITCH_SIZE_HEIGHT;

	Draw::Draw(GRA_ROLL_BLOCK_SWITCH, &src, &dst, color, 0.0f);
}