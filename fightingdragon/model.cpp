//============================
//
//���f������(model.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "model.h"
#include "renderer.h"
#include "objectx.h"

//�ÓI�����o�ϐ��錾
CModel::SET_MODEL CModel::pModels[MAX_PART] = {};

//============================
//�R���X�g���N�^
//============================
CModel::CModel()
{
	//m_pMesh = NULL;								//���b�V��
	//m_pBuffMat = NULL;						//���_���̃}�e���A��
	//m_dwNumMat = 0;								//�}�e���A��
												//D3DXMATRIX m_mtxWorld;							//���[���h�}�g���b�N�X
	for (int nCntIndx = 0; nCntIndx < MAX_PART; nCntIndx++)
	{
		m_nIdx = nCntIndx;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu���N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�X�����N���A

	m_Type = MODELTYPE_PLAYER;							//���f���̃^�C�v���N���A
}

//============================
//�f�X�g���N�^
//============================
CModel::~CModel()
{

}

//============================
//��������
//============================
CModel *CModel::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, int nType)
{
	CModel *pModel;

	//�I�u�W�F�N�g2D�̐���
	pModel = NEW_DBG CModel;

	//����������
	pModel->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex, fWidth, fHeight,nType);

	return pModel;
}

//====================
//���f���̏�����
//====================
HRESULT CModel::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, int nType)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	DWORD dwSizeFVF;  //���_�t�H�[�}�b�g�̃T�C�Y

	BYTE *pVtxBUff;  //���_�o�b�t�@�̃|�C���^

	int nNumVtx;  //���_��

	if (nType == 0)
	{
		m_Type = MODELTYPE_PLAYER;
	}
	if (nType == 1)
	{
		m_Type = MODELTYPE_ENEMY0;
	}
	if (nType == 2)
	{
		m_Type = MODELTYPE_ENEMY1;
	}
	if (nType == 3)
	{
		m_Type = MODELTYPE_ENEMY2;
	}

	if (m_Type == MODELTYPE_PLAYER)
	{
		if (nTex == 0)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\hip.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[0].m_pBuffMat,
				NULL,
				&pModels[0].m_dwNumMat,
				&pModels[0].m_pMesh);
		}

		if (nTex == 1)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\body.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[1].m_pBuffMat,
				NULL,
				&pModels[1].m_dwNumMat,
				&pModels[1].m_pMesh);
		}

		if (nTex == 2)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\head.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[2].m_pBuffMat,
				NULL,
				&pModels[2].m_dwNumMat,
				&pModels[2].m_pMesh);
		}

		if (nTex == 3)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\tigh_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[3].m_pBuffMat,
				NULL,
				&pModels[3].m_dwNumMat,
				&pModels[3].m_pMesh);
		}

		if (nTex == 4)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\leg_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[4].m_pBuffMat,
				NULL,
				&pModels[4].m_dwNumMat,
				&pModels[4].m_pMesh);
		}

		if (nTex == 5)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\shuuze_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[5].m_pBuffMat,
				NULL,
				&pModels[5].m_dwNumMat,
				&pModels[5].m_pMesh);
		}

		if (nTex == 6)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\tigh_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[6].m_pBuffMat,
				NULL,
				&pModels[6].m_dwNumMat,
				&pModels[6].m_pMesh);
		}

		if (nTex == 7)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\leg_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[7].m_pBuffMat,
				NULL,
				&pModels[7].m_dwNumMat,
				&pModels[7].m_pMesh);
		}

		if (nTex == 8)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\shuuze_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[8].m_pBuffMat,
				NULL,
				&pModels[8].m_dwNumMat,
				&pModels[8].m_pMesh);
		}

		if (nTex == 9)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\shoulder_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[9].m_pBuffMat,
				NULL,
				&pModels[9].m_dwNumMat,
				&pModels[9].m_pMesh);
		}

		if (nTex == 10)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\arm_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[10].m_pBuffMat,
				NULL,
				&pModels[10].m_dwNumMat,
				&pModels[10].m_pMesh);
		}

		if (nTex == 11)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\arm2_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[11].m_pBuffMat,
				NULL,
				&pModels[11].m_dwNumMat,
				&pModels[11].m_pMesh);
		}

		if (nTex == 12)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\hand_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[12].m_pBuffMat,
				NULL,
				&pModels[12].m_dwNumMat,
				&pModels[12].m_pMesh);
		}

		if (nTex == 13)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\shoulder_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[13].m_pBuffMat,
				NULL,
				&pModels[13].m_dwNumMat,
				&pModels[13].m_pMesh);
		}

		if (nTex == 14)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\arm_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[14].m_pBuffMat,
				NULL,
				&pModels[14].m_dwNumMat,
				&pModels[14].m_pMesh);
		}

		if (nTex == 15)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\arm2_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[15].m_pBuffMat,
				NULL,
				&pModels[15].m_dwNumMat,
				&pModels[15].m_pMesh);
		}

		if (nTex == 16)
		{
			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX("data\\MODEL\\hand_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[16].m_pBuffMat,
				NULL,
				&pModels[16].m_dwNumMat,
				&pModels[16].m_pMesh);
		}
	}

	D3DXMATERIAL *pMat; //�}�e���A���ւ̃|�C���^

	
		if (pModels[nTex].m_pBuffMat != NULL)
		{
			//�}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)pModels[nTex].m_pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)pModels[nTex].m_dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//�e�N�X�`���t�@�C���l�[�������݂���
				 //�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&pModels[nTex].m_apTexture[nCntMat]);
				}
			}
		}

	SetPos(pos);

		if (pModels[nTex].m_pMesh != NULL)
		{
			//���_���̎擾
			nNumVtx = pModels[nTex].m_pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			dwSizeFVF = D3DXGetFVFVertexSize(pModels[nTex].m_pMesh->GetFVF());

			//���_�o�b�t�@�����b�N
			pModels[nTex].m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

				if (vtx.x > pModels[nTex].m_VtxMax.x)
				{
					pModels[nTex].m_VtxMax.x = vtx.x;
				}

				if (vtx.x < pModels[nTex].m_VtxMin.x)
				{
					pModels[nTex].m_VtxMin.x = vtx.x;
				}

				if (vtx.y > pModels[nTex].m_VtxMax.y)
				{
					pModels[nTex].m_VtxMax.y = vtx.y;
				}

				if (vtx.y < pModels[nTex].m_VtxMin.y)
				{
					pModels[nTex].m_VtxMin.y = vtx.y;
				}

				if (vtx.z > pModels[nTex].m_VtxMax.z)
				{
					pModels[nTex].m_VtxMax.z = vtx.z;
				}

				if (vtx.z < pModels[nTex].m_VtxMin.z)
				{
					pModels[nTex].m_VtxMin.z = vtx.z;
				}

				pVtxBUff += dwSizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���ڂ����i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			pModels[nTex].m_pMesh->UnlockVertexBuffer();
		}

		//���f���̏���n��
		nModel = nTex;

		//���f���̕��E�������Z�b�g
		SetVtxMax(pModels[nModel].m_VtxMax);
		SetVtxMin(pModels[nModel].m_VtxMin);

		SetBuffMat(pModels[nModel].m_pBuffMat);

		//���L�̃f�[�^�������p��
		Model = pModels[nTex];

	return S_OK;
}

