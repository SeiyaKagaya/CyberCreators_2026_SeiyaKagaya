//=========================================================
//
// Tutorial.cppで使う関数[Tutorial.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TUTORIAL_H
#define _TUTORIAL_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

class CTutorialUI
{
public:
	static const int TEXNUM = 3;
	CTutorialUI();//コンストラクタ
	~CTutorialUI();//デストラクタ
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static CTutorialUI* Create();//object生成

	void AddSelectNum(int addnum);//選択肢加算格納
	void DirectSetNum(int Num);	  //選択肢直接格納
	int GetSelectNum();			  //選択肢取得

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[TEXNUM] = {};//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture[TEXNUM] = {};		//テクスチャ
	D3DXVECTOR3 m_Pos[TEXNUM] = {};					//座標
	int m_nTexIdx[TEXNUM] = {};						//テクスチャID
	int m_SelectNum = 0;							//選択肢番号
	bool m_bPhase2 = false;							//Pause第二段階か
};

#endif