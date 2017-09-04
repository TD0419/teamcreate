//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBlock::CObjBlock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{	
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);

}

//�A�N�V����
void CObjBlock::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//��l���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();//�����蔻��̏������s��
	}
	
	//�{�X�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_BOSS) != nullptr)
	{
		BossHit();//�����蔻��̏������s��
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjBlock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//�`��
	Draw::Draw(2, &src, &dst, color, 0.0f);

}

void CObjBlock::HeroHit()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0.0f < r && r < 45.0f || 315.0f < r && r < 360.0f)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45.0f < r && r < 125.0f)
			{
				obj_hero->SetPosY(m_py - HERO_SIZE_Y);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125.0f < r && r < 225.0f)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px - HERO_SIZE_X);//��l���̈ʒu���u���b�N�̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225.0f < r && r < 315.0f)
			{
				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				obj_hero->SetPosY(m_py + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
		}
	}
}
//�m�F�p�Ƀ{�X�ł�p�ӂ��܂����B����A�폜�ύX���Ă����܂��܂���B
void CObjBlock::BossHit()
{
	//���g��HitBox���擾
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;						//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_BOSS); //�Փ˂̏���hit_data�ɓ����

												//�f�o�b�O�p�{�X�I�u�W�F�N�g�����擾
	CObjBoss* obj_boss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^����
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�Ԃ����Ă���p�x�������Ă���

									 //�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_boss->SetVecX(0.0f);//�{�X��X�����̈ړ����O�ɂ���
				obj_boss->SetPosX(m_px + BLOCK_SIZE);//�{�X�̈ʒu���u���b�N�̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{
				obj_boss->SetVecY(0.0f);//�{�X��Y�����̈ړ����O�ɂ���
				obj_boss->SetPosY(m_py - BOSS_SIZE);//�{�X�̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225)
			{
				obj_boss->SetVecX(0.0f);//�{�X��X�����̈ړ����O�ɂ���
				obj_boss->SetPosX(m_px - BOSS_SIZE);//�{�X�̈ʒu���u���b�N�̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				obj_boss->SetVecY(0.0f);//�{�X��Y�����̈ړ����O�ɂ���
				obj_boss->SetPosY(m_py + BLOCK_SIZE);//�{�X�̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
		}
	}
}