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
	int mSeveData;	//�T���v���Z�[�u�f�[�^
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
#define MAP_X_MAX (100)	//map�̍ő�lX
#define MAP_Y_MAX (10)	//map�̍ő�lY
#define MAP_WINDOW_MAX_X (int)( WINDOW_SIZE_W/ BLOCK_SIZE )	//��ʓ��Ɏ��܂�map�̍ő�lX
#define MAP_WINDOW_MAX_Y (int)( WINDOW_SIZE_H/ BLOCK_SIZE )	//��ʓ��Ɏ��܂�map�̍ő�lY

//�}�b�v�̔ԍ��ƃI�u�W�F�N�g�̑Ή��@�i���j
enum MAP_BER
{
	MAP_SPACE		 , 	//�����Ȃ��ꏊ
	MAP_BLOCK		 ,	//�u���b�N(�m�[�}��)
	MAP_LADDERS		 ,	//�͂���
	MAP_BUTTON		 ,	//�{�^��
	MAP_ROPE_SWITCH	 ,	//���[�v�X�C�b�`
	MAP_LIFT		 ,	//���t�g
	MAP_ROCK		 ,	//��
	MAP_WOOD		 ,	//��
	MAP_WATER		 ,	//��
	MAP_ENEMY		 ,	//�G
	MAP_BOSS		 ,	//�{�X
	MAP_STAGE3_BOSS  ,	//�X�e�[�W�R�̃{�X
	MAP_BLOCK2		 ,	//
	MAP_THROUGH_BLOCK,	//
	MAP_REFLECT_BLOCK,	//���˃u���b�N
	MAP_SIGN		 ,	//
	MAP_DOOR		 ,	//�h�A
	MAP_LEVER_SWICH	 ,	//���o�[�X�C�b�`
	MAP_FALLING_WALLS,  //������
	MAP_LIFT_MOVE    ,  //�������t�g
};

//�I�u�W�F�N�g�̃T�C�Y
#define HERO_SIZE_WIDTH	      (64.0f)		//��l���̉��T�C�Y	
#define HERO_SIZE_HEIGHT	  (128.0f)		//��l���̏c�T�C�Y	
#define ENEMY_SIZE			  (64.0f)		//�G�̃T�C�Y(��)
#define BULLET_SIZE			  (20.0f)		//�e�ۃT�C�Y�i���j
#define ROPE_SIZE			  (5.0f)		//���[�v�T�C�Y�i���j
#define BLOCK_SIZE			  (64.0f)		//�u���b�N�̃T�C�Y�i���j	
#define WATER_SIZE_WIDTH	  (64.0f)		//���̉��T�C�Y
#define WATER_SIZE_HEIGHT	  (64.0f)       //���̏c�T�C�Y
#define LADDERS_SIZE		  (64.0f)		//�͂����̃T�C�Y
#define BUTTON_SIZE			  (64.0f)		//�{�^���T�C�Y�i���j
#define SIGN_SIZE			  (32.0f)		//�Ŕ̃T�C�Y�i���j
#define LEVER_SWITCH_SIZE	  (64.0f)	    //���o�[�X�C�b�`�̃T�C�Y
#define ROPE_SWITCH_SIZE	  (64.0f)	    //���[�v�X�C�b�`�̃T�C�Y
#define LIFT_SIZE_WIDTH		  (128.0f)		//���t�g�T�C�Y���T�C�Y
#define LIFT_SIZE_HEIGHT	  (32.0f)		//���t�g�T�C�Y�c�T�C�Y
#define LIFT_MOVE_SIZE_WIDTH  (128.0f)      //�������t�g�T�C�Y���T�C�Y
#define LIFT_MOVE_SIZE_HEIGHT (32.0f)       //�������t�g�T�C�Y�c�T�C�Y
#define ROCK_SIZE_WIDTH		  (170.0f)		//��̉��T�C�Y�i��
#define ROCK_SIZE_HEIGHT	  (240.0f)		//��̏c�T�C�Y�i��
#define WOOD_SIZE			  (320.0f)		//�؂̃T�C�Y(��)
#define BOSS_SIZE			  (170.0f)		//BOSS�T�C�Y(��)
#define BOSS_DORP_KEY_SIZE	  (32.0f)	    //�{�X�h���b�v�L�[�T�C�Y(��)
#define DOOR_SIZE_WIDTH		  (32.0f)		//�h�A�̉��T�C�Y(��)
#define DOOR_SIZE_HEIGHT	  (128.0f)		//�h�A�̏c�T�C�Y(��)
#define SIGN_SIZE			  (32.0f)		//�ŔT�C�Y(��)
//#define BOSS_CORRECTION (90.0f)	    //�{�X�T�C�Y�␳(��)
#define THROUGHT_BLOCK_SIZE	 (64.0f)	    //�X���[�u���b�N�T�C�Y�i���j
#define FALLING_WALLS_SAIZE  (64.0f)		//�����ǃT�C�Y(��)
#define CANNON_SIZE_WIDTH	 (64.0f)		//�C��̉��T�C�Y(��)
#define CANNON_SIZE_HEIGHT	 (32.0f)		//�C��̏c�T�C�Y(��)

//�X�N���[���̃��C���@�i�v�����j
#define SCROLL_LINE_LEFT	(464.0f)	//��
#define SCROLL_LINE_RIGHT	(560.0f)	//�E
#define SCROLL_LINE_UP		(276.0f)	//��
#define SCROLL_LINE_DOWN	(400.0f)	//��

//�I�u�W�F�N�g�̐������C���i�v�����j
#define CREATE_LINE_LEFT	(1)														//��
#define CREATE_LINE_RIGHT	( (int)(WINDOW_SIZE_W / BLOCK_SIZE) - CREATE_LINE_LEFT)	//�E
#define CREATE_LINE_UP		(1)														//��	
#define CREATE_LINE_DOWN	( (int)(WINDOW_SIZE_H / BLOCK_SIZE) - CREATE_LINE_UP)	//��
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
#include "ObjLiftMove.h"        //�������t�g
#include "ObjLadders.h"			//�͂���
#include "ObjMap.h"				//�}�b�v
#include "ObjWood.h"			//��	
#include "ObjWater.h"			//��
#include "ObjRopeSwitch.h"		//���[�v�X�C�b�`
#include "ObjEnemy.h"			//�G
#include "ObjBoss.h"			//�{�X
#include "ObjStage3Boss.h"		//��O�X�e�[�W�{�X
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
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"		//���C��
#include "SceneTitle.h"		//�^�C�g��
#include "SceneGameOver.h"	//�Q�[���I�[�o�[
#include "SceneGameClear.h"	//�N���A
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneMain
//-----------------------------------------------