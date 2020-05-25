;Por Siekmanski
Load_wav proc Wav_name:DWORD,pDSBuffer:DWORD
        LOCAL w_pDSSample:LPDIRECTSOUNDBUFFER8
        LOCAL dsbdesc:DSBUFFERDESC
        LOCAL hMmio:DWORD
        LOCAL WaveInfo:MMCKINFO
        LOCAL ChunkInfo:MMCKINFO
        LOCAL wfx:WAVEFORMATEX
        LOCAL S_data:DWORD
        LOCAL S_lengte:DWORD

        mov			eax,pDSBuffer	; get the soundbuffer adres
        mov			eax,[eax]
        mov			w_pDSSample,eax ; save adres

        SAFE_RELEASE 	w_pDSSample ; release in case it is an old sample

        ;Open the WAV-file and get all info
        invoke	mmioOpen,Wav_name,NULL,MMIO_ALLOCBUF or MMIO_READ	; Open the WAV file
        .if (eax)
            mov		hMmio,eax
            mov		WaveInfo.fccType,"EVAW"	; WAVE header info
            invoke	mmioDescend,hMmio,addr WaveInfo,NULL,MMIO_FINDRIFF
            .if (eax)
                invoke	MessageBox,NULL,TEXT_("this is not a wav file..."),TEXT_("Wav read error"),MB_OK OR MB_ICONERROR
                jmp		Load_wav_error
            .endif
            mov		ChunkInfo.ckid," tmf"		; fmt  field in WAVE header
            invoke	mmioDescend,hMmio,addr ChunkInfo,addr WaveInfo,MMIO_FINDCHUNK
            .if (eax)
                invoke	MessageBox,NULL,TEXT_("FMT Chunk not found..."),TEXT_("Wav read error"),MB_OK OR MB_ICONERROR
                jmp		Load_wav_error
            .endif
            invoke	mmioRead,hMmio,addr wfx,ChunkInfo.ckSize	; read Wave Format Header
            .if (eax != ChunkInfo.ckSize)
                invoke	MessageBox,NULL,TEXT_("Wave Format Info Read Error..."),TEXT_("Wav read error"),MB_OK OR MB_ICONERROR
                jmp		Load_wav_error
            .endif
            invoke	mmioAscend,hMmio,addr ChunkInfo,NULL
            mov		ChunkInfo.ckid,"atad"	; Wave Data
            invoke	mmioDescend, hMmio,addr ChunkInfo,addr WaveInfo,MMIO_FINDCHUNK
            .if (eax)
                invoke	MessageBox,NULL,TEXT_("DATA Chunk not found..."),TEXT_("Wav read error"),MB_OK OR MB_ICONERROR
                jmp		Load_wav_error
            .endif


        ; Init a Directsound buffer with the Info we found in the Wav-file
        invoke		RtlZeroMemory,ADDR dsbdesc,sizeof dsbdesc
    mov			dsbdesc.dwSize,sizeof DSBUFFERDESC
    mov			dsbdesc.dwFlags,DSBCAPS_GLOBALFOCUS
        mov			eax,ChunkInfo.ckSize		; Wav-data size
        mov			dsbdesc.dwBufferBytes,eax
        lea			eax,wfx						; Wav-data format
        mov			dsbdesc.lpwfxFormat,eax
        lea			eax,dsbdesc.guid3DAlgorithm
        GUID_COPY	eax,GUID_(DS3DALG_DEFAULT)
        ; create the soundbuffer
        coinvoke	g_pDS,IDirectSound8,CreateSoundBuffer,addr dsbdesc,addr w_pDSSample,NULL 
        .if (eax != DS_OK)
            invoke	MessageBox, NULL, TEXT_("CreateSoundBuffer..."), TEXT_("DSound Error"),MB_OK OR MB_ICONERROR
            jmp		Load_wav_error
        .endif

        ; lock and get the adres of the soundbuffer
        coinvoke	w_pDSSample,IDirectSoundBuffer8,Lock,0,ChunkInfo.ckSize,addr S_data,addr S_lengte,NULL,0,0 
        .if (eax != DS_OK)
            invoke	MessageBox, NULL, TEXT_("Lock SoundBuffer..."), TEXT_("DSound Error"),MB_OK OR MB_ICONERROR
            jmp		Load_wav_error
        .endif

        ; Read the wave data into the soundbufffer
        invoke		mmioRead,hMmio,S_data,ChunkInfo.ckSize

        ; unlock the soundbuffer
        coinvoke	w_pDSSample,IDirectSoundBuffer8,Unlock,S_data,S_lengte,NULL,0 
        .if (eax != DS_OK)
            invoke	MessageBox, NULL, TEXT_("Unlock SoundBuffer..."), TEXT_("DSound Error"),MB_OK OR MB_ICONERROR
            jmp		Load_wav_error
        .endif
        ; set sample start position
        coinvoke	w_pDSSample,IDirectSoundBuffer8,SetCurrentPosition,0 
    .else
        invoke		MessageBox,NULL,TEXT_("wav file not found..."),TEXT_("Wav read error"),MB_OK OR MB_ICONERROR
        jmp			No_wav
    .endif
        xor			ecx,ecx
        xor			edx,edx
        mov			eax,wfx.nSamplesPerSec
        mov			cx,wfx.wBitsPerSample 
        mov			dx,wfx.nChannels

    invoke		wsprintf,addr String_buffer,TEXT_(" Rate: %d   BPS: %d   Channels: %d   Length: %d"),eax,ecx,edx,ChunkInfo.ckSize

        ;invoke		SetDlgItemText,dshWnd,101,addr String_buffer

        invoke		mmioClose,hMmio,NULL
        mov			eax,pDSBuffer
        mov			ecx,w_pDSSample
        mov			[eax],ecx		; save soundbuffer adres
        return		DS_OK
    Load_wav_error:
        invoke		mmioClose,hMmio,NULL
        SAFE_RELEASE 	w_pDSSample
    No_wav:
        ;invoke		SetDlgItemText,dshWnd,100,TEXT_(" no file loaded..")
        ;invoke		SetDlgItemText,dshWnd,101,TEXT_(" none..")
        mov			eax,pDSBuffer
        xor			ecx,ecx
        mov			[eax],ecx		; clear soundbuffer adres

        return		E_FAIL
