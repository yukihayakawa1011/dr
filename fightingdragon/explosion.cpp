//============================
//
//��������(bullet.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include"explosion.h"
//#include "bullet.h"
#include "renderer.h"

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9  CExplosion::m_pTexture;
//============================
//�R���X�g���N�^
//============================
CExplosion::CExplosion()
{
	m_nCounterAnim = 0;			//�A�j���[�V�����J�E���^�[�N���A
	m_nPatternAnim = 0;			//�A�j���[�V�����p�^�[���N���A

	m_pTexture = 0;								//�e�N�X�`��������

	m_nLife = 0;								//�̗̓N���A
}

CExplosion::CExplosion(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//�f�X�g���N�^
//============================
CExplosion::~CExplosion()
{

}

//============================
//�e�N�X�`���̐���(�ǂݍ���)
//============================
HRESULT CExplosion::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion.png",
		&m_pTexture);

	return S_OK;
}

//============================
//�e�N�X�`���̔j��
//============================
void CExplosion::Unload(void)
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CExplosion *pExplosion;

	//�I�u�W�F�N�g2D�̐���
	pExplosion = NEW_DBG CExplosion(pos);

	//����������
	pExplosion->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	//�e�N�X�`���̊��蓖��
	pExplosion->BindTexture(m_pTexture);

	return pExplosion;
}

//============================
//�|���S���̏�����
//============================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CBilboard::Init(pos, fRot, nTex,50.0f,50.0f);

	m_nLife = 80;

	//���_���̎󂯎��
	LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	/*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
	Buff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y + 50.0f, 0.0f);

	//rhw(�@��)�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	Buff->Unlock();

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CExplosion::Uninit(void)
{
	Release();
}
//============================
//�|���S���̍X�V
//============================
void CExplosion::Update(void)
{
	m_nLife--;

	DrawAnim();

	if (m_nLife < 0)
	{
		Release();
	}

}
//============================
//�|���S���̕`��
//============================
void CExplosion::Draw(void)
{
	CBilboard::Draw();
}

//�A�j���[�V����
void CExplosion::DrawAnim(void)
{
	//���_���̎󂯎��
	LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	Buff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu�����X�V
	/*g_posPlayer.x += g_movePlayer.x;*/

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[0].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[1].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[2].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[3].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[3].pos.z = 0.0f;

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(g_posPlayer.x - 100.0f, g_posPlayer.y - 100.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posPlayer.x + 100.0f, g_posPlayer.y - 100.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_posPlayer.x - 100.0f, g_posPlayer.y + 100.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_posPlayer.x + 100.0f, g_posPlayer.y + 100.0f, 0.0f);

	m_nCounterAnim++;			//�J�E���^�[�����Z

	if (m_nCounterAnim == 8)
	{
		m_nCounterAnim = 0;	//�J�E���^�[�������l�ɖ߂�

							/*g_nPatternAnimPlayer++;	*/	//�@�p�^�[��NO.���X�V����
		m_nPatternAnim = (m_nPatternAnim + 1) % 8;

		//�e�N�X�`�����W�̐ݒ�

		pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.125f, (m_nPatternAnim / 5) * 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f + (m_nPatternAnim % 5) * 0.125f, (m_nPatternAnim / 5) * 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.125f, 1.0f + (m_nPatternAnim / 5) * 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f + (m_nPatternAnim % 5) * 0.125f, 1.0f + (m_nPatternAnim / 5) * 0.0f);

		//���_�o�b�t�@���A�����b�N����
		Buff->Unlock();
	}
}

