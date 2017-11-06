#include "Function.h"
#include "GameHead.h"

//HitBoxの位置を更新する関数
//引数1 更新するHitBoxポインタ
//引数2 現在のHitBoxの位置X
//引数3 現在のHitBoxの位置Y
void HitBoxUpData(CHitBox* hit,float m_px,float m_py)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBoxの位置情報の変更
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY());
}
//HitBoxの位置と大きさを更新する関数
//引数1 更新するHitBoxポインタ
//引数2 現在のHitBoxの位置X
//引数3 現在のHitBoxの位置Y
//引数4	現在のHitBoxの幅
//引数5	現在のHitBoxの高さ
void HitBoxUpData(CHitBox* hit, float m_px, float m_py, float w, float h)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBoxの位置情報の変更
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY(),w,h);
}
//画面の外に出ているか判定する関数
//引数1,2 :オブジェクトのポジション
//引数3,4 :オブジェクトのサイズ
//戻り値：　画面内：true、画面外：false
bool WindowCheck(float m_px, float m_py,float obj_size_x, float obj_size_y)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	float x = m_px - objmap->GetScrollX();
	float y = m_py - objmap->GetScrollY();

	//上または下でチャック
	if (y < 0 - obj_size_y || y > WINDOW_SIZE_H)
		return false;
	//左または右でチェック
	if (x < 0 - obj_size_x || x > WINDOW_SIZE_W)
		return false;

	return true;
}