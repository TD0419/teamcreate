#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"
#include "ObjStage5Boss.h"

#include <time.h>

//使用するネームスペース
using namespace GameL;
//コンストラクタ
CObjStage5Boss::CObjStage5Boss(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 50; //第5ボスのＨＰ

	m_right_arm_down_flag = false;
	m_left_arm_down_flag = false;

	//初期化する(何もしていない)
	m_attack_mode = 0;

	m_lastwall_hit_flag=false;

	//タイミング管理
	m_time = 0;

	//描画関連
	m_draw_time = 0;	
	m_shot_hit_time = 0;
	m_draw_flag=false;
	m_damage_flag=false;

	//攻撃パターン3
	m_attack3_flag = false;
	m_attack3_count = 0;

	//攻撃パターン4
	m_attack4_flag = false;
	m_attack4_scroll = 0.0f;
	m_block_down_flag = false;
	m_attack4_count = 0;

	//死亡フラグをOFFにする
	m_death_flag = false;

	m_progress_atk4_count = false;//false…120フレーム経過していない　true…120フレーム経過した

	//音楽
	Audio::Start(BOSS);
	Audio::Stop(STAGE);

	//死亡アニメーション関係の変数の初期化
	for (int i = 0; i < 4; i++)
	{
		//描画フレーム、アニメーションフレーム動作間隔の要素数
		//０：最初の爆発
		//１：2回目の爆発
		//２：最後の爆発
		//３：ボス(胴体)サイズの爆発
		//詳細はActionDeathAnimation関数に書いています
		//描画フレーム(死亡)
		m_ani_frame_death[i] = 0;
		//アニメーションフレーム動作間隔(死亡)
		m_ani_time_death[i] = 0;
	}
	//アニメーションフレーム動作間隔最大値(死亡)
	//要素数０：64＊64の爆発をいくつも出すのだがそのアニメーションフレーム動作間隔最大値
	//要素数１：ボス(胴体)サイズの爆発をボス死亡直後にだすのだがそのアニメーションフレーム動作間隔最大値
	m_ani_max_time_death[0] = 4;
	m_ani_max_time_death[1] = 8;

	//左右の腕作成ー------------------
	//右腕オブジェクト作成								↓ボスの胴体に密着する位置
	m_boos_arm_right = new CObjStage5BossArms((m_px+ STAGE5_BOSS_BODY_SIZE)+60.0f, m_py - 100.0f, 1);
	Objs::InsertObj(m_boos_arm_right, OBJ_STAGE5_BOSS_ARMS, 8);

	//左腕オブジェクト作成								↓ボスの胴体に密着する位置		
	m_boos_arm_left = new CObjStage5BossArms((m_px-  STAGE5_BOSS_ARMS_WIDTH_SIZE)-60.0f, m_py - 100.0f, 2);
	Objs::InsertObj(m_boos_arm_left, OBJ_STAGE5_BOSS_ARMS, 8);

	//-------------------------------
	
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BODY_SIZE, STAGE5_BOSS_BODY_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
}

