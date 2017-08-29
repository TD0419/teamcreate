#include "Function.h"
#include "GameHead.h"

//HitBoxの位置を更新する関数
//引数1 更新するHitBoxポインタ
//引数2 現在のHitBoxの位置X
//引数2 現在のHitBoxの位置Y
void HitBoxUpData(CHitBox* hit,float m_px,float m_py)
{
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBoxの位置情報の変更
	hit->SetPos(m_px - obj_m->GetScrollX(), m_py);
}