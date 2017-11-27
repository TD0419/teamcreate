#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\SceneManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjDiffusionCannon.h"
#include "Function.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjDiffusionCannon::CObjDiffusionCannon(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//イニシャライズ
void CObjDiffusionCannon::Init()
{
	m_time = 0;
}

//アクション
void CObjDiffusionCannon::Action()
{
	//15°間隔で弾丸発射
	m_time++;
	if (m_time > 25)
	{
		m_time = 0;

		//7発同時上に向かって発射
		CObjDiffusionBullet* obj_b;
		for (int i = 35; i<165; i += 19)
		{
			//約15角度で角度弾丸発射
			obj_b = new CObjDiffusionBullet(m_px, m_py, i);
			Objs::InsertObj(obj_b, OBJ_DIFFUSION_BULLET, 100);
		}

	}
}

//ドロー
void CObjDiffusionCannon::Draw()
{
	//描画カラー
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//マップオブジェクトを持ってくる
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + DIFFUSION_CANNON_SIZE;
	src.m_bottom = src.m_top + DIFFUSION_CANNON_SIZE;

	//描画位置
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + DIFFUSION_CANNON_SIZE;
	dst.m_bottom = dst.m_top + DIFFUSION_CANNON_SIZE;

	//描画
	Draw::Draw(GRA_CANNON, &src, &dst, color, 0.0f);
}