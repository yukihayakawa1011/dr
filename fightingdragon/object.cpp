//============================
//
//�I�u�W�F�N�g����(object.cpp)
//Author:���� �F�M
//
//============================
#include "object.h"
#include "camera.h"
#include "debugproc.h"
#include "mode.h"
#include "pause.h"

//�ÓI�ϐ��錾
CObject *CObject::m_apObject[MAX_OBJECT];
int  CObject::m_nNumAll;
//============================
//�R���X�g���N�^
//============================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject <= MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		//�������g�����D
			m_nId = nCntObject;					//�������g��ID��ۑ�
			m_nNumAll++;						//�������J�E���g�A�b�v
			break;
		}
	}

	m_Type = TYPE_NONE;							//�^�C�v���N���A

}

//============================
//�R���X�g���N�^
//============================
CObject::CObject(TYPE type)
{
	SetType(type);
}

//============================
//�f�X�g���N�^
//============================
CObject::~CObject()
{

}

//============================
//�S�ẴI�u�W�F�N�g�̔j��
//============================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//============================
//�S�ẴI�u�W�F�N�g�̍X�V
//============================
void CObject::UpdateAll(void)
{
	/*CPause *pause;
	pause = NEW_DBG CPause;
	bool bPause = pause->GetPause();

	if (bPause == false)
	{*/
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntObject] != NULL)
			{
				m_apObject[nCntObject]->Update();
			}
		}
	/*}*/
	/*else
	{
		return;
	}*/
	
	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("�I�u�W�F�N�g�̑��� : %d\n", m_nNumAll);
#endif
}

//============================
//�S�ẴI�u�W�F�N�g�̕`��
//============================
void CObject::DrawAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}

//============================
//�I�u�W�F�N�g�̔j��
//============================
void CObject::Release(void)
{
	int nCnt = m_nId;

	if (m_apObject[nCnt] != NULL)
	{
		delete m_apObject[nCnt];

		m_apObject[nCnt] = NULL;

		m_nNumAll--;		//�������J�E���g�_�E��
	}
}

//==============================
//��ނ̐ݒ�
//==============================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}

//==============================
//��ނ̎擾
//==============================
CObject::TYPE CObject::GetType(void)
{
	return m_Type;
}

//���Ԗڂ̃I�u�W�F�N�g���w��
CObject *CObject:: GetObject(int nIdx)
{
	return m_apObject[nIdx];
}


