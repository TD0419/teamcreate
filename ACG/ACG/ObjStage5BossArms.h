#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//------------------------------------------

//�I�u�W�F�N�g�F��܃X�e�[�W�̃{�X�̘r
class CObjStage5BossArms :public CObj
{
public:
	//�X�e�[�W5�{�Xcpp����̕`��̓s���ŁAx��y�̌^��int����float�ɕύX���Ă��܂��B(�`��ōׂ����l���g����������)
	CObjStage5BossArms(float x, float y ,int type);      //�R���X�g���N�^
	~CObjStage5BossArms() {};	//�f�X�g���N�^
	void Init();	        //�C�j�V�����C�Y
	void Action();	        //�A�N�V����
	void Draw();	        //�h���[


private:
	float m_px;	 // ��܃{�X�̃A�[��X���W
	float m_py;	 // ��܃{�X�̃A�[��Y���W
	
	float m_vx;  // ��܃{�X�̃A�[��X���ړ��x�N�g��
	float m_vy;  // ��܃{�X�̃A�[��Y���ړ��x�N�g��

	int m_arms_type;	 //��܃{�X�A�[���̃^�C�v(1�c���C�g�A�[��  2�c���t�g�A�[��)

	int m_arm_hp;    // ��܃{�X�̃A�[���̂g�o
	
	

};