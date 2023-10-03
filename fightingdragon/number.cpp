//============================
//
//�i���o�[����(number.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "number.h"
#include "renderer.h"

//============================
//�R���X�g���N�^
//============================
CNumber::CNumber()
{

}

//============================
//�f�X�g���N�^
//============================
CNumber::~CNumber()
{

}

//============================
//��������
//============================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CNumber *pNumber;

	//�I�u�W�F�N�g2D�̐���
	pNumber = NEW_DBG CNumber;

	//����������
	pNumber->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pNumber;
}

//============================
//�|���S���̏�����
//============================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&m_pTexture);

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
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CNumber::Uninit(void)
{
	CObject2D::Release();
}
//============================
//�|���S���̍X�V
//============================
void CNumber::Update(void)
{
	//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//CNumber::DrawAnim();

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();
}
//============================
//�|���S���̕`��
//============================
void CNumber::Draw(void)
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

//�A�j���[�V����
void CNumber::DrawAnim(void)
{

}

