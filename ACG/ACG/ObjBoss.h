#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�{�X
class CObjBoss :public CObj
{
public:
    CObjBoss(int x,int y);        //�R���X�g���N�^
    ~CObjBoss() {};	//�f�X�g���N�^
    void Init();	        //�C�j�V�����C�Y
    void Action();	        //�A�N�V����
    void Draw();	        //�h���[
private:
    float m_px;	 // �{�XX���W
    float m_py;	 // �{�XY���W
    float m_vx; // �{�XX�������̃x�N�g��
    float m_vy; // �{�XY�������̃x�N�g��

    int m_hp;   // �{�X�̂g�o

};
