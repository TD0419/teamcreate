#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjHero.h"
#include"Function.h"
#include <math.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
//����1 x			:�����|�W�V����X
//����2	y			:�����|�W�V����Y
//����3	remaining	:�c�@��
CObjHero::CObjHero(int x, int y, int remaining)
{
	m_px = (float)x * BLOCK_SIZE;
	m_py = (float)y * BLOCK_SIZE;
	//�c�@���̏�����
	m_remaining = remaining;	
}

//�A�N�V����
void CObjHero::Action()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	m_count++;//�J�E���^�[�𑝂₷

	if (m_count >= 10000)//�J�E���g����萔�ɂȂ��0�ɖ߂�
	{
		m_count = 50;//�J�E���g�̏�����
		
		//�e�̐����ϐ����X�V
		m_before_shot_time = SHOT_INTERVAL - (10000 - m_before_shot_time) ;
	}

	GetBlockInformation();	//��l���̍����A�^���A�E���ɂ���u���b�N�����擾
	
	//�����Ƀ��X�^�[�g----------------------------------
	//m_py��2000�ȉ��Ȃ烊�X�^�[�g����
	if (m_hero_die_screen_out == true)
	{
		//��O�ɏo���烊�X�^�[�g
		Scene::SetScene(new CSceneMain(-1));
	}

	//�}�E�X�̈ʒu���擾
	m_mous_x = (float)Input::GetPosX();
	m_mous_y = (float)Input::GetPosY();

	//�u���b�N�I�u�W�F�N�g�������Ă���
	CObjBlock* objblock = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�Ƃ̓����蔻��
	objblock->AllBlockHit(&m_px, &m_py, 46.0f, HERO_SIZE_HEIGHT,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy);
		
	LandingCheck();//���n�t���O�̍X�V

	LadderScene();//��q����

	MoveScene();//�ړ�

	Scroll();//�X�N���[��

	Shot();//���C

	RopeThrow();//���[�v�ˏo

	HitScene();	//�����蔻��

	if (m_posture == 0.0f)
	{
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(Hits::GetHitBox(this), m_px+3, m_py + 14);
	}
	else
	{
		//HitBox�̈ʒu���X�V����
		HitBoxUpData(Hits::GetHitBox(this), m_px+15, m_py + 14);
	}
}

//��l���̍����A�^���A�E���ɂ���u���b�N�����擾
void CObjHero::GetBlockInformation()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�^���̃u���b�N����D�悷��
	for (int i = 0; i < 3; i++)
	{
		//��l����X�ʒu(���� = 0;�^�� = HERO_SIZE_WIDTH/2;�E�� = HERO_SIZE_WIDTH)
		int pos_x = 0;
		//�E��
		if (i == 1)
		{
			pos_x = (int)HERO_SIZE_WIDTH;
		}
		//����
		else if (i == 2)
		{
			pos_x = (int)HERO_SIZE_WIDTH / 2;
		}
		//��l����X�ʒu(�}�b�v�̗v�f��)
		int x = ((int)m_px + pos_x) / (int)BLOCK_SIZE;
		//��l����Y�ʒu(�}�b�v�̗v�f��)
		//�������ɂ���
		int y = ((int)m_py + 1 + (int)HERO_SIZE_HEIGHT) / (int)BLOCK_SIZE;
		//�u���b�N���0�Ŗ����Ȃ�擾
		if (objmap->GetMap(x, y) != 0)
		{
			m_block_type = objmap->GetMap(x, y);
			m_block_type_up = objmap->GetMap(x, y - 1); //��l���̏�̃}�b�v�ԍ������
		}
	}
}

