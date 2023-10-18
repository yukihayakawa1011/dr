//============================
//
//�|���S������(porygon.cpp)
//Author:���� �F�M
//
//============================
#include "object3d.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CObject3d::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CObject3d::m_pVtxBuff = NULL;
CObject3d *CObject3d::m_pObject[320] = {};

//========================
//�R���X�g���N�^
//========================
CObject3d::CObject3d()
{
	 //m_mtxWorld = NULL;						//���[���h�}�g���b�N�X

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_objectcol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_TimeBlinking = 0;

	//m_bShowEnemy = true;
}

//========================
//�f�X�g���N�^
//========================
CObject3d::~CObject3d()
{

}

//============================
//�e�N�X�`���̐���(�ǂݍ���)
//============================
HRESULT CObject3d::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	return S_OK;
}

//============================
//�e�N�X�`���̔j��
//============================
void CObject3d::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//========================
//�N���G�C�g
//========================
CObject3d *CObject3d::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CObject3d *pObject3D;

	//�I�u�W�F�N�g2D�̐���
	pObject3D = NEW_DBG CObject3d;

	//����������
	pObject3D->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f,0, fWidth, fHeight);

	return pObject3D;
}

 //�|���S���̏���������
HRESULT CObject3d::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (nTex == 0)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\black.jpg",
			&m_pTexture);
	}

	//�e��ϐ��̏�����
	m_pos = pos; //�ʒu��������
	
	m_rot.x = fRot; //������������
	m_rot.y = fRot; //������������
	m_rot.z = fRot; //������������

	/*m_bShowEnemy = true;*/

	m_objectcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_TimeBlinking = 600;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^

	 //���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, + pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, + pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, - pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, - pos.z);

	D3DXVECTOR3 vec0 = D3DXVECTOR3(0, 0.0, 0.0f) - D3DXVECTOR3(0.0f, 0.0f,0.0f);
	D3DXVECTOR3 vec1 = D3DXVECTOR3(200, 0.0, + 100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec2 = D3DXVECTOR3(- 200, 0.0,+ 100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 nor;
	//float fheight;		//���߂鍂��

	//�ӂ��̃x�N�g������@�������߂�
	D3DXVec3Cross(&nor,
		&vec1,
		&vec2);

	//�@���𐳋K������
	D3DXVec3Normalize(&nor, &nor);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	pVtx[1].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	pVtx[2].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	pVtx[3].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
	pVtx[1].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
	pVtx[2].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
	pVtx[3].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�F���Z�b�g����
	SetColor(m_objectcol);

	//SetShowEnemy(m_bShowEnemy);

	return S_OK;
}

//�|���S���̏I������
void CObject3d::Uninit(void)
{
	Release();
}

//�|���S���̍X�V����
void CObject3d::Update(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx; //���_���W�ւ̃|�C���^

	//���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�F�𖾂��n��
	m_objectcol = GetColor();

	/*if (m_objectcol.a < 1.0f || m_objectcol.a > 0.0f)
	{*/
		
			m_TimeBlinking--;

			/*m_bShowEnemy = false;

			SetShowEnemy(m_bShowEnemy);*/

			//��莞�ԂŔ�������
			if (m_TimeBlinking == 50)
			{
				//����������
				m_objectcol.a = 1.1f;

				CSound::PlaySound(CSound::SOUND_LABEL_SE_THUNDER);
			}

			if (m_TimeBlinking < 0)
			{//���Ԃ��������烊�Z�b�g
				m_TimeBlinking = 600;
			}
			else if (m_TimeBlinking <= 50)
			{//�����Ă��烊�Z�b�g�܂ł̊�

				//���X�ɔ�������
				m_objectcol.a -= 0.02f;

			/*	m_bShowEnemy = true;

				SetShowEnemy(m_bShowEnemy);*/
			}
			else
			{//����ȊO�͌����Ȃ�����
				m_objectcol.a = 0.0f;
			}
		
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
		pVtx[1].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
		pVtx[2].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
		pVtx[3].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);

		SetColor(m_objectcol);
	/*}*/
}

//�|���S���̕`�揈��
void CObject3d::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}

//============================
//�ʒu���Z�b�g����
//============================
void CObject3d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//============================
//�ʒu�̎擾
//============================
D3DXVECTOR3 CObject3d::GetPosition(void)
{
	return m_pos;
}

//============================
//�ړ��ʂ̎擾
//============================
D3DXVECTOR3 CObject3d::GetMove(void)
{
	return m_move;
}

//===================================
//�v���C���[�̍�����m�邽�߂̏���
//===================================
float CObject3d::GetHeight(D3DXVECTOR3 pos)
{

	D3DXVECTOR3 vec0 = D3DXVECTOR3(0, 0.0, 0.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec1 = D3DXVECTOR3(200, 0.0, +100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec2 = D3DXVECTOR3(-200, 0.0, +100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 nor;
	float fheight = 0.0f;		//���߂鍂��

	//���ς̏���
	fheight = (pos.x - vec0.x *  nor.x) + (fheight - vec0.y  * nor.y) + (pos.z - vec0.z  * nor.z);

	if (fheight != 0.0f)
	{
		fheight = pos.y;
	}
	return fheight;
}

//===================================
//�F��n������
//===================================
D3DXCOLOR CObject3d::GetColor(void)
{
	return m_objectcol;
}

//===================================
//�F���Z�b�g���鏈��
//===================================
void CObject3d::SetColor(D3DXCOLOR col)
{
	m_objectcol = col;
}

////===================================
////�G�̎p���f������n������
////===================================
//bool CObject3d::GetShowEnemy(void)
//{
//	return m_bShowEnemy;
//}
//
////===================================
////�F���Z�b�g���鏈��
////===================================
//void CObject3d::SetShowEnemy(bool ShowEnemy)
//{
//	m_bShowEnemy = ShowEnemy;
//}
//
//
//
//
