#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjEnemy : public CObj
{
public:
	CObjEnemy(); 	//�R���X�g���N�^
	~CObjEnemy() {};	//�f�X�g���N�^
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetVX() { return m_vx; }
	float GetVY() { return m_vy; }
	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetVX(float vx) { m_vx = vx; }
	void SetVY(float vy) { m_vy = vy; }
private:
	float m_x;	//X���W
	float m_y;	//Y���W
	float m_vx;	//X�������̃x�N�g��
	float m_vy;	//Y�������̃x�N�g��

};