#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjDownDrawBlock : public CObj
{
public:
	CObjDownDrawBlock(int x, int y);
	~CObjDownDrawBlock() {};

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }
	
private:

	float m_scroll; //���E�X�N���[���p
	float m_px;     //�u���b�N�ʒuX
	float m_py;     //�u���b�N�ʒuY


};