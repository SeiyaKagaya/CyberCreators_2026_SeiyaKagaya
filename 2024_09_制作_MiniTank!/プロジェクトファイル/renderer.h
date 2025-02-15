//=========================================================
//
// renderer.cpp�Ŏg���֐�[renderer.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _RENDERER_H
#define _RENDERER_H//��d�C���N���[�h�h�~

#include <Windows.h>
#include "object.h"
#include "d3dx9.h"//�`�ʏ����Ɏg��

class CRenderer
{
public:
	CRenderer();//�R���X�g���N�^
	~CRenderer();//�f�X�g���N�^
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice();//3D�f�o�C�X�̎擾
	
private:
	LPDIRECT3D9 m_pD3D;				//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	//Direct3D�f�o�C�X
	LPD3DXFONT m_pFont;				//�t�H���g�ւ̃|�C���^
	CObject* m_pCObject = nullptr;
	bool m_mesh;					//���C���[�t���[���؂�ւ��p
	void DrawFPS(void);
};
#endif