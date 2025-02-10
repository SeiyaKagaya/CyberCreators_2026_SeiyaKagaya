//=========================================================
//
// player3D.cppで使う関数[player3D.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER3D_H
#define _PLAYER3D_H//二重インクルード防止

#include "object.h"
#include "objectX.h"
#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
#include "MathUtilities.h"

class CPlayer3D : public CObjectX
{
public:	
	const  float DAMPING_RATIO = 0.5f;
	
	CPlayer3D(int nPriority = CObject::LAYERINDEX_PLAYER3D);//コンストラクタ
	~CPlayer3D() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void Action_Keyboard();//操作受付Keyboard
	void Action_JoyPad();//操作受付ジョイパッド
	void HitCollision();//当たり判定まとめ

	CObject::DATA GetPlayerData();//データ取得(player情報はよく使用するため)

	static CPlayer3D* Create();//オブジェクト生成
private:
	CMathProc::CollisionData m_HitData;//当たり判定データ
};

#endif