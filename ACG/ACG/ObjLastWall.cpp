#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjLastWall.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjLastWall::CObjLastWall(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_map_x = x;
	m_map_y = y;
}

//イニシャライズ
void CObjLastWall::Init()
{
	//当たり判定																
	Hits::SetHitBox(this, m_px, m_py, 32.0f, 512.0f, ELEMENT_GIMMICK, OBJ_LAST_WALL, 1);
	
	m_wall_gauge = 0;
	m_wall_down_gauge = 0;
	m_wall_unlock_flag = false;
	m_wall_down_flag = false;
	m_hero_hit_flag = false;

	switch (((UserData*)Save::GetData())->stagenum)
	{
		//ステージ１
	case 1:
		m_wall_type = 1;
		break;
		//ステージ２
	case 2:
		m_wall_type = 2;
		break;
		//ステージ３
	case 3:
		m_wall_type = 3;
		break;
		
	default:
		break;
	}
}

//アクション
void CObjLastWall::Action()
{
	//HitBoxの位置の変更
	//引数で持ってきたオブジェクトとあたっているか調べる
	CHitBox* hit = Hits::GetHitBox(this);

	//主人公オブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//敵オブジェクと持ってくる
	CObjEnemy*objenemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
	//BOSSオブジェクトと持ってくる
	CObjBoss*objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);
	//BOSSオブジェクトと持ってくる
	CObjStage5Boss*objstage5boss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HIT_DATA** hit_data;		//主人公の衝突の情報を入れる構造体
		hit_data = hit->SearchObjNameHit(OBJ_HERO);//主人公の衝突の情報をhit_dataに入れる
		for (int i=0;i < hit->GetCount();i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r=0.0f;
				
				r =hit_data[i]->r;
				//主人公が右側に衝突
				if (0.0f < r && r < 85.0f || 275.0f < r && r < 360.0f)
				{
					//壁にめりこまないようにする処理
					if (objhero->GetPosture() == 0.0f)//右向き
					{
						objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
						objhero->SetPosX(m_px + 61.0f);//主人公の位置をLastWallの右側までずらす
					}
					else//左向き
					{
						objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
						objhero->SetPosX(m_px + 47.0f);//主人公の位置をLastWallの右側までずらす
					}
				}

				//LastWallの上側が衝突している場合
				else if (85.0f < r && r < 94.0f)
				{
					objhero->SetVecY(0.0f);//主人公のY方向の移動を０にする
					objhero->SetPosY(m_py - 60.0f);//主人公の位置をLastWallの上側までずらす
				}

				//LastWallの左側が衝突している場合
				else if (94.0f < r && r < 266.0f)
				{
					//壁にめりこまないようにする処理
					if (objhero->GetPosture() == 0.0f)//右向き
					{
						objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
						objhero->SetPosX(m_px - 63.0f + 42.0f);//主人公の位置をLastWallの左側までずらす
					}
					else//左向き
					{
						objhero->SetVecX(0.0f);//主人公のX方向の移動を０にする
						objhero->SetPosX(m_px - 63.0f + 28.0f);//主人公の位置をLastWallの左側までずらす
					}
					
					m_hero_hit_flag = true;
				}

				//LastWallの下側が衝突している場合
				else if (266.0f < r && r < 275.0f)
				{
					objhero->SetVecY(0.0f);//主人公のY方向の移動を０にする
					objhero->SetPosY(m_py + 512.0f - m_wall_gauge +65.0f);//主人公の位置をLastWallの下側までずらす
				}
			}
		}
	}
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		HIT_DATA** hit_data_enemy;	//敵の衝突の情報を入れる構造体
		hit_data_enemy = hit->SearchObjNameHit(OBJ_ENEMY);//敵の衝突の情報をhit_dataに入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data_enemy[i] != nullptr)
			{
				float r = 0.0f;
				r = hit_data_enemy[i]->r;

				//LastWallの右側が衝突している場合
				if (0.0f < r && r < 85.0f || 275.0f < r && r < 360.0f)
				{
					objenemy->SetVecX(2.0f);//敵のX方向の移動を2にする
					objenemy->SetPosture(1.0f);//向き変更
				}
				else if (94.0f < r && r < 266.0f)
				{
					objenemy->SetVecX(-2.0f);//敵のX方向の移動を-2にする
					objenemy->SetPosture(0.0f);//向き変更
				}
			}
		}
	}
	if (hit->CheckObjNameHit(OBJ_BOSS) != nullptr)
	{
		HIT_DATA** hit_data_boss;	//敵の衝突の情報を入れる構造体
		hit_data_boss = hit->SearchObjNameHit(OBJ_BOSS);//敵の衝突の情報をhit_dataに入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data_boss[i] != nullptr)
			{
				float r = 0.0f;
				r = hit_data_boss[i]->r;
				//LastWallの右側が衝突している場合
				if (0.0f < r && r < 85.0f || 275.0f < r && r < 360.0f)
				{
					objboss->SetVecX(2.0f);//BOSSのX方向の移動を2にする
					objboss->SetPosture(0.0f);//BOSS向き変更
				}
				//LastWallの左側が衝突している場合
				else if (94.0f < r && r < 266.0f)
				{
					objboss->SetPosX(m_px-BOSS_SIZE_WIDTH);//ボスの位置を壁の左側にずらす。
					objboss->SetHitF(true);//投擲のフラグを立てる
				}
			}
		}
	}

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	int map_num = objmap->GetMap(m_map_x, m_map_y);

	// m_wall_gaugeが512を越えたら処理ストップ
	if (m_wall_gauge >= 512)
	{
		// 主人公が壁の右側にいないと壁がしまらないようにする
		if (objhero->GetPosX() > m_px + BLOCK_SIZE)
		{
			//主人公が右側にいったので、壁が下がるフラグをtrueにする
			m_wall_down_flag = true;

			//壁のゲージを0にする
			m_wall_gauge = 0;
		}
				
		Audio::Stop(WALL);//音楽ストップ
	}
	else
	{
		//heroが左側に振れてたら
		if (m_hero_hit_flag == true && m_wall_down_flag == false)
		{
			m_wall_gauge += 3; // 3ずつ増やしていく
			Audio::Start(WALL);//開門の音楽スタート
		}
	}

	//壁のしまるフラグがfalseのとき
	if (m_wall_down_flag == false)
	{
		// 壁のhitboxを小さくする
		HitBoxUpData(hit, m_px, m_py + m_wall_gauge, 32.0f, 512.0f - m_wall_gauge);
	}

	// ボスが出てきたら強制的に閉める処理
	if (objboss != nullptr || objenemy != nullptr||objstage5boss!=nullptr)
	{
		m_wall_down_flag = true;//切り替えフラグオン
		m_wall_gauge = 0;		//wall初期化
		Audio::Stop(WALL);		//音楽ストップ
	}

	//壁がしまった時
	if (m_wall_down_gauge >= 512)
	{
		Audio::Stop(WALL);//音楽ストップ
		m_wall_unlock_flag = false;
	}
	//壁が開いているとき
	else
	{
		//壁が下がるフラグオン
		if (m_wall_down_flag == true)
		{
			m_wall_down_gauge += 512;	//一番下まで下がる
			Audio::Start(WALL);		//開門の音楽スタート

			//hitboxが小さくなる
			HitBoxUpData(hit, m_px, m_py + m_wall_gauge, 32.0f,(float) m_wall_down_gauge);
		}
	}

	//HitBoxの位置を更新する
	HitBoxUpData(hit, m_px+29.0f, m_py+65.0f);
}

//ドロー
void CObjLastWall::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 256.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY() - 190.0f;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + 96.0f;
	dst.m_bottom = dst.m_top + 256.0f;

	//描画(上の部分)
	Draw::Draw(GRA_LAST_WALL, &src, &dst, color, 0.0f);

	//切り取り位置
	src.m_top = (float)m_wall_gauge;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 512.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY() + 65.0f;
	dst.m_left = m_px - objmap->GetScrollX() + 30.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 512.0f - (float)m_wall_gauge;

	//描画(下の部分)
	Draw::Draw(GRA_OPEN_WALL, &src, &dst, color, 0.0f);

	//-----------------------------------------------------
}