//============================
//
//�����_���[����(renderer.h)
//Author:���� �F�M
//
//============================
#ifndef _RENDERER_H_   //���̃}�N����`������Ă��Ȃ�������
#define _RENDERER_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void);

private:
	LPDIRECT3D9				m_pD3D;				//Direct3D�̃I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9		m_pD3DDevice;		//Direct3D�f�o�C�X�̃|�C���^
};

#endif




