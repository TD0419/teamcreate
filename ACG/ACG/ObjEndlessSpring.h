#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N��
#define TIME (1.0)

//�I�u�W�F�N�g�F�G�����V�X�e��(�G���h���X����)
class CObjEndlessSpring :public CObj
{
public:
	CObjEndlessSpring();        //�R���X�g���N�^
	~CObjEndlessSpring() {};	//�f�X�g���N�^
	void Init();				//�C�j�V�����C�Y
	void Action();				//�A�N�V����
	void Draw();				//�h���[
private:
	float m_x;			 // �G�����V�X�e��X���W
	float m_y;			 // �G�����V�X�e��Y���W

	float m_timelag;	 //�G�����܂ł̊Ԋu����
	

};