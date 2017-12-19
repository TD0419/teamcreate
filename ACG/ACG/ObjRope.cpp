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
//����1,2	:��l���̘r�̈ʒu
//����3,4	:�}�E�X�̈ʒu
CObjRope::CObjRope(float arm_x, float arm_y,float mous_x,float mous_y)
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//���[�v�̏����ʒu�����߂�
	m_px = arm_x;
	m_py = arm_y;

	//���������߂�
	m_speed = 6.5f;
	
	//R�����������̃}�E�X�̈ʒu��ۑ�
	m_moux = mous_x; 
	m_mouy = mous_y; 

	//��l���̘r��(�X�N���[�����l��������ʏ�ł�)�ʒu��ۑ�
	m_hero_arm_x = arm_x - objmap->GetScrollX();
	m_hero_arm_y = arm_y - objmap->GetScrollY();

	//��l���̘r����}�E�X�ւ̃x�N�g�����擾
	float vector_x = m_moux - m_hero_arm_x;
	float vector_y = m_mouy - m_hero_arm_y;

	//�Εӎ擾
	float hypotenuse = sqrt(vector_y * vector_y + vector_x * vector_x);

	//�Εӂ̑傫����1�ɂ������̃x�N�g�������߂�
	vector_x /= hypotenuse;
	vector_y /= hypotenuse;

	//�X�s�[�h�������Ĉړ��x�N�g����ݒ肷��
	m_vx = vector_x * m_speed;
	m_vy = vector_y * m_speed;
}

