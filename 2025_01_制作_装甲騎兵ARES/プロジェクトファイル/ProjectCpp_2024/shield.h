//=========================================================
//
// CShield.cpp�Ŏg���֐�[CShield.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SHIELD_H

#define _SHIELD_H//��d�C���N���[�h�h�~

#include "objectX.h"

#include "MathUtilities.h"
#include "player_motion.h"

#include "manager.h"
#include "newbullet.h"

class CShield : public CObjectX
{
public:

	CShield(int nPriority = CObject::LAYERINDEX_SHIELD);//�R���X�g���N�^
	~CShield() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	void HitCollision();//�����蔻��܂Ƃ�

	static CShield* Create(DATA SetData, CObjectMotionPlayer* pMotion);//�I�u�W�F�N�g����

	void SetParent(CObjectMotionPlayer* pMotion) { m_pParent = pMotion; };
	//���W�ϓ�
	void SetPos(D3DXVECTOR3 pos) { DATA EscData = GetDATA(); EscData.Pos = pos; SetDATA(EscData); };
	void SetRot(D3DXVECTOR3 rot) { DATA EscData = GetDATA(); EscData.rot = rot; SetDATA(EscData); };

	void setDrawOk(bool set) { m_bDrawOk = set; };
	bool getDrawOk() { return m_bDrawOk; };
	void SetParent(CModelParts* pParentParts) { m_pParentParts = pParentParts; };

private:
	D3DXMATRIX m_mtxWorld;

	LPD3DXMESH m_pMesh[2]; // Mesh�|�C���^
	LPD3DXBUFFER m_pBuffMat[2]; // �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat[2]; // �}�e���A���̐�
		//�e�N�X�`���ǂݍ���
	LPDIRECT3DTEXTURE9	m_ESCpTexture[2];

	bool m_bFast[2];
	D3DXCOLOR m_OriginalColor[2];


	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	CObjectMotionPlayer* m_pParent;//���ׂĂ̐e�̃|�C���^

	bool m_bDrawOk = false;

	CModelParts* m_pParentParts;//�e���f���ւ̃|�C���^


		//OBB�̓����蔻��p
	COBB m_Obb;

	int m_nLife = 300;


};

#endif






