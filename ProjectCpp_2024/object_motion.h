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

	typedef enum
	{
		MOTIONTYPE_STANDBY = 0,
		MOTIONTYPE_MOVE_FRONT,
		MOTIONTYPE_MOVE_BACK,
		MOTIONTYPE_HIGH_MOVE_FRONT,
		MOTIONTYPE_HIGH_MOVE_BACK,
		MOTIONTYPE_HIGH_MOVE_LEFT,
		MOTIONTYPE_HIGH_MOVE_RIGHT,
		MOTIONTYPE_ATTACK,
		MOTIONTYPE_GUARD,
		MOTIONTYPE_JUMP,
		MOTIONTYPE_RANDING,
		MOTIONTYPE_BREND,
		MOTIONTYPE_MAX,
	}MOTIONTYPE;

	// �萔
	const int GROUND_COUNTER_THRESHOLD = 10; // �ڒn��Ԃ��ێ����邽�߂̃J�E���g臒l


	 const float  BULLET_SHOT_POS_Y = 45.0f;//ballet�̍���Y

	const  float DAMPING_RATIO_LOAD_XZ = 0.3f;
	const  float DAMPING_RATIO_Y = 0.095f;


	static const int MAX_PARTS = 30;//�ő�parts��
	static const int MAX_WORD = 1000;
	static const int MAXKEY = 60;
	static const int MAX_MOTION = MOTIONTYPE_MAX;
	static const int MAX_TEXTURE = 10;
	static const int BRENDFLAME = 2;

	//------------------------------------------------------------------------
	typedef struct
	{
		//�����܂ŁAOFFSET���猩���␳�l
		D3DXVECTOR3 CorrectionPos;	//�ʒu�␳��
		D3DXVECTOR3 CorrectionRot;	//�����␳��
	}PARTSDATA;//PARTS���Ƃ̕␳�f�[�^

	typedef struct
	{
		int nSplitFrame;//�����t���[����

		PARTSDATA PartsData[MAX_PARTS];//���[�V�����̒��ł̃p�[�c�f�[�^����

	}KEYDATA;//�L�[�P��-----------Key���ŕϓ�

	typedef struct
	{
		int Motiontype;//MOTION�̎��//int�^�Ŏd�l
		int nLoop;//���[�v���邩[0:���[�v���Ȃ�1:���[�v����]
		int nNumKey;//���[�V�����̃L�[�̐�

		KEYDATA KeyData[MAXKEY];
	}MOTION;//���[�V�����̃f�[�^--���[�V�����̐�����

	typedef struct
	{
		//���[�V�����̈ʒu�v�Z�ɉ^�p�A�Ō��MODEL��DrawPosS�ɓ����
		D3DXVECTOR3 Pos;	//�ʒu
		D3DXVECTOR3 Rot;	//����
		int INDEX;//�����̔ԍ�
		int PEARENT;		//�����̐e

		D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X

		//�͂��߂�T�|�[�Y
		D3DXVECTOR3 StartPos;
		D3DXVECTOR3 StartRot;


		D3DXVECTOR3 CorrectCorrectionPosMove;//���[�V�����ł̈ړ���pos
		D3DXVECTOR3 CorrectCorrectionRotMove;//���[�V�����ł̈ړ���move
		bool calculationExecution;//�␳�l�v�Z������bool
	
	}MODELPARTS;//���݂̃p�[�c�̃f�[�^

	typedef struct
	{
		int nMaxMotionCnt;//�ő僂�[�V������

		int nMaxPartsCnt;//�ő�p�[�c��
		int nMaxLoadPartsCnt;//�ǂݍ��ލő�p�[�c��

	//	MODELPARTS ModelParts[MAX_PARTS];//�^�p���錻�݂�Parts--X
		MOTION Motion[MAX_MOTION];//�ܑヂ�[�V�����Ȃ�

	}MODEL;//���f��(�Ƃ�������)
	//---------------------------------------------------------------------------

	CObjectMotion(int nPriority = CObject::LAYERINDEX_MOTIONMODEL);//�R���X�g���N�^
	~CObjectMotion() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotion* Create(const char* pfilePass,DATA SetData);//�I�u�W�F�N�g����


	 void DataLoad();//motion.txt�ǂݍ��݂ƃN���G�C�g���s��

	void SetFilePass(const char* FilePass);//�t�@�C���p�X�i�[


	//motion1�n
	void Motion_Parent();//motion�{��
	void Motion_Sub();//�T�umotion

	void SetNowMotion_Parent(MOTIONTYPE nMotionNum);
	void SetNowMotion_Sub(MOTIONTYPE nMotionNum);
	
	//motion
	MOTIONTYPE GetNowMotionParent() { return m_NowMotionIndex_Parent;};
	MOTIONTYPE GetNowMotionSub() { return m_NowMotionIndex_Sub; };
	



	void SetClassData(DATA data);//�W���̂ƌ��Ă�DATA
	DATA GetClassData();//�W���̂Ƃ��Ă�DATA�擾


	D3DXMATRIX GetMatrix();
	void SetMatrix(D3DXMATRIX mtx);

	//�ύX�f�[�^�����̃N���X����ăp�[�c�ɂ킽��
	void SetChangeDataInObjectMotion(DATA ChangeData);
	
	//�p�[�c�擾
	CModelParts* GetModelParts(int index);
	//�p�[�c���擾
	int GetMaxLoadPartsNum();

	//�f�[�^�ύX�����郂�f���ԍ��擾(����͖C��)
	int GetChangeDataPartsIndex();

	//OBB�̑傫������
	void SetOBBLength(float fLength[3]);

	//OBB�擾
	COBB GetOBB();

	//GRID�ԍ��擾
	int GetNowGRIDNum();

	//���@�����Q���Ȃǂւ̓����蔻��(player/enemy����)
	void HitCollisionToStageBlock();

	//���̂Ƃ���move�l�擾
	D3DXVECTOR3 GetNowMove();

	//���n��Ԃ�
	void SetIsOnGroundBool(bool bSet);
	bool GetIsOnGroundBool();// { return m_isOnGround; };

	////�󒆏�Ԃ�
	//void SetIsInAirBool(bool bSet);
	//bool GetIsInAirBool();// { return m_isInAir; };

	//���nmotion������������
	void SetIsLandingTriggerBool(bool bSet);
	bool GetIsLandingTriggerBool();// { return m_isLandingTriggered; };

	//���nmotion������������
	void SetOldPosY(float OldPosY);
	float GetOldPosY();




	int GetGroundFrame();
	void SetGroundFrame(int cnt);

