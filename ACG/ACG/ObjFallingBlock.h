#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�X�e�[�W5�{�X���p������u���b�N
class CObjFallingBlock :public CObj
{
public:
	CObjFallingBlock(int x, int y); 	//�R���X�g���N�^
	~CObjFallingBlock() {};				//�f�X�g���N�^
	void Init();						//�C�j�V�����C�Y
	void Action();						//�A�N�V����
	void Draw();						//�h���[
	void HeroHit();						//��l���Ƃ̓����蔻�����������

	//�}�b�v��̈ʒu�i�v�f���j
	int m_map_x;//X
	int m_map_y;//Y
private:
	
	float m_px;			//������u���b�NX���W
	float m_py;			//������u���b�NY���W
	int   m_falling_time;//�u���b�N��������܂ł̎���
};
