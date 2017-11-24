#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"
#include <math.h>

//使用するネームスペース
using namespace GameL;

//コンストラクタ
//引数1,2　初期ぽじしょん
//引数3	残機数
CObjHero::CObjHero(int x, int y, int remaining)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	//残機数の初期化
	m_remaining = remaining;	
}

//アクション
void CObjHero::Action()
{

	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//主人公の左下、真下、右下にあるブロック情報を取得
	//真下のブロック情報を優先する
	for (int i = 0; i < 3; i++)
	{
		//主人公のX位置(左下 = 0;真下 = HERO_SIZE_WIDTH/2;右下 = HERO_SIZE_WIDTH)
		int pos_x = 0;
		//右下
		if (i == 1)
		{
			pos_x = (int)HERO_SIZE_WIDTH;
		}
		//左下
		else if (i == 2)
		{
			pos_x = (int)HERO_SIZE_WIDTH / 2;
		}
		//主人公のX位置(マップの要素数)
		int x = ((int)m_px + pos_x) / (int)BLOCK_SIZE;
		//主人公のY位置(マップの要素数)
		//少し下にする
		int y = ((int)m_py + 1 + (int)HERO_SIZE_HEIGHT) / (int)BLOCK_SIZE;
		//ブロック情報が0で無いなら取得
		if (objmap->GetMap(x, y) != 0)
		{
			m_block_type = objmap->GetMap(x, y);
		}
	}
	//落下にリスタート----------------------------------
	//m_pyが2000以下ならリスタートする
	if (m_hero_die_screen_out == true)
	{
		//場外に出たらリスタート
		Scene::SetScene(new CSceneMain(-1));
	}

	//マウスの位置情報取得
	m_mous_x = (float)Input::GetPosX();
	m_mous_y = (float)Input::GetPosY();

	//ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブロックとの当たり判定
	objblock->AllBlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	LandingCheck();//着地フラグの更新


	//はしご-------------------------------------------------LadderScene()
	//はしごオブジェクトを持ってくる
	CObjLadders* objladders = (CObjLadders*)Objs::GetObj(OBJ_LADDERS);

	if (objladders != nullptr)
	{
		//主人公のしたに通常ブロックがあったらはしごに上っていない判定にする
		if (m_block_type == MAP_BLOCK)
		{
			//はしごに登っていない
			m_ladder_updown = 0;
		}

		objladders->HeroHit(m_px, m_py);//はしごと接触しているかどうかを調べる
	}

	//はしごのアニメーションタイムを進める
	m_ani_time_ladders += m_ladder_ani_updown;//はしごから取ってくる

	//はしごのMAXTIMEを超えるとアニメーションを進める
	if (m_ani_time_ladders > m_ani_max_time_ladders)
	{
		m_ani_frame_ladders += 1;
		m_ani_time_ladders = 0;
	}

	//最後までアニメーションが進むと最初に戻る
	if (m_ani_frame_ladders == 4)
	{
		m_ani_frame_ladders = 0;
	}


	//はしご終了---------------------------------------------

	//移動ーーーーーーーーーーーーーーーーーーーーーーーーーーーーMoveScene
	//ロープを出している時と水に当たった時と敵に当たった時は動かない
	if (m_rope_ani_con == false && m_hero_die_water == false && m_ani_frame_enemy_die == false && m_py < 2000.0f)
	{
		//Dキーがおされたとき：右移動　
		if (Input::GetVKey('D') == true)
		{
			m_vx += 0.5f;
			m_ani_frame_stop_move = 0;  //主人公が動いてるなら0にする
			m_posture = 0.0f;		    //主人公の向き
			m_ani_time_move += 1;
		}
		//Aキーがおされたとき：左移動　
		else if (Input::GetVKey('A') == true)
		{
			m_vx -= 0.5f;
			m_ani_frame_stop_move = 0;  //主人公が動いてるなら0にする

			if (m_ladder_updown == 1)   //はしごに登ってるときは向きを変えない
				m_posture = 0.0f;		//主人公の向き
			else
				m_posture = 1.0f;		//主人公の向き
			m_ani_time_move += 1;
		}
		else
		{
			m_ani_frame_stop_move = 1;	//キー入力が無い時は1を入れる
			m_ani_frame_move = 1;		//キー入力が無い場合は静止フレームにする
			m_ani_time_move = 0;
		}
	}

	//アニメーションの感覚管理
	if (m_ani_time_move > m_ani_max_time_move)
	{
		m_ani_frame_move += 1;
		m_ani_time_move = 0;
	}

	//最後までアニメーションが進むと最初に戻る
	if (m_ani_frame_move == 4)
	{
		m_ani_frame_move = 0;
	}

	//ジャンプ--------------------------------------------------------------------
	//ロープを出している時は動かない  はしごを上っている時も動かない　　水に当たっているときと敵と当たった時も動かない
	if (Input::GetVKey(VK_SPACE) == true &&
		m_rope_ani_con == false && m_hero_die_water == false &&
		m_ani_frame_enemy_die == false)
	{
		if (m_hit_down == true)
		{
			m_vy = -17.0f;
		}
	}

	//ジャンプ終了-------------------------------------------------------------------------------------


	//↓キーがおされたとき：下に下がる（デバッグ）
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy = 20.0f;
	}
	//↑キーがおされたとき：上に下がる（デバッグ）
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vy = -20.0f;
	}

	//摩擦
	m_vx += -(m_vx * 0.098f);

	//自由落下運動
	// フラグがたっていたら重力をかける
	if (m_gravity_flag == true)
		m_vy += 9.8f / (16.0f);

	//最大落下スピードを超えないようにする
	if (m_gravity_flag == true && m_vy > m_fall_speed_max)
		m_vy = m_fall_speed_max;

	Scroll();	//スクロール処理をおこなう

	//移動
	m_px += m_vx;
	m_py += m_vy;

	//移動終わり-----------------------------------------


	//腕の角度を求める-----------------------

	//マウスポインタとの距離を求める

	float x = m_mous_x - (m_px - objmap->GetScrollX() + (HERO_SIZE_WIDTH / 2.0f));	//X
	float y = m_mous_y - (m_py - objmap->GetScrollY() + (HERO_SIZE_HEIGHT / 2.0f));//Y
	float inclination = sqrt(x * x + y * y);				//斜辺

	////角度を求める
	//float rad = acosf(x / inclination);
	//m_r = rad* 180.0f / 3.14f;

	if (y > 0.0f)	//yの値が0より大きいなら角度を正しい値に修正
		m_r = 360.0f - m_r;

	//ラジアン値を求める
	float rad = asinf(-y / inclination);
	//角度を求める
	m_r = rad * 180.0f / 3.14f;
	//--------------------------------------------------------


	//発砲---------------------------------------------------Shot()
	Shot();

	//ロープ射出---------------------------------------------RopeThrow
	RopeThrow();

	//-------HitScene()
	//針オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_NEEDLE) != nullptr)
	{
		m_hero_die_enemy = true; //主人公の針にあたったときの死亡フラグをONにする
	}
	//水オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		m_hero_die_water = true; //主人公の水にあたったときの溺れるフラグをONにする
	}

	//敵オブジェクトと衝突していれば
	if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		m_hero_die_enemy = true; //主人公の敵にあたったときの死亡フラグをONにする
	}

	//主人公の敵に当たったときの死亡フラグがONなら死亡アニメーションをする
	if (m_hero_die_enemy == true)
	{
		//主人公が敵に当たった時のアニメーションタイムを進める
		m_ani_time_enemy_die += 1;
		//アニメーションの感覚管理
		if (m_ani_time_enemy_die > m_ani_max_time_enemy_die)
		{
			m_ani_frame_enemy_die += 1;
			m_ani_time_enemy_die = 0;
		}

		//最後までアニメーションが進むと主人公削除
		if (m_ani_frame_enemy_die == 4)
		{
			this->SetStatus(false);		//自身を削除
			Hits::DeleteHitBox(this);	//ヒットボックスを削除

			return;
		}
	}

	//主人公の水に当たったときの溺れるフラグがONなら溺れるアニメーションをする
	if (m_hero_die_water == true)
	{
		//落ちるのをゆっくりにする（自由落下のおかげでゆっくりになる）
		m_vy = 0.0f;
		//主人公が水に当たった時のアニメーションタイムを進める
		m_ani_time_water_die += 1;
		//アニメーションの感覚管理
		if (m_ani_time_water_die > m_ani_max_time_water_die)
		{
			m_ani_frame_water_die += 1;
			m_ani_time_water_die = 0;
		}

		//最後までアニメーションが進むと主人公削除
		if (m_ani_frame_water_die == 3)
		{
			this->SetStatus(false);		//自身を削除
			Hits::DeleteHitBox(this);	//ヒットボックスを削除

			return;
		}
	}
	
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py + 14);
}

