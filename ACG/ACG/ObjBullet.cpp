#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjBullet.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�R���X�g���N�^
//����1	float x		:�����ʒuX
//����2	float y		:�����ʒuY
//����3	float angle	:�ړ�����p�x
CObjBullet::CObjBullet(int x, int y)
{
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
	if (mous_y > y )
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
void CObjBullet::Init()
{
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, BULLET_SIZE, BULLET_SIZE, ELEMENT_PLAYER, OBJ_BULLET, 1);
}

//�A�N�V����
void CObjBullet::Action()
{	
	//��ʊO�ւ����������
	if (m_px < -(BULLET_SIZE+BULLET_SIZE/2) || //���@��]���Ă邩���Ȃ̂ŏ����]�T����������
		m_px > WINDOW_SIZE_W||   //�E
		m_py < -(BULLET_SIZE+BULLET_SIZE/2) || //��@��]���Ă邩���Ȃ̂ŏ����]�T����������
		m_py > WINDOW_SIZE_H     //��
		)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	//�G�Ƃ������������
	if (hit->CheckElementHit(ELEMENT_ENEMY)==true)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//��Ƃ������������
	if (hit->CheckObjNameHit(OBJ_ROCK) != nullptr)//���@ElementHit�ɕς��邩��
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}

	//Water(��)�Ƃ������������
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		return;
	}
	
	//�u���b�N�Ƃ��������ꍇ
	if (hit->CheckObjNameHit(OBJ_BLOCK) != nullptr)
	{
		HIT_DATA** hit_data;	//�Փ˂̏�������\����
		hit_data = hit->SearchObjNameHit(OBJ_BLOCK);//�Փ˂̏���hit_data�ɓ����

		float r = hit_data[0]->r;

		//��@�܂��́@���ŏՓ˂��Ă���ꍇ
		if (45 <= r && r < 135 || 225 <= r && r < 315)
		{
			m_vy *= (-1);//�ړ��x�N�g���̏㉺�𔽓]����
		}
		else //���܂��͉E�ŏՓ˂��Ă���ꍇ
		{
			m_vx *= (-1);//�ړ��x�N�g���̍��E�𔽓]����
		}
	}

	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	hit->SetPos(m_px, m_py);//HitBox�̈ʒu���X�V

}

//�h���[
void CObjBullet::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
	RECT_F src, dst;

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu
	dst.m_top = m_py;
	dst.m_left =  m_px;
	dst.m_right = dst.m_left + BULLET_SIZE;
	dst.m_bottom = dst.m_top + BULLET_SIZE;

	Draw::Draw(0, &src, &dst, color, m_angle);

}