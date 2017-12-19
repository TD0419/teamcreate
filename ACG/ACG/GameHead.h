#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_HERO,			//��l��
	OBJ_BUTTON,			//�{�^��
    OBJ_BULLET,			//�e��(��l���p)
	OBJ_ENEMY_BULLET,	//�e��(�G�p)
	OBJ_ROCK,			//��
    OBJ_BLOCK,			//�u���b�N
	OBJ_REFLECT_BLOCK,	//�e�𔽎˂���u���b�N
	OBJ_LIFT,			//���t�g
	OBJ_LIFT_MOVE,      //�������t�g
	OBJ_MAP,			//�}�b�v
    OBJ_WOOD,			//��
	OBJ_WATER,			//��
    OBJ_ROPE_SWITCH,	//���[�v�X�C�b�`
	OBJ_LADDERS,		//��q
	OBJ_SIGN,			//�Ŕ�
	OBJ_ROPE,           //��i�X�C�b�`�Ɉ����|�����j
	OBJ_ENEMY,			//�G
	OBJ_BOSS,			//�{�X
	OBJ_STAGE3_BOSS,	//��O�X�e�[�W�{�X
	OBJ_STAGE5_BOSS,	//��܃X�e�[�W�{�X
	OBJ_BOSS_DROP_KEY,	//�{�X�����Ƃ���
	OBJ_TITLE,			//�^�C�g��
	OBJ_GAME_OVER,		//�Q�[���I�[�o�[
	OBJ_GAME_CLEAR,		//�Q�[���N���A
	OBJ_ENDLESS_SPRING, //�G�����V�X�e��(�G���h���X����)
	OBJ_LEVER_SWICH,    //���o�[�X�C�b�`
	OBJ_DOOR,           //�h�A
	OBJ_THROUGHT_BLOCK,	//�X���[�u���b�N
	OBJ_FALLING_WALLS,  //������
	OBJ_BACKGROUND,		//�o�b�O�O���E���h(�w�i)
	OBJ_CANNON,		    //�C��
	OBJ_LAST_WALL,		//�Ō�̕�
	OBJ_TIME,			//�^�C��
	OBJ_ROLL_BLOCK,		//��]����u���b�N
	OBJ_ROLL_BLOCK_SWITCH,//��]����u���b�N�p�̃X�C�b�`
	OBJ_NEEDLE,			  //�j
	OBJ_NEEDLE_STAND,	  //�j�̓y��
	OBJ_TARZAN_POINT,	  //���[�v�łԂ牺���邱�Ƃ��ł���M�~�b�N
	OBJ_DIFFUSION_CANNON, //�X�e�[�W�T�̊g�U�e�L���m��
	OBJ_DIFFUSION_BULLET, //�X�e�[�W�T�̊g�U�e
	OBJ_FALLING_LIFT,	  //���Ɨ����郊�t�g
	OBJ_FALLING_BLOCK,	  //�X�e�[�W5�{�X���p������u���b�N
	OBJ_STAGE5_BOSS_ARMS, //�X�e�[�W5�{�X�̘r
	OBJ_WIRE_MESH,		  //�X�e�[�W5�̋���
	OBJ_DIFFUSION_SOURCE, //�g�U�e�̌�
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,		//�v���C���[
	ELEMENT_ENEMY,		//�G
	ELEMETN_ITEM,		//�A�C�e��
	ELEMENT_GIMMICK,	//�M�~�b�N
	ELEMENT_BLOCK,		//�u���b�N
};
//------------------------------------------------

//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int stagenum;	//�X�e�[�W�ԍ�
};
//------------------------------------------------


//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--

//�E�B���h�E�T�C�Y
#define WINDOW_SIZE_W	(1024)	//��
#define WINDOW_SIZE_H	(768)	//�c
//�𑜓x�T�C�Y
#define PIXEL_SIZE_W	(1024)	//��
#define PIXEL_SIZE_H	(768)	//�c

