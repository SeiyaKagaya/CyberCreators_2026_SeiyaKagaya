//=========================================================
//
// pause.cpp�Ŏg���֐�[pause.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PAUSE_H
#define _PAUSE_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

class CPause 
{
public:
	static const int TEXNUM = 7;
	CPause();//�R���X�g���N�^
	~CPause() ;//�f�X�g���N�^
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CPause* Create();//object����

	void AddSelectNum(int addnum);	//�I�������Z�i�[
	void DirectSetNum(int Num);		//�I�������ڊi�[
	int GetSelectNum();				//�I�����擾
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM] = {};//���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM] = {};		//�e�N�X�`��
	D3DXVECTOR3 m_Pos[TEXNUM] = {};					//���W
	int m_nTexIdx[TEXNUM] = {};						//�e�N�X�`��ID
	int m_SelectNum = 0;							//�I�����ԍ�
	bool m_bPhase2 = false;							//Pause���i�K��
};

#endif