//�ړ��֐�
void CObjHero::MoveScene()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//���[�v�I�u�W�F�N�g���������Ă���
	CObjRope* objrope = (CObjRope*)Objs::GetObj(OBJ_ROPE);
	
	//���[�v���o���Ă��鎞�����[�v���^�[�U���|�C���g�Ɉ����������Ă���
	if (m_rope_ani_con == false || (objrope != nullptr && objrope->GetTarzanPointFlag() == true))
	{
		//���ɓ����������ƓG�ɓ����������͓����Ȃ�
		if (m_hero_die_water == false && m_ani_frame_enemy_die == false && m_py < 2000.0f)
		{
			//D�L�[�������ꂽ�Ƃ��F�E�ړ��@
			if (Input::GetVKey('D') == true)
			{
				m_vx += 0.5f;
				m_ani_frame_stop_move = 0;  //��l���������Ă�Ȃ�0�ɂ���
				m_posture = 0.0f;		    //��l���̌���
				m_ani_time_move += 1;
			}
			//A�L�[�������ꂽ�Ƃ��F���ړ��@
			else if (Input::GetVKey('A') == true)
			{
				m_vx -= 0.5f;
				m_ani_frame_stop_move = 0;  //��l���������Ă�Ȃ�0�ɂ���

				if (m_ladder_updown == 1)   //�͂����ɓo���Ă�Ƃ��͌�����ς��Ȃ�
					m_posture = 0.0f;		//��l���̌���
				else
					m_posture = 1.0f;		//��l���̌���
				m_ani_time_move += 1;
			}
			else
			{
				m_ani_frame_stop_move = 1;	//�L�[���͂���������1������
				m_ani_frame_move = 1;		//�L�[���͂������ꍇ�͐Î~�t���[���ɂ���
				m_ani_time_move = 0;
			}
		}
	}

	//�A�j���[�V�����̊��o�Ǘ�
	if (m_ani_time_move > m_ani_max_time_move)
	{
		m_ani_frame_move += 1;
		m_ani_time_move = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame_move == 4)
	{
		m_ani_frame_move = 0;
	}

	//�W�����v--------------------------------------------------------------------

	//���[�v���o���Ă��鎞�͓����Ȃ�  �͂���������Ă��鎞�������Ȃ��@�@���ɓ������Ă���Ƃ��ƓG�Ɠ����������������Ȃ�
	if (Input::GetVKey(VK_SPACE) == true && m_ladder_updown == 0 &&
		m_rope_ani_con == false && m_hero_die_water == false &&
		m_ani_frame_enemy_die == false && l_jump == false)
	{
		if (m_hit_down == true)
		{
			m_vy = -13.0f;
		}
	}

	//�W�����v�I��-------------------------------------------------------------------------------------


	//���L�[�������ꂽ�Ƃ��F���ɉ�����i�f�o�b�O�j
	if (Input::GetVKey(VK_DOWN) == true)
	{
		m_vy = 20.0f;
	}
	//���L�[�������ꂽ�Ƃ��F��ɉ�����i�f�o�b�O�j
	if (Input::GetVKey(VK_UP) == true)
	{
		m_vy = -20.0f;
	}

	//���C
	m_vx += -(m_vx * 0.098f);

	//���R�����^��
	// �t���O�������Ă�����d�͂�������
	if (m_gravity_flag == true)
		m_vy += 9.8f / (16.0f);

	//�ő嗎���X�s�[�h�𒴂��Ȃ��悤�ɂ���
	if (m_gravity_flag == true && m_vy > m_fall_speed_max)
		m_vy = m_fall_speed_max;

	//���[�v�I�u�W�F�N�g���L�� ���� �^�[�U���|�C���g�Ɉ����������Ă���Ȃ�
	//���[�v�̈ʒu�𒆐S�ɐU��q�̓���������
	if ((objrope != nullptr && objrope->GetTarzanPointFlag() == true))
	{
		float ab_x = objrope->GetPosX() - m_px;//��l�����烍�[�v�̃x�N�g��X����
		float ab_y = objrope->GetPosY() - m_py;//��l�����烍�[�v�̃x�N�g��Y����

		//���[�v�̈ʒu
		float rope_x = objrope->GetPosX(), rope_y = objrope->GetPosY();

		//�U��q�f�[�^�̒l�����߂邩�ǂ����t���O��NO�̂Ƃ�
		//�l(�����A�ӂ蕝�A����)�����߂�
		if (pendulum_data.find_value_flag == true)
		{
			//�U��q�̎��̒������v�Z
			pendulum_data.length = sqrt((ab_x * ab_x) + (ab_y * ab_y));

			//�U��q�̎��̒������獡����(����)�Ȃ̂������߂�					���d�͉����x��0.98�Ȃ̂�9.8�ɒ����Ă���
			//�U��q�̓�����
			pendulum_data.time = 2.0f*3.141592f*sqrt(pendulum_data.length / (pendulum_data.gravity * 10.0f));

			//���[�v��X�ʒu����l�����E�ɂ����玞��(�������[�ɂ���)
			if (m_px > rope_x)
				pendulum_data.time *= -1;

			//�ӂ蕝���v�Z		����Œ������Ă��܂��@���ߕ�������̂ł����炻��ɂ��Ă��������B
			pendulum_data.pretend_width = pendulum_data.length / 7.0f;

			//�ӂ蕝����萔�𒴂��Ȃ��悤�ɂ���
			if (pendulum_data.pretend_width > 50.0f)
				pendulum_data.pretend_width = 50.0f;
			//�l�����߂��̂Ńt���O��OFF�ɂ���
			pendulum_data.find_value_flag = false;
		}
		//���[�v�����l���̃x�N�g���̊p�x���v�Z
		float r = 2 * pendulum_data.pretend_width*sinf(sqrt(pendulum_data.gravity / pendulum_data.length)*pendulum_data.time);

		r = r * 3.14f / 180.0f;//���W�A���x�ɂ���

		//�u���b�N�ɓ������Ă��Ȃ�������ړ��x�N�g�������ߎ�����i�߂�
		if (!m_hit_down && !m_hit_left && !m_hit_right && !m_hit_up)
		{
			//�ړ��x�N�g�����v�Z			�@						���̌v�Z�͈ړ��x�N�g����������肽����������
			m_vx = cosf(r) - sinf(r) * pendulum_data.length + (rope_x - m_px);
			m_vy = sinf(r) + cosf(r) * pendulum_data.length + (rope_y - m_py);
			//������i�߂�
			pendulum_data.time += 1.0f;
		}
		//�u���b�N�ɓ������Ă���==�U��q�̉^����~���Ă���Ȃ�
		//������x�l�����߂����̂Ńt���O��ON�ɂ���
		else
			pendulum_data.find_value_flag = true;
		
	}
	//���[�v���^�[�U���|�C���g�Ɉ����������Ă��Ȃ�������
	//�l�����߂�t���O��ON�ɂ���
	else
		pendulum_data.find_value_flag = true;
	
	//�ړ�
	m_px += m_vx;
	m_py += m_vy;

	//�ړ��悪��ʊO�Ȃ�ړ������ɖ߂�
	if (WindowCheck(m_px - HERO_SIZE_WIDTH, m_py, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT) == false)
		m_px -= m_vx;

	//�r�̊p�x�����߂�-----------------------

	//�}�E�X�|�C���^�Ƃ̋��������߂�

	float x = m_mous_x - (m_px - objmap->GetScrollX() + (HERO_SIZE_WIDTH / 2.0f));	//X
	float y = m_mous_y - (m_py - objmap->GetScrollY() + (HERO_SIZE_HEIGHT / 2.0f));//Y
	float inclination = sqrt(x * x + y * y);				//�Ε�


	if (y > 0.0f)	//y�̒l��0���傫���Ȃ�p�x�𐳂����l�ɏC��
		m_r = 360.0f - m_r;

	//���W�A���l�����߂�
	float rad = asinf(-y / inclination);
	//�p�x�����߂�
	m_r = rad * 180.0f / 3.14f;
}

