//=========================================================
//
// item.cpp�Ŏg���֐�[item.cpp]
// Author seiya kagaya
//
//=========================================================
#include "item.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "particle.h"
#include "all_texture.h"
#include "MathUtilities.h"

//=============================
//�R���X�g���N�^
//=============================
CItem::CItem(int nPriority) :CObject2D(nPriority)
{
}

//=============================
//�f�X�g���N�^
//=============================
CItem::~CItem()
{
}

//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CItem::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\item001.png", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);
	BindTexture(m_ESCpTexture);//�ݒ�

	DATA EscData = GetDATA();
	EscData.Radius = (ITEM_SIZE + ITEM_SIZE) / 4;
	EscData.MinLength = D3DXVECTOR3(-ITEM_SIZE, -ITEM_SIZE, 0.0f);
	EscData.MaxLength = D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, 0.0f);

	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_ITEM);

	return S_OK;
}

//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CItem::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//�X�V(���_���̍X�V)
//=============================
void CItem::Update()
{
	InputpVtx();
	CObject2D::Update();
}

//=============================
//�`�揈��(POLYGON�`��)
//=============================
void CItem::Draw()
{
	CObject2D::Draw();
}

//=============================
//�ݒ�i�[
//=============================
void CItem::InputpVtx()
{
	//�擾
	DATA EscData = GetDATA();
	VERTEX_2D EscVtx[BASE_INDEX];

	//���_���W�̍X�V-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - ITEM_SIZE;//����
	EscVtx[0].pos.y = EscData.Pos.y - ITEM_SIZE;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + ITEM_SIZE;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - ITEM_SIZE;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - ITEM_SIZE;//����
	EscVtx[2].pos.y = EscData.Pos.y + ITEM_SIZE;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + ITEM_SIZE;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + ITEM_SIZE;//�E��
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
CItem* CItem::Create(DATA data)
{
	CItem* pItem = new CItem;
	pItem->Init();

	//�擾
	DATA EscData = pItem->GetDATA();
	EscData.Pos = data.Pos;
	EscData.move = data.move;
	pItem->SetDATA(EscData);//�i�[
	pItem->ChangeRGBA(D3DCOLOR_RGBA(255, 255, 255, 255));

	return pItem;
}