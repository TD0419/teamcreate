#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[���F�^�C�g��
class CSceneTitle :public CScene
{
public:
	CSceneTitle() {};
	~CSceneTitle() {};
	void InitScene();		//���������\�b�h
	void Scene();			//���s�����\�b�h
	void ImageDataLoading();//�摜�f�[�^�ǂݍ��݊֐�
	void AudioDataLoading();//���y�f�[�^�ǂݍ��݊֐�
private:
};