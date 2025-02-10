//=========================================================
//
// object_motion.cpp�Ŏg���֐�[object_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECTMOTION_H
#define _OBJECTMOTION_H//��d�C���N���[�h�h�~

#include "object.h"
#include "objectX.h"
#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include "MathUtilities.h"
#include <vector>
#include "ModelParts.h"

class CObjectMotion : public CObjectX
{
public:

	const float  BULLET_SHOT_POS_Y = 45.0f;//ballet�̍���Y
	const  float DAMPING_RATIO = 0.5f;	   //������
	static const int MAX_PARTS = 15;	   //�ő�parts��
	static const int MAX_WORD = 1000;	   //�ő啶����
	static const int MAXKEY = 60;		   //�ő�L�[��
	static const int MAX_MOTION = 5;	   //�ő僂�[�V������
	static const int MAX_TEXTURE = 10;	   //�ő�e�N�X�`����
	static const int BRENDFLAME = 2;	   //���[�V�����u�����h���̃t���[����


	//------------------------------------------------------------------------------------------------------------------------------
	typedef struct
	{
		//�����܂ŁAOFFSET���猩���␳�l
		D3DXVECTOR3 CorrectionPos;	//�ʒu�␳��
		D3DXVECTOR3 CorrectionRot;	//�����␳��
	}PARTSDATA;//PARTS���Ƃ̕␳�f�[�^

	typedef struct
	{
		int nSplitFrame;				//�����t���[����
		PARTSDATA PartsData[MAX_PARTS];	//���[�V�����̒��ł̃p�[�c�f�[�^����

	}KEYDATA;//�L�[�P��-----------Key���ŕϓ�

	typedef struct
	{
		int Motiontype;			//MOTION�̎��//int�^�Ŏd�l
		int nLoop;				//���[�v���邩[0:���[�v���Ȃ�1:���[�v����]
		int nNumKey;			//���[�V�����̃L�[�̐�
		KEYDATA KeyData[MAXKEY];//�L�[�P��

	}MOTION;//���[�V�����̃f�[�^--���[�V�����̐�����

	typedef struct
	{
		//���[�V�����̈ʒu�v�Z�ɉ^�p�A�Ō��MODEL��DrawPosS�ɓ����
		D3DXVECTOR3 Pos;						//�ʒu
		D3DXVECTOR3 Rot;						//����
		int INDEX;								//�����̔ԍ�
		int PEARENT;							//�����̐e

		D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X

		//�͂��߂�T�|�[�Y
		D3DXVECTOR3 StartPos;					//���߂̈ʒu
		D3DXVECTOR3 StartRot;					//���߂̊p�x


		D3DXVECTOR3 CorrectCorrectionPosMove;	//���[�V�����ł̈ړ���pos
		D3DXVECTOR3 CorrectCorrectionRotMove;	//���[�V�����ł̈ړ���move
		bool calculationExecution;				//�␳�l�v�Z������bool
	
	}MODELPARTS;//���݂̃p�[�c�̃f�[�^

	typedef struct
	{
		int nMaxMotionCnt;						//�ő僂�[�V������
		int nMaxPartsCnt;						//�ő�p�[�c��
		int nMaxLoadPartsCnt;					//�ǂݍ��ލő�p�[�c��
		MOTION Motion[MAX_MOTION];				//�ܑヂ�[�V�����Ȃ�

	}MODEL;//���f��(�Ƃ�������)

	//------------------------------------------------------------------------------------------------------------------------------

	CObjectMotion(int nPriority = CObject::LAYERINDEX_MOTIONMODEL);//�R���X�g���N�^
	~CObjectMotion() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotion* Create(const char* pfilePass,DATA SetData);//�I�u�W�F�N�g����


	 void DataLoad();												//motion.txt�ǂݍ��݂ƃN���G�C�g���s��

	void SetFilePass(const char* FilePass);							//�t�@�C���p�X�i�[

	void Motion_Parent();											//motion�{��
	void Motion_Sub();												//�T�umotion

	void SetNowMotion_Parent(int nMotionNum);						//���[�V�����Z�b�g
	void SetNowMotion_Sub(int nMotionNum);


