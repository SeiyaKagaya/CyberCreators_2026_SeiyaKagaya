//=======================================================
//
// tankfootprint�Ɋւ��鏈��[tankfootprint.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "tankfootprint.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectFootPrint::CObjectFootPrint(int nPriority) :CObject3D(nPriority)
{
    SetObjectType(CObject::OBJECT_FOOTPRINT);
}

//=============================
// �f�X�g���N�^
//=============================
CObjectFootPrint::~CObjectFootPrint()
{
    Uninit();
}

//=============================
// �����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CObjectFootPrint::Init()
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff;//���_�o�b�t�@
    
    if (FAILED(EscDevice->CreateVertexBuffer(
        sizeof(VERTEX_3D) * 4,//�l�p�`�̂���4
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_3D,
        D3DPOOL_MANAGED,
        &ESCpVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    BindVtxBuffer(ESCpVtxBuff);

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

    int texIndex = pTexture->Regist("DATA\\TEXTURE\\TankMove.png", EscDevice);//�e�N�X�`���o�^

    m_ESCpTexture = pTexture->GetAddress(texIndex);

    BindTexture(m_ESCpTexture);//�ݒ�

    m_nLife = STANPLIFE;

    return S_OK;
}

//=============================
// �I������(���_�o�b�t�@�j��)
//=============================
void CObjectFootPrint::Uninit()
{
	CObject3D::Uninit();
}

//=============================
// �X�V(���_���̍X�V)
//=============================
void CObjectFootPrint::Update()
{
    CScene::MODE NowState = CScene::GetNowScene();

    if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4)
    {//�Q�[����

    }
    else if (NowState == CScene::MODE_TITLE)
    {//�^�C�g��

      //�擾
        DATA EscData = GetDATA();

        EscData.Pos.x += 13.0f;
        //�擾
        SetDATA(EscData);
    }
    else if (NowState == CScene::MODE_RESULT)
    {//�^�C�g��
      //�擾
        DATA EscData = GetDATA();

        EscData.Pos.x -= 13.0f;
        //�擾
        SetDATA(EscData);
    }

    InputpVtx();

    CObject3D::Update();

    m_nLife--;

    if (m_nLife <= 0)
    {
        SetDeath(true);
    }
}

//=============================
// �`�揈��(POLYGON�`��)
//=============================
void CObjectFootPrint::Draw()
{
	CObject3D::Draw();
}

//=============================
// ���W�ݒ�
//=============================
void CObjectFootPrint::SetPos_Rot(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    //�擾
    DATA EscData = GetDATA();

    EscData.Pos = Pos;
    EscData.rot = rot;
    //�擾
    SetDATA(EscData);
}

//=============================
// ���_���
//=============================
void CObjectFootPrint::InputpVtx()
{
    // �����ݒ�
    VERTEX_3D pVtx[BASE_INDEX];
    
    //�擾
    DATA EscData = GetDATA();

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3((float)-PRINTSIZE_X, (float)PRINTSIZE_Y, (float)PRINTSIZE_Z);
    pVtx[1].pos = D3DXVECTOR3((float)PRINTSIZE_X, (float)PRINTSIZE_Y, (float)PRINTSIZE_Z);
    pVtx[2].pos = D3DXVECTOR3((float)-PRINTSIZE_X, (float)PRINTSIZE_Y, (float)-PRINTSIZE_Z);
    pVtx[3].pos = D3DXVECTOR3((float)PRINTSIZE_X, (float)PRINTSIZE_Y, (float)-PRINTSIZE_Z);

    //�@���x�N�g���̐ݒ�
    pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    //���_�J���[�̐ݒ�
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COL_A);

    //�e�N�X�`�����W��ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//����
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);//�E��
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);//����
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);//�E��

    SetpVtx(pVtx);
}

//=============================
// Object����
//=============================
CObjectFootPrint* CObjectFootPrint::Create(D3DXVECTOR3 Pos, D3DXVECTOR3 rot)
{
    CObjectFootPrint* pObject3D = new CObjectFootPrint;
	pObject3D->SetPos_Rot(Pos,rot);
    pObject3D->Init();
    return pObject3D;
}