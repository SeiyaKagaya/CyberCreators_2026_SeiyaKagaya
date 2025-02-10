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


//�o���b�g
class CNewBullet : public CObjectX
{
public:
	static const int NEWMAXREFLECTION = 2;				//���ˉ�
	static const int HIT_COL_ESCAPE_TIME = 30;			//�����蔻�薳��������
	static const int LIFE = 200;						//����
	const float ObbLength[3] = { 15.0f,15.0f,30.0f };	//Obb�̒���
	const float SIZE = 30.0f;							//�T�C�Y
	const float SIZEMAG = 5.5f;							//�T�C�Y�{��

	CNewBullet(int nPriority = CObject::LAYERINDEX_NEWBULLET);//�R���X�g���N�^
	~CNewBullet() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
    void Update()override;
	void Draw()override;

	void HitCollision();			//�����蔻��

	void SetCaller(void* pCaller);	//�e�i�[

	void SetCOL(D3DXCOLOR col);		//�F�i�[

	static CNewBullet* Create();	//�I�u�W�F�N�g����

	void SetbUse(bool bUse);		//�g�p��Ԃ��i�[

	bool GetbUse();					//�g�p��Ԃ��擾

	void SetBulletData(DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);//�o���b�g���Z�b�g
	
	int GetHitEscapeTime();			//�ˌ���ւ̓����蔻��}���擾

	COBB GetOBB();					//obb�擾

	void* GetCaller();				//�e�擾

	void SetGoodby();				//���E����ƃo�O���オ�邽�ߔ������B�����Ŏ���ł��炤

	//�z��ԍ��i�[
	int GetID();
	void SetID(int nID);

private:
	
	bool m_bUse = false;									//�g�p��Ԃ�
	void* m_pCaller = nullptr;								//�e	(���˂����{�l�̂ݓ����蔻��ɘa���邽�ߕK�v)
	D3DXCOLOR m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�J���[
	CMathProc::CollisionData m_HitData;						//�����蔻��f�[�^
	COBB m_OBB = {};

	int m_nLife = 0;				//����
	int m_Reflection = 0;			//���ˉ�
	int m_ShotByHitEscapeTime = 0;	//�����蔻�薳��������
	int m_bGoodbyNow = false;		//bUse�Ɠ�������/�����I�o�O�h�~
	int m_nID = 0;					//�z��ԍ�
};






//�o���b�g�Ǘ�
class CNewBulletALL
{
public:
	static const int MAXBULLETALL = 120;//�ő吔
	
	CNewBulletALL();//�R���X�g���N�^
	~CNewBulletALL();//�f�X�g���N�^
	HRESULT Init();
	void Uninit();

	void ReleaseAllBullet();///���g��Release

	static CNewBulletALL* Create();//�I�u�W�F�N�g����


	void AllClean();//���ׂĂ�bUse��false��

	static CNewBullet* GetBulletData(int nNum);//����̔z��ԍ��̒e�����擾

	//���łɐ�������Ă��镨��bUse��true�ɂ��ĉғ�������
	static void SetBullet(CObject::DATA SetData, int ReflectCnt, D3DXCOLOR col, void* pCaller);

private:

	//�ÓI�����o�ϐ�
	static CNewBullet* m_NewBullet[MAXBULLETALL];
};

#endif