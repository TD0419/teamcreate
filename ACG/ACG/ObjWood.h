#pragma once
#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��(�M�~�b�N)
class CObjWood :public CObj
{
public:
    CObjWood();        //�R���X�g���N�^
    ~CObjWood() {};	   //�f�X�g���N�^
    void Init();	   //�C�j�V�����C�Y
    void Action();	   //�A�N�V����
    void Draw();	   //�h���[
private:
    float m_wood_x;	   // ��X���W
    float m_wood_y;	   // ��Y���W
   

};
