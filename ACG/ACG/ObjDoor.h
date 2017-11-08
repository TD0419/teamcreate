#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�h�A�Ƃ�������
class CObjDoor :public CObj
{
public:
	CObjDoor(int x, int y); // �R���X�g���N�^
	~CObjDoor() {};			// �f�X�g���N�^
	void Init();			// �C�j�V�����C�Y
	void Action();			// �A�N�V����
	void Draw();			// �h���[

	bool m_unlock_flag;		//�{�X���S�t���O
private:
	float m_px;	// �h�AX���W
	float m_py; // �h�AY���W

	//�A�j���[�V�����֘A
	int m_ani_door_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_door_frame;//�`��t���[��
	float m_ani_door_time_max;//�A�j���[�V��������Ԋu�ő�l
	
};