	void SetClassData(DATA data);									//�W���̂ƌ��Ă�DATA
	DATA GetClassData();											//�W���̂Ƃ��Ă�DATA�擾

	D3DXMATRIX GetMatrix();											//�}�g���b�N�X�擾
	void SetMatrix(D3DXMATRIX mtx);									//�}�g���b�N�X�i�[

	void SetChangeDataInObjectMotion(DATA ChangeData);				//�ύX�f�[�^�����̃N���X����ăp�[�c�ɂ킽��
	
	CModelParts* GetModelParts(int index);							//�p�[�c�擾
	
	int GetMaxLoadPartsNum();										//�p�[�c���擾

	int GetChangeDataPartsIndex();									//�f�[�^�ύX�����郂�f���ԍ��擾(����͖C��)

	void SetOBBLength(float fLength[3]);							//OBB�̑傫������

	COBB GetOBB();													//OBB�擾

	int GetNowGRIDNum();											//GRID�ԍ��擾

	void HitCollisionToStageBlock();								//���@�����Q���Ȃǂւ̓����蔻��(player/enemy����)

	D3DXVECTOR3 GetNowMove();										//���̂Ƃ���move�l�擾

private:

	CMathProc::CollisionData m_HitData = {};						//�����蔻��f�[�^

	MODEL m_Model = {};												//���f���ƌ�������

	const char* m_PartfilePass[MAX_PARTS] = {};						//�emodel���Ƃ�pass

	LPD3DXMESH m_pMesh[MAX_PARTS] = {};								//Mesh�|�C���^
	LPD3DXBUFFER m_pBuffMat[MAX_PARTS] = {};						//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat[MAX_PARTS] = {};								//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_PARTS][MAX_TEXTURE] = {};		//�e�N�X�`��

	DATA m_CrassData = {};											//��̂Ƃ��Ẵf�[�^

	const char* m_FilePass=nullptr;									//motion�̃p�X

	D3DXMATRIX m_mtxWorld = {};									    //�}�g���b�N�X�i�[

	//motion�ŕK�v�V���[�Y-------------------------------
	int m_oldMotionIndex_Parent=0;		//�O���motion
	int m_NowMotionIndex_Parent=0;		//����motion
	int m_NowKeyCnt_Parent=0;			//���݂�motion�̃L�[Cnt
	int m_NowFrameCnt_Parent=0;			//���݂�motion�̃t���[��Cnt
	int m_EscapeMotion_Parent=0;		//motion�̑ޔ�p
	int m_BrendCnt_Parent=0;			//motion�u�����h�pCnt
	bool m_MotionLoopStop_Parent=false;	//motion���[�v���~�߂邩bool
	bool m_MotionBrend_Parent=false;	//motion�u�����h�����邩bool
	//----------------------------------------------------

	//motion�ŕK�v�V���[�Y------------------------------------------�T�u
	int m_oldMotionIndex_Sub=0;			//�O���motion
	int m_NowMotionIndex_Sub=0;			//����motion
	int m_NowKeyCnt_Sub=0;				//���݂�motion�̃L�[Cnt
	int m_NowFrameCnt_Sub=0;			//���݂�motion�̃t���[��Cnt
	int m_EscapeMotion_Sub=0;			//motion�̑ޔ�p
	int m_BrendCnt_Sub=0;				//motion�u�����h�pCnt
	bool m_MotionLoopStop_Sub=false;	//motion���[�v���~�߂邩bool
	bool m_MotionBrend_Sub=false;		//motion�u�����h�����邩bool
	//---------------------------------------------------------------

	CModelParts* m_pModelParts[MAX_PARTS] = {};	//�p�[�c
	int m_ChangeDataModelIndex=0;				//�f�[�^�ύX�̂��郂�f���̃C���f�b�N�X

	COBB m_Obb = {};							//OBB�̓����蔻��p

	int m_NowGridNum=0;							//���݂̎����̂���GRID�̔ԍ�
	int m_RunCnt = 0;							//���s�J�E���^
};

#endif