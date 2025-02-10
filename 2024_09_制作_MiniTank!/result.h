//=========================================================
//
// result.cpp�Ŏg���֐�[result.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _result_H
#define _result_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"
//
class CResultUI : public CObject
{
public:
	static const int TEXNUM = 1;
	CResultUI(int nPriority = CObject::LAYERINDEX_RESULTUI);//�R���X�g���N�^
	~CResultUI() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CResultUI* Create();//object����
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM] = {};//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM] = {};     //�e�N�X�`��
	int m_nTexIdx[TEXNUM] = {};						//�e�N�X�`���ԍ�
	D3DXVECTOR3 m_Pos[TEXNUM] = {};					//���W
};

#endif