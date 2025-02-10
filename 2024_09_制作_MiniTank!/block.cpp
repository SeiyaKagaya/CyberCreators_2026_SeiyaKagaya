//=======================================================
//
//block�Ɋւ��鏈��[block.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "block.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"

//=============================
//�R���X�g���N�^
//=============================
CBlock::CBlock(int nPriority) :CObject2D(nPriority), m_nCounterAnim(0), m_nDirectionMove(0), m_nPatternAnim(0),m_nLife(STARTLIFE)
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//�擾
	DATA EscData = GetDATA();

	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	EscData.MinLength = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, 0.0f);//����
	EscData.MaxLength = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, 0.0f);//����

	//�e�N�X�`���ǂݍ���
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//�e�N�X�`���擾
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\Block004.jpg", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);
	
	BindTexture(m_ESCpTexture);//�ݒ�

	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_BLOCK);
}

//=============================
//�f�X�g���N�^
//=============================
CBlock::~CBlock()
{
}

//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CBlock::Init()
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

	return S_OK;
}

//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CBlock::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//�X�V(���_���̍X�V)
//=============================
void CBlock::Update()
{
	//�擾
	DATA EscData = GetDATA();

	if (m_nLife <= 0)
	{
		CExplosion::Create(EscData);
		Uninit();
		SetDeath(true);
		return;
	}

	InputpVtx();

	CObject2D::Update();
}

//=============================
//�`�揈��(BLOCK�`��)
//=============================
void CBlock::Draw()
{
	CObject2D::Draw();
}

//=============================
//��e����
//=============================
void CBlock::Damage(int nDamage)
{
	m_nLife -= nDamage;
}

//=============================
//�ݒ�i�[
//=============================
void CBlock::InputpVtx()
{
	//�擾
	DATA EscData = GetDATA();

	VERTEX_2D EscVtx[BASE_INDEX];

	//���_���W�̍X�V-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - BLOCK_SIZE;//����
	EscVtx[0].pos.y = EscData.Pos.y - BLOCK_SIZE;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + BLOCK_SIZE;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - BLOCK_SIZE;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - BLOCK_SIZE;//����
	EscVtx[2].pos.y = EscData.Pos.y + BLOCK_SIZE;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + BLOCK_SIZE;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + BLOCK_SIZE;//�E��
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
CBlock* CBlock::Create(DATA data)
{
	CBlock* pBlock = new CBlock;
	pBlock->Init();

	//�擾
	DATA EscData = pBlock->GetDATA();

	EscData.Pos = data.Pos;
	EscData.move = data.move;

	pBlock->SetDATA(EscData);//�i�[

	pBlock->ChangeRGBA(D3DCOLOR_RGBA(255, 255, 255, 255));

	return pBlock;
}