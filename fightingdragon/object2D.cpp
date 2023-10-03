//============================
//
//�I�u�W�F�N�g2D����(object2D.cpp)
//Author:���� �F�M
//
//============================
#include "object2D.h"
#include "manager.h"
#include "anim.h"
#include "bg.h"
#include "renderer.h"

//�ÓI�����o�ϐ��錾
CObject2D *CObject2D::m_apObject[320];

//============================
//�R���X�g���N�^
//============================
CObject2D::CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu���N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ��ʂ��N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�X�����N���A
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);				//�F���N���A
	m_nLife = 0;
}

//============================
//�f�X�g���N�^
//============================
CObject2D::~CObject2D()
{

}

//============================
//��������
//============================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CObject2D *pObject2D;

	//�I�u�W�F�N�g2D�̐���
	pObject2D = NEW_DBG CObject2D;

	//����������
	pObject2D->Init(D3DXVECTOR3(pos.x,pos.y,pos.z),fRot,nTex,fWidth,fHeight);

	return pObject2D;
}

//============================
//�|���S���̏�����
//============================
HRESULT CObject2D::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@��NULL��������
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//�e�N�X�`���̃|�C���^��NULL��������
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//rhw(�@��)�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}
//============================
//�|���S���̍X�V
//============================
void CObject2D::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_pos.x, pos.y - m_pos.y, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_pos.x, pos.y - m_pos.y, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_pos.x, pos.y + m_pos.y, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_pos.x, pos.y + m_pos.y, m_pos.z);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	SetPosition(pos);
}
//============================
//�|���S���̕`��
//============================
void CObject2D::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}

//============================
//�ʒu���Z�b�g����
//============================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//�ړ��ʂ��Z�b�g����
//============================
void CObject2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================
//�X�����Z�b�g����
//============================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//�F���Z�b�g����
//============================
void CObject2D::SetCol(D3DXCOLOR col)
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
//���_�����Z�b�g����
//============================
void CObject2D::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
{
	m_pVtxBuff = Buff;
}

//============================
//�̗͂��Z�b�g����
//============================
void CObject2D::SetLife(int nLife)
{
	m_nLife = nLife;
}

//============================
//�ʒu�̎擾
//============================
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

//============================
//�ړ��ʂ̎擾
//============================
D3DXVECTOR3 CObject2D::GetMove(void)
{
	return m_move;
}

//============================
//�X���̎擾
//============================
D3DXVECTOR3 CObject2D::GetRot(void)
{
	return m_rot;
}

//============================
//�F�̎擾
//============================
D3DXCOLOR CObject2D::GetCol(void)
{
	return m_col;
}

//============================
//���_�̎擾
//============================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetBuff(void)
{
	return m_pVtxBuff;
}

//============================
//�̗͎擾
//============================
int CObject2D::GetLife(void)
{
	return m_nLife;
}

//===================================
//�e�N�X�`���̊��蓖��
//===================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTextur)
{
	m_pTexture = pTextur;
}