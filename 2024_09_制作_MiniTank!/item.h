//=========================================================
//
// item.cppで使う関数[item.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ITEM_H
#define _ITEM_H//二重インクルード防止

#include "object.h"
#include "object2D.h"
#include <Windows.h>
#include "d3dx9.h"//描写処理に使う

class CItem : public CObject2D
{
public:

	static const int ITEM_SIZE = 20;//サイズ

	CItem(int nPriority = CObject::LAYERINDEX_ITEM);//コンストラクタ
	~CItem() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//頂点格納
	void InputpVtx()override;

	static CItem* Create(DATA data);//オブジェクト生成
};
#endif