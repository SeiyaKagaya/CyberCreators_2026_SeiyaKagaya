//=========================================================
//
// newbullet.cpp�Ŏg���֐�[newbullet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MISSILE_H

#define _MISSILE_H//��d�C���N���[�h�h�~

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
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

	CMissileALL(int nPriority = CObject::LAYERINDEX_MISSILE_MNG);//�R���X�g���N�^
	~CMissileALL() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	//void Update()override;
	//void Draw()override;
	static CMissileALL* Create();//�I�u�W�F�N�g����

	void ReleaseAllBullet();

	//�o�O����̂��ߓ���
	//static CMissileALL* Create();//�I�u�W�F�N�g����

	//�K�萔������������
	void AllClean();

	CMissile* GetBulletData(int nNum);

	//���łɐ�������Ă�����̂�bUse��true�ɂ��ĉғ�������
	void SetMissile(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, SHOTTYPE ShotType);

	//�ǔ��Ώێ��S������
	void KillMissileTarget(void* pCaller);

private:

	//��Ɋm�ۂ��A��
	CMissile* m_Missile[MAXMISSILEALL];
};


class CMissile : public CObjectX
{
public:
	static const int NEWMAXREFLECTION = 2;//���ˉ�
	const float MISSILEROT = 4.0f;//�~�T�C���̗U���p�x

	const float MISSILEMOVESPEED = 80.0f;//�~�T�C���X�s�[�h

	CMissile(int nPriority = CObject::LAYERINDEX_MISSILE);//�R���X�g���N�^
	~CMissile() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();

	void SetReflect(int nCnt);
	void SetCaller(void* pCaller);
	void SetCOL(D3DXCOLOR col);

	//�o�O����̂��ߓ���
	static CMissile* Create();//�I�u�W�F�N�g����

	void SetbUse(bool bUse);

	bool GetbUse();

	void SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller, CMissileALL::SHOTTYPE ShotType);


	//�ˌ���ւ̓����蔻��}���擾
	int GetHitEscapeTime();

	COBB GetOBB();
	void* GetCaller();


	//���E����ƃo�O���オ�邽�ߔ������B�����Ŏ���ł��炤
	void SetGoodby();

	int GetID();
	void SetID(int nID);

	void* GetpCaller() { return m_pCaller; };
	//�ˌ��^�C�v
	CMissileALL::SHOTTYPE GetShotType() { return m_ShotType; };

	void Homing();

	// �x�N�g���̑傫����ۂ��p�x��ύX����֐�
	void ChangeVectorDirection(D3DXVECTOR3& vector, const D3DXVECTOR3& newDirection, float maxAngleChange);

private:

	bool m_bUse = false;

	int m_nReflect = 0;
	void* m_pCaller = nullptr;//���˂����{�l�̂ݓ����蔻��ɘa���邽�ߕK�v
	D3DXCOLOR m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	COBB m_OBB = {};

	int m_nLife = 0;

	int m_Reflection = 0;

	int m_ShotByHitEscapeTime = 0;

	//�o�O�̉����
	int m_bGoodbyNow = false;

	int m_nID = 0;
	CMissileALL::SHOTTYPE m_ShotType = CMissileALL::SHOTTYPE_MAX;

};






#endif