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
	//m_ani_time = 60;
	//m_ani_frame = 1;  //静止フレームを初期にする
	//m_ani_max_time = 4; //アニメーション間隔幅

	//Hits::SetHitBox(this, m_x, m_y, 64, 64, ELEMENT_GREEN, OBJ_ROCK, 1);
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

	//ブロック情報を持ってくる
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	////HitBoxの位置の変更
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_x + block->GetScroll(), m_y + 2);
}

//ドロー
void CObjRock::Draw()
{
	////アニメーション情報を登録
	//int AniData[2] =
	//{
	//	0 , 1
	//};

	////描画カラー情報
	//float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//RECT_F src; //描画元切り取り位置
	//RECT_F dst; //描画先表示位置

	//			//切り取り位置の設定
	//src.m_top = 0.0f;
	//src.m_left = AniData[m_ani_frame] * 64.0f;
	//src.m_right = src.m_left + 64.0f;
	//src.m_bottom = 64.0f;

	////ブロック情報を持ってくる
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	////表示位置の設定
	//dst.m_top = -16.0f + m_y;
	//dst.m_left = -12.0f + m_x + block->GetScroll();
	//dst.m_right = 78.0f + m_x + block->GetScroll();
	//dst.m_bottom = 50.0f + m_y;

	////描画
	//Draw::Draw(28, &src, &dst, c, 0.0f);
}