//============================
//
//�I�u�W�F�N�g2D����(object2D.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "anim.h"
#include "renderer.h"

//============================
//�R���X�g���N�^
//============================
CAnim::CAnim()
{
	m_nCounterAnim = 0;			//�A�j���[�V�����J�E���^�[�N���A
	m_nPatternAnim = 0;			//�A�j���[�V�����p�^�[���N���A

	m_pos = 0.0f;
	m_move = 0.0f;
}

//============================
//�f�X�g���N�^
//============================
CAnim::~CAnim()
{

}

//============================
//��������
//============================
CAnim *CAnim::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CAnim *pAnim;

	//�I�u�W�F�N�g2D�̐���
	pAnim = NEW_DBG CAnim;

	//����������
	pAnim->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pAnim;
}

//============================
//�|���S���̏�����
//============================
HRESULT CAnim::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (nTex == 0)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\runningman100.png",
			&m_pTexture);
	}
	
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
	pVtx[0].pos = D3DXVECTOR3(pos.x - 100.0f, pos.y - 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 100.0f, pos.y - 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 100.0f, pos.y + 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 100.0f, pos.y + 100.0f, 0.0f);
	

	////�p�x�����߂�
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////�������Z�o����
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

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
	pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CAnim::Uninit(void)
{
	Release();
}
//============================
//�|���S���̍X�V
//============================
void CAnim::Update(void)
{
	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	CAnim::DrawAnim();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//============================
//�|���S���̕`��
//============================
void CAnim::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

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

//�A�j���[�V����
void CAnim::DrawAnim(void)
{
		VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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

		if (m_nCounterAnim == 5)
		{
			m_nCounterAnim = 0;	//�J�E���^�[�������l�ɖ߂�

								/*g_nPatternAnimPlayer++;	*/	//�@�p�^�[��NO.���X�V����
			m_nPatternAnim = (m_nPatternAnim + 1) % 10;

			//�e�N�X�`�����W�̐ݒ�

			pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.2f, (m_nPatternAnim / 5) * 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.2f + (m_nPatternAnim % 5) * 0.2f, (m_nPatternAnim / 5) * 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.2f, 0.5f + (m_nPatternAnim / 5) * 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.2f + (m_nPatternAnim % 5) * 0.2f, 0.5f + (m_nPatternAnim / 5) * 0.5f);

			//���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();
		}
}

