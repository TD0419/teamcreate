//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "Function.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBlock::CObjBlock(int x, int y)
{
	m_px = x * BLOCK_SIZE;
	m_py = y * BLOCK_SIZE;
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{	
	//�����蔻��
	Hits::SetHitBox(this, m_px, m_py, BLOCK_SIZE, BLOCK_SIZE, ELEMENT_BLOCK, OBJ_BLOCK, 1);

}

//�A�N�V����
void CObjBlock::Action()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//��l���I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		HeroHit();//�����蔻��̏������s��
	}
	
	//�{�X�I�u�W�F�N�g�ƏՓ˂��Ă����
	if (hit->CheckObjNameHit(OBJ_BOSS) != nullptr)
	{
		BossHit();//�����蔻��̏������s��
	}

	//HitBox�̈ʒu���X�V����
	HitBoxUpData(Hits::GetHitBox(this), m_px, m_py);
}

//�h���[
void CObjBlock::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,1.0f, 1.0f };

	RECT_F src, dst;

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�`��ʒu
	dst.m_top = m_py - obj_m->GetScrollY();
	dst.m_left = m_px - obj_m->GetScrollX();
	dst.m_right = dst.m_left + BLOCK_SIZE;
	dst.m_bottom = dst.m_top + BLOCK_SIZE;

	//�`��
	Draw::Draw(2, &src, &dst, color, 0.0f);

}

void CObjBlock::HeroHit()
{
	//���g��HitBox�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;	//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_HERO);//�Փ˂̏���hit_data�ɓ����

	//��l���I�u�W�F�N�g�������Ă���
	CObjHero* obj_hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^�������
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�������Ă���p�x�������Ă���

			//�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{
				obj_hero->bu = true;
				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				obj_hero->SetPosY(m_py - HERO_SIZE_Y);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225)
			{
				obj_hero->SetVecX(0.0f);//��l����X�����̈ړ����O�ɂ���
				obj_hero->SetPosX(m_px - HERO_SIZE_X);//��l���̈ʒu���u���b�N�̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				obj_hero->SetVecY(0.0f);//��l����Y�����̈ړ����O�ɂ���
				obj_hero->SetPosY(m_py + BLOCK_SIZE);//��l���̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
		}
	}
}

//�m�F�p�Ƀ{�X�ł�p�ӂ��܂����B����A�폜�ύX���Ă����܂��܂���B
void CObjBlock::BossHit()
{
	//���g��HitBox���擾
	CHitBox*hit = Hits::GetHitBox(this);

	HIT_DATA** hit_data;						//�Փ˂̏�������\����
	hit_data = hit->SearchObjNameHit(OBJ_BOSS); //�Փ˂̏���hit_data�ɓ����

	//�f�o�b�O�p�{�X�I�u�W�F�N�g�����擾
	CObjBoss* obj_boss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);

	for (int i = 0; i < hit->GetCount(); i++)
	{
		//�f�[�^����
		if (hit_data[i] != nullptr)
		{
			float r = hit_data[i]->r;//�Ԃ����Ă���p�x�������Ă���

			//�u���b�N�̉E�����Փ˂��Ă���ꍇ
			if (0 < r && r < 45 || 315 < r && r < 360)
			{
				obj_boss->SetVecX(0.0f);//�{�X��X�����̈ړ����O�ɂ���
				obj_boss->SetPosX(m_px + BLOCK_SIZE);//�{�X�̈ʒu���u���b�N�̉E���܂ł��炷
			}
			//�u���b�N�̏㑤���Փ˂��Ă���ꍇ
			else if (45 < r && r < 125)
			{
				obj_boss->SetVecY(0.0f);//�{�X��Y�����̈ړ����O�ɂ���
				obj_boss->SetPosY(m_py - BOSS_SIZE);//�{�X�̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
			//�u���b�N�̍������Փ˂��Ă���ꍇ
			else if (125 < r && r < 225)
			{
				obj_boss->SetVecX(0.0f);//�{�X��X�����̈ړ����O�ɂ���
				obj_boss->SetPosX(m_px - BOSS_SIZE);//�{�X�̈ʒu���u���b�N�̍����܂ł��炷
			}
			//�u���b�N�̉������Փ˂��Ă���ꍇ
			else if (225 < r && r < 315)
			{
				obj_boss->SetVecY(0.0f);//�{�X��Y�����̈ړ����O�ɂ���
				obj_boss->SetPosY(m_py + BLOCK_SIZE);//�{�X�̈ʒu���u���b�N�̏㑤�܂ł��炷
			}
		}
	}
}

