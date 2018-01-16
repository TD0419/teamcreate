#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//������u���b�N�̓����蔻�肪�Ȃ��Ȃ�ʒu
#define PERDECISION_CLEAR_POINT (1700.0f) 

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

	bool GetScreenOut() { return m_screen_out; }//��ʊO�Ƀu���b�N���o����������
private:

	float m_px;			//������u���b�NX���W
	float m_py;			//������u���b�NY���W
	int   m_falling_time;//�u���b�N��������܂ł̎���
	bool m_fallint_start_flag;//�u���b�N�𗎉������邩�ǂ����̃t���O

	float m_return_block_y;	//�u���b�N�����̈ʒu�ɖ߂����߂̕ϐ�
	bool m_screen_out;		//�u���b�N����ʊO�ɏo�Ă��邩�𒲂ׂ�
};
