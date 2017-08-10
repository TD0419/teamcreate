#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_BUTTON,
	OBJ_HERO,
	OBJ_ROCK,
    OBJ_BOSS_ENEMY,
	OBJ_TITLE,
	OBJ_BLOCK,
	OBJ_LIFT,
	OBJ_GAME_OVER,
	OBJ_MAP,
    OBJ_WOOD,
    OBJ_ROPE_SWITCH,
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_PLAYER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_MAGIC,
	ELEMENT_FIELD,
	ELEMENT_RED,
	ELEMENT_GREEN,
	ELEMENT_BLUE,
	ELEMENT_BLACK,
	ELEMENT_WHITE,
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
#define WINDOW_SIZE_W	(1024)
#define WINDOW_SIZE_H	(768)
//�𑜓x�T�C�Y
#define PIXEL_SIZE_W	(1024)
#define PIXEL_SIZE_H	(768)

//�}�b�v�T�C�Y
#define MAP_X 10
#define MAP_Y 10

//�I�u�W�F�N�g�̃T�C�Y
#define HERO_SIZE 64.0f

//�X�N���[���̃��C��
#define SCROLL_LINE_LEFT	(480.0f)
#define SCROLL_LINE_RIGHT	(WINDOW_SIZE_W - SCROLL_LINE_LEFT)
#define SCROLL_LINE_UP		(250.0f)
#define SCROLL_LINE_DOWN	(WINDOW_SIZE_H - SCROLL_LINE_UP)

//------------------------------------------------
//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_-----------------
#include "ObjButton.h"
#include "ObjHero.h"
#include "ObjRock.h"
#include "ObjBossEnemy.h"
#include "ObjTitle.h"
#include "ObjBlock.h"
#include "ObjLift.h"
#include "ObjLadders.h"
#include "ObjMap.h"
#include "ObjWood.h"
#include "ObjRopeSwitch.h"
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"
//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneMain
//-----------------------------------------------