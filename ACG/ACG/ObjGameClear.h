#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define FONT_SIZE_GC (86.0f)	//�����̃T�C�Y(�Q�[���N���A�p)

//�I�u�W�F�N�g�F�N���A
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};		//�R���X�g���N�^
	~CObjGameClear() {};	//�f�N�X���N�^
	void Init();			//�C�j�V�����C�Y
	void Action();			//�A�N�V����
	void Draw();			//�h���[

private:
	
};