#pragma once

//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�FWater(�M�~�b�N)
class CObjWater :public CObj
{
public:
	CObjWater(int x, int y); 	//�R���X�g���N�^
	~CObjWater() {};			//�f�X�g���N�^
	void Init();				//�C�j�V�����C�Y
	void Action();				//�A�N�V����
	void Draw();				//�h���[
private:
	float m_px;	//X���W
	float m_py;	//Y���W

	//�}�b�v��̈ʒu�i�v�f���j
	int m_map_x;//X
	int m_map_y;//Y

	//�A�j���[�V�����֌W
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	int m_water_audio_count; // ���̉��y����p�̕ϐ��@3.75���݂Ȃ̂�float
	int m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	float m_water_gauge; // ���ʊǗ�
	bool m_ani_start;//�A�j���[�V�����̎n�܂��Ă邩�ǂ���������킷�t���O
};