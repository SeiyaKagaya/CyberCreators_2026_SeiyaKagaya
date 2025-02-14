//=========================================================
//
// ObstacleSet.cpp�Ŏg���֐�[ObstacleSet.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBSTACLESET_H
#define _OBSTACLESET_H//��d�C���N���[�h�h�~

#include "objectX.h"
#include "MathUtilities.h"

class CObstacleSet : public CObjectX
{
public:

	static const int STAGE_HITSIZE = 150;//�X�e�[�W�z�u���̃T�C�Y

	//objectPass�Ǘ��\����
	typedef struct
	{
		int ModelIndex;			//���f���ԍ�
		const char* pFilePass;	// �t�@�C���p�X
	} OBSTACLEINFO;

	typedef struct
	{
		bool bObstacleBool;  // ��Q���t���O
		int distance;        // �X�^�[�g�n�_����̋���
		bool visited;        // �T���ς݃t���O
		int parentX;         // �o�H�ۑ��p�̐e�m�[�hX
		int parentY;         // �o�H�ۑ��p�̐e�m�[�hY

		//�Ōサ���g�p����
		int MoveNumX;
		int MoveNumZ;

	}GRIDDATA;

	CObstacleSet(int nPriority = CObject::LAYERINDEX_OBSTACLE);//�R���X�g���N�^
	~CObstacleSet() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


	//void HitCollision();																//�����蔻��܂Ƃ�

	bool GetStageBlockbool();															//��Ԏ擾

	static CObstacleSet* Create(DATA SetData, int SetType, bool bBreak, bool _bPreview);//�I�u�W�F�N�g����

	static void Resize(int count);														//�z��̃T�C�Y�ύX
	static void DataLoad(const char* filename);											//�X�e�[�W�f�[�^�̓ǂݍ��݂ƃN���G�C�g���s��
	static void previewModelLoad();														//�ݒu�\�胂�f�����`��--�����ɉߋ��̃v���r���[���f����������폜
	static void Model_DebugSave();														//�Z�b�g��ԃZ�[�u

	bool GetPreviewBool();																//�v���r���[���f�����擾
	int GetModelType();																	//���f���^�C�v�擾

	static void Input();																//���͌n(static)
	static void DebugSetDataDraw();														//�Z�b�g�p���`��

	static void ObstacleScanMapping();													//��Q���̌��m�Ƃ���𓥂܂����}�b�s���O


private:

	CMathProc::CollisionData m_HitData = {};											//�����蔻��f�[�^
	static std::vector<OBSTACLEINFO> m_ObstacleInfo;									//�t�@�C���p�X�i�[
	static int m_ObstacleCount;															//���f����(�z��T�C�Y)

	bool m_bBreak = false;																//�j��\��
	bool m_StageBlock = false;															//�X�e�[�Wblock��
	bool m_bPreview = false;															//�v���r���[��

	int m_nType = 0;																	//���(x.file�p

	static int m_NowSetModelIndex;														//�ݒu����^�C�v
	static int m_MAXModelIndex;															//���f���ő吔
	static D3DXVECTOR3 m_SetRot;														//�ݒu���p�x	
};

#endif