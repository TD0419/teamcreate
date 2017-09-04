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
	
	//�}�b�v�����ɃI�u�W�F�N�g�𐶐�--------------------------------------
	
	//i���@��ʂɎ��܂�ő�l�@�܂��́@�}�b�v�̍ő�l�ɂȂ�܂ł܂킷
	for (int y = 0; y < MAP_WINDOW_MAX_Y && y<MAP_Y_MAX; y++)
	{
		//j���@��ʂɎ��܂�ő�l�@�܂��́@�}�b�v�̍ő�l�ɂȂ�܂ł܂킷
		for (int x = 0; x < MAP_WINDOW_MAX_X && x<MAP_X_MAX;x++)
		{
			CreateObj(x, y);//�I�u�W�F�N�g�̐���
		}
	}

	//�I�u�W�F�N�g���������	-----------------------------------------------

	//�X�N���[����(�u���b�N�̐��Ɍv�Z���ēn��)�����ƂɃI�u�W�F�N�g�𐶐�����
	ScrollCreateObj(int(m_scroll_x / BLOCK_SIZE), int(m_scroll_y / BLOCK_SIZE));	
}


//�h���[
void CObjMap::Draw()
{
}


//�X�N���[���ʂ����ƂɃI�u�W�F�N�g�̐���������֐�
//	scroll_block_num_x:	X���̌��݂̃X�N���[���ʂ��u���b�N������
//	scroll_block_num_y:	Y���̌��݂̃X�N���[���ʂ��u���b�N������
// *���̊֐����̃R�����g�̃X�N���[���ʂ͂��ׂĈ����œn���Ă����u���b�N���Ŋ��Z�������̂��Ƃ��w��
void CObjMap::ScrollCreateObj(int scroll_block_num_x, int scroll_block_num_y)
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
				CreateObj(x, y);//�I�u�W�F�N�g�𐶐�
			}
		}
	}
}


//�I�u�W�F�N�g�̐������s���֐�
//����1�@�}�b�v�̗v�f��X
//����2�@�}�b�v�̗v�f��Y
void CObjMap::CreateObj(int x, int y)
{
	//�u���b�N�쐬
	if (m_map[y][x] == MAP_BLOCK)
	{
		CObjBlock* obj_block = new CObjBlock(x, y);
		Objs::InsertObj(obj_block, OBJ_BLOCK, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}
	//�u���b�N�쐬
	if (m_map[y][x] == MAP_DOWN_DRAW_BLOCK)
	{
		CObjDownDrawBlock* obj_down_drawblock = new CObjDownDrawBlock(x, y);
		Objs::InsertObj(obj_down_drawblock, OBJ_DOWN_DRAW_BLOCK, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}
	//�͂����쐬
	if (m_map[y][x] == MAP_LADDERS)
	{
		CObjLadders* obj_ladders = new CObjLadders(x, y);
		Objs::InsertObj(obj_ladders, OBJ_LADDERS, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//�{�^���쐬
	if (m_map[y][x] == MAP_BUTTON)
	{
		CObjButton* obj_button = new CObjButton(x, y);
		Objs::InsertObj(obj_button, OBJ_BUTTON, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//���[�v�X�C�b�`
	if (m_map[y][x] == MAP_ROPE_SWITCH)
	{
		CObjRopeSwitch* obj_rope_switch = new CObjRopeSwitch(x, y);
		Objs::InsertObj(obj_rope_switch, OBJ_ROPE_SWITCH, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//���t�g�쐬
	if (m_map[y][x] == MAP_LIFT)
	{
		CObjLift* obj_lift = new CObjLift(x, y);
		Objs::InsertObj(obj_lift, OBJ_LIFT, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//��쐬
	if (m_map[y][x] == MAP_ROCK)
	{
		CObjRock* obj_rock = new CObjRock(x, y);
		Objs::InsertObj(obj_rock, OBJ_ROCK, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//�؍쐬
	if (m_map[y][x] == MAP_WOOD)
	{
		CObjWood* obj_wood = new CObjWood(x, y);
		Objs::InsertObj(obj_wood, OBJ_WOOD, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//���쐬
	if (m_map[y][x] == MAP_WOOD)
	{
		CObjWater* obj_water = new CObjWater(x, y);
		Objs::InsertObj(obj_water, OBJ_WATER, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//�G�쐬
	if (m_map[y][x] == MAP_ENEMY)
	{
		CObjEnemy* obj_enemy = new CObjEnemy(x, y);
		Objs::InsertObj(obj_enemy, OBJ_ENEMY, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}

	//�{�X�쐬
	if (m_map[y][x] == MAP_BOSS)
	{
		CObjBoss* obj_boss = new CObjBoss(x, y);
		Objs::InsertObj(obj_boss, OBJ_BOSS, 9);

		m_map[y][x] = MAP_SPACE;//�������I���Ƌ󔒂�����
	}
}


