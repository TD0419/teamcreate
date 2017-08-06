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
	m_rock_x = x;
	m_rock_y = y;
}

//イニシャライズ
void CObjRock::Init()
{

}

//アクション
void CObjRock::Action()
{
	//////弾と接触しているかどうかを調べる
	//if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	//{
	//	//岩が壊れるアニメーションを入れる

	//	//----//

	//	this->SetStatus(false);		//自身に削除命令を出す
	//	Hits::DeleteHitBox(this);	//敵が所有するHitBoxに削除する
	//}
}

//ドロー
void CObjRock::Draw()
{

}