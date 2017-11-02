#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"
#include <math.h>

//使用するネームスペース
using namespace GameL;


//コンストラクタ
CObjHero::CObjHero(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjHero::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_posture = 0.0f;			 //右向き0.0f 左向き1.0f
	m_r = 0.0f;
	m_rope_delete_ani_con = false;

	m_mous_x = 0.0f;            //マウスの位置X
	m_mous_y = 0.0f;		    //マウスの位置X
	m_rope_moux = 0.0f;			//Rを押したときのマウスの位置X
	m_rope_mouy = 0.0f;		    //Rを押したときのマウスの位置Y
	
	m_bullet_control = false;	//弾丸発射制御用
	m_rope_control = false;		//ロープ発射制御用
	m_rope_ani_con = false;
	m_rope_delete = false;    //ロープが消えたかどうか調べる変数
	m_rope_delete_ani_con = false;//アニメーション用ロープが消えたかどうかを管理する 
	m_hero_water_delete = false;

	m_ladder_updown = 0;
	m_ladder_ani_updown = 0;
	m_ladder_jump = 0;

	m_ani_max_time_move = 6;	//moveアニメーション間隔幅
	m_ani_time_move = 0;
	m_ani_frame_move = 1;		//move静止フレームを初期にする

	m_ani_max_time_ladders = 9; //laddersアニメーション間隔幅 
	m_ani_time_ladders = 0;
	m_ani_frame_ladders = 0;	//ladders静止フレームを初期にする

	m_ani_max_time_rope = 25; //ropeアニメーション間隔幅 
	m_ani_time_rope = 0;
	m_ani_frame_rope = 0;	//rope静止フレームを初期にする

	m_ani_max_time_water_die = 25;         //主人公が水に当たった時アニメーション間隔幅 
	m_ani_time_water_die  = 0;
	m_ani_frame_water_die = 0;//主人公が水に当たった時静止フレームを初期にする


	m_remaining = 2;//ざんき初期化

	m_block_type = 0;//主人公のしたのブロック情報

	//ブロックとの衝突した状態(場所)確認用
	m_hit_up	= false;
	m_hit_left  = false;
	m_hit_right = false;
	m_hit_down  = false;

	//当たり判定
	Hits::SetHitBox(this, m_px, m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, ELEMENT_PLAYER, OBJ_HERO, 1);
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
		int pos_x=0;
		//右下
		if (i == 1)
		{
			pos_x = HERO_SIZE_WIDTH;
		}
		//左下
		else if(i == 2)
		{
			pos_x = HERO_SIZE_WIDTH / 2;
		}
		//主人公のX位置(マップの要素数)
		int x = (m_px + pos_x) / BLOCK_SIZE;
		//主人公のY位置(マップの要素数)
		//少し下にする
		int y = (m_py + 1 + HERO_SIZE_HEIGHT) / BLOCK_SIZE;
		//ブロック情報が０で無いなら取得
		if (objmap->GetMap(x, y)!= 0)
		{
			//取得
			m_block_type = objmap->GetMap(x, y);
		}
	}
	//落下にリスタート----------------------------------
	//m_pyが1000以下ならリスタートする
	if (m_py > 1000.0f)
	{
		//場外に出たらリスタート
		Scene::SetScene(new CSceneMain());
	}
	
	//マウスの位置情報取得
	m_mous_x = Input::GetPosX();
	m_mous_y = Input::GetPosY();

	//ブロックオブジェクトを持ってくる
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//ブロックとの当たり判定
	objblock->AllBlockHit(&m_px, &m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	LandingCheck();//着地フラグの更新

	//はしご-------------------------------------------------
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

	

	//移動ーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	//Dキーがおされたとき：右移動　　ロープを出している時と水に当たった時は動かない
	if (Input::GetVKey('D') == true && m_rope_ani_con == false && m_hero_water_delete == false)
	{
		m_vx += 0.5f;
		m_ani_frame_stop_move = 0;  //主人公が動いてるなら0にする
		m_posture = 0.0f;		    //主人公の向き
		m_ani_time_move += 1;
	}
	//Aキーがおされたとき：左移動　　ロープを出している時と水に当たった時は動かない
	else if (Input::GetVKey('A') == true && m_rope_ani_con == false && m_hero_water_delete == false)
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
	//ロープを出している時は動かない  はしごを上っている時も動かない　　水に当たっているときも動かない
	if (Input::GetVKey(VK_SPACE) == true && m_ladder_jump == 0 && m_rope_ani_con == false && m_hero_water_delete == false)
	{
		if (m_hit_down == true)
		{
			m_vy = -16.0f;
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
	m_vx += -(m_vx * 0.098);

	//自由落下運動
	m_vy += 9.8 / (16.0f);
	
		
	if (m_ladder_jump==1)
	{
		if (m_ladder_updown == 0)
		{
			m_vy += 160.0f / (32.0f);
		}
	}
	

	Scroll();	//スクロール処理をおこなう
	
	m_px += m_vx;
	m_py += m_vy;

	//移動終わり-----------------------------------------


	//腕の角度を求める-----------------------
	
	//マウスポインタとの距離を求める
	float x = m_mous_x - (m_px - objmap->GetScrollX());	//X
	float y = m_mous_y - (m_py - objmap->GetScrollY());	//Y
	float inclination = sqrt(x * x + y * y);				//斜辺

	//ラジアン値を求める
	float rad = asin( - y / inclination);
	//角度を求める
	m_r = rad * 180.0f / 3.14f;
	
	//--------------------------------------------------------
	

	//発砲---------------------------------------------------
	//左クリックを押したら   水に当たっているときは動かない
	if (Input::GetMouButtonL() == true && m_hero_water_delete == false)
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
					if (m_posture == 0.0f && m_ladder_updown == 0)//主人公が右を向いていてはしごに登っていない時とき右側から発射
					{
						//弾丸作成
						CObjBullet* objbullet = new CObjBullet(m_px + 64.0f, m_py + 50.0f);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //弾丸を出ないフラグにする。
					}
					else if (m_posture == 1.0f && m_ladder_updown == 0)//主人公が左を向いていてはしごに登っていない時とき右側から発射
					{
						//弾丸作成
						CObjBullet* objbullet = new CObjBullet(m_px - 16.0f, m_py + 50.0f);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //弾丸を出ないフラグにする。
					}
				}
			}
		}
	}
	else
		m_bullet_control = true; //左クリックしてなければ弾丸をでるフラグにする。

	//発砲終了-----------------------------------------------


