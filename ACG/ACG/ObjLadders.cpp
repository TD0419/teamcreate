#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "ObjLadders.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLadders::CObjLadders(int x, int y)
{
	m_px = x * LADDERS_SIZE;
	m_py = y * LADDERS_SIZE;
	m_map_x = x;
	m_map_y = y;	
}

//イニシャライズ
void CObjLadders::Init()
{
}

//アクション
void CObjLadders::Action()
{
}

//ドロー
void CObjLadders::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = LADDERS_SIZE;
	src.m_bottom = LADDERS_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + LADDERS_SIZE;
	dst.m_bottom = dst.m_top + LADDERS_SIZE;

	//描画
	Draw::Draw(5, &src, &dst, color, 0);
}

//プレイヤーがあたったときの処理
void CObjLadders::HeroHit(float px, float py)
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//主人公のオブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//プレイヤーの位置をマップの要素番号に直す
	int map_num_x = (int)((px + BLOCK_SIZE / 2) / BLOCK_SIZE);//中央を基準に調べる
	int map_num_y = (int)(py / BLOCK_SIZE);	//主人公の上端を基準で調べる
	int map_num_up = objmap->GetMap(map_num_x, map_num_y);//主人公（上半分）のマップの値を持って来る
	
	map_num_y = (int)((py) / BLOCK_SIZE) + 1;//主人公の中央を基準に調べる
	int map_num_center = objmap->GetMap(map_num_x, map_num_y);//主人公（上半分）のマップの値を持って来る	

	map_num_y = (int)((py + BLOCK_SIZE) / BLOCK_SIZE) + 1;//主人公の下端を基準に調べる
	int map_num_down = objmap->GetMap(map_num_x, map_num_y);//主人公（上半分）のマップの値を持って来る	

	//主人公がはしごを上りきる時に判定する用
	int map_num_ladder = (int)(py / BLOCK_SIZE) + 1;	//主人公の上端を基準で調べる
	int map_num_ladder_up = objmap->GetMap(map_num_x, map_num_ladder);

	//マップの値がはしごなら
	if (map_num_up == MAP_LADDERS || map_num_center == MAP_LADDERS || map_num_down == MAP_LADDERS)
	{

		objhero->SetVecY(0.0f);//yの移動方向を初期化
		objhero->SetHitDown(true);//着地状態にする
		objhero->SetLadderJump(1);//1を渡す
		//Wキーがおされたとき 上るとき
		if (Input::GetVKey('W') == true)
		{
			objhero->SetVecY(-2.0f);

			//はしごを上りきる時に2を渡す
			if (map_num_ladder_up == MAP_SPACE)
			{
				objhero->SetLaddersUpdown(2);
			}
			else
			{
				objhero->SetLaddersUpdown(1);//はしごを上っているときは1を渡す
			}
			objhero->SetLaddersAniUpdown(1);//アニメーションを進める
		}

		//Sキーがおされたとき　下るとき
		else if (Input::GetVKey('S') == true)
		{
			objhero->SetVecY(2.0f);
			objhero->SetLaddersUpdown(1);//はしごを下りるているときは1を渡す
			objhero->SetLaddersAniUpdown(1);//アニメーションを進める
		}
		//それ以外の時
		else
		{
			objhero->SetLaddersAniUpdown(0);//アニメーションを止める
		}
		
	}
	else
	{
		objhero->SetLaddersUpdown(0);//主人公がはしごに当たってないときは0を渡す
		objhero->SetLadderJump(0);//ゼロを渡す
	}
	
}