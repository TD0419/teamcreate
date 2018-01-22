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

	m_arm_down_flag = false;//初期は落ちていない

	m_ani_frame_claw = 0;	//描画アニメーション(爪)
	m_ani_max_time_claw = 5;//アニメーションフレーム動作間隔最大値(爪)
	m_ani_time_claw = 0;		//アニメーションフレーム動作間隔(爪)

	m_arm_lower_marker_px = 0.0f;	//腕を下ろすX位置
	m_arm_down_marker = false;		//腕を下ろす位置を示さない

	m_armdown_time=0;//腕を下ろすときの管理用タイム

	m_time=0;			//たいみんぐ管理用
	m_shot_hit_time = 0;//弾丸が当たったたいみんぐの保存用
	m_draw_flag=false;//描画用のフラグ
	m_damage_flag=false;//ダメージフラグ

	m_wall_hit_flag = false;

	m_block_hit_flag = false;
	m_initpos_flag = false;

	m_arm_down_attack_flag = false;	//最初は腕下ろし攻撃フラグをOFF

	//腕の接続部分の電流を表示する/しないかを判断するための変数----------------------
	//接続部分の描画はObjStage5Boss.cppにて

	m_left_arm_move = false; //false…初期位置から動いていない　true…動いている(レフトアーム用)
	m_right_arm_move = false;//false…初期位置から動いていない　true…動いている(ライトアーム用)

	//-------------------------------------------------------------------------------

	//typeの値が1のときライトアームの当たり判定表示
	if (m_arms_type == RIGHT_ARM)
	{
		//当たり判定用HitBoxを作成(HITBOXのサイズ調整用に補正値を加えています)
		//																横サイズ補正値						   縦サイズ補正値
		Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
		
	}
	//typeの値が1のときレフトアームの当たり判定表示
	else if (m_arms_type == LEFT_ARM)
	{
		//当たり判定用HitBoxを作成(HITBOXのサイズ調整用に補正値を加えています)
		//																横サイズ補正値						   縦サイズ補正値
		Hits::SetHitBox(this, m_px , m_py, STAGE5_BOSS_ARMS_WIDTH_SIZE, STAGE5_BOSS_ARMS_HEIGHT_SIZE-5.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 2);
	}
}

