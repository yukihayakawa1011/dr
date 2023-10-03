//============================
//
//�p�[�e�B�N������(particle.h)
//Author:���� �F�M
//
//============================
#ifndef _PARTICLE_H_   //���̃}�N����`������Ă��Ȃ�������
#define _PARTICLE_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "bilboard.h"

//�}�N����`
#define MAX_PARTICLE (128)		//�p�[�e�B�N���ő吔
#define USE_PARTICLE (20)		//�g�p���Ă���p�[�e�B�N����
#define USE_RADIUS	 (10.0f)		//�g�����a

class CParticle : public CBilboard
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_DAMAGE,		//�_���[�W
		TYPE_WINDOW,		//�K���X
		TYPE_MAX
	}TYPE;

	CParticle();
	CParticle(D3DXVECTOR3 pos);
	~CParticle();

	static void *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nLife;																								//�̗�
	static void ParticleRed(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife);		//�Ԃ��p�[�e�B�N��
	static void ParticleWindow(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife);		//�K���X�p�[�e�B�N��

	static CEffect *pEffect;

};


#endif




