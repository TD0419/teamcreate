#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\SceneManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjDiffusionCannon.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDiffusionCannon::CObjDiffusionCannon(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjDiffusionCannon::Init()
{
	m_time = 0;
}

//�A�N�V����
void CObjDiffusionCannon::Action()
{
	//15���Ԋu�Œe�۔���
	m_time++;
	if (m_time > 25)
	{
		m_time = 0;

		//7��������Ɍ������Ĕ���
		CObjDiffusionBullet* obj_b;
		for (int i = 35; i<165; i += 19)
		{
			//��15�p�x�Ŋp�x�e�۔���
			obj_b = new CObjDiffusionBullet(m_px, m_py, i);
			Objs::InsertObj(obj_b, OBJ_DIFFUSION_BULLET, 100);
		}

	}
}

//�h���[
void CObjDiffusionCannon::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + DIFFUSION_CANNON_SIZE;
	src.m_bottom = src.m_top + DIFFUSION_CANNON_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + DIFFUSION_CANNON_SIZE;
	dst.m_bottom = dst.m_top + DIFFUSION_CANNON_SIZE;

	//�`��
	Draw::Draw(GRA_CANNON, &src, &dst, color, 0.0f);
}