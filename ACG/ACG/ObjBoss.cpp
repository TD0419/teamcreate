#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjBoss.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBoss::CObjBoss(int x,int y)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
    m_vx = -1.0f; // �ړ��x�N�g��
    m_vy = 0.0f;
	m_hp = 20; //�{�X�̂g�o
	m_posture = 1.0f; // ������
	m_speed = 1.0f;   // ���x

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 3; //�A�j���[�V�����Ԋu��
	
	// block�Ƃ̏Փˊm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_die_flag = false;
	 //�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT, ELEMENT_ENEMY, OBJ_BOSS, 1);
}

//�A�N�V����
void CObjBoss::Action()
{
	m_ani_time++;//�A�j���[�V�����͗V�тȂ̂ŏ����Ă�����Ă������ł�
	//�A�j���[�V�����̊��o�Ǘ�
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɂ���
	if (m_ani_frame == 8)
	{
		m_ani_frame = 0;
	}
	//HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);
	
	if (m_posture == 0.0f)		// �E�����Ȃ�
		m_vx = m_speed;			// �E�ɐi��
	else if (m_posture == 1.0f) // �������Ȃ�
		m_vx = -m_speed;		// ���ɐi��

	//���C
	m_vx += -(m_vx * 0.098f);

	//���R�����^��
	m_vy += 9.8f / (16.0f);

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx;
	m_py += m_vy;
	
	//�u���b�N�Ƃ̓����蔻����s
	CObjBlock* objblock = (CObjBlock*) Objs::GetObj(OBJ_BLOCK);
	objblock-> BlockHit(&m_px,&m_py,BOSS_SIZE_WIDTH, BOSS_SIZE_HEIGHT,
	&m_hit_up,&m_hit_down,&m_hit_left,&m_hit_right,&m_vx,&m_vy
	);
	
	if (m_hit_right == true)    // �u���b�N�̉E���ɓ������Ă����� 
		m_posture = 0.0f;		// �E�����ɂ���
	else if (m_hit_left == true)// �u���b�N�̍����ɓ������Ă�����
		m_posture = 1.0f;		// �������ɂ���

	CObjDoor* objdoor = (CObjDoor*)Objs::GetObj(OBJ_DOOR);
	//�e�ۂƂ���������HP-1
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{
		m_hp -= 1;
	}

	// �̗͂�0�ȉ��Ȃ�
	if (m_hp <= 0)
	{
		m_die_flag = true;
		Hits::DeleteHitBox(this);	//BOSS�����L����HitBox�ɍ폜����
		this->SetStatus(false);		//���g�ɍ폜���߂��o��
		return;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

}

//�h���[
void CObjBoss::Draw()
{
	//�摜�̐؂���z��
	
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu(	�����z)
	src.m_top = 0.0f;
	src.m_left = m_ani_frame * 128.0-128.0;
	src.m_right = src.m_left+128.0f;
	src.m_bottom = src.m_top + 128.0f;

	//�`��ʒu
	dst.m_top = m_py - objmap->GetScrollY();
	dst.m_left = BOSS_SIZE_WIDTH * m_posture + m_px - objmap->GetScrollX();
	dst.m_right = (BOSS_SIZE_WIDTH - BOSS_SIZE_WIDTH * m_posture) + m_px - objmap->GetScrollX();
	dst.m_bottom = dst.m_top  + BOSS_SIZE_HEIGHT+6;

	////�`��
	/*Draw::Draw(14, &src, &dst, color, 0.0f);*/
	Draw::Draw(4, &src, &dst, color, 0.0f);

}