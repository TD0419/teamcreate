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
	m_r = 0.0f;
	m_rotation_flag = false;//回転はまだしない

	m_rope_hit_flag = false;//初期は衝突してい無い

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


	//回転フラグがONなら
	if (m_rotation_flag == true)
	{
		
		//90度以下ならスイッチを回転させる
		if (m_r < 90.0f) 
		{
			//ロープと回転ブロックスイッチの位置を調整する
			PositionAdjustment();
			m_r += 2.0f;//角度の加算
		}
	}
	//90度以上かつロープと接触していたら
	//ロープを消し、90度にする
	if (m_r >= 90.0f && hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		//回転が終了しているのでロープを消去する
		CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
		if (objrope != nullptr)
			objrope->Delete();

		m_r = 90.0f;//90を超えないようにする
	}

	//ロープと当たっている
	if (hit->CheckObjNameHit(OBJ_ROPE) != nullptr)
	{
		//1フレーム前、フラグがOFFならロープの位置を調整する
		if (m_rope_hit_flag == false)
		{
			//ロープと回転ブロックスイッチの位置を調整する
			//一回でもしておかないと回転ブロックスイッチの上のほうでロープが引っかかったら
			//一瞬だけHit判定は起きるがそれ以降Hit判定無し状態になってしまうので
			//ここで位置を調整する
			PositionAdjustment();
			//衝突しているのでフラグをONにする
			m_rope_hit_flag = true;
		}
		//Aキーが入力されたら
		//回転フラグをON(回転する)にする
		if (Input::GetVKey('A') == true)
		{
			m_rotation_flag = true; //回転をする
			//フラグを入れる
			mp_base_block->SetRollFlag(m_rotation_flag);
		}
	}
	else
		m_rope_hit_flag = false;
	
	//hitBox更新
	HitBoxUpData(hit, m_px, m_py);

	//回転が最後までいっていたら自身を消去する
	//回転が終了したら不必要と思ったので消去しました。
	if (m_r >= 90.0f)
		WindowOutDelete(this);
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

	Draw::Draw(GRA_TARZAN_POINT, &src, &dst, color, 0.0f);
}

//ロープと回転ブロックスイッチの位置を調整する関数
void CObjRollBlockSwitch::PositionAdjustment()
{
	//sin値　cos値を求める
	float sin = sinf(m_r * 3.14f / 180.0f);
	float cos = cosf(m_r * 3.14f / 180.0f);

	//角度を元に位置を調節する
	m_px = m_base_block_px - sin * ROLL_BLOCK_SIZE_WIDTH;
	m_py = m_base_block_py + ROLL_BLOCK_SIZE_WIDTH - cos * ROLL_BLOCK_SIZE_WIDTH;

	//ロープオブジェクトを持ってくる
	CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
	if (objrope != nullptr)
	{
		//ロープの位置をこのオブジェクトの位置に合わせる　+6.0fすることでロープとスイッチが常にあたるようにする
		objrope->SetPosX(m_px + 6.0f);
		objrope->SetPosY(m_py + 6.0f);
	}
}