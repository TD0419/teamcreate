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
	OBJ_MAP,			//�}�b�v
    OBJ_WOOD,			//��
	OBJ_WATER,			//��
    OBJ_ROPE_SWITCH,	//���[�v�X�C�b�`
	OBJ_LADDERS,		//��q
	OBJ_SIGN,			//�Ŕ�
	OBJ_ROPE,           //��i�X�C�b�`�Ɉ����|�����j
	OBJ_ENEMY,			//�G
	OBJ_BOSS_ENEMY,		//�{�X
	OBJ_STAGE3_BOSS,	//��O�X�e�[�W�{�X
	OBJ_TITLE,			//�^�C�g��
	OBJ_GAME_OVER,		//�Q�[���I�[�o�[
	OBJ_GAME_CLEAR,		//�Q�[���N���A
	OBJ_ENDLESS_SPRING,//�G�����V�X�e��(�G���h���X����)
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
#define MAP_SPACE	(0)		//�����Ȃ��ꏊ
#define MAP_BLOCK	(1)		//�u���b�N(�m�[�}��)
#define MAP_LADDERS	(2)		//�͂���
#define MAP_BUTTON	(3)		//�{�^��
#define MAP_ROPE_SWITCH	(4) //���[�v�X�C�b�`
#define MAP_LIFT	(5)		//���t�g
#define MAP_ROCK	(6)		//��
#define MAP_WOOD	(7)		//��
#define MAP_WATER	(8)		//��
#define MAP_ENEMY	(9)		//�G
#define MAP_BOSS	(10)	//�{�X

//�I�u�W�F�N�g�̃T�C�Y
#define HERO_SIZE_X (64.0f)	//��l���̉��T�C�Y	
#define HERO_SIZE_Y (128.0f)//��l���̏c�T�C�Y	
#define ENEMY_SIZE	(64.0f) //�G�̃T�C�Y(��)
#define BULLET_SIZE (20.0f)	//�e�ۃT�C�Y�i���j
#define BLOCK_SIZE	(32.0f) //�u���b�N�̃T�C�Y�i���j	
#define WATER_SIZE	(32.0f) //���̃T�C�Y�i���j
#define LADDERS_SIZE (32.0f)//�͂����̃T�C�Y�i���j
#define BUTTON_SIZE	(32.0f)//�{�^���T�C�Y�i���j
#define ROPE_SWITCH_SIZE	(32.0f)	//���[�v�X�C�b�`�̃T�C�Y�i���j
#define LIFT_SIZE	(32.0f)//���t�g�T�C�Y(��)
#define ROCK_SIZE	(32.0f)//��T�C�Y�i���j
#define WOOD_SIZE	(32.0f)//�؃T�C�Y(��)
#define BOSS_SIZE	(32.0f)//BOSS�T�C�Y(��)


//�X�N���[���̃��C���@�i�v�����j
#define SCROLL_LINE_LEFT	(480.0f)							//��
#define SCROLL_LINE_RIGHT	(WINDOW_SIZE_W - SCROLL_LINE_LEFT)	//�E
#define SCROLL_LINE_UP		(250.0f)							//��
#define SCROLL_LINE_DOWN	(WINDOW_SIZE_H - SCROLL_LINE_UP)	//��

//�I�u�W�F�N�g�̐������C���i�v�����j
#define CREATE_LINE_LEFT	(1)														//��
#define CREATE_LINE_RIGHT	( (int)(WINDOW_SIZE_W / BLOCK_SIZE) - CREATE_LINE_LEFT)	//�E
#define CREATE_LINE_UP		(1)														//��	
#define CREATE_LINE_DOWN	( (int)(WINDOW_SIZE_H / BLOCK_SIZE) - CREATE_LINE_UP)	//��

//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_-----------------
#include "ObjHero.h"		//��l��
#include "ObjButton.h"		//�{�^��
#include "ObjBullet.h"		//�e��(��l���p)
#include "ObjEnemyBullet.h"	//�e��(�G�p)
#include "ObjRock.h"		//��
#include "ObjBlock.h"		//�u���b�N
#include "ObjReflectBlock.h"//�e�𔽎˂���u���b�N
#include "ObjLift.h"		//���t�g
#include "ObjLadders.h"		//��q
#include "ObjMap.h"			//�}�b�v
#include "ObjWood.h"		//��	
#include "ObjWater.h"		//��
#include "ObjRopeSwitch.h"	//���[�v�X�C�b�`
#include "ObjEnemy.h"		//�G
#include "ObjBossEnemy.h"	//�{�X
#include "ObjStage3Boss.h"  //��O�X�e�[�W�{�X
#include "ObjTitle.h"		//�^�C�g��
#include "ObjSign.h"		//�Ŕ�
#include "ObjRope.h"        //��i�X�C�b�`�Ɉ����|�����j
#include "ObjGameClear.h"	//�N���A
#include "ObjGameOver.h"	//�Q�[���I�[�o�[
#include "ObjEndlessSpring.h"//�G�����V�X�e��(�G���h���X����)
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