//�}�b�v�T�C�Y
#define MAP_X_MAX (111)	//map�̍ő�lX���X�e�[�W�ɂ���ĕϓ�����悤�ɂ���K�v������
#define MAP_Y_MAX (24)	//map�̍ő�lY
#define MAP_WINDOW_MAX_X (int)( WINDOW_SIZE_W/ BLOCK_SIZE )	//��ʓ��Ɏ��܂�map�̍ő�lX(16)
#define MAP_WINDOW_MAX_Y (int)( WINDOW_SIZE_H/ BLOCK_SIZE )	//��ʓ��Ɏ��܂�map�̍ő�lY(12)

//�}�b�v�̔ԍ��ƃI�u�W�F�N�g�̑Ή��@�i���j
enum MAP_BER
{
	//�S�X�e�[�W���ʃI�u�W�F�N�g�`��ԍ�
	MAP_SPACE				, 			//�����Ȃ��ꏊ
	MAP_HERO_START			,			//hero�̃X�^�[�g�ʒu(�}�b�v���͂����炱�̃R�����g���͂���)
	MAP_BLOCK				,			//�u���b�N(�m�[�}��)

	//�����̃X�e�[�W�Ŏg�p�����I�u�W�F�N�g�`��ԍ�
	MAP_LADDERS				,			//�͂���
	MAP_ROPE_SWITCH			,			//���[�v�X�C�b�`
	MAP_LEVER_SWICH			,			//���o�[�X�C�b�`
	MAP_ROCK				,			//��
	MAP_SIGN				,			//�Ŕ�
	MAP_GOAL_DOOR			,			//�S�[���p�h�A
	MAP_LIFT_TYPE_MANUAL	,			//�蓮���t�g(�ʏ펞�͓����Ȃ��B�M�~�b�N�̉ߒ��ň�������Ɠ�������)
    MAP_LIFT_TYPE_AUTO_WIDTH	 ,		//�������ړ����t�g(�����ō��E�ɓ���)	
	MAP_LIFT_TYPE_AUTO_LENGTH	 ,		//�������ړ����t�g(�����ŉ������ɓ���)
	MAP_ENEMY				,			//�G
	MAP_LAST_WALL			,			//���X�e�[�W�ւ̓����(�Ō�̕�)
	
	//�X�e�[�W1�݂̂Ɏg�p����I�u�W�F�N�g�`��ԍ�
	MAP_WOOD				,			//��

	//�X�e�[�W2�݂̂Ɏg�p����I�u�W�F�N�g�`��ԍ�
	MAP_NO_LOOK_LADDERS		,			//�����Ȃ��n�V�S
	MAP_BUTTON				,			//�{�^��
	MAP_WATER				,			//��
	MAP_THROUGH_BLOCK		,			//�ʂ蔲�����u���b�N
	MAP_BOSS				,			//�X�e�[�W�Q�̃{�X

	//�X�e�[�W3�݂̂Ɏg�p����I�u�W�F�N�g�`��ԍ�
	MAP_FALLING_WALLS		,			//������
	MAP_CANNON				,			//�C��
	MAP_REFLECT_BLOCK		,			//���˃u���b�N
	MAP_STAGE3_BOSS			,			//�X�e�[�W�R�̃{�X
	MAP_ENDLESS_SPRING		,			//�G���������M�~�b�N
	MAP_OPEN_DOOR_SWITCH    ,			//�V���b�^�[�J���p�X�C�b�`	

