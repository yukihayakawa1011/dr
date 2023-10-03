//============================
//
//�r���{�[�h����(bilboard.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "renderer.h"
#include "bilboard.h"
//#include "bullet.h"
#include "debugproc.h"

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CBilboard::m_pTexture0 = NULL;


//========================
//�R���X�g���N�^
//========================
CBilboard::CBilboard()
{
	//m_mtxWorld = NULL;						//���[���h�}�g���b�N�X

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pTexture1 = 0;

	m_pVtxBuff = NULL;
}

//========================
//�f�X�g���N�^
//========================
CBilboard::~CBilboard()
{

}

//============================
//�e�N�X�`���̐���(�ǂݍ���)
//============================
HRESULT CBilboard::Load(void)
{
	////�f�o�C�X�̎擾
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//
	//	//�e�N�X�`���̓ǂݍ���
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\raginee.png",
	//		&m_pTexture0);
	//
	return S_OK;
}

//============================
//�e�N�X�`���̔j��
//============================
void CBilboard::Unload(void)
{
		//�e�N�X�`���̔j��
		if (m_pTexture0 != NULL)
		{
			m_pTexture0->Release();
			m_pTexture0 = NULL;
		}
}

//========================
//�N���G�C�g
//========================
CBilboard *CBilboard::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CBilboard *pBilboard;

	//�I�u�W�F�N�g2D�̐���
	pBilboard = NEW_DBG CBilboard;

	//����������
	pBilboard->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 0,fWidth,fHeight);

	/*for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{*/
		pBilboard->BindTexture(m_pTexture0);
	/*}*/

	return pBilboard;
}

//�|���S���̏���������
HRESULT CBilboard::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//��ނ�ݒ�
	SetType(CObject::TYPE_BILBOARD);

	//�e��ϐ��̏�����
	m_pos = pos; //�ʒu��������

	m_rot.x = fRot; //������������
	m_rot.y = fRot; //������������
	m_rot.z = fRot; //������������

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
	pVtx[0].pos = D3DXVECTOR3(-fWidth, + fHeight, 20.0f);
	pVtx[1].pos = D3DXVECTOR3(+fWidth, + fHeight, 20.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, - fHeight, 20.0f);
	pVtx[3].pos = D3DXVECTOR3(+fWidth, - fHeight, 20.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//�|���S���̏I������
void CBilboard::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture1 != NULL)
	{
		m_pTexture1->Release();
		m_pTexture1 = NULL;
	}

	Release();
}

//�|���S���̍X�V����
void CBilboard::Update(void)
{
	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetDebugProck();

	//int nCnt = CBullet::GetNumAllBullet();

#ifdef _DEBUG
	//�e�̑������f�o�b�O�\��
	//pDebug->Print("�e�̑��� : %d\n", nCnt);
#endif
}

//�|���S���̕`�揈��
void CBilboard::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans; 

	//�r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //�t�s������߂�

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

		pDevice->SetTexture(0, m_pTexture1);

		//�r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//============================
//�ʒu���Z�b�g����
//============================
void CBilboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//�ړ��ʂ��Z�b�g����
//============================
void CBilboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//===========================
//���_�����Z�b�g
//===========================
void CBilboard::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
{
	m_pVtxBuff = Buff;
}

//============================
//�X�����Z�b�g����
//============================
void CBilboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//�F���Z�b�g����
//============================
void CBilboard::SetCol(D3DXCOLOR col)
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

//============================
//�ʒu�̎擾
//============================
D3DXVECTOR3 CBilboard::GetPosition(void)
{
	return m_pos;
}

//============================
//�ړ��ʂ̎擾
//============================
D3DXVECTOR3 CBilboard::GetMove(void)
{
	return m_move;
}

//============================
//���_���̎擾
//============================
LPDIRECT3DVERTEXBUFFER9 CBilboard::GetBuff(void)
{
	return m_pVtxBuff;
}

//============================
//�X���̎擾
//============================
D3DXVECTOR3 CBilboard::GetRot(void)
{
	return m_rot;
}

//============================
//�F�̎擾
//============================
D3DXCOLOR CBilboard::GetCol(void)
{
	return m_col;
}

//===================================
//�e�N�X�`���̊��蓖��
//===================================
void CBilboard::BindTexture(LPDIRECT3DTEXTURE9 pTextur)
{
		m_pTexture1 = pTextur;
}
