#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���[�v�X�C�b�`
class CObjRopeSwitch :public CObj
{
public:
    CObjRopeSwitch() {};        //�R���X�g���N�^
    ~CObjRopeSwitch() {};	 //�f�X�g���N�^
    void Init();	         //�C�j�V�����C�Y
    void Action();	         //�A�N�V����
    void Draw();	         //�h���[
private:
    float m_RopeSwitch_x;	 // ���[�v�X�C�b�`X���W
    float m_RopeSwitch_y;	 // ���[�v�X�C�b�`Y���W


};