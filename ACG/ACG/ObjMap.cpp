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
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			m_map[i][j].num = map[i][j];//数値のコピー
		}
	}
}

//イニシャライズ
void CObjMap::Init()
{
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;

	//フラグの初期化
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			m_map[i][j].create = true;
		}
	}

}

//アクション
void CObjMap::Action()
{
	//マップを元にオブジェクトを生成--------------------------------------
	
	//iが　画面に収まる最大値　または　マップの最大値になるまでまわす
	for (int y = 0; y < MAP_WINDOW_MAX_Y && y<MAP_Y_MAX; y++)
	{
		//jが　画面に収まる最大値　または　マップの最大値になるまでまわす
		for (int x = 0; x < MAP_WINDOW_MAX_X && x<MAP_X_MAX;x++)
		{
			CreateObj(x, y);//オブジェクトの生成	
		}
	}

	//オブジェクト生成おわり	-----------------------------------------------

	//スクロール量(ブロックの数に計算して渡す)をもとにオブジェクトを生成する
	ScrollCreateObj(int(m_scroll_x / BLOCK_SIZE), int(m_scroll_y / BLOCK_SIZE));	
}

//ドロー
void CObjMap::Draw()
{
}

//スクロール量をもとにオブジェクトの生成をする関数
//	scroll_block_num_x:	X軸の現在のスクロール量がブロック何個分か
//	scroll_block_num_y:	Y軸の現在のスクロール量がブロック何個分か
// *この関数内のコメントのスクロール量はすべて引数で渡ってきたブロック数で換算した物のことを指す
void CObjMap::ScrollCreateObj(int scroll_block_num_x, int scroll_block_num_y)
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
				//マップの範囲ないなら
				if(x >= 0 && y >= 0 && x < MAP_X_MAX && y < MAP_Y_MAX)
						CreateObj(x, y);//オブジェクトを生成
			}
		}
	}
}

//オブジェクトの生成を行う関数
//引数1　マップの要素数X
//引数2　マップの要素数Y
void CObjMap::CreateObj(int x, int y)
{
	//フラグがオフなら 抜ける
	if (m_map[y][x].create == false)	return;
	
	switch (m_map[y][x].num)
	{
		case MAP_BLOCK:		//ブロック作成
		{
			CObjBlock* objblock = new CObjBlock(x, y);
			Objs::InsertObj(objblock, OBJ_BLOCK, 9);
			break;
		}
		
		case MAP_LADDERS:	//はしご作成
		{
			CObjLadders* objladders = new CObjLadders(x, y);
			Objs::InsertObj(objladders, OBJ_LADDERS, 9);
			break;
		}
		
		case MAP_BUTTON:	//ボタン作成
		{
			CObjButton* objbutton = new CObjButton(x, y);
			Objs::InsertObj(objbutton, OBJ_BUTTON, 9);
			break;
		}
		
		case MAP_ROPE_SWITCH:	//ロープスイッチ作成
		{
			CObjRopeSwitch* objrope_switch = new CObjRopeSwitch(x, y);
			Objs::InsertObj(objrope_switch, OBJ_ROPE_SWITCH, 9);
			break;
		}

		case MAP_LIFT:		//リフト作成
		{
			CObjLiftMove* objlift = new CObjLiftMove(x, y);
			Objs::InsertObj(objlift, OBJ_LIFT_MOVE, 9);
			break;
		}
		
		case MAP_ROCK:		//岩作成
		{
			CObjRock* objrock = new CObjRock(x, y);
			Objs::InsertObj(objrock, OBJ_ROCK, 9);
			break;
		}
	
		case MAP_WOOD:	//木作成
		{
			CObjWood* objwood = new CObjWood(x, y);
			Objs::InsertObj(objwood, OBJ_WOOD, 9);
			break;
		}

		case MAP_WATER: //水作成
		{
			CObjWater* objwater = new CObjWater(x, y);
			Objs::InsertObj(objwater, OBJ_WATER, 9);
			break;
		}

		case MAP_ENEMY://敵作成
		{
			CObjEnemy* objenemy = new CObjEnemy(x, y);
			Objs::InsertObj(objenemy, OBJ_ENEMY, 9);
			break;
		}

		case MAP_BOSS://ボス作成
		{
			CObjBoss* objboss = new CObjBoss(x, y);
			Objs::InsertObj(objboss, OBJ_BOSS, 9);
			break;
		}
		
		case MAP_STAGE3_BOSS:		//第三ボス作成
		{
			CObjStage3Boss* objstage3_boss = new CObjStage3Boss(x, y);
			Objs::InsertObj(objstage3_boss, OBJ_STAGE3_BOSS, 9);
			break;
		}

		case MAP_THROUGH_BLOCK://スルーブロック作成
		{
			CObjThroughBlock* objthrough_block = new CObjThroughBlock(x, y);
			Objs::InsertObj(objthrough_block, OBJ_THROUGHT_BLOCK, 9);
			break;
		}

		case MAP_REFLECT_BLOCK:	//反射用ブロック作成
		{
			CObjReflectBlock* objreflec_block = new CObjReflectBlock(x, y);
			Objs::InsertObj(objreflec_block, OBJ_REFLECT_BLOCK, 9);
			break;
		}
		
		case MAP_SIGN :	//看板作成
		{
			CObjSign* objsign = new CObjSign(x, y);
			Objs::InsertObj(objsign, OBJ_SIGN, 9);
			break;
		}
		
		case MAP_DOOR:	//ドア作成
		{
			CObjDoor* objDoor = new CObjDoor(x, y);
			Objs::InsertObj(objDoor, OBJ_DOOR, 9);
			break;
		}

		case MAP_LEVER_SWICH:	//レバースイッチ作成
		{
			CObjLeverSwich* objLeverSwich = new CObjLeverSwich(x, y);
			Objs::InsertObj(objLeverSwich, OBJ_LEVER_SWICH, 19);
			break;
		}
	}

	m_map[y][x].create = false;//フラグをオフにする	
}

//調べたいマップの位置にあるマップ番号を返す
int CObjMap::GetMap(int x, int y)
{
	if (0 <= y && y < MAP_Y_MAX && 0 <= x && x < MAP_X_MAX)

		return m_map[y][x].num;

	return -99999;//無かった場合
}

