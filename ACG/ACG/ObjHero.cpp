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
//引数1 x			:初期ポジションX
//引数2	y			:初期ポジションY
//引数3	remaining	:残機数
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
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	m_count++;//カウンターを増やす

	if (m_count >= 10000)//カウントが一定数になると0に戻る
	{
		m_count = 50;//カウントの初期化
		
		//弾の制御を変数を更新
		m_before_shot_time = SHOT_INTERVAL - (10000 - m_before_shot_time) ;
	}

	GetBlockInformation();	//主人公の左下、真下、右下にあるブロック情報を取得
	
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
	objblock->AllBlockHit(&m_px, &m_py, 46.0f, HERO_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
		
	LandingCheck();//着地フラグの更新

	LadderScene();//梯子処理

	MoveScene();//移動

	Scroll();//スクロール

	Shot();//発砲

	RopeThrow();//ロープ射出

	HitScene();	//当たり判定

	if (m_posture == 0.0f)
	{
		//HitBoxの位置を更新する
		HitBoxUpData(Hits::GetHitBox(this), m_px+3, m_py + 14);
	}
	else
	{
		//HitBoxの位置を更新する
		HitBoxUpData(Hits::GetHitBox(this), m_px+15, m_py + 14);
	}
}

//主人公の左下、真下、右下にあるブロック情報を取得
void CObjHero::GetBlockInformation()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

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
			m_block_type_up = objmap->GetMap(x, y - 1); //主人公の上のマップ番号を取る
		}
	}
}

