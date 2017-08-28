//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBlock::CObjBlock(int map[MAP_Y_MAX][MAP_X_MAX])
{

}

//�C�j�V�����C�Y
void CObjBlock::Init()
{

}


//�A�N�V����
void CObjBlock::Action()
{
}
//�h���[
void CObjBlock::Draw()
{
	
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
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy, int* bt
)
{
	//��l���̏Փˏ�ԗp�t���O�̏�����
	*up = (false);
	*down = (false);
	*left = (false);
	*right = (false);

	//����ł���u���b�N�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//��l���ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//���������߂�
					float len = sqrt(rvx * rvx + rvy * rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
					{
						r = abs(r);
					}
					else
					{
						r = 360.0f - abs(r);
					}
					//len��������̒����̂��Z���ꍇ�ɓ���
					if (len < 88.0f)
					{

						//�p�x�ŏ㉺���E�𔻒�
						if ((r < 45 && r > 0) || r > 315)
						{
							//�E
							*right = (true);					//��l���̍��̕������Փ˂��Ă���
							*x = bx + 64.0f + (scroll);   //�u���b�N�̈ʒu�{��l���̕�
							*vx = -(*vx) * 0.1f; //-VX*�����W��
						}
						if (r > 45 && r < 135)
						{
							//��
							*down = (true);					//��l���̉��̕������Փ˂��Ă���
							*y = by - 64.0f;				//�u���b�N�̈ʒu�{��l���̕�
															//��ނ�n���̃X�^�[�g�ƃS�[���̂ݕύX����
							if (m_map[i][j] >= 2)
							{
								*bt = m_map[i][j];			//�u���b�N�v�f ( type )����l���ɓn��
							}
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = (true);					//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 64.0f + (scroll);	//�u���b�N�̈ʒu�{��l���̕�
							*vx = -(*vx) * -0.1f; //-VX*�����W��
						}
						if (r > 255 && r < 315)
						{
							//��
							*up = (true);					//��l���̏�̕������Փ˂��Ă���
							*y = by + 64.0f;				//�u���b�N�̈ʒu�{��l���̕�
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}


	}
}
