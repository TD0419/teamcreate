#include "GameHead.h"
#include "ObjMap.h"

//使用するネームスペース
using namespace GameL;


//コンストラクタ
CObjMap::CObjMap(int map[MAP_Y_MAX][MAP_X_MAX], int remaining)
{
	//マップデータをコピー
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			m_map[i][j].num = map[i][j];//数値のコピー
		}
	}
	m_remaining = remaining; // 残機数情報を入れる
}

//イニシャライズ
void CObjMap::Init()
{
	m_scroll_x = 0.0f;
	
	for (int y = 0; y < MAP_Y_MAX; y++)
	{
		for (int x = 0; x < MAP_X_MAX; x++)
		{
			// 主人公のマップ位置から初期のスクロール値を決める
			if (m_map[y][x].num == MAP_HERO_START)
			{
				m_scroll_y = (float)y * BLOCK_SIZE;
			}
			m_map[y][x].create = true; //フラグの初期化
		}
	}
}

//アクション
void CObjMap::Action()
{
	// 一定のスクロール値を超えないようする
	if (m_scroll_y > WINDOW_SIZE_H)
		m_scroll_y = WINDOW_SIZE_H;

	//マップを元にオブジェクトを生成--------------------------------------
	
	//yが　画面に収まる最大値　または　マップの最大値になるまでまわす
	for (int y = 0; y < MAP_WINDOW_MAX_Y && y<MAP_Y_MAX; y++)
	{
		//xが　画面に収まる最大値　または　マップの最大値になるまでまわす
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
//引数1	scroll_block_num_x:	X軸の現在のスクロール量がブロック何個分か
//引数2	scroll_block_num_y:	Y軸の現在のスクロール量がブロック何個分か
// *この関数内のコメントのスクロール量はすべて引数で渡ってきたブロック数で換算した物のことを指す
void CObjMap::ScrollCreateObj(int scroll_block_num_x, int scroll_block_num_y)
{
	//yの値がスクロール量Y　から　ウィンドウ内に収まる最大値＋スクロール量Y　または　マップの最大値　に達するまで回す
	for (int y = scroll_block_num_y ; y < MAP_Y_MAX && y <= scroll_block_num_y + MAP_WINDOW_MAX_Y; y++)
	{
		//xの値がスクロール量X　から　マップの最大値　または　ウィンドウ内に収まる最大値＋スクロール量X　　に達するまで回す
		for (int x = scroll_block_num_x;
			x < MAP_X_MAX && x <= scroll_block_num_x + MAP_WINDOW_MAX_X ; x++)
		{			
			//マップの範囲ないなら
			if ((x >= 0 && x < MAP_X_MAX))
			{
				if (y >= 0 && y < MAP_Y_MAX)
				{

					CreateObj(x, y);//オブジェクトを生成
				}
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
		// プランナーからマップが届いたらコメントをはずす
		
	
		case MAP_HERO_START:	//ヒーローの作成
		{

			//主人公オブジェクトを作成する
			CObjHero* objhero = new CObjHero(x, y, m_remaining);
			Objs::InsertObj(objhero, OBJ_HERO, 10);
			break;
		}
		
		case MAP_BLOCK:		//ブロック作成
		{
			CObjBlock* objblock = new CObjBlock(x, y);
			Objs::InsertObj(objblock, OBJ_BLOCK, 9);
			break;
		}
		
		case MAP_LADDERS:	//はしご作成
		{
			CObjLadders* objladders = new CObjLadders(x, y, true);
			Objs::InsertObj(objladders, OBJ_LADDERS, 9);
			break;
		}
		
		case MAP_ROPE_SWITCH:	//ロープスイッチ作成
		{
			CObjRopeSwitch* objrope_switch = new CObjRopeSwitch(x, y);
			Objs::InsertObj(objrope_switch, OBJ_ROPE_SWITCH, 9);
			break;
		}

		case MAP_LEVER_SWICH:	//レバースイッチ作成
		{
			CObjLeverSwich* objLeverSwich = new CObjLeverSwich(x, y);
			Objs::InsertObj(objLeverSwich, OBJ_LEVER_SWICH, 9);
			break;
		}

		case MAP_ROCK:		//岩作成
		{
			CObjRock* objrock = new CObjRock(x, y);
			Objs::InsertObj(objrock, OBJ_ROCK, 9);
			break;
		}

		case MAP_SIGN:	//看板作成
		{
			CObjSign* objsign = new CObjSign(x, y);
			Objs::InsertObj(objsign, OBJ_SIGN, 9);
			break;
		}

		case MAP_GOAL_DOOR:	//ゴール用ドア作成
		{
			CObjDoor* objDoor = new CObjDoor(x, y);
			Objs::InsertObj(objDoor, OBJ_DOOR, 9);
			break;
		}
		
		case MAP_LIFT_TYPE_AUTO_WIDTH:		//自動横移動リフト作成
		{
			CObjLift* objlift = new CObjLift(x, y,0,300.0f,1);
			Objs::InsertObj(objlift, OBJ_LIFT, 9);
			break;
		}

		case MAP_LIFT_TYPE_AUTO_LENGTH:		//自動縦移動リフト作成
		{
			CObjLift* objlift = new CObjLift(x, y,3);
			Objs::InsertObj(objlift, OBJ_LIFT, 9);
			break;
		}
		
		case MAP_ENEMY://敵作成
		{
			CObjEnemy* objenemy = new CObjEnemy(x, y);
			Objs::InsertObj(objenemy, OBJ_ENEMY, 10);
			break;
		}

		case MAP_LAST_WALL:		//壁(次ステージを隔てる壁)
		{
			CObjLastWall* objLastWall = new CObjLastWall(x, y);
			Objs::InsertObj(objLastWall, OBJ_LAST_WALL, 10);
			break;
		}
	
		case MAP_WOOD:	//木作成
		{
			CObjWood* objwood = new CObjWood(x, y);
			Objs::InsertObj(objwood, OBJ_WOOD, 9);
			break;
		}

		case MAP_NO_LOOK_LADDERS: // 見えないハシゴ作成
		{
			CObjLadders* objladders = new CObjLadders(x, y, false);
			Objs::InsertObj(objladders, OBJ_LADDERS, 9);
			break;
		}

		case MAP_BUTTON:	//ボタン作成
		{
			CObjButton* objbutton = new CObjButton(x, y);
			Objs::InsertObj(objbutton, OBJ_BUTTON, 9);
			break;
		}

		case MAP_WATER: //水作成
		{
			CObjWater* objwater = new CObjWater(x, y);
			Objs::InsertObj(objwater, OBJ_WATER, 8);
			break;
		}

		case MAP_THROUGH_BLOCK://スルーブロック作成
		{
			CObjThroughBlock* objthrough_block = new CObjThroughBlock(x, y);
			Objs::InsertObj(objthrough_block, OBJ_THROUGHT_BLOCK, 9);
			break;
		}

		case MAP_BOSS://ボス作成
		{
			CObjBoss* objboss = new CObjBoss(x, y);
			Objs::InsertObj(objboss, OBJ_BOSS, 9);
			break;
		}

		case MAP_REFLECT_BLOCK:	//反射用ブロック作成
		{
			CObjReflectBlock* objreflec_block = new CObjReflectBlock(x, y);
			Objs::InsertObj(objreflec_block, OBJ_REFLECT_BLOCK, 9);
			break;
		}

		case MAP_ROLL_BLOCK_TYPE_AUTO://回転ブロック（自動回転）作成
		{
			CObjRollBlock* objrollblock = new CObjRollBlock(x, y,1);
			Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 9);
			break;
		}
		
		case MAP_ROLL_BLOCK_TYPE_MANUAL://回転ブロック（手動）作成
		{
			CObjRollBlock* objrollblock = new CObjRollBlock(x, y, 2);
			Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 9);
			break;
		}

		case MAP_STAGE3_BOSS:		//第三ボス作成
		{
			CObjStage3Boss* objstage3_boss = new CObjStage3Boss(x, y);
			Objs::InsertObj(objstage3_boss, OBJ_STAGE3_BOSS, 9);
			break;
		}

		case MAP_CANNON:		//砲台
		{
			CObjCannon* objcannon = new CObjCannon(x, y);
			Objs::InsertObj(objcannon, OBJ_CANNON, 9);
			break;
		}

		case MAP_TARZAN_POINT://ロープでぶら下がれるギミック
		{
			CObjTarzanPoint* objtarzanpoint = new CObjTarzanPoint(x, y);
			Objs::InsertObj(objtarzanpoint, OBJ_TARZAN_POINT, 9);
			break;

		}
		/*
		実装されたら、コメント化を外してください。
		case MAP_LIFT_TYPE_AUTO_UP:
		{
			break;
		}
		*/
		case MAP_FALLING_BLOCK://ステージ5ボス戦専用落ちるブロック
		{
			CObjFallingBlock* objfalling_block = new CObjFallingBlock(x,y);
			Objs::InsertObj(objfalling_block, OBJ_FALLING_BLOCK,9);
			break;
		}

		case MAP_STAGE5_BOSS://ステージ5ボス(本体)
		{
			CObjStage5Boss* objstage5_boss = new CObjStage5Boss(x,y);
			Objs::InsertObj(objstage5_boss, OBJ_STAGE5_BOSS ,9);
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

