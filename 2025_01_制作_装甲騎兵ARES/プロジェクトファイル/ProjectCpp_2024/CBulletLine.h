//=========================================================
//
// CBulletLine.cppで使う関数[CBulletLine.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _BULLETLINE_H

#define _BULLETLINE_H//二重インクルード防止

#include "objectX.h"

#include "MathUtilities.h"
#include "player_motion.h"

#include "manager.h"
#include "newbullet.h"

class CBulletLine : public CObjectX
{
public:

	CBulletLine(int nPriority = CObject::LAYERINDEX_BULLETLINE);//コンストラクタ
	~CBulletLine() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();//当たり判定まとめ

	static CBulletLine* Create(DATA SetData, CObjectMotionPlayer* pMotion);//オブジェクト生成

	void SetParent(CObjectMotionPlayer* pMotion) { m_pParent = pMotion; };
	//座標変動
	void SetPos(D3DXVECTOR3 pos) { DATA EscData = GetDATA(); EscData.Pos = pos; SetDATA(EscData); };
	void SetRot(D3DXVECTOR3 rot) { DATA EscData = GetDATA(); EscData.rot = rot; SetDATA(EscData); };

	void setDrawOk(bool set) { m_bDrawOk = set; };
	bool getDrawOk() { return m_bDrawOk; };
	void SetParent(CModelParts* pParentParts) { m_pParentParts = pParentParts; };

private:
	D3DXMATRIX m_mtxWorld;

	LPD3DXMESH m_pMesh; // Meshポインタ
	LPD3DXBUFFER m_pBuffMat; // マテリアルへのポインタ
	DWORD m_dwNumMat; // マテリアルの数
		//テクスチャ読み込み
	LPDIRECT3DTEXTURE9	m_ESCpTexture;

	bool m_bFast;

	//OBBの当たり判定用
	COBB m_OBB = {};

	D3DXCOLOR m_OriginalColor;


	CMathProc::CollisionData m_HitData;//当たり判定データ

	CObjectMotionPlayer* m_pParent;//すべての親のポインタ

	bool m_bDrawOk = false;

	CModelParts* m_pParentParts;//親モデルへのポインタ





//	int m_nLife = 300;
	bool m_bHit = false;

};

#endif






