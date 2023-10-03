//============================
//
//���C�g����(light.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "light.h"
#include "renderer.h"
#include "debugproc.h"

//========================
//�R���X�g���N�^
//========================
CLight::CLight()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		m_VecDir[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//========================
//�f�X�g���N�^
//========================
CLight::~CLight()
{

}

//========================
//���C�g�̏���������
//========================
HRESULT CLight::Init(void)
{
	int nCnt;

	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		if (nCnt == 0)
		{
			//���C�g�̊g�U����ݒ�
			m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕������w��
			m_VecDir[nCnt] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}

		if (nCnt == 1)
		{
			//���C�g�̊g�U����ݒ�
			m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕������w��
			m_VecDir[nCnt] = D3DXVECTOR3(-0.2f, 0.9f, -0.4f);
		}

		if (nCnt == 2)
		{
			//���C�g�̊g�U����ݒ�
			m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕������w��
			m_VecDir[nCnt] = D3DXVECTOR3(0.9f, 0.1f, 0.4f);
		}

		D3DXVec3Normalize(&m_VecDir[nCnt], &m_VecDir[nCnt]); //�x�N�g���𐳋K������

		m_aLight[nCnt].Direction = m_VecDir[nCnt];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//======================
//���C�g�̏I������
//======================
void CLight::Uninit(void)
{

}

//==========================
//���C�g�̍X�V����
//==========================
void CLight::Update(void)
{
	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("\n���C�g�̌���0 X : %f Y : %f Z : %f\n", m_VecDir[0].x, m_VecDir[0].y, m_VecDir[0].z);
	pDebug->Print("���C�g�̌���1 X : %f Y : %f Z : %f\n", m_VecDir[1].x, m_VecDir[1].y, m_VecDir[1].z);
	pDebug->Print("���C�g�̌���2 X : %f Y : %f Z : %f\n", m_VecDir[2].x, m_VecDir[2].y, m_VecDir[2].z);
#endif

}