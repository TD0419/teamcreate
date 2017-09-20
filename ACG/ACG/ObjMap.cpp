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
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			m_map[i][j].num = map[i][j];//���l�̃R�s�[
		}
	}
}

//�C�j�V�����C�Y
void CObjMap::Init()
{
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;

	//�t���O�̏�����
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			m_map[i][j].create = true;
		}
	}

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
				//�}�b�v�͈̔͂Ȃ��Ȃ�
				if(x >= 0 && y >= 0 && x < MAP_X_MAX && y < MAP_Y_MAX)
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
	//�t���O���I�t�Ȃ� ������
	if (m_map[y][x].create == false)	return;
	
	switch (m_map[y][x].num)
	{
		case MAP_BLOCK:		//�u���b�N�쐬
		{
			CObjBlock* obj_block = new CObjBlock(x, y);
			Objs::InsertObj(obj_block, OBJ_BLOCK, 9);
			break;
		}
		
		case MAP_LADDERS:	//�͂����쐬
		{
			CObjLadders* obj_ladders = new CObjLadders(x, y);
			Objs::InsertObj(obj_ladders, OBJ_LADDERS, 9);
			break;
		}
		
		case MAP_BUTTON:	//�{�^���쐬
		{
			CObjButton* obj_button = new CObjButton(x, y);
			Objs::InsertObj(obj_button, OBJ_BUTTON, 9);
			break;
		}
		
		case MAP_ROPE_SWITCH:	//���[�v�X�C�b�`�쐬
		{
			CObjRopeSwitch* obj_rope_switch = new CObjRopeSwitch(x, y);
			Objs::InsertObj(obj_rope_switch, OBJ_ROPE_SWITCH, 9);
			break;
		}

		case MAP_LIFT:		//���t�g�쐬
		{
			CObjLift* obj_lift = new CObjLift(x, y);
			Objs::InsertObj(obj_lift, OBJ_LIFT, 9);
			break;
		}
		
		case MAP_ROCK:		//��쐬
		{
			CObjRock* obj_rock = new CObjRock(x, y);
			Objs::InsertObj(obj_rock, OBJ_ROCK, 9);
			break;
		}
	
		case MAP_WOOD:	//�؍쐬
		{
			CObjWood* obj_wood = new CObjWood(x, y);
			Objs::InsertObj(obj_wood, OBJ_WOOD, 9);
			break;
		}

		case MAP_WATER: //���쐬
		{
			CObjWater* obj_water = new CObjWater(x, y);
			Objs::InsertObj(obj_water, OBJ_WATER, 9);
			break;
		}

		case MAP_ENEMY://�G�쐬
		{
			CObjEnemy* obj_enemy = new CObjEnemy(x, y);
			Objs::InsertObj(obj_enemy, OBJ_ENEMY, 9);
			break;
		}

		case MAP_BOSS://�{�X�쐬
		{
			CObjBoss* obj_boss = new CObjBoss(x, y);
			Objs::InsertObj(obj_boss, OBJ_BOSS, 9);
			break;
		}
		
		case MAP_STAGE3_BOSS:		//��O�{�X�쐬
		{
			CObjStage3Boss* obj_stage3_boss = new CObjStage3Boss(x, y);
			Objs::InsertObj(obj_stage3_boss, OBJ_STAGE3_BOSS, 9);
			break;
		}

		case MAP_THROUGH_BLOCK://�X���[�u���b�N�쐬
		{
			CObjThroughBlock* obj_through_block = new CObjThroughBlock(x, y);
			Objs::InsertObj(obj_through_block, OBJ_THROUGHT_BLOCK, 9);
			break;
		}

		case MAP_REFLECT_BLOCK:	//���˗p�u���b�N�쐬
		{
			CObjReflectBlock* obj_reflec_block = new CObjReflectBlock(x, y);
			Objs::InsertObj(obj_reflec_block, OBJ_REFLECT_BLOCK, 9);
			break;
		}
		
		case MAP_SIGN :	//�Ŕ쐬
		{
			CObjSign* Obj_sign = new CObjSign(x, y);
			Objs::InsertObj(Obj_sign, OBJ_SIGN, 9);
			break;
		}
		
		case MAP_DOOR:	//�h�A�쐬
		{
			CObjDoor* ObjDoor = new CObjDoor(x, y);
			Objs::InsertObj(ObjDoor, OBJ_DOOR, 9);
			break;
		}

		case MAP_LEVER_SWICH:	//���o�[�X�C�b�`�쐬
		{
			CObjLeverSwich* ObjLeverSwich = new CObjLeverSwich(x, y);
			Objs::InsertObj(ObjLeverSwich, OBJ_LEVER_SWICH, 19);
			break;
		}
	}

	m_map[y][x].create = false;//�t���O���I�t�ɂ���	
}

//���ׂ����}�b�v�̈ʒu�ɂ���}�b�v�ԍ���Ԃ�
int CObjMap::GetMap(int x, int y)
{
	if (0 <= y && y < MAP_Y_MAX && 0 <= x && x < MAP_X_MAX)

		return m_map[y][x].num;

	return -99999;//���������ꍇ
}

