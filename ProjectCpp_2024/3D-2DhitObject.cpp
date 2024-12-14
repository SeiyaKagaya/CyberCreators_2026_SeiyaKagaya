//=========================================================
//
// 2D-3DhitColision[2D-3DhitColision.cpp]
// Author seiya kagaya
//
//=========================================================
#include"3D-2DhitObject.h"
#include "manager.h"
#include "player_motion.h"
#include "enemy_motion_Nomal.h"





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

   // LPD3DXMESH pMesh = nullptr;
    LPD3DXBUFFER pBuffMat = nullptr;
    DWORD dwNumMat = 0;

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    
    const char* aData = {};

    switch (m_hitbox)
    {
    case TYPE_RIGHTSLOPE:
        aData = "DATA\\MODEL\\iwaR.x";
        break;
    
    case TYPE_LEFTSLOPE:
        aData = "DATA\\MODEL\\iwaL.x";
        break;

    case TYPE_NOMALBLOCK:
    
        aData = "DATA\\MODEL\\iwa.x";
        break;

    case TYPE_3DSTAGE:

        aData = "DATA\\MODEL\\iwa2.x";
        break;
    
    }

    // ���b�V���̓ǂݍ���
        D3DXLoadMeshFromX(aData,
            D3DXMESH_SYSTEMMEM,
            EscDevice,
            NULL,
            &pBuffMat,
            NULL,
            &dwNumMat,
            &m_pMesh);

    












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
    float VSize = m_TexSize.y / 150.0f;

    m_pMesh = ScaleMeshUVs(m_pMesh, USize,VSize);

    SetXfireData(m_pMesh, pBuffMat, dwNumMat);
    SetObjectType(CObject::OBJECT_HITBOX_2D3D);

    return S_OK;
}

//=============================
// �j��
//=============================
void CStageCollisionBox3D2D::Uninit()
{
    //if (m_pMesh != nullptr)
    //{
    //    delete m_pMesh;
    //    m_pMesh = nullptr;
    //}
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

//#if _DEBUG

    ChengeStageTex(true);
    SizeMagChangebool(true);
 //   SetColorChangeBool(true);
    CObjectX::Draw();
    ChengeStageTex(false);

//#else

//#endif // _D

}