//スクロール処理の関数
void CObjHero::Scroll()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//右にスクロールです
	//原点を右にする
	if ((m_px + HERO_SIZE_WIDTH) - objmap->GetScrollX() > SCROLL_LINE_RIGHT)
	{
		//差分を調べる
		float scroll =  ((m_px + HERO_SIZE_WIDTH) - objmap->GetScrollX())-SCROLL_LINE_RIGHT;
		//スクロールに影響を与える
		objmap->SetScrollX(scroll);
	}
	//左にスクロールです
	if (m_px - objmap->GetScrollX() < SCROLL_LINE_LEFT &&
		objmap->GetScrollX() > 0)
	{
		//差分を調べる
		float scroll = SCROLL_LINE_LEFT - (m_px - objmap->GetScrollX());
		//スクロールに影響を与える
		objmap->SetScrollX(-scroll);
	}

	//上にスクロールです
	if (m_py - objmap->GetScrollY() < SCROLL_LINE_UP)
	{
		//差分を調べる
		float scroll = (m_py - objmap->GetScrollY()) - SCROLL_LINE_UP;
		//スクロールに影響を与える
		objmap->SetScrollY(scroll);
	}
	
	//下にスクロールです
	//原点を下にする
	if ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY() > SCROLL_LINE_DOWN&& objmap->GetScrollY() < WINDOW_SIZE_H)
	{
		//差分を調べる
		float scroll = SCROLL_LINE_DOWN - ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY());
		//スクロールに影響を与える
		objmap->SetScrollY(-scroll);
	}
}

