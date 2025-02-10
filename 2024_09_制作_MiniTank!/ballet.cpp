//=========================================================
//
// ballet.cpp�Ŏg���֐�[ballet.cpp]
// Author seiya kagaya
//
//=========================================================
#include "ballet.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "explosion.h"
#include "particle.h"
#include "all_texture.h"
#include "MathUtilities.h"
#include "block.h"

//=============================
//�R���X�g���N�^
//=============================
CBullet::CBullet(int nPriority):CObject2D(nPriority),m_nLife(START_LIFE),m_speed((float)START_SPEED)
{
}

//=============================
//�f�X�g���N�^
//=============================
CBullet::~CBullet()
{
}

//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CBullet::Init()
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

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\bullet000.png", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);

	BindTexture(m_ESCpTexture);//�ݒ�
							   
	//�擾
	DATA EscData = GetDATA();

	EscData.Radius = (BULLET_SIZE + BULLET_SIZE) / 4;
	EscData.MinLength = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0.0f);
	EscData.MaxLength = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0.0f);

	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_BULLET);

	return S_OK;
}

//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//�X�V(���_���̍X�V)
//=============================
void CBullet::Update()
{
	//�擾
	DATA EscData = GetDATA();
	EscData.OldPos = EscData.Pos;
	EscData.Pos += EscData.move*m_speed;

	m_nLife--;

	CParticle::Create(EscData);

	SetDATA(EscData);//�i�[
	
	HitCollision();//�����蔻��

	//�ēx�擾
	EscData = GetDATA();

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
void CBullet::Draw()
{
	CObject2D::Draw();
}

//=============================
//�����蔻��i�[
//=============================
void CBullet::HitCollision()
{
	//�擾
	DATA EscData = GetDATA();

	CMathProc::CollisionData HitData;//�����蔻��f�[�^

	//�����蔻��v�Z--�G
	HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_ENEMY);//�G

	if (HitData.bHit ==false)
	{
		//�����蔻��v�Z--BLOCK
		HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_POLYGON);//�|���S��

		if (HitData.bHit == false)
		{
			//�����蔻��v�Z--�G
			HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_BLOCK);//block
		}
	}

	if (HitData.bHit == true)
	{
		m_nLife = 0;
	}

	SetDATA(EscData);//�i�[
}

//=============================
//�ݒ�i�[
//=============================
void CBullet::InputpVtx()
{
	//�擾
	DATA EscData = GetDATA();


	VERTEX_2D EscVtx[BASE_INDEX];

	//���_���W�̍X�V-----------------------------------
	EscVtx[0].pos.x = EscData.Pos.x - BULLET_SIZE;//����
	EscVtx[0].pos.y = EscData.Pos.y - BULLET_SIZE;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + BULLET_SIZE;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - BULLET_SIZE;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - BULLET_SIZE;//����
	EscVtx[2].pos.y = EscData.Pos.y + BULLET_SIZE;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + BULLET_SIZE;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + BULLET_SIZE;//�E��
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
CBullet* CBullet::Create(DATA data)
{
	CBullet* pBullet = new CBullet;
	pBullet->Init();

	//�擾
	DATA EscData = pBullet->GetDATA();
	EscData.Pos = data.Pos;
	EscData.move = data.move;

	pBullet->SetDATA(EscData);//�i�[	
	pBullet->ChangeRGBA(D3DCOLOR_RGBA(155, 155, 0, 255));

	return pBullet;
}