//�X�N���[�������̊֐�
void CObjHero::Scroll()
{
	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�E�ɃX�N���[���ł�
	//���_���E�ɂ���
	if ((m_px + HERO_SIZE_WIDTH) - objmap->GetScrollX() > SCROLL_LINE_RIGHT)
	{
		//�����𒲂ׂ�
		float scroll =  ((m_px + HERO_SIZE_WIDTH) - objmap->GetScrollX())-SCROLL_LINE_RIGHT;
		//�X�N���[���ɉe����^����
		objmap->SetScrollX(scroll);
	}
	//���ɃX�N���[���ł�
	if (m_px - objmap->GetScrollX() < SCROLL_LINE_LEFT &&
		objmap->GetScrollX() > 0)
	{
		//�����𒲂ׂ�
		float scroll = SCROLL_LINE_LEFT - (m_px - objmap->GetScrollX());
		//�X�N���[���ɉe����^����
		objmap->SetScrollX(-scroll);
	}

	//��ɃX�N���[���ł�
	if (m_py - objmap->GetScrollY() < SCROLL_LINE_UP)
	{
		//�����𒲂ׂ�
		float scroll = (m_py - objmap->GetScrollY()) - SCROLL_LINE_UP;
		//�X�N���[���ɉe����^����
		objmap->SetScrollY(scroll);
	}
	
	//���ɃX�N���[���ł�
	//���_�����ɂ���
	if ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY() > SCROLL_LINE_DOWN&& objmap->GetScrollY() < WINDOW_SIZE_H)
	{
		//�����𒲂ׂ�
		float scroll = SCROLL_LINE_DOWN - ((m_py + HERO_SIZE_HEIGHT) - objmap->GetScrollY());
		//�X�N���[���ɉe����^����
		objmap->SetScrollY(-scroll);
	}
}

