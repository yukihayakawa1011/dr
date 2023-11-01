//=============================================================================
//
// �T�E���h���� (sound.h)
// Author : ����@�F�M
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "Manager.h"
#include "XAudio2.h"

class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h���̍\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

	//�Ȃ̐ݒ�
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_SE_DAMAGE,		//�_���[�W����
		SOUND_LABEL_SE_TITLEENTER,	//�^�C�g���G���^�[��
		SOUND_LABEL_SE_TUTORIALENTER, //�`���[�g���A���G���^�[��
		SOUND_LABEL_SE_DEATH,		  //�Q�[���I�[�o�[��
		SOUND_LABEL_SE_BALLHITVOICE,  //���I�q�b�g�{�C�X
		SOUND_LABEL_SE_BALLHIT,  //���I�q�b�g�I��
		SOUND_LABEL_SE_EYEHITVOICE,  //�ڂԂ��q�b�g�{�C�X
		SOUND_LABEL_SE_EYEHIT,  //�ڂԂ��q�b�g��
		SOUND_LABEL_SE_KILL,  //�|������
		SOUND_LABEL_SE_PUNCH,  //�p���`��
		SOUND_LABEL_SE_KICK,  //�L�b�N��
		SOUND_LABEL_SE_UNFAIR,  //unfair�U����
		SOUND_LABEL_SE_ATTACKVOICE,  //�U���{�C�X
		SOUND_LABEL_SE_EYEVOICE,  //�U���{�C�X
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	static HRESULT InitSound(HWND hWnd);
	static void UninitSound(void);
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);

private:
	
	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	static IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y


};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif
