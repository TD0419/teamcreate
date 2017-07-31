#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�g�F�e��
class CObjAngleBullet : public CObj
{
public :
	CObjAngleBullet(float x,float y,float r,float speed);	//�R���X�g���N�^
	~CObjAngleBullet(){};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_x;	//�I�u�W�F�N�g�̂�����
	float m_y;	//�I�u�W�F�N�g�̂�����
	float m_vx;	//�I�u�W�F�N�g�̈ړ��x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��x�N�g��Y
	float m_r;	//�ړ�����p�x
	float m_speed;//���x

	int	m_ani;		//���e�A�j���[�V�����p
	int m_ani_time;//���e�A�j���[�V�����Ԋu�^�C��
	bool m_del;		//�����`�F�b�N
	RECT_F m_eff;	//���e�G�t�F�N�g�`��p

};
