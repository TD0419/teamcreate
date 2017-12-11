#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"

#include "ObjStage5BossArms.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//ステージ5ボスcppからの描画の都合で、xとyの型をintからfloatに変更しています。(描画で細かい値を使いたいため)
CObjStage5BossArms::CObjStage5BossArms(float x, float y, int type)
{
	m_px = x;
	m_py = y;
	m_arms_type = type;//type = 1…ライトアーム  2…レフトアーム
}

//イニシャライズ
void CObjStage5BossArms::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_arm_hp = 10; //第5ボスアームのＨＰ(仮にＨＰを[10]と設定、左右のアーム共通)

	m_input_posture = false;//入力された姿の初期化　最初は閉じている

	m_posture = false;//現在の姿　最初は閉じている

	m_ani_frame = 0;	//描画アニメーション
	m_ani_max_time = 10;//アニメーションフレーム動作間隔最大値
	m_ani_time = 0;		//アニメーションフレーム動作間隔

	//typeの値が1のときライトアームの当たり判定表示
	if (m_arms_type == 1)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE - 360.0f, STAGE5_BOSS_ARMS_HEIGHT_SIZE - 225.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
	}
	//typeの値が1のときレフトアームの当たり判定表示
	else if (m_arms_type == 2)
	{
		//当たり判定用HitBoxを作成
		Hits::SetHitBox(this, m_px , m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE - 360.0f, STAGE5_BOSS_ARMS_HEIGHT_SIZE - 225.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 2);
	}

}

//アクション
void CObjStage5BossArms::Action()
{
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//アームタイプが1のとき、ライトアーム用の当たり判定表示
	if (m_arms_type == 1)
	{
		//当たり判定更新
		HitBoxUpData(Hits::GetHitBox(this), m_px + 160.0f, m_py + 138.0f);
	}
	//アームタイプが2のとき、レフトアーム用の当たり判定表示
	else if (m_arms_type == 2)
	{
		//当たり判定更新
		HitBoxUpData(Hits::GetHitBox(this), m_px + 186.0f, m_py + 138.0f);
	}

	//弾丸とあたったらＨＰを1減らす
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_arm_hp -= 1;
	}

	//ＨＰが0になったらオブジェクト消去
	if (m_arm_hp == 0)
	{
		this->SetStatus(false);		//自身に消去命令を出す。
		Hits::DeleteHitBox(this);	//アームが所持するHitBoxを除去。
		return;
	}
	
	//入力姿と現在の姿が違う
	if (m_posture != m_input_posture)
	{
		//アニメーション動作間隔を進める
		m_ani_time++;
		//アニメーション動作間隔最大値以上なら
		if (m_ani_time >= m_ani_max_time)
		{
			//アニメーション動作間隔を０にする
			m_ani_time = 0;
			//入力姿が開いている
			if (m_input_posture == true)
			{
				//描画フレームを戻す
				m_ani_frame++;
			}
			//入力姿が閉じている
			else
			{
				//描画フレームを進める
				m_ani_frame--;
			}
		}
	}
	//描画フレームが０なら閉じている
	if (m_ani_frame == 0)
	{
		m_posture = false;
	}
	//描画フレームは２なら開いている
	if(m_ani_frame == 2)
	{
		m_posture = true;
	}
}

//ドロー
void CObjStage5BossArms::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//右腕(ライトアーム)---------------------------------------
	//アームタイプが1のときはライトアームを描画
	if (m_arms_type == 1)
	{
		//切り取り位置
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//描画位置
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		//描画
		Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);

	}

	//左腕(ライトアーム)---------------------------------------
	//アームタイプが2のときはレフトアームを描画
	if (m_arms_type == 2)
	{
		//切り取り位置
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//描画位置
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left =   m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		//描画
		Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);
	}
}