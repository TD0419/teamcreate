#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"
#include "ObjStage5Boss.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;
//�R���X�g���N�^
CObjStage5Boss::CObjStage5Boss(int x, int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjStage5Boss::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_hp = 100; //��5�{�X�̂g�o(���ɂg�o��[100]�Ɛݒ�)

	//����������(�������Ă��Ȃ�)
	m_attack_mode = 0;

	//���y
	//Audio::Start(BOSS);
	//Audio::Stop(STAGE);

	//�E�r�I�u�W�F�N�g�쐬
	m_boos_arm_right = new CObjStage5BossArms(m_px - 370.0f, m_py - 166.0f, 1);
	Objs::InsertObj(m_boos_arm_right, OBJ_STAGE5_BOSS_ARMS, 10);

	//���r�I�u�W�F�N�g�쐬
	m_boos_arm_left = new CObjStage5BossArms(m_px + 126.0f, m_py - 166.0f, 2);
	Objs::InsertObj(m_boos_arm_left, OBJ_STAGE5_BOSS_ARMS, 10);

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, STAGE5_BOSS_BODY_SIZE, STAGE5_BOSS_BODY_SIZE, ELEMENT_ENEMY, OBJ_STAGE5_BOSS, 1);
}

//�A�N�V����
void CObjStage5Boss::Action()
{
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	switch (m_attack_mode)
	{
		//�������Ă��Ȃ����
	case 0:
		//�������Ă��Ȃ��̂ōU�����[�h�������_���Ō��߂�
		m_attack_mode = GetRandom(1, 4);
		break;
		//��l���̂���ʒu������ďォ��n�ʂ܂łɓ�����Ǝ��ʍU���𗎂Ƃ��U��
	case 1:

		break;
		//�ł��o���Ă��烉���_���Ȏ��Ԍo�߂Ŋg�U�e(15�x�ق�)�ɂȂ�e���o���U��
	case 2:

		break;
		//�{�X���g�������Ȃ����l���̈ʒu�ɒe������(���[�U�[)�U��
	case 3:

		break;
		//3�n�_�ɓ�������|����I�u�W�F�N�g���o�������A���̌�n�ʂ�������U��������B
	case 4:

		break;
	default:
		break;
	}
	//�����蔻��X�V
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

	//��l���̒e�ۂƂԂ�������g�o��-1�ɂ���
	//�e�ۂƂ���������g�o��1���炷
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	//(��)�g�o��0�ɂȂ�����N���A��ʂɈړ�
	//�N���A��ʈړ��������m�肵����A�ύX���Ă��������B
	if (m_hp == 0)
	{
		//�N���A��ʂɈړ�
		Scene::SetScene(new CSceneGameClear());
		return;
	}

}

//�h���[
void CObjStage5Boss::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//���r�ڑ��d�C-------------------------------
	//���r����
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY()  + ELECTRIC_L_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() - ELECTRIC_L_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
	//�`��
	Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);

	//�E�r����
	//�؂���ʒu
	src.m_top = STAGE5_BOSS_ELECTRIC_HEIGHT;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	src.m_bottom = src.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;

	//�`��ʒu
	dst.m_top =  m_py - objmap->GetScrollY() + ELECTRIC_R_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() + ELECTRIC_R_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_ELECTRIC_WIDTH;
	dst.m_bottom = dst.m_top + STAGE5_BOSS_ELECTRIC_HEIGHT;
	//�`��
	Draw::Draw(GRA_STAGE5_BOSS_ELECTRIC, &src, &dst, color, 0.0f);

	//����--------------------------------------
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_BODY_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_BODY_SIZE;
	
	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = m_px - objmap->GetScrollX();
	dst.m_right = STAGE5_BOSS_BODY_SIZE + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top + STAGE5_BOSS_BODY_SIZE;
	//�`��
	Draw::Draw(GRA_STAGE5_BOSS_BODY, &src, &dst, color, 0.0f);


	//�ዅ---------------------------------------
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + STAGE5_BOSS_EYE_SIZE;
	src.m_bottom = src.m_top + STAGE5_BOSS_EYE_SIZE;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY()  + EYE_CORRECTION_HEIGHT;
	dst.m_left = m_px - objmap->GetScrollX() + EYE_CORRECTION_WIDTH;
	dst.m_right = dst.m_left + STAGE5_BOSS_EYE_SIZE;	
	dst.m_bottom = dst.m_top + STAGE5_BOSS_EYE_SIZE;
	//�`��
	Draw::Draw(GRA_STAGE5_BOSS_EYE, &src, &dst, color, 0.0f);
	

}
//�����_���Œl�����߂�֐�
//����1 int min	:�ŏ��l
//����2 int max	:�ő�l
//�߂�l int	:�ŏ��l�`�ő�l�̊Ԃ̐��l�������_���œn��(�ő�l�A�ŏ��l���܂�)
int CObjStage5Boss::GetRandom(int min, int max)
{
	//��񂾂�������������p
	static bool initialization = true;
	if (initialization == true)
	{
		srand((unsigned)time(NULL));  //�����n��̕ύX
		initialization = false;
	}
	return min + (int)(rand()*(max - min + 1.0f) / (1.0f + RAND_MAX));
}