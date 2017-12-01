#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBoss::CObjBoss(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjBoss::Init()
{
	m_vx = -1.0f;		// 移動ベクトル
	m_hp = 20;			//ボスのＨＰ
	m_posture = 1.0f;	// 左向き
	m_speed = 3.0f;		// 速度

	m_ani_time_walk = 0;
	m_ani_time_throw = 0;

	m_ani_frame_walk = 1;		//静止フレームを初期にする(歩くモーション)
	m_ani_frame_throw = 1;		//静止フレームを初期にする(投げるモーション)
	m_ani_walk_max_time = 10;	//歩くアニメーション間隔幅
	m_ani_throw_max_time = 5;	//投げるアニメーション間隔幅

	m_ani_throw_start_flag = false;//投げるアニメーション開始フラグ false=オフ ture=オン

	m_wall_hit_flag = false;
	// blockとの衝突確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py+100.0f, 150.0f, 150.0f, ELEMENT_ENEMY, OBJ_BOSS, 1);

	Audio::Stop(STAGE);
	Audio::Start(BOSS);
	
}

//アクション
void CObjBoss::Action()
{

	m_ani_time_walk++;
	m_ani_time_throw++;

	//歩くアニメーションの間隔管理(投げるアニメーションフラグがＯＦＦのとき)
	if (m_ani_throw_start_flag == false && (m_ani_time_walk > m_ani_walk_max_time))
	{
		m_ani_frame_walk += 1;
		m_ani_time_walk = 0;
	}
	//投げるアニメーションの間隔管理(投げるアニメーションフラグがＯＮのとき)
	else if (m_ani_throw_start_flag == true && (m_ani_time_throw > m_ani_throw_max_time))
	{
		m_ani_frame_throw += 1;
		m_ani_time_throw = 0;
	}

	//(歩くアニメーション)最後までアニメーションが進むと最初にいく
	if (m_ani_frame_walk == 10)
	{
		m_ani_frame_walk = 1;
	}

	//(アニメーション)最後までアニメーションが進むと最初にいく
	if (m_ani_frame_throw == 4)
	{
		m_ani_throw_start_flag = false;
		m_ani_frame_throw = 1;
		
	}
	
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	if (m_posture == 0.0f)		// 右向きなら
		m_vx = m_speed;			// 右に進む
	else if (m_posture == 1.0f) // 左向きなら
		m_vx = -m_speed;		// 左に進む
	
	//摩擦
	m_vx += -(m_vx * 0.098f);

	////移動先ががけなら反転させる------------------------------

	//CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	////ゴリラの左下にあたるブロックの位置
	//float x = (m_px + m_vx) / BLOCK_SIZE;
	//float y = (m_py + BOSS_SIZE_HEIGHT )/ BLOCK_SIZE;

	////1マス下のブロックを調べる
	//int block_num = objmap->GetMap((int)x,(int)y+1);
	//
	//if (block_num==MAP_SPACE)

	////-------------------------------------------------------


	//ブロックとの当たり判定実行
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	objblock->BlockHit(&m_px, &m_py, BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
	);

	if (m_hit_down == false)//下にブロックがなければ
		m_posture = 1.0f;//左向きにする
	

	if (m_hit_right == true)    // ブロックの右側に当たっていたら 
	{
		m_posture = 0.0f;		// 右向きにする

		//投げモーション中でなければ（多重生成を防ぐ）
		if (m_ani_throw_start_flag == false)
		{
			//音楽スタート
			Audio::Start(GORILLATHROW);

			// 敵弾丸作成
			CObjEnemyBullet* objenemy = new CObjEnemyBullet(m_px, m_py, 0.0f);
			Objs::InsertObj(objenemy, OBJ_ENEMY_BULLET, 10);
			
			//投げるアニメーション開始フラグをＯＮにする
			m_ani_throw_start_flag = true;
		}
	}
	else if (m_hit_left == true||m_wall_hit_flag==true)// ブロックの左側に当たっていたら
	{
		//右向きの時に
		if (m_posture == 0.0f)
		{
			m_posture = 1.0f;//左向きにする
			
			//投げモーション中でなければ（多重生成を防ぐ）
			if (m_ani_throw_start_flag == false)
			{
				//音楽スタート
				Audio::Start(GORILLATHROW);

				// 敵弾丸作成
				CObjEnemyBullet* objenemy = new CObjEnemyBullet(m_px, m_py, 0.0f);
				Objs::InsertObj(objenemy, OBJ_ENEMY_BULLET, 10);

				//壁ヒットフラグをfalseにする。
				m_wall_hit_flag = false;

				//投げるアニメーション開始フラグをＯＮにする
				m_ani_throw_start_flag = true;
			}
		}
	}

	CObjDoor* objdoor = (CObjDoor*)Objs::GetObj(OBJ_DOOR);
	
	//弾丸とあたったらHP-1
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		Audio::Start(LANDING);
		m_hp -= 1;
	}

	// 体力が0以下なら
	if (m_hp <= 0)
	{
		Hits::DeleteHitBox(this);	//BOSSが所有するHitBoxに削除する
		this->SetStatus(false);		//自身に削除命令を出す
		return;
	}

	if (m_posture == 1.0f)
	{
		//HitBoxの位置を更新する
		HitBoxUpData(Hits::GetHitBox(this), m_px + 30.0f, m_py + 100.0f);
	}
	else
	{
		//HitBoxの位置を更新する
		HitBoxUpData(Hits::GetHitBox(this), m_px + 20.0f, m_py + 100.0f);
	}
}

//ドロー
void CObjBoss::Draw()
{
	
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	//歩くアニメーション
	if (m_ani_throw_start_flag == false)
	{
		src.m_top = 0.0f;
		src.m_left = m_ani_frame_walk * 96.0f - 96.0f;
		src.m_right = src.m_left + 96.0f;
		src.m_bottom = src.m_top + 72.0f;
	}
	//投げるアニメーション
	else if (m_ani_throw_start_flag == true)
	{
		src.m_top = 82.0f;
		src.m_left = m_ani_frame_throw * 96.0f - 96.0f;
		src.m_right = src.m_left + 96.0f;
		src.m_bottom = src.m_top + 72.0f;
	}

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = BOSS_SIZE_WIDTH * m_posture + m_px - objmap->GetScrollX();
	dst.m_right = (BOSS_SIZE_WIDTH - BOSS_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + BOSS_SIZE_HEIGHT + 2;

	//描画
	Draw::Draw(GRA_BOSS, &src, &dst, color, 0.0f);

}