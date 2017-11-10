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
//����1	float x		:��l���̘r�̈ʒuX
//����2	float y		:��l���̘r�̈ʒuY
CObjRope::CObjRope(float x, float y)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��l���I�u�W�F�N�g�����擾
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�����ʒu�����߂�
	m_px = x;
	m_py = y;

	//���������߂�
	m_speed = 6.5f;
	
	//�}�E�X�̈ʒu����hero���玝���Ă���̂Ń}�[�W���鎞�͂��������c���Ă��������i�ϐ����������ɕς��Ă��������j
	m_moux = objhero->GetRopeMouX(); //R�����������̃}�E�X�̈ʒuX�������Ă���
	m_mouy = objhero->GetRopeMouY(); //R�����������̃}�E�X�̈ʒuY�������Ă���

	//��l�����{������ʒu�ɕύX
	x -= objmap->GetScrollX();
	y -= objmap->GetScrollY();
	
	//��l���̘r�̈ʒu��ۑ�
	m_hero_arm_x = x;
	m_hero_arm_y = y;

	//��l���̈ʒu����}�E�X�̈ʒu�̃x�N�g�����擾
	float vector_x = m_moux - x;
	float vector_y = m_mouy - y;

	//�Εӎ擾
	float hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//�p�x�����߂�
	m_r = acos(vector_x / hypotenuse);
	
	//�p�x�����Ɉړ�
	m_vx = cos(m_r) * m_speed;

	//�}�E�X��Y�ʒu����l����Y�ʒu��艺��������
	if (m_mouy > y)
	{
		//180���`360���̒l�ɂ���
		m_r = 360.0f - abs(m_r);
	}
	//�}�E�X��Y�ʒu������Y�ʒu����
	if (m_mouy < y)
	{
		m_vy = -sin(m_r) * m_speed;
	}
	else
	{
		m_vy = sin(m_r) * m_speed;
	}
}

//�C�j�V�����C�Y
void CObjRope::Init()
{
	m_caught_flag = false;//false = �t���OOFF true = �t���OON
	m_delete = false;     //false = �t���OOFF true = �t���OON
	
	//�u���b�N�Ƃ̓����蔻��t���O�̏�����
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
						  
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, ROPE_SIZE, ROPE_SIZE, ELEMENT_PLAYER, OBJ_ROPE, 1);
}

//�A�N�V����
void CObjRope::Action()
{
	//��l���̃I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��ʊO�ɂ����
	if(WindowCheck(m_px,m_py,ROPE_SIZE, ROPE_SIZE) == false)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//���[�v����������HitBox�������B
		m_delete =true;  //���[�v�͏����Ă��邱�Ƃ�ϐ��ɓ����
		return;
	}
	else
		m_delete =false;//���[�v�͏����Ă��Ȃ����Ƃ�ϐ��ɓ����
	
	//���[�v��HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);

	// �u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�Ƃ̓����蔻��
	objblock->AllBlockHit(&m_px, &m_py, ROPE_SIZE, ROPE_SIZE,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);

	//�u���b�N�Ƃ������Ă���΍폜����
	if (m_hit_up == true || m_hit_down == true || m_hit_right == true || m_hit_left == true)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//�e�ۂ���������HitBox�������B
		m_delete = true;  //���[�v�̍폜�t���O���I���ɂ���
		return;
	}

	//���[�v�X�C�b�`�ƏՓ˂����Ƃ��A���[�v������������悤�ɂ���
	if(hit->CheckObjNameHit(OBJ_ROPE_SWITCH) != nullptr)
	{
		//���[�v�X�C�b�`�ƐڐG����ƁA���[�v������������(�������~�܂�)
		m_px -= m_vx ;
		m_py -= m_vy ;
		m_caught_flag = true;		//���[�v����������t���O��ON�ɂ���
	
		//����l���������Ă���m_vx��0�ɂ���B���ꂾ���ł͂܂������̂ŉ��̏���������
		objhero->SetVecX(0.0f);
	}
	//���[�v�������Ă������ǂ����𒲂ׂ�
	bool rope_delete_ani_con = objhero->GetRopeDeleteAniCon();

	//���[�v���������蔻�肪ON�̎��AR�������ꂽ�烍�[�v���폜
	if (Input::GetMouButtonR() == true && m_caught_flag==true && rope_delete_ani_con ==true)
	{
		m_delete = true;			//���[�v�͏����Ă��邱�Ƃ�ϐ��ɓ����
		m_caught_flag = false;		//���[�v����������t���O��OFF�ɂ���
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//���[�v����������HitBox�������B
		return;
	}

	//�����|�����܂܈ړ�����ƁA���[�v���Y���ĊO��܂��B
	//���[�v�������|���Ă���Ƃ��͎�l���͓����Ȃ�(�ړ��ł��Ȃ�)�d�l�������ŉ��P�\��

	//�ړ�
	m_px += m_vx ;
	m_py += m_vy ;

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(hit, m_px, m_py);
}

//�h���[
void CObjRope::Draw()
{
	float color[4] = {1.0f,0.6f,0.0f,1.0f};

	//��l���I�u�W�F�N�g�����擾
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�}�b�v�I�u�W�F�N�g�����擾
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//��l���������Ă�������������Ă���
	float hero_postrue = objhero->GetPosture();

	////��l�������݂��Ă������l���ƃ��[�v�����Ԑ���`��(��)
	//if (objhero != nullptr)
	//{
	//	//�`��̑���
	//	int size = 2;

	//	//�_��łʒu�̈ړ��p�ϐ�
	//	float pos_vx; 
	//	float pos_vy;

	//	//�`��ʂ����߂�	(�}�E�X�̈ʒu - ��l���̘r�̈ʒu)
	//	float change_x = m_moux - m_hero_arm_x;
	//	float change_y = m_mouy - m_hero_arm_y;

	//	int pattan;//������ۑ��i1�E��F2�E���F3����:4�����j

	//	//X����
	//	if (change_x > 0.0f)	
	//	{
	//		//Y����
	//		if (change_y > 0.0f)
	//			pattan = 0;
	//		else
	//			pattan = 1;
	//	}
	//	else //X����
	//	{
	//		//Y����
	//		if (change_y > 0.0f)
	//			pattan = 3;
	//		else
	//			pattan = 4;
	//	}

	//	//�p�^�[���ɉ�����
	//	switch(pattan)
	//	{
	//		case 1://�E��
	//		{
	//			break;
	//		}
	//		case 2://�E��
	//		{
	//			break;
	//		}
	//		case 3://����
	//		{
	//			break;
	//		}
	//		case 4://����
	//		{
	//			break;
	//		}
	//	}

	//	//�_��`�悷��
	//	Draw::DrawHitBox(m_hero_arm_x+pos_vx, m_hero_arm_y+pos_vy, size, size, color);
	//}
}