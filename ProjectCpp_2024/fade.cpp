//==================================================
//
//�t�F�[�h�Ɋւ��鏈��[fade.cpp]
// Author seiya kagaya
//
//==================================================
//#include "main.h"
#include "fade.h"
#include "renderer.h"
#include "manager.h"
//#include "object3D.h"

//�O���[�o���ϐ��錾

//=============================
// �R���X�g���N�^
//=============================
CFade::CFade(int nPriority)
{
	m_ColorA = 0.0f;
	m_fade = FADE_IN;
	m_fadeCnt = 0;
	m_SetMode = false;

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	//�擾
	DATA EscData = GetDATA();

	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	//�e�N�X�`���ǂݍ���
//	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//�e�N�X�`���擾
//	CAllTexture* pTexture = pManager->GetTexture();

//	int texIndex = pTexture->Regist("DATA\\TEXTURE\\FADE.jpg", EscDevice);//�e�N�X�`���o�^

//	m_ESCpTexture = pTexture->GetAddress(texIndex);



//	BindTexture(m_ESCpTexture);//�ݒ�

	//���܂������Ȃ������Ƃ�
//	m_pTexture2 = m_ESCpTexture;
	
	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_FADE);//�ݒ�

}
//=============================
// �f�X�g���N�^
//=============================
CFade::~CFade()
{
}
//=============================
// ������
//=============================
HRESULT CFade::Init(CScene::MODE ModeNext)
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

	VERTEX_2D* pVtx;
	ESCpVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V-----------------------------------
	pVtx[0].pos.x = 0.0f;//����
	pVtx[0].pos.y = 0.0f;//����
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = SCREEN_WIDTH;//�E��
	pVtx[1].pos.y = 0.0f;//�E��
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;//����
	pVtx[2].pos.y = SCREEN_HEIGHT;//����
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = SCREEN_WIDTH;//�E��
	pVtx[3].pos.y = SCREEN_HEIGHT;//�E��
	pVtx[3].pos.z = 0.0f;

	pVtx[0].rhw = 1.f;
	pVtx[1].rhw = 1.f;
	pVtx[2].rhw = 1.f;
	pVtx[3].rhw = 1.f;

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	ESCpVtxBuff->Unlock();

	InputpVtx();

	//�ݒ�
	BindVtxBuffer(ESCpVtxBuff);

	m_ModeNext = ModeNext;
	
	SetObjectType(CObject::OBJECT_FADE);

	return S_OK;
}
//=============================
// �I��
//=============================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}
//=============================
// �X�V
//=============================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{//�t�F�[�h�C�����
			
			if (m_SetMode == false)
			{
			CObject::ReleaseAll();//�S�I�u�W�F�N�g�J��


				//���[�h�ݒ�(���̉�ʂɈڍs)
				CManager::SetMode(m_ModeNext);

				CRenderer* pRenderer = nullptr;

				CManager* pManager = CManager::GetInstance();

				pManager->SetNewBulletAll(CNewBulletALL::Create());

				m_SetMode = true;
			}


			m_ColorA -= 0.05f;	//�|���S���𓧖��ɂ��Ă���

			if (m_ColorA <= 0.0f)
			{
				m_ColorA = 0.0f;

				m_fade = FADE_NONE;	//�������Ă��Ȃ����
			}
		}
		else if (m_fade == FADE_OUT)
		{//�t�F�[�h�A�E�g���

			

			m_ColorA += 0.1f;	//�|���S����s�����ɂ��Ă���

			if (m_ColorA >= 1.0f)
			{
				m_ColorA = 1.0f;

				m_fadeCnt++;//���[�h�ڍs�J�E���^�[

				m_fade = FADE_IN;	//�t�F�[�h�C�����
			}

			if (m_fadeCnt == 1)
			{//�F�������c���������
				m_fadeCnt = 0;
			}

		}

		D3DXCOLOR EscColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_ColorA);
	
		ChangeRGBA(EscColor);
	
		CObject2D::Update();
	
		return;

	}
}
//=============================
// �`��
//=============================
void CFade::Draw(void)
{
#if _DEBUG

	if (m_fade != FADE_NONE)
	{

		if (m_fade == FADE_IN)
		{
			const char* aData = "�t�F�[�h�C��";


			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
		}
		else if (m_fade == FADE_OUT)
		{
			const char* aData = "�t�F�[�h�A�E�g";

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
		}

	}

#endif // _DEBUG

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	EscDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// Z�̔�r���@
	EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		// Z�o�b�t�@�ɏ������܂Ȃ�

	CObject2D::Draw();

	EscDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	// Z�̔�r���@�ύX
	EscDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Z�o�b�t�@�ɏ�������


}
//=============================
// �t�F�[�h�ݒ�
//=============================
void CFade::SetFade(CScene::MODE ModeNext)
{
	if (m_fade == FADE_NONE)
	{
		m_SetMode = false;
		m_ColorA = 0.0f;
		m_fadeCnt = 0;
		m_ColorA = 0.0f;			//�����|���S��(����)�ɂ��Ă���
		m_fade = FADE_OUT;											//�t�F�[�h�A�E�g��Ԃ�
		m_ModeNext = ModeNext;										//���̉��(���[�h)��ݒ�

	}
}
//=============================
// ��Ԏ擾
//=============================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}
//=============================
// ���_���W���
//=============================
void CFade::InputpVtx()
{
	//�擾
//	DATA EscData = GetDATA();


	VERTEX_2D EscVtx[BASE_INDEX];

	//���_���W�̍X�V-----------------------------------
	EscVtx[0].pos.x = 0.0f;//����
	EscVtx[0].pos.y = 0.0f;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = SCREEN_WIDTH;//�E��
	EscVtx[1].pos.y = 0.0f;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = 0.0f;//����
	EscVtx[2].pos.y = SCREEN_HEIGHT;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = SCREEN_WIDTH;//�E��
	EscVtx[3].pos.y = SCREEN_HEIGHT;//�E��
	EscVtx[3].pos.z = 0.0f;

	EscVtx[0].rhw = 1.f;
	EscVtx[1].rhw = 1.f;
	EscVtx[2].rhw = 1.f;
	EscVtx[3].rhw = 1.f;

	EscVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	EscVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	EscVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	EscVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	EscVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	EscVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	EscVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	EscVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	SetpVtx(EscVtx);

	
}
