#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjMap.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjMap::CObjMap(int map[MAP_Y_MAX][MAP_X_MAX])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int)*(MAP_Y_MAX * MAP_X_MAX));
}

//�C�j�V�����C�Y
void CObjMap::Init()
{
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;
}

//�A�N�V����
void CObjMap::Action()
{
	//�X�N���[����(�u���b�N�̐��Ɍv�Z���ēn��)�����ƂɃI�u�W�F�N�g�𐶐�����
	CreateObj(int(m_scroll_x / BLOCK_SIZE), int(m_scroll_y / BLOCK_SIZE));	//���}�b�v�f�[�^�̓ǂݍ��݂�����܂Ŏg���Ȃ��̂ŃR�����g�����Ă���	
}

//�X�N���[���ʂ����ƂɃI�u�W�F�N�g�̐���������֐�
//	scroll_block_num_x:	X���̌��݂̃X�N���[���ʂ��u���b�N������
//	scroll_block_num_y:	Y���̌��݂̃X�N���[���ʂ��u���b�N������
// *���̊֐����̃R�����g�̃X�N���[���ʂ͂��ׂĈ����œn���Ă����u���b�N���Ŋ��Z�������̂��Ƃ��w��
void CObjMap::CreateObj(int scroll_block_num_x, int scroll_block_num_y)
{
	//y�̒l���X�N���[����Y�@����@�E�B���h�E���Ɏ��܂�ő�l�{�X�N���[����Y�@�܂��́@�}�b�v�̍ő�l�@�ɒB����܂ŉ�
	for (int y = scroll_block_num_y ; y < MAP_Y_MAX && y < scroll_block_num_y + MAP_WINDOW_MAX_Y; y++)
	{
		//x�̒l���X�N���[����X�@����@�E�B���h�E���Ɏ��܂�ő�l�{�X�N���[����X�@�܂��́@�}�b�v�̍ő�l�@�ɒB����܂ŉ�
		for (int x = scroll_block_num_x; x < MAP_X_MAX && x < scroll_block_num_x + MAP_WINDOW_MAX_X; x++)
		{			
			//y�̒l���i�N���G�C�g���C���̏㉺�{�X�N���[����Y�j�Ɠ��� �܂��́@x�̒l���i�N���G�C�g���C���̍��E�{�X�N���[����X�j�Ɠ��� �Ȃ�
			if (	y == (CREATE_LINE_UP	+ scroll_block_num_y)	|| y == ( CREATE_LINE_DOWN	+ scroll_block_num_y) ||
					x == (CREATE_LINE_LEFT	+ scroll_block_num_x)	|| x == ( CREATE_LINE_RIGHT + scroll_block_num_x)
				)
			{
				//�G�I�u�W�F�N�g�������
				if (m_map[y][x] == MAP_ENEMY)
				{
					//�G�I�u�W�F�N�g���쐬���� �f�o�b�O�Ȃ̂ō��̓q�[���[�I�u�W�F�N�g�𐶐�)
					CObjEnemy* ObjEnemy = new CObjEnemy(x , y);
					Objs::InsertObj(ObjEnemy, OBJ_ENEMY, 10);
	
					//�I�u�W�F�N�g�̐�����ǂ������ɂ���
					m_map[y][x] = MAP_SPACE;
				}
			}
		}
	}
}

//�h���[
void CObjMap::Draw()
{
	//�`��J���[
	float color[4] = { 1.0f,1.0f,0.5f, 1.0f };

	//�}�b�v�I�u�W�F�N�g�������Ă���
	CObjMap* obj_m = (CObjMap*)Objs::GetObj(OBJ_MAP);

	for (int map_y = 0; map_y < MAP_Y_MAX; map_y++)
	{
		for (int map_x = 0; map_x < MAP_X_MAX; map_x++)
		{
			RECT_F src, dst;
			//�u���b�N(�m�[�}��)
			switch (m_map[map_y][map_x])
			{
			case MAP_BLOCK:
				//�؂���ʒu
				src.m_top = 0.0f;
				src.m_left = 0.0f;
				src.m_right = 512.0f;
				src.m_bottom = 512.0f;

				//�`��ʒu
				dst.m_top = map_y * BLOCK_SIZE - obj_m->GetScrollY();
				dst.m_left = map_x * BLOCK_SIZE - obj_m->GetScrollX();
				dst.m_right = dst.m_left + BLOCK_SIZE;
				dst.m_bottom = dst.m_top + BLOCK_SIZE;

				//�`��
				Draw::Draw(0, &src, &dst, color, 0.0f);
				break;

			
			default:
				break;
			}
		}
	}
}
