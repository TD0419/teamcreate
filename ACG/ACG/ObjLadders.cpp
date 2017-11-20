#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameHead.h"
#include "ObjLadders.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLadders::CObjLadders(int x, int y,bool look)
{
	m_px = x * LADDERS_SIZE;
	m_py = y * LADDERS_SIZE;
	m_map_x = x;
	m_map_y = y;	
	m_obj_look_f = look;		//ハシゴが見えるかどうか false:見えない true:見える
}

//イニシャライズ
void CObjLadders::Init()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//左右のマップ数値を持ってくる
	int map_left_side  = objmap->GetMap(m_map_x - 1, m_map_y);
	int map_right_side = objmap->GetMap(m_map_x + 1, m_map_y);

	//左右にブロックがあれば
	if (map_left_side == MAP_BLOCK || map_right_side == MAP_BLOCK)
		m_side_block_flag = true;
	else
		m_side_block_flag = false;

	m_up_and_down_speed = 6.0f;//ハシゴ上り下り時の速度
}

//アクション
void CObjLadders::Action()
{
	// ボタンオブジェクトを持ってくる
	CObjButton* objbutton = (CObjButton*)Objs::GetObj(OBJ_BUTTON);

		// ボタンを押していたら
	if (objbutton != nullptr && objbutton->GetTrickFlag() == true)
		m_obj_look_f = true;			   // はしごが見えるようにする
}

//ドロー
void CObjLadders::Draw()
{
	// 見える状態なら描画する
	if (m_obj_look_f == true)
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

		//サイドにブロックがあれば
		if (m_side_block_flag == true)
			Draw::Draw(GRA_BLOCK, &src, &dst, color, 0);//ブロックの描画

		//ハシゴの描画
		Draw::Draw(GRA_LADDERS, &src, &dst, color, 0);
	}
}

//プレイヤーがあたったときの処理
void CObjLadders::HeroHit(float px, float py)
{
	// 見える状態なら判定をする
	if (m_obj_look_f == true)
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
		if (map_num_up == MAP_LADDERS || map_num_center == MAP_LADDERS || map_num_down == MAP_LADDERS ||
			map_num_up == MAP_NO_LOOK_LADDERS || map_num_center == MAP_NO_LOOK_LADDERS || map_num_down == MAP_NO_LOOK_LADDERS)
		{
			//Wキーがおされたとき 上るとき
			if (Input::GetVKey('W') == true)
			{
				// はしごに掴まっていない(アニメーション中ではない) 調整の余地あり
				if (objhero->GetLadderUpdown() == 0 && map_num_center != MAP_LADDERS && map_num_center != MAP_NO_LOOK_LADDERS)
				{
					objhero->SetVecY(0.0f);				// 下に落ちないようにする
					objhero->SetGravityFlag(false);		// 重力がかからないようにする
					objhero->SetHitDown(true);			// 着地フラグを立てジャンプできるようにする
				}
				else
				{
					objhero->SetVecY(-m_up_and_down_speed);//上方向への移動ベクトルをセットする
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
			}
			//Sキーがおされたとき　下るとき
			else if (Input::GetVKey('S') == true)
			{
				//下に通常ブロックが無かったら
				if (objhero->GetBlockType() != MAP_BLOCK)
				{
					objhero->SetVecY(m_up_and_down_speed);//下方向への移動ベクトルをセットする
					objhero->SetLaddersUpdown(1);//はしごを下りるているときは1を渡す
					objhero->SetLaddersAniUpdown(1);//アニメーションを進める
				}
				else
				{
					objhero->SetLaddersUpdown(0);//主人公がはしごを下り終えたらアニメーション終了
				}
			}
			//それ以外の時
			else
			{
				// はしごにつかまっていない場合(はしごを上るアニメーション中ではない)
				if (objhero->GetLadderUpdown() == 0)
				{
					// 一番下にしかはしごがなかったらブロックのように落ちないようにする(一応動いているが判定の仕方に問題あり)
					if(map_num_down == MAP_LADDERS && map_num_up != MAP_LADDERS && map_num_center != MAP_LADDERS ||
						map_num_down == MAP_NO_LOOK_LADDERS && map_num_up != MAP_NO_LOOK_LADDERS && map_num_center != MAP_NO_LOOK_LADDERS)
					{
      					objhero->SetVecY(0.0f);			// 下に落ちないようにする	
						objhero->SetGravityFlag(false); // 重力がかからないようにする
    					objhero->SetHitDown(true);		// 着地フラグを立てジャンプできるようにする
					}
					// それ以外ならはしごに当たってもすり抜けるようにする
					else
					{
						objhero->SetGravityFlag(true);	// はしごにつかまっていない時は重力がかかるようにする
					}
				}
				// はしごに掴まっている場合(はしごを上るアニメーション中)
				else
				{
					objhero->SetVecY(0.0f);			// 下に落ちないようにする	
					objhero->SetGravityFlag(false);	// 重力がかからないようにする
				}
					
				objhero->SetLaddersAniUpdown(0);//アニメーションを止める
			}
		}
		else
		{
			objhero->SetGravityFlag(true); // はしごに当たっていないときは重力がかかるようにする
			objhero->SetLaddersUpdown(0);//主人公がはしごに当たってないときは0を渡す
		}
	}
	
}

