//=========================================================
//
// 2D-3DhitColision[2D-3DhitColision.cpp]
// Author seiya kagaya
//
//=========================================================
#include"3D-2DhitObject.h"
#include "manager.h"





//=============================
// �R���X�g���N�^
//=============================
CStageCollisionBox3D2D::CStageCollisionBox3D2D(int nPriority) :CObjectX(nPriority)
{

}

//=============================
// �f�X�g���N�^
//=============================
CStageCollisionBox3D2D::~CStageCollisionBox3D2D()
{
}

//=============================
// ������
//=============================
HRESULT CStageCollisionBox3D2D::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr;
    LPD3DXBUFFER pBuffMat = nullptr;
    DWORD dwNumMat = 0;

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    // ���b�V���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\iwa.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    // �e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();
    LPDIRECT3DTEXTURE9 m_ESCpTexture = nullptr;

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
    //        const char* TexName = "DATA\\TEXTURE\\iwa.jpg";
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);
            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);

            // UV�X�P�[���𒲐��iUV��2�{�ɂ��邱�Ƃ�600�T�C�Y�ɍ��킹���j
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
            EscDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
        }
    }


    float USize = m_TexSize.x / 150.0f;
    float VSize = m_TexSize.y / 150.0f;;

    pMesh = ScaleMeshUVs(pMesh, USize,VSize);

    SetXfireData(pMesh, pBuffMat, dwNumMat);
    SetObjectType(CObject::OBJECT_HITBOX);

    return S_OK;
}

//=============================
// �j��
//=============================
void CStageCollisionBox3D2D::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// �X�V
//=============================
void CStageCollisionBox3D2D::Update()
{


}

//=============================
// �`��
//=============================
void CStageCollisionBox3D2D::Draw()
{

#if _DEBUG

    ChengeStageTex(true);
    SizeMagChangebool(true);
 //   SetColorChangeBool(true);
    CObjectX::Draw();
    ChengeStageTex(false);

#else

#endif // _D
}

//=============================
// ����
//=============================
CStageCollisionBox3D2D* CStageCollisionBox3D2D::Create(DATA SetData)
{
    CStageCollisionBox3D2D* pObstacle = new CStageCollisionBox3D2D;

    pObstacle->SetSIzeTexture(SetData.MaxLength);


    pObstacle->Init();

    // �擾
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // �ڂ�

    D3DXVECTOR3 SizeMag;

    //�T�C�Y�ϓ�
    SizeMag.x = EscData.MaxLength.x / 10.0f;
    SizeMag.y = EscData.MaxLength.y / 10.0f;
    SizeMag.z = EscData.MaxLength.z / 10.0f;

    pObstacle->SetSizeMag(SizeMag);//�{���ϓ�

    pObstacle->SetChangeColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f));

    pObstacle->SetDATA(EscData); // �i�[

     

    return pObstacle;
}




//=============================
// �����蔻��܂Ƃ�
//=============================
void CStageCollisionBox3D2D::HitCollision()
{

}
// ���b�V����UV���W���X�P�[�����O����֐�
LPD3DXMESH CStageCollisionBox3D2D::ScaleMeshUVs(LPD3DXMESH pMesh, float uScale, float vScale)
{
    
    struct Vertex
    {
        D3DXVECTOR3 position;
        D3DXVECTOR3 normal;
        float u, v;
    };

    Vertex* pVertices = nullptr;
    pMesh->LockVertexBuffer(0, (void**)&pVertices);

    // ���b�V���̒��_�����擾
    DWORD numVertices = pMesh->GetNumVertices();

    // �e���_��UV���W���X�P�[�����O
    for (DWORD i = 0; i < numVertices; ++i)
    {
        pVertices[i].u *= uScale;  // �������̃X�P�[��
        pVertices[i].v *= vScale;  // �c�����̃X�P�[��
    }

    // �o�b�t�@���A�����b�N
    pMesh->UnlockVertexBuffer();

    return pMesh;
}

void CStageCollisionBox3D2D::SetSIzeTexture(D3DXVECTOR3 TexSize)
{
    m_TexSize = TexSize;
}
