//============================
//
//�I�u�W�F�N�gX����(objectx.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "objectx.h"
#include "input.h"
#include "renderer.h"
#include "objectx.h"

//�ÓI�����o�ϐ��錾
CObjectx::SET_OBJECTX CObjectx::Objectx[MAX_OBJECTX] = {};

//============================
//�R���X�g���N�^
//============================
CObjectx::CObjectx()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu���N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ��ʂ��N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�X�����N���A

	//m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);				//�F���N���A
	m_nLife = 0;

	m_nTexCnt = 0;		//�e�N�X�`�����̔ԍ����N���A

}

//============================
//�f�X�g���N�^
//============================
CObjectx::~CObjectx()
{

}

//============================
//��������
//============================
CObjectx *CObjectx::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CObjectx *pObjectx;

	//�I�u�W�F�N�g2D�̐���
	pObjectx = NEW_DBG CObjectx;

	//����������
	pObjectx->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex, fWidth, fHeight);

	return pObjectx;
}

//====================
//���f���̏�����
//====================
HRESULT CObjectx::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	int nNumVtx;  //���_��

	DWORD dwSizeFVF;  //���_�t�H�[�}�b�g�̃T�C�Y

	BYTE *pVtxBUff;  //���_�o�b�t�@�̃|�C���^

	if (nTex == 0)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\wall.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[0].m_pBuffMat,
			NULL,
			&Objectx[0].m_dwNumMat,
			&Objectx[0].m_pMesh);
	}

	if (nTex == 1)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\floor.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[1].m_pBuffMat,
			NULL,
			&Objectx[1].m_dwNumMat,
			&Objectx[1].m_pMesh);
	}

	if (nTex == 2)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\long_Floor.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[2].m_pBuffMat,
			NULL,	 
			&Objectx[2].m_dwNumMat,
			&Objectx[2].m_pMesh);
	}

	if (nTex == 3)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\escape_door.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[3].m_pBuffMat,
			NULL,
			&Objectx[3].m_dwNumMat,
			&Objectx[3].m_pMesh);
	}

	if (nTex == 4)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data\\MODEL\\window.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[4].m_pBuffMat,
			NULL,
			&Objectx[4].m_dwNumMat,
			&Objectx[4].m_pMesh);
	}

	D3DXMATERIAL *pMat; //�}�e���A���ւ̃|�C���^

	if (Objectx[nTex].m_pBuffMat != NULL)
	{
		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)Objectx[nTex].m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)Objectx[nTex].m_dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//�e�N�X�`���t�@�C���l�[�������݂���
			 //�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&Objectx[nTex].m_apTexture[nCntMat]);
			}
		}
	}

	SetPosition(pos);

	if (Objectx[nTex].m_pMesh != NULL)
	{

		//���_���̎擾
		nNumVtx = Objectx[nTex].m_pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		dwSizeFVF = D3DXGetFVFVertexSize(Objectx[nTex].m_pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		Objectx[nTex].m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

			if (vtx.x > Objectx[nTex].m_VtxMax.x)
			{
				Objectx[nTex].m_VtxMax.x = vtx.x;
			}

			if (vtx.x < Objectx[nTex].m_VtxMin.x)
			{
				Objectx[nTex].m_VtxMin.x = vtx.x;
			}

			if (vtx.y > Objectx[nTex].m_VtxMax.y)
			{
				Objectx[nTex].m_VtxMax.y = vtx.y;
			}

			if (vtx.y < Objectx[nTex].m_VtxMin.y)
			{
				Objectx[nTex].m_VtxMin.y = vtx.y;
			}

			if (vtx.z > Objectx[nTex].m_VtxMax.z)
			{
				Objectx[nTex].m_VtxMax.z = vtx.z;
			}

			if (vtx.z < Objectx[nTex].m_VtxMin.z)
			{
				Objectx[nTex].m_VtxMin.z = vtx.z;
			}

			pVtxBUff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���ڂ����i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		Objectx[nTex].m_pMesh->UnlockVertexBuffer();
	}

	//���f���̕��E�������Z�b�g
	SetVtxMax(Objectx[nTex].m_VtxMax);
	SetVtxMin(Objectx[nTex].m_VtxMin);

	//���Ԗڂ��̃I�u�W�F�N�g����m�点��
	m_Objectx = Objectx[nTex];

	m_nTexCnt = nTex;

	return S_OK;
}

