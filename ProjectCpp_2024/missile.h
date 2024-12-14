//=========================================================
//
// newbullet.cppで使う関数[newbullet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MISSILE_H

#define _MISSILE_H//二重インクルード防止

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
#include "MathUtilities.h"
//


class CMissile;

class CMissileALL : public CObjectX
{
public:
	typedef enum
	{
		SHOTTYPE_PLAYER = 0,
		SHOTTYPE_ENEMY,
		SHOTTYPE_MAX,
	}SHOTTYPE;


	static const int MAXMISSILEALL = 120;

	CMissileALL(int nPriority = CObject::LAYERINDEX_MISSILE_MNG);//コンストラクタ
	~CMissileALL() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	//void Update()override;
	//void Draw()override;
	static CMissileALL* Create();//オブジェクト生成

	void ReleaseAllBullet();

	//バグ回避のため凍結
	//static CMissileALL* Create();//オブジェクト生成

	//規定数を初期化する
	void AllClean();

	CMissile* GetBulletData(int nNum);

	//すでに生成されているもののbUseをtrueにして稼働させる
	void SetMissile(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, SHOTTYPE ShotType);

	//追尾対象死亡時処理
	void KillMissileTarget(void* pCaller);

private:

	//先に確保し、回す
	CMissile* m_Missile[MAXMISSILEALL];
};


class CMissile : public CObjectX
{
public:
	static const int NEWMAXREFLECTION = 2;//反射回数
	const float MISSILEROT = 4.0f;//ミサイルの誘導角度

	const float MISSILEMOVESPEED = 80.0f;//ミサイルスピード

	CMissile(int nPriority = CObject::LAYERINDEX_MISSILE);//コンストラクタ
	~CMissile() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();

	void SetReflect(int nCnt);
	void SetCaller(void* pCaller);
	void SetCOL(D3DXCOLOR col);

	//バグ回避のため凍結
	static CMissile* Create();//オブジェクト生成

	void SetbUse(bool bUse);

	bool GetbUse();

	void SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, CMissileALL::SHOTTYPE ShotType);


	//射撃手への当たり判定抑制取得
	int GetHitEscapeTime();

	COBB GetOBB();
	void* GetCaller();


	//相殺あるとバグ率上がるため避難方式。寿命で死んでもらう
	void SetGoodby();

	int GetID();
	void SetID(int nID);

	void* GetpCaller() { return m_pCaller; };
	//射撃タイプ
	CMissileALL::SHOTTYPE GetShotType() { return m_ShotType; };

	void Homing();

	// ベクトルの大きさを保ちつつ角度を変更する関数
	void ChangeVectorDirection(D3DXVECTOR3& vector, const D3DXVECTOR3& newDirection, float maxAngleChange);

private:

	bool m_bUse = false;

	int m_nReflect = 0;
	void* m_pCaller = nullptr;//発射した本人のみ当たり判定緩和するため必要
	D3DXCOLOR m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	CMathProc::CollisionData m_HitData;//当たり判定データ

	COBB m_OBB = {};

	int m_nLife = 0;

	int m_Reflection = 0;

	int m_ShotByHitEscapeTime = 0;

	//バグの回避策
	int m_bGoodbyNow = false;

	int m_nID = 0;
	CMissileALL::SHOTTYPE m_ShotType = CMissileALL::SHOTTYPE_MAX;

};






#endif