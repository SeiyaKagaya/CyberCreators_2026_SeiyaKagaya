//=========================================================
//
// ballet.cppで使う関数[ballet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BULLET_H
#define _BULLET_H//二重インクルード防止

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う

class CBullet : public CObject2D
{
public:

	static const int BULLET_SIZE = 10;	//サイズ

	const int START_LIFE = 120;			//寿命
	const int START_SPEED = 10;			//速度

	CBullet(int nPriority=CObject::LAYERINDEX_BULLET);//コンストラクタ
	~CBullet() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void HitCollision();//当たり判定まとめ
	//頂点格納
	void InputpVtx()override;
	static CBullet* Create(DATA data);//オブジェクト生成
private:
	int m_nLife = 0;		//寿命
	float m_speed = 0.0f;	//速度
};

#endif