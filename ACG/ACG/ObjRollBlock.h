#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�N���X�@��]�u���b�N
class CObjRollBlock : public CObj
{
public:
	CObjRollBlock(int x,int y, int pattan) ;		//�R���X�g���N�^
	~CObjRollBlock() {};	//�f�X�g���N�^

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	
	void HeroHit();	//�q�[���[�����������Ƃ��̏���
	void SetRollFlag(bool f) { m_roll_flag = f; }//��]�̃t���O������֐�

	void HitRollBlockAndRope();//��]�u���b�N�ƃ��[�v(�S��)���ڐG���Ă����烍�[�v����������֐�
private:
	//�I�u�W�F�N�g�̈ʒu
	float m_px;		
	float m_py;		
	
	//��]�̒��S�ʒu
	float m_center_x;
	float m_center_y;

	//��]��̃|�W�V�����ƒ��S�ʒu�̍���
	float m_difference_x;
	float m_difference_y;

	//�}�b�v�̗v�f�ԍ�
	int m_map_x;
	int m_map_y;

	float m_r;		//��]�p
	int m_count;	//��]�̐���p�J�E���^�[
	int m_pattan;	//�^�C�v(1:��莞�Ԃŉ�],2�F���[�v�ň���������)
	int m_audio_time;//���y���d�����Ė�Ȃ����߂̃^�C��
	bool m_roll_flag;//��]���邩�ǂ����̃t���O
	bool m_pos_adjustment_flag;//�|�W�V�����̒��ߍς𒲂ׂ�t���O
	bool m_situation_width_flag;	//�u���b�N�̌����𒲂ׂ�t���O true:���@false:�c

};