//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjBlock::CObjBlock(int map[MAP_Y][MAP_X])
{
	//�}�b�v�f�[�^�R�s�[
	//memcpy(m_map,map,sizeof(int) * (MAP_Y*MAP_X));

}
//�}�b�v�ύX�p
void CObjBlock::MapChange(int map[MAP_Y][MAP_X])
{
	//�}�b�v�f�[�^�R�s�[
	//memcpy(m_map,map,sizeof(int) * (MAP_Y*MAP_X));
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_scroll = 0.0f;
}


//�A�N�V����
void CObjBlock::Action()
{
}
//�h���[
void CObjBlock::Draw()
{
	
}