#pragma once
//�g�p����w�b�_�[

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F����
class CObjWireMesh :public CObj
{
public:
	CObjWireMesh(int x, int y);	// �R���X�g���N�^
	~CObjWireMesh() {};			// �f�X�g���N�^
	void Init();				// �C�j�V�����C�Y
	void Action();				// �A�N�V����
	void Draw();				// �h���[

private:
	float m_px;		//�ʒuX
	float m_py;		//�ʒuY
	//�}�b�v�̗v�f��
	int m_map_x;
	int m_map_y;
};