//アクション
void CObjStage5BossArms::Action()
{
	m_time++;

	//初期位置を更新する
	UpdateInitial();

	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//移動
	m_px += m_vx;
	m_py += m_vy;

	//落ちるブロックと当たれば
	if (hit->CheckObjNameHit(OBJ_FALLING_BLOCK) != nullptr)
	{
		m_py -= m_vy;
		m_vx = 0.0f;
		m_vy = 0.0f;

		m_block_hit_flag = true;
	}
	//落ちるブロックと当たっていなければ
	else
		m_block_hit_flag = false;//落ちるブロックHitフラグをOFFにする

	//腕を下ろす攻撃フラグがONなら行う
	if (m_arm_down_attack_flag == true)
	{
		ArmLowerAttack();
		m_left_arm_move = true; //レフトアームが「初期位置から動いている」判定を出す
		m_right_arm_move = true;//ライトアームが「初期位置から動いている」判定を出す

		
	}
	//ボスオブジェクトの取得
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);

	//ステージ５のボスが存在していたら
	if (objboss != nullptr)
	{
		if ( objboss->GetAttackMode() == 3)//攻撃パターン３なら
		{
			MoveShotAttack();
		}
	}

	if ( m_arms_type == RIGHT_ARM )//右腕
		m_arm_down_flag = objboss->GetArmDownFlagRight();
	else
		m_arm_down_flag = objboss->GetArmDownFlagLeft();
	
	//腕が落ちてるとき かつ　初期に戻すフラグがオフ　なら
	if ( m_arm_down_flag == true && m_initpos_flag == false )
	{
		//弾丸とあたったらＨＰを1減らす
		if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{
			m_damage_flag = true;
			m_shot_hit_time = m_time;
			m_draw_flag = true;

			m_arm_hp -= 1;
		}
	}

	//ＨＰが0になったらオブジェクトを初期位置に戻すためのフラグをオンにする
	if (m_arm_hp <= 0)
	{
		//腕の復活位置が2本の柱の内側にあれば
		if (6100.0f < m_initial_px && m_initial_px + STAGE5_BOSS_ARMS_WIDTH_SIZE < 7000.0f)
		{
			//腕のフラグを更新する
			if (m_arms_type == RIGHT_ARM)//右腕
				objboss->SetArmDownFlagRight();
			else
				objboss->SetArmDownFlagLeft();

			m_initpos_flag = true;
		}
	}

	//初期位置フラグがオンなら
	if (m_initpos_flag == true)
	{
		
		m_left_arm_move = false; //レフトアームが「初期位置から動いていない」判定を出す
		m_right_arm_move = false;//ライトアームが「初期位置から動いていない」判定を出す

		//初期位置に戻す
		m_px = m_initial_px;
		m_py = m_initial_py;

		//HPを戻す
		m_arm_hp = 10;
		m_initpos_flag = false;
		m_block_hit_flag = false;

		//当たり判定更新
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
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
			//アニメーション動作間隔を0にする
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

	//当たり判定更新
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//ドロー
void CObjStage5BossArms::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	float transparent[4] = { 0.0f,0.0f,0.0f, 0.0f };//透明に描画する

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//ボスオブジェクトをもってくる
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);


	int time = m_time - m_shot_hit_time;

	//ダメージをうけているなら
	if (m_damage_flag == true)
	{
		if (time % 5 == 0)//5フレームに一度フラグを切り替える
			m_draw_flag = !m_draw_flag;
	}

	if (time > 15)//15フレーム経過でダメージフラグをオフにする
	{
		//フラグの初期化
		m_damage_flag = false;
		m_draw_flag = false;
		//タイムの初期化
		m_time = 0;
		m_shot_hit_time = 0;
	}

	//胴腕接続電気-------------------------------

	if (m_arms_type == LEFT_ARM)
	{
		//左腕部分																//切り取り位置
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

		//描画位置
		dst.m_top = objboss->GetPosY()+ ELECTRIC_L_CORRECTION_HEIGHT-objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX() ;
		dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

		//描画
		//レフトアームが動いているときは、透明に描画する。
		if (m_left_arm_move == true)//レフトアームが「動いている」判定がでているとき
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, transparent, 0.0f);//透明に描画する。
		}
		else//レフトアームが「初期位置(描画)から動いていない」判定がでている 
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);//通常の描画をする。
		}
	}
	else
	{
		//右腕部分
		//切り取り位置
		src.m_top = STAGE5_BOSS_ELECTRIC_HEIGHT;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

		//描画位置

		dst.m_top = objboss->GetPosY() + ELECTRIC_L_CORRECTION_HEIGHT-objmap->GetScrollY();		
		dst.m_left = m_px - objmap->GetScrollX() - STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
		//描画
		//ライトアームが動いているときは、透明に描画する。
		if (m_right_arm_move == true)//ライトアームが「動いている」判定がでているとき
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, transparent, 0.0f);//透明に描画する。
		}
		else//ライトアームが「初期位置(描画)から動いていない」判定がでているとき
		{
			Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);//通常の描画をする。
		}
	}
	//爪の開閉アニメーションをするときの配列
	//要素数はm_ani_frame_claw
	int ani_claw[3] = { 1,2,0 };

	//右腕(ライトアーム)---------------------------------------
	//アームタイプが1のときはライトアームを描画
	if (m_arms_type == RIGHT_ARM)
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
		
		//描画のフラグがオンなら白く表示
		if (m_draw_flag == true)
			Draw::Draw(GRA_STAGE5_BOSS_WHITE_ARMS, &src, &dst, color, 0.0f);
		else
			Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);
	}

	//左腕(ライトアーム)---------------------------------------
	//アームタイプが2のときはレフトアームを描画
	if (m_arms_type == LEFT_ARM)
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
	
		//描画のフラグがオンなら白く表示
		if (m_draw_flag == true)
			Draw::Draw(GRA_STAGE5_BOSS_WHITE_ARMS, &src, &dst, color, 0.0f);
		else
			Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);
	}

	//腕を下ろす位置を示すなら示す
	if (m_arm_down_marker == true)
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
				if (objmap->GetMap(map_x, map_y) == MAP_FALLING_BLOCK)
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

