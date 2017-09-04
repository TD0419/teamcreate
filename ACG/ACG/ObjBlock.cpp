//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBlock::CObjBlock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjBlock::Init()
{	
	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);

}

//アクション
void CObjBlock::Action()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//主人公オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();//当たり判定の処理を行う
	}
	
	//ボスオブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_BOSS) != nullptr)
	{
		BossHit();//当たり判定の処理を行う
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjBlock::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//描画
	Draw::Draw(2, &src, &dst, color, 0.0f);

}

void CObjBlock::HeroHit()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//衝突の情報をhit_dataに入れる

	//主人公オブジェクトを持ってくる
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//データがあれば
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//あたっている角度をもってくる

			//ブロックの右側が衝突している場合
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_hero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				obj_hero->SetPosX(m_px + BLOCK_SIZE);//主人公の位置をブロックの右側までずらす
			}
			//ブロックの上側が衝突している場合
			else if (45 < r && r < 125)
			{
				obj_hero->bu = true;
				obj_hero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				obj_hero->SetPosY(m_py - HERO_SIZE_Y);//主人公の位置をブロックの上側までずらす
			}
			//ブロックの左側が衝突している場合
			else if (125 < r && r < 225)
			{
				obj_hero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				obj_hero->SetPosX(m_px - HERO_SIZE_X);//主人公の位置をブロックの左側までずらす
			}
			//ブロックの下側が衝突している場合
			else if (225 < r && r < 315)
			{
				obj_hero->SetVecY(0.0f);//主人公のY方向の移動を０にする
				obj_hero->SetPosY(m_py + BLOCK_SIZE);//主人公の位置をブロックの上側までずらす
			}
		}
	}
}

//確認用にボス版を用意しました。今後、削除変更してもかまいません。
void CObjBlock::BossHit()
{
	//自身のHitBoxを取得
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;						//衝突の情報を入れる構造体
	hit_data = hit->SearchObjNameHit(OBJ_BOSS); //衝突の情報をhit_dataに入れる

	//デバッグ用ボスオブジェクト情報を取得
	CObjBoss* obj_boss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//データあり
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//ぶつかっている角度をもってくる

			//ブロックの右側が衝突している場合
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_boss->SetVecX(0.0f);//ボスのX方向の移動を０にする
				obj_boss->SetPosX(m_px + BLOCK_SIZE);//ボスの位置をブロックの右側までずらす
			}
			//ブロックの上側が衝突している場合
			else if (45 < r && r < 125)
			{
				obj_boss->SetVecY(0.0f);//ボスのY方向の移動を０にする
				obj_boss->SetPosY(m_py - BOSS_SIZE);//ボスの位置をブロックの上側までずらす
			}
			//ブロックの左側が衝突している場合
			else if (125 < r && r < 225)
			{
				obj_boss->SetVecX(0.0f);//ボスのX方向の移動を０にする
				obj_boss->SetPosX(m_px - BOSS_SIZE);//ボスの位置をブロックの左側までずらす
			}
			//ブロックの下側が衝突している場合
			else if (225 < r && r < 315)
			{
				obj_boss->SetVecY(0.0f);//ボスのY方向の移動を０にする
				obj_boss->SetPosY(m_py + BLOCK_SIZE);//ボスの位置をブロックの上側までずらす
			}
		}
	}
}

// BlockHit関数
// 引数1  float x        :判定を行うobjectのX位置
// 引数2  float y        :判定を行うobjectのY位置
// 引数3  bool scroll_on :判定を行うobjectはスクロールの影響与えるかどうか（true = 与える false = 与えない）　
// 引数4  bool* up       :上下左右判定の上部分に当たっているかどうかを返す
// 引数5  bool* down     :上下左右判定の上部分に当たっているかどうかを返す
// 引数6  bool* left     :上下左右判定の上部分に当たっているかどうかを返す
// 引数7  bool* right    :上下左右判定の上部分に当たっているかどうかを返す
// 引数8  float* vx      :左右判定時の反発による移動方向・力の値を変えて返す
// 引数9  float* vy      :上下左右判定時による自由落下運動の移動方向・力の値変えて返す
// 引数10 int* bt        :下部判定時、特殊なブロックのタイプを返す
//判定を行うオブジェクトとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
//void CObjBlock::BlockHit(
//	float *x, float *y, bool scroll_on,
//	bool*up, bool* down, bool* left, bool* right,
//	float* vx, float*vy, int* bt
//)
//{
//	//主人公の衝突状態用フラグの初期化
//	*up = (false);
//	*down = (false);
//	*left = (false);
//	*right = (false);
//
//	//踏んでいるブロックの種類の初期化
//	*bt = 0;
//
//	//m_mapの全要素にアクセス
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 100; j++)
//		{
//			if (m_map[i][j] > 0 && m_map[i][j] != 4)
//			{
//				//要素番号を座標に変更
//				float bx = j * 64.0f;
//				float by = i * 64.0f;
//
//				//スクロールの影響
//				float scroll = scroll_on ? m_scroll : 0;
//
//				//主人公とブロックの当たり判定
//				if ((*x/* + (-scroll)*/ + 64.0f > bx) && (*x /*+ (-scroll)*/ < bx + 64.0f) && (*y + HERO_SIZE_Y > by) && (*y < (by + BLOCK_SIZE)))
//				{
//					//上下左右判定
//
//					//vectorの作成
//					float rvx = (*x /*+ (-scroll)*/) - bx;
//					float rvy = *y - by;
//
//					//長さを求める
//					float len = sqrt(rvx * rvx + rvy * rvy);
//
//					//角度を求める
//					float r = atan2(rvy, rvx);
//					r = r * 180.0f / 3.14f;
//
//					if (r <= 0.0f)
//					{
//						r = abs(r);
//					}
//					else
//					{
//						r = 360.0f - abs(r);
//					}
//					//lenがある一定の長さのより短い場合に入る
//					if (len < 88.0f)
//					{
//
//						//角度で上下左右を判定
//						if ((r < 45 && r > 0) || r > 315)
//						{
//							//右
//							*right = (true);					//主人公の左の部分が衝突している
//							*x = bx + 64.0f /*+ (scroll)*/;   //ブロックの位置＋主人公の幅
//							*vx = -(*vx) * 0.1f; //-VX*反発係数
//						}
//						if (r > 45 && r < 135)
//						{
//							//上
//							*down = (true);					//主人公の下の部分が衝突している
//							*y = by - HERO_SIZE_Y ;				//ブロックの位置＋主人公の幅
//															//種類を渡すのスタートとゴールのみ変更する
//							if (m_map[i][j] >= 2)
//							{
//								*bt = m_map[i][j];			//ブロック要素 ( type )を主人公に渡す
//							}
//							*vy = 0.0f;
//						}
//						if (r > 135 && r < 225)
//						{
//							//左
//							*left = (true);					//主人公の右の部分が衝突している
//							*x = bx - 64.0f /*+ (scroll)*/;	//ブロックの位置＋主人公の幅
//							*vx = -(*vx) * -0.1f; //-VX*反発係数
//						}
//						if (r > 255 && r < 315)
//						{
//							//下
//							*up = (true);					//主人公の上の部分が衝突している
//							*y = by + HERO_SIZE_Y;				//ブロックの位置＋主人公の幅
//							if (*vy < 0)
//							{
//								*vy = 0.0f;
//							}
//							
//						}
//					}
//				}
//			}
//		}
//
//
//	}
//}
//