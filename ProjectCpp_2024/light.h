//=========================================================
//
//ライト関係使う宣言など[light.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _LIGHT_H_

#define _LIGHT_H_//二重インクルード防止

#include"main.h"



class CLight
{
public:
	CLight();
	~CLight();

	static const int LIGHTNUM = 3;//ライトの数

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static int GetlightNum();
	D3DXVECTOR3 GetLightVec(int LightNum);


private:

	D3DLIGHT9 m_aLight[LIGHTNUM];//LIGHT構造体
	D3DXVECTOR3 m_VecDir[LIGHTNUM];
};



#endif
