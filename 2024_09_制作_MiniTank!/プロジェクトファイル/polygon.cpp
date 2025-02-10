//=======================================================
//
//polygon�Ɋւ��鏈��[polygon.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "polygon.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"

//=============================
//�R���X�g���N�^
//=============================
CPolygon::CPolygon(int nPriority):CObject2D(nPriority), m_nCounterAnim(0), m_nDirectionMove(0), m_nPatternAnim(0)
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//�擾
	DATA EscData = GetDATA();
	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 0.0f);
	EscData.MinLength = D3DXVECTOR3(-POLYGON_SIZE /2, -POLYGON_SIZE /2, 0.0f);//����
	EscData.MaxLength = D3DXVECTOR3(POLYGON_SIZE /2, POLYGON_SIZE /2, 0.0f);//����

	//�e�N�X�`���ǂݍ���
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//�e�N�X�`���擾
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\Block001.jpg", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//�ݒ�

	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_POLYGON);
}

//=============================
//�f�X�g���N�^
//=============================
CPolygon::~CPolygon()
{
}

//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CPolygon::Init()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//�擾
	LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff = GetpVtxBuffer();

	if (FAILED(EscDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&ESCpVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	//�ݒ�
	BindVtxBuffer(ESCpVtxBuff);
	VERTEX_2D* pVtx;

	ESCpVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//�擾
	DATA EscData = GetDATA();

	//���_���W�̐ݒ�
	pVtx[0].pos.x = EscData.Pos.x - POLYGON_SIZE / 2;//����
	pVtx[0].pos.y = EscData.Pos.y - POLYGON_SIZE / 2;//����
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x =EscData.Pos.x + POLYGON_SIZE / 2;//�E��
	pVtx[1].pos.y =EscData.Pos.y - POLYGON_SIZE / 2;//�E��
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x =EscData.Pos.x - POLYGON_SIZE / 2;//����
	pVtx[2].pos.y =EscData.Pos.y + POLYGON_SIZE / 2;//����
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x =EscData.Pos.x + POLYGON_SIZE / 2;//�E��
	pVtx[3].pos.y =EscData.Pos.y + POLYGON_SIZE / 2;//�E��
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


	ESCpVtxBuff->Unlock();

	SetDATA(EscData);//�i�[

	return S_OK;
}

//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CPolygon::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//�X�V(���_���̍X�V)
//=============================
void CPolygon::Update()
{
}

//=============================
//�`�揈��(POLYGON�`��)
//=============================
void CPolygon::Draw()
{
	CObject2D::Draw();
}

//=============================
//Object����
//=============================
CPolygon* CPolygon::Create()
{
	CPolygon* pPolygon = new CPolygon;
	pPolygon->Init();
	return pPolygon;
}