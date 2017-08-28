#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMap.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjMap::CObjMap(int map[MAP_Y_MAX][MAP_X_MAX])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int)*(MAP_Y_MAX * MAP_X_MAX));
}

//イニシャライズ
void CObjMap::Init()
{
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;
}

//アクション
void CObjMap::Action()
{
	//スクロール量(ブロックの数に計算して渡す)をもとにオブジェクトを生成する
	CreateObj(int(m_scroll_x / BLOCK_SIZE), int(m_scroll_y / BLOCK_SIZE));	//←マップデータの読み込みをするまで使えないのでコメント化しておく	
}

//スクロール量をもとにオブジェクトの生成をする関数
//	scroll_block_num_x:	X軸の現在のスクロール量がブロック何個分か
//	scroll_block_num_y:	Y軸の現在のスクロール量がブロック何個分か
// *この関数内のコメントのスクロール量はすべて引数で渡ってきたブロック数で換算した物のことを指す
void CObjMap::CreateObj(int scroll_block_num_x, int scroll_block_num_y)
{
	//yの値がスクロール量Y　から　ウィンドウ内に収まる最大値＋スクロール量Y　または　マップの最大値　に達するまで回す
	for (int y = scroll_block_num_y ; y < MAP_Y_MAX && y < scroll_block_num_y + MAP_WINDOW_MAX_Y; y++)
	{
		//xの値がスクロール量X　から　ウィンドウ内に収まる最大値＋スクロール量X　または　マップの最大値　に達するまで回す
		for (int x = scroll_block_num_x; x < MAP_X_MAX && x < scroll_block_num_x + MAP_WINDOW_MAX_X; x++)
		{			
			//yの値が（クリエイトラインの上下＋スクロール量Y）と同じ または　xの値が（クリエイトラインの左右＋スクロール量X）と同じ なら
			if (	y == (CREATE_LINE_UP	+ scroll_block_num_y)	|| y == ( CREATE_LINE_DOWN	+ scroll_block_num_y) ||
					x == (CREATE_LINE_LEFT	+ scroll_block_num_x)	|| x == ( CREATE_LINE_RIGHT + scroll_block_num_x)
				)
			{
				//敵オブジェクトがあれば
				if (m_map[y][x] == MAP_ENEMY)
				{
					//敵オブジェクトを作成する デバッグなので今はヒーローオブジェクトを生成)
					CObjEnemy* ObjEnemy = new CObjEnemy(x , y);
					Objs::InsertObj(ObjEnemy, OBJ_ENEMY, 10);
	
					//オブジェクトの生成を追えたら空にする
					m_map[y][x] = MAP_SPACE;
				}
			}
		}
	}
}

//ドロー
void CObjMap::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,0.5f, 1.0f };

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	for (int map_y = 0; map_y < MAP_Y_MAX; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X_MAX; map_x++)
		{
			RECT_F src, dst;
			//ブロック(ノーマル)
			switch (m_map[map_y][map_x])
			{
			case MAP_BLOCK:
				//切り取り位置
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 512.0f;
				src.m_bottom = 512.0f;

				//描画位置
				dst.m_top = map_y * BLOCK_SIZE - obj_m->GetScrollY();
				dst.m_left = map_x * BLOCK_SIZE - obj_m->GetScrollX();
				dst.m_right = dst.m_left + BLOCK_SIZE;
				dst.m_bottom = dst.m_top + BLOCK_SIZE;

				//描画
				Draw::Draw(0, &src, &dst, color, 0.0f);
				break;

			
			default:
				break;
			}
		}
	}
}