//移動しながら弾を撃つ攻撃
void CObjStage5BossArms::MoveShotAttack()
{
	//HitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);

	//ラストウォールと当たっていれば
	if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
	{
		//衝突ふらぐがオフなら
		if (m_wall_hit_flag == false)
		{
			//ボスのオブジェクトを持ってくる
			CObjStage5Boss* objbossbase = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
			if(objbossbase != nullptr)	//ステージ５のボスが存在していたら
				objbossbase->LastWallHit();//ラストウォールと当たった時の処理をする

			m_wall_hit_flag = true;//ふらぐをtrueに
		}
	}
	else
	{
		m_wall_hit_flag = false;//ふらぐをfalseに
	}
}

//拡散弾を打つ攻撃
//引数：爆発までの時間
void CObjStage5BossArms::DiffusionAttack(int limit_time)
{
	//拡散弾の源を作成
	CObjDiffusionSource* p = new CObjDiffusionSource(m_px + STAGE5_BOSS_ARMS_WIDTH_SIZE / 2.0f, m_py + STAGE5_BOSS_ARMS_HEIGHT_SIZE, limit_time);
	Objs::InsertObj(p, OBJ_DIFFUSION_SOURCE, 10);
}

//腕を下ろす攻撃
//引数1	float x		:腕を下ろすX位置
//引数2 bool marker	:腕を下ろす位置を示すかどうか
void CObjStage5BossArms::ArmLowerAttack(float x,bool marker)
{
	//腕を下ろす攻撃フラグをONにする
	m_arm_down_attack_flag = true;
	//腕を下ろすときの管理用タイムを０にする
	m_armdown_time = 0;
	//腕を下ろすX位置を決める
	m_arm_lower_marker_px = x;
	//腕を下ろす位置を示すかどうかを決める
	m_arm_down_marker = marker;
	//

}
//腕を下ろす攻撃
void CObjStage5BossArms::ArmLowerAttack()
{
	m_armdown_time++;

	//120フレームの間に主人公のX位置と同じになるようにベクトルXを調整
	if (m_armdown_time < 120)
	{
		m_vx = (m_arm_lower_marker_px - m_px) / (float)(120 - m_armdown_time);
	}
	//120以上なら腕を下ろすのでX移動量を0.0fにする
	else
	{
		m_vx = 0.0f;
	}

	//時間が120になったら腕を下ろす攻撃をする
	if (m_armdown_time >= 120)
	{
		
		//腕を下ろす位置を示さない
		m_arm_down_marker = false;
		m_arm_lower_marker_px = 0.0f;

		//ライトアームまたはレフトアームがＸ軸初期位置から動かず、Ｙ軸初期位置の直下に
		//腕を下ろした場合に「腕が動いている」判定を出す処理---------------------------
		if (m_right_arm_move == false)	//ライトアームが「初期位置から動いていない」判定が出ているとき
		{
			m_right_arm_move = true;	//「ライトアームが動いている」判定を出す
		}
		if(m_left_arm_move == false)	//ライトアームが「初期位置から動いていない」判定が出ているとき
		{
			m_left_arm_move = true;		//「レフトアームが動いている」判定を出す
		}
		//---------------------------------------------------------------------------------

		//ブロックと当たるまで
		if (m_block_hit_flag == false)
		{
			//腕を下ろす
			m_vy = 10.0f;
		}
		//ブロックに当たったら腕を下ろす攻撃をやめる
		else
		{
			m_arm_down_attack_flag = false;
		}
	}
}

//初期位置を計算する
//初期位置をボス(胴体)の位置を元に求める
void CObjStage5BossArms::UpdateInitial()
{
	//ボス(胴体)の情報を取得
	CObjStage5Boss* objstage5_boss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	
	//ステージ５のボスが存在していたら
	if (objstage5_boss != nullptr)
	{
		//ライトアームの時
		if (m_arms_type == RIGHT_ARM)
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
}

//自身(腕)とHIT_BOXを消去する
void CObjStage5BossArms::Delete()
{
	this->SetStatus(false);		//自身に削除命令を出す
	Hits::DeleteHitBox(this);//自身が所有するHitBoxを削除する
}