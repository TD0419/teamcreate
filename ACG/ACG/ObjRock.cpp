//使用するヘッダーファイル　
#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjRock.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRock::CObjRock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//イニシャライズ
void CObjRock::Init()
{
	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 5; //アニメーション間隔幅
	m_ani_start_flag = false;//アニメフラグOFF

	//当たり判定用HitBoxを作成                          
	Hits::SetHitBox(this, m_px, m_py, ROCK_SIZE_WIDTH, ROCK_SIZE_HEIGHT, ELEMENT_GIMMICK, OBJ_ROCK, 1);
}

//アクション
void CObjRock::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	
	//弾と接触しているかどうかを調べる
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		Audio::Start(ROCK);//岩の音楽スタート
		m_ani_start_flag = true;//アニメフラグON
	}
	//アニメフラグONだと
	if (m_ani_start_flag == true)
	{
		m_ani_time+=1;
		//アニメーションの感覚管理
		if (m_ani_time > m_ani_max_time)
		{
			m_ani_frame += 1;
			m_ani_time = 0;
		}

		//最後までアニメーションが進むと存在を消す
		if (m_ani_frame == 4)
		{
			Hits::DeleteHitBox(this);	//岩が所有するHitBoxに削除する
			this->SetStatus(false);		//自身に削除命令を出す
			return;
		}
	}

	//主人公オブジェクト情報を持ってくる
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hero_x = objhero->GetPosX();
	float hero_y = objhero->GetPosY();
	float hero_vx = objhero->GetVecX();
	float hero_vy = objhero->GetVecY();

	//HitBoxの幅、高さ
	float hit_w, hit_h;

	//HitBoxの幅、高さ設定
	hit_w = ROCK_SIZE_WIDTH;
	hit_h = ROCK_SIZE_HEIGHT;
	//主人公との当たり判定
	//衝突したら主人公の位置を更新する
	m_rock_determine = HitTestOfAB(m_px - 7.0f, m_py - 8.0f, hit_w - 8.0f, hit_h + 12.0f, &hero_x, &hero_y, 42, 120, &hero_vx, &hero_vy);

	switch (m_rock_determine)
	{
	case 1://下が当たっている
		   //主人公の位置を更新
		objhero->SetPosY(hero_y);
		objhero->SetVecY(hero_vy);
		break;
	case 2://上が当たっている
		   //主人公の位置を更新
		objhero->SetPosY(hero_y);
		objhero->SetVecY(hero_vy);
		break;
	case 3://右が当たっている
		   //主人公の位置を更新
		objhero->SetPosX(hero_x);
		objhero->SetVecX(hero_vx);
		break;
	case 4://左が当たっている
		   //主人公の位置を更新
		objhero->SetPosX(hero_x);
		objhero->SetVecX(hero_vx);
		break;
	}
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py- ROCK_SIZE_WIDTH);

}

//ドロー
void CObjRock::Draw()
{
	//画像の切り取り配列
	int AniData[4] =
	{
		0, 1, 2, 3
	};

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 1.0f;
	src.m_left = AniData[m_ani_frame] * 128.0f - 128.0f;
	src.m_right = src.m_left + 128.0f;
	src.m_bottom = src.m_top + 198.0f;
	
	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()- ROCK_SIZE_WIDTH;
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + ROCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + ROCK_SIZE_HEIGHT;

	
	//描画
	Draw::Draw(GRA_ROCK, &src, &dst, color, 0.0f);
}