//アクション
void CObjStage5Boss::Action()
{
	m_draw_time++;

	//生きているとき
	if (m_death_flag == false)
	{
		m_time++;

		if (m_time > 10000)
			m_time = 0;

		//HitBox更新用ポインター取得
		CHitBox* hit = Hits::GetHitBox(this);

		switch (m_attack_mode)
		{
			//何もしていない状態
		case 0:
		{
			if (m_time % 100 == 0)
			{
				//何もしていないので攻撃モードをランダムで決める
				m_attack_mode = GetRandom(1, 4);
				m_time = 0;
			}
			break;
		}
		//主人公のいる位置を取って上から地面までに当たると死ぬ攻撃を落とす攻撃
		case 1:
		{
			//主人公オブジェクト情報を取得
			CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

			if (m_time == 200)
			{
				//腕を下ろす攻撃をする(左腕)
				m_boos_arm_left->ArmLowerAttack(objhero->GetPosX(), true);
				m_left_arm_down_flag = true;
			}
			else if (m_time == 300)
			{
				//腕を下ろす攻撃をする(右腕)
				m_boos_arm_right->ArmLowerAttack(objhero->GetPosX(), true);
				m_right_arm_down_flag = true;
			}

			if (m_time >= 400)
			{
				m_attack_mode = 3;//腕をおろした後は攻撃３にする
			}
			break;
		}
		case 2:	//打ち出してからランダムな時間経過で拡散弾になる弾を出す攻撃
		{
			if (m_time % 300 == 150)
			{
				m_boos_arm_left->DiffusionAttack(GetRandom(60, 180));
			}
			else if (m_time % 300 == 0)
			{
				m_boos_arm_right->DiffusionAttack(GetRandom(60, 180));
				m_attack_mode = 0;
			}
			break;
		}
		case 3://ボス自身が動きながら主人公の位置に弾を撃つ(レーザー)攻撃
		{
			if (m_attack3_flag == false)//フラグがオフなら
			{
				m_attack3_count = 0;
				m_vx = -1.0f;//移動量を左に設定
				m_attack3_flag = true;//フラグをオン
			}

			//60フレームに一度
			if (m_time % 60 == 0)
			{
				CObjEnemyBullet* p = new CObjEnemyBullet(m_px + EYE_CORRECTION_WIDTH + STAGE5_BOSS_EYE_SIZE / 2.0f, m_py + EYE_CORRECTION_HEIGHT + STAGE5_BOSS_EYE_SIZE / 2.0f);
				Objs::InsertObj(p, OBJ_ENEMY_BULLET, 11);

				m_attack3_count++;
			}

			if (m_attack3_count == 10)//10回攻撃したら
			{
				m_attack3_flag = false;//フラグをオフ
				m_vx = 0.0f;//移動をとめる

				//腕が地面に残っていなければ
				if (m_right_arm_down_flag == false && m_left_arm_down_flag == false)
					m_attack_mode = 0;
				else
					m_attack_mode = 3;
			}
			//腕にも移動量を渡す
			if (m_right_arm_down_flag == false)	//腕が落ちていなければ
				m_boos_arm_right->SetVecX(m_vx);
			if (m_left_arm_down_flag == false)		//腕が落ちていなければ
				m_boos_arm_left->SetVecX(m_vx);
			break;
		}
		//3地点に縄を引っ掛けるオブジェクトを出現させ、その後地面が落ちる攻撃をする。
		case 4:
		{
			//マップオブジェクトを持ってくる
			CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

			//攻撃が始まって一回のみ
			if (m_attack4_flag == false)
			{
				m_attack4_scroll = objmap->GetScrollX();//スクロール値Xを持ってくる
				m_attack4_flag = true;

				//腕を移動させて落とす

				//左腕を下ろすX位置
				//初期値はラストウォールの横
				float left_down_x = 94 * BLOCK_SIZE;
				//右腕を下ろす位置
				//初期値はラストウォールの横
				float right_down_x = 108 * BLOCK_SIZE;
				//ラストウォールの横より画面左端が大きかったら
				//下ろす位置を画面左端にする
				if (left_down_x < m_attack4_scroll)
					left_down_x = m_attack4_scroll;
				//ラストウォールの横より画面右端が小さかったら
				//下ろす位置を画面右端にする
				if (right_down_x > m_attack4_scroll + WINDOW_SIZE_W - STAGE5_BOSS_ARMS_WIDTH_SIZE)
					right_down_x = m_attack4_scroll + WINDOW_SIZE_W - STAGE5_BOSS_ARMS_WIDTH_SIZE;

				//腕を下ろす攻撃をする
				m_boos_arm_left->ArmLowerAttack(left_down_x, false);
				m_boos_arm_right->ArmLowerAttack(right_down_x, false);
			}
			//左右の腕が地面まで落ちているかどうかを調べる
			bool left_arm_down = m_boos_arm_left->GetBlockHit();
			bool right_arm_down = m_boos_arm_right->GetBlockHit();

			//両方の腕が地面までおちていれば
			if (left_arm_down == true && right_arm_down == true)
			{
				m_block_down_flag = true;	//ブロックが落ちる様にする
			}
			else
			{
				m_block_down_flag = false;	//ブロックが落ちない様にする
			}

			//落ちるブロックの取得
			CObjFallingBlock* objfallingblock = (CObjFallingBlock*)Objs::GetObjBack(OBJ_FALLING_BLOCK);
			//スクリーン外にブロック出た情報を取得
			bool screen_out_brock = objfallingblock->GetScreenOut();

			//スクリーン外にブロック出た
			if (screen_out_brock == true)
				m_attack4_count++;

			if (m_attack4_count >= 300)//ブロックの無い状態で300フレーム経過すれば
			{
				//腕の位置を初期位置に戻す
				m_boos_arm_left->SetInitPosFlagON();
				m_boos_arm_right->SetInitPosFlagON();

				screen_out_brock = false;//スクリーン内にブロックを戻す
				m_progress_atk4_count = true;//300フレームが経過した

				m_attack4_flag = false;

				m_attack4_count = 0;		//カウンターの初期化
				m_attack4_scroll = 0.0f;	//スクロール量の初期化
				m_attack_mode = 0;
			}
			else
			{
				m_progress_atk4_count = false;//300フレーム経過していない
			}
			break;
		}
		}

		//移動
		m_px += m_vx;

		//当たり判定更新
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

		//ラストウォールと当たったら
		if (hit->CheckObjNameHit(OBJ_LAST_WALL) != nullptr)
		{
			//ラストウォールのヒットフラグオフなら
			if (m_lastwall_hit_flag == false)
			{
				LastWallHit();//ヒット処理を行う
				m_lastwall_hit_flag = true; //ラストウォールのヒットフラグオンにする
			}
		}
		else
			m_lastwall_hit_flag = false;//ラストウォールのヒットフラグオフ

		//主人公の弾丸とぶつかったらＨＰを-1にする
		//弾丸とあたったらＨＰを1減らす
		if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{
			//フラグを立ててタイムを保存
			m_damage_flag = true;
			m_shot_hit_time = m_time;
			m_draw_flag = true;

			m_hp -= 1;
		}

		//ＨＰが0になったら、
		//両腕を消滅させ、HIT_BOXをけし、死亡フラグをONにする
		if (m_hp == 0)
		{
			//両腕を消去する
			m_boos_arm_right->Delete();
			m_boos_arm_left->Delete();

			//BOSSが所有するHitBoxを削除する
			Hits::DeleteHitBox(this);

			//死亡フラグをONにする
			m_death_flag = true;

			Audio::Stop(BOSS);//戦闘音終了

			return;
		}
	}
	//死んでいるとき
	else
	{
		//死亡アニメーションが終了したら自身を消す
		if (ActionDeathAnimation() == false)
		{
			//ステージ５ボス消滅アニメーション後のオブジェクト作成
			CObjAfterBossDisappearance* objafter_boss_disappearance = new CObjAfterBossDisappearance();
			Objs::InsertObj(objafter_boss_disappearance, OBJ_AFTER_BOSS_DISAPPEARANCE, 9);
			this->SetStatus(false);		//自身に削除命令を出す
			return;
		}
	}
}

