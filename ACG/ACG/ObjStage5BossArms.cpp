#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameL\Audio.h"
#include "GameHead.h"
#include "Function.h"

#include "ObjStage5BossArms.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
//�X�e�[�W5�{�Xcpp����̕`��̓s���ŁAx��y�̌^��int����float�ɕύX���Ă��܂��B(�`��ōׂ����l���g����������)
CObjStage5BossArms::CObjStage5BossArms(float x, float y, int type)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
	m_arms_type = type;//type = 1�c���C�g�A�[��  2�c���t�g�A�[��
}

//�C�j�V�����C�Y
void CObjStage5BossArms::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	m_arm_hp = 10; //��5�{�X�A�[���̂g�o(���ɂg�o��[10]�Ɛݒ�A���E�̃A�[������)

	//type�̒l��1�̂Ƃ����C�g�A�[���̓����蔻��\��
	if (m_arms_type == 1)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_px + 160.0f, m_py + 138.0f, STAGE5_BOSS_ARMS_WIDTH_SIZE - 360.0f, STAGE5_BOSS_ARMS_HEIGHT_SIZE - 225.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 1);
	}
	//type�̒l��1�̂Ƃ����t�g�A�[���̓����蔻��\��
	else if (m_arms_type == 2)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_px + 698.0f, m_py + 138.0f, STAGE5_BOSS_ARMS_WIDTH_SIZE - 360.0f, STAGE5_BOSS_ARMS_HEIGHT_SIZE - 225.0f, ELEMENT_ENEMY, OBJ_STAGE5_BOSS_ARMS, 2);
	}

}

//�A�N�V����
void CObjStage5BossArms::Action()
{
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�A�[���^�C�v��1�̂Ƃ��A���C�g�A�[���p�̓����蔻��\��
	if (m_arms_type == 1)
	{
		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px + 160.0f, m_py + 138.0f);
	}
	//�A�[���^�C�v��2�̂Ƃ��A���t�g�A�[���p�̓����蔻��\��
	else if (m_arms_type == 2)
	{
		//�����蔻��X�V
		HitBoxUpData(Hits::GetHitBox(this), m_px + 698.0f, m_py + 138.0f);
	}

	//�e�ۂƂ���������g�o��1���炷
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_arm_hp -= 1;
	}

	//�g�o��0�ɂȂ�����I�u�W�F�N�g����
	if (m_arm_hp == 0)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�A�[������������HitBox�������B
		return;
	}
	
	
}

//�h���[
void CObjStage5BossArms::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�E�r(���C�g�A�[��)---------------------------------------
	//�A�[���^�C�v��1�̂Ƃ��̓��C�g�A�[����`��
	if (m_arms_type == 1)
	{
		//�؂���ʒu
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		src.m_left = 0.0f;
		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		//�`��
		Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);

	}

	//���r(���C�g�A�[��)---------------------------------------
	//�A�[���^�C�v��2�̂Ƃ��̓��t�g�A�[����`��
	if (m_arms_type == 2)
	{
		//�؂���ʒu
		src.m_top = STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		src.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_right = src.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		src.m_bottom = src.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;

		//�`��ʒu
		dst.m_top = m_py - objmap->GetScrollY();
		dst.m_left = STAGE5_BOSS_ARMS_WIDTH_SIZE + m_px - objmap->GetScrollX();
		dst.m_right = dst.m_left + STAGE5_BOSS_ARMS_WIDTH_SIZE;
		dst.m_bottom = dst.m_top + STAGE5_BOSS_ARMS_HEIGHT_SIZE;
		//�`��
		Draw::Draw(GRA_STAGE5_BOSS_ARMS_ALL, &src, &dst, color, 0.0f);
	}
}