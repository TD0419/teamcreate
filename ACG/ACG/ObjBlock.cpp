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
	//マップオブジェクトを持ってくる
	//CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	////当たり判定
	//Hits::SetHitBox(this, m_px-obj_m->GetScrollX(), m_py - obj_m->GetScrollY(), BLOCK_SIZE, BLOCK_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);
	m_b = false;
}

//アクション
void CObjBlock::Action()
{
	////自身のHitBoxをもってくる
	//CHitBox*hit = Hits::GetHitBox(this);

	//主人公オブジェクトと衝突していれば
	/*if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();//当たり判定の処理を行う
	}*/
	
	////ボスオブジェクトと衝突していれば
	//if (hit->CheckObjNameHit(OBJ_BOSS) != nullptr)
	//{
	//	BossHit();//当たり判定の処理を行う
	//}

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//画面内か調べる
	bool wincheck_flag =WindowCheck(m_px,m_py,BLOCK_SIZE,BLOCK_SIZE);

	//画面ないなら
	if (wincheck_flag == true)
	{
		//HitBoxの位置を更新する
//		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}
	else
	{
		//マップ要素に数値を入れる
		//obj_m->SetMap((m_px / BLOCK_SIZE), (m_py / BLOCK_SIZE), MAP_BLOCK);
	
		//削除するので次に来たときに生成するようにフラグをオンにする
		obj_m->SetMapCreate(int(m_px / BLOCK_SIZE), int(m_py / BLOCK_SIZE), true);

		this->SetStatus(false);		//自身を削除
	//	Hits::DeleteHitBox(this);	//ヒットボックスを削除
	}

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
	if (m_b==true)
	{
		src.m_top = 0.0f;
		src.m_left = 65.0f;
		src.m_right = 128.0f;
		src.m_bottom = 64.0f;
	}
	//描画位置
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//描画
	Draw::Draw(2, &src, &dst, color, 0.0f);
}

//ブロックとオブジェクトの当たり判定
void CObjBlock::BlockHit(
	float* x, float* y, float width, float height, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy
)
{
	//マップ情報を持ってくる
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	
	//描画
	Draw::Draw(2, &src, &dst, color, 0.0f);
	//衝突情報初期化
	*up		= false;
	*left	= false;
	*right	= false;
	*down	= false;

	//幅と高さを半分にする
	float width_half = width / 2.0f;
	float height_half = height / 2.0f;

	//ブロックの幅と高さを半分にする
	float block_width_half  = BLOCK_SIZE / 2.0f;
	float block_height_half = BLOCK_SIZE / 2.0f;

	//次フレームでの移動場所
	float new_y = *y + *vy;
	float new_x = *x + *vx;
	
	scroll_on = false;
	//スクロールを加えるか(基本主人公のみ)
	float scroll_x = scroll_on ? map->GetScrollX() : 0.0f;
	float scroll_y = scroll_on ? map->GetScrollY() : 0.0f;

	//m_mapの全要素にアクセス
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//判定したいブロック
			if (map->GetMap(j,i) == MAP_BLOCK/*100*/)
			{
				//要素番号を座標に変更
				float bx = j*BLOCK_SIZE;
				float by = i*BLOCK_SIZE;

				//ブロックとの当たり判定
				if (abs((bx + block_width_half) - (*x - scroll_x + width_half)) <= block_width_half + width_half)
				{
					if (abs((by + block_height_half) - (*y - scroll_y + height_half)) <= block_height_half + height_half)
					{
						//左に移動している
						if (*vx < 0.0f)
						{
							//左にあるブロック
							for (int i = (int)((*y - scroll_y + 10.0f) / BLOCK_SIZE);
								i <= (int)((*y - scroll_y + height - 20.0f) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x - scroll_x + *vx) / BLOCK_SIZE);
								//進む先がブロックの右側が衝突している場合(当たっているのが0以外)
								if (0 < map->GetMap(map_b_x, i) ||
									0 < map->GetMap(map_b_x, i))
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE + BLOCK_SIZE + scroll_x;
									*right = true;
								}
							}
						}
						//右に移動している
						else if (*vx > 0.0f)
						{
							//右にあるブロック
							for (int i = (int)((*y - scroll_y + 10.0f) / BLOCK_SIZE);
								i <= (int)((*y - scroll_y + height - 20.0f) / BLOCK_SIZE); i++)
							{
								float map_b_x = (int)((*x - scroll_x + width + *vx) / BLOCK_SIZE);
								//進む先がブロックの左側が衝突している場合(当たっているのが0以外)
								if (0 < map->GetMap(map_b_x, i) ||
									0 < map->GetMap(map_b_x, i))
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE - width + scroll_x;
									*left = true;
								}
							}
						}

						//下に移動している
						if (*vy > 0.0f)
						{
							//下にあるブロックを全て調べる
							for (int i = (int)((*x - scroll_x + 5.0f) / BLOCK_SIZE);
								i <= (int)((*x - scroll_x + width - 5.0f) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y + height - scroll_y + *vy) / BLOCK_SIZE);
								//進む先がブロックの上側が衝突している場合(当たっているのが0以外)
								if (0 < map->GetMap(i, map_b_y) ||
									0 < map->GetMap(i, map_b_y))
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE - height + scroll_y;
									*down = true;
								}
							}
						}
						//上に移動している
						else if (*vy < 0.0f)
						{
							//上にあるブロックを全て調べる
							for (int i = (int)((*x - scroll_x + 5.0f) / BLOCK_SIZE);
								i <= (int)((*x - scroll_x + width - 5.0f) / BLOCK_SIZE); i++)
							{
								float map_b_y = (int)((*y - scroll_y + *vy) / BLOCK_SIZE);
								//進む先がブロックの下側が衝突している場合(当たっているのが0以外)
								if (0 < map->GetMap(i, map_b_y) ||
									0 < map->GetMap(i, map_b_y))
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE + BLOCK_SIZE + scroll_y;
									*up = true;
									m_b = true;
								}
								
							}
						}
						return;
					}
				}
			}
		}
	}
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
			if (0.0f < r && r < 45.0f || 315.0f < r && r < 360.0f)
			{
				obj_hero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				obj_hero->SetPosX(m_px + BLOCK_SIZE);//主人公の位置をブロックの右側までずらす
			}
			//ブロックの上側が衝突している場合
			else if (45.0f < r && r < 125.0f)
			{
				obj_hero->SetPosY(m_py - HERO_SIZE_Y);//主人公の位置をブロックの上側までずらす
				obj_hero->SetVecY(0.0f);//主人公のY方向の移動を０にする
			}
			//ブロックの左側が衝突している場合
			else if (125.0f < r && r < 225.0f)
			{
				obj_hero->SetVecX(0.0f);//主人公のX方向の移動を０にする
				obj_hero->SetPosX(m_px - HERO_SIZE_X);//主人公の位置をブロックの左側までずらす
			}
			//ブロックの下側が衝突している場合
			else if (225.0f < r && r < 315.0f)
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