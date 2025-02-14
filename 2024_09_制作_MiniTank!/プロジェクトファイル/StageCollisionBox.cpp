//=========================================================
//
// StageCollisionBox[StageCollisionBox.cpp]
// Author seiya kagaya
//
//=========================================================
#include"StageCollisionBox.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
StageCollisionBox::StageCollisionBox(int nPriority) :CObjectX(nPriority)
{
}

//=============================
// �f�X�g���N�^
//=============================
StageCollisionBox::~StageCollisionBox()
{
}

//=============================
// ������
//=============================
HRESULT StageCollisionBox::Init()
{
    CObjectX::Init();

    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr; // Mesh�|�C���^
    LPD3DXBUFFER pBuffMat = nullptr; // �}�e���A���ւ̃|�C���^
    DWORD dwNumMat = 0; // �}�e���A���̐�

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    // �t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\DebugModel\\BOX.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    D3DXMATERIAL* pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

    //�e�N�X�`���ǂݍ���
    LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

    //�e�N�X�`���擾
    CAllTexture* pTexture = pManager->GetTexture();

    for (int nCntMat = 0; nCntMat < (int)dwNumMat; nCntMat++)
    {
        if (pMat[nCntMat].pTextureFilename != NULL)
        {
            int texIndex = pTexture->Regist(pMat[nCntMat].pTextureFilename, EscDevice);//�e�N�X�`���o�^

            m_ESCpTexture = pTexture->GetAddress(texIndex);

            BindTexture(m_ESCpTexture, nCntMat);//�ݒ�
        }
    }

    SetXfireData(pMesh, pBuffMat, dwNumMat); // �f�[�^�i�[

    SetObjectType(CObject::OBJECT_HITBOX);

    return S_OK;
}

//=============================
// �j��
//=============================
void StageCollisionBox::Uninit()
{
    CObjectX::Uninit();
}

//=============================
// �X�V
//=============================
void StageCollisionBox::Update()
{
}

//=============================
// �`��
//=============================
void StageCollisionBox::Draw()
{
    //debug���̂ݕ`��
#if _DEBUG
    
    SizeMagChangebool(true);
    SetColorChangeBool(true);
    CObjectX::Draw();

#else
#endif // _D
}

//=============================
// ����
//=============================
StageCollisionBox* StageCollisionBox::Create(DATA SetData)
{
    StageCollisionBox* pObstacle = new StageCollisionBox;

    pObstacle->Init();

    // �擾
    DATA EscData = pObstacle->GetDATA();
    EscData = SetData; // �ڂ�

    D3DXVECTOR3 SizeMag;

       //�T�C�Y�ϓ�
    SizeMag.x = EscData.MaxLength.x / (float)SIZE;
    SizeMag.y = EscData.MaxLength.y / (float)SIZE*2.0f;
    SizeMag.z = EscData.MaxLength.z / (float)SIZE;
    
    pObstacle->SetSizeMag(SizeMag);//�{���ϓ�

    pObstacle->SetChangeColor(D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.1f));

    pObstacle->SetDATA(EscData); // �i�[

    return pObstacle;
}

//=============================
// �����蔻��܂Ƃ�
//=============================
void StageCollisionBox::HitCollision()
{

}