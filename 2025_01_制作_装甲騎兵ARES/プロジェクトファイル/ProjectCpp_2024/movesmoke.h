////=========================================================
////
//// movesmokeで使う関数[movesmoke.h]
//// Author seiya kagaya
////
////=========================================================
//#ifndef _MOVESMOKE_H
//#define _MOVESMOKE_H//二重インクルード防止
//
//#include "Object_billboard.h"
//#include "d3dx9.h"//描写処理に使う
//#include "main.h"
//
//class CMoveSmoke : public CObjectBillBoard
//{
//public:
//
//	static const int EX_WIDE = 150;
//	static const int EX_HEIGHT = 150;
//
//	const int START_LIFE = 120;
//	const int DIVISION_NUMBER = 8;	//テクスチャ分割数
//
//	static const int  PRINTSIZE_X = 120;
//	static const int  PRINTSIZE_Z = 120;
//
//
//	CMoveSmoke(int nPriority = CObject::LAYERINDEX_ReflectEffect);//コンストラクタ
//	~CMoveSmoke() override;//デストラクタ
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//
//	static CMoveSmoke* Create(D3DXVECTOR3 Pos);//object生成
//
//	void SetPos_Rot(D3DXVECTOR3 Pos);
//
//	//頂点格納
//	void InputpVtx()override;
//
//
//private:
//
//	int m_nLife;//寿命で消す
//
//	int m_nPatternAnim;//分割
//
//	int m_nDelay;
//
//	D3DXCOLOR m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//	int m_nACnt = 100;
//};
//
//#endif