#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEnemy::CObjEnemy(int x, int y)
{
	//マップの要素数を補間
	m_map_x = x;
	m_map_y = y;
	m_px = (float)x * ENEMY_SIZE;
	m_py = (float)y * ENEMY_SIZE;
}

//イニシャライズ
void CObjEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;
	m_posture = 0.0f; //右向き1.0f 左向き0.0f

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 6; //アニメーション間隔幅

	m_speed = 0.5f;	//初期スピード

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, ENEMY_SIZE,48.0, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//アクション
void CObjEnemy::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//マップ情報を取ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//ーーーーーーーーーーー取っといてください、ステージ３くらいで使います。
	////画面内か調べる
	//m_window_check = WindowCheck(m_px, m_py, BULLET_SIZE, BULLET_SIZE);

	////画面外なら消去
	//if (m_window_check == false)
	//{
	//	this->SetStatus(false);		//自身に消去命令を出す。
	//	Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。

	//	//戻ってきたときに復活するようにする
	//	objmap->SetMapCreate(m_map_x, m_map_y, true);
	//	
	//	return;
	//}
	//－－－－－－－－－－－－－－－－－－－－－－－
	//移動----------------------------------------------

	//左に向いているなら左へ移動する
	if (m_posture == 0.0)
	{
		m_vx -= m_speed;
		m_ani_time += 1;
	}
	//右に向いているなら右へ移動する
	else
	{
		m_vx += m_speed;
		m_ani_time += 1;
	}

	//アニメーションの間隔管理
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//最後までアニメーションが進むと最初に戻る
	if (m_ani_frame == 3)
	{
		m_ani_frame = 0;
	}
	
	//摩擦
	m_vx += -(m_vx * 0.098f);

	//自由落下運動
	m_vy += 9.8f / (16.0f);

	//移動終わり-----------------------------------------

	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//弾丸とあたったら消去
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		Audio::Start(LANDING);		//敵に着弾したときの音をスタート
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//敵が所持するHitBoxを除去。
	
		return;
	}
	
	//ブロックとのあたり判定
	objblock->BlockHit(
		&m_px, &m_py, ENEMY_SIZE, ENEMY_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, 
		&m_vx, &m_vy
	);

	//右に衝突判定があったら左方向にする
	if (m_hit_left == true)
	{
		m_posture = 0.0f;
	}
	//左に衝突判定があったら右方向にするです
	if (m_hit_right == true)
	{
		m_posture = 1.0f;
	}

	//下に衝突判定がある
	if (m_hit_down == true)
	{
		//移動しようとしているところが崖なら方向転換
		//右に動いていて && 
		int block_num = objmap->GetMap( (int)m_px / ((int)BLOCK_SIZE)+1, ((int)m_py / ((int)BLOCK_SIZE))+1 );
		
		//右下にブロックが無かったら
		if (m_vx > 0.0f && block_num != MAP_BLOCK)
		{
			//方向を左にする
			m_posture = 0.0f;
		}
		//左に移動していて &&
		//左下にブロックが無かったら		↓原点調整
		block_num = objmap->GetMap( ( (int)(m_px + ENEMY_SIZE ) / ( (int)BLOCK_SIZE) )-1, ( (int)m_py / ((int)BLOCK_SIZE) )+1 );
		if (m_vx < 0.0f && block_num != MAP_BLOCK)
		{
			//方向を右にする
			m_posture = 1.0f;
		}
	}
	
	//移動ベクトルをポジションに加算
	m_px += m_vx;
	m_py += m_vy;

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py+15);	
}

//ドロー
void CObjEnemy::Draw()
{
	//画像の切り取り配列
	int AniData[3] =
	{
		0  , 1 , 2
	};

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = m_py + 6.5f - objmap->GetScrollY();
	dst.m_left = (ENEMY_SIZE * m_posture) + m_px - objmap->GetScrollX();
	dst.m_right = (ENEMY_SIZE - ENEMY_SIZE * m_posture) + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + ENEMY_SIZE;

	//描画
	Draw::Draw(GRA_ENEMY, &src, &dst, color, m_r);

}