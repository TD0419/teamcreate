#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBoss::CObjBoss(int x,int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjBoss::Init()
{
    m_vx = -1.0f; // 移動ベクトル
    m_vy = 0.0f;
	m_hp = 20; //ボスのＨＰ
	m_posture = 1.0f; // 左向き
	m_speed = 1.0f;   // 速度

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 3; //アニメーション間隔幅
	
	// blockとの衝突確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_die_flag = false;
	 //当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_BOSS, 1);
}

//アクション
void CObjBoss::Action()
{
	m_ani_time++;//アニメーションは遊びなので消してもらってもおｋです
	//アニメーションの感覚管理
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//最後までアニメーションが進むと最初にいく
	if (m_ani_frame == 8)
	{
		m_ani_frame = 0;
	}
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);
	
	if (m_posture == 0.0f)		// 右向きなら
		m_vx = m_speed;			// 右に進む
	else if (m_posture == 1.0f) // 左向きなら
		m_vx = -m_speed;		// 左に進む

	//摩擦
	m_vx += -(m_vx * 0.098f);

	//自由落下運動
	m_vy += 9.8f / (16.0f);

	//移動ベクトルをポジションに加算
	m_px += m_vx;
	m_py += m_vy;
	
	//ブロックとの当たり判定実行
	CObjBlock* objblock = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	objblock-> BlockHit(&m_px,&m_py,BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT,
	&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy
	);
	
	if (m_hit_right == true)    // ブロックの右側に当たっていたら 
		m_posture = 0.0f;		// 右向きにする
	else if (m_hit_left == true)// ブロックの左側に当たっていたら
		m_posture = 1.0f;		// 左向きにする

	CObjDoor* objdoor = (CObjDoor*)Objs::GetObj(OBJ_DOOR);
	//弾丸とあたったらHP-1
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	// 体力が0以下なら
	if (m_hp <= 0)
	{
		m_die_flag = true;
		Hits::DeleteHitBox(this);	//BOSSが所有するHitBoxに削除する
		this->SetStatus(false);		//自身に削除命令を出す
		return;
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjBoss::Draw()
{
	//画像の切り取り配列
	
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置(	いらん奴)
	src.m_top = 0.0f;
	src.m_left = m_ani_frame * 128.0-128.0;
	src.m_right = src.m_left+128.0f;
	src.m_bottom = src.m_top + 128.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = BOSS_SIZE_WIDTH * m_posture + m_px - objmap->GetScrollX();
	dst.m_right = (BOSS_SIZE_WIDTH - BOSS_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top  + BOSS_SIZE_HEIGHT+6;

	////描画
	/*Draw::Draw(14, &src, &dst, color, 0.0f);*/
	Draw::Draw(4, &src, &dst, color, 0.0f);

}