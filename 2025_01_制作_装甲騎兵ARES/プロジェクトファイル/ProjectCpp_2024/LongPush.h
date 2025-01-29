//=========================================================
//
// Game_UI.cpp�Ŏg���֐�[Game_UI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LONGPUSH_H

#define _LONGPUSH_H//��d�C���N���[�h�h�~

#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "main.h"

#include "object.h"

//
class CLongPush : public CObject
{
public:

	typedef enum
	{
		UI_BOOST_BACK=0,
		UI_BOOST_MAIN,
		UI_MAX,
	}UITYPE;

	//static const int TEXNUM = 7;
	static const int MAX_PUSHCNT = 90;
	
	CLongPush(int nPriority = CObject::LAYERINDEX_LONGPUSH);//�R���X�g���N�^
	~CLongPush() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CLongPush* Create();//object����

	void InputpVtx(int nCnt);

	void AddCnt();
	void SubCnt();
	bool PushOkBool() { return m_bPushOk; };


private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[UI_MAX];//���_�o�b�t�@

	int m_nTexIdx[UI_MAX];

	//�^�C�v�i�[
	UITYPE m_UiType[UI_MAX];
	D3DXVECTOR3 m_Pos[UI_MAX];
	D3DXVECTOR3 m_Size[UI_MAX];
	
	float m_fLength[UI_MAX];

	int m_nCnt=0;
	//int m_nMotionCnt[UI_MAX] = 0;
	bool m_bPushOk = false;
};

#endif