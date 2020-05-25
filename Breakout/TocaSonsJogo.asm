Parede proc
    push eax
    push ebx
    push ecx
    push edx
        invoke Load_wav,TEXT_("walls.wav"),addr g_pDSWavSample
        .if (g_pDSWavSample != 0)
        ; só copia, é p rodar em outras threads
            coinvoke    g_pDSWavSample,IDirectSoundBuffer8,SetCurrentPosition,0 
            coinvoke    g_pDSWavSample,IDirectSoundBuffer8,Play,0,0,0
        .endif
    pop edx
    pop ecx
    pop ebx
    pop eax

    ret
Parede endp

Paddle proc
    push eax
    push ebx
    push ecx
    push edx
        invoke Load_wav,TEXT_("paddle.wav"),addr g_pDSWavSample
        .if (g_pDSWavSample != 0)
        ; só copia, é p rodar em outras threads
            coinvoke    g_pDSWavSample,IDirectSoundBuffer8,SetCurrentPosition,0 
            coinvoke    g_pDSWavSample,IDirectSoundBuffer8,Play,0,0,0
        .endif
    pop edx
    pop ecx
    pop ebx
    pop eax

    ret
Paddle endp

Brick proc
    push eax
    push ebx
    push ecx
    push edx
        invoke Load_wav,TEXT_("brick.wav"),addr g_pDSWavSample
        .if (g_pDSWavSample != 0)
        ; só copia, é p rodar em outras threads
            coinvoke    g_pDSWavSample,IDirectSoundBuffer8,SetCurrentPosition,0 
            coinvoke    g_pDSWavSample,IDirectSoundBuffer8,Play,0,0,0
        .endif
    pop edx
    pop ecx
    pop ebx
    pop eax

    ret
Brick endp