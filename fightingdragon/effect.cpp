//============================
//
//�G�t�F�N�g����(effect.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include"explosion.h"
#include "effect.h"
#include "renderer.h"

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9  CEffect::m_pTexture = NULL;
//============================
//�R���X�g���N�^
//============================
CEffect::CEffect()
{
	m_nLife = 0;								//�̗̓N���A

	m_fRadius = 0;								//���a���N���A
}

//�I�[�o�[���[�h�R���X�g���N�^
CEffect::CEffect(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//�f�X�g���N�^
//============================
CEffect::~CEffect()
{

}

////============================
////�e�N�X�`���̐���(�ǂݍ���)
////============================
//HRESULT CEffect::Load(int nTex)
//{
//	//�f�o�C�X�̎擾
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//	
//	
//
//	return S_OK;
//}

//============================
//�e�N�X�`���̔j��
//============================
void CEffect::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}


//============================
//��������
//============================
CEffect *CEffect::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	CEffect *pEffect;

	//�I�u�W�F�N�g2D�̐���
	pEffect = NEW_DBG CEffect(pos);

	//����������
	pEffect->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight,move,col,nLife);

	//�e�N�X�`���̊��蓖��
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}

//============================
//�|���S���̏�����
//============================
HRESULT CEffect::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (nTex == 0)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\effect000.jpg",
			&m_pTexture);
	}

	if (nTex == 1)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\brake_Window.png",
			&m_pTexture);
	}

	SetCol(col);

	CBilboard::Init(pos, fRot, nTex, fWidth,fHeight);

	//��ނ�ݒ�
	SetType(CObject::TYPE_EFFECT);

	m_nLife = nLife;

	m_fRadius = 6.0f;

	//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	///*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y + m_fRadius, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y + m_fRadius, 0.0f);

	////rhw(�@��)�̐ݒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();

	m_move = move;

	SetCol(col);

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CEffect::Uninit(void)
{
	CBilboard::Release();
}
//============================
//�|���S���̍X�V
//============================
void CEffect::Update(void)
{
	//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	D3DXCOLOR col = GetCol();

	D3DXVECTOR3 pos = GetPosition();

	///*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y + m_fRadius, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y + m_fRadius, 0.0f);

	////rhw(�@��)�̐ݒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	////���_�J���[�̐ݒ�
 // 	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();

	pos += m_move;

	SetPosition(pos);

	//�G�t�F�N�g�̗̑͂����炷
	m_nLife--;

	//�G�t�F�N�g�̃��l�����炷
	col.a -= 0.1f;

	//���a�����������Ă���
	m_fRadius -= 2.0f;

	SetCol(col);

	//�̗͂��Ȃ��Ȃ��������
	if (m_nLife < 0 || m_fRadius < 0)
	{
		Release();
	}

}
//============================
//�|���S���̕`��
//============================
void CEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�I�u�W�F�N�g�̕`��
	CBilboard::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

