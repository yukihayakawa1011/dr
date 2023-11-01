//=============================================================================
//
// サウンド処理 (sound.h)
// Author : 早川　友貴
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

	// サウンド情報の構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	//曲の設定
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_SE_DAMAGE,		//ダメージ音声
		SOUND_LABEL_SE_TITLEENTER,	//タイトルエンター音
		SOUND_LABEL_SE_TUTORIALENTER, //チュートリアルエンター音
		SOUND_LABEL_SE_DEATH,		  //ゲームオーバー音
		SOUND_LABEL_SE_BALLHITVOICE,  //金的ヒットボイス
		SOUND_LABEL_SE_BALLHIT,  //金的ヒットオン
		SOUND_LABEL_SE_EYEHITVOICE,  //目つぶしヒットボイス
		SOUND_LABEL_SE_EYEHIT,  //目つぶしヒット音
		SOUND_LABEL_SE_KILL,  //倒した音
		SOUND_LABEL_SE_PUNCH,  //パンチ音
		SOUND_LABEL_SE_KICK,  //キック音
		SOUND_LABEL_SE_UNFAIR,  //unfair攻撃音
		SOUND_LABEL_SE_ATTACKVOICE,  //攻撃ボイス
		SOUND_LABEL_SE_EYEVOICE,  //攻撃ボイス
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
	static IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ


};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif
