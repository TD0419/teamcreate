#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�N���X�@��]�u���b�N�X�C�b�`
class CObjRollBlockSwitch : public CObj
{
public:
	CObjRollBlockSwitch(float x, float y, CObjRollBlock* p);		//�R���X�g���N�^
	~CObjRollBlockSwitch() {};	//�f�X�g���N�^

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	//���[�v�Ɖ�]�u���b�N�X�C�b�`�̈ʒu�𒲐�����֐�
	void PositionAdjustment();
private:
	//�ʒu
	float m_px;
	float m_py;
	float m_r;
	bool  m_rotation_flag; //��]�����邩�ǂ����̃t���O�@true=��]����A��]���Ă���@false=��]���Ȃ��A��]���Ă��Ȃ�

	//�u���b�N�̃|�W�V����
	float m_base_block_px;
	float m_base_block_py;

	//�X�C�b�`����p�������]�u���b�N�̃|�C���^
	CObjRollBlock* mp_base_block;

	//���[�v�ƏՓ˂��Ă��邩�ǂ����t���O
	//true = �Փ˂��Ă���@false = �Փ˂��Ă��Ȃ�
	bool m_rope_hit_flag;
};