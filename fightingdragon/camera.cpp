//============================

//�J��������(camera.cpp)
//Author:���� �F�M

//============================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "debugproc.h"
#include "player.h"
#include "mode.h"

//�J�����̃��[�h(��)
typedef enum
{
	MODE_CAMV = 0,
	MODE_CAMR,
	MODE_CAMMAX
}MODE_CAM;

////�O���[�o���ϐ�
//Camera g_Camera; //�J�����̏��				
//MODE_CAM g_Mode;

//========================
//�R���X�g���N�^
//========================
CCamera::CCamera()
{
	//m_mtxView = NULL;			//�}�g���b�N�X�̃r���[
	//m_mtxProjection;		//�}�g���b�N�X�̃v���W�F�N�V����

	m_posV = D3DXVECTOR3(0.0f,0.0f,0.0f);				//���_�̃N���A
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�����_�̃N���A
	m_vecU = D3DXVECTOR3(0.0f,0.0f,0.0f);				//�����x�N�g���̃N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�X���̃N���A

	m_fAngle = 0.0f;
	m_Length = 0.0f;
}

//========================
//�f�X�g���N�^
//========================
CCamera::~CCamera()
{

}

//========================
//�J�����̏���������
//========================
HRESULT CCamera::Init(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	m_posV = D3DXVECTOR3(pos.x, pos.y, -500.0f);	//���_
	m_posR = D3DXVECTOR3(pos.x, pos.y, pos.z);      //�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		    //������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			   //����

	// //���_���Œ肷��ꍇ
	//m_fAngle = atan2f
	//(//�Ίp���̊p�x
	//	m_posR.x - m_posV.x,
	//	m_posV.z - m_posR.z
	//);

	//m_Length = sqrtf
	//(//�Ίp���̒���
	//	(m_posR.x - m_posV.x)* (m_posR.x - m_posV.x) +
	//	(m_posV.z - m_posR.z) * ( m_posV.z - m_posR.z)
	//) * 0.5f;

	return S_OK;
}

//======================
//�J�����̏I������
//======================
void CCamera::Uninit(void)
{

}