//ドロー
void CObjStage5Boss::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	float transparent[4] = { 0.0f,0.0f,0.0f, 0.0f };//透明に描画する

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//生きているときの描画
	if(m_death_flag == false)
	{
		//胴体--------------------------------------
		//切り取り位置
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_BODY_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_BODY_SIZE;

		//描画位置
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = STAGE5_BOSS_BODY_SIZE + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE;
		
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
			m_draw_time = 0;
			m_shot_hit_time = 0;
		}

		//描画のフラグがオンなら白く表示
		if (m_draw_flag == true)
			Draw::Draw(GRA_STAGE5_BOSS_WHITE_BODY, &src, &dst, color, 0.0f);
		else
			Draw::Draw(GRA_STAGE5_BOSS_BODY, &src, &dst, color, 0.0f);

		//眼球---------------------------------------
		//切り取り位置
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_EYE_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_EYE_SIZE;

		//描画位置
		dst.m_top = m_py - objmap->GetScrollY() + EYE_CORRECTION_HEIGHT;
		dst.m_left = m_px - objmap->GetScrollX() + EYE_CORRECTION_WIDTH;
		dst.m_right = dst.m_left + STAGE5_BOSS_EYE_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_EYE_SIZE;

		//主人公のオブジェクト情報を取得
		CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

		//眼球を主人公の方へ向くようにする-----------------
		//主人公が生存している場合、角度の計算を行う
		float r = 0.0f;
		if (obj_hero != nullptr)
		{
			float hero_x = obj_hero->GetPosX() - m_px;		//主人公の位置情報X取得
			float hero_y = obj_hero->GetPosY() - m_py;		//主人公の位置情報Y取得
			r = atan2f(-hero_y, hero_x)*180.0f / 3.14f;
			if (r < 0.0f)
			{
				r = 360.0f - abs(r);
			}
		}
		//--------------------------------------------------

		//描画
		Draw::Draw(GRA_STAGE5_BOSS_EYE, &src, &dst, color, r);
	}
	//死んでいるときの描画
	else
	{
		//死亡アニメーションを描画
		DrawDeathAnimation();
	}
}

