//=========================================================
//
// ModelParts.cpp�Ŏg���֐�[ModelParts.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MODELPARTS_H

#define _MODELPARTS_H//��d�C���N���[�h�h�~

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��

class CObjectMotion;//�O���錾

//
class CModelParts : public CObjectX
{
public:



	CModelParts(int nPriority = CObject::LAYERINDEX_MODELPARTS);//�R���X�g���N�^
	~CModelParts() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CModelParts* Create(const char* FilePass);//�I�u�W�F�N�g����

	void SetFilePass(const char* FilePass);//�t�@�C���p�X�i�[
	void SetParent(CModelParts* pParentParts);

	void SetOffSetData(DATA offSetData);//Offset�ʒu�i�[
	DATA GetOffSetData();//Offset�ʒu�擾

	D3DXMATRIX GetMtxWorld();//�}�g���b�N�X�擾

	CModelParts* GetParent();//�e�擾

	void SetNowData(DATA data);//���s�f�[�^
	DATA GetNowData();

	//�v�Z����擾
	D3DXVECTOR3 GetCorrectCorrectionPosMove();//�␳�l
	D3DXVECTOR3 GetCorrectCorrectionRotMove();
	bool GetcalculationExecution();			  //�v�Z�ς݂�

	void SetCorrectCorrectionPosMove(D3DXVECTOR3 pos);		//�␳�l
	void SetCorrectCorrectionRotMove(D3DXVECTOR3 Rot);
	void SetcalculationExecution(bool calculationExecution);//�v�Z�ς݂�

	//����
	void UpdatePosMotion();
	void UpdateRotMotion();

	void SetMotionPoint(CObjectMotion* Motion);

	D3DXMATRIX GetPartsMtx();
	void SetPartsMtx(D3DXMATRIX mtxWorld);


	//�f�[�^�ύX���f��bool
	void m_DataChangeModel(bool changebool);
	
	//�ύX�f�[�^�i�[
	void ChangeDataSet(DATA data);
	
	//���[�V���������Z�b�g
	void SetMotion_Parent(int Check);//1��Parent�@0��Sub

	//���[�V���������擾
	int GetMotion_Parent();//1��Parent�@0��Sub

	void DrawOkBool(bool Draw);

	void ChengeRGBAbool(bool chenge, D3DXCOLOR col );

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE];//�e�N�X�`��


	//LPD3DXMESH m_pMesh;//Mesh�|�C���^
	//LPD3DXBUFFER m_pBuffMat;//�}�e���A���ւ̃|�C���^
	//DWORD m_dwNumMat;//�}�e���A���̐�

	//�����ł�DATA���ŏI�I�ȕ`��ȂǂɎg�p�B
	//���n�p(�e�}�g���b�N�X�Ƃ̗Z���Ȃ�)�͕ʂ̕ϐ��ɓ����
	D3DXMATRIX m_mtxWorld;

	DATA m_offSetData;//Offset�ʒu
	DATA m_NowData;

	DATA m_ChangeDATA;

//	int INDEX;//�����̔ԍ�
// 
//		int PEARENT;		//�����̐e�ԍ�
	CModelParts* m_pParentParts;//�e���f���ւ̃|�C���^

	const char* m_PartfilePass;					//�emodel���Ƃ�pass

	D3DXVECTOR3 m_CorrectCorrectionPosMove;//���[�V�����ł̈ړ���pos
	D3DXVECTOR3 m_CorrectCorrectionRotMove;//���[�V�����ł̈ړ���move
	bool m_calculationExecution;//�␳�l�v�Z������bool

	CObjectMotion* pMotion;//���ׂĂ̐e�̃|�C���^

	bool m_ChangeDatabool;//�f�[�^�ύX�����郂�f����
	int m_MotionParent;//motion��parent�����A1�ł����Ȃ�

	bool m_bDrawBool = true;

	D3DXCOLOR m_ChengeCol;
	bool m_bChengeCol = false;
};

#endif