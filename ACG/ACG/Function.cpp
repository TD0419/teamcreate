#include "Function.h"
#include "GameHead.h"
//オブジェクト同士が衝突したときに消失する関数
//引数1　HitBoxポインタ
//引数2　判定したいオブジェクトポインタ
//引数3　オブジェクトネーム
//戻り値 bool 　当たってるか、当たってないか
bool DeleteCheckObjNameHit(CHitBox* hit, CObj* cobj, OBJ_NAME objname)
{
	//指定したオブジェクトとネームが設定されてるオブジェクトがあたったら消去
	if (hit->CheckObjNameHit(objname) != nullptr)
	{
		cobj->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(cobj);	//所持するHitBoxを除去。
		return true;				//当たってる
	}
	return false;					//当たってない
}

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

//ブロックAとブロックBの当たり判定
//ブロックA＝当たった場合移動しないブロック
//ブロックB＝あたった場合移動するブロック
//引数1  float  ax		:ブロックAのX位置
//引数2  float  ay		:ブロックAのY位置
//引数3  float  aw		:ブロックAの幅
//引数4  float  ah		:ブロックAの高さ
//引数5  float* bx		:ブロックBのX位置 ポインタ
//引数6  float* by		:ブロックBのY位置 ポインタ
//引数7  float  bw		:ブロックBの幅
//引数8  float  bh		:ブロックBの高さ
//引数9  float* bvx		:ブロックBのX移動量 ポインタ
//引数10 float* bvy		:ブロックBのY移動量 ポインタ
//戻り値	int			:当たったかどうか||どこに当たったか　0=当たり無し：1=Bから見て上：2=Bから見て下：3=Bから見て右:4=Bから見て左
int HitTestOfAB(float ax, float ay, float aw, float ah,
	float* bx, float* by, float bw, float bh,
	float* bvx, float* bvy)
{
	float ax_min = ax;			//ブロックAのX座標最小
	float ay_min = ay;			//ブロックAのY座標最小
	float ax_max = ax_min + aw;	//ブロックAのX座標最大
	float ay_max = ay_min + ah;	//ブロックAのY座標最大

	float bx_min = *bx;			//ブロックBのX座標最小
	float by_min = *by;			//ブロックBのY座標最小
	float bx_max = bx_min + bw;	//ブロックBのX座標最大
	float by_max = by_min + bh;	//ブロックBのY座標最大

	//はみ出し許容範囲
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	//当たり判定チェック
	if (ax_max < bx_min);//AよりBが右
	else if (bx_max < ax_min);//AよりBが左
	else if (ay_max < by_min);//AよりBが下
	else if (by_max < ay_min);//AよりBが上
	else	//当たりあり。
	{
		//ブロックAの上
		if (by_max - ay_min < bleed_y)
		{
			if (*bvy >= 0.0f)
			{
				*bvy = 0.00000f;//Y移動量を0にする
				*by -= by_max - ay_min-1.390f;//ぶるぶるするので-1.390fしている
				return 2;
			}
		}
		//ブロックAの下
		if (ay_max - by_min < bleed_y)
		{
			if (*bvy <= 0.0f)
			{
				*bvy = 0.00000f;//Y移動量を0にする
				*by += ay_max - by_min;
				return 1;
			}
		}
		//ブロックAの左
		if (bx_max - ax_min < bleed_x)
		{
			if (*bvx >= 0.0f)
			{
				*bvx = 0.00000f;//X移動量を0にする
				*bx -= bx_max - ax_min + 0.001f;//密着してジャンプすると上に乗ってしまうので＋0.001している
				return 3;
			}
		}
		//ブロックAの右
		if (ax_max - bx_min < bleed_x)
		{
			if (*bvx <= 0.0f)
			{
				*bvx = 0.00000f;//X移動量を0にする
				*bx += ax_max - bx_min + 0.001f;//密着してジャンプるると上に乗ってしまうので＋0.001している
				return 4;
			}
		}
	}
	return 0;
}