//ラストウォールと当たったときの処理
void CObjStage5Boss::LastWallHit()
{
	m_vx *= -1.0f;//移動ベクトルを逆にする。
}

//ランダムで値を決める関数
//引数1 int min	:最小値
//引数2 int max	:最大値
//戻り値 int	:最小値～最大値の間の数値をランダムで渡す(最大値、最小値を含む)
int CObjStage5Boss::GetRandom(int min, int max)
{
	//一回だけ初期化をする用
	static bool initialization = true;
	if (initialization == true)
	{
		srand((unsigned)time(NULL));  //乱数系列の変更
		initialization = false;
	}
	return min + (int)(rand()*(max - min + 1.0f) / (1.0f + RAND_MAX));
}

//ボスの死亡アニメーション処理用関数(アクション用)
//戻り値 bool	:アニメーション中	:true
//				 アニメーション終了	:false
/* 　　　　　　　
					詳細

爆発のタイミングが3回ある
イメージ図
下の図([-]のところ)をボス(胴体)全体の画像とする
{
12345678
a--------
b--------
c--------
d--------
e--------
f--------
g--------
h--------
}
ボス(胴体)サイズの爆発：ボス(胴体)の位置でボス(胴体)のサイズで爆発させる
爆発タイミング		  ：ボスが死亡した直後

最初の爆発		：イメージ図の上(b4,b5)下(g4,g5)右(d8,e8)左(d1,e1)辺りを爆発させる
爆発タイミング	：ボスが死亡した直後

2回目の爆発		：イメージ図の左上(b2,b3)右上(b6,b7)左下(g2,g3)右下(g6,g7)辺りを爆発させる
爆発タイミング	：最初の爆発アニメーションの途中(真ん中辺り)

最後の爆発		：最初の爆発と2回目の爆発とイメージ図全体を爆発させる
爆発タイミング	：2回目の爆発アニメーションの途中(真ん中辺り)
*/
bool CObjStage5Boss::ActionDeathAnimation()
{

	//最初の爆発、2回目の爆発、最後の爆発のアニメーションを進めるかどうかを判断する
	for (int i = 0; i < 3; i++)
	{
		if (m_ani_time_death[i] == m_ani_max_time_death[0] && m_ani_frame_death[i] != 16)
		{
			m_ani_time_death[i] = 0;
			m_ani_frame_death[i]++;
		}
	}
	//ボス(胴体)のアニメーションを[薦めるかどうかを判断する
	if (m_ani_time_death[3] == m_ani_max_time_death[1] && m_ani_frame_death[3] != 16)
	{
		m_ani_time_death[3] = 0;
		m_ani_frame_death[3]++;
	}
	//アニメーションフレーム動作間隔(死亡)ーーーーーーーーーーーー
	//ボス(胴体)のサイズの爆発のフレームが16でないならこの動作間隔を進める
	if (m_ani_frame_death[3] != 16)
		m_ani_time_death[3]++;
	//最初の爆発のフレームが16でないなら最初の爆発の動作間隔を進める
	if (m_ani_frame_death[0] != 16)
		m_ani_time_death[0]++;
	//2回目の爆発のフレームが16でないならかつ
	//最初の爆発のフレームが8(真ん中)以上なら2回目の爆発の動作間隔を進める
	if (m_ani_frame_death[1] != 16 && m_ani_frame_death[0] >= 8)
		m_ani_time_death[1]++;
	//最後の爆発のフレームが16でないならかつ
	//2回目の爆発のフレームが８(真ん中)以上なら最後の爆発の動作間隔を進める
	if (m_ani_frame_death[2] != 16 && m_ani_frame_death[1] >= 8)
		m_ani_time_death[2]++;
	//－－－－－－－－－ーーー－－－－－－－－－－－－－－－－－－－

	//ボス(胴体)のサイズの爆発アニメーションが終了していたら
	if (m_ani_frame_death[3] == 16)
		return false;//アニメーションが終了

	return true;//アニメーション動作中
}
//ボスの死亡アニメーション処理用関数(ドロー用)
//詳細はActionDeathAnimation関数を見てください
void CObjStage5Boss::DrawDeathAnimation()
{
	//最初の爆発、2回目の爆発、最後の爆発の描画サイズ
	//各位置を決めるときにも使っています
	float size = 256.0f;

	//最初の爆発のときの位置情報　　左					上					右				下
	float pos_x1[4] = { m_px + 128.0f,	 m_px + 128.0f + size,	m_px + 128.0f + size *  2,	m_px + 128.0f + size };
	float pos_y1[4] = { m_py + 64.0f + size,m_py + 64.0f,		m_py + 64.0f + size,	m_py + 64.0f + size * 2 };

	//2回目の爆発のときの位置情報		左上			右上					左下						右下			
	float pos_x2[4] = { m_px + 128.0f,m_px + 128.0f + size * 2.0f	,m_px + 128.0f			,m_px + 128.0f + size * 2.0f };
	float pos_y2[4] = { m_py + 128.0f,m_py + 128.0f				,m_py + 128.0f + size * 2.0f,m_py + 128.0f + size * 2.0f };

	//最後の爆発	a1,b1～a8,b8 -> c1,d1～c8,d8のような順番で登録
	float pos_x3[16] = { m_px,m_px + size,m_px + size * 2.0f,m_px + size * 3.0f,
		m_px,m_px + size,m_px + size * 2.0f,m_px + size * 3.0f,
		m_px,m_px + size,m_px + size * 2.0f,m_px + size * 3.0f,
		m_px,m_px + size,m_px + size * 2.0f,m_px + size * 3.0f };
	float pos_y3[16] = { m_py,m_py,m_py,m_py,
		m_py + size,m_py + size ,m_py + size ,m_py + size ,
		m_py + size * 2.0f,m_py + size * 2.0f,m_py + size * 2,m_py + size * 2.0f,
		m_py + size * 3.0f,m_py + size * 3.0f,m_py + size * 3,m_py + size * 3.0f };

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//ボス(胴体)サイズの爆発を描画ーーーーーーーーーーーー
	//切り取り位置
	src.m_top = (m_ani_frame_death[3] / 5) * 64.0f;
	src.m_left = (m_ani_frame_death[3] % 5) * 64.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY()-64.0f;
	dst.m_left = m_px - objmap->GetScrollX()-256.0f;
	dst.m_right = dst.m_left + STAGE5_BOSS_BODY_SIZE*3.0f;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE*3.0f;
	//描画
	Draw::Draw(GRA_EXPLOSION, &src, &dst, color, 0.0f);
	//－－－－－－－－－－－－－－－－－－－－－－－－－ー
	//最初の爆発の描画
	//最初の爆発のフレームが16でないなら描画をする
	if (m_ani_frame_death[0] != 16)
	{
		for (int i = 0; i < 4; i++)
		{
			//切り取り位置
			src.m_top = (m_ani_frame_death[0] / 5) * 64.0f;
			src.m_left = (m_ani_frame_death[0] % 5) * 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;

			//描画位置
			dst.m_top = pos_y1[i] - objmap->GetScrollY()-64.0f;
			dst.m_left = pos_x1[i] - objmap->GetScrollX()-320.0f;
			dst.m_right = dst.m_left + size;
			dst.m_bottom = dst.m_top + size;
			//描画
			Draw::Draw(GRA_EXPLOSION, &src, &dst, color, 0.0f);
		}
	}

	//2回目の爆発の描画
	//2回目の爆発のフレームが16でないかつ
	//最初の爆発のフレームが８(真ん中)以上なら描画をする
	if (m_ani_frame_death[1] != 16 && m_ani_frame_death[0] >= 8)
	{
		for (int i = 0; i < 4; i++)
		{
			//切り取り位置
			src.m_top = (m_ani_frame_death[1] / 5) * 64.0f;
			src.m_left = (m_ani_frame_death[1] % 5) * 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;

			//描画位置
			dst.m_top = pos_y2[i] - objmap->GetScrollY()-64.0f;
			dst.m_left = pos_x2[i] - objmap->GetScrollX()-320.0f;
			dst.m_right = dst.m_left + size;
			dst.m_bottom = dst.m_top + size;
			//描画
			Draw::Draw(GRA_EXPLOSION, &src, &dst, color, 0.0f);
		}
	}

	//最後の爆発の描画
	//最後の爆発のフレームが16でないかつ
	//2回目の爆発のフレームが８(真ん中)以上なら描画をする
	if (m_ani_frame_death[2] != 16 && m_ani_frame_death[1] >= 8)
	{
		//切り取り位置
		src.m_top = (m_ani_frame_death[2] / 5) * 64.0f;
		src.m_left = (m_ani_frame_death[2] % 5) * 64.0f;
		src.m_right = src.m_left + 64.0f;
		src.m_bottom = src.m_top + 64.0f;
		for (int i = 0; i < 16; i++)
		{
			//描画位置
			dst.m_top = pos_y3[i] - objmap->GetScrollY()-64.0f;
			dst.m_left = pos_x3[i] - objmap->GetScrollX()-320.0f;
			dst.m_right = dst.m_left + size;
			dst.m_bottom = dst.m_top + size;
			//描画
			Draw::Draw(GRA_EXPLOSION, &src, &dst, color, 0.0f);
		}
		for (int i = 0; i < 4; i++)
		{
			//描画位置
			dst.m_top = pos_y2[i] - objmap->GetScrollY()-64.0f;
			dst.m_left = pos_x2[i] - objmap->GetScrollX()-320.0f;
			dst.m_right = dst.m_left + size;
			dst.m_bottom = dst.m_top + size;
			//描画
			Draw::Draw(GRA_EXPLOSION, &src, &dst, color, 0.0f);
			//描画位置
			dst.m_top = pos_y1[i] - objmap->GetScrollY()-64.0f;
			dst.m_left = pos_x1[i] - objmap->GetScrollX()-320.0f;
			dst.m_right = dst.m_left + size;
			dst.m_bottom = dst.m_top + size;
			//描画
			Draw::Draw(GRA_EXPLOSION, &src, &dst, color, 0.0f);
		}
	}
}