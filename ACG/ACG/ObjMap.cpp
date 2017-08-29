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
	
	//マップを元にオブジェクトを生成--------------------------------------
	
	//iが　画面に収まる最大値　または　マップの最大値になるまでまわす
	for (int i = 0; i < MAP_WINDOW_MAX_Y && i<MAP_Y_MAX; i++)
	{
		//jが　画面に収まる最大値　または　マップの最大値になるまでまわす
		for (int j = 0; j < MAP_WINDOW_MAX_X && j<MAP_X_MAX; j++)
		{
			//ブロック作成
			if (m_map[i][j] == MAP_BLOCK)
			{
				CObjBlock* obj_block = new CObjBlock(i,j);
				Objs::InsertObj(obj_block, OBJ_BLOCK, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}
			
			//はしご作成
			if (m_map[i][j] == MAP_LADDERS)
			{
				CObjLadders* obj_ladders = new CObjLadders(i, j);
				Objs::InsertObj(obj_ladders, OBJ_LADDERS, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}

			//ボタン作成
			if (m_map[i][j] == MAP_BUTTON)
			{
				CObjButton* obj_button = new CObjButton(i, j);
				Objs::InsertObj(obj_button, OBJ_BUTTON, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}

			//ロープスイッチ作成
			if (m_map[i][j] == MAP_ROPE_SWITCH)
			{
				CObjRopeSwitch* obj_rope_switch = new CObjRopeSwitch(i, j);
				Objs::InsertObj(obj_rope_switch, OBJ_ROPE_SWITCH, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}

			//リフト作成
			if (m_map[i][j] == MAP_LIFT)
			{
				CObjLift* obj_lift = new CObjLift(i, j);
				Objs::InsertObj(obj_lift, OBJ_LIFT, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}

			//岩作成
			if (m_map[i][j] == MAP_LIFT)
			{
				CObjRock* obj_rock = new CObjRock(i, j);
				Objs::InsertObj(obj_rock, OBJ_ROCK, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}

			//木作成
			if (m_map[i][j] == MAP_WOOD)
			{
				CObjWood* obj_wood = new CObjWood(i, j);
				Objs::InsertObj(obj_wood, OBJ_WOOD, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}

			//水作成
			if (m_map[i][j] == MAP_WATER)
			{
				CObjWater* obj_water = new CObjWater(i, j);
				Objs::InsertObj(obj_water, OBJ_WATER, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}
		
			//敵作成
			if (m_map[i][j] == MAP_ENEMY)
			{
				CObjEnemy* obj_enemy = new CObjEnemy(i, j);
				Objs::InsertObj(obj_enemy, OBJ_ENEMY, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}

			//BOSS作成
			if (m_map[i][j] == MAP_ENEMY)
			{
				CObjBossEnemy* obj_boss = new CObjBossEnemy(i, j);
				Objs::InsertObj(obj_boss, OBJ_BOSS_ENEMY, 9);

				m_map[i][j] = MAP_SPACE;//生成が終わると空白を入れる
			}
		}
	}

	//オブジェクト生成おわり	-----------------------------------------------

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
}
