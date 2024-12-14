//=======================================================
//
//renderer�Ɋւ��鏈��[renderer.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "renderer.h"
//#include "object2D.h"
//#include "polygon.h"
#include "main.h"
#include "manager.h"
//#include "input.h"
#include <stdio.h>

//=============================
//�R���X�g���N�^
//=============================
CRenderer::CRenderer()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pCObject = nullptr;
	m_pFont = nullptr;
	m_mesh = false;
}
//=============================
//�f�X�g���N�^
//=============================
CRenderer::~CRenderer()
{
}
//=============================
//�����ݒ�
//=============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;//�v���[���e�[�V�����p�����[�^
	
	//direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�[���܂����`]
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//�Q�[����ʃT�C�Y��
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//�Q�[����ʃT�C�Y�c
	d3dpp.BackBufferFormat = d3ddm.Format;								//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;											//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//�_�u���o�b�t�@�̐؂�ւ��i�f���M���ɓ����j
	d3dpp.EnableAutoDepthStencil = TRUE;								//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8/*D3DFMT_D16*/;	//24�r�b�g�ɕύX(Zfight�h�~)--		//�f�p�X�o�b�t�@�Ƃ��ĂP�U�r�b�g���g��
	d3dpp.Windowed = bWindow;											//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//�C���^�[�o��

		//direct3D�f�o�C�X�̐����i�`�揈���ƒ��_�������n�[�h�E�F�A�ōs���j
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//direct�RD�f�o�C�X�̐����i�`�揈���̓n�[�h�E�F�A�A���_������CPU�ōs���j
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//direct�RD�f�o�C�X�̐����i�`�揈���ƒ��_������CPU�ōs���j
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�//-----------------------------------------------------------------
#if 1
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//�J�����O�̐ݒ�


	//�A���t�@�u�����h�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//D3DXMATRIX matProj;
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 4.0f / 3.0f, 1.0f, 1000.0f); // z-near��1.0f�Az-far��1000.0f�ɐݒ�
	//m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // �����v���̖ʂ��J�����O

		//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);


	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


#endif

	//�f�o�b�O�\���p�̃t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pFont);



	//�e��I�u�W�F�N�g�̏���������
	return S_OK;
}
//=============================
//�I������
//=============================
void CRenderer::Uninit()
{

	//direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}
	//direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}
//=============================
//�X�V����(�S�I�u�W�F�N�g)
//=============================
void CRenderer::Update()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	if (pManager->GetStayState() == false)
	{
		if (pManager->GetPauseState() == false)
		{

			m_pCObject->UpdateAll();//---------------------------------------------------------���ׂẴI�u�W�F�N�g�X�V

			if (keyboard->GetTrigger(DIK_F4) == true)//-----------------���b�V���\���n
			{
				m_mesh = !m_mesh;
				if (m_mesh == false)
				{
					//���̏��
					m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				}
				else if (m_mesh == true)
				{
					//���C���[�t���[�����[�h�̏��
					m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				}
			}
		}
	}
}
//=============================
//�`�揈��(�S�I�u�W�F�N�g)
//=============================
void CRenderer::Draw()
{
	
	CManager* pManager = CManager::GetInstance();


	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(
		0,
		nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(100, 100, 100, 100),
		1.0f,
		0);


	//�`��i�K
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		


		 pManager->GetCamera()->SetCamera();



		 m_pCObject->DrawAll();

		//�V�[���̕`��
		if (pManager->GetScene() != nullptr)
		{
			pManager->GetScene()->Draw();
		}
	
		//�t�F�[�h�`��
		if (pManager->GetFade() != nullptr)
		{
			pManager->GetFade()->Draw();
		}

//#if _DEBUG

		DrawFPS();
//#else
//#endif // _DEBUG

		//----------------------------------------------------------------------------------------------------------------------------------


		m_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
//=============================
//3D�f�o�C�X�̎擾
//=============================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}
//=============================
//FPS�\������
//=============================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];
	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d", GetFPS());

	//�e�L�X�g�̕`��
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 15, 15, 255));

}
