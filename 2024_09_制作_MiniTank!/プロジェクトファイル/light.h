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

	static const int LIGHTNUM = 3;//ライトの数
	const D3DXVECTOR3 LIGHT_POS[LIGHTNUM] =
	{
		D3DXVECTOR3(0.2f,-0.8f,0.4f),
		D3DXVECTOR3(0.4f,0.8f,0.4f),
		D3DXVECTOR3(-0.2f,-0.8f,-0.4f),
	};

	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static int GetlightNum();				//ライトの数取得
	D3DXVECTOR3 GetLightVec(int LightNum);  //ライトのベクトルを取得
private:

	D3DLIGHT9 m_aLight[LIGHTNUM] = {};		//LIGHT構造体
	D3DXVECTOR3 m_VecDir[LIGHTNUM] = {};	//ベクトル
};

#endif
