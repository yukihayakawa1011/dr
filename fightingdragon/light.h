//============================
//
//���C�g����(light.h)
//Author:���� �F�M
//
//============================
#ifndef _LIGHT_H_   //���̃}�N����`������Ă��Ȃ�������
#define _LIGHT_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"

#define MAX_LIGHT (3)		//���C�g�̍ő吔

class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	D3DLIGHT9 m_aLight[3];		//���C�g���

	D3DXVECTOR3 m_VecDir[3];		//�ݒ�p�����x�N�g��
};


#endif


