#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��(�M�~�b�N)
class CObjWood :public CObj
{
public:
    CObjWood(int x, int y);     //�R���X�g���N�^
    ~CObjWood() {};				//�f�X�g���N�^
    void Init();				//�C�j�V�����C�Y
    void Action();				//�A�N�V����
    void Draw();				//�h���[
	void HeroHit(float px, float py);	//��l�����G�ꂽ�Ƃ��̏���
private:
    float m_px;		//��X���W
    float m_py;		//��Y���W
	float m_r;		//��]�p�x
};
