#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�{�X��(�h���b�v�A�C�e��)
class CObjBossDropKey :public CObj
{
public:
	CObjBossDropKey(int x, int y);  //�R���X�g���N�^
	~CObjBossDropKey() {};			//�f�X�g���N�^
	void Init();					//�C�j�V�����C�Y
	void Action();					//�A�N�V����
	void Draw();					//�h���[
private:
	float m_px;	   // �{�X��X���W
	float m_py;	   // �{�X��Y���W


};
