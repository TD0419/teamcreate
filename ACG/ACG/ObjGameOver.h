#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define TEXT_SIZE (52.0f)	//�����̃T�C�Y

//�I�u�W�F�N�g�F�Q�[���I�[�o�[
class CObjGameOver : public CObj
{
public:
	CObjGameOver() {};
	~CObjGameOver() {};
	void Init();		//�C�j�V�����C�Y
	void Action();		//�A�N�V����
	void Draw();		//�h���[
private:
	int m_mode;				//���[�h�̑I��p�ϐ�(0�`1)
	bool m_keypush_flag;	//�L�[�̃g���K�[�����p�t���O
	bool m_enter_key_flag;  //�����ɔ��ł��܂���ł���𐧌䂷��ϐ�
	
};