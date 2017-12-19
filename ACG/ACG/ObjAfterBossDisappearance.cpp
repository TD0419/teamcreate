#include "GameL\DrawTexture.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjAfterBossDisappearance.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjAfterBossDisappearance::Init()
{
	//�}�b�v�����擾
	CObjMap* objmap = (CObjMap*)Objs::GetObj(OBJ_MAP);

	//�}�b�v���Ƀh�A��ǉ�
	objmap->SetMap(108,18, MAP_GOAL_DOOR);

	//�h�A���쐬
	CObjDoor* objDoor = new CObjDoor(108, 18);
	Objs::InsertObj(objDoor, OBJ_DOOR, 9);
}

//�A�N�V����
void CObjAfterBossDisappearance::Action()
{
	
}

//�h���[
void CObjAfterBossDisappearance::Draw()
{
	
}