//============================
//
//�J��������(camera.h)
//Author:���� �F�M
//
//============================
#ifndef _CAMERA_H_   //���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "manager.h"
#include "main.h"
//#include "object.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
private:
	D3DXMATRIX m_mtxView;			//�}�g���b�N�X�̃r���[
	D3DXMATRIX m_mtxProjection;		//�}�g���b�N�X�̃v���W�F�N�V����

	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_vecU;				//�����x�N�g��
	D3DXVECTOR3 m_rot;				//�X��

	float m_fAngle;					//�p�x
	float m_Length;					//����
};


#endif

