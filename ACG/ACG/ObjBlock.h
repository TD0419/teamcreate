#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[MAP_X][MAP_Y]);
	~CObjBlock() {};

	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	//�}�b�v�ύX�p�֐�
	void MapChange(int map[MAP_Y][MAP_X]);

private:
	
	int m_map[MAP_Y][MAP_X]; //�}�b�v���

	float m_scroll;		//���E�X�N���[���p
	
};
