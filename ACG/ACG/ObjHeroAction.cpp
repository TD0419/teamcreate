
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjHero.h"

void CObjHero::RopeThrow() {

	//Scene�@�J�X���� ���H�H�H??

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	//���[�v�I�u�W�F�N�g�������Ă���
	CObjRope* obj_rope = (CObjRope*)Objs::GetObj(OBJ_ROPE);

	bool rope_caught = false; //���[�v�����[�v�X�C�b�`�Ɠ������Ă��邩�ǂ������m���߂�ϐ�
	bool rope_delete = false; //���[�v�������Ă邩���������m���߂�ϐ�

	//�}�E�X�̈ʒu���v���C���[���猩�Ăǂ̕��������ׂ邽�߂̕ϐ�
	float mous_rope_way = 0.0f;//�E�F0.0���@���F1.0�� �E�����ŏ�����

	if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//��l����荶���N���b�N�����Ƃ�
		mous_rope_way = 1.0f;

	//�E�N���b�N����������̕�������ɕύX�����̂Ń}�[�W���鎞�͌��̓z�������Ă��������c���Ă�������
	//�E�N���b�N����������   ���ɓ������Ă���Ƃ��ƓG�ɓ������Ă���Ƃ��͓����Ȃ�
	if ( Input::GetMouButtonR() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
	{
		//��l�����N���b�N���Ă����ꍇ
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//�q�[���[�N���b�N�����ꍇ
		}
		//�}�E�X�̈ʒu����낶��Ȃ��@���[�v�A�j���̃t���O���Ȃ��@���[�v�̍폜�t���O���Ȃ�
		else if (m_posture == mous_rope_way && m_rope_ani_con == false && m_rope_delete_r_kye == false)
		{
			m_rope_moux = (float)Input::GetPosX(); //���[�v���ˏo�����Ƃ��̃}�E�X�̈ʒuX������
			m_rope_mouy = (float)Input::GetPosY(); //���[�v���ˏo�����Ƃ��̃}�E�X�̈ʒuY������
			m_rope_ani_con = true;

		}
	}

	if (obj_rope != nullptr)//���[�v�I�u�W�F�N�g���o�Ă���ꍇ
	{
		rope_caught = obj_rope->GetCaughtFlag();//���[�v�����[�v�X�C�b�`�ɓ������Ă��邩�̏������炤
		rope_delete = false; //���[�v�͏����Ă��Ȃ�
		m_rope_delete_control = true;
	}
	else //���[�v�I�u�W�F�N�g���o�Ă��Ȃ��ꍇ
	{
		rope_caught = false;
		//���[�v��������悤�ɂ���
		if (m_rope_delete_control == true)
		{
			rope_delete = true; //���[�v��������
			m_rope_delete_control = false;
		}
	}

	//true�Ȃ�A�j���[�V������i�߂� �@�͂����ɓo���Ă���Ƃ��͓����Ȃ�
	if (m_rope_ani_con == true && m_ladder_updown == 0)
	{
		//���[�v�̃A�j���[�V�����t���[����2�ȊO�Ȃ�A�j���[�V������i�߂�
		if (m_ani_frame_rope != 2)
		{
			//���[�v�̃A�j���[�V�����^�C����i�߂�
			m_ani_time_rope += 1;

			//���[�v��MAXTIME�𒴂���ƃA�j���[�V������i�߂�
			if (m_ani_time_rope > m_ani_max_time_rope)
			{
				m_ani_frame_rope += 1;
				m_ani_time_rope = 0;
			}
		}
		//���[�v�̃A�j���[�V�����t���[�����Q�Ȃ烍�[�v���o��
		if (m_ani_frame_rope == 2)
		{
			if (m_rope_control == true)//true�Ȃ烍�[�v���o����
			{
				//���[�v�쐬
				if (m_posture == 0.0f)//��l�����E�������Ă���Ƃ��E�����甭��
				{
					CObjRope* objrope = new CObjRope(m_px + 64.0f, m_py + 80.0f, m_rope_moux, m_rope_mouy);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
					Audio::Start(ROPE);//���[�v�̉��y�X�^�[�g
				}
				else if (m_posture == 1.0f)//��l�������������Ă���Ƃ��������甭��
				{
					CObjRope* objrope = new CObjRope(m_px, m_py + 80.0f, m_rope_moux, m_rope_mouy);
					Objs::InsertObj(objrope, OBJ_ROPE, 10);
					m_rope_control = false;
					Audio::Start(ROPE);//���[�v�̉��y�X�^�[�g
				}
			}
			if (m_rope_control == false) //���[�v���o���Ă��鎞
			{
				m_ani_frame_rope = 2;//�A�j���[�V�������Q�Ŏ~�߂�
				if (rope_delete == true)//���[�v�������Ă���ꍇ
				{
					m_rope_delete_r_kye = true;
					m_ani_frame_rope = 0;//�A�j���[�V�����̃t���[����߂��B
					m_rope_ani_con = false;
				}
			}
		}
		else
			m_rope_control = true;
	}
	//�͂����ɓo���Ă���Ƃ��ɉE�N���b�N��������I�������Ɍ����Ă����̂ł�����C������
	else if (m_ladder_updown != 0)
	{
		m_rope_ani_con = false;
	}

	//�E�N���b�N���Ă��Ȃ��Ƃ�false�ɂ���
	if (Input::GetMouButtonR() == false)
		m_rope_delete_r_kye = false;

	//���[�v�ƃ��[�v�X�C�b�`���������Ă���Ƃ�
	if (rope_caught == true)
	{
		m_rope_delete_r_kye = true; //���[�v��������悤�ɂ���i���[�v���ŏ����j
	}

	//�ˏo�I��------------------------------------------------RopeThrow() end

}

