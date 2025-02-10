//=========================================================
//
// polygon.cppで使う関数[polygon.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _POLYGON_H
#define _POLYGON_H//二重インクルード防止

#include "object.h"
#include "object2D.h"
#include <Windows.h>
#include "d3dx9.h"//描写処理に使う

class CPolygon : public CObject2D
{
public:
	static const int POLYGON_SIZE = 100;//サイズ

	CPolygon(int nPriority=CObject::LAYERINDEX_POLYGON);//コンストラクタ
	~CPolygon() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CPolygon* Create();//オブジェクト生成
private:

	int m_nCounterAnim = 0;		//アニメCounter
	int m_nDirectionMove = 0;	//向き//0が右向き1が左
	int m_nPatternAnim = 0;		//パターン番号
};

#endif