#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�{�X
class CObjBossEnemy :public CObj
{
public:
    CObjBossEnemy();        //�R���X�g���N�^
    ~CObjBossEnemy() {};	//�f�X�g���N�^
    void Init();	        //�C�j�V�����C�Y
    void Action();	        //�A�N�V����
    void Draw();	        //�h���[
private:
    float m_x;	//X���W
    float m_y;	//Y���W
    float m_vx;	//X�������̃x�N�g��
    float m_vy;	//Y�������̃x�N�g��

    int m_hp;   //�{�X�̂g�o

};