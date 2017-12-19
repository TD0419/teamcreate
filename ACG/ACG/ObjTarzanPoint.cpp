#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTarzanPoint.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjTarzanPoint::CObjTarzanPoint(int x, int y,bool look_flag)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;

	m_look_flag = look_flag;
}

//イニシャライズ
void CObjTarzanPoint::Init()
{
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, TARZAN_POINT_WIDTH, TARZAN_POINT_HEIGHT, ELEMENT_GIMMICK, OBJ_TARZAN_POINT, 1);
}

//アクション
void CObjTarzanPoint::Action()
{
	//ボスオブジェクトを持ってくる
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);

	//ボスオブジェクトがあれば
	if (objboss != nullptr)
	{
		//4番目の攻撃なら
		if (objboss->GetAttackMode() == 4)
			m_look_flag = true;
		else
			m_look_flag = false;
	}

	if (m_look_flag == false)//見えない状態なら
	{
		Hits::DeleteHitBox(this);	//所持するHitBoxを除去。
		return;
	}

	//画面外なら
	if (WindowCheck(m_px, m_py, TARZAN_POINT_WIDTH, TARZAN_POINT_HEIGHT) == false )
	{
		WindowOutDelete(this, m_map_x, m_map_y);//削除処理(復活あり)
		return;
	}

	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//当たり判定がなければ当たり判定をセット
	if (hit == nullptr)
	{
		Hits::SetHitBox(this, m_px, m_py, TARZAN_POINT_WIDTH, TARZAN_POINT_HEIGHT, ELEMENT_GIMMICK, OBJ_TARZAN_POINT, 1);
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjTarzanPoint::Draw()
{
	if (m_look_flag == false)	//見えない状態なら
		return;

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top    = 0.0f;
	src.m_left   = 0.0f;
	src.m_right  = TARZAN_POINT_WIDTH;
	src.m_bottom = TARZAN_POINT_HEIGHT;

	//描画位置
	dst.m_top    = m_py - objmap->GetScrollY();
	dst.m_left   = m_px - objmap->GetScrollX();
	dst.m_right  = dst.m_left + TARZAN_POINT_WIDTH;
	dst.m_bottom = dst.m_top + TARZAN_POINT_HEIGHT;

	//描画
	Draw::Draw(GRA_TARZAN_POINT, &src, &dst, color, 0.0f);

}