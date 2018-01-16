//使用するヘッダーファイル
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjFallingBlock.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjFallingBlock::CObjFallingBlock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
	m_return_block_y = m_py;
}

//イニシャライズ
void CObjFallingBlock::Init()
{
	m_falling_time = 10;			//ブロックが落ちるまでの時間
	m_fallint_start_flag = false;	//true…落とす  false…落とさない
	m_screen_out = false;			//ブロックが画面外に出ているかを調べる

	m_screen_out = false;		//ブロックが画面外に出ているかを調べる

	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, FALLING_BLOCK_SIZE_WIDTH, BLOCK_SIZE, ELEMENT_GIMMICK, OBJ_FALLING_BLOCK, 1);
}

//アクション
void CObjFallingBlock::Action()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBoxのポインタを持ってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//マップの外側までいけば
	if (m_py > BLOCK_SIZE * MAP_Y_MAX)
	{
		Audio::Stop(GROUND);
		m_screen_out = true;//画面外にブロックが出ている
	}
	else
	{
		m_screen_out = false;//画面外にブロックが出ていない
	}

	//ステージ3ボスのオブジェクトの取得
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	bool stage5boss_atk4_count = false;//ステージ5ボスの攻撃４用カウンターの情報取得用
	bool stage5boss_death_flag = false;//ステージ5ボスの死亡フラグの情報取得用

	if (objboss != nullptr)//ボスオブジェクトがあれば
	{
		//ステージ3ボスの死亡フラグの情報を取得する
		stage5boss_death_flag = objboss->GetBossDeathFlag();
		
		//ブロックを初期位置に戻すためのフラグ
		stage5boss_atk4_count = objboss->GetBlockRetuenFlag();

		//落下させるかのフラグを更新
		m_fallint_start_flag = objboss->GetBlockDownFlag();
	}
	
	//ボスの攻撃4のカウンターが300フレーム経過したら、ブロックを初期位置に戻す
	if (stage5boss_atk4_count == true && stage5boss_death_flag == false)
	{
		m_py = m_return_block_y;//初期位置にブロックを戻す
		m_falling_time = 10;	//ブロックが落ちるまでの時間
		m_fallint_start_flag = false;//落下フラグをオフにする
		hit->SetInvincibility(false);//自身の当たり判定をつける
	}

	if (m_fallint_start_flag == true)//落下開始フラグがオンなら
		m_falling_time--;
	

	//タイムが0になると下に落ちる
	if (m_falling_time < 0)
	{
		m_py += 1.0f;
		Audio::Start(GROUND);
		
	}
	//ステージ3ボスを倒したとき、落ちるブロックを上昇させる
	if( stage5boss_death_flag == true)
	{
		m_py -= 8.0f;
		m_falling_time = 10;		 //ブロックが落ちるまでの時間
		m_fallint_start_flag = false;//落下フラグをオフにする
		hit->SetInvincibility(false);//自身の当たり判定をつける
		
		//戻す位置(初期位置)より上に上昇したら、初期位置で上昇を止める
		if (m_py<=m_return_block_y)
		{
			m_py = m_return_block_y;
		}
	}

	//落ちるブロックが一定距離落ちたら、自身の当たり判定をなくす
	if (m_py>PERDECISION_CLEAR_POINT)
	{
		hit->SetInvincibility(true);//当たり判定をなくす
	}

	//ヒーローオブジェクトと当たっていれば
	if (hit != nullptr)
{	
		HeroHit();//衝突処理をする
		
		//HitBoxの位置を更新する
		HitBoxUpData(hit, m_px, m_py);
	}
}

//ドロー
void CObjFallingBlock::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = FALLING_BLOCK_SIZE_WIDTH;
	src.m_bottom = BLOCK_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + FALLING_BLOCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//描画
	Draw::Draw(GRA_FALLING_BLOCK, &src, &dst, color, 0.0f);
}

//主人公が当たったときの処理
void CObjFallingBlock::HeroHit()
{
	//主人公オブジェクトを持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公から判定とその後の処理に必要な情報を持ってくる

	//位置
	float* h_px = objhero->GetPointPosX();
	float* h_py = objhero->GetPointPosY();
	//移動のベクトル
	float* h_vx = objhero->GetPointVecX();
	float* h_vy = objhero->GetPointVecY();

	//衝突判定
	HitTestOfAB(m_px, m_py, FALLING_BLOCK_SIZE_WIDTH, BLOCK_SIZE,
		h_px, h_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, h_vx, h_vy);

}