//���f���̏I������
void CModel::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		//���b�V���̔j��
		if (pModels[nCnt].m_pMesh != NULL)
		{
			pModels[nCnt].m_pMesh->Release();
			pModels[nCnt].m_pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (pModels[nCnt].m_pBuffMat != NULL)
		{
			pModels[nCnt].m_pBuffMat->Release();
			pModels[nCnt].m_pBuffMat = NULL;
		}
	}
}

//���f���̍X�V����
void CModel::Update(void)
{
	SetPos(m_pos);

	////���ړ�
	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	if (GetKeyboardPress(DIK_D) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.25f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.25f * D3DX_PI) * 1.0f;
	//	}

	//	else if (GetKeyboardPress(DIK_A) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.25f * -D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.25f * -D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.0f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.0f * D3DX_PI) * 1.0f;
	//	}
	//}

	////��O�ړ�
	//else if (GetKeyboardPress(DIK_S) == true)
	//{
	//	if (GetKeyboardPress(DIK_D) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.75f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.75f * D3DX_PI) * 1.0f;
	//	}

	//	else if (GetKeyboardPress(DIK_A) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.75f * -D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.75f * -D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 1.0f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 1.0f * D3DX_PI) * 1.0f;
	//	}
	//}

	////���ړ�
	//else if (GetKeyboardPress(DIK_A) == true)
	//{
	//	g_posModel.x -= sinf(g_rotModel.x + 0.5f * D3DX_PI) * 1.0f;
	//	g_posModel.z -= cosf(g_rotModel.z + 0.5f * D3DX_PI) * 1.0f;
	//}

	////�E�ړ�
	//else if (GetKeyboardPress(DIK_D) == true)
	//{
	//	g_posModel.x += sinf(g_rotModel.x + 0.5f * D3DX_PI) * 1.0f;
	//	g_posModel.z += cosf(g_rotModel.z + 0.5f * D3DX_PI) * 1.0f;
	//}

	////��ړ�
	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_posModel.y += 0.4f;
	//}

	////���ړ�
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_posModel.y -= 0.4f;
	//}
}

