#include "GameL\DrawTexture.h"
#include "GameL\UserData.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjDoor.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDoor::CObjDoor(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjDoor::Init()
{
	m_ani_door_time = 0;
	m_ani_door_frame = 1;	 //静止フレームを初期化する
	m_ani_door_time_max = 20;//アニメーション間隔幅

	m_unlock_flag = false;
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, DOOR_SIZE, DOOR_SIZE, ELEMENT_GIMMICK, OBJ_DOOR, 1);
}

//アクション
void CObjDoor::Action()
{
	//ドアのHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//ボスの情報を呼ぶの
	CObjBoss*objboss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);


	//ボスが消滅したとき
	if (objboss==nullptr)
	{
		m_unlock_flag = true;//施錠解除フラグをonにします
	}

	//施錠解除フラグオンのとき
	if (m_unlock_flag==true)
	{
		m_ani_door_time += 1;//アニメーションタイム+１
	}

	//ドアアニメタイムがマックスタイムより少なく、フレームが2じゃないとき
	if (m_ani_door_time > m_ani_door_time_max&&m_ani_door_frame != 2)
	{
		m_ani_door_frame += 1;//ドアのフレームを+1します。
		m_ani_door_time = 0;  //ドアタイムを0にします
		Audio::Start(DOOR);//ドア音楽スタート
	}
	//ドアフレームが2のとき
	if (m_ani_door_frame == 2)
	{
		m_ani_door_frame = 2;//フレームを2に固定
		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//ステージカウントを増やして次のステージにする
			((UserData*)Save::GetData())->stagenum += 1;
			Scene::SetScene(new CSceneMain());
		}
	}
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjDoor::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = m_ani_door_frame * 128.0f-128.0f;
	src.m_right = src.m_left+128.0f;
	src.m_bottom = src.m_top+128.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + DOOR_SIZE;
	dst.m_bottom = dst.m_top + DOOR_SIZE;

	//描画
	Draw::Draw(GRA_DOOR, &src, &dst, color, 0.0f);
}