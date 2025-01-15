//=========================================================
//
// particle.cpp�Ŏg���֐�[particle.cpp]
// Author seiya kagaya
//
//=========================================================
#include "particle.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "all_texture.h"

//=============================
//�R���X�g���N�^
//=============================
CParticle::CParticle(int nPriority):CObject2D(nPriority), m_nLife(START_LIFE),m_Radius((float)START_RADiUS)
{


}
//=============================
//�f�X�g���N�^
//=============================
CParticle::~CParticle()
{
}
//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CParticle::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\effect000.jpg", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//�ݒ�

	SetObjectType(CObject2D::OBJECT_PARTICLE);
	return S_OK;
}
//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CParticle::Uninit()
{
	CObject2D::Uninit();
}
//=============================
//�X�V(���_���̍X�V)
//=============================
void CParticle::Update()
{	
	//�擾
	DATA EscData = GetDATA();



	m_nLife--;
	m_Radius -= 0.1f;



	if (m_nLife <= 0 || EscData.Pos.x <= 0 || EscData.Pos.x >= SCREEN_WIDTH || EscData.Pos.y <= 0 || EscData.Pos.y >= SCREEN_HEIGHT)
	{
		Uninit();
		Release();
		return;
	}


	SetDATA(EscData);//�i�[


	InputpVtx();//�|���S���X�V
	CObject2D::Update();
}
//=============================
//�`�揈��(POLYGON�`��)
//=============================
void CParticle::Draw()
{
	ChengeAddDrawMode(true);

	CObject2D::Draw();

	ChengeAddDrawMode(false);

}
//=============================
//�ݒ�i�[
//=============================
void CParticle::InputpVtx()
{
	//�擾
	DATA EscData = GetDATA();


	VERTEX_2D EscVtx[BASE_INDEX];

	//���_���W�̍X�V-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - m_Radius;//����
	EscVtx[0].pos.y = EscData.Pos.y - m_Radius;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + m_Radius;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - m_Radius;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - m_Radius;//����
	EscVtx[2].pos.y = EscData.Pos.y + m_Radius;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + m_Radius;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + m_Radius;//�E��
	EscVtx[3].pos.z = 0.0f;

	EscVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EscVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EscVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EscVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetpVtx(EscVtx);
}
//=============================
//Object����
//=============================
CParticle* CParticle::Create(DATA data)
{
	CParticle* pParticle = new CParticle;
	pParticle->Init();


	//�擾
	DATA EscData = pParticle->GetDATA();

	EscData.Pos = data.Pos;

	pParticle->SetDATA(EscData);//�i�[


	pParticle->ChangeRGBA(D3DCOLOR_RGBA(255, 0, 0, 255));

	return pParticle;
}