// ����1 float : �~��1�t���[�����Ƃ̔��a�̕ω���
// ����2 color : �~�̐F
// ����3 type  : �~�̏�����
// ���S���ƃS�[�����p�̉~��`�悷��֐�
void CObjHero::CircleDraw(float add_radius, float color[4], int type)
{
	// �}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);
	// �����̂��ʒu�̏�����
	float ball_y = 0.0f;

	//�����ʒu�ݒ�       
	float ball_x = m_px + HERO_SIZE_WIDTH / 2.f - objmap->GetScrollX();

	// Hero������ł�����
	if (type == Die)
	{
		//�������̒����ʒu 
		if (m_hero_die_flag == false)
		{
			m_screen_out = m_py; //�Â��Ȃ钆���̈ʒu����l����ǂ�Ȃ����邽��
			m_hero_die_flag = true;
		}

		//�������̔��a�̒����ʒu
		if (m_py > 2000.0f)
			ball_y = m_screen_out - 1450.0f + HERO_SIZE_HEIGHT / 1.5f;
		//�������ȊO�̔��a�̒����ʒu
		else if (m_py < 2000.0f)
			ball_y = m_py + HERO_SIZE_HEIGHT / 1.5f - objmap->GetScrollY();
	}
	// Hero���X�e�[�W���N���A���Ă����ԂȂ�
	else if (type == Clear)
	{
		ball_y = m_py + HERO_SIZE_HEIGHT / 1.5f - objmap->GetScrollY();
	}

	//���a�����񂾂�Z������
	m_radius += add_radius;
	
	//���l�p�`�̂P�ӂ̒���
	//������Β����قǌy��
	//�Z����ΒZ���قǏd����
	float one_side = 5.5f;

	//���a���ŏ��ɂȂ�����V�[���ڍs����i��̂ق��ɂ���j
	// Hero������ł�����
	if (type == Die)
	{
		// ���a��0�ȉ��Ȃ烊�X�^�[�g
		if (m_radius <= 0.0f)
		{
			m_radius = 0.0f;
			Scene::SetScene(new CSceneMain(-1)); // ���X�^�[�g
		}
	}
	// Hero���X�e�[�W���N���A���Ă����ԂȂ�
	else if (type == Clear)
	{
		// ���a�����l�𒴂�����V�[���ڍs
		if (m_radius >= 768.0f)
		{
			//�X�e�[�W�T�Ȃ�N���A�̃V�[���ɂ���
			if (((UserData*)Save::GetData())->stagenum == 5)
			{
				Scene::SetScene(new CSceneGameClear());
				return;
			}
			else
			{
				//�X�e�[�W�J�E���g�𑝂₵�Ď��̃X�e�[�W�ɂ���
				Objs::ListDeleteSceneObj();//�I�u�W�F�N�g�̍폜
				((UserData*)Save::GetData())->stagenum += 1;
				Scene::SetScene(new CSceneMain());
			}
		}
	}

	//�~�O���l�p�`�Ŗ��ߐs����
	for (float y = 0.0f; y < (float)WINDOW_SIZE_H; y += one_side)
	{
		for (float x = 0.0f; x < (float)WINDOW_SIZE_W; x += one_side)
		{
			//�~�̒�
			if ((x - ball_x)*(x - ball_x) + (y - ball_y)*(y - ball_y) <= m_radius * m_radius)
			{
				if (type == Clear) // �~�̒���h��
					Draw::DrawHitBox(x, y, one_side, one_side, color);
			}
			//�~�O
			else
			{
				if (type == Die)	// �~�̊O��h��
					Draw::DrawHitBox(x, y, one_side, one_side, color);
			}
		}
	}
}

