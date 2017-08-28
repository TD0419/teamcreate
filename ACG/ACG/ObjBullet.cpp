#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjBullet.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//引数1	float x		:初期位置X
//引数2	float y		:初期位置Y
//引数3	float angle	:移動する角度
CObjBullet::CObjBullet(float x,float y,float angle)
{
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//主人公が本来いる位置に変更
	x -= obj_m->GetScrollX();
	y -= obj_m->GetScrollY();
	//初期位置を決める
	m_bullet_x = x;
	m_bullet_y = y;
	//速さを決める
	m_speed = 0.5f;
	//角度を代入
	m_angle = angle;

	//マウスの位置と主人公の位置からマウスの角度を求める
	//マウスの位置情報取得
	double mous_x = Input::GetPosX();
	double mous_y = Input::GetPosY();

	//主人公の位置からマウスの位置のベクトル情報取得
	double vector_x = mous_x - x;
	double vector_y = mous_y - y;

	//斜辺取得
	double hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//角度を求め、その方向に移動
	m_bullet_vx = cos(acos(vector_x / hypotenuse)) * m_speed;

	//マウスのY位置が初期Y位置より上
	if (mous_y < y)
	{
		m_bullet_vy = -sin(acos(vector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_bullet_vy = sin(acos(vector_x / hypotenuse)) * m_speed;
	}
}

//イニシャライズ
void CObjBullet::Init()
{
	//当たり判定用HitBoxを作成
	//属性は仮なので変更してください	このコメントも消してね♪				↓(仮)
	Hits::SetHitBox(this, m_bullet_x, m_bullet_y, BULLET_SIZE, BULLET_SIZE, ELEMENT_PLAYER, OBJ_BULLET, 1);
}

//アクション
void CObjBullet::Action()
{
	//移動
	m_bullet_x += m_bullet_vx;
	m_bullet_y += m_bullet_vy;

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_bullet_x, m_bullet_y);//HitBoxの位置を更新

	//画面外へいったら消去
	if (m_bullet_x < -(BULLET_SIZE+BULLET_SIZE/2) || //左　回転してるかもなので少し余裕を持たせる
		m_bullet_x > WINDOW_SIZE_W||   //右
		m_bullet_y < -(BULLET_SIZE+BULLET_SIZE/2) || //上　回転してるかもなので少し余裕を持たせる
		m_bullet_y > WINDOW_SIZE_H     //下
		)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
	}
	
}

//ドロー
void CObjBullet::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置
	dst.m_top = m_bullet_y;
	dst.m_left =  m_bullet_x;
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(0, &src, &dst, color, m_angle);

}