//=========================================================
//
// renderer.cppで使う関数[renderer.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _RENDERER_H
#define _RENDERER_H//二重インクルード防止

#include <Windows.h>
#include "object.h"
#include "d3dx9.h"//描写処理に使う

class CRenderer
{
public:
	CRenderer();//コンストラクタ
	~CRenderer();//デストラクタ
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	LPDIRECT3DDEVICE9 GetDevice();//3Dデバイスの取得
	
private:
	LPDIRECT3D9 m_pD3D;				//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;	//Direct3Dデバイス
	LPD3DXFONT m_pFont;				//フォントへのポインタ
	CObject* m_pCObject = nullptr;
	bool m_mesh;					//ワイヤーフレーム切り替え用
	void DrawFPS(void);
};
#endif