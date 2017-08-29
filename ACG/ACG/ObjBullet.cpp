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
CObjBullet::CObjBullet(int x, int y)
{
	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//主人公が本来いる位置に変更
	x -= obj_m->GetScrollX();
	y -= obj_m->GetScrollY();
	//初期位置を決める
	m_px = x;
	m_py = y;
	//速さを決める
	m_speed = 6.5f;

	//マウスの位置と主人公の位置からマウスの角度を求める
	//マウスの位置情報取得
	double mous_x = Input::GetPosX();
	double mous_y = Input::GetPosY();

	//主人公の位置からマウスの位置のベクトル情報取得
	double vector_x = mous_x - x;
	double vector_y = mous_y - y;

	//斜辺取得
	double hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//角度を求める
	m_angle = acos(vector_x / hypotenuse);
	//角度方向に移動
	m_vx = cos(m_angle) * m_speed;
	m_angle = m_angle * 180.0 / 3.14;

	//マウスのY位置が主人公のY位置より下だったら
	if (mous_y > y )
	{
		//180°～360°の値にする
		m_angle = 360 - abs(m_angle);
	}
	//マウスのY位置が初期Y位置より上
	if (mous_y < y)
	{
		m_vy = -sin(acos(vector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acos(vector_x / hypotenuse)) * m_speed;
	}
}

//イニシャライズ
void CObjBullet::Init()
{
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_PLAYER, OBJ_BULLET, 1);
}

//アクション
void CObjBullet::Action()
{	
	//画面外へいったら消去
	if (m_px < -(BULLET_SIZE+BULLET_SIZE/2) || //左　回転してるかもなので少し余裕を持たせる
		m_px > WINDOW_SIZE_W||   //右
		m_py < -(BULLET_SIZE+BULLET_SIZE/2) || //上　回転してるかもなので少し余裕を持たせる
		m_py > WINDOW_SIZE_H     //下
		)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//弾丸が所持するHitBoxを除去。
		return;
	}

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//敵とあたったら消去
	if (hit->CheckElementHit(ELEMENT_ENEMY)==true)
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
	
	//ブロックとあたった場合
	if (hit->CheckObjNameHit(OBJ_BLOCK) != nullptr)
	{
		HIT_DATA** hit_data;	//衝突の情報を入れる構造体
		hit_data = hit->SearchObjNameHit(OBJ_BLOCK);//衝突の情報をhit_dataに入れる

		float r = hit_data[0]->r;

		//上　または　下で衝突している場合
		if (45 <= r && r < 135 || 225 <= r && r < 315)
		{
			m_vy *= (-1);//移動ベクトルの上下を反転する
		}
		else //左または右で衝突している場合
		{
			m_vx *= (-1);//移動ベクトルの左右を反転する
		}
	}

	//移動
	m_px += m_vx;
	m_py += m_vy;

	hit->SetPos(m_px, m_py);//HitBoxの位置を更新

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
	dst.m_top = m_py;
	dst.m_left =  m_px;
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(0, &src, &dst, color, m_angle);

}