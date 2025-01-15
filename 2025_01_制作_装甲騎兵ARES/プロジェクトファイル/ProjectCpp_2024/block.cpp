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

	//	EscData.Radius = m_fLength;

	EscData.MinLength = D3DXVECTOR3(-BLOCK_WIDE, -BLOCK_HEIGHT, 0.0f);//����
	EscData.MaxLength = D3DXVECTOR3(BLOCK_WIDE, BLOCK_HEIGHT, 0.0f);//����


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



	//VERTEX_2D* pVtx;

	////ESCpVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//////�擾
	////DATA EscData = GetDATA();


	//////���_���W�̐ݒ�

	////pVtx[0].pos.x = EscData.Pos.x - BLOCK_WIDE / 2;//����
	////pVtx[0].pos.y = EscData.Pos.y - BLOCK_HEIGHT / 2;//����
	////pVtx[0].pos.z = 0.0f;

	////pVtx[1].pos.x = EscData.Pos.x + BLOCK_WIDE / 2;//�E��
	////pVtx[1].pos.y = EscData.Pos.y - BLOCK_HEIGHT / 2;//�E��
	////pVtx[1].pos.z = 0.0f;

	////pVtx[2].pos.x = EscData.Pos.x - BLOCK_WIDE / 2;//����
	////pVtx[2].pos.y = EscData.Pos.y + BLOCK_HEIGHT / 2;//����
	////pVtx[2].pos.z = 0.0f;

	////pVtx[3].pos.x = EscData.Pos.x + BLOCK_WIDE / 2;//�E��
	////pVtx[3].pos.y = EscData.Pos.y + BLOCK_HEIGHT / 2;//�E��
	////pVtx[3].pos.z = 0.0f;



	////pVtx[0].rhw = 1.0f;
	////pVtx[1].rhw = 1.0f;
	////pVtx[2].rhw = 1.0f;
	////pVtx[3].rhw = 1.0f;

	////pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	////pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	////pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	////pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////////�e�N�X�`�����W���X�V
	//////pVtx[0].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * m_nDirectionMove));//����//�j���[�g�����̏��
	//////pVtx[1].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * m_nDirectionMove));//�E��
	//////pVtx[2].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//����
	//////pVtx[3].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//�E��


	////	//�e�N�X�`�����W���X�V
	////pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	////pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	////pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	////pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//ESCpVtxBuff->Unlock();


	//SetDATA(EscData);//�i�[


	////�e�N�X�`���ǂݍ���
	//LPDIRECT3DTEXTURE9	m_ESCpTexture = CAllTexture::GetTexture(CAllTexture::OBJECT_BLOCK);

	//////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(EscDevice, "DATA\\TEXTURE\\Player001.png", &m_ESCpTexture);//�ʏ펞


//	BindTexture(m_ESCpTexture);//�ݒ�


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
		//Release();
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
	EscVtx[0].pos.x = EscData.Pos.x - BLOCK_WIDE;//����
	EscVtx[0].pos.y = EscData.Pos.y - BLOCK_HEIGHT;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + BLOCK_WIDE;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - BLOCK_HEIGHT;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - BLOCK_WIDE;//����
	EscVtx[2].pos.y = EscData.Pos.y + BLOCK_HEIGHT;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + BLOCK_WIDE;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + BLOCK_HEIGHT;//�E��
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





//�p������2D�̂ق��H