Load_wav endp

StartDSound 	proc hwnd:DWORD,Mono_stereo:DWORD,Sample_rate:DWORD,Sample_bits:DWORD
    LOCAL		dsbdesc:DSBUFFERDESC
    LOCAL		wfx:WAVEFORMATEX
    LOCAL		g_pDSBPrimary:LPDIRECTSOUNDBUFFER8

    invoke		DirectSoundCreate,NULL,addr g_pDS,NULL
    .if (eax != DS_OK)
        invoke	MessageBox, NULL, TEXT_("DirectSoundCreate..."), TEXT_("DSound Error"),MB_OK OR MB_ICONERROR
        return	E_FAIL
    .endif

    coinvoke	g_pDS,IDirectSound8,SetCooperativeLevel,hwnd,DSSCL_PRIORITY 
    .if (eax != DS_OK)
        invoke	MessageBox, NULL, TEXT_("SetCooperativeLevel..."), TEXT_("DSound Error"),MB_OK OR MB_ICONERROR
        return	E_FAIL
    .endif

    invoke		RtlZeroMemory,ADDR dsbdesc,sizeof dsbdesc
    mov			dsbdesc.dwSize,sizeof DSBUFFERDESC
    mov			dsbdesc.dwFlags,DSBCAPS_PRIMARYBUFFER
    coinvoke	g_pDS,IDirectSound8,CreateSoundBuffer,addr dsbdesc,addr g_pDSBPrimary,NULL 
    .if (eax != DS_OK)
        invoke	MessageBox, NULL, TEXT_("CreateSoundBuffer..."), TEXT_("DSound Error"),MB_OK OR MB_ICONERROR
        return	E_FAIL
    .endif

    invoke		RtlZeroMemory,ADDR wfx,sizeof wfx
    mov			wfx.wFormatTag,WAVE_FORMAT_PCM 
    mov			eax,Mono_stereo
    mov			wfx.nChannels,ax
    mov			eax,Sample_bits
    mov			wfx.wBitsPerSample,ax 
    mul			Mono_stereo
    shr			eax,3
    mov			wfx.nBlockAlign,ax
    mov			ecx,Sample_rate
    mov			wfx.nSamplesPerSec,ecx
    mul			ecx
    mov			wfx.nAvgBytesPerSec,eax

    coinvoke 	g_pDSBPrimary,IDirectSoundBuffer8,SetFormat,addr wfx
    .if (eax != DS_OK)
        invoke		MessageBox, NULL, TEXT_("SetFormat Primary Buffer..."), TEXT_("DSound Error"),MB_OK OR MB_ICONERROR
        return	E_FAIL
    .endif

    SAFE_RELEASE g_pDSBPrimary

    return	DS_OK
StartDSound	endp

StopDSound 	proc
	SAFE_RELEASE 	g_pDSWavSample
	SAFE_RELEASE 	g_pDS

	return	0
StopDSound	endp