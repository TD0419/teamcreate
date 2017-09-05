//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRock::CObjRock(int x, int y)
{
	m_px = x * ROCK_SIZE;
	m_py = y * ROCK_SIZE;
}

//イニシャライズ
void CObjRock::Init()
{
	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, ROCK_SIZE, ROCK_SIZE, ELEMENT_GIMMICK, OBJ_ROCK, 1);
}

//アクション
void CObjRock::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	
	//弾と接触しているかどうかを調べる　//ObjEnemyと同じようにしたほうがいいかも知れない。
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//自身に削除命令を出す
		Hits::DeleteHitBox(this);	//岩が所有するHitBoxに削除する
	}

	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//ドロー
void CObjRock::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;
	
	//描画位置
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + ROCK_SIZE;
	dst.m_bottom = dst.m_top + ROCK_SIZE;

	//描画
	Draw::Draw(10, &src, &dst, color, 0.0f);
}