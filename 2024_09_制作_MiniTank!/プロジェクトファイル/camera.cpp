//============================================================================================
//
//�J�������Ǘ����鏈��[camera.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include <time.h>
#include "player_motion.h"

float CCamera::m_Screen_Width = (float)SCREEN_WIDTH;//�X�N���[������
float CCamera::m_Screen_Height = (float)SCREEN_HEIGHT;//�X�N���[���c��

//=============================
//�R���X�g���N�^
//=============================
CCamera::CCamera()
{
	// ���݂̎��Ԃ��V�[�h�l�Ƃ��Đݒ�
	srand(static_cast<unsigned int>(time(0)));
}

//=============================
//�f�X�g���N�^
//=============================
CCamera::~CCamera()
{
}

//=============================
//������
//=============================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(700.0f, 800.0f, 0.0f);//���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_nShakeFlame = 0;
	m_fMag = 0.0f;

	return S_OK;
}

//=============================
//�I��
//=============================
void CCamera::Uninit()
{
}

//=============================
//�X�V
//=============================
void CCamera::Update()
{
	float fLength;

	CScene::MODE NowState = CScene::GetNowScene();

	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4)
	{//�Q�[����
		//player�̈ʒu���擾
		CObject* pObj = nullptr;
		pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

		if (pObj != nullptr)
		{
			CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

			CObject::DATA EscData;

			EscData = pPlayer->GetClassData();

			m_posR = EscData.Pos;//�����_
		}
	 
	 //�J��������	
		fLength = CAMERA_LENGTH[0];

		//�p�x�ɂ��ʒu����
		m_rot.x = ROT_X[0];
		m_rot.y = 0.0f;
		m_rot.z = 0.0f;
	}
	else if (NowState == CScene::MODE_TITLE|| NowState == CScene::MODE_RESULT)
	{//�^�C�g��
		m_posR = D3DXVECTOR3(0.0f, TITLE_Y, 0.0f);

		//�J��������	
		fLength = CAMERA_LENGTH[1];

		//�p�x�ɂ��ʒu����
		m_rot.x = ROT_X[1];
		m_rot.y = 0.0f;
		m_rot.z = 0.0f;
	}

	//��������p�x								//
	m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1�R�T�C���V�[�^��������--�R�T�C���t�@�C��������
	m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Y�͕��Ղ̂��߂����Ȃ�
	m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//�P�Ɠ�������
	//posR��			������PosV	������+�ɕύX
}

//=============================
//�J�����ݒ�
//=============================
void CCamera::SetCamera()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),//����p
		(float)m_Screen_Width / (float)m_Screen_Height,//��ʂ̃A�X�y�N�g��
		10.0f,//�����ŏ��l
		9000.0f);//z���ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	EscDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//----------------------------------------------------------
	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_fMag > 1)
	{
		m_fMag--;
		float nRandomX = (float)(rand() % (int)m_fMag);
		float nRandomY = (float)(rand() % (int)m_fMag);
		float nRandomZ = (float)(rand() % (int)m_fMag);

		adjust = D3DXVECTOR3(nRandomX * 0.1f, nRandomY * 0.1f, nRandomZ * 0.1f);

		D3DXVECTOR3 adjustedPosV = m_posV + adjust;
		D3DXVECTOR3 adjustedPosR = m_posR + adjust;

		D3DXMatrixLookAtLH(&m_mtxView, &adjustedPosV, &adjustedPosR, &m_vecU);
		//-----------------------------------------------------------
	}

	//�r���[�}�g���b�N�X�̐ݒ�
	EscDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================
//�J�����h��
//=============================
void CCamera::SetShake(int ShakeFlame, float Magnitude)
{
	m_fMag = Magnitude;
	m_nShakeFlame = ShakeFlame;
}

//=============================
//�X�N���[���T�C�Y�i�[
//=============================
void CCamera::SetScreenSize(float screenWidth, float screenHeight)
{
	m_Screen_Width = (float)screenWidth;
	m_Screen_Height = (float)screenHeight;
}

//=============================
//�X�N���[���U�C�Y�擾
//=============================
D3DXVECTOR2 CCamera::GetScreenSize()
{
	return D3DXVECTOR2((float)m_Screen_Width, (float)m_Screen_Height);
}

//=============================
//�p�x�擾
//=============================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}