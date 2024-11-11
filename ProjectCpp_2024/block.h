//=========================================================
//
// block.cpp�Ŏg���֐�[block.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BLOCK_H

#define _BLOCK_H//��d�C���N���[�h�h�~

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
//
class CBlock : public CObject2D
{
public:

	static const int BLOCK_WIDE = 50;
	static const int BLOCK_HEIGHT = 50;
	const int STARTLIFE = 100;

	CBlock(int nPriority = CObject::LAYERINDEX_BLOCK);//�R���X�g���N�^
	~CBlock() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Damage(int nDamage);

	//���_�i�[
	void InputpVtx()override;

	static CBlock* Create(DATA data);//�I�u�W�F�N�g����
private:

	int m_nLife;
	int m_nCounterAnim;//�A�j��Counter
	int m_nDirectionMove;//����//0���E����1����
	int m_nPatternAnim;//�p�^�[���ԍ�

};

#endif