	//�X�e�[�W5�݂̂Ɏg�p����I�u�W�F�N�g�`��ԍ�
	MAP_ROLL_BLOCK_TYPE_AUTO	,		//��������]����u���b�N
	MAP_ROLL_BLOCK_TYPE_MANUAL	,		//�蓮��90�x��]����u���b�N
	MAP_TARZAN_POINT			,		//���[�v�łԂ牺�����M�~�b�N
	MAP_NEEDLE					,		//�j
	MAP_NEEDLE_STAND			,		//�j�̓y��
	MAP_DIFFUSION_CANNON		,		//�g�U�e���˃M�~�b�N
	MAP_FALLING_LIFT			,		//���Ɨ����郊�t�g
	MAP_LIFT_TYPE_AUTO_UP		,		//������ړ����t�g(�����ŏ�����ɓ���)
	MAP_WIRE_MESH_FLOOR			,		//���ԏ�
	MAP_FALLING_BLOCK           ,		//�{�X�X�e�[�W�p������u���b�N
	MAP_STAGE5_BOSS             ,		//�X�e�[�W5�̃{�X
	MAP_BOSS_TARZAN_POINT		,		//�{�X�펞�ɏo�����郍�[�v�łԂ牺�����M�~�b�N
};

//�O���t�B�b�NID
enum GRAPHIC_ID
{
	GRA_BACKGROUND,		//�w�i
	GRA_HERO,			//�v���C���[
	GRA_HERO_BULLET,    //�v���C���[�̒e
	GRA_BLOCK,			//�u���b�N
	GRA_THROUGH_BLOCK,  //���蔲����u���b�N
	GRA_BOSS,			//�{�X
	GRA_LADDERS,		//�͂���
	GRA_LIFT,			//���t�g
	GRA_DOOR,			//�h�A
	GRA_WOOD,			//��
	GRA_ENEMY,			//�G
	GRA_LEVER_SWICH,	//���o�[�X�C�b�`
	GRA_ROCK,			//��
	GRA_AQUATIC,		//����(�g������)
	GRA_UNDER_WATER,	//����(�g���Ȃ�)
	GRA_ROPE_SWITCH,	//���[�v�X�C�b�`
	GRA_CANNON,			//�C��
	GRA_SIGN_FRAME,		//�Ŕ̘g�g��
	GRA_BUTTON,			//�{�^��
	GRA_LAST_WALL,		//��(�㕔���̓S����)
	GRA_OPEN_WALL,		//�J����V���b�^�[(�Ō�̕Ǘp)
	GRA_LAST_WALL3,		//��(�㕔���̓S����)
	GRA_OPEN_WALL3,		//�J����V���b�^�[(�Ō�̕Ǘp)
	GRA_LIFE,			//���C�t
	GRA_SIGN,			//�Ŕ�
	GRA_ROLL_BLOCK,		//��]�u���b�N
	GRA_ROLL_BLOCK2,	//��]�u���b�N�i�p�^�[��2�j
	GRA_TITLE,			//�^�C�g��
	GRA_GAME_OVER,		//�Q�[���I�[�o�[
	GRA_GAME_CLEAR,		//�Q�[���N���A
	GRA_COCONUT,		//�R�R�i�b�c
	GRA_NEEDLE,         //�j
	GRA_NEEDLE_STAND,   //�j�̓y��
	GRA_TARZAN_POINT,	//���[�v�łԂ牺�����M�~�b�N

	GRA_BLACK_BALL,			//��]�u���b�N�̎d�|���̃X�C�b�`
	GRA_CANNON_BEAM,		//�X�e�[�W5�̊g�U�e
	GRA_WIRE_MASH,			//�X�e�[�W5�̋���
	GRA_STAGE5_BOSS_ELECTRIC,	 	//�X�e�[�W5�̃{�X���r�ڑ��d�C
	GRA_STAGE5_BOSS_BODY,	//�X�e�[�W5�̃{�X����
	GRA_STAGE5_BOSS_EYE,	//�X�e�[�W5�̃{�X�ዅ
	GRA_STAGE5_BOSS_ARMS_ALL,      	//�X�e�[�W5�̃{�X�r(���E�r)
	GRA_FALLING_LIFT,	//�����郊�t�g
	GRA_HAND_LIFT,//�蓮�ň������郊�t�g
	GRA_DIFFUSION_SOURCE,//�g�U�e�����e
	GRA_BOSS_DIFFUSION,//�{�X�̔��˂���g�U�e
	GRA_STAGE5_BOSS_BULLET,//�{�X�̔��˂���e
};