void CObjHero::Shot() {


	//Scene�@�J�X����
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//���N���b�N����������   ���ɓ������Ă���Ƃ��ƓG�ɓ������Ă��鎞�͓����Ȃ�
	if (Input::GetMouButtonL() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
	{

		//��l�����N���b�N���Ă����ꍇ
		if ((m_px - objmap->GetScrollX()) <= m_mous_x && m_mous_x <= ((m_px - objmap->GetScrollX()) + HERO_SIZE_WIDTH))
		{
			;//�q�[���[�N���b�N�����ꍇ
		}
		else
		{
			//�}�E�X�̈ʒu���v���C���[���猩�Ăǂ̕��������ׂ邽�߂̕ϐ�
			float mous_bullet_way = 0.0f;//�E�F0.0���@���F1.0�� �E�����ŏ�����

			if ((m_mous_x - (m_px - objmap->GetScrollX())) < 0)//��l����荶���N���b�N�����Ƃ�
				mous_bullet_way = 1.0f;

			if (m_bullet_control == true)
			{
				//�����Ă�������ƃN���b�N���Ă�������������ŏ����A���[�v�̃A�j���[�V�����̃t���O��false�̏ꍇ
				if (m_posture == mous_bullet_way && m_rope_ani_con == false)
				{
					// �e�۔��ˌ���(�x���@)
					float m_bullet_r;
					
					if (m_posture == 0.0f && m_ladder_updown == 0)//��l�����E�������Ă��Ă͂����ɓo���Ă��Ȃ����Ƃ��E�����甭��
					{
						// �e�۔��ˈʒu���v�Z���邽�߂̊p�x����
						if (m_r > 0.f)
							m_bullet_r = 360.0f - m_r;
						else
							m_bullet_r = -m_r;

						// �e�ۂ̊p�x���甭�ˈʒu�̂�������߂�(*50.0f�͘r�̉��ɂ��~�̔��a)
						float x_add = cos(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sin(m_bullet_r* 3.14f / 180.f) * 50.0f;
						//�e�ۍ쐬
						Audio::Start(FIRING);//���y�X�^�[�g
						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 30.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
					}
					else if (m_posture == 1.0f && m_ladder_updown == 0)//��l�������������Ă��Ă͂����ɓo���Ă��Ȃ����Ƃ��E�����甭��
					{
						// �e�۔��ˈʒu���v�Z���邽�߂̊p�x����
						if (abs(m_r) > 90.0f)
							m_bullet_r = m_r;
						else
							m_bullet_r = 180.0f + m_r;

						// �e�ۂ̊p�x���甭�ˈʒu�̂�������߂�(*50.0f�͘r�̉��ɂ��~�̔��a)
						float x_add = cos(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sin(m_bullet_r* 3.14f / 180.f) * 50.0f;
						Audio::Start(FIRING);//���y�X�^�[�g
						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 20.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);
						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
					}
				}
			}
		}
	}
	else
		m_bullet_control = true; //���N���b�N���ĂȂ���Βe�ۂ��ł�t���O�ɂ���B
















}