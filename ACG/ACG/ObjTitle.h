#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define FONT_SIZE_TITLE (54.0f)	//�����̃T�C�Y(�^�C�g���p)

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle :public CObj
{
public:
	CObjTitle() {}; 	//�R���X�g���N�^
	~CObjTitle() {};	//�f�X�g���N�^
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	int m_mode;				//���[�h�̑I��p�ϐ�(0�`2)
	bool m_keypush_flag;	//�L�[�̃g���K�[�����p�t���O
	bool m_enter_key_flag;  //�Q�[���I�[�o�[���炭��Ƃ����ɔ��ł��܂���ł���𐧌䂷��ϐ�
	

};
