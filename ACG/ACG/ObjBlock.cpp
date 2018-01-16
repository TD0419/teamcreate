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
	m_map_x = x;
	m_map_y = y;
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjBlock::Init()
{	
	m_block_determine=0;
}

//アクション
void CObjBlock::Action()
{
	
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//画面内か調べる
	bool wincheck_flag =WindowCheck(m_px,m_py,BLOCK_SIZE,BLOCK_SIZE);

	//画面外なら
	if (wincheck_flag == false)
	{
		//削除するので次に来たときに生成するようにフラグをオンにする
		objmap->SetMapCreate(m_map_x, m_map_y, true);
		this->SetStatus(false);		//自身を削除
	}

	
}

//ドロー
void CObjBlock::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//map_numにマップ情報の一個上の情報を送る
	int map_num = objmap->GetMap(m_map_x, m_map_y - 1);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//ブロックの一個上にブロックがある時描画変更
	if (map_num==MAP_BLOCK)
	{
		src.m_top = 0.0f;
		src.m_left = 65.0f;
		src.m_right = 128.0f;
		src.m_bottom = 64.0f;
	}

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//描画
	Draw::Draw(GRA_BLOCK, &src, &dst, color, 0.0f);
}

//ブロックとオブジェクトの当たり判定
void CObjBlock::BlockHit(
	float* x, float* y, float width, float height,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy
)
{
	//マップ情報を持ってくる
	CObjMap* map = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//衝突情報初期化
	*up = false;
	*left = false;
	*right = false;
	*down = false;

	//幅と高さを半分にする
	float width_half = width / 2.0f;
	float height_half = height / 2.0f;

	//ブロックの幅と高さを半分にする
	float block_width_half = BLOCK_SIZE / 2.0f;
	float block_height_half = BLOCK_SIZE / 2.0f;

	//次フレームでの移動場所
	float new_y = *y + *vy;
	float new_x = *x + *vx;

	//はみ出し許容範囲
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	//m_mapの全要素にアクセス
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//判定したいブロック
			if (map->GetMap(j, i) == MAP_BLOCK)
			{
				//要素番号を座標に変更
				float bx = j*BLOCK_SIZE;
				float by = i*BLOCK_SIZE;

				//ブロックとの当たり判定
				if (abs((bx + block_width_half) - (*x + width_half)) <= block_width_half + width_half)
				{
					if (abs((by + block_height_half) - (*y + height_half)) <= block_height_half + height_half)
					{
						//左に移動している
						if (*vx < 0.0f)
						{
							//左にあるブロック
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								int map_b_x = (int)((*x + *vx) / BLOCK_SIZE);
								//進む先がブロックの右側が衝突している場合(当たっているのが0以外)
								if (map->GetMap(map_b_x, i) == MAP_BLOCK)
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE + BLOCK_SIZE;
									*right = true;
								}
							}
						}
						//右に移動している
						else if (*vx > 0.0f)
						{
							//右にあるブロック
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								int map_b_x = (int)((*x + width + *vx) / BLOCK_SIZE);
								//進む先がブロックの左側が衝突している場合(当たっているのが0以外)
								if (map->GetMap(map_b_x, i) == MAP_BLOCK)
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE - width;
									*left = true;
								}
							}
						}

						//下に移動している
						if (*vy > 0.0f)
						{
							//下にあるブロックを全て調べる
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								int map_b_y = (int)((*y + height + *vy) / BLOCK_SIZE);
								//進む先がブロックの上側が衝突している場合(ブロック(1))
								if (map->GetMap(i, map_b_y) == MAP_BLOCK)
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE - height;
									*down = true;
								}
							}
						}
						//上に移動している
						else if (*vy < 0.0f)
						{
							//上にあるブロックを全て調べる
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								int map_b_y = (int)((*y + *vy) / BLOCK_SIZE);
								//進む先がブロックの下側が衝突している場合(ブロック(1))
								if (map->GetMap(i, map_b_y) == MAP_BLOCK)
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE + BLOCK_SIZE;
									*up = true;
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

//全てのブロックとオブジェクトの当たり判定
void CObjBlock::AllBlockHit(
	float* x, float* y, float width, float height,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy
)
{
	//マップ情報を持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//衝突情報初期化
	*up = false;
	*left = false;
	*right = false;
	*down = false;

	//幅と高さを半分にする
	float width_half = width / 2.0f;
	float height_half = height / 2.0f;

	//ブロックの幅と高さを半分にする
	float block_width_half = BLOCK_SIZE / 2.0f;
	float block_height_half = BLOCK_SIZE / 2.0f;

	//次フレームでの移動場所
	float new_y = *y + *vy;
	float new_x = *x + *vx;

	//はみ出し許容範囲
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	int block_type;//ブロックの種類

	//m_mapの全要素にアクセス
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//ブロックの種類を持ってくる
			block_type = objmap->GetMap(j, i);
			
			//判定したいブロック
			if (block_type == MAP_BLOCK || block_type == MAP_THROUGH_BLOCK|| block_type ==MAP_LADDERS || block_type == MAP_NEEDLE_STAND)
			{
				//要素番号を座標に変更
				float bx = j*BLOCK_SIZE;
				float by = i*BLOCK_SIZE;

				//ブロックとの当たり判定
				if (abs((bx + block_width_half) - (*x + width_half)) <= block_width_half + width_half)
				{
					if (abs((by + block_height_half) - (*y + height_half)) <= block_height_half + height_half)
					{
						//左に移動している
						if (*vx < 0.0f)
						{
							//左にあるブロック
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								int map_b_x = (int)((*x + *vx) / BLOCK_SIZE);
								//進む先がブロックの右側が衝突している場合(当たっているのが0以外)
								if (objmap->GetMap(map_b_x, i) == MAP_BLOCK || objmap->GetMap(map_b_x, i) == MAP_THROUGH_BLOCK )
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE + BLOCK_SIZE;
									*right = true;
								}
							}
						}
						//右に移動している
						else if (*vx > 0.0f)
						{
							//右にあるブロック
							for (int i = (int)((*y + bleed_y) / BLOCK_SIZE);
								i <= (int)((*y + height - bleed_y) / BLOCK_SIZE); i++)
							{
								int map_b_x = (int)((*x + width + *vx) / BLOCK_SIZE);
								//進む先がブロックの左側が衝突している場合(当たっているのが0以外)
								if (objmap->GetMap(map_b_x, i) == MAP_BLOCK || objmap->GetMap(map_b_x, i) == MAP_THROUGH_BLOCK )
								{
									*vx = 0.0f;
									*x = map_b_x * BLOCK_SIZE - width;
									*left = true;
								}
							}
						}

						//下に移動している
						if (*vy > 0.0f)
						{
							//下にあるブロックを全て調べる
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								int map_b_y = (int)((*y + height + *vy) / BLOCK_SIZE);
								//進む先がブロックの上側が衝突している場合(ブロック(1)とスルーブロック(12))
								if (objmap->GetMap(i, map_b_y) == MAP_BLOCK || objmap->GetMap(i, map_b_y) == MAP_THROUGH_BLOCK )
								{
									*vy = 0.0f; 
									*y = map_b_y * BLOCK_SIZE - height;
									*down = true;
								}
							}
						}
						//上に移動している
						else if (*vy < 0.0f)
						{
							//上にあるブロックを全て調べる
							for (int i = (int)((*x + bleed_x) / BLOCK_SIZE);
								i <= (int)((*x + width - bleed_x) / BLOCK_SIZE); i++)
							{
								int map_b_y = (int)((*y + *vy) / BLOCK_SIZE);
								//進む先がブロックの下側が衝突している場合(ブロック(1))
								if (objmap->GetMap(i, map_b_y) == MAP_BLOCK || objmap->GetMap(i, map_b_y) == MAP_THROUGH_BLOCK )
								{
									*vy = 0.0f;
									*y = map_b_y * BLOCK_SIZE + BLOCK_SIZE;
									*up = true;
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
