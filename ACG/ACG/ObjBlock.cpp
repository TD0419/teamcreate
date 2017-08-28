//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBlock::CObjBlock(int map[MAP_Y_MAX][MAP_X_MAX])
{

}

//イニシャライズ
void CObjBlock::Init()
{

}


//アクション
void CObjBlock::Action()
{
}
//ドロー
void CObjBlock::Draw()
{
	
}

// BlockHit関数
// 引数1  float x        :判定を行うobjectのX位置
// 引数2  float y        :判定を行うobjectのY位置
// 引数3  bool scroll_on :判定を行うobjectはスクロールの影響与えるかどうか（true = 与える false = 与えない）　
// 引数4  bool* up       :上下左右判定の上部分に当たっているかどうかを返す
// 引数5  bool* down     :上下左右判定の上部分に当たっているかどうかを返す
// 引数6  bool* left     :上下左右判定の上部分に当たっているかどうかを返す
// 引数7  bool* right    :上下左右判定の上部分に当たっているかどうかを返す
// 引数8  float* vx      :左右判定時の反発による移動方向・力の値を変えて返す
// 引数9  float* vy      :上下左右判定時による自由落下運動の移動方向・力の値変えて返す
// 引数10 int* bt        :下部判定時、特殊なブロックのタイプを返す
//判定を行うオブジェクトとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy, int* bt
)
{
	//主人公の衝突状態用フラグの初期化
	*up = (false);
	*down = (false);
	*left = (false);
	*right = (false);

	//踏んでいるブロックの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//主人公とブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//長さを求める
					float len = sqrt(rvx * rvx + rvy * rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
					{
						r = abs(r);
					}
					else
					{
						r = 360.0f - abs(r);
					}
					//lenがある一定の長さのより短い場合に入る
					if (len < 88.0f)
					{

						//角度で上下左右を判定
						if ((r < 45 && r > 0) || r > 315)
						{
							//右
							*right = (true);					//主人公の左の部分が衝突している
							*x = bx + 64.0f + (scroll);   //ブロックの位置＋主人公の幅
							*vx = -(*vx) * 0.1f; //-VX*反発係数
						}
						if (r > 45 && r < 135)
						{
							//上
							*down = (true);					//主人公の下の部分が衝突している
							*y = by - 64.0f;				//ブロックの位置＋主人公の幅
															//種類を渡すのスタートとゴールのみ変更する
							if (m_map[i][j] >= 2)
							{
								*bt = m_map[i][j];			//ブロック要素 ( type )を主人公に渡す
							}
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = (true);					//主人公の右の部分が衝突している
							*x = bx - 64.0f + (scroll);	//ブロックの位置＋主人公の幅
							*vx = -(*vx) * -0.1f; //-VX*反発係数
						}
						if (r > 255 && r < 315)
						{
							//下
							*up = (true);					//主人公の上の部分が衝突している
							*y = by + 64.0f;				//ブロックの位置＋主人公の幅
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}


	}
}
