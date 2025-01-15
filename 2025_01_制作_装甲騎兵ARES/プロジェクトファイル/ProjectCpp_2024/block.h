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
//
class CBlock : public CObject2D
{
public:

	static const int BLOCK_WIDE = 50;
	static const int BLOCK_HEIGHT = 50;
	const int STARTLIFE = 100;

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

	int m_nLife;
	int m_nCounterAnim;//アニメCounter
	int m_nDirectionMove;//向き//0が右向き1が左
	int m_nPatternAnim;//パターン番号

};

#endif