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

	m_ani_flag_claw = false;//爪の開閉アニメーションをしない

	m_ani_frame_claw = 0;	//描画アニメーション(爪)
	m_ani_max_time_claw = 5;//アニメーションフレーム動作間隔最大値(爪)
	m_ani_time_claw = 0;		//アニメーションフレーム動作間隔(爪)

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
	//初期位置を更新する
	UpdateInitial();

	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブロックとの当たり判定
	bool hit_up, hit_down, hit_left, hit_right;
	objblock->AllBlockHit(&m_px, &m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE,
		&hit_up, &hit_down, &hit_left, &hit_right, &m_vx, &m_vy);

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
	m_py += m_vy;

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
		//初期位置に戻す
		m_px = m_initial_px;
		m_py = m_initial_py;
		//HPを戻す
		m_arm_hp = 10;
		return;
	}
	
	//爪のアニメーション処理-----------------------------------
	//爪のアニメーションをする
	if (m_ani_flag_claw == true)
	{
		//アニメーション動作間隔を進める
		m_ani_time_claw++;
		//アニメーション動作間隔最大値以上なら
		if (m_ani_time_claw >= m_ani_max_time_claw)
		{
			//アニメーション動作間隔を０にする
			m_ani_time_claw = 0;
			m_ani_frame_claw++;
			
		}
		if (m_ani_frame_claw == 5)
		{
			m_ani_frame_claw = 0;
			m_ani_flag_claw = false;
		}
	}
	//---------------------------------------------------------
}

//拡散弾を打つ攻撃
//引数：爆発までの時間
void CObjStage5BossArms::DiffusionAttack(int limit_time)
{
	//爪の開閉アニメーションをする
	m_ani_flag_claw = true;

	//拡散弾の源を作成
	CObjDiffusionSource* p = new CObjDiffusionSource(m_px+ STAGE5_BOSS_ARMS_WIDTH_SIZE /2.0f, m_py+ STAGE5_BOSS_ARMS_HEIGHT_SIZE-10.0f,limit_time);
	Objs::InsertObj(p, OBJ_DIFFUSION_SOURCE, 10);
}

//腕を下ろす攻撃
//引数1	float x	:腕を下ろすX位置
//引数3 int time:腕を下ろそうとしたときから経過時間
void CObjStage5BossArms::ArmLowerAttack(float x, int time)
{
	//攻撃が始まる瞬間に腕を下ろすX位置を決める
	if (time == 1)
	{
		m_arm_lower_marker_px = x;
	}
	//120フレームの間に主人公のX位置と同じになるようにベクトルXを調整
	if (time < 120)
	{
		m_vx = (m_arm_lower_marker_px - m_px) / (120 - time);
	}
	//120以上なら腕を下ろす攻撃をするのでX移動量を0.0fにする
	else
	{
		m_vx=0.0f;
	}

	//時間が120になったら腕を下ろす攻撃をする
	if (time >= 120)
	{
		//腕を下ろす位置を示さない
		m_arm_lower_marker_px = 0.0f;
		//腕を下ろす
		m_vy = 10.0f;
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

	//爪の開閉アニメーションをするときの配列
	//要素数はm_ani_frame_claw
	int ani_claw[5] = { 1,2,0 };

	//右腕(ライトアーム)---------------------------------------
	//アームタイプが1のときはライトアームを描画
	if (m_arms_type == 1)
	{
	
		
		//切り取り位置
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		if(m_ani_flag_claw == true)//爪の開閉アニメーションをするなら
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*ani_claw[m_ani_frame_claw];
		else
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*1;
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
		if (m_ani_flag_claw == true)//爪の開閉アニメーションをするなら
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE*ani_claw[m_ani_frame_claw];
		else
			src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE * 1;
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

		//腕を下ろすX位置をマップ番号に当てはめたときのX位置
		int map_x = (int)(m_arm_lower_marker_px / BLOCK_SIZE);

		//マーカーを四角形で出すのでその高さ
		float marker_h= WINDOW_SIZE_H;

		//X位置が最大値未満なら
		if (map_x < MAP_X_MAX)
		{
			//Y位置を0～最大値まで調べる
			for (int map_y = 0; map_y < MAP_Y_MAX; map_y++)
			{
				//ブロックがあるか調べてあるならその位置までを高さとする
				if (objmap->GetMap(map_x, map_y) == MAP_BLOCK)
				{
					marker_h = map_y * BLOCK_SIZE-m_py;
					break;
				}
			}
		}

		//マーカー(四角形)を表示する
		Draw::DrawHitBox(m_arm_lower_marker_px - objmap->GetScrollX(), m_py - objmap->GetScrollY(), marker_h, STAGE5_BOSS_ARMS_WIDTH_SIZE, marker_color);
	}
}

//初期位置を計算する
//初期位置をボス(胴体)の位置を元に求める
void CObjStage5BossArms::UpdateInitial()
{
	//ボス(胴体)の情報を取得
	CObjStage5Boss* objstage5_boss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	
	//ライトアームの時
	if (m_arms_type == 1)
	{	//										↓ボスの胴体に密着する位置
		m_initial_px = (objstage5_boss->GetPosX() + STAGE5_BOSS_BODY_SIZE) + 60.0f;
	}
	//レフトアームの時
	else
	{
		//										↓ボスの胴体に密着する位置
		m_initial_px = (objstage5_boss->GetPosX() - STAGE5_BOSS_ARMS_WIDTH_SIZE) - 60.0f;
		
	}
	m_initial_py = objstage5_boss->GetPosY() - 100.0f;
}