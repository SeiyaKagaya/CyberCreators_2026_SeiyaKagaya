//=======================================================
//
//background�Ɋւ��鏈��[background.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "background.h"
#include "renderer.h"
#include "manager.h"
#include "main.h"

//=============================
//�R���X�g���N�^
//=============================
CBG::CBG()
{
	CRenderer* pRenderer = nullptr;
	
	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();



	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

//	data.Pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\title000.png", &m_pTexture);//�ʏ펞

}
//=============================
//�f�X�g���N�^
//=============================
CBG::~CBG()
{
}
//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CBG::Init()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


	if (FAILED(EscDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}




	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�

	float fTest = 1500.0f;

	pVtx[0].pos.x = -fTest;//����
	pVtx[0].pos.y = 0.0f;//����
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fTest;//�E��
	pVtx[1].pos.y = 0.0f;//�E��
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = -fTest;//����
	pVtx[2].pos.y = fTest;//����
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fTest;//�E��
	pVtx[3].pos.y = fTest;//�E��
	pVtx[3].pos.z = 0.0f;



	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



		//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	m_pVtxBuff->Unlock();


	return S_OK;

}
//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CBG::Uninit()
{
	if (m_pTexture)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//=============================
//�X�V(���_���̍X�V)
//=============================
void CBG::Update()
{
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, reinterpret_cast<void**>(&pVtx), 0);

	

	m_pVtxBuff->Unlock();

}
//=============================
//�`�揈��(POLYGON�`��)
//=============================
void CBG::Draw()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();



	EscDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	EscDevice->SetFVF(FVF_VERTEX_2D);

	EscDevice->SetTexture(0, m_pTexture);

	EscDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);


}


//=============================
//Object����
//=============================
CBG* CBG::Create()
{
	CBG* pPolygon = new CBG;
	pPolygon->Init();


	return pPolygon;
}





//�p������2D�̂ق��H