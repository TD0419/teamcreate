#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���˃u���b�N
class CObjReflectBlock : public CObj
{
public:
	CObjReflectBlock(int x, int y);
	~CObjReflectBlock() {};

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[


private:

	float m_x;     //�u���b�N�ʒuX
	float m_y;     //�u���b�N�ʒuY
};
