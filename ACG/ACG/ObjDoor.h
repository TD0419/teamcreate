#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�h�A
class CObjDoor :public CObj
{
public:
	CObjDoor(int x, int y); // �R���X�g���N�^
	~CObjDoor() {};			// �f�X�g���N�^
	void Init();			// �C�j�V�����C�Y
	void Action();			// �A�N�V����
	void Draw();			// �h���[

private:
	float m_px;	// �h�AX���W
	float m_py; // �h�AY���W
	bool m_unlock_flag;		//�{�X���S�t���O
	bool m_boss_save;		//�{�X�̏��ۑ�
	//�A�j���[�V�����֘A
	int m_ani_door_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_door_frame;//�`��t���[��
	float m_ani_door_time_max;//�A�j���[�V��������Ԋu�ő�l
	
	//�X�e�[�W�ɂ���Ẵh�A�̎�ޕύX
	//1=�G�l�~�[���j�ŊJ���@2,5���{�X���j�ŊJ��
	int m_door_type;
	
	bool m_goal_flag; // �S�[���t���O(�S�[���̏���������񂾂��ɂ���p) true:�S�[������ false:�S�[�����Ă��Ȃ�
};