//���y(BGM)
enum MUSIC
{
//BGM--------------------
	STAGE,      //�X�e�[�W
	BOSS,       //�{�X
	GAMEOVER,	//�Q�[���I�[�o�[
	TITLE,		//�^�C�g��
	CLEAR,		//�N���A
//SE---------------------
	FIRING		,//�e�̔���
	ROPE		,//���[�v�̑ł��o��
	ROCK		,//��̔���
	WALL		,//�ǂ̊J��
	TREE		,//�؂̓]�|
	DOOR		,//�o���J��
	LANDING		,//�G�ɒ��e
	LEVER		,//���o�[
	BUTTON		,//�{�^��
	ENEMYFIR	,//�G�̒e����
	PULLLIFT	,//���t�g(��������)
	RELEASELIFT	,//���t�g(�����)
	WAVE		,//���̗���
	GORILLATHROW,//�S�����̓�����
	ROLLBLOCK,	 //��]�u���b�N
	BOSSPOP,	 //�{�X�����e���e���鉹(�{�X�g�U�e���ł鎞�̉�)
	BOSSLASER,	 //�{�X�̃��[�U�[�r�[���̉�
	GROUND,		 //�n�ʂ������鉹
	DIFFUSION,	 //�X�e�[�W5�̊g�U�e
};

//�I�u�W�F�N�g�̃T�C�Y
#define HERO_SIZE_WIDTH	      (64.0f)		//��l���̉��T�C�Y	
#define HERO_SIZE_HEIGHT	  (128.0f)		//��l���̏c�T�C�Y	
#define ENEMY_SIZE			  (64.0f)		//�G�̃T�C�Y(��)
#define BULLET_SIZE			  (20.0f)		//�e�ۃT�C�Y�i���j
#define ROPE_SIZE			  (5.0f)		//���[�v�T�C�Y�i���j
#define BLOCK_SIZE			  (64.0f)		//�u���b�N�̃T�C�Y�i���j	
#define WATER_SIZE_WIDTH	  (640.0f)		//���̉��T�C�Y
#define WATER_SIZE_HEIGHT	  (192.0f)       //���̏c�T�C�Y
#define LADDERS_SIZE		  (64.0f)		//�͂����̃T�C�Y
#define BUTTON_SIZE			  (64.0f)		//�{�^���T�C�Y�i���j
#define SIGN_SIZE			  (32.0f)		//�Ŕ̃T�C�Y�i���j
#define SIGN_FRAME_WIDTH	  (192.0f)		//�Ŕ̘g�T�C�Y�i���j


#define LEVER_SWITCH_SIZE	  (64.0f)	    //���o�[�X�C�b�`�̃T�C�Y
#define ROPE_SWITCH_SIZE	  (64.0f)	    //���[�v�X�C�b�`�̃T�C�Y

#define LIFT_SIZE_WIDTH		  (128.0f)		//���t�g�T�C�Y���T�C�Y
#define LIFT_SIZE_HEIGHT	  (32.0f)		//���t�g�T�C�Y�c�T�C�Y
#define STAGE5_LIFT_SIZE_WIDTH (320.0f)		//�X�e�[�W5�̃��t�g�T�C�Y
#define STAGE5_LIFT_SIZE_HEIGHT (16.0f)		//�X�e�[�W5�̃��t�g�T�C�Y

