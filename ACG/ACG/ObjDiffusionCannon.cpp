#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
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
	m_map_x = x;
	m_map_y = y;
}

//�C�j�V�����C�Y
void CObjDiffusionCannon::Init()
{
	m_time = 100;
}

//�A�N�V����
void CObjDiffusionCannon::Action()
{
	m_time++;
	
	//�X�e�[�W3�{�X�I�u�W�F�N�g�������Ă���
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);

	if (objboss != nullptr)	//�{�X�I�u�W�F�N�g�������
	{
		WindowOutDelete(this);//�폜
	}

	//100�t���[���̓x�ɑł��o��
	if (m_time > 100)
	{
		m_time = 0;

		//7��������Ɍ������Ĕ���
		CObjDiffusionBullet* obj_b;
		for (int i = 30; i<165; i += 20)
		{
			//��20�p�x�Ŋp�x�e�۔���
			obj_b = new CObjDiffusionBullet(m_px + 28.0f, m_py+20.0f, i);
			Objs::InsertObj(obj_b, OBJ_DIFFUSION_BULLET, 100);
			Audio::Start(DIFFUSION);
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