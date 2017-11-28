//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"

int g_remaining;//�c�@�Ǘ��p�ϐ�

//�R���X�g���N�^
CSceneMain::CSceneMain()
{
	g_remaining = 3;
}

//�R���X�g���N�^(���X�^�[�g�p)
//�����F�ϓ��������
CSceneMain::CSceneMain(int n)
{
	g_remaining += n;
}

//�Q�[�����C�����������\�b�h
void CSceneMain::InitScene()
{
	//�c�@���O�����ɂȂ�����GameOver��ʂֈړ�����
	if (g_remaining < 0)
	{
		Scene::SetScene(new CSceneGameOver());
		return;
	}
	AudioDataLoading();//���y�f�[�^�ǂݍ��݊֐�
	MapDataLoading(m_map);//�}�b�v����ǂݍ���
	ImageDataLoading();//�摜�f�[�^�ǂݍ��݊֐�
	
	
    //Map�I�u�W�F�N�g���쐬����
	CObjMap* objmap = new CObjMap(m_map,g_remaining);
	Objs::InsertObj(objmap, OBJ_MAP, 10);

	//�w�i�I�u�W�F�N�g���쐬����
	CObjBackGround* objback_ground = new CObjBackGround();
	Objs::InsertObj(objback_ground, OBJ_BACKGROUND, 1);

	//�^�C��
	CObjTime* objtime = new CObjTime();
	Objs::InsertObj(objtime, OBJ_TIME, 100);

	//�f�o�b�O�@�h�g���I�����������Ă��������I�h----------------
	
	//�v����--------------------------------------------------
	//�v���--------------------------------------------------

	//��]���e�X�g�p
	//CObjRollBlock* objrollblock = new CObjRollBlock(18,20,2);
	//Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 10);

	//objrollblock = new CObjRollBlock(10, 15, 1);
	//Objs::InsertObj(objrollblock, OBJ_ROLL_BLOCK, 10);

	//���Ɨ����郊�t�g(�f�o�b�O���ɂ��A�폜���Ȃ���)
	CObjFallingLift* objfalling_lift = new CObjFallingLift(10, 18);
	Objs::InsertObj(objfalling_lift, OBJ_FALLING_LIFT, 10);
	
	//�X�e�[�W�T�̊g�U�e
	/*CObjDiffusionCannon* objtime2 = new CObjDiffusionCannon(3,20);
	Objs::InsertObj(objtime2, OBJ_DIFFUSION_CANNON, 100);
*/
	//�f�o�b�O--------------------------------------------------


	//BGM�Đ�
	/*
	
	Audio::Start(STAGE5);*/

}

//�Q�[�����C�����s�����\�b�h
void CSceneMain::Scene()
{

}

//�}�b�v�f�[�^�ǂݍ��݊֐�
void CSceneMain::MapDataLoading(int map[MAP_Y_MAX][MAP_X_MAX])
{
	//�O���f�[�^�̓ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p;	//�X�e�[�W���|�C���^�[
	int size;				//�X�e�[�W���̑傫��

	//�f�o�b�O�p�X�e�[�W�ԍ������p
	UserData* s = (UserData*)Save::GetData();
	s->stagenum = 2;
	//----------------

	//�X�e�[�W�ԍ����ƂɃX�e�[�W�ǂݍ���
	switch (((UserData*)Save::GetData())->stagenum )
	{
	case 1:
		Audio::Start(STAGE1);
		p = Save::ExternalDataOpen(L"stage1.csv", &size);//�O���f�[�^�ǂݍ���
		break;
	case 2:
		Audio::Start(STAGE2);
		p = Save::ExternalDataOpen(L"stage2.csv", &size);//�O���f�[�^�ǂݍ���
		break;
	case 3:
		p = Save::ExternalDataOpen(L"stage3.csv", &size);//�O���f�[�^�ǂݍ���
		break;
	default:
		break;
	}
	
	if (p == nullptr)
	{
		MessageBox(0, L"�}�b�v�f�[�^��������܂���ł����B", NULL, MB_OK);
		return;
	}

	//�O���̃}�b�v��񂸂炷���
	int count = 1;

	for (int i = 0; i < MAP_Y_MAX; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//�}�b�v��������
			int w = 0;
			//�}�b�v���擾
			swscanf_s(&p.get()[count], L"%d", &w);
			
			//�}�b�v������
			map[i][j] = w;
			
			//-1���������炷
			while (w/10 != 0)
			{
				count++;
				w /= 10;
			}
			count += 2;
		}
	}
}

