//=========================================================
//
// block.cppで使う関数[block.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BLOCK_H
#define _BLOCK_H//二重インクルード防止

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う

class CBlock : public CObject2D
{
public:

	static const int BLOCK_SIZE = 50;//サイズ
	static const int STARTLIFE = 100;		 //寿命

	CBlock(int nPriority = CObject::LAYERINDEX_BLOCK);//コンストラクタ
	~CBlock() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Damage(int nDamage);

	//頂点格納
	void InputpVtx()override;

	static CBlock* Create(DATA data);//オブジェクト生成
private:

	int m_nLife = 0;		 //寿命
	int m_nCounterAnim = 0;	 //アニメCounter
	int m_nDirectionMove = 0;//向き//0が右向き1が左
	int m_nPatternAnim = 0;	 //パターン番号
};

#endif