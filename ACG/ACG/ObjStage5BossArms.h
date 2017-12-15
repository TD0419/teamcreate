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

	//�A�N�Z�T�[�[�[�[�[-------------------------------
	void SetPosX(float x) { m_px = x; }//�|�W�V����X���Z�b�g����
	void SetPosY(float y) { m_py = y; }//�|�W�V����Y���Z�b�g����
	void SetVecX(float vx) { m_vx = vx; }//�x�N�g��X���Z�b�g����
	void SetVecY(float vy) { m_vy = vy; }//�x�N�g��Y���Z�b�g����

	float GetPosX() { return m_px; }//�|�W�V����X��n��
	float GetPosY() { return m_py; }//�|�W�V����Y��n��
	float GetVecX() { return m_vx; }//�x�N�g��X��n��
	float GetVecY() { return m_vy; }//�x�N�g��Y��n��

	void DiffusionAttack(int limit_time);		//�g�U�e��łU��

	void SetPosture(bool posture) { m_input_posture = posture; }//���͎p���Z�b�g����@true=�J���@false=����
	//-------------------------------------------------

	void ArmLowerAttack(float x,int time);	//�r�����낷�U��
private:
	float m_px;	 // ��܃{�X�̃A�[��X���W
	float m_py;	 // ��܃{�X�̃A�[��Y���W
	
	float m_vx;  // ��܃{�X�̃A�[��X���ړ��x�N�g��
	float m_vy;  // ��܃{�X�̃A�[��Y���ړ��x�N�g��

	float m_arm_lower_marker_px;//�r�����낷�ʒu���������ǂ����Ƃ���X�ʒu�@0.0f�ȉ� �������Ȃ��@0.0f�𒴂��遁��������X�ʒu���

	float m_initial_px;//����X�ʒu(�{�X�̉�)
	float m_initial_py;//����Y�ʒu(�{�X�̉�)

	int m_arms_type;	 //��܃{�X�A�[���̃^�C�v(1�c���C�g�A�[��  2�c���t�g�A�[��)

	int m_arm_hp;    // ��܃{�X�̃A�[���̂g�o

	bool m_posture;//�p�@true=�J���Ă���@false=���Ă���
	bool m_input_posture;//���͂��ꂽ�p�@true=�J���Ă���	false=���Ă���
	bool m_hit_flag;//�Փˎ��̑��d�����h���t���O

	int m_ani_frame_claw;//�`��t���[��(��)
	int m_ani_time_claw;	//�A�j���[�V�����t���[�����슴�o(��)
	int m_ani_max_time_claw;//�A�j���[�V�����t���[�����슴�o�ő�l(��)

	void UpdateInitial();//�����ʒu���v�Z����
};