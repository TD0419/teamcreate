#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�Q�[�����C��
class CSceneMain:public CScene
{
public:
	CSceneMain();
	~CSceneMain();
	void InitScene();//�Q�[�����C�����������\�b�h
	void Scene();   //�Q�[�����C���̎��s�����\�b�h
	void MapDataLoading(int map[10][10]);//�}�b�v�f�[�^�ǂݍ��݊֐��@�����͉�
	void InageDataLoading();//�摜�f�[�^�ǂݍ��݊֐�
	void AudioDataLoading();//���y�f�[�^�ǂݍ��݊֐�
private:
};