//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRock.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRock::CObjRock(float x, float y)
{
	m_x = x;
	m_y = y;
}

//イニシャライズ
void CObjRock::Init()
{
	//当たり判定用HitBoxを作成                          仮
	Hits::SetHitBox(this, m_x, m_y, 128.0f, 198.0f, ELEMENT_NULL, OBJ_ROCK, 1);
}

//アクション
void CObjRock::Action()
{
	////ブロック情報を持ってくる
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	////HitBoxの位置の変更
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_x + block->GetScroll(), m_y);

	////弾と接触しているかどうかを調べる　//ObjEnemyと同じようにしたほうがいいかも知れない。
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	this->SetStatus(false);		//自身に削除命令を出す
	//	Hits::DeleteHitBox(this);	//岩が所有するHitBoxに削除する
	//}
}

//ドロー
void CObjRock::Draw()
{

}