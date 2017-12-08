#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��
class CObjRock :public CObj
{
public:
	CObjRock(int x, int y); //�R���X�g���N�^
	~CObjRock() {};			//�f�X�g���N�^
	void Init();			//�C�j�V�����C�Y
	void Action();			//�A�N�V����
	void Draw();			//�h���[
private:
	float m_px;				//��X���W
	float m_py;				//��Y���W

	bool m_ani_start_flag;//�A�j���[�V�����̃t���O�𗧂Ă邽�߂̕ϐ�

	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	bool m_ani_start;//�A�j���[�V�����̎n�܂��Ă邩�ǂ���������킷�t���O
	int m_rock_determine;//�u���b�N�̔���p
};