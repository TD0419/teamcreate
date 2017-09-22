#include "Function.h"
#include "GameHead.h"

//HitBox�̈ʒu���X�V����֐�
//����1 �X�V����HitBox�|�C���^
//����2 ���݂�HitBox�̈ʒuX
//����2 ���݂�HitBox�̈ʒuY
void HitBoxUpData(CHitBox* hit,float m_px,float m_py)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBox�̈ʒu���̕ύX
	hit->SetPos(m_px - objmap->GetScrollX(), m_py - objmap->GetScrollY());
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