#define ROCK_SIZE_WIDTH		  (170.0f)		//��̉��T�C�Y�i��
#define ROCK_SIZE_HEIGHT	  (240.0f)		//��̏c�T�C�Y�i��
#define WOOD_SIZE			  (320.0f)		//�؂̃T�C�Y(��)
#define BOSS_SIZE_WIDTH		  (192.0f)		//BOSS����(��)
#define BOSS_SIZE_HEIGHT	  (256.0f)		//BOSS�c��(��)
#define BOSS_DORP_KEY_SIZE	  (32.0f)	    //�{�X�h���b�v�L�[�T�C�Y(��)
#define DOOR_SIZE			  (128.0f)		//�h�A�̃T�C�Y(��)
#define THROUGHT_BLOCK_SIZE	  (64.0f)	    //�X���[�u���b�N�T�C�Y�i���j
#define FALLING_WALLS_SAIZE   (64.0f)		//�����ǃT�C�Y(��)
#define CANNON_SIZE_WIDTH	  (64.0f)		//�C��̉��T�C�Y(��)
#define CANNON_SIZE_HEIGHT	  (32.0f)		//�C��̏c�T�C�Y(��)
#define ROLL_BLOCK_SIZE_WIDTH	(192.0f)	//��]����u���b�N�̉��T�C�Y
#define ROLL_BLOCK_SIZE_HEIGHT	(64.0f)		//��]����u���b�N�̏c�T�C�Y
#define NEEDLE_SIZE_WIDTH     (64.0f)		//�j�̉��̃T�C�Y
#define NEEDLE_SIZE_HEIGHT    (32.0f)		//�j�̏c�̃T�C�Y
#define NEEDLE_STAND_SIZE     (64.0f)		//�j�̓y��̃T�C�Y
#define TARZAN_POINT_WIDTH	  (16.0f)		//���[�v�łԂ牺�����M�~�b�N���T�C�Y
#define TARZAN_POINT_HEIGHT	  (16.0f)		//���[�v�łԂ牺�����M�~�b�N�c�T�C�Y
#define ROLL_BLOCK_SWITCH_SIZE_WIDTH  (16.0f)	//��]����u���b�N���܂킷�X�C�b�`�̉��T�C�Y
#define ROLL_BLOCK_SWITCH_SIZE_HEIGHT (16.0f)	//��]����u���b�N���܂킷�X�C�b�`�̏c�T�C�Y
#define DIFFUSION_CANNON_SIZE	      (64.0f)   //�X�e�[�W5�̊g�U����L���m���̃T�C�Y
#define STAGE5_BOSS_BODY_SIZE	     (256.0f)	//�X�e�[�W5�̃{�X���̃T�C�Y
#define STAGE5_BOSS_EYE_SIZE	     (133.0f)	//�X�e�[�W5�̃{�X�ዅ�T�C�Y
#define STAGE5_BOSS_ARMS_WIDTH_SIZE       (175.0f)	//�X�e�[�W5�̃{�X�r�T�C�Y(��)
#define STAGE5_BOSS_ARMS_HEIGHT_SIZE      (577.0f)	//�X�e�[�W5�̃{�X�r�T�C�Y(�c)
#define STAGE5_BOSS_ELECTRIC_WIDTH	 (300.0f)	//�X�e�[�W5�̃{�X���r�ڑ��d�C�T�C�Y(��)
#define STAGE5_BOSS_ELECTRIC_HEIGHT	 (256.0f)	//�X�e�[�W5�̃{�X���r�ڑ��d�C�T�C�Y(�c)
#define WIRE_MESH_SIZE_WIDTH	(640.0f) //���Ԃ̉��T�C�Y
#define WIRE_MESH_SIZE_HEIGHT	(64.0f) //���Ԃ̏c�T�C�Y
#define DIFFUSION_SOURCE_SIZE	(32.0f)//�g�U�e�����e�̃T�C�Y
#define STAGE5_BOSS_BULLET_SIZE (32.0f)//�X�e�[�W�T�̃{�X���łe�̃T�C�Y

