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

//�R���g���X�g
CSceneMain::CSceneMain()
{

}
//�f�X�g���X�g
CSceneMain::~CSceneMain()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMain::InitScene()
{
	//�}�b�v���i�[�p�ϐ��e�X�g�p
	int map[MAP_Y][MAP_X] = { 0 };
	//�}�b�v����ǂݍ���
	MapDataLoading(map);


	//block�I�u�W�F�N�g�쐬
	CObjBlock* obj_block = new CObjBlock(map);
	Objs::InsertObj(obj_block, OBJ_BLOCK, 9);
}

//�Q�[�����C�����s�����\�b�h
void CSceneMain::Scene()
{

}
//�}�b�v�f�[�^�ǂݍ��݊֐�
void CSceneMain::MapDataLoading(int map[MAP_Y][MAP_X])
{
	//�O���f�[�^�̓ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p;//�X�e�[�W���|�C���^�[
	int size;				//�X�e�[�W���̑傫��

	p = Save::ExternalDataOpen(L"testomap.csv", &size);//�O���f�[�^�ǂݍ���

	if (p == nullptr)
	{
		MessageBox(0, L"�}�b�v�f�[�^��������܂���ł����B", L"�G���[�R�b�`��", MB_OK);
		return;
	}

	int count = 1;

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);
			
			map[i][j] = w;

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
void CSceneMain::InageDataLoading()
{
	//�摜�o�^ID
	int id = 0;
	//�O���t�B�b�N�ǂݍ���
	//Draw::LoadImageW(L"", id++, TEX_SIZE_???);
}

//���y�f�[�^�ǂݍ��݊֐�
void CSceneMain::AudioDataLoading()
{
	//���y�o�^ID
	int id = 0;

	//Audio::LoadAudio(id++, L"", ? ? ? ? );
	
}