//移動関数
void CObjHero::MoveScene()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//ロープオブジェクト情報を持ってくる
	CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
	
	//ロープを出している時かロープがターザンポイントに引っかかっている
	if (m_rope_ani_con == false || (objrope != nullptr && objrope->GetTarzanPointFlag() == true))
	{
		//水に当たった時と敵に当たった時は動かない
		if (m_hero_die_water == false && m_ani_frame_enemy_die == false && m_py < 2000.0f)
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
	if (Input::GetVKey(VK_SPACE) == true && m_ladder_updown == 0 &&
		m_rope_ani_con == false && m_hero_die_water == false &&
		m_ani_frame_enemy_die == false && l_jump == false)
	{
		if (m_hit_down == true)
		{
			m_vy = -13.0f;
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

	//ロープオブジェクトが有る かつ ターザンポイントに引っかかっているなら
	//ロープの位置を中心に振り子の動きをする
	if ((objrope != nullptr && objrope->GetTarzanPointFlag() == true))
	{
		float ab_x = objrope->GetPosX() - m_px;//主人公からロープのベクトルX成分
		float ab_y = objrope->GetPosY() - m_py;//主人公からロープのベクトルY成分

		//ロープの位置
		float rope_x = objrope->GetPosX(), rope_y = objrope->GetPosY();

		//振り子データの値を求めるかどうかフラグがNOのとき
		//値(長さ、ふり幅、周期)を求める
		if (pendulum_data.find_value_flag == true)
		{
			//振り子の糸の長さを計算
			pendulum_data.length = sqrt((ab_x * ab_x) + (ab_y * ab_y));

			//振り子の糸の長さから今何時(周期)なのかを求める					↓重力加速度が0.98なのを9.8に直している
			//振り子の等時性
			pendulum_data.time = 2.0f*3.141592f*sqrt(pendulum_data.length / (pendulum_data.gravity * 10.0f));

			//ロープのX位置より主人公が右にいたら時間(周期をーにする)
			if (m_px > rope_x)
				pendulum_data.time *= -1;

			//ふり幅を計算		自作で調整しています　求め方があるのでしたらそれにしてください。
			pendulum_data.pretend_width = pendulum_data.length / 7.0f;

			//ふり幅を一定数を超えないようにする
			if (pendulum_data.pretend_width > 50.0f)
				pendulum_data.pretend_width = 50.0f;
			//値を求めたのでフラグをOFFにする
			pendulum_data.find_value_flag = false;
		}
		//ロープから主人公のベクトルの角度を計算
		float r = 2 * pendulum_data.pretend_width*sinf(sqrt(pendulum_data.gravity / pendulum_data.length)*pendulum_data.time);

		r = r * 3.14f / 180.0f;//ラジアン度にする

		//ブロックに当たっていなかったら移動ベクトルを求め周期を進める
		if (!m_hit_down && !m_hit_left && !m_hit_right && !m_hit_up)
		{
			//移動ベクトルを計算			　						↓の計算は移動ベクトルだけを取りたかったから
			m_vx = cosf(r) - sinf(r) * pendulum_data.length + (rope_x - m_px);
			m_vy = sinf(r) + cosf(r) * pendulum_data.length + (rope_y - m_py);
			//周期を進める
			pendulum_data.time += 1.0f;
		}
		//ブロックに当たっている==振り子の運動停止しているなら
		//もう一度値を求めたいのでフラグをONにする
		else
			pendulum_data.find_value_flag = true;
		
	}
	//ロープがターザンポイントに引っかかっていなかったら
	//値を求めるフラグをONにする
	else
		pendulum_data.find_value_flag = true;
	
	//移動
	m_px += m_vx;
	m_py += m_vy;

	//移動先が画面外なら移動を元に戻す
	if (WindowCheck(m_px - HERO_SIZE_WIDTH, m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT) == false)
		m_px -= m_vx;

	//腕の角度を求める-----------------------

	//マウスポインタとの距離を求める

	float x = m_mous_x - (m_px - objmap->GetScrollX() + (HERO_SIZE_WIDTH / 2.0f));	//X
	float y = m_mous_y - (m_py - objmap->GetScrollY() + (HERO_SIZE_HEIGHT / 2.0f));//Y
	float inclination = sqrt(x * x + y * y);				//斜辺


	if (y > 0.0f)	//yの値が0より大きいなら角度を正しい値に修正
		m_r = 360.0f - m_r;

	//ラジアン値を求める
	float rad = asinf(-y / inclination);
	//角度を求める
	m_r = rad * 180.0f / 3.14f;
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
	float one_side = 5.5f;

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
			//ステージ５ならクリアのシーンにする
			if (((UserData*)Save::GetData())->stagenum == 5)
			{
				Scene::SetScene(new CSceneGameClear());
				return;
			}
			else
			{
				//ステージカウントを増やして次のステージにする
				Objs::ListDeleteSceneObj();//オブジェクトの削除
				((UserData*)Save::GetData())->stagenum += 1;
				Scene::SetScene(new CSceneMain());
			}
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
	bool c1,c2,c3,c4,c5,c6,c7;//チェック結果を保存するための変数:チェック項目を増やすたびに数を増やす必要がある
	
	c1 = HitUpCheck(OBJ_LIFT); //リフトとの着地チェック
	c2 = HitUpCheck(OBJ_WOOD); //木との着地チェック
	c3 = HitUpCheck(OBJ_LIFT_MOVE); //動くリフトとの着地チェック
	c4 = HitUpCheck(OBJ_ROLL_BLOCK);//回転するブロック
	c5 = HitUpCheck(OBJ_FALLING_LIFT);//落ちるリフト
	c6 = HitUpCheck(OBJ_FALLING_BLOCK);//落ちるブロック
	c7 = HitUpCheck(OBJ_WIRE_MESH);//金網
	//チェック項目のどれか一つでもtrueなら
	if ( c1 == true || c2 ==true || c3 == true || c4 ==true || c5 == true || c6 == true||c7==true)
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

//梯子関数
void CObjHero::LadderScene()
{
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
		l_jump = objladders->GetHeroJumpCon();  //はしごと接触しているかどうかを調べる
		objladders->HeroHit(m_px, m_py);
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
}

//ロープ投げる関数
void CObjHero::RopeThrow() {

	//Scene　開店準備 
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//ロープオブジェクトを持ってくる
	CObjRope* obj_rope = (CObjRope*)Objs::GetObj(OBJ_ROPE);

	bool rope_caught = false; //ロープがロープスイッチと当たっているかどうかを確かめる変数
	bool rope_delete = false; //ロープが消えてるか同うかを確かめる変数

							  //マウスの位置がプレイヤーから見てどの方向か調べるための変数
	float mous_rope_way = 0.0f;//右：0.0ｆ　左：1.0ｆ 右向きで初期化

	if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//主人公より左をクリックしたとき
		mous_rope_way = 1.0f;

	//右クリックを押したらの部分を上に変更したのでマージする時は元の奴を消してこっちを残してください
	//右クリックを押したら   水に当たっているときと敵に当たっているときは動かない
	if (Input::GetMouButtonR() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
	{
		//主人公をクリックしていた場合
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//ヒーロークリックした場合
		}
		//マウスの位置が後ろじゃない　ロープアニメのフラグがなし　ロープの削除フラグがなし
		else if (m_posture == mous_rope_way && m_rope_ani_con == false && m_rope_delete_r_kye == false)
		{
			m_rope_moux = (float)Input::GetPosX(); //ロープを射出したときのマウスの位置Xを入れる
			m_rope_mouy = (float)Input::GetPosY(); //ロープを射出したときのマウスの位置Yを入れる
			m_rope_ani_con = true;

		}
	}

	if (obj_rope != nullptr)//ロープオブジェクトが出ている場合
	{
		rope_caught = obj_rope->GetCaughtFlag();//ロープがロープスイッチに当たっているかの情報をもらう
		rope_delete = false; //ロープは消えていない
		m_rope_delete_control = true;
	}
	else //ロープオブジェクトが出ていない場合
	{
		rope_caught = false;
		//ロープを消せるようにする
		if (m_rope_delete_control == true)
		{
			rope_delete = true; //ロープが消える
			m_rope_delete_control = false;
		}
	}

	//trueならアニメーションを進める 　はしごに登っているときは動かない
	if (m_rope_ani_con == true && m_ladder_updown == 0)
	{
		//ロープのアニメーションフレームが2以外ならアニメーションを進める
		if (m_ani_frame_rope != 2)
		{
			//ロープのアニメーションタイムを進める
			m_ani_time_rope += 1;

			//ロープのMAXTIMEを超えるとアニメーションを進める
			if (m_ani_time_rope > m_ani_max_time_rope)
			{
				m_ani_frame_rope += 1;
				m_ani_time_rope = 0;
			}
		}
		//ロープのアニメーションフレームが２ならロープを出す
		if (m_ani_frame_rope == 2)
		{
			if (m_rope_control == true)//trueならロープを出せる
			{
				//ロープ作成
				if (m_posture == 0.0f)//主人公が右を向いているとき右側から発射
				{
					CObjRope* objrope = new CObjRope(m_px + 64.0f, m_py + 80.0f, m_rope_moux, m_rope_mouy);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
					Audio::Start(ROPE);//ロープの音楽スタート
				}
				else if (m_posture == 1.0f)//主人公が左を向いているとき左側から発射
				{
					CObjRope* objrope = new CObjRope(m_px, m_py + 80.0f, m_rope_moux, m_rope_mouy);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
					Audio::Start(ROPE);//ロープの音楽スタート
				}
			}
			if (m_rope_control == false) //ロープを出している時
			{
				m_ani_frame_rope = 2;//アニメーションを２で止める
				if (rope_delete == true)//ロープが消えている場合
				{
					m_rope_delete_r_kye = true;
					m_ani_frame_rope = 0;//アニメーションのフレームを戻す。
					m_rope_ani_con = false;
				}
			}
		}
		else
			m_rope_control = true;
	}
	//はしごに登っているときに右クリックしたら上り終わった後に撃っていたのでそれを修正する
	else if (m_ladder_updown != 0)
	{
		m_rope_ani_con = false;
	}

	//右クリックしていないときfalseにする
	if (Input::GetMouButtonR() == false)
		m_rope_delete_r_kye = false;

	//ロープとロープスイッチが当たっているとき
	if (rope_caught == true)
	{
		m_rope_delete_r_kye = true; //ロープを消せるようにする（ロープ側で処理）
	}
}

void CObjHero::Shot()
{
	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//左クリックを押したら   水に当たっているときと敵に当たっている時は動かない
	if (Input::GetMouButtonL() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
	{
		//主人公をクリックしていた場合
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//ヒーロークリックした場合
		}
		else
		{
			//マウスの位置がプレイヤーから見てどの方向か調べるための変数
			float mous_bullet_way = 0.0f;//右：0.0ｆ　左：1.0ｆ 右向きで初期化

			if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//主人公より左をクリックしたとき
				mous_bullet_way = 1.0f;

			if (m_bullet_control == true)
			{
				//向いている方向とクリックしている方向が同じで尚且つ、ロープのアニメーションのフラグがfalseの場合
				if (m_posture == mous_bullet_way && m_rope_ani_con == false)
				{
					// 弾丸発射向き(度数法)
					float m_bullet_r;

					if (m_posture == 0.0f && m_ladder_updown == 0)//主人公が右を向いていてはしごに登っていない時とき右側から発射
					{
						// 弾丸発射位置を計算するための角度調整
						if (m_r > 0.f)
							m_bullet_r = 360.0f - m_r;
						else
							m_bullet_r = -m_r;

						// 弾丸の角度から発射位置のずれを求める(*50.0fは腕の回りによる円の半径)
						float x_add = cosf(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sinf(m_bullet_r* 3.14f / 180.f) * 50.0f;

						//弾丸作成
						Audio::Start(FIRING);//音楽スタート

						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 30.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);

						m_bullet_control = false; //弾丸を出ないフラグにする。
						m_before_shot_time = m_count;//弾を撃った時間を記憶する
					}
					else if (m_posture == 1.0f && m_ladder_updown == 0)//主人公が左を向いていてはしごに登っていない時とき右側から発射
					{
						// 弾丸発射位置を計算するための角度調整
						if (abs(m_r) > 90.0f)
							m_bullet_r = m_r;
						else
							m_bullet_r = 180.0f + m_r;

						// 弾丸の角度から発射位置のずれを求める(*50.0fは腕の回りによる円の半径)
						float x_add = cosf(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sinf(m_bullet_r* 3.14f / 180.f) * 50.0f;

						Audio::Start(FIRING);//音楽スタート

						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 20.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);

						m_bullet_control = false; //弾丸を出ないフラグにする。
						m_before_shot_time = m_count;//弾を撃った時間を記憶する
					}
				}
			}
		}
	}
	else
	{
		//前回のshotから一定時間経過していれば
		if (m_count - m_before_shot_time >= SHOT_INTERVAL)
			m_bullet_control = true; //左クリックしてなければ弾丸をでるフラグにする。
	}
}

//当たり判定の関数
void CObjHero::HitScene()
{
	//自身のHitBoxをもってくる
	CHitBox*hit = Hits::GetHitBox(this);

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
}