//�C�j�V�����C�Y
void CObjRope::Init()
{
	m_caught_flag = false;//false = �t���OOFF true = �t���OON
	m_r_key_flag = false;
	m_tarzan_point_flag = false;
	
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
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	
	//��l���̃I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��]�u���b�N�̃X�C�b�`�̃I�u�W�F�N�g�������Ă���
	CObjRollBlockSwitch* objrolls = (CObjRollBlockSwitch*)Objs::GetObj(OBJ_ROLL_BLOCK_SWITCH);

	//��ʊO�ɂ����
	if(WindowCheck(m_px,m_py,ROPE_SIZE, ROPE_SIZE) == false)
	{
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//���[�v����������HitBox�������B
		return;
	}
	
	//HitBox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//���[�v�̍폜�����𒲂ׂ�
	RopeDelete();

	//���[�v�X�C�b�`�Ɠ������ĂȂ��Ȃ�R�L�[��������
	if (m_caught_flag == false)
	{
		if (Input::GetMouButtonR() == true)
		{
			m_r_key_flag = true; //���[�v��R�L�[�ŏ����Ȃ��悤�ɂ���
		}
	}

	//���[�v�X�C�b�`�ƏՓ˂����Ƃ��A���[�v������������悤�ɂ���
	if (hit->CheckObjNameHit(OBJ_ROPE_SWITCH) != nullptr)
	{
		m_vx = 0.0f; //���[�v�{�̂̈ړ����x��0�ɂ��ă��[�v�𓮂��Ȃ��悤�ɂ���
		m_vy = 0.0f;

		objhero->SetVecX(0.0f);

		m_caught_flag = true;		//���[�v����������t���O��ON�ɂ���

		if (Input::GetMouButtonR() == false)//�@R�L�[�������ĂȂ��Ȃ烍�[�v��R�L�[�ŏ�����悤�ɂ���
		{
			m_r_key_flag = false;
		}
	}

	//�^�[�U���|�C���g�ƏՓ˂����Ƃ��A���[�v������������悤�ɂ���
	if(hit->CheckObjNameHit(OBJ_TARZAN_POINT)!=nullptr)
	{
		//���[�v�X�C�b�`�ƐڐG����ƁA���[�v������������(�������~�܂�)
		/*m_px -= m_vx ;
		m_py -= m_vy */;
		m_caught_flag = true;		//���[�v����������t���O��ON�ɂ���

		//�^�[�U���|�C���g�I�u�W�F�N�g�Ɠ������Ă������Avx���T�ȏ�Avy��-6.2�ȉ�����Ȃ��Ƃ�
		if (hit->CheckObjNameHit(OBJ_TARZAN_POINT) != nullptr&&m_vx <= 5.0f&&m_vy >= -6.2f)
		{
			m_tarzan_point_flag = true;//�t���O��ON�ɂ���
									   //����l���������Ă���m_vx��0�ɂ���B���ꂾ���ł͂܂������̂ŉ��̏���������
			objhero->SetVecX(0.0f);
		}
		else
		{
			m_tarzan_point_flag = false;		//�^�[�U�������|����t���O��OFF�ɂ���
			this->SetStatus(false);		//���g�ɏ������߂��o���B
			Hits::DeleteHitBox(this);	//���[�v����������HitBox�������B
		}
		if (Input::GetMouButtonR() == false)//�@R�L�[�������ĂȂ��Ȃ烍�[�v��R�L�[�ŏ�����悤�ɂ���
		{
			m_r_key_flag = false;
		}
	}	
	else
	{
		//�ړ�
		m_px += m_vx;
		m_py += m_vy;
	}

	//�o�O���������̂ŏ�Ƃ킯�܂���
	//��]���p�̃X�C�b�`�ƏՓ˂����Ƃ��A���[�v������������悤�ɂ���
	if (hit->CheckObjNameHit(OBJ_ROLL_BLOCK_SWITCH) != nullptr)
	{
		//�@�X�e�[�W�T�̉�]�u���b�N�X�C�b�`�������Ă鎞��R�L�[�������Ă����[�v�������Ȃ��悤�ɂ���
		if (objrolls->GetKeyFlag() == true)
		{
			m_r_key_flag = true;
		}
		else if (objrolls->GetKeyFlag() == false && Input::GetMouButtonR() == false)
		{
			m_caught_flag = true;
			m_r_key_flag = false;
		}
		//�@�X�e�[�W5�̉�]�u���b�N�X�C�b�`���Ō�܂ōs���������[�v�������I�ɏ����悤�ɂ���
		if (objrolls->GetLastRoll() == true)
		{
			this->SetStatus(false);		//���g�ɏ������߂��o��
			Hits::DeleteHitBox(this);	//���[�v����������HitBox�������B
			return;
		}
	}

	//��]�u���b�N�̃X�C�b�`�Ɠ������Ă���ꍇ
	if (hit->CheckObjNameHit(OBJ_ROLL_BLOCK_SWITCH) != nullptr)
	{
		m_vx = 0.0f; //���[�v�{�̂̈ړ����x��0�ɂ��ă��[�v�Ɖ�]�u���b�N�̃X�C�b�`�𗣂ꂳ���Ȃ��悤�ɂ���
		m_vy = 0.0f;
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(hit, m_px, m_py);
	
	//��l���̘r�̈ʒu���X�V
	//��l�����E�������Ă���Ƃ��̈ʒu
	if (objhero->GetPosture() == 0.0f)
	{
		m_hero_arm_x = objhero->GetPosX() + 64.0f - objmap->GetScrollX();
		m_hero_arm_y = objhero->GetPosY() + 80.0f - objmap->GetScrollY();
	}
	//��l�������ƌ����Ă���Ƃ��̈ʒu
	else
	{
		m_hero_arm_x = objhero->GetPosX() - objmap->GetScrollX();
		m_hero_arm_y = objhero->GetPosY() + 80.0f - objmap->GetScrollY();
	}
}

//�h���[
void CObjRope::Draw()
{
	float color[4] = {1.0f,0.6f,0.0f,1.0f};

	//��l���I�u�W�F�N�g�����擾
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l�������݂��Ă�����
	if (objhero != nullptr)
	{
		RopeDraw(color);//���[�v�̕`��
	}
}

// ���[�v�̕`��֐�
//����1	�`��F�̔z��
void CObjRope::RopeDraw(float color[])				
{
	//�}�b�v�I�u�W�F�N�g�����擾
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�`��̑���
	float drow_size = 2;

	//�_��łʒu�Ǝ�l���̘r�̋���
	float drow_px = 0.0f;
	float drow_py = 0.0f;

	//�_��łʒu�̈ړ��ʗp�ϐ�
	float drow_vx;
	float drow_vy;

	//�ω��ʂ����߂�	(���[�v�̐�[ - ��l���̘r�̈ʒu)
	float change_x = (m_px - objmap->GetScrollX()) - m_hero_arm_x;
	float change_y = (m_py - objmap->GetScrollY()) - m_hero_arm_y;

	//�`��̕����𒲂ׂ�-------------------------------------------
	int pattan;//�`������̕ۑ��p�ϐ��i1�E��:2�E��:3����:4�����j

	if (change_x >= 0.0f)//X�̕ω��ʂ���
	{
		if (change_y >= 0.0f)	//Y�̕ω��ʂ���
			pattan = 2;//�E��
		else					//Y�̕ω��ʂ���
			pattan = 1;//�E��
	}
	else //X�̕ω��ʂ���
	{
		if (change_y >= 0.0f)	//Y�̕ω��ʂ���
			pattan = 4;//����
		else					//Y�̕ω��ʂ���
			pattan = 3;//����
	}
	//�`��̕����𒲂ׂ� �I���-------------------------------------------

	//X�̕ω��ʂ�Y�̕ω��ʂ��傫���ꍇ
	if (abs(change_x) > abs(change_y))
	{
		//X����ɐ�������

		//�`����������Ƃɓ_��łʒu�̈ړ��ʂ����߂�----------------------
		switch (pattan)
		{
			case 1://�E��
			case 2://�E��
			{
				drow_vx = 1.0f;							//X�͉E�ɂP��������
				drow_vy = change_y / change_x;			//Y�͌X������������
				break;
			}
			case 3://����
			case 4://����
			{
				drow_vx = -1.0f;						//X�͍��ɂP��������
				drow_vy = -1.0f*(change_y / change_x);	//Y��(-1*�X��)����������
				break;
			}
		}
		//�`����������Ƃɓ_��łʒu�̈ړ��ʂ����߂� �I���----------------------

		while (abs(drow_px) <= abs(change_x)) //�_��łʒu�Ǝ�l���̘r�̋���X�@���@�ω���X�ɂȂ�܂Ń��[�v
		{
			//�_��`�悷��
			Draw::DrawHitBox(m_hero_arm_x + drow_px, m_hero_arm_y + drow_py, drow_size, drow_size, color);

			//�_�̑łʒu�̍X�V
			drow_px += drow_vx;
			drow_py += drow_vy;
		}
	}
	//Y�̕ω��ʂ�X�̕ω��ʂ��傫���ꍇ
	else
	{
		//Y����ɐ�������

		//�`����������Ƃɓ_��łʒu�̈ړ��ʂ����߂�----------------------
		switch (pattan)
		{
			case 1://�E��
			case 3://����
			{
				drow_vy = -1.0f;						//Y�͏�ɂP��������
				drow_vx = -1.0f*(change_x / change_y);	//X��(-1*�X��)����������
				break;
			}
			case 2://�E��
			case 4://����
			{
				drow_vy = 1.0f;							//Y�͉��ɂP��������
				drow_vx = change_x / change_y;			//X�͌X������������
				break;
			}
		}
		//�`����������Ƃɓ_��łʒu�̈ړ��ʂ����߂� �I���----------------------

		while (abs(drow_py) <= abs(change_y)) //�_��łʒu�Ǝ�l���̘r�̋���Y�@���@�ω���Y�ɂȂ�܂Ń��[�v
		{
			//�_��`�悷��
			Draw::DrawHitBox(m_hero_arm_x + drow_px, m_hero_arm_y + drow_py, drow_size, drow_size, color);

			//�_�̑łʒu�̍X�V
			drow_px += drow_vx;
			drow_py += drow_vy;
		}
	}
}

//���[�v�̏���������𒲂ׂ�
void CObjRope::RopeDelete()
{
	//HitBox�̏��������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//��l���̃I�u�W�F�N�g�������Ă���
	CObjHero* objhero = (CObjHero*)Objs::GetObj(OBJ_HERO);

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
		return;
	}

	//��ɓ��������ꍇ���[�v������
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROCK))
	{
		return;
	}

	//���t�g�ɓ��������ꍇ���[�v������
	if (DeleteCheckObjNameHit(hit, this, OBJ_LIFT))
	{
		return;
	}

	//�؂ɓ��������ꍇ���[�v������
	if (DeleteCheckObjNameHit(hit, this, OBJ_WOOD))
	{
		return;
	}

	//���ɓ��������ꍇ���[�v������
	if (DeleteCheckObjNameHit(hit, this, OBJ_WATER))
	{
		return;
	}

	//Lastwall(��)�ɂ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_LAST_WALL))
	{
		return;
	}
	//���ԂƓ������������
	if (DeleteCheckObjNameHit(hit, this, OBJ_WIRE_MESH))
	{
		return;
	}
	//��]�u���b�N�Ɠ���������폜
	if (DeleteCheckObjNameHit(hit, this, OBJ_ROLL_BLOCK))
	{
		return;
	}
	
	//���[�v�������Ă������ǂ����𒲂ׂ�
	bool rope_delete_r_key = objhero->GetRopeDeleteRKey();

	//���[�v���������蔻�肪ON�̎��AR�������ꂽ�烍�[�v���폜
	if (Input::GetMouButtonR() == true && m_r_key_flag == false && m_caught_flag == true && rope_delete_r_key == true)
	{
		m_caught_flag = false;		//���[�v����������t���O��OFF�ɂ���
		m_tarzan_point_flag = false;		//�^�[�U�������|����t���O��OFF�ɂ���
		this->SetStatus(false);		//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);	//���[�v����������HitBox�������B
		return;
	}
}