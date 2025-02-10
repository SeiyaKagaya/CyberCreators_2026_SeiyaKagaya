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

class CModelParts : public CObjectX
{
public:
	CModelParts(int nPriority = CObject::LAYERINDEX_MODELPARTS);//�R���X�g���N�^
	~CModelParts() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CModelParts* Create(const char* FilePass);		//�I�u�W�F�N�g����

	void SetFilePass(const char* FilePass);					//�t�@�C���p�X�i�[
	void SetParent(CModelParts* pParentParts);				//�e�i�[

	void SetOffSetData(DATA offSetData);					//Offset�ʒu�i�[
	DATA GetOffSetData();									//Offset�ʒu�擾

	D3DXMATRIX GetMtxWorld();								//�}�g���b�N�X�擾
	CModelParts* GetParent();								//�e�擾

	void SetNowData(DATA data);								//���s�f�[�^�i�[
	DATA GetNowData();										//�f�[�^�擾

	//�v�Z����擾
	D3DXVECTOR3 GetCorrectCorrectionPosMove();				//POS�␳�l�擾
	D3DXVECTOR3 GetCorrectCorrectionRotMove();				//ROT�␳�l�擾

	bool GetcalculationExecution();							//�v�Z�ς݂�

	void SetCorrectCorrectionPosMove(D3DXVECTOR3 pos);		//POS�␳�l�i�[
	void SetCorrectCorrectionRotMove(D3DXVECTOR3 Rot);		//ROT�␳�l�i�[

	void SetcalculationExecution(bool calculationExecution);//�v�Z�ς݂�

	//����
	void UpdatePosMotion();
	void UpdateRotMotion();

	void SetMotionPoint(CObjectMotion* Motion);				//���[�V�����i�[

	D3DXMATRIX GetPartsMtx();								//�}�g���b�N�X�擾
	void SetPartsMtx(D3DXMATRIX mtxWorld);					//�}�g���b�N�X�i�[

	void m_DataChangeModel(bool changebool);				//�f�[�^�ύX���f��bool
	
	void ChangeDataSet(DATA data);							//�ύX�f�[�^�i�[
	
	//���[�V���������Z�b�g
	void SetMotion_Parent(int Check);						//1��Parent�@0��Sub

	//���[�V���������擾
	int GetMotion_Parent();									//1��Parent�@0��Sub

	void DrawOkBool(bool Draw);								//�`�悵�ėǂ���

	void ChengeRGBAbool(bool chenge, D3DXCOLOR col );		//�F�ύX�����邩

private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_XFILE] = {};	//�e�N�X�`��
	
	//�����ł�DATA���ŏI�I�ȕ`��ȂǂɎg�p�B
	//���n�p(�e�}�g���b�N�X�Ƃ̗Z���Ȃ�)�͕ʂ̕ϐ��ɓ����
	D3DXMATRIX m_mtxWorld = {};

	DATA m_offSetData = CObject::DataInit();	//Offset�ʒu
	DATA m_NowData = CObject::DataInit();		//���݂̈ʒu
	DATA m_ChangeDATA = CObject::DataInit();	//�ύX��

	CModelParts* m_pParentParts = nullptr;		//�e���f���ւ̃|�C���^
	const char* m_PartfilePass = nullptr;		//�emodel���Ƃ�pass
	D3DXVECTOR3 m_CorrectCorrectionPosMove = {};//���[�V�����ł̈ړ���pos
	D3DXVECTOR3 m_CorrectCorrectionRotMove = {};//���[�V�����ł̈ړ���move
	CObjectMotion* pMotion = nullptr;			//���ׂĂ̐e�̃|�C���^
	bool m_calculationExecution = false;		//�␳�l�v�Z������bool
	bool m_ChangeDatabool = false;				//�f�[�^�ύX�����郂�f����
	bool m_bChengeCol = false;					//�J���[�`�F���W���ǂ���
	bool m_bDrawBool = true;					//�`���Ԃ�
	int m_MotionParent = 0;						//motion��parent�����A1�ł����Ȃ�
	D3DXCOLOR m_ChengeCol = {};					//�`�F���W���̃J���[
};

#endif