//�X�N���[���̃��C���@�i�v�����j
#define SCROLL_LINE_LEFT	(464.0f)	//��
#define SCROLL_LINE_RIGHT	(560.0f)	//�E
#define SCROLL_LINE_UP		(276.0f)	//��
#define SCROLL_LINE_DOWN	(400.0f)	//��

//�I�u�W�F�N�g�̐������C���i�v�����j
#define CREATE_LINE_LEFT	(1)						//��
#define CREATE_LINE_RIGHT	( MAP_WINDOW_MAX_X )	//�E
#define CREATE_LINE_UP		(1)						//��	
#define CREATE_LINE_DOWN	( MAP_WINDOW_MAX_Y )	//��
//------------------------------------------------

//�Q�[�����Ŏg�p����N���X�w�b�_------------------
//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_-----------------
#include "ObjHero.h"			//��l��
#include "ObjButton.h"			//�{�^��
#include "ObjBullet.h"			//�e��(��l���p)
#include "ObjEnemyBullet.h"		//�e��(�G�p)
#include "ObjRock.h"			//��
#include "ObjBlock.h"			//�u���b�N
#include "ObjReflectBlock.h"	//�e�𔽎˂���u���b�N
#include "ObjLift.h"			//���t�g
#include "ObjLadders.h"			//�͂���
#include "ObjMap.h"				//�}�b�v
#include "ObjWood.h"			//��	
#include "ObjWater.h"			//��
#include "ObjRopeSwitch.h"		//���[�v�X�C�b�`
#include "ObjEnemy.h"			//�G
#include "ObjBoss.h"			//�{�X
#include "ObjStage3Boss.h"		//��O�X�e�[�W�{�X
#include "ObjStage5Boss.h"		//��܃X�e�[�W�{�X
#include "ObjStage5BossArms.h"	//��܃X�e�[�W�{�X�̘r
#include "ObjBossDropKey.h"		//�{�X�����Ƃ���
#include "ObjTitle.h"			//�^�C�g��
#include "ObjSign.h"			//�Ŕ�
#include "ObjRope.h"			//��i�X�C�b�`�Ɉ����|�����j
#include "ObjGameClear.h"		//�N���A
#include "ObjGameOver.h"		//�Q�[���I�[�o�[
#include "ObjEndlessSpring.h"	//�G�����V�X�e��(�G���h���X����)
#include "ObjLeverSwich.h"		//���o�[�X�C�b�`
#include "ObjDoor.h"			//�h�A
#include "ObjThroughBlock.h"	//�X���[�u���b�N
#include "ObjFallingWalls.h"	//������
#include "ObjBackGround.h"		//�o�b�O�O���E���h(�w�i)
#include "ObjCannon.h"			//�C��
#include "ObjLastWall.h"		//�Ō�̕�
#include "ObjTime.h"			//�^�C��
#include "ObjNeedle.h"			//�j
#include "ObjNeedleStand.h"     //�j�̓y��
#include "ObjDiffusionCannon.h" //�g�U�e���ˑ��u
#include "ObjRollBlock.h"		//��]�u���b�N
#include "ObjTarzanPoint.h"		//���[�v�łԂ牺���邱�Ƃ��ł���M�~�b�N
#include "ObjRollBlockSwitch.h"	//��]�u���b�N�p�̃X�C�b�`
#include "ObjDiffusionBullet.h" //�g�U�e
#include "ObjFallingLift.h"		//���Ɨ����郊�t�g
#include "ObjFallingBlock.h"	//�X�e�[�W5�{�X���p������u���b�N
#include "ObjWireMesh.h"			//�X�e�[�W5�̋���
#include "ObjDiffusionSource.h"	//�X�e�[�W�T�{�X�̊g�U�e�̃\�[�X
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"		//���C��
#include "SceneTitle.h"		//�^�C�g��
#include "SceneGameOver.h"	//�Q�[���I�[�o�[
#include "SceneGameClear.h"	//�N���A
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^

#define SET_GAME_START CSceneTitle //�^�C�g�����
//-----------------------------------------------