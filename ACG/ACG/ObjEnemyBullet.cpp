#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjEnemyBullet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjEnemyBullet::CObjEnemyBullet(float x, float y, float angle)
{
	
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//初期位置を決める
	m_x = x;
	m_y = y;
	m_angle = angle;

	//速さを決める
	m_speed = 2.5f;

	//主人公機と敵用弾丸で角度を取る
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公との角度の計算を行う
	double hero_x = obj_hero->GetPosX();		//主人公の位置情報X取得
	double hero_y = obj_hero->GetPosY();		//主人公の位置情報Y取得

	//主人公が本来いる位置に変更
	x -= obj_m->GetScrollX();
	y -= obj_m->GetScrollY();

	//初期位置を決める
	m_x = x;
	m_y = y;

	//速さを決める
	m_speed = 6.5f;

	//主人公の位置のベクトル情報取得
	double Hvector_x = hero_x - x ;
	double Hvector_y = hero_y - y ;

	//斜辺取得
	double hypotenuse = sqrt(Hvector_y * Hvector_y + Hvector_x * Hvector_x);

	//角度を求める
	m_angle = acos(Hvector_x / hypotenuse);

	//角度方向に移動
	m_vx = cos(m_angle) * m_speed;
	m_angle = m_angle * 180.0 / 3.14;

	//マウスのY位置が主人公のY位置より下だったら
	if (hero_y > y)
	{
		//180°～360°の値にする
		m_angle = 360 - abs(m_angle);
	}
	//マウスのY位置が初期Y位置より上
	if (hero_y < y)
	{
		m_vy = -sin(acos(Hvector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acos(Hvector_x / hypotenuse)) * m_speed;
	}
	
}

//イニシャライズ
void CObjEnemyBullet::Init()
{
	/*
	m_vx = 0.0f;
	m_vy = 1.0f;
	m_speed = 0.0f;
	
	m_vx = cos(m_angle) * m_speed;
	m_angle = m_angle * 180.0 / 3.14;
	*/

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, BULLET_SIZE, BULLET_SIZE, ELEMENT_ENEMY, OBJ_ENEMY_BULLET, 1);

}

//アクション
void CObjEnemyBullet::Action()
{
	
	//移動
	m_x += m_vx*1.0f;
	m_y += m_vy*1.0f;

	//Scroll();	//スクロール処理をおこなう

	//画面外へいったら消去
	if (m_x < -(BULLET_SIZE + BULLET_SIZE / 2) ||	//左　
		m_x > WINDOW_SIZE_W ||						//右
		m_y < -(BULLET_SIZE + BULLET_SIZE / 2) ||	//上　
		m_y > WINDOW_SIZE_H							//下
		)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);//HitBoxの位置を更新

	//主人公とあたったら消去
	if (hit->CheckElementHit(OBJ_HERO) == true)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//岩とあたったら消去
	if (hit->CheckObjNameHit(OBJ_ROCK) != nullptr)//仮　ElementHitに変えるかも
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//Water(水)とあたったら消去
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}


}

//ドロー
void CObjEnemyBullet::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top = m_y;
	dst.m_left = m_x;
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(18, &src, &dst, color, m_angle);

}