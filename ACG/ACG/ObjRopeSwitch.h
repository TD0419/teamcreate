#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���[�v�X�C�b�`
class CObjRopeSwitch :public CObj
{
public:
    CObjRopeSwitch(int x, int y);       //�R���X�g���N�^
    ~CObjRopeSwitch() {};
	//�f�X�g���N�^
    void Init();	         //�C�j�V�����C�Y
    void Action();	         //�A�N�V����
    void Draw();	         //�h���[

	//�A�N�Z�T-----------------------------------------
	bool GetRopeFlag() { return m_rope_flag; }//���[�v�����������Ƃ��̏�Ԃ�Ԃ�

private:
    float m_px;	 // ���[�v�X�C�b�`X���W
    float m_py;	 // ���[�v�X�C�b�`Y���W
	//�}�b�v�̗v�f��
	int m_map_x;
	int m_map_y;

	bool m_rope_flag; //���[�v���������Ƃ��L������p
};