private:

	CMathProc::CollisionData m_HitData;//�����蔻��f�[�^

	MODEL m_Model;//���f���ƌ�������

	const char* m_PartfilePass[MAX_PARTS];					//�emodel���Ƃ�pass

	 LPD3DXMESH m_pMesh[MAX_PARTS];							//Mesh�|�C���^
	 LPD3DXBUFFER m_pBuffMat[MAX_PARTS*3];					//�}�e���A���ւ̃|�C���^
	 DWORD m_dwNumMat[MAX_PARTS*3];							//�}�e���A���̐�
	 LPDIRECT3DTEXTURE9 m_pTexture[MAX_PARTS][MAX_TEXTURE];//�e�N�X�`��

	 DATA m_CrassData;		//��̂Ƃ��Ẵf�[�^

	const char* m_FilePass;	//motion�̃p�X

	D3DXMATRIX m_mtxWorld;	//�}�g���b�N�X�i�[


	//motion�ŕK�v�V���[�Y-------------------------------
	MOTIONTYPE m_oldMotionIndex_Parent;	//�O���motion
	MOTIONTYPE m_NowMotionIndex_Parent;	//����motion
	int m_NowKeyCnt_Parent;	//���݂�motion�̃L�[Cnt
	int m_NowFrameCnt_Parent;	//���݂�motion�̃t���[��Cnt
	int m_EscapeMotion_Parent;		//motion�̑ޔ�p
	int m_BrendCnt_Parent;			//motion�u�����h�pCnt
	bool m_MotionLoopStop_Parent;	//motion���[�v���~�߂邩bool
	bool m_MotionBrend_Parent;		//motion�u�����h�����邩bool
	//----------------------------------------------------

	//motion�ŕK�v�V���[�Y------------------------------------------�T�u
	MOTIONTYPE m_oldMotionIndex_Sub;	//�O���motion
	MOTIONTYPE m_NowMotionIndex_Sub;	//����motion

	int m_NowKeyCnt_Sub;	//���݂�motion�̃L�[Cnt
	int m_NowFrameCnt_Sub;	//���݂�motion�̃t���[��Cnt
	int m_EscapeMotion_Sub;		//motion�̑ޔ�p
	int m_BrendCnt_Sub;			//motion�u�����h�pCnt
	bool m_MotionLoopStop_Sub;	//motion���[�v���~�߂邩bool
	bool m_MotionBrend_Sub;		//motion�u�����h�����邩bool
	//---------------------------------------------------------------













	CModelParts* m_pModelParts[MAX_PARTS];
	int m_ChangeDataModelIndex;//�f�[�^�ύX�̂��郂�f���̃C���f�b�N�X


	//OBB�̓����蔻��p
	COBB m_Obb;

	//
	int m_NowGridNum;//���݂̎����̂���GRID�̔ԍ�
	int m_RunCnt = 0;




//	bool m_isInAir=true;//�󒆂ɂ��邩�ǂ���
	bool m_isLandingTriggered=false;//���n���[�V�����������������ǂ���
	bool m_isOnGround=false;//�n�ʂɐڐG���Ă��邩�ǂ���
	// �ڒn��Ԃ�ێ����邽�߂̕ϐ�
	int m_groundCounter; // �ڒn��Ԃ̃J�E���^�[

	float m_OldPosY = 0.0f;
};

#endif