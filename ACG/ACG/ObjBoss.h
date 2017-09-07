#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�{�X
class CObjBoss :public CObj
{
public:
    CObjBoss(int x,int y);  //�R���X�g���N�^
    ~CObjBoss() {};			//�f�X�g���N�^
    void Init();	        //�C�j�V�����C�Y
    void Action();	        //�A�N�V����
    void Draw();	        //�h���[

	void SetVecX(float x) { m_vx = x; };	//�x�N�g��X���擾�p
	void SetVecY(float y) { m_vy = y; };	//�x�N�g��Y���擾�p
	void SetPosX(float x) { m_x = x; };		//�|�W�V����X���擾�p
	void SetPosY(float y) { m_y = y; };		//�|�W�V����Y���擾�p
	float GetPosX() { return m_x; }			//�|�W�V����X��Ԃ�
	float GetPosY() { return m_y; }			//�|�W�V����Y��Ԃ�
private:
    float m_x;		 // �{�XX���W
    float m_y;		 // �{�XY���W
    float m_vx;		 // �{�XX�������̃x�N�g��
    float m_vy;		 // �{�XY�������̃x�N�g��

    int m_hp;		 // �{�X�̂g�o
	float m_r;		 // �{�X�̉�]�p�x

	//block�Ƃ̏Փˊm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
};
