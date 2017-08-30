#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjRope.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
//����1	float x		:�����ʒuX
//����2	float y		:�����ʒuY
CObjRope::CObjRope(int x, int y)
{
	m_px = x;
	m_py = y;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//��l�����{������ʒu�ɕύX
	x -= obj_m->GetScrollX();
	y -= obj_m->GetScrollY();
	//�����ʒu�����߂�
	m_px = x;
	m_py = y;
	//���������߂�
	m_speed = 6.5f;

	//�}�E�X�̈ʒu�Ǝ�l���̈ʒu����}�E�X�̊p�x�����߂�
	//�}�E�X�̈ʒu���擾
	double mous_x = Input::GetPosX();
	double mous_y = Input::GetPosY();

	//��l���̈ʒu����}�E�X�̈ʒu�̃x�N�g�����擾
	double vector_x = mous_x - x;
	double vector_y = mous_y - y;

	//�Εӎ擾
	double hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//�p�x�����߂�
	m_angle = acos(vector_x / hypotenuse);
	//�p�x�����Ɉړ�
	m_vx = cos(m_angle) * m_speed;
	m_angle = m_angle * 180.0 / 3.14;

	//�}�E�X��Y�ʒu����l����Y�ʒu��艺��������
	if (mous_y > y)
	{
		//180���`360���̒l�ɂ���
		m_angle = 360 - abs(m_angle);
	}
	//�}�E�X��Y�ʒu������Y�ʒu����
	if (mous_y < y)
	{
		m_vy = -sin(acos(vector_x / hypotenuse)) * m_speed;
	}
	else
	{
		m_vy = sin(acos(vector_x / hypotenuse)) * m_speed;
	}
}

//�C�j�V�����C�Y
void CObjRope::Init()
{
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_PLAYER, OBJ_ROPE, 1);

}

//�A�N�V����
void CObjRope::Action()
{
	//��ʊO�ւ����������
	if (m_px < -(BULLET_SIZE + BULLET_SIZE / 2) || //���@��]���Ă邩���Ȃ̂ŏ����]�T����������
		m_px > WINDOW_SIZE_W ||   //�E
		m_py < -(BULLET_SIZE + BULLET_SIZE / 2) || //��@��]���Ă邩���Ȃ̂ŏ����]�T����������
		m_py > WINDOW_SIZE_H     //��
		)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//���[�v����������HitBox�������B
		return;
	}

	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//���[�v�X�C�b�`�ƏՓ˂����Ƃ��̏���
	if(hit->CheckObjNameHit(OBJ_ROPE_SWITCH) != nullptr)
	{
		;
	}

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	hit->SetPos(m_px, m_py);//HitBox�̈ʒu���X�V
}

//�h���[
void CObjRope::Draw()
{
}