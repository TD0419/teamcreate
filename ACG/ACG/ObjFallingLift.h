#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���Ɨ����郊�t�g(�M�~�b�N)
class CObjFallingLift :public CObj
{
public:
	CObjFallingLift(int x, int y); 		//�R���X�g���N�^
	~CObjFallingLift() {};				//�f�X�g���N�^
	void Init();						//�C�j�V�����C�Y
	void Action();						//�A�N�V����
	void Draw();						//�h���[
	void HeroRide();					//��l��������Ă���Ƃ��̏���
private:
	float m_px;							//�����郊�t�g(�M�~�b�N)X���W
	float m_py;							//�����郊�t�g(�M�~�b�N)Y���W
	bool m_get_on_flag;					//��l���������郊�t�g�̏�ɏ���Ă��邩���ׂ�
};
