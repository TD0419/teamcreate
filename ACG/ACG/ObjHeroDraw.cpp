#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjHero.h"

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
	src.m_top = 0.5f;
	src.m_left = 128.0f;
	src.m_right = 192.0f;
	src.m_bottom = 64.0f;

	//描画位置 
	dst.m_top = m_py - objmap->GetScrollY() + 43.0f;
	//　主人公が右を向いている時の腕の描画位置
	if (m_posture == 0.0f)
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_left = (HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 20.0f - (HERO_SIZE_WIDTH * m_posture);
	//　主人公が右を向いている時の腕の描画位置
	if (m_posture == 0.0f)
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);
	else
		dst.m_right = (HERO_SIZE_WIDTH - HERO_SIZE_WIDTH * m_posture) + m_px + 16.0f - objmap->GetScrollX() + 33.0f - (HERO_SIZE_WIDTH * m_posture);

	dst.m_bottom = dst.m_top + 59.0f;

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
	if (m_hero_die_enemy == true)
	{
		//敵があたって立ちの時のアニメーション
		if (m_ani_frame_enemy_die == 0 || m_ani_frame_enemy_die == 1)
		{
			//　主人公が右を向いている時の描画位置
			if (m_posture == 0.0f)
			{
				src.m_top = 832.0f;
				src.m_left = 0.0f + m_ani_frame_enemy_die * 64;
				src.m_right = 64.0f + m_ani_frame_enemy_die * 64;
				src.m_bottom = 958.0f;
			}
			//　主人公が左を向いている時の描画位置
			else
			{
				src.m_top = 832.0f;
				src.m_left = 128.0f + m_ani_frame_enemy_die * 64;
				src.m_right = 190.0f + m_ani_frame_enemy_die * 64;
				src.m_bottom = 958.0f;
			}
		}
		//フレームが２と３の時倒れるアニメーション
		else if (m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3)
		{
			if (m_ani_frame_enemy_die == 2)
			{
				//　主人公が右を向いている時の描画位置
				if (m_posture == 0.0f)
				{
					src.m_top = 960.0f;
					src.m_left = 0.0f;
					src.m_right = 128.0f;
					src.m_bottom = 1024.0f;
				}
				//　主人公が左を向いている時の描画位置
				else
				{
					src.m_top = 960.0f;
					src.m_left = 256.0f;
					src.m_right = 374.0f;
					src.m_bottom = 1024.0f;
				}
			}
			else
			{
				//　主人公が右を向いている時の描画位置
				if (m_posture == 0.0f)
				{
					src.m_top = 960.0f;
					src.m_left = 128.0f;
					src.m_right = 256.0f;
					src.m_bottom = 1024.0f;
				}
				//　主人公が左を向いている時の描画位置
				else
				{
					src.m_top = 960.0f;
					src.m_left = 384.0f;
					src.m_right = 520.0f;
					src.m_bottom = 1024.0f;
				}
			}
		}
	}

	//水にあたった時
	else if (m_hero_die_water == true)
	{
		//フレームが0か1ならもがくアニメーション
		if (m_ani_frame_water_die == 0 || m_ani_frame_water_die == 1)
		{
			//　主人公が右を向いている時の描画位置
			if (m_posture == 0.0f)
			{
				src.m_top = 641.0f;
				src.m_left = 0.0f + m_ani_frame_water_die * 64;
				src.m_right = 64.0f + m_ani_frame_water_die * 64;
				src.m_bottom = 768.0f;
			}
			//　主人公が左を向いている時の描画位置
			else
			{
				src.m_top = 641.0f;
				src.m_left = 128.0f + m_ani_frame_water_die * 64;
				src.m_right = 190.0f + m_ani_frame_water_die * 64;
				src.m_bottom = 768.0f;
			}
		}
		else if (m_ani_frame_water_die == 2) //フレームが2なら倒れるアニメーション
		{
			//　主人公が右を向いている時の描画位置
			if (m_posture == 0.0f)
			{
				src.m_top = 769.0f;
				src.m_left = 0.0f;
				src.m_right = 128.0f;
				src.m_bottom = 826.0f;
			}
			//　主人公が左を向いている時の描画位置
			else
			{
				src.m_top = 769.0f;
				src.m_left = 128.0f;
				src.m_right = 256.0f;
				src.m_bottom = 826.0f;
			}
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
		//左足をあげて上る
		if (m_ani_frame_ladders == 0 || m_ani_frame_ladders == 3)
		{
			src.m_top = 256.0f;
			src.m_left = 320.0f;
			src.m_right = 384.0f;
			src.m_bottom = 384.0f;
		}
		//右足を上げて上る
		else if (m_ani_frame_ladders == 1 || m_ani_frame_ladders == 2)
		{
			src.m_top = 256.0f;
			src.m_left = 256.0f;
			src.m_right = 320.0f;
			src.m_bottom = 384.0f;
		}
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
		//　主人公が右を向いている時の描画位置
		if (m_posture == 0.0f)
		{
			src.m_top = 128.0f;
			src.m_left = 256.0f;
			src.m_right = 320.0f;
			src.m_bottom = 256.0f;
		}
		//　主人公が左を向いている時の描画位置
		else
		{
			src.m_top = 128.0f;
			src.m_left = 578.0f;
			src.m_right = 640.0f;
			src.m_bottom = 256.0f;
		}
	}
	else if (m_ani_frame_stop_move == 1 && m_ladder_updown == 0 && rope_caught == false)  //止まっているとき
	{
		//　主人公が右を向いている時の描画位置
		if (m_posture == 0.0f)
		{
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 128.0f;
		}
		//　主人公が左を向いている時の描画位置
		else
		{
			src.m_top = 0.0f;
			src.m_left = 64.0f;
			src.m_right = 128.0f;
			src.m_bottom = 128.0f;
		}
	}
	else if (m_ani_frame_stop_move == 0 && m_ladder_updown == 0 && rope_caught == false)//動いているとき
	{
		//　主人公が右を向いている時の描画位置
		if (m_posture == 0.0f)
		{
			src.m_top = 129.0f;
			src.m_left = 0.0f + AniData[m_ani_frame_move] * 64;
			src.m_right = 64.0f + AniData[m_ani_frame_move] * 64;
			src.m_bottom = 256.0f;
		}
		//　主人公が左を向いている時の描画位置
		else
		{
			src.m_top = 129.0f;
			src.m_left = 320.0f + AniData[m_ani_frame_move] * 64;
			src.m_right = 384.0f + AniData[m_ani_frame_move] * 64;
			src.m_bottom = 256.0f;
		}
	}

	//描画位置
	//   水にあった時主人公が倒れてる時　　敵に当たって倒れている時
	if (m_ani_frame_water_die == 2 || m_ani_frame_enemy_die == 2 || m_ani_frame_enemy_die == 3)  //水や敵にあたった時（死んだとき）のアニメーションで横に倒れるフレーム用
	{
		dst.m_top = 64.0f + m_py - objmap->GetScrollY();
		dst.m_left = (128.0f * m_posture) + m_px - objmap->GetScrollX() - 64.0f;
		dst.m_right = (128.0f - 128.0f * m_posture) + m_px - objmap->GetScrollX() - 64.0f;
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