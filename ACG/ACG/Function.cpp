#include "Function.h"
#include "GameHead.h"
//�I�u�W�F�N�g���m���Փ˂����Ƃ��ɏ�������֐�
//����1�@HitBox�|�C���^
//����2�@���肵�����I�u�W�F�N�g�|�C���^
//����3�@�I�u�W�F�N�g�l�[��
//�߂�l bool �@�������Ă邩�A�������ĂȂ���
bool DeleteCheckObjNameHit(CHitBox* hit, CObj* cobj, OBJ_NAME objname)
{
	//�w�肵���I�u�W�F�N�g�ƃl�[�����ݒ肳��Ă�I�u�W�F�N�g���������������
	if (hit->CheckObjNameHit(objname) != nullptr)
	{
		cobj->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(cobj);	//��������HitBox�������B
		return true;				//�������Ă�
	}
	return false;					//�������ĂȂ�
}

//HitBox�̈ʒu���X�V����֐�
//����1 �X�V����HitBox�|�C���^
//����2 ���݂�HitBox�̈ʒuX
//����3 ���݂�HitBox�̈ʒuY
void HitBoxUpData(CHitBox* hit,float m_px,float m_py)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBox�̈ʒu���̕ύX
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY());
}
//HitBox�̈ʒu�Ƒ傫�����X�V����֐�
//����1 �X�V����HitBox�|�C���^
//����2 ���݂�HitBox�̈ʒuX
//����3 ���݂�HitBox�̈ʒuY
//����4	���݂�HitBox�̕�
//����5	���݂�HitBox�̍���
void HitBoxUpData(CHitBox* hit, float m_px, float m_py, float w, float h)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBox�̈ʒu���̕ύX
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY(),w,h);
}

//��ʂ̊O�ɏo�Ă��邩���肷��֐�
//����1,2 :�I�u�W�F�N�g�̃|�W�V����
//����3,4 :�I�u�W�F�N�g�̃T�C�Y
//�߂�l�F�@��ʓ��Ftrue�A��ʊO�Ffalse
bool WindowCheck(float m_px, float m_py,float obj_size_x, float obj_size_y)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	float x = m_px - objmap->GetScrollX();
	float y = m_py - objmap->GetScrollY();

	//��܂��͉��Ń`���b�N
	if (y < 0 - obj_size_y || y > WINDOW_SIZE_H)
		return false;
	//���܂��͉E�Ń`�F�b�N
	if (x < 0 - obj_size_x || x > WINDOW_SIZE_W)
		return false;

	return true;
}

//�u���b�NA�ƃu���b�NB�̓����蔻��
//�u���b�NA�����������ꍇ�ړ����Ȃ��u���b�N
//�u���b�NB�����������ꍇ�ړ�����u���b�N
//����1  float  ax		:�u���b�NA��X�ʒu
//����2  float  ay		:�u���b�NA��Y�ʒu
//����3  float  aw		:�u���b�NA�̕�
//����4  float  ah		:�u���b�NA�̍���
//����5  float* bx		:�u���b�NB��X�ʒu �|�C���^
//����6  float* by		:�u���b�NB��Y�ʒu �|�C���^
//����7  float  bw		:�u���b�NB�̕�
//����8  float  bh		:�u���b�NB�̍���
//����9  float* bvx		:�u���b�NB��X�ړ��� �|�C���^
//����10 float* bvy		:�u���b�NB��Y�ړ��� �|�C���^
//�߂�l	int			:�����������ǂ���||�ǂ��ɓ����������@0=�����薳���F1=B���猩�ď�F2=B���猩�ĉ��F3=B���猩�ĉE:4=B���猩�č�
int HitTestOfAB(float ax, float ay, float aw, float ah,
	float* bx, float* by, float bw, float bh,
	float* bvx, float* bvy)
{
	float ax_min = ax;			//�u���b�NA��X���W�ŏ�
	float ay_min = ay;			//�u���b�NA��Y���W�ŏ�
	float ax_max = ax_min + aw;	//�u���b�NA��X���W�ő�
	float ay_max = ay_min + ah;	//�u���b�NA��Y���W�ő�

	float bx_min = *bx;			//�u���b�NB��X���W�ŏ�
	float by_min = *by;			//�u���b�NB��Y���W�ŏ�
	float bx_max = bx_min + bw;	//�u���b�NB��X���W�ő�
	float by_max = by_min + bh;	//�u���b�NB��Y���W�ő�

	//�͂ݏo�����e�͈�
	float bleed_x = 5.0f;
	float bleed_y = 20.0f;

	//�����蔻��`�F�b�N
	if (ax_max < bx_min);//A���B���E
	else if (bx_max < ax_min);//A���B����
	else if (ay_max < by_min);//A���B����
	else if (by_max < ay_min);//A���B����
	else	//�����肠��B
	{
		//�u���b�NA�̏�
		if (by_max - ay_min < bleed_y)
		{
			if (*bvy >= 0.0f)
			{
				*bvy = 0.00000f;//Y�ړ��ʂ�0�ɂ���
				*by -= by_max - ay_min-1.390f;//�Ԃ�Ԃ邷��̂�-1.390f���Ă���
				return 2;
			}
		}
		//�u���b�NA�̉�
		if (ay_max - by_min < bleed_y)
		{
			if (*bvy <= 0.0f)
			{
				*bvy = 0.00000f;//Y�ړ��ʂ�0�ɂ���
				*by += ay_max - by_min;
				return 1;
			}
		}
		//�u���b�NA�̍�
		if (bx_max - ax_min < bleed_x)
		{
			if (*bvx >= 0.0f)
			{
				*bvx = 0.00000f;//X�ړ��ʂ�0�ɂ���
				*bx -= bx_max - ax_min + 0.001f;//�������ăW�����v����Ə�ɏ���Ă��܂��̂Ł{0.001���Ă���
				return 3;
			}
		}
		//�u���b�NA�̉E
		if (ax_max - bx_min < bleed_x)
		{
			if (*bvx <= 0.0f)
			{
				*bvx = 0.00000f;//X�ړ��ʂ�0�ɂ���
				*bx += ax_max - bx_min + 0.001f;//�������ăW�����v���Ə�ɏ���Ă��܂��̂Ł{0.001���Ă���
				return 4;
			}
		}
	}
	return 0;
}