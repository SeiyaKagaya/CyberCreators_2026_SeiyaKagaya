//=========================================================
//
// enemy.cpp�Ŏg���֐�[enemy.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "particle.h"
#include "all_texture.h"

//=============================
//�R���X�g���N�^
//=============================
CEnemy::CEnemy(int nPriority):CObject2D(nPriority),m_nLife(START_LIFE)
{
}

//=============================
//�f�X�g���N�^
//=============================
CEnemy::~CEnemy()
{
}

//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CEnemy::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\player000.png", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//�ݒ�

	//�擾
	DATA EscData = GetDATA();
	EscData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EscData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EscData.OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	EscData.Radius = (ENEMY_SIZE + ENEMY_SIZE) / 4;
 	EscData.MinLength = D3DXVECTOR3(-ENEMY_SIZE, -ENEMY_SIZE, 0.0f);
	EscData.MaxLength = D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f);

	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_ENEMY);

	return S_OK;
}

//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CEnemy::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//�X�V(���_���̍X�V)
//=============================
void CEnemy::Update()
{
	//�擾
	DATA EscData = CEnemy::GetDATA();

	if (m_nLife <= 0 || EscData.Pos.x <= 0 || EscData.Pos.x >= SCREEN_WIDTH || EscData.Pos.y <= 0 || EscData.Pos.y >= SCREEN_HEIGHT)
	{
		CExplosion::Create(EscData);
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
void CEnemy::Draw()
{
	CObject2D::Draw();
}

//=============================
//�ݒ�i�[
//=============================
void CEnemy::InputpVtx()
{
	//�擾
	DATA EscData = GetDATA();
	VERTEX_2D EscVtx[BASE_INDEX];

	//���_���W�̍X�V-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - ENEMY_SIZE;//����
	EscVtx[0].pos.y = EscData.Pos.y - ENEMY_SIZE;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + ENEMY_SIZE;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - ENEMY_SIZE;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - ENEMY_SIZE;//����
	EscVtx[2].pos.y = EscData.Pos.y + ENEMY_SIZE;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + ENEMY_SIZE;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + ENEMY_SIZE;//�E��
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
CEnemy* CEnemy::Create(DATA data)
{
	CEnemy* pEnemy = new CEnemy;
	pEnemy->Init();

	//�擾
	DATA EscData = pEnemy->GetDATA();
	EscData.Pos = data.Pos;

	pEnemy->SetDATA(EscData);//�i�[
	pEnemy->ChangeRGBA(D3DCOLOR_RGBA(155, 155, 0, 255));

	return pEnemy;
}