//=============================
// ����
//=============================
CStageCollisionBox3D2D* CStageCollisionBox3D2D::Create(DATA SetData, HITBOX hitman)
{
    CStageCollisionBox3D2D* pObstacle = new CStageCollisionBox3D2D;

    pObstacle->SetSIzeTexture(SetData.MaxLength);

    pObstacle->SetType(hitman);
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




////=============================
//// �����蔻��܂Ƃ�
////=============================
//void CStageCollisionBox3D2D::HitCollision()
//{
//
//}
//=============================
// ���b�V����UV���W���X�P�[�����O����֐�
//=============================
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
//=============================
// �e�N�X�`���T�C�Y
//=============================
void CStageCollisionBox3D2D::SetSIzeTexture(D3DXVECTOR3 TexSize)
{
    m_TexSize = TexSize;
}
//=============================
// �^�C�v�i�[
//=============================
void CStageCollisionBox3D2D::SetType(HITBOX type)
{
    m_hitbox = type;
}
//=============================
// �^�C�v�擾
//=============================
CStageCollisionBox3D2D::HITBOX CStageCollisionBox3D2D::GetHitBoxType()
{
    return m_hitbox;
}
LPD3DXMESH CStageCollisionBox3D2D::GetMesh()
{
	return m_pMesh;
}


CMathProc::CollisionData CStageCollisionBox3D2D::bHitColision(D3DXVECTOR3 pos, D3DXVECTOR3 rayDirection, CObject::OBJECTTYPE MyType, void* pCaller)
{
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();
    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

    bool EscHit = false;
    CMathProc::CollisionData HitData;
    HitData.bHit = false;
    HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    HitData.targetIndex = -1;

    bool bLandingHit = false;

    CObject* pObject = CObject::GetpTop(LAYERINDEX_HITBOX_2D3D);
    int nIndex = 0;

    while (pObject != nullptr)
    {
        bool bSkip = false;

        // �I�u�W�F�N�g�^�C�v�̊m�F
        if (pObject->GetObjectType() == LAYERINDEX_HITBOX_2D3D)
        {
            CStageCollisionBox3D2D* pStageHitBox_2D3D = (CStageCollisionBox3D2D*)pObject;
            CObject::DATA EscData = pStageHitBox_2D3D->GetDATA();

            // �X���[�v�ȊO�̃I�u�W�F�N�g���X�L�b�v
            if (pStageHitBox_2D3D->GetHitBoxType() != CStageCollisionBox3D2D::TYPE_LEFTSLOPE)
            {
                bSkip = true;
            }

            if (!bSkip)
            {
                D3DXMATRIX matWorld;
                D3DXMatrixIdentity(&matWorld);

                // ���b�V���̃X�P�[�����O�Ɖ�]�E�ʒu��K�p
                D3DXMatrixScaling(&matWorld, pStageHitBox_2D3D->GetSizeMag().x, pStageHitBox_2D3D->GetSizeMag().y, pStageHitBox_2D3D->GetSizeMag().z);
                D3DXMatrixRotationYawPitchRoll(&matWorld, pStageHitBox_2D3D->GetDATA().rot.y, pStageHitBox_2D3D->GetDATA().rot.x, pStageHitBox_2D3D->GetDATA().rot.z);
                D3DXMatrixTranslation(&matWorld, pStageHitBox_2D3D->GetDATA().Pos.x, pStageHitBox_2D3D->GetDATA().Pos.y, pStageHitBox_2D3D->GetDATA().Pos.z);

                LPD3DXMESH pMesh;
                pStageHitBox_2D3D->GetMesh()->CloneMeshFVF(
                    D3DXMESH_MANAGED,
                    D3DFVF_XYZ | D3DFVF_NORMAL,
                    EscDevice,
                    &pMesh);

                // �Փˌ��o�p�̍ŒZ�����ƌ������̏�����
                float nearestDist = FLT_MAX;
                D3DXVECTOR3 hitPoint, hitNormal;
                BOOL hit = FALSE;
                DWORD faceIndex;
                FLOAT u, v, dist;

                if (SUCCEEDED(D3DXIntersect(pMesh, &pos, &rayDirection, &hit, &faceIndex, &u, &v, &dist, NULL, NULL)))
                {
                    if (hit && dist < nearestDist)
                    {
                        nearestDist = dist;
                        EscHit = true;
                        bLandingHit = true;

                        // ���[���h�s��̐ݒ�
                        D3DXMATRIX matScale, matRot, matTrans, matWorld;
                        D3DXMatrixScaling(&matScale, pStageHitBox_2D3D->GetSizeMag().x, pStageHitBox_2D3D->GetSizeMag().y, pStageHitBox_2D3D->GetSizeMag().z);
                        D3DXMatrixRotationYawPitchRoll(&matRot, pStageHitBox_2D3D->GetDATA().rot.y, pStageHitBox_2D3D->GetDATA().rot.x, pStageHitBox_2D3D->GetDATA().rot.z);
                        D3DXMatrixTranslation(&matTrans, pStageHitBox_2D3D->GetDATA().Pos.x, pStageHitBox_2D3D->GetDATA().Pos.y, pStageHitBox_2D3D->GetDATA().Pos.z);
                        matWorld = matScale * matRot * matTrans;

                        // �C���f�b�N�X�o�b�t�@�ƒ��_�o�b�t�@��������ʂ̒��_���W���擾
                        LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = nullptr;
                        LPDIRECT3DINDEXBUFFER9 pIndexBuffer = nullptr;
                        pMesh->GetVertexBuffer(&pVertexBuffer);
                        pMesh->GetIndexBuffer(&pIndexBuffer);

                        // �O�p�`�̒��_�C���f�b�N�X���擾
                        WORD* pIndices = nullptr;
                        pIndexBuffer->Lock(0, 0, (void**)&pIndices, D3DLOCK_READONLY);
                        WORD i0 = pIndices[faceIndex * 3 + 0];
                        WORD i1 = pIndices[faceIndex * 3 + 1];
                        WORD i2 = pIndices[faceIndex * 3 + 2];
                        pIndexBuffer->Unlock();

                        // �O�p�`�̒��_���W���擾
                        D3DXVECTOR3* pVertices = nullptr;
                        pVertexBuffer->Lock(0, 0, (void**)&pVertices, D3DLOCK_READONLY);
                        D3DXVECTOR3 v0 = pVertices[i0];
                        D3DXVECTOR3 v1 = pVertices[i1];
                        D3DXVECTOR3 v2 = pVertices[i2];
                        pVertexBuffer->Unlock();

                        // ���_���W�����[���h�s��ŕϊ�
                        D3DXVec3TransformCoord(&v0, &v0, &matWorld);
                        D3DXVec3TransformCoord(&v1, &v1, &matWorld);
                        D3DXVec3TransformCoord(&v2, &v2, &matWorld);

                        // �o�����G�[�V������ԂŐڐG�_���v�Z
                        D3DXVECTOR3 hitPoint = (1 - u - v) * v0 + u * v1 + v * v2;

                        // �@���x�N�g�����v�Z�i�N���X�ς�p����j
                        D3DXVECTOR3 edge1 = v1 - v0;
                        D3DXVECTOR3 edge2 = v2 - v0;
                        D3DXVECTOR3 hitNormal;
                        D3DXVec3Cross(&hitNormal, &edge1, &edge2);
                        D3DXVec3Normalize(&hitNormal, &hitNormal);

                        // �q�b�g�f�[�^�ɏ��𔽉f
                        HitData.bHit = true;
                        HitData.HitAngle = hitNormal;  // �q�b�g�p�x�Ƃ��Ė@����ݒ�
                        HitData.ResultDistance = hitPoint - pos;  // �ڐG�_�܂ł̃x�N�g��
                        HitData.targetIndex = nIndex;

                        // �㏈��
                        pVertexBuffer->Release();
                        pIndexBuffer->Release();
                    }
                }

                pMesh->Release();
            }
        }

        pObject = pObject->GetNext();
        nIndex++;
    }

    HitData.bHit = EscHit;
    if (bLandingHit)
    {
        HitData.HitAngle.y = 1;  // �K�v�ɉ�����Y���̊p�x���C��
    }

    return HitData;
}