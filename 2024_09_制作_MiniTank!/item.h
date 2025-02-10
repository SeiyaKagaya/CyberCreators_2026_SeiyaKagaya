//=========================================================
//
// item.cpp�Ŏg���֐�[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ITEM_H
#define _ITEM_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"
#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��

class CItem : public CObject2D
{
public:

	static const int ITEM_SIZE = 20;//�T�C�Y

	CItem(int nPriority = CObject::LAYERINDEX_ITEM);//�R���X�g���N�^
	~CItem() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//���_�i�[
	void InputpVtx()override;

	static CItem* Create(DATA data);//�I�u�W�F�N�g����
};
#endif