//���f���̏I������
void CObjectx::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTX; nCnt++)
	{
		for (int nCntMat = 0; nCntMat < (int)Objectx[m_nTexCnt].m_dwNumMat; nCntMat++)
		{
			//�e�N�X�`���̔j��
			if (Objectx[nCnt].m_apTexture[nCntMat] != NULL)
			{
				Objectx[nCnt].m_apTexture[nCntMat]->Release();
				Objectx[nCnt].m_apTexture[nCntMat] = NULL;
			}
		}

		//���b�V���̔j��
		if (Objectx[nCnt].m_pMesh != NULL)
		{	  		
			Objectx[nCnt].m_pMesh->Release();
			Objectx[nCnt].m_pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (Objectx[nCnt].m_pBuffMat != NULL)
		{			
			Objectx[nCnt].m_pBuffMat->Release();
			Objectx[nCnt].m_pBuffMat = NULL;
		}
	}
	CObject::Release();
}

//���f���̍X�V����
void CObjectx::Update(void)
{

}

//���f���̕`�揈��
void CObjectx::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;  //���݂̃}�e���A���ۑ��p

	D3DXMATERIAL *pMat;	  //�}�e���A���f�[�^�ւ̃|�C���^

	 //���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Objectx.m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_Objectx.m_mtxWorld,
		&m_Objectx.m_mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_Objectx.m_mtxWorld, &m_Objectx.m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Objectx.m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_Objectx.m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_Objectx.m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_Objectx.m_apTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		m_Objectx.m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//============================
//�ʒu���Z�b�g����
//============================
void CObjectx::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//�ړ��ʂ��Z�b�g����
//============================
void CObjectx::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================
//�X�����Z�b�g����
//============================
void CObjectx::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//�F���Z�b�g����
//============================
void CObjectx::SetCol(D3DXCOLOR col)
{
	m_col = col;

	//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	//pVtx[1].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	//pVtx[2].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	//pVtx[3].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();
}

////============================
////���_�����Z�b�g����
////============================
//void CObjectx::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
//{
//	
//}

//============================
//�̗͂��Z�b�g����
//============================
void CObjectx::SetLife(int nLife)
{
	m_nLife = nLife;
}

//============================
//���f���ő�l���Z�b�g����
//============================
void CObjectx::SetVtxMax(D3DXVECTOR3 VtxMax)
{
	m_Objectx.m_VtxMax = VtxMax;
}

//============================
//���f���ŏ��l���Z�b�g����
//============================
void CObjectx::SetVtxMin(D3DXVECTOR3 VtxMin)
{
	m_Objectx.m_VtxMin = VtxMin;
}


//============================
//�ʒu�̎擾
//============================
D3DXVECTOR3 CObjectx::GetPosition(void)
{
	return m_pos;
}

//============================
//�ړ��ʂ̎擾
//============================
D3DXVECTOR3 CObjectx::GetMove(void)
{
	return m_move;
}

//============================
//�X���̎擾
//============================
D3DXVECTOR3 CObjectx::GetRot(void)
{
	return m_rot;
}

//============================
//�F�̎擾
//============================
D3DXCOLOR CObjectx::GetCol(void)
{
	return m_col;
}

////============================
////���_�̎擾
////============================
//LPDIRECT3DVERTEXBUFFER9 CObjectx::GetBuff(void)
//{
//	
//}

//============================
//�̗͎擾
//============================
int CObjectx::GetLife(void)
{
	return m_nLife;
}

//============================
//�ő�l�̎擾
//============================
D3DXVECTOR3 CObjectx::GetVtxMax(void)
{
	return m_Objectx.m_VtxMax;
}

//============================
//�ŏ��l�̎擾
//============================
D3DXVECTOR3 CObjectx::GetVtxMin(void)
{
	return m_Objectx.m_VtxMin;
}


