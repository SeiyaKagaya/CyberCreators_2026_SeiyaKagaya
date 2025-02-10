//=========================================================
//
// ballet.cppで使う関数[ballet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _ENEMY_H
#define _ENEMY_H//二重インクルード防止

#include "object.h"
#include "object2D.h"
#include <Windows.h>
#include "d3dx9.h"//描写処理に使う

class CEnemy : public CObject2D
{
public:
	static const int ENEMY_SIZE = 40;	//サイズ
	static const int START_LIFE = 120;			//寿命
	
	CEnemy(int nPriority=CObject::LAYERINDEX_ENEMY);//コンストラクタ
	~CEnemy() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	//頂点格納
	void InputpVtx()override;
	static CEnemy* Create(DATA data);//オブジェクト生成
private:
	int m_nLife = 0;//寿命
};

#endif