#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjHero:public CObj
{
public:
	CObjHero(int x, int y); 		//�R���X�g���N�^
	~CObjHero() {};					//�f�X�g���N�^
	void Init();					//�C�j�V�����C�Y
	void Action();					//�A�N�V����
	void Draw();					//�h���[
	void Scroll();					//�X�N���[�������̊֐�
	void LandingCheck();			//���n�ł��Ă邩�ǂ����𒲂ׂ�֐�
	bool HitUpCheck(int obj_name);	//�w�肵���I�u�W�F�N�g�̏㑤�Ɠ������Ă��邩����ׂ�֐�


	//�A�N�Z�T------------------------------------------
	void SetVecX(float x) { m_vx = x; };	//�x�N�g��X���Z�b�g����
	void SetVecY(float y) { m_vy = y; };	//�x�N�g��Y���Z�b�g����
	void SetPosX(float x) { m_px = x; };	//�|�W�V����X���Z�b�g����
	void SetPosY(float y) { m_py = y; };	//�|�W�V����Y���Z�b�g����
	void SetHitDown(bool b) { m_hit_down = b; }; //�q�b�g�_�E�����Z�b�g����
	float GetPosX() { return m_px; }		//�|�W�V����X��Ԃ�
	float GetPosY() { return m_py; }		//�|�W�V����X��Ԃ�
	float GetVecX() { return m_vx; }		//�x�N�g��X��n��
	float GetVecY() { return m_vy; }		//�x�N�g��Y��n��

private:
	float m_px;		//X���W
	float m_py;		//Y���W
	float m_vx;		//X�������̃x�N�g��
	float m_vy;		//Y�������̃x�N�g��
	float m_posture;//�p��
	float m_r;		//��l���̉�]�p�x

	bool  m_bullet_control; //�e�۔��ː���p
	bool  m_rope_control;	//���[�v���ː���p

	//�A�j���[�V�����֌W
	int m_ani_frame_stop;	//�~�܂������̕`��𒲐�
	int m_ani_time;			//�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;		//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l

	bool m_landingflag;		//���n���Ă邩�ǂ����̃t���O
	

	//block�Ƃ̏Փˊm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	
};