//���n�ł��Ă邩�ǂ����𒲂ׂ�֐�
void CObjHero::LandingCheck()
{
	bool c1,c2,c3,c4,c5,c6,c7;//�`�F�b�N���ʂ�ۑ����邽�߂̕ϐ�:�`�F�b�N���ڂ𑝂₷���тɐ��𑝂₷�K�v������
	
	c1 = HitUpCheck(OBJ_LIFT); //���t�g�Ƃ̒��n�`�F�b�N
	c2 = HitUpCheck(OBJ_WOOD); //�؂Ƃ̒��n�`�F�b�N
	c3 = HitUpCheck(OBJ_LIFT_MOVE); //�������t�g�Ƃ̒��n�`�F�b�N
	c4 = HitUpCheck(OBJ_ROLL_BLOCK);//��]����u���b�N
	c5 = HitUpCheck(OBJ_FALLING_LIFT);//�����郊�t�g
	c6 = HitUpCheck(OBJ_FALLING_BLOCK);//������u���b�N
	c7 = HitUpCheck(OBJ_WIRE_MESH);//����
	//�`�F�b�N���ڂ̂ǂꂩ��ł�true�Ȃ�
	if ( c1 == true || c2 ==true || c3 == true || c4 ==true || c5 == true || c6 == true||c7==true)
		m_hit_down = true;//���n�t���O���I���ɂ���

}

//�w�肵���I�u�W�F�N�g�̏㑤�ɓ������Ă��邩����ׂ�
//�����@���ׂ����I�u�W�F�N�g�l�[��
//�߂�l�@���n���Ă����:true�@���Ă��Ȃ����:false
bool CObjHero::HitUpCheck(int obj_name)
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);
	
	//�����Ŏ����Ă����I�u�W�F�N�g�Ƃ������Ă��邩���ׂ�
	if (hit->CheckObjNameHit(obj_name) != nullptr)
	{
		HIT_DATA** hit_data;	//�Փ˂̏�������\����
		hit_data = hit->SearchObjNameHit(obj_name);//�Փ˂̏���hit_data�ɓ����

		//�������Ă��鐔�����ׂ�
		for (int i = 0; i < hit->GetCount(); i++)
		{
			//�f�[�^�������
  			if (hit_data[i] != nullptr)
			{
				//�Փ˂�������̈ʒu�A���A���������擾
				HIT_BOX* hit = Hits::GetHitBox(hit_data[i]->o)->GetHitBox();
				//�}�b�v�I�u�W�F�N�g�������Ă���
				CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

				//HitTestOfAB�֐����g���ƕύX����Ă��܂��̂ŉ��ϐ��쐬
				float hero_x = m_px;
				float hero_y = m_py;
				float hero_vx = m_vx;
				float hero_vy = m_vy;
				//�Փ˂����������擾
				int collision = HitTestOfAB(hit->x+objmap->GetScrollX(), hit->y+objmap->GetScrollY(), hit->w, hit->h,
					&hero_x, &hero_y, HERO_SIZE_WIDTH, HERO_SIZE_HEIGHT,
					&hero_vx, &hero_vy
				);
				//��l�����猩�ĉ��ɏՓ˂����璅�n���Ă���
				if (collision == 2)
					return true;
			}
		}
	}
	return false;//���n���Ă��Ȃ�
}

//��q�֐�
void CObjHero::LadderScene()
{
	//�͂����I�u�W�F�N�g�������Ă���
	CObjLadders* objladders = (CObjLadders*)Objs::GetObj(OBJ_LADDERS);

	if (objladders != nullptr)
	{
		//��l���̂����ɒʏ�u���b�N����������͂����ɏ���Ă��Ȃ�����ɂ���
		if (m_block_type == MAP_BLOCK)
		{
			//�͂����ɓo���Ă��Ȃ�
			m_ladder_updown = 0;
		}
		l_jump = objladders->GetHeroJumpCon();  //�͂����ƐڐG���Ă��邩�ǂ����𒲂ׂ�
		objladders->HeroHit(m_px, m_py);
	}

	//�͂����̃A�j���[�V�����^�C����i�߂�
	m_ani_time_ladders += m_ladder_ani_updown;//�͂����������Ă���

	//�͂�����MAXTIME�𒴂���ƃA�j���[�V������i�߂�
	if (m_ani_time_ladders > m_ani_max_time_ladders)
	{
		m_ani_frame_ladders += 1;
		m_ani_time_ladders = 0;
	}

	//�Ō�܂ŃA�j���[�V�������i�ނƍŏ��ɖ߂�
	if (m_ani_frame_ladders == 4)
	{
		m_ani_frame_ladders = 0;
	}
}

