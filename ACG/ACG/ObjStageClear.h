#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�X�e�[�W�N���A�́i�����������j�N���X
class CObjStageClear : public CObj
{
public:
	CObjStageClear(int x,int y);
	~CObjStageClear() {};
	void Init();
	void Action();
	void Draw();
private:
	//�`��̈ʒu
	float m_px;
	float m_py;
	float m_scroll_x;
	float m_scroll_y;
};
