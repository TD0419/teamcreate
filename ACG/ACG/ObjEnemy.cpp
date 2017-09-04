#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy::CObjEnemy(int x, int y)
{
	m_px = x * ENEMY_SIZE;
	m_py = y * ENEMY_SIZE;
}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_r = 0.0f;
	m_posture = 0.0f; //�E����1.0f ������0.0f

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 4; //�A�j���[�V�����Ԋu��

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, ENEMY_SIZE,ENEMY_SIZE, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}

//�A�N�V����
void CObjEnemy::Action()
{
	//�ړ�----------------------------------------------

	//�f�o�b�O�p�Ƀ{�^������œ����悤�ɂ��Ă܂��B
	//�K���Ɉړ��������������Ă����܂��܂���B

	//A�L�[�������ꂽ�Ƃ��F���ړ�
	if (Input::GetVKey('J') == true)
	{
		m_posture = 0.0f;
		m_vx -= 5.0f;
		m_ani_time += 1;
	}

	//D�L�[�������ꂽ�Ƃ��F�E�ړ�
	else if (Input::GetVKey('L') == true)
	{
		m_posture = 1.0f;
		m_vx += 5.0f;
		m_ani_time += 1;
	}
	else
	{
		m_ani_frame = 0; //�L�[���͂������ꍇ�͐Î~�t���[���ɂ���
		m_ani_time = 0;
	}

	//�A�j���[�V�����̊��o�Ǘ�
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame == 2)
	{
		m_ani_frame = 0;
	}

	//���C
	//m_vx += -(m_vx * 0.098);

	//���R�����^��
	//m_vy += 9.8 / (16.0f);

	//�ړ��x�N�g�����|�W�V�����ɉ��Z
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��x�N�g����������
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�ړ��I���-----------------------------------------

	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�e�ۂƂ������������
	if (hit->SearchObjNameHit(OBJ_BULLET) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�G����������HitBox�������B
		return;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);

	
}

//�h���[
void CObjEnemy::Draw()
{
	//�摜�̐؂���z��
	int AniData[2] =
	{
		0  , 1 , 
	};

	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 64;
	src.m_right = 64.0f + AniData[m_ani_frame] * 64;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = 0.0f + m_py - obj_m->GetScrollY();
	dst.m_left = (ENEMY_SIZE * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_right = (ENEMY_SIZE - ENEMY_SIZE * m_posture) + m_px - obj_m->GetScrollX();
	dst.m_bottom = dst.m_top + ENEMY_SIZE;

	//�`��
	Draw::Draw(8, &src, &dst, color, m_r);

}