//ドロー
void CObjHero::Draw()
{
	//画像の切り取り配列
	int AniData[4] =
	{
		1 , 0 , 1 ,2
	};

	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//ロープオブジェクトを持ってくる
	CObjRope* obj_rope = (CObjRope*)Objs::GetObj(OBJ_ROPE);

	// ロープとロープスイッチが当たっているかどうかを入れる変数
	bool rope_caught;

	if (obj_rope != nullptr)//ロープオブジェクトが出ている場合
		rope_caught = obj_rope->GetCaughtFlag();//ロープがロープスイッチに当たっているかの情報をもらう
	else
		rope_caught = false;


	//腕---------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 64.0f;
	src.m_right = 128.0f;
	src.m_bottom = 64.0f;

	//描画位置 
	dst.m_top = m_py - objmap->GetScrollY() + 48.0f;
	//　主人公が右を向いている時の腕の描画位置
	if(m_posture == 0.0f)
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	//　主人公が右を向いている時の腕の描画位置
	if (m_posture == 0.0f)
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);

	dst.m_bottom = dst.m_top + 64.0f;

	//描画    ロープが出てる時、はしごに登ってる時、ロープとロープスイッチが当たっている時  主人公が水に当たった時
	if (m_rope_ani_con == true || m_ladder_updown != 0 || rope_caught == true || m_hero_die_water == true || m_hero_die_enemy == true)
	{
		;    // 何も描画しない
	}
	else
		Draw::Draw(GRA_HERO, &src, &dst, color, m_r, -0.2f, -0.4f);
	//-----------------------------------------


	//本体---------------------------------
	//切り取り位置
	//敵に当たった時
	if(m_hero_die_enemy == true)
	{
		//敵があたって立ちの時のアニメーション
		if (m_ani_frame_enemy_die == 0 || m_ani_frame_enemy_die == 1)
		{
			src.m_top = 832.0f;
			src.m_left = 0.0f + m_ani_frame_enemy_die * 64;
			src.m_right = 64.0f + m_ani_frame_enemy_die * 64;
			src.m_bottom = 958.0f;
		}
		//フレームが２と３の時倒れるアニメーション
		else if (m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3) 
		{
			if (m_ani_frame_enemy_die == 2)
			{
				src.m_top = 960.0f;
				src.m_left = 0.0f ;
				src.m_right = 128.0f ;
				src.m_bottom = 1024.0f;
			}
			else
			{
				src.m_top = 960.0f;
				src.m_left = 0.0f + 128;
				src.m_right = 128.0f + 128;
				src.m_bottom = 1024.0f;
			}
		}
	}

	//水にあたった時
	else if (m_hero_die_water == true )
	{
		//フレームが0か1ならもがくアニメーション
		if (m_ani_frame_water_die == 0 || m_ani_frame_water_die == 1)
		{
			src.m_top = 640.0f;
			src.m_left = 0.0f + m_ani_frame_water_die * 64;
			src.m_right = 64.0f + m_ani_frame_water_die * 64;
			src.m_bottom = 768.0f;
		}
		else if (m_ani_frame_water_die == 2) //フレームが2なら倒れるアニメーション
		{
			src.m_top = 769.0f;
			src.m_left = 0.0f;
			src.m_right = 128.0f;
			src.m_bottom = 826.0f;
		}
	}
	else if (m_ladder_updown == 1)//はしごに上っている時
	{
		src.m_top = 256.0f;
		src.m_left = 0.0f + m_ani_frame_ladders * 64;
		src.m_right = 64.0f + m_ani_frame_ladders * 64;
		src.m_bottom = 384.0f;
	}
	else if (m_ladder_updown == 2)//はしごを上りきるとき
	{
		src.m_top = 256.0f;
		src.m_left = 256.0f;
		src.m_right = 320.0f;
		src.m_bottom = 384.0f;
	}
	else if (m_rope_ani_con == true || rope_caught == true) //ロープを投げるとき
	{
		src.m_top = 515.0f;
		src.m_left = 0.0f + m_ani_frame_rope * 64;
		src.m_right = 64.0f + m_ani_frame_rope * 64;
		src.m_bottom = 640.0f;
	}
	else if (m_ladder_updown == 0 && m_hit_down == false && rope_caught == false)  //ジャンプしている時
	{
		src.m_top = 128.0f;
		src.m_left = 256.0f;
		src.m_right = 320.0f;
		src.m_bottom = 256.0f;
	}
	else if (m_ani_frame_stop_move == 1 && m_ladder_updown == 0 && rope_caught == false)  //止まっているとき
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 128.0f;
	}
	else if (m_ani_frame_stop_move == 0 && m_ladder_updown == 0 && rope_caught == false)//動いているとき
	{
		src.m_top = 129.0f;
		src.m_left = 0.0f + AniData[m_ani_frame_move] * 64;
		src.m_right = 64.0f + AniData[m_ani_frame_move] * 64;
		src.m_bottom = 256.0f;
	}
	
	//描画位置
	//   水にあった時主人公が倒れてる時　　敵に当たって倒れている時
	if (m_ani_frame_water_die == 2 || m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3)  //水にあたった時のアニメーションで横に倒れるフレーム用
	{
		dst.m_top = 64.0f + m_py - objmap->GetScrollY();
		dst.m_left = (128.0f * m_posture) + m_px - objmap->GetScrollX() - 64.0f;
		dst.m_right = (128.0f - 128.0f * m_posture) + m_px - objmap->GetScrollX() -64.0f;
		dst.m_bottom = dst.m_top + 64.0f;
	}
	else
	{
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + HERO_SIZE_HEIGHT;
	}

	//描画
	Draw::Draw(GRA_HERO, &src, &dst, color, 0.0f);
	//本体-------------------------------------


	////画面全体を暗くするです。
	//Draw::SetFill(true);
	////画面全体をこの色にする
	////staticなのは消すかもしれないから
	//static float col[4] = { 0.0f };
	//col[0] -= 0.001f;
	//col[1] -= 0.001f;
	//col[2] -= 0.001f;
	//Draw::SetColor(col);

	//画面全体をだんだん暗くする処理----------------------------------
	//死んだことが確定した場合
	if (m_hero_die_water == true || m_hero_die_enemy == true || m_py > 2000.0f)
	{
		// 黒色
		float radius_color[4] = { 0.f, 0.f, 0.f, 1.f };
		// 円描画
		CircleDraw(-11.0f, radius_color, Die);
	}
	//----------------------------------------------------------------

	//---円の中から白くする処理----------------------------------------
	// ゴールした時
	if (m_goal_flag == true)
	{
		// 白色
		float radius_color[4] = { 1.f, 1.f, 1.f, 1.f };
		// 円描画
		CircleDraw(20.0f, radius_color, Clear);
	}
	//-----------------------------------------------------------------

	//残機描画----------------------------------------------------------

	//残機数を描画する
	wchar_t str2[128];//描画する用のwchar_t型を宣言
	swprintf_s(str2, L"×%d", m_remaining);//int型をwcahr_t型に変換
	Font::StrDraw(str2, 48, 15, 30, color);//描画

	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 48.0f;
	dst.m_bottom = 50.0f;

	//描画
	Draw::Draw(GRA_LIFE, &src, &dst, color, 0.0f);
}

