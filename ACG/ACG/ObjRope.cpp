#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\WinInputs.h"
#include "Function.h"

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
	float c[4] = {0.0f,0.0f,0.0f,1.0f};
	//��l���I�u�W�F�N�g�����擾
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	CObjMap* obj_map = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//��l�������݂��Ă������l���Ǝ��g�����Ԑ���`��(��)
	if (obj_hero != nullptr)
	{
		//���A����
		int thick = 2;
		//���g�̈ʒu
		int own_x = m_px;
		int own_y = m_py;
		//�_��`�悷��X�ʒu
		int nextX = obj_hero->GetPosX() - obj_map->GetScrollX();
		//�_��`�悷��Y�ʒu
		int nextY = obj_hero->GetPosY() - obj_map->GetScrollY();
		//���g�����l���̈ʒu���������lX(�ϗ�)
		int deltaX = own_x - nextX;
		//���g�����l���̈ʒu���������lY(�ϗ�)
		int deltaY = own_y - nextY;
		//�ǂ̕����ɐ���`�悷�邩
		int stepX, stepY;
		//�X�e�b�v
		int step = 0;
		//����
		int fraction;

		//X�̕ϗʂ��}�C�i�X�Ȃ�
		if (deltaX < 0)
		{
			//X������-1�ɂ���
			stepX = -1;
		}
		//X�̕ϗʂ��v���X�Ȃ�
		else
		{
			//X�������{1�ɂ���
			stepX = 1;
		}
		//Y�̕ϗʂ��}�C�i�X�Ȃ�
		if (deltaY < 0)
		{
			//Y������-1�ɂ���
			stepY = -1;
		}
		//Y�̕ϗʂ��v���X�Ȃ�
		else
		{
			//Y������+1�ɂ���
			stepY = 1;
		}
		//X�̕ϗʂ�*2����
		deltaX = deltaX * 2;
		//�������{�ɂ���
		if (deltaX < 0)
			deltaX *= -1;
		//Y�̕ϗʂ�*2����
		deltaY = deltaY * 2;
		//�������{�ɂ���
		if (deltaY < 0)
			deltaY *= -1;
		//��l���̈ʒu�ɓ_��ł�
		Draw::DrawHitBox(nextX, nextY, thick, thick, c);
		//�X�e�b�v��i�߂�
		step++;

		//�ϗʂ�X�̂ق����傫��������
		if (deltaX > deltaY)
		{
			//Y�̕ϗʁ[X�̕ϗ�/2
			fraction = deltaY - deltaX / 2;
			//�_��łƂ��Ƃ��Ă���X�ʒu�����g��X�ʒu�ɂȂ�܂œ_��`��
			while (nextX != own_x)
			{
				//�������{�l
				if (fraction >= 0)
				{
					//�_��`�悷��Y�ʒu��i�߂�
					nextY += stepY;
					//X�̕ϗʂ𕪐��Ɉ����Z����
					fraction -= deltaX;
				}
				//�_��`�悷��X�ʒu��i�߂�
				nextX += stepX;
				//Y�̕ϗʂ𕪐��ɉ��Z����
				fraction += deltaY;
				//�_��`��
				Draw::DrawHitBox(nextX, nextY, thick, thick, c);
				//�X�e�b�v��i�߂�
				step++;
			}
		}
		//�ϗʂ�Y�̂ق����傫��������b�b����
		else
		{
			//X�̕ϗʁ[Y�̕ϗ�/2
			fraction = deltaX - deltaY / 2;
			//�_��łƂ��Ƃ��Ă���Y�ʒu�����g��Y�ʒu�ɂȂ�܂œ_��`��
			while (nextY != own_y)
			{
				//�������{�l
				if (fraction >= 0)
				{
					//�_��`�悷��X�ʒu��i�߂�
					nextX += stepX;
					//Y�̕ϗʂ𕪐��Ɉ����Z����
					fraction -= deltaY;
				}
				//�_��`�悷��Y�ʒu��i�߂�
				nextY += stepY;
				//X�̕ϗʂ𕪐��ɉ��Z����
				fraction += deltaX;
				//�_��`��
				Draw::DrawHitBox(nextX, nextY, thick, thick, c);
				//�X�e�b�v��i�߂�
				step++;
			}
		}
	}
}