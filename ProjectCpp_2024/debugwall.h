//=========================================================
//
// tankfootprintで使う関数[tankfootprint.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _DEBUGWALL_H

#define _DEBUGWALL_H//二重インクルード防止

#include "object3D.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

//

class CDebugwall : public CObject3D
{
public:

	static const int  PRINTSIZE = 3300/2;
//	static const int  SETPOS

	CDebugwall(int nPriority = CObject::LAYERINDEX_DEBUGWALL);//コンストラクタ
	~CDebugwall() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CDebugwall* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);//object生成

	void SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot);

	//頂点格納
	void InputpVtx()override;


private:

	
};

#endif