// 引数1 float : 円の1フレームごとの半径の変化量
// 引数2 color : 円の色
// 引数3 type  : 円の処理別
// 死亡時とゴール時用の円を描画する関数
void CObjHero::CircleDraw(float add_radius, float color[4], int type)
{
	// マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	// 中央のｙ位置の初期化
	float ball_y = 0.0f;

	//中央位置設定       
	float ball_x = m_px + HERO_SIZE_WIDTH / 2.f - objmap->GetScrollX();

	// Heroが死んでいたら
	if (type == Die)
	{
		//落下時の中央位置 
		if (m_hero_die_flag == false)
		{
			m_screen_out = m_py; //暗くなる中央の位置が主人公を追わなくするため
			m_hero_die_flag = true;
		}

		//落下時の半径の中央位置
		if (m_py > 2000.0f)
			ball_y = m_screen_out - 1450.0f + HERO_SIZE_HEIGHT / 1.5f;
		//落下時以外の半径の中央位置
		else if (m_py < 2000.0f)
			ball_y = m_py + HERO_SIZE_HEIGHT / 1.5f - objmap->GetScrollY();
	}
	// Heroがステージをクリアしている状態なら
	else if (type == Clear)
	{
		ball_y = m_py + HERO_SIZE_HEIGHT / 1.5f - objmap->GetScrollY();
	}

	//半径をだんだん短くする
	m_radius += add_radius;
	
	//正四角形の１辺の長さ
	//長ければ長いほど軽く
	//短ければ短いほど重いよ
	float one_side = 6.0f;

	//半径が最小になったらシーン移行する（上のほうにある）
	// Heroが死んでいたら
	if (type == Die)
	{
		// 半径が0以下ならリスタート
		if (m_radius <= 0.0f)
		{
			m_radius = 0.0f;
			Scene::SetScene(new CSceneMain(-1)); // リスタート
		}
	}
	// Heroがステージをクリアしている状態なら
	else if (type == Clear)
	{
		// 半径が一定値を超えたらシーン移行
		if (m_radius >= 768.0f)
		{
			//ステージカウントを増やして次のステージにする
			((UserData*)Save::GetData())->stagenum += 1;
			Scene::SetScene(new CSceneMain());
		}
	}


	//円外を四角形で埋め尽くす
	for (float y = 0.0f; y < (float)WINDOW_SIZE_H; y += one_side)
	{
		for (float x = 0.0f; x < (float)WINDOW_SIZE_W; x += one_side)
		{
			//円の中
			if ((x - ball_x)*(x - ball_x) + (y - ball_y)*(y - ball_y) <= m_radius * m_radius)
			{
				if (type == Clear) // 円の中を塗る
					Draw::DrawHitBox(x, y, one_side, one_side, color);
			}
			//円外
			else
			{
				if (type == Die)	// 円の外を塗る
					Draw::DrawHitBox(x, y, one_side, one_side, color);
			}
		}
	}
}

