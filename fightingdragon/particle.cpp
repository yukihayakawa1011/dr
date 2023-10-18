//============================
//
//�G�t�F�N�g����(effect.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include"explosion.h"
#include "effect.h"
#include "particle.h"
#include "renderer.h"

//�ÓI�����o�ϐ��錾
CEffect *CParticle::pEffect = NULL;

//============================
//�R���X�g���N�^
//============================
CParticle::CParticle()
{

	m_nLife = 0;								//�̗̓N���A
}

//�I�[�o�[���[�h�R���X�g���N�^
CParticle::CParticle(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//�f�X�g���N�^
//============================
CParticle::~CParticle()
{

}


//============================
//��������
//============================
void *CParticle::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	switch (nTex)
	{
	case TYPE_DAMAGE:

		//�p�[�e�B�N��(�ԐF)
		ParticleRed(pos, D3DXVECTOR3(0.0f,300.0f,0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), 10.0f,200);

		////�p�[�e�B�N��(���F)
		//ParticleYellow();

		break;

	case TYPE_WINDOW:

		//�p�[�e�B�N��(�K���X)
		ParticleWindow(pos, D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 200);

		break;
	}

	return S_OK;
}

//============================
//�|���S���̏�����
//============================
HRESULT CParticle::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CBilboard::Init(pos, fRot, nTex, fWidth,fHeight);

	//��ނ�ݒ�
	SetType(CObject::TYPE_PARTICLE);

	////���_���̎󂯎��
	//LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

	//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//					/*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
	//Buff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y - 50.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y - 50.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y + 50.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y + 50.0f, 0.0f);

	////rhw(�@��)�̐ݒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////���_�o�b�t�@���A�����b�N����
	//Buff->Unlock();

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CParticle::Uninit(void)
{
	CBilboard::Release();
}
//============================
//�|���S���̍X�V
//============================
void CParticle::Update(void)
{

}

//============================
//�|���S���̕`��
//============================
void CParticle::Draw(void)
{
	/*CObject2D::Draw();*/
}

//=============================
//�p�[�e�B�N��(�ԐF)
//=============================
void CParticle::ParticleRed(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife)
{
	int nCntParticle = 0, nCntParticle1 = 0;

	//�p�[�e�B�N���̐���
	for (nCntParticle1 = 0; nCntParticle1 < USE_PARTICLE; nCntParticle1++)
	{
		//�ړ��ʂ̐ݒ�
		move.x = sinf(((float)(rand() % 629 - 400.0f)) / 200) * ((float)(rand() % 300) / 50.0f + 1.0f);
		move.y = cosf(((float)(rand() % 629 - 200)) / 200) * ((float)(rand() % 400) / 50.0f + 1.0f);

		//���_�J���[�̐ݒ�
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���a�̐ݒ�
		m_fRadius = USE_RADIUS;

		pEffect->Create(pos, 0.0f, 0,10.0f,10.0f,move * 10,col,nLife);
	}
}

//=============================
//�p�[�e�B�N��(�K���X)
//=============================
void CParticle::ParticleWindow(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife)
{
	int nCntParticle = 0, nCntParticle1 = 0;

	//�p�[�e�B�N���̐���
	for (nCntParticle1 = 0; nCntParticle1 < 4; nCntParticle1++)
	{
		//�ړ��ʂ̐ݒ�
		move.x = sinf(((float)(rand() % 629 - 250.0f)) / 200) * ((float)(rand() % 400) / 50.0f + 1.0f);
		move.y = cosf(((float)(rand() % 629 - 100.0f)) / 200) * ((float)(rand() % 400) / 50.0f + 1.0f);

		//���_�J���[�̐ݒ�
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���a�̐ݒ�
		m_fRadius = m_fRadius;

		pEffect->Create(D3DXVECTOR3(pos.x - 10.0f,pos.y + 40.0f,pos.z), 0.0f, 1, 30.0f, 30.0f, move * 2, col, nLife);
	}
}
