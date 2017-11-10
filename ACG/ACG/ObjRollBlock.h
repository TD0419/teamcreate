#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�N���X�@��]�u���b�N
class CObjRollBlock : CObj
{
	CObjRollBlock(int x,int y) ;		//�R���X�g���N�^
	~CObjRollBlock() {};	//�f�X�g���N�^

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_px;		//�I�u�W�F�N�g�̈ʒuX
	float m_py;		//�I�u�W�F�N�g�̈ʒuY
	float m_r;		//��]�p
	int m_count;	//��]�̐���p�J�E���^�[
	bool m_roll_flag;//��]���邩�ǂ����̃t���O
};