//���[�v������֐�
void CObjHero::RopeThrow() {

	//Scene�@�J�X���� 
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
	if (Input::GetMouButtonR() == true && m_hero_die_water == false && m_ani_frame_enemy_die == false)
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
}

void CObjHero::Shot()
{
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
						float x_add = cosf(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sinf(m_bullet_r* 3.14f / 180.f) * 50.0f;

						//�e�ۍ쐬
						Audio::Start(FIRING);//���y�X�^�[�g

						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 30.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);

						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
						m_before_shot_time = m_count;//�e�����������Ԃ��L������
					}
					else if (m_posture == 1.0f && m_ladder_updown == 0)//��l�������������Ă��Ă͂����ɓo���Ă��Ȃ����Ƃ��E�����甭��
					{
						// �e�۔��ˈʒu���v�Z���邽�߂̊p�x����
						if (abs(m_r) > 90.0f)
							m_bullet_r = m_r;
						else
							m_bullet_r = 180.0f + m_r;

						// �e�ۂ̊p�x���甭�ˈʒu�̂�������߂�(*50.0f�͘r�̉��ɂ��~�̔��a)
						float x_add = cosf(m_bullet_r* 3.14f / 180.f) * 50.0f;
						float y_add = sinf(m_bullet_r* 3.14f / 180.f) * 50.0f;

						Audio::Start(FIRING);//���y�X�^�[�g

						CObjBullet* objbullet = new CObjBullet(m_px + x_add + 20.0f, m_py + y_add + 55.0f, m_bullet_r);
						Objs::InsertObj(objbullet, OBJ_BULLET, 10);

						m_bullet_control = false; //�e�ۂ��o�Ȃ��t���O�ɂ���B
						m_before_shot_time = m_count;//�e�����������Ԃ��L������
					}
				}
			}
		}
	}
	else
	{
		//�O���shot�����莞�Ԍo�߂��Ă����
		if (m_count - m_before_shot_time >= SHOT_INTERVAL)
			m_bullet_control = true; //���N���b�N���ĂȂ���Βe�ۂ��ł�t���O�ɂ���B
	}
}

//�����蔻��̊֐�
void CObjHero::HitScene()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�j�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_NEEDLE) != nullptr)
	{
		m_hero_die_enemy = true; //��l���̐j�ɂ��������Ƃ��̎��S�t���O��ON�ɂ���
	}
	//���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_WATER) != nullptr)
	{
		m_hero_die_water = true; //��l���̐��ɂ��������Ƃ��̓M���t���O��ON�ɂ���
	}

	//�G�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		m_hero_die_enemy = true; //��l���̓G�ɂ��������Ƃ��̎��S�t���O��ON�ɂ���
	}

	//��l���̓G�ɓ��������Ƃ��̎��S�t���O��ON�Ȃ玀�S�A�j���[�V����������
	if (m_hero_die_enemy == true)
	{
		//��l�����G�ɓ����������̃A�j���[�V�����^�C����i�߂�
		m_ani_time_enemy_die += 1;
		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time_enemy_die > m_ani_max_time_enemy_die)
		{
			m_ani_frame_enemy_die += 1;
			m_ani_time_enemy_die = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƎ�l���폜
		if (m_ani_frame_enemy_die == 4)
		{
			this->SetStatus(false);		//���g���폜
			Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

			return;
		}
	}

	//��l���̐��ɓ��������Ƃ��̓M���t���O��ON�Ȃ�M���A�j���[�V����������
	if (m_hero_die_water == true)
	{
		//������̂��������ɂ���i���R�����̂������ł������ɂȂ�j
		m_vy = 0.0f;
		//��l�������ɓ����������̃A�j���[�V�����^�C����i�߂�
		m_ani_time_water_die += 1;
		//�A�j���[�V�����̊��o�Ǘ�
		if (m_ani_time_water_die > m_ani_max_time_water_die)
		{
			m_ani_frame_water_die += 1;
			m_ani_time_water_die = 0;
		}

		//�Ō�܂ŃA�j���[�V�������i�ނƎ�l���폜
		if (m_ani_frame_water_die == 3)
		{
			this->SetStatus(false);		//���g���폜
			Hits::DeleteHitBox(this);	//�q�b�g�{�b�N�X���폜

			return;
		}
	}
}