//着地できてるかどうかを調べる関数
void CObjHero::LandingCheck()
{
	bool c1,c2,c3,c4;//チェック結果を保存するための変数:チェック項目を増やすたびに数を増やす必要がある
	
	c1 = HitUpCheck(OBJ_LIFT); //リフトとの着地チェック
	c2 = HitUpCheck(OBJ_WOOD); //木との着地チェック
	c3 = HitUpCheck(OBJ_LIFT_MOVE); //動くリフトとの着地チェック
	c4 = HitUpCheck(OBJ_ROLL_BLOCK);//回転するブロック

	//チェック項目のどれか一つでもtrueなら
	if ( c1 == true || c2 ==true || c3 == true || c4 ==true)
		m_hit_down = true;//着地フラグをオンにする

}

//指定したオブジェクトの上側に当たっているかしらべる
//引数　調べたいオブジェクトネーム
//戻り値　着地していれば:true　していなければ:false
bool CObjHero::HitUpCheck(int obj_name)
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);
	
	//引数で持ってきたオブジェクトとあたっているか調べる
	if (hit->CheckObjNameHit(obj_name) != nullptr)
	{
		HIT_DATA** hit_data;	//衝突の情報を入れる構造体
		hit_data = hit->SearchObjNameHit(obj_name);//衝突の情報をhit_dataに入れる

		//あたっている数分調べる
		for (int i = 0; i < hit->GetCount(); i++)
		{
			//データがあれば
  			if (hit_data[i] != nullptr)
			{
				//衝突した相手の位置、幅、高さ情報を取得
				HIT_BOX* hit = Hits::GetHitBox(hit_data[i]->o)->GetHitBox();
				//マップオブジェクトを持ってくる
				CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

				//HitTestOfAB関数を使うと変更されてしまうので仮変数作成
				float hero_x = m_px;
				float hero_y = m_py;
				float hero_vx = m_vx;
				float hero_vy = m_vy;
				//衝突した方向を取得
				int collision = HitTestOfAB(hit->x+objmap->GetScrollX(), hit->y+objmap->GetScrollY(), hit->w, hit->h,
					&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
					&hero_vx, &hero_vy
				);
				//主人公から見て下に衝突したら着地している
				if (collision == 2)
					return true;
			}
		}
	}
	return false;//着地していない
}

