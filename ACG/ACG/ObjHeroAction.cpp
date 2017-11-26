
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjHero.h"

void CObjHero::RopeThrow() {

	//Scene　開店準備 ←？？？??

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
	if ( Input::GetMouButtonR() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
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

	//射出終了------------------------------------------------RopeThrow() end

}

void CObjHero::Shot() {


	//Scene　開店準備
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
						float x_add = cos(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sin(m_bullet_r* 3.14f / 180.f) * 50.0f;
						//弾丸作成
						Audio::Start(FIRING);//音楽スタート
						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 30.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //弾丸を出ないフラグにする。
					}
					else if (m_posture == 1.0f && m_ladder_updown == 0)//主人公が左を向いていてはしごに登っていない時とき右側から発射
					{
						// 弾丸発射位置を計算するための角度調整
						if (abs(m_r) > 90.0f)
							m_bullet_r = m_r;
						else
							m_bullet_r = 180.0f + m_r;

						// 弾丸の角度から発射位置のずれを求める(*50.0fは腕の回りによる円の半径)
						float x_add = cos(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sin(m_bullet_r* 3.14f / 180.f) * 50.0f;
						Audio::Start(FIRING);//音楽スタート
						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 20.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //弾丸を出ないフラグにする。
					}
				}
			}
		}
	}
	else
		m_bullet_control = true; //左クリックしてなければ弾丸をでるフラグにする。
















}