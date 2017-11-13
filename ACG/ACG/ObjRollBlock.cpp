//使用するヘッダー
#include "GameHead.h"
#include "ObjRollBlock.h"
#include "Function.h"

#include "GameL\HitBoxManager.h"

//コンストラクタ
//引数1,2	mapの要素番号
CObjRollBlock::CObjRollBlock(int x,int y,int pattan)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	m_pattan = pattan;
}

//イニシャライズ
void CObjRollBlock::Init()
{
	m_r = 0.0f;	//角度初期化
	m_count = 0;//カウンターの初期化

	m_roll_flag = false;//回転のフラグを初期化
	
	switch (m_pattan)
	{
		case 1:	//90fごとに回転
		{
			//回転の中心位置を求める
			m_center_x = m_px + ROLL_BLOCK_SIZE_WIDTH / 2.0f;
			m_center_y = m_py + ROLL_BLOCK_SIZE_HEIGHT / 2.0f;

			//回転後のポジションと中心位置の差分
			m_difference_x = ROLL_BLOCK_SIZE_HEIGHT / 2.0f;
			m_difference_y = ROLL_BLOCK_SIZE_WIDTH / 2.0f;

			break;
		}
		case 2:	//引っ張ったときに一度のみ回転
		{
			break;
		}
	}

	//当たり判定セット
	Hits::SetHitBox(this,m_px, m_py,ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
}

//アクション
void CObjRollBlock::Action()
{
	if(m_count<=90)//90以下なら
		m_count++;//カウントを増やす

	switch (m_pattan)
	{
		case 1:	//90fごとに回転
		{
			//90fになったら
			if (m_count == 90)
			{
				m_roll_flag = true;//回転のフラグをオンにする
			}

			if (m_roll_flag == true)//回転したとき
			{
				m_r += 90.0f;	//角度を加算

				if (m_r >= 360.0f)	//360度以上にならないようにする
					m_r = 0.0f;

				//回転後のポジションを入れる
				m_px = m_center_x - m_difference_x;
				m_py = m_center_y - m_difference_y;

				//差分の更新（xとyの入れ替え）をする
				float tmp = m_difference_x;
				m_difference_x = m_difference_y;
				m_difference_y = tmp;

				m_roll_flag = false;	//フラグをオフにする
				m_count = 0;			//カウントを0で初期化する
			}
			break;
		}
		case 2:	//引っ張ったときに一度のみ回転
		{
			break;
		}
	}

	if( ((int)m_r % 180) ==0)	//横向きなら
	{
		//高さと幅をそのままで当たり判定の更新
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py, ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT);
	}
	else 	//縦向きなら
	{
		//高さと幅を逆にしてあたり判定の更新
		HitBoxUpData(Hits::GetHitBox(this), m_px, m_py, ROLL_BLOCK_SIZE_HEIGHT, ROLL_BLOCK_SIZE_WIDTH);
	}
}

//ドロー
void CObjRollBlock::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = ROLL_BLOCK_SIZE_WIDTH;
	src.m_bottom = ROLL_BLOCK_SIZE_HEIGHT;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left =m_px - objmap->GetScrollX();

	if (((int)m_r % 180) == 0)	//横向き
	{
		dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
		dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
	}
	else//縦向き
	{
		dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_HEIGHT;
		dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_WIDTH;
	}

	//描画
	Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, m_r,-0.5f,-0.5f);
}
