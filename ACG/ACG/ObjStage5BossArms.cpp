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

	m_arm_lower_marker_px = 0.0f;	//腕を下ろす位置を示すかどうかとそのX位置

	m_hit_flag = false;

	//typeの値が1のときライトアームの当たり判定表示
	if (m_arms_type == 1)
	{
		//当たり判定用HitBoxを作成(HITBOXのサイズ調整用に補正値を加えています)
		//																横サイズ補正値						   縦サイズ補正値
		Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
		
	}
	//typeの値が1のときレフトアームの当たり判定表示
	else if (m_arms_type == 2)
	{
		//当たり判定用HitBoxを作成(HITBOXのサイズ調整用に補正値を加えています)
		//																横サイズ補正値						   縦サイズ補正値
		Hits::SetHitBox(this, m_px , m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 2);
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
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}
	//アームタイプが2のとき、レフトアーム用の当たり判定表示
	else if (m_arms_type == 2)
	{
		//当たり判定更新
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
	}

	//移動
	m_px += m_vx;

	//ラストウォールと当たっていれば
	if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
	{
		//衝突ふらぐがオフなら
		if (m_hit_flag == false)
		{
			//ボスのオブジェクトを持ってくる
			CObjStage5Boss* objbossbase = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
			objbossbase->LastWallHit();//ラストウォールと当たった時の処理をする

			m_hit_flag = true;//ふらぐをtrueに
		}
	}
	else
	{
		m_hit_flag = false;//ふらぐをfalseに
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

//拡散弾を打つ攻撃
//引数：爆発までの時間
void CObjStage5BossArms::DiffusionAttack(int limit_time)
{
	//拡散弾の源を作成
	CObjDiffusionSource* p = new CObjDiffusionSource(m_px+ STAGE5_BOSS_ARMS_WIDTH_SIZE /2.0f, m_py+ STAGE5_BOSS_ARMS_HEIGHT_SIZE-10.0f,limit_time);
	Objs::InsertObj(p, OBJ_DIFFUSION_SOURCE, 10);
}

//腕を下ろす攻撃
//引数1	float x	:腕を下ろすX位置
//引数3 int time:
//まだ作成中なので待ってください。
void CObjStage5BossArms::ArmLowerAttack(float x, int time)
{
	static float xx = x;
	//120フレームの間に主人公のX位置と同じになるようにベクトルXを調整
	if (time < 120)
	{
		m_vx = (xx - m_px) / (120 - time);
	}
	else
	{
		m_vx=0.0f;
	}

	//時間が120になったら腕を下ろす攻撃をする
	if (time >= 120)
	{
		m_arm_lower_marker_px = 0.0f;
		m_vy = 10.0f;
		//ブロックオブジェクトを持ってくる
		CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		bool hit_up, hit_down, hit_left, hit_right;
		//ブロックとの当たり判定
		objblock->AllBlockHit(&m_px, &m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE,
			&hit_up, &hit_down, &hit_left, &hit_right, &m_vx, &m_vy);

		
	}
	//時間が120になるまで腕を下ろす位置をマークする
	else
	{
		m_arm_lower_marker_px = xx;
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
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*m_ani_frame;
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
		src.m_top = 0.0f;
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*m_ani_frame;
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

	//腕を下ろす位置を示すなら示す
	if (m_arm_lower_marker_px > 0.0f)
	{
		//カラー情報
		float marker_color[4] = { 1.0f,0.0f,0.0f,0.2f };

		//途中なのでおいといてください。
		/*int map_x = (int)m_arm_lower_marker_px / BLOCK_SIZE;
		float 
		if (map_x < MAP_X_MAX)
		{
			for (int i = 0;i < MAP_Y_MAX; i++)
			{
				objmap->GetMap(map_x, i)
			}
		}*/
		//
		Draw::DrawHitBox(m_arm_lower_marker_px, 0.0f, 1000.0f, 100.0f, marker_color);
	}
}