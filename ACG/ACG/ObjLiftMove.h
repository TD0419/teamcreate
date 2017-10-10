#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�������t�g
class CObjLiftMove :public CObj
{
public:
	CObjLiftMove(int x, int y); // �R���X�g���N�^
	~CObjLiftMove() {};			// �f�X�g���N�^
	void Init();			// �C�j�V�����C�Y
	void Action();			// �A�N�V����
	void Draw();			// �h���[
	void HeroRide();		//�@��l��������Ă���Ƃ��̏���
							//�A�N�Z�T-----------------------------------------
	float GetVecX() { return m_vx; }	//�ړ��x�N�g��X��Ԃ�
	float GetVecY() { return m_vy; }	//�ړ��x�N�g��Y��Ԃ�

private:
	float m_px;		// �������t�gX���W
	float m_py;		// �������t�gY���W
	float m_vx;		// �������t�g�̈ړ��x�N�g��X
	float m_vy;		// �������t�g�̈ړ��x�N�g��Y

	//�}�b�v��̈ʒu�i�v�f���j
	int m_map_x;//X
	int m_map_y;//Y
};
