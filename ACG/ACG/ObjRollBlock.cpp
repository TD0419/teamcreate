//�g�p����w�b�_�[
#include "GameHead.h"
#include "ObjRollBlock.h"
#include "Function.h"

#include "GameL\HitBoxManager.h"

////�R���X�g���N�^
////����1,2	map�̗v�f�ԍ�
//CObjRollBlock::CObjRollBlock(int x,int y,int)
//{
//	m_px = (float)x * BLOCK_SIZE;
//	m_py = (float)y * BLOCK_SIZE;
//}
//
////�C�j�V�����C�Y
//void CObjRollBlock::Init()
//{
//	m_r = 0.0f;	//�p�x������
//	m_count = 0;//�J�E���^�[�̏�����
//
//	m_roll_flag = false;//��]�̃t���O��������
//
//	//�����蔻��Z�b�g
//	Hits::SetHitBox(this,m_px, m_py,ROLL_BLOCK_SIZE_WIDTH, ROLL_BLOCK_SIZE_HEIGHT, ELEMENT_BLOCK, OBJ_ROLL_BLOCK, 1);
//}
//
////�A�N�V����
//void CObjRollBlock::Action()
//{
//	if(m_count<=90)//90�ȉ��Ȃ�
//		m_count++;//�J�E���g�𑝂₷
//
//
//}
//
////�h���[
//void CObjRollBlock::Draw()
//{
//	//�`��J���[
//	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };
//
//	RECT_F src, dst;
//
//	//�}�b�v�I�u�W�F�N�g�������Ă���
//	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
//
//	//�؂���ʒu
//	src.m_top = 0.0f;
//	src.m_left = 0.0f;
//	src.m_right = ROLL_BLOCK_SIZE_WIDTH;
//	src.m_bottom = ROLL_BLOCK_SIZE_HEIGHT;
//
//	//�`��ʒu
//	dst.m_top = m_py - objmap->GetScrollY();
//	dst.m_left =m_px - objmap->GetScrollX();
//	dst.m_right = dst.m_left + ROLL_BLOCK_SIZE_WIDTH;
//	dst.m_bottom = dst.m_top + ROLL_BLOCK_SIZE_HEIGHT;
//
//	//�`��
//	Draw::Draw(GRA_ROLL_BLOCK, &src, &dst, color, m_r);
//}
