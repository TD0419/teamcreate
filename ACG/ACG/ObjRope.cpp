#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjRope.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//引数1	float x		:初期位置X
//引数2	float y		:初期位置Y
CObjRope::CObjRope(int x, int y)
{
	m_px = x;
	m_py = y;

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
	if (mous_y > y)
	{
		//180°〜360°の値にする
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
void CObjRope::Init()
{
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_PLAYER, OBJ_ROPE, 1);

}

//アクション
void CObjRope::Action()
{
	//画面外へいったら消去
	if (m_px < -(BULLET_SIZE + BULLET_SIZE / 2) || //左　回転してるかもなので少し余裕を持たせる
		m_px > WINDOW_SIZE_W ||   //右
		m_py < -(BULLET_SIZE + BULLET_SIZE / 2) || //上　回転してるかもなので少し余裕を持たせる
		m_py > WINDOW_SIZE_H     //下
		)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//ロープが所持するHitBoxを除去。
		return;
	}

	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//ロープスイッチと衝突したときの処理
	if(hit->CheckObjNameHit(OBJ_ROPE_SWITCH) != nullptr)
	{
		;
	}

	//移動
	m_px += m_vx;
	m_py += m_vy;

	hit->SetPos(m_px, m_py);//HitBoxの位置を更新
}

//ドロー
void CObjRope::Draw()
{
}