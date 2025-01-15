//=========================================================
//
// StageCollisionBox.cppで使う関数[StageCollisionBox.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _STAGECOLLISIONBOXSET_H

#define _STAGECOLLISIONBOXSET_H//二重インクルード防止

//#include "object.h"
#include "objectX.h"

//#include <Windows.h>
//#include "d3dx9.h"//描写処理に使う
#include "MathUtilities.h"
//#include <vector>
//#include "enemy_motion_base.h"

class StageCollisionBox : public CObjectX
{
public:

	StageCollisionBox(int nPriority = CObject::LAYERINDEX_HITBOX);//コンストラクタ
	~StageCollisionBox() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();//当たり判定まとめ



	static StageCollisionBox* Create(DATA SetData);//オブジェクト生成

	static void Resize(int count);//配列のサイズ変更

private:

	CMathProc::CollisionData m_HitData;//当たり判定データ
//	D3DXVECTOR3 m_SizeMag;
	
};

#endif