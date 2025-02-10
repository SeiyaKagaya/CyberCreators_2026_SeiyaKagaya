//=========================================================
//
// explosion.cpp�Ŏg���֐�[explosion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "explosion.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "all_texture.h"

//=============================
//�R���X�g���N�^
//=============================
CExplosion::CExplosion(int nPriority):CObject2D(nPriority),m_nLife(START_LIFE), m_nPatternAnim(1)
{
}

//=============================
//�f�X�g���N�^
//=============================
CExplosion::~CExplosion()
{
}

//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CExplosion::Init()
{
	CObject2D::Init();//��{�ݒ�
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
	
	//�e�N�X�`���ǂݍ���
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;
	
	//�e�N�X�`���擾
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\explosion000.png", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//�ݒ�

	SetObjectType(CObject2D::OBJECT_EXPLOSION);

	return S_OK;
}

//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CExplosion::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//�X�V(���_���̍X�V)
//=============================
void CExplosion::Update()
{
	//�擾
	DATA EscData = GetDATA();

	m_nLife--;

	m_nPatternAnim++;
	
	SetDATA(EscData);//�i�[

	if (m_nLife <= 0 || m_nPatternAnim > DIVISION_NUMBER)
	{
		Uninit();
		Release();

		return;
	}
	
	InputpVtx();//�|���S���X�V

	CObject2D::Update();
}

//=============================
//�`�揈��(POLYGON�`��)
//=============================
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//=============================
//�ݒ�i�[
//=============================
void CExplosion::InputpVtx()
{
	//�擾
	DATA EscData = GetDATA();

	VERTEX_2D EscVtx[BASE_INDEX];

	//���_���W�̍X�V-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - SIZE;//����
	EscVtx[0].pos.y = EscData.Pos.y - SIZE;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + SIZE;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - SIZE;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - SIZE;//����
	EscVtx[2].pos.y = EscData.Pos.y + SIZE;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + SIZE;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + SIZE;//�E��
	EscVtx[3].pos.z = 0.0f;

	EscVtx[0].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 0.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
	EscVtx[1].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 0.0f);
	EscVtx[2].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim - (1.0f / DIVISION_NUMBER), 1.0f);//�e�N�X�`�����������E���ɍ��W���Y���Ă�
	EscVtx[3].tex = D3DXVECTOR2((1.0f / DIVISION_NUMBER) * m_nPatternAnim, 1.0f);

	SetpVtx(EscVtx);
}

//=============================
//Object����
//=============================
CExplosion* CExplosion::Create(DATA data)
{
	CExplosion* pExplosion = new CExplosion;

	pExplosion->Init();

	//�擾
	DATA EscData = pExplosion->GetDATA();
	EscData.Pos = data.Pos;

	pExplosion->SetDATA(EscData);//�i�[
	
	return pExplosion;
}