//==========================
//�J�����̍X�V����
//==========================
void CCamera::Update(void)
{
	/*D3DXVECTOR3 g_ModelPos = PosModel();*/

	/*CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();*/

	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	m_posV = D3DXVECTOR3(pos.x, pos.y + 25.0f, -500.0f); //���_
	m_posR = D3DXVECTOR3(pos.x, pos.y, pos.z);     //�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		   //������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			   //����

	////���ړ�
	//if (pInputKeyboard->GetPless(DIK_UP) == true)
	//{
	//	//���ړ�
	//	if (pInputKeyboard->GetPless(DIK_LEFTARROW) == true)
	//	{
	//		m_posV.x += sinf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//		m_posV.z += cosf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//		m_posR.x += sinf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//	}

	//	//�E�ړ�
	//	else if (pInputKeyboard->GetPless(DIK_RIGHTARROW) == true)
	//	{
	//		m_posV.x += sinf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//		m_posV.z += cosf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//		m_posR.x += sinf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		m_posV.z += cosf(m_rot.z + 0.0f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.0f * D3DX_PI) * 1.0f;
	//	}
	//}

	////��O�ړ�
	//else if (pInputKeyboard->GetPless(DIK_DOWNARROW) == true)
	//{
	//	//���ړ�
	//	if (pInputKeyboard->GetPless(DIK_LEFTARROW) == true)
	//	{
	//		m_posV.x += sinf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//		m_posV.z += cosf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//		m_posR.x += sinf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//	}

	//	//�E�ړ�
	//	else if (pInputKeyboard->GetPless(DIK_RIGHTARROW) == true)
	//	{

	//		m_posV.x += sinf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//		m_posV.x += sinf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		m_posV.z += cosf(m_rot.z + 1.0f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 1.0f * D3DX_PI) * 1.0f;
	//	}
	//}


	////���ړ�
	//else if (pInputKeyboard->GetPless(DIK_LEFTARROW) == true)
	//{
	//	m_posV.x += sinf(m_rot.z + 0.5f * -D3DX_PI) * 1.0f;
	//	m_posR.z += cosf(m_rot.z + 0.5f * -D3DX_PI) * 1.0f;
	//}

	////�E�ړ�
	//else if (pInputKeyboard->GetPless(DIK_RIGHTARROW) == true)
	//{
	//	m_posV.x += sinf(m_rot.z + 0.5f * D3DX_PI) * 1.0f;
	//	m_posR.z += cosf(m_rot.z + 0.5f * D3DX_PI) * 1.0f;
	//}

	////��ړ�
	//if (pInputKeyboard->GetPless(DIK_N) == true)
	//{
	//	m_posV.y -= 1.0f;
	//	m_posR.y -= 1.0f;
	//}

	////���ړ�
	//if (pInputKeyboard->GetPless(DIK_B) == true)
	//{
	//	m_posV.y += 1.0f;
	//	m_posR.y += 1.0f;

	//}

	////�����_�E�ړ�
	//if (pInputKeyboard->GetPless(DIK_L) == true)
	//{
	//	//�J���������b�N����Ă���ꍇ
	//	m_rot.y += 0.1f;
	//}

	////�����_���ړ�
	//if (pInputKeyboard->GetPless(DIK_K) == true)
	//{
	//	//�J���������b�N����Ă���ꍇ
	//	m_rot.y -= 0.1f;
	//}

	////�����_��ړ�
	//if (pInputKeyboard->GetPless(DIK_P) == true)
	//{
	//	//�J���������b�N����Ă���ꍇ
	//	m_posR.y += 1.0f;
	//}

	////�����_��ړ�
	//if (pInputKeyboard->GetPless(DIK_O) == true)
	//{
	//	//�J���������b�N����Ă���ꍇ
	//	m_posR.y -= 1.0f;
	//}

	////���[�h��ς��鏈��
	//if (GetKeyboardTrigger(DIK_I) == true)
	//{
	//	switch (g_Mode)
	//	{
	//	case 0:

	//		g_Mode = MODE_CAMR;

	//		break;

	//	case 1:

	//		g_Mode = MODE_CAMV;

	//		break;
	//	}
	//}


	////���[�h�I��
	//if (g_Mode == 0)
	//{//�������[�h��0�Ȃ�1�ɂ��鏈��
	// //y��(���_)�����b�N
	//	/*m_posR.x = m_posV.x + sinf(m_rot.y + D3DX_PI * m_fAngle) * m_Length;
	//	m_posR.y = 0.0f;
	//	m_posR.z = m_posV.z + cosf(m_rot.y + D3DX_PI* m_fAngle) * m_Length;*/
	//}

	//else
	//{//�������[�h��1�Ȃ�0�ɂ��鏈��
	// //y��(�����X)�����b�N
		//m_posV.x = m_posR.x - sinf(m_rot.y + D3DX_PI - m_fAngle) * m_Length;
		///*g_Camera.posV.y = 0.0f;*/
		//m_posV.z = m_posR.z - cosf(m_rot.y + D3DX_PI - m_fAngle) * m_Length;

	//	g_Camera.posR = D3DXVECTOR3(g_ModelPos.x, g_ModelPos.y, g_ModelPos.z);
	//}

		//�f�o�b�O�\���̏���n��
		CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
		//�J�����̈ʒu���f�o�b�O�\��
		pDebug->Print("�J�����̈ʒu X : %f Y : %f Z : %f\n", m_posV.x, m_posV.y, m_posV.z);

		//�J�����̒����_���f�o�b�O�\��
		pDebug->Print("�J�����̒����_ X : %f Y : %f Z : %f", m_posR.x, m_posR.y, m_posR.z);
#endif
}

//=======================
//�J�����̐ݒ�
//=======================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),  //����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, //��ʂ̃A�X�y�N�g��
		10.0f,  //Z�l�̍ŏ��l
		1000.0f); //Z�l�̍ő�l

	////�v���W�F�N�V�����}�g���b�N�X���쐬(���s���e)
	//D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
	//	8.0f, //��ʂ̕�
	//	1.0f, //��ʂ̍���
	//	10.0f,  //Z�l�̍ŏ��l
	//	1000.0f); //Z�l�̍ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,	  //���_
		&m_posR,   //�����_
		&m_vecU);  //������x�N�g��

						  //�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

////==========================
////�J�����̎��_�̏���n������
////===========================
//D3DXVECTOR3 Getposv(void)
//{
//	return g_Camera.posV;
//}
//
////============================
////�J�����̒����_�̏���n������
////===========================
//D3DXVECTOR3 Getposr(void)
//{
//	return g_Camera.posR;
//}
//
////============================
////�J�����̎��_�̏���n������
////===========================
//D3DXVECTOR3 Getrot(void)
//{
//	return g_Camera.rot;
//}