//=========================================================
//
// block3D[block3D.cpp]
// Author seiya kagaya
//
//=========================================================
#include "block3D.h"
#include "renderer.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CBlock3D::CBlock3D(int nPriority) :CObjectX(nPriority)
{
}

//=============================
//�f�X�g���N�^
//=============================
CBlock3D::~CBlock3D()
{
}

//=============================
//������
//=============================
HRESULT CBlock3D::Init()
{
    CObjectX::Init();
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPD3DXMESH pMesh = nullptr;//Mesh�|�C���^
    LPD3DXBUFFER pBuffMat = nullptr;//�}�e���A���ւ̃|�C���^
    DWORD dwNumMat = 0;//�}�e���A���̐�

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    //�t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\baseBlock.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    //�}�e���A���f�[�^�ւ̃|�C���^���擾
    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        // �f�B�t���[�Y�J���[���T�C�Y�Ɋ�Â��ĕύX
        D3DXCOLOR originalColor = pMat[nCntMat].MatD3D.Diffuse;

        pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�F�������Ŏw��
    }

    SetXfireData(pMesh, pBuffMat, dwNumMat);//�f�[�^�i�[

    SetObjectType(CObject::OBJECT_BLOCK3D);

    SetSizeMag(D3DXVECTOR3(5.0f, 5.0f, 5.0f));//�傫���{��

    //�擾
    DATA EscData = GetDATA();
    EscData = GetDATA();//�Ď擾
    EscData.MinLength = D3DXVECTOR3(-SIZE, 0.0f, -SIZE);
    EscData.MaxLength = D3DXVECTOR3(SIZE, SIZE, SIZE);
    SetDATA(EscData);//�i�[

    return S_OK;
}

//=============================
//�j��
//=============================
void CBlock3D::Uninit()
{
    CObjectX::Uninit();
}

//=============================
//�X�V
//=============================
void CBlock3D::Update()
{   
    CObjectX::Update();
}

//=============================
//�`��
//=============================
void CBlock3D::Draw()
{
    //�T�C�Y�ύX
    SizeMagChangebool(true);

    CObjectX::Draw();
}

//=============================
//����
//=============================
CBlock3D* CBlock3D::Create()
{
    CBlock3D* pBlock3D = new CBlock3D;
    pBlock3D->Init();
    return pBlock3D;
}