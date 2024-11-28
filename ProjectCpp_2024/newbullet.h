//=========================================================
//
// newbullet.cpp�Ŏg���֐�[newbullet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _NEWBULLET_H

#define _NEWBULLET_H//��d�C���N���[�h�h�~

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "MathUtilities.h"
//

class CNewBullet : public CObjectX
{
public:
	static const int NEWMAXREFLECTION = 2;//���ˉ�

	CNewBullet(int nPriority = CObject::LAYERINDEX_NEWBULLET);//�R���X�g���N�^
	~CNewBullet() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
    void Update()override;
	void Draw()override;


	void HitCollision();

	void SetReflect(int nCnt);
	void SetCaller(void* pCaller);
	void SetCOL(D3DXCOLOR col);

	//�o�O����̂��ߓ���
	static CNewBullet* Create();//�I�u�W�F�N�g����

	void SetbUse(bool bUse);

	bool GetbUse();

	void SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);


	//�ˌ���ւ̓����蔻��}���擾
	int GetHitEscapeTime();

	COBB GetOBB();
	void* GetCaller();


	//���E����ƃo�O���オ�邽�ߔ������B�����Ŏ���ł��炤
	void SetGoodby();

	int GetID();
	void SetID(int nID);

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

};







class CNewBulletALL : public CObjectX
{
public:
	static const int MAXBULLETALL = 120;
	
	CNewBulletALL(int nPriority = CObject::LAYERINDEX_NEWBULLET_MNG);//�R���X�g���N�^
	~CNewBulletALL() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CNewBulletALL* Create();//�I�u�W�F�N�g����

	void ReleaseAllBullet();

	//�o�O����̂��ߓ���
	//static CNewBulletALL* Create();//�I�u�W�F�N�g����

	//�K�萔������������
	void AllClean();

	CNewBullet* GetBulletData(int nNum);

	//���łɐ�������Ă�����̂�bUse��true�ɂ��ĉғ�������
	void SetBullet(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);


private:

	//��Ɋm�ۂ��A��
	CNewBullet* m_NewBullet[MAXBULLETALL];
};

#endif