//=========================================================
//
// block3D.cppで使う関数[block3D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BLOCK3D_H
#define _BLOCK3D_H//二重インクルード防止

#include "object.h"
#include "objectX.h"
#include <Windows.h>
#include "d3dx9.h"//描写処理に使う

class CBlock3D : public CObjectX
{
public:
	const float SIZE = 50.0f;

	CBlock3D(int nPriority = CObject::LAYERINDEX_OBJECT3D);//コンストラクタ
	~CBlock3D() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CBlock3D* Create();//オブジェクト生成
};
#endif