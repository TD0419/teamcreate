#pragma once
//�g�p����w�b�_�[
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�n�V�S
class CObjLadders :public CObj
{
public:
	CObjLadders(int x,int y,bool look);	//�R���X�g���N�^
	~CObjLadders() {};					//�f�X�g���N�^
	void Init();						//�C�j�V�����C�Y
	void Action();						//�A�N�V����
	void Draw();						//�h���[
	void HeroHit(float px, float py);//�v���C���[�����������Ƃ��̏���
	bool GetHeroJumpCon() { return m_hero_jump_con; } //��l�������ʂɃW�����v����̂𐧌䂷��ϐ���Ԃ�
private:
	float m_px;					//�n�V�SX���W
	float m_py;					//�n�V�SY���W
	int m_map_x;				//�}�b�v�v�f��X
	int m_map_y;				//�}�b�v�v�f��Y
	float m_up_and_down_speed;  //�n�V�S�̏�艺�莞�̑��x
	bool  m_obj_look_f;			//�n�V�S�������邩�ǂ��� false:�����Ȃ� true:������
	bool  m_side_block_flag;	//�T�C�h�Ƀu���b�N�����邩���m�F����
	bool  m_side_through_block_flag;	//�T�C�h�ɃX���[�u���b�N�����邩���m�F����
	bool  m_hero_jump_con;      //��l�������ʂɃW�����v����̂𐧌�
};