//�摜�f�[�^�ǂݍ��݊֐�
void CSceneMain::ImageDataLoading()
{

	//�X�e�[�W�ʂ̉摜�ǂݍ���
	switch (((UserData*)Save::GetData())->stagenum)
	{
	//�X�e�[�W�P
	case 1:
		//�w�i�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\BackGround\\Stage1.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//���t�g�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Lift\\Stage1.png", GRA_LIFT, TEX_SIZE_128);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Block\\Stage1.png", GRA_BLOCK, TEX_SIZE_128);
		
		break;
	//�X�e�[�W�Q
	case 2:
		//�w�i�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\BackGround\\Stage2.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//���t�g�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Lift\\Stage2.png", GRA_LIFT, TEX_SIZE_128);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Block\\Stage2.png", GRA_BLOCK, TEX_SIZE_128);
		//���蔲����u���b�N�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Throughblock.png", GRA_THROUGH_BLOCK, TEX_SIZE_64);
		//�{�X�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Gorira.png", GRA_BOSS, TEX_SIZE_1024);
		//�S�����̓������ǂݍ���
		Draw::LoadImageW(L"Image\\Coconut.png", GRA_COCONUT, TEX_SIZE_32);
		break;
	//�X�e�[�W�R
	case 3:
		//���t�g�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Lift\\Stage3.png", GRA_LIFT, TEX_SIZE_128);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Block\\Stage3.png", GRA_BLOCK, TEX_SIZE_128);
		//�L���m���̓ǂݍ���
		Draw::LoadImageW(L"Image\\Cannon.png", GRA_CANNON, TEX_SIZE_64);
		//lastwall3�摜�̓ǂݍ���
		Draw::LoadImageW(L"Image\\Lastwall3.png", GRA_LAST_WALL, TEX_SIZE_256);//��
		Draw::LoadImageW(L"Image\\Openwall3.png", GRA_OPEN_WALL, TEX_SIZE_512);//��
		break;
	//�X�e�[�W�S
	case 4:
	//�X�e�[�W�T
	case 5:
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Block\\Stage5.png", GRA_BLOCK, TEX_SIZE_128);
		//��]�u���b�N�̉摜�ǂݍ���
		Draw::LoadImageW(L"Image\\RollBlock.png", GRA_ROLL_BLOCK, TEX_SIZE_256);
		//���ԃu���b�N�̓ǂݍ���
		Draw::LoadImageW(L"Image\\Block\\Buttery_Upper_Floor.png", GRA_ROLL_BLOCK, TEX_SIZE_256);
		//Stage5��C�̓ǂݍ���
		Draw::LoadImageW(L"Image\\Stage5Cannon.png", GRA_CANNON, TEX_SIZE_128);
		//��]�u���b�N�̎d�|���̃X�C�b�`�̉摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Vis_Blackball.png", GRA_BLACK_BALL, TEX_SIZE_16);
		//�j�̓ǂݍ���
		Draw::LoadImageW(L"Image\\Needle.png", GRA_NEEDLE, TEX_SIZE_32);
		//�j�̓y��̓ǂݍ���
		Draw::LoadImageW(L"Image\\Needle stand.png", GRA_NEEDLE_STAND, TEX_SIZE_64);
		//���[�v�łԂ牺���邱�Ƃ��ł���M�~�b�N
		Draw::LoadImageW(L"Image\\Vis_Blackball2.png", GRA_TARZAN_POINT, TEX_SIZE_16);

		break;

	//�摜���p�ӂ���Ă��Ȃ��ꍇ
	default:
		//�w�i�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\BackGround\\Stage1.png", GRA_BACKGROUND, TEX_SIZE_1536);
		//���t�g�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Lift\\Stage1.png", GRA_LIFT, TEX_SIZE_128);
		//�u���b�N�摜�ǂݍ���
		Draw::LoadImageW(L"Image\\Block\\Stage1.png", GRA_BLOCK, TEX_SIZE_128);
		break;
	}
	
	//�v���C���[�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Hero.png", GRA_HERO, TEX_SIZE_1024);

	//��l���̒e�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Hero_bullet.png", GRA_HERO_BULLET, TEX_SIZE_64);
	//�n�V�S�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Ladders.png", GRA_LADDERS, TEX_SIZE_64);

	//�h�A & ���摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Door.png", GRA_DOOR, TEX_SIZE_256);

	//��(�M�~�b�N)�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Wood.png", GRA_WOOD, TEX_SIZE_512);
	
	//�G�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Snake.png", GRA_ENEMY, TEX_SIZE_256);

	//���o�[�X�C�b�`�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Lever.png", GRA_LEVER_SWICH, TEX_SIZE_128);

	//��摜�ǂݍ���
	Draw::LoadImageW(L"Image\\rock.png", GRA_ROCK, TEX_SIZE_512);

	//Water�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Water.png", GRA_AQUATIC, TEX_SIZE_1024);

	//���[�v�X�C�b�`�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\RopeSwitch.png", GRA_ROPE_SWITCH, TEX_SIZE_64);
	
	//�Ŕ̘g���摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Sign.png", GRA_SIGN_FRAME, TEX_SIZE_256);
	
	//�Ŕ̓ǂݍ���
	Draw::LoadImageW(L"Image\\Billboard_stage1.png", GRA_SIGN, TEX_SIZE_64);

	//�{�^���ǂݍ���
	Draw::LoadImageW(L"Image\\button.png", GRA_BUTTON, TEX_SIZE_128);

	//lastwall�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\Lastwall.png", GRA_LAST_WALL, TEX_SIZE_256);//��
	Draw::LoadImageW(L"Image\\Openwall.png", GRA_OPEN_WALL, TEX_SIZE_512);//��

	//���C�t(��)�摜�ǂݍ���
	Draw::LoadImageW(L"Image\\zanki.png", GRA_LIFE, TEX_SIZE_64);
	
	//��]�u���b�N�̉摜�ǂݍ���
	Draw::LoadImageW(L"Image\\RollBlock.png", GRA_ROLL_BLOCK, TEX_SIZE_256);
	Draw::LoadImageW(L"Image\\Rotate_Block2.png", GRA_ROLL_BLOCK2, TEX_SIZE_256);
	
	//�S�����̓������ǂݍ���
	Draw::LoadImageW(L"Image\\Coconut.png", GRA_COCONUT, TEX_SIZE_32);
	
	//��]�u���b�N�̃X�C�b�`
	Draw::LoadImageW(L"Image\\Vis_Blackball.png", GRA_ROLL_BLOCK_SWITCH, TEX_SIZE_16);

	//�X�e�[�W5�̑�C
	Draw::LoadImageW(L"Image\\Stage5Cannon.png", GRA_CANNON, TEX_SIZE_128);

	//�X�e�[�W5�̑�C�̒e�i���j
	Draw::LoadImageW(L"Image\\Enemy_Bullet.png", GRA_CANNON_BEAM, TEX_SIZE_64);

}

