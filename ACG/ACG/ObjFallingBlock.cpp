//�g�p����w�b�_�[�t�@�C��
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjFallingBlock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFallingBlock::CObjFallingBlock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
	m_return_block_y = m_py;
}

//�C�j�V�����C�Y
void CObjFallingBlock::Init()
{
	m_falling_time = 10;			//�u���b�N��������܂ł̎���
	m_fallint_start_flag = false;	//true�c���Ƃ�  false�c���Ƃ��Ȃ�
	m_screen_out = false;			//�u���b�N����ʊO�ɏo�Ă��邩�𒲂ׂ�

	m_screen_out = false;		//�u���b�N����ʊO�ɏo�Ă��邩�𒲂ׂ�

	//�����蔻��pHitBox���쐬                          
	Hits::SetHitBox(this, m_px, m_py, FALLING_BLOCK_SIZE_WIDTH, BLOCK_SIZE, ELEMENT_GIMMICK, OBJ_FALLING_BLOCK, 1);
}

//�A�N�V����
void CObjFallingBlock::Action()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBox�̃|�C���^�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�}�b�v�̊O���܂ł�����
	if (m_py > BLOCK_SIZE * MAP_Y_MAX)
	{
		Audio::Stop(GROUND);
		m_screen_out = true;//��ʊO�Ƀu���b�N���o�Ă���
	}
	else
	{
		m_screen_out = false;//��ʊO�Ƀu���b�N���o�Ă��Ȃ�
	}

	//�X�e�[�W3�{�X�̃I�u�W�F�N�g�̎擾
	CObjStage5Boss* objboss = (CObjStage5Boss*)Objs::GetObj(OBJ_STAGE5_BOSS);
	bool stage5boss_atk4_count = false;//�X�e�[�W5�{�X�̍U���S�p�J�E���^�[�̏��擾�p
	bool stage5boss_death_flag = false;//�X�e�[�W5�{�X�̎��S�t���O�̏��擾�p

	if (objboss != nullptr)//�{�X�I�u�W�F�N�g�������
	{
		//�X�e�[�W3�{�X�̎��S�t���O�̏����擾����
		stage5boss_death_flag = objboss->GetBossDeathFlag();
		
		//�u���b�N�������ʒu�ɖ߂����߂̃t���O
		stage5boss_atk4_count = objboss->GetBlockRetuenFlag();

		//���������邩�̃t���O���X�V
		m_fallint_start_flag = objboss->GetBlockDownFlag();
	}
	
	//�{�X�̍U��4�̃J�E���^�[��300�t���[���o�߂�����A�u���b�N�������ʒu�ɖ߂�
	if (stage5boss_atk4_count == true && stage5boss_death_flag == false)
	{
		m_py = m_return_block_y;//�����ʒu�Ƀu���b�N��߂�
		m_falling_time = 10;	//�u���b�N��������܂ł̎���
		m_fallint_start_flag = false;//�����t���O���I�t�ɂ���
		hit->SetInvincibility(false);//���g�̓����蔻�������
	}

	if (m_fallint_start_flag == true)//�����J�n�t���O���I���Ȃ�
		m_falling_time--;
	

	//�^�C����0�ɂȂ�Ɖ��ɗ�����
	if (m_falling_time < 0)
	{
		m_py += 1.0f;
		Audio::Start(GROUND);
		
	}
	//�X�e�[�W3�{�X��|�����Ƃ��A������u���b�N���㏸������
	if( stage5boss_death_flag == true)
	{
		m_py -= 8.0f;
		m_falling_time = 10;		 //�u���b�N��������܂ł̎���
		m_fallint_start_flag = false;//�����t���O���I�t�ɂ���
		hit->SetInvincibility(false);//���g�̓����蔻�������
		
		//�߂��ʒu(�����ʒu)����ɏ㏸������A�����ʒu�ŏ㏸���~�߂�
		if (m_py<=m_return_block_y)
		{
			m_py = m_return_block_y;
		}
	}

	//������u���b�N����苗����������A���g�̓����蔻����Ȃ���
	if (m_py>PERDECISION_CLEAR_POINT)
	{
		hit->SetInvincibility(true);//�����蔻����Ȃ���
	}

	//�q�[���[�I�u�W�F�N�g�Ɠ������Ă����
	if (hit != nullptr)
{	
		HeroHit();//�Փˏ���������
		
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(hit, m_px, m_py);
	}
}

//�h���[
void CObjFallingBlock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = FALLING_BLOCK_SIZE_WIDTH;
	src.m_bottom = BLOCK_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = dst.m_left + FALLING_BLOCK_SIZE_WIDTH;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//�`��
	Draw::Draw(GRA_FALLING_BLOCK, &src, &dst, color, 0.0f);
}

//��l�������������Ƃ��̏���
void CObjFallingBlock::HeroHit()
{
	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l�����画��Ƃ��̌�̏����ɕK�v�ȏ��������Ă���

	//�ʒu
	float* h_px = objhero->GetPointPosX();
	float* h_py = objhero->GetPointPosY();
	//�ړ��̃x�N�g��
	float* h_vx = objhero->GetPointVecX();
	float* h_vy = objhero->GetPointVecY();

	//�Փ˔���
	HitTestOfAB(m_px, m_py, FALLING_BLOCK_SIZE_WIDTH, BLOCK_SIZE,
		h_px, h_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT, h_vx, h_vy);

}