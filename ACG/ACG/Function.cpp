#include "Function.h"
#include "GameHead.h"

//HitBox�̈ʒu���X�V����֐�
//����1 �X�V����HitBox�|�C���^
//����2 ���݂�HitBox�̈ʒuX
//����2 ���݂�HitBox�̈ʒuY
void HitBoxUpData(CHitBox* hit,float m_px,float m_py)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//HitBox�̈ʒu���̕ύX
	hit->SetPos(m_px - obj_m->GetScrollX(), m_py);
}