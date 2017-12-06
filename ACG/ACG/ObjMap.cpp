#include "GameHead.h"
#include "ObjMap.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�R���X�g���N�^
CObjMap::CObjMap(int map[MAP_Y_MAX][MAP_X_MAX], int remaining)
{
	//�}�b�v�f�[�^���R�s�[
	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			m_map[i][j].num = map[i][j];//���l�̃R�s�[
		}
	}
	m_remaining = remaining; // �c�@����������
}

//�C�j�V�����C�Y
void CObjMap::Init()
{
	m_scroll_x = 0.0f;
	
	for (int y = 0; y < MAP_Y_MAX; y++)
	{
		for (int x = 0; x < MAP_X_MAX; x++)
		{
			// ��l���̃}�b�v�ʒu���珉���̃X�N���[���l�����߂�
			if (m_map[y][x].num == MAP_HERO_START)
			{
				m_scroll_y = (float)y * BLOCK_SIZE;
			}
			m_map[y][x].create = true; //�t���O�̏�����
		}
	}
}

//�A�N�V����
void CObjMap::Action()
{
	// ���̃X�N���[���l�𒴂��Ȃ��悤����
	if (m_scroll_y > WINDOW_SIZE_H)
		m_scroll_y = WINDOW_SIZE_H;

	//�}�b�v�����ɃI�u�W�F�N�g�𐶐�--------------------------------------
	
	//y���@��ʂɎ��܂�ő�l�@�܂��́@�}�b�v�̍ő�l�ɂȂ�܂ł܂킷
	for (int y = 0; y < MAP_WINDOW_MAX_Y && y<MAP_Y_MAX; y++)
	{
		//x���@��ʂɎ��܂�ő�l�@�܂��́@�}�b�v�̍ő�l�ɂȂ�܂ł܂킷
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
//����1	scroll_block_num_x:	X���̌��݂̃X�N���[���ʂ��u���b�N������
//����2	scroll_block_num_y:	Y���̌��݂̃X�N���[���ʂ��u���b�N������
// *���̊֐����̃R�����g�̃X�N���[���ʂ͂��ׂĈ����œn���Ă����u���b�N���Ŋ��Z�������̂��Ƃ��w��
void CObjMap::ScrollCreateObj(int scroll_block_num_x, int scroll_block_num_y)
{
	//y�̒l���X�N���[����Y�@����@�E�B���h�E���Ɏ��܂�ő�l�{�X�N���[����Y�@�܂��́@�}�b�v�̍ő�l�@�ɒB����܂ŉ�
	for (int y = scroll_block_num_y ; y < MAP_Y_MAX && y <= scroll_block_num_y + MAP_WINDOW_MAX_Y; y++)
	{
		//x�̒l���X�N���[����X�@����@�}�b�v�̍ő�l�@�܂��́@�E�B���h�E���Ɏ��܂�ő�l�{�X�N���[����X�@�@�ɒB����܂ŉ�
		for (int x = scroll_block_num_x;
			x < MAP_X_MAX && x <= scroll_block_num_x + MAP_WINDOW_MAX_X ; x++)
		{			
			//�}�b�v�͈̔͂Ȃ��Ȃ�
			if ((x >= 0 && x < MAP_X_MAX))
			{
				if (y >= 0 && y < MAP_Y_MAX)
				{

					CreateObj(x, y);//�I�u�W�F�N�g�𐶐�
				}
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
		// �v�����i�[����}�b�v���͂�����R�����g���͂���
		
	
		case MAP_HERO_START:	//�q�[���[�̍쐬
		{

			//��l���I�u�W�F�N�g���쐬����
			CObjHero* objhero = new CObjHero(x, y, m_remaining);
			Objs::InsertObj(objhero, OBJ_HERO, 10);
			break;
		}
		
		case MAP_BLOCK:		//�u���b�N�쐬
		{
			CObjBlock* objblock = new CObjBlock(x, y);
			Objs::InsertObj(objblock, OBJ_BLOCK, 9);
			break;
		}
		
		case MAP_LADDERS:	//�͂����쐬
		{
			CObjLadders* objladders = new CObjLadders(x, y, true);
			Objs::InsertObj(objladders, OBJ_LADDERS, 9);
			break;
		}
		
		case MAP_ROPE_SWITCH:	//���[�v�X�C�b�`�쐬
		{
			CObjRopeSwitch* objrope_switch = new CObjRopeSwitch(x, y);
			Objs::InsertObj(objrope_switch, OBJ_ROPE_SWITCH, 9);
			break;
		}

		case MAP_LEVER_SWICH:	//���o�[�X�C�b�`�쐬
		{
			CObjLeverSwich* objLeverSwich = new CObjLeverSwich(x, y);
			Objs::InsertObj(objLeverSwich, OBJ_LEVER_SWICH, 9);
			break;
		}

		case MAP_ROCK:		//��쐬
		{
			CObjRock* objrock = new CObjRock(x, y);
			Objs::InsertObj(objrock, OBJ_ROCK, 9);
			break;
		}

		case MAP_SIGN:	//�Ŕ쐬
		{
			CObjSign* objsign = new CObjSign(x, y);
			Objs::InsertObj(objsign, OBJ_SIGN, 9);
			break;
		}

		case MAP_GOAL_DOOR:	//�S�[���p�h�A�쐬
		{
			CObjDoor* objDoor = new CObjDoor(x, y);
			Objs::InsertObj(objDoor, OBJ_DOOR, 9);
			break;
		}
		
		case MAP_LIFT_TYPE_AUTO_WIDTH:		//�������ړ����t�g�쐬
		{
			CObjLift* objlift = new CObjLift(x, y,0,300.0f,1);
			Objs::InsertObj(objlift, OBJ_LIFT, 9);
			break;
		}

		case MAP_LIFT_TYPE_AUTO_LENGTH:		//�����c�ړ����t�g�쐬
		{
			CObjLift* objlift = new CObjLift(x, y,3);
			Objs::InsertObj(objlift, OBJ_LIFT, 9);
			break;
		}
		
		case MAP_ENEMY://�G�쐬
		{
			CObjEnemy* objenemy = new CObjEnemy(x, y);
			Objs::InsertObj(objenemy, OBJ_ENEMY, 10);
			break;
		}

		case MAP_LAST_WALL:		//��(���X�e�[�W���u�Ă��)
		{
			CObjLastWall* objLastWall = new CObjLastWall(x, y);
			Objs::InsertObj(objLastWall, OBJ_LAST_WALL, 10);
			break;
		}
	
		case MAP_WOOD:	//�؍쐬
		{
			CObjWood* objwood = new CObjWood(x, y);
			Objs::InsertObj(objwood, OBJ_WOOD, 9);
			break;
		}

		case MAP_NO_LOOK_LADDERS: // �����Ȃ��n�V�S�쐬
		{
			CObjLadders* objladders = new CObjLadders(x, y, false);
			Objs::InsertObj(objladders, OBJ_LADDERS, 9);
			break;
		}

		case MAP_BUTTON:	//�{�^���쐬
		{
			CObjButton* objbutton = new CObjButton(x, y);
			Objs::InsertObj(objbutton, OBJ_BUTTON, 9);
			break;
		}

		case MAP_WATER: //���쐬
		{
			CObjWater* objwater = new CObjWater(x, y);
			Objs::InsertObj(objwater, OBJ_WATER, 8);
			break;
		}

		case MAP_THROUGH_BLOCK://�X���[�u���b�N�쐬
		{
			CObjThroughBlock* objthrough_block = new CObjThroughBlock(x, y);
			Objs::InsertObj(objthrough_block, OBJ_THROUGHT_BLOCK, 9);
			break;
		}

		case MAP_BOSS://�{�X�쐬
		{
			CObjBoss* objboss = new CObjBoss(x, y);
			Objs::InsertObj(objboss, OBJ_BOSS, 9);
			break;
		}

		case MAP_REFLECT_BLOCK:	//���˗p�u���b�N�쐬
		{
			CObjReflectBlock* objreflec_block = new CObjReflectBlock(x, y);
			Objs::InsertObj(objreflec_block, OBJ_REFLECT_BLOCK, 9);
			break;
		}

		case MAP_ROLL_BLOCK_TYPE_AUTO://��]�u���b�N�i������]�j�쐬
		{
			CObjRollBlock* objrollblock = new CObjRollBlock(x, y,1);
			Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 9);
			break;
		}
		
		case MAP_ROLL_BLOCK_TYPE_MANUAL://��]�u���b�N�i�蓮�j�쐬
		{
			CObjRollBlock* objrollblock = new CObjRollBlock(x, y, 2);
			Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 9);
			break;
		}

		case MAP_STAGE3_BOSS:		//��O�{�X�쐬
		{
			CObjStage3Boss* objstage3_boss = new CObjStage3Boss(x, y);
			Objs::InsertObj(objstage3_boss, OBJ_STAGE3_BOSS, 9);
			break;
		}

		case MAP_CANNON:		//�C��
		{
			CObjCannon* objcannon = new CObjCannon(x, y);
			Objs::InsertObj(objcannon, OBJ_CANNON, 9);
			break;
		}

		case MAP_TARZAN_POINT://���[�v�łԂ牺�����M�~�b�N
		{
			CObjTarzanPoint* objtarzanpoint = new CObjTarzanPoint(x, y);
			Objs::InsertObj(objtarzanpoint, OBJ_TARZAN_POINT, 9);
			break;

		}
		/*
		�������ꂽ��A�R�����g�����O���Ă��������B
		case MAP_LIFT_TYPE_AUTO_UP:
		{
			break;
		}
		*/
		case MAP_FALLING_BLOCK://�X�e�[�W5�{�X���p������u���b�N
		{
			CObjFallingBlock* objfalling_block = new CObjFallingBlock(x,y);
			Objs::InsertObj(objfalling_block, OBJ_FALLING_BLOCK,9);
			break;
		}

		case MAP_STAGE5_BOSS://�X�e�[�W5�{�X(�{��)
		{
			CObjStage5Boss* objstage5_boss = new CObjStage5Boss(x,y);
			Objs::InsertObj(objstage5_boss, OBJ_STAGE5_BOSS ,9);
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