//���y�f�[�^�ǂݍ��݊֐�
void CSceneMain::AudioDataLoading()
{
//BGM--------------------------------------------------------

	//�X�e�[�W1
	Audio::LoadAudio(STAGE1, L"BGM\\Grassland6.wav",BACK_MUSIC);
	//�X�e�[�W2
	Audio::LoadAudio(STAGE2, L"BGM\\Jangle.wav", BACK_MUSIC);

	//�X�e�[�W2_BOSS
	Audio::LoadAudio(STAGE2_BOSS, L"BGM\\BOSS2.wav", BACK_MUSIC);

	//�X�e�[�W5
	Audio::LoadAudio(STAGE5, L"BGM\\Temple1.wav", BACK_MUSIC);
//------------------------------------------------------------

//SE--------------------------------------------------------
	//�e�̔���
	Audio::LoadAudio(FIRING, L"SE\\Firing1.wav", EFFECT);

	//��̑ł��o��
	Audio::LoadAudio(ROPE, L"SE\\Rope2.wav", EFFECT);

	//��̔���
	Audio::LoadAudio(ROCK, L"SE\\Rock2.wav", EFFECT);

	//�Ō�̕ǂ̊J��
	Audio::LoadAudio(WALL, L"SE\\Door1.wav", EFFECT);

	//�؂̓]�|
	Audio::LoadAudio(TREE, L"SE\\Tree3.wav", EFFECT);

	//�h�A�̊J��
	Audio::LoadAudio(DOOR, L"SE\\Wood Door.wav",EFFECT);

	//�G�ɒ��e
	Audio::LoadAudio(LANDING, L"SE\\Landing1.wav", EFFECT);

	//���o�[�X�C�b�`
	Audio::LoadAudio(LEVER, L"SE\\Lever1.wav", EFFECT);

	//�{�^��
	Audio::LoadAudio(BUTTON, L"SE\\Switch2.wav", EFFECT);

	//�G�̒e��
	Audio::LoadAudio(ENEMYFIR, L"SE\\Enemy Fir3.wav", EFFECT);

	//���t�g(��������)
	Audio::LoadAudio(PLIFT, L"SE\\LiftTrickPull.wav", EFFECT);

	//���t�g(����)
	Audio::LoadAudio(RLIFT, L"SE\\LiftTrickRelease.wav", EFFECT);

	//���̗���鉹
	Audio::LoadAudio(WAVE, L"SE\\Wave.wav", EFFECT);

	//�S�����̓�����
	Audio::LoadAudio(GORILLATHROW, L"SE\\Gorilla Throw5.wav", EFFECT);
//------------------------------------------------------------
}