// BlockHit�֐�
// ����1  float x        :������s��object��X�ʒu
// ����2  float y        :������s��object��Y�ʒu
// ����3  bool scroll_on :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue = �^���� false = �^���Ȃ��j�@
// ����4  bool* up       :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
// ����5  bool* down     :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
// ����6  bool* left     :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
// ����7  bool* right    :�㉺���E����̏㕔���ɓ������Ă��邩�ǂ�����Ԃ�
// ����8  float* vx      :���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
// ����9  float* vy      :�㉺���E���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l�ς��ĕԂ�
// ����10 int* bt        :�������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s���I�u�W�F�N�g�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
//void CObjBlock::BlockHit(
//	float *x, float *y, bool scroll_on,
//	bool*up, bool* down, bool* left, bool* right,
//	float* vx, float*vy, int* bt
//)
//{
//	//��l���̏Փˏ�ԗp�t���O�̏�����
//	*up = (false);
//	*down = (false);
//	*left = (false);
//	*right = (false);
//
//	//����ł���u���b�N�̎�ނ̏�����
//	*bt = 0;
//
//	//m_map�̑S�v�f�ɃA�N�Z�X
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 100; j++)
//		{
//			if (m_map[i][j] > 0 && m_map[i][j] != 4)
//			{
//				//�v�f�ԍ������W�ɕύX
//				float bx = j * 64.0f;
//				float by = i * 64.0f;
//
//				//�X�N���[���̉e��
//				float scroll = scroll_on ? m_scroll : 0;
//
//				//��l���ƃu���b�N�̓����蔻��
//				if ((*x/* + (-scroll)*/ + 64.0f > bx) && (*x /*+ (-scroll)*/ < bx + 64.0f) && (*y + HERO_SIZE_Y > by) && (*y < (by + BLOCK_SIZE)))
//				{
//					//�㉺���E����
//
//					//vector�̍쐬
//					float rvx = (*x /*+ (-scroll)*/) - bx;
//					float rvy = *y - by;
//
//					//���������߂�
//					float len = sqrt(rvx * rvx + rvy * rvy);
//
//					//�p�x�����߂�
//					float r = atan2(rvy, rvx);
//					r = r * 180.0f / 3.14f;
//
//					if (r <= 0.0f)
//					{
//						r = abs(r);
//					}
//					else
//					{
//						r = 360.0f - abs(r);
//					}
//					//len��������̒����̂��Z���ꍇ�ɓ���
//					if (len < 88.0f)
//					{
//
//						//�p�x�ŏ㉺���E�𔻒�
//						if ((r < 45 && r > 0) || r > 315)
//						{
//							//�E
//							*right = (true);					//��l���̍��̕������Փ˂��Ă���
//							*x = bx + 64.0f /*+ (scroll)*/;   //�u���b�N�̈ʒu�{��l���̕�
//							*vx = -(*vx) * 0.1f; //-VX*�����W��
//						}
//						if (r > 45 && r < 135)
//						{
//							//��
//							*down = (true);					//��l���̉��̕������Փ˂��Ă���
//							*y = by - HERO_SIZE_Y ;				//�u���b�N�̈ʒu�{��l���̕�
//															//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
//							if (m_map[i][j] >= 2)
//							{
//								*bt = m_map[i][j];			//�u���b�N�v�f ( type )����l���ɓn��
//							}
//							*vy = 0.0f;
//						}
//						if (r > 135 && r < 225)
//						{
//							//��
//							*left = (true);					//��l���̉E�̕������Փ˂��Ă���
//							*x = bx - 64.0f /*+ (scroll)*/;	//�u���b�N�̈ʒu�{��l���̕�
//							*vx = -(*vx) * -0.1f; //-VX*�����W��
//						}
//						if (r > 255 && r < 315)
//						{
//							//��
//							*up = (true);					//��l���̏�̕������Փ˂��Ă���
//							*y = by + HERO_SIZE_Y;				//�u���b�N�̈ʒu�{��l���̕�
//							if (*vy < 0)
//							{
//								*vy = 0.0f;
//							}
//							
//						}
//					}
//				}
//			}
//		}
//
//
//	}
//}
//