//ロープ射出---------------------------------------------

	//ロープオブジェクトを持ってくる
	CObjRope* obj_rope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
	
	bool rope_caught; //ロープがロープスイッチと当たっているかどうかを確かめる変数
	bool rope_delete; //ロープが消えてるか同うかを確かめる変数

	//マウスの位置がプレイヤーから見てどの方向か調べるための変数
	float mous_rope_way = 0.0f;//右：0.0ｆ　左：1.0ｆ 右向きで初期化

	if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//主人公より左をクリックしたとき
		mous_rope_way = 1.0f;

	//右クリックを押したらの部分を上に変更したのでマージする時は元の奴を消してこっちを残してください
	//右クリックを押したら   水に当たっているときは動かない
	if (Input::GetMouButtonR() == true && m_hero_water_delete == false)
	{
		//主人公をクリックしていた場合
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//ヒーロークリックした場合
		}       //マウスの位置が後ろじゃない　ロープアニメのフラグがなし　ロープの削除フラグがなし
		else if (m_posture == mous_rope_way && m_rope_ani_con == false && m_rope_delete_ani_con == false)
		{
			m_rope_moux = Input::GetPosX(); //ロープを射出したときのマウスの位置Xを入れる
			m_rope_mouy = Input::GetPosY(); //ロープを射出したときのマウスの位置Yを入れる
			m_rope_ani_con = true;
		}
	}

	if (obj_rope != nullptr)//ロープオブジェクトが出ている場合
	{
		rope_caught = obj_rope->GetCaughtFlag();//ロープがロープスイッチに当たっているかの情報をもらう
		rope_delete = obj_rope->GetDelete();    //ロープが消えているかどうかを調べる
	}
	else //ロープオブジェクトが出ていない場合
	{
		rope_caught = false;
		rope_delete = false;
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
				if (m_posture == 0.0f )//主人公が右を向いているとき右側から発射
				{
					CObjRope* objrope = new CObjRope(m_px + 64.0f, m_py + 50.0f);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
				}
				else if (m_posture == 1.0f)//主人公が左を向いているとき左側から発射
				{
					CObjRope* objrope = new CObjRope(m_px - 16.0f, m_py + 50.0f);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
				}
			}
			if (m_rope_control == false) //ロープを出している時
			{
				m_ani_frame_rope = 2;//アニメーションを２で止める
				if (rope_delete == true)//ロープが消えている場合
				{
					m_rope_delete_ani_con = true;
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
		m_rope_delete_ani_con = false;

	//ロープとロープスイッチが当たっているとき
	if (rope_caught == true)
	{
		m_rope_delete_ani_con = false;
		if (Input::GetMouButtonR() == false)////右クリックしていないときtrueにする
		m_rope_delete_ani_con = true;
	}

	//射出終了------------------------------------------------

	//水オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		m_hero_water_delete = true; //主人公の水にあたったときの死亡フラグをONにする
	}

	//敵オブジェクトと衝突していれば
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr) //仮です。敵が多いようならElementに変えます
	{
		this->SetStatus(false);		//自身を削除
		Hits::DeleteHitBox(this);	//ヒットボックスを削除

		//メインへ移行
		Scene::SetScene(new CSceneMain());
		return;
	}
	//主人公の水に当たったときの死亡フラグがONなら死亡アニメーションをする
	if (m_hero_water_delete == true)
	{
		m_vy = 0.0f;
		//主人公が水に当たった時のアニメーションタイムを進める
		m_ani_time_water_die += 1;
		//アニメーションの感覚管理
		if (m_ani_time_water_die > m_ani_max_time_water_die)
		{
			m_ani_frame_water_die += 1;
			m_ani_time_water_die = 0;
		}

		//最後までアニメーションが進むと最初に戻る
		if (m_ani_frame_water_die == 3)
		{
			this->SetStatus(false);		//自身を削除
			Hits::DeleteHitBox(this);	//ヒットボックスを削除
			//メインへ移行
			Scene::SetScene(new CSceneMain());
			return;
		}

	}
	//HitBoxの位置を更新する
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

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
	if ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY() > SCROLL_LINE_DOWN &&
		objmap->GetScrollY() < 0)
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

	bool rope_caught;

	if (obj_rope != nullptr)//ロープオブジェクトが出ている場合
		rope_caught = obj_rope->GetCaughtFlag();//ロープがロープスイッチに当たっているかの情報をもらう
	else
		rope_caught = false;
	//本体---------------------------------
	//切り取り位置

	//水にあたった時
	if ( m_hero_water_delete == true )
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
		src.m_top = 128.0f;
		src.m_left = 0.0f + AniData[m_ani_frame_move] * 64;
		src.m_right = 64.0f + AniData[m_ani_frame_move] * 64;
		src.m_bottom = 256.0f;
	}
	
	//描画位置
	if (m_ani_frame_water_die != 2)//水に当たった時の横に倒れるアニメーション以外はこっちを通す
	{
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + HERO_SIZE_HEIGHT;
	}
	else if (m_ani_frame_water_die == 2)  //水にあたった時のアニメーションで横に倒れるフレーム用
	{
		dst.m_top = 64.0f + m_py - objmap->GetScrollY();
		dst.m_left = (128.0f * m_posture) + m_px - objmap->GetScrollX();
		dst.m_right = (128.0f - 128.0f * m_posture) + m_px - objmap->GetScrollX();
		dst.m_bottom = dst.m_top + 64.0f;
	}

	//描画
	Draw::Draw(3, &src, &dst, color, 0.0f);
	//本体-------------------------------------

	//腕---------------------------------------
	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 64.0f;
	src.m_right = 128.0f;
	src.m_bottom = 64.0f;

	//描画位置
	dst.m_top += 48.0f;
	dst.m_left += 33.0f - (HERO_SIZE_WIDTH * m_posture);
	dst.m_right +=33.0f - (HERO_SIZE_WIDTH * m_posture);
	dst.m_bottom = dst.m_top +64.0f;
	
	//描画    ロープが出てる時、はしごに登ってる時、ロープとロープスイッチが当たっている時  主人公が水に当たった時
	if (m_rope_ani_con == true || m_ladder_updown != 0 || rope_caught == true || m_hero_water_delete == true)
	{
		;    //何も描画しない
	}
	else
		Draw::Draw(3, &src, &dst, color, m_r,-0.2f,-0.25f);
	//-----------------------------------------


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
	if (false)
	{
		//中央位置設定
		static int ball_x = WINDOW_SIZE_W / 2;
		static int ball_y = WINDOW_SIZE_H / 2;
		//半径初期
		static int ball_r = 768 ;
		//半径をだんだん短くする
		ball_r -= 3;
		//カラー
		float c[4] = {0.0f,0.0f,0.0f,1.0f};
		//正四角形の１辺の長さ
		//長ければ長いほど軽く
		//短ければ短いほど重いよ
		int one_side = 6;

		//円外を四角形で埋め尽くす
		for (int y = 0; y < WINDOW_SIZE_H; y+= one_side)
		{
			for (int x = 0; x < WINDOW_SIZE_W; x+= one_side)
			{
				//円の中
				if ((x - ball_x)*(x - ball_x) + (y - ball_y)*(y - ball_y) <= ball_r * ball_r)
				{

				}
				//円外
				else
				{
					Draw::DrawHitBox(x, y, one_side, one_side, c);
				}				
			}
		}
	}
	//----------------------------------------------------------------
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
	Draw::Draw(23, &src, &dst, color, 0.0f);
}

//着地できてるかどうかを調べる関数
void CObjHero::LandingCheck()
{
	bool c1,c2,c3;//チェック結果を保存するための変数:チェック項目を増やすたびに数を増やす必要がある
	
	c1 = HitUpCheck(OBJ_LIFT); //リフトとの着地チェック
	c2 = HitUpCheck(OBJ_WOOD); //木との着地チェック
	c3 = HitUpCheck(OBJ_LIFT_MOVE); //木との着地チェック

	//チェック項目のどれか一つでもtrueなら
	if (c1 == true || c2 ==true || c3 == true)
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
				float r = hit_data[i]->r;//あたっている角度をもってくる

				 //Heroの下側があたっていれば
				if (225.0f < r && r < 315.0f)
				{
					return true;//着地している
				}
			}
		}
	}
	return false;//着地していない
}

