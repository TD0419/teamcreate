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
    float m_Boss_x;	 // �{�XX���W
    float m_Boss_y;	 // �{�XY���W
    float m_Boss_vx; // �{�XX�������̃x�N�g��
    float m_Boss_vy; // �{�XY�������̃x�N�g��

    int m_Boss_hp;   // �{�X�̂g�o

};