//���f���̕`�揈��
void CModel::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�S���f��[�p�[�c]�̕`��
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;  //���݂̃}�e���A���ۑ��p

	D3DXMATERIAL *pMat;	  //�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&Model.m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&Model.m_mtxWorld,
		&Model.m_mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&Model.m_mtxWorld, &Model.m_mtxWorld, &mtxTrans);

	//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
	if (m_pParent != NULL)
	{//�e���f��������ꍇ
		Model.m_mtxParent = m_pParent->GetMtxWorld();  //�e�C���f�b�N�X���擾
	}

	else
	{//�e���f�����Ȃ��ꍇ
	 //���݂̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &Model.m_mtxParent); //�v���C���[�̃}�g���b�N�X��ݒ�
	}

	//�݂��o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&Model.m_mtxWorld,
		&Model.m_mtxWorld,
		&Model.m_mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &Model.m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)Model.m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)Model.m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, Model.m_apTexture[nCntMat]);

		//���f��(�p�[�c)�̕`��
		Model.m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//���f���̕`�揈��
void CModel::DrawCol(D3DXCOLOR col)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�S���f��[�p�[�c]�̕`��
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;  //���݂̃}�e���A���ۑ��p

	D3DXMATERIAL *pMat;	  //�}�e���A���f�[�^�ւ̃|�C���^

	D3DXMATERIAL mat;

	ZeroMemory(&mat, sizeof(D3DXMATERIAL));
		
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&Model.m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&Model.m_mtxWorld,
			&Model.m_mtxWorld,
			&mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&Model.m_mtxWorld, &Model.m_mtxWorld, &mtxTrans);

		//�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (m_pParent != NULL)
		{//�e���f��������ꍇ
			Model.m_mtxParent = m_pParent->GetMtxWorld();  //�e�C���f�b�N�X���擾
		}

		else
		{//�e���f�����Ȃ��ꍇ
			//���݂̃}�g���b�N�X���擾����
			pDevice->GetTransform(D3DTS_WORLD, &Model.m_mtxParent); //�v���C���[�̃}�g���b�N�X��ݒ�
		}

		//�݂��o�����p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&Model.m_mtxWorld,
			&Model.m_mtxWorld,
			&Model.m_mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &Model.m_mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)Model.m_pBuffMat->GetBufferPointer();

		mat.MatD3D.Ambient = col;
		mat.MatD3D.Diffuse = col;
		//mat.MatD3D.Emissive = col;

		for (int nCntMat = 0; nCntMat < (int)Model.m_dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&mat.MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, Model.m_apTexture[nCntMat]);

			//���f��(�p�[�c)�̕`��
			Model.m_pMesh->DrawSubset(nCntMat);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
}

//========================
//�e���f���̐ݒ�
//========================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//========================
//�}�g���b�N�X����n��
//========================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return Model.m_mtxWorld;
}


//============================
//�ʒu���Z�b�g����
//============================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//�ړ��ʂ��Z�b�g����
//============================
void CModel::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================
//�X�����Z�b�g����
//============================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//���f���ő�l���Z�b�g����
//============================
void CModel::SetVtxMax(D3DXVECTOR3 VtxMax)
{
	Model.m_VtxMax = VtxMax;
}

//============================
//���f���ŏ��l���Z�b�g����
//============================
void CModel::SetVtxMin(D3DXVECTOR3 VtxMin)
{
	Model.m_VtxMin = VtxMin;
}

//============================
//���f���}�e���A�����Z�b�g����
//============================
void CModel::SetBuffMat(LPD3DXBUFFER Mat)
{
	Model.m_pBuffMat = Mat;
}

//============================
//���f���^�C�v���Z�b�g����
//============================
void CModel::SetModelType(MODELTYPE type)
{
	m_Type = type;
}

//============================
//�ʒu�̎擾
//============================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//============================
//�ړ��ʂ̎擾
//============================
D3DXVECTOR3 CModel::GetMove(void)
{
	return m_move;
}

//============================
//�X���̎擾
//============================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//============================
//�ő�l�̎擾
//============================
D3DXVECTOR3 CModel::GetVtxMax(void)
{
	return Model.m_VtxMax;
}

//============================
//�ŏ��l�̎擾
//============================
D3DXVECTOR3 CModel::GetVtxMin(void)
{
	return Model.m_VtxMin;
}

//============================
//�}�e���A�����̎擾
//============================
LPD3DXBUFFER CModel::GetBuffMat(void)
{
	return Model.m_pBuffMat;
}

//============================
//���f�����̎擾
//============================
CModel::SET_MODEL *CModel::GetModel(void)
{
	return &Model;
}


