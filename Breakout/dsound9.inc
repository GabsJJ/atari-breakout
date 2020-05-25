;/*==========================================================================;
; *
; *  Copyright (c) Microsoft Corporation.  All rights reserved.
; *
; *  File:       dsound.inc
; *  Content:    DirectSound include file
; *
; *  Translated to .ASM by: Siekmanski
; *
; **************************************************************************/

ifndef DIRECTSOUND_VERSION
DIRECTSOUND_VERSION	equ 00900h ;/* Version 9.0 */
endif

ifndef __DSOUND_INCLUDED__
__DSOUND_INCLUDED__ equ 1

;/* Type definitions shared with Direct3D */

ifndef DX_SHARED_DEFINES

D3DVALUE	typedef FLOAT
LPD3DVALUE	typedef PTR FLOAT

ifndef D3DCOLOR_DEFINED
D3DCOLOR	typedef DWORD
D3DCOLOR_DEFINED equ 1
endif

ifndef LPD3DCOLOR_DEFINED
LPD3DCOLOR	typedef PTR DWORD
LPD3DCOLOR_DEFINED equ 1
endif


ifndef D3DVECTOR_DEFINED
_D3DVECTOR struct
	x	FLOAT ?
	y	FLOAT ?
	z	FLOAT ?
_D3DVECTOR ends
D3DVECTOR	typedef _D3DVECTOR
D3DVECTOR_DEFINED equ 1
endif

ifndef LPD3DVECTOR_DEFINED
LPD3DVECTOR	typedef PTR _D3DVECTOR
LPD3DVECTOR_DEFINED equ 1
endif

DX_SHARED_DEFINES equ 1
endif ;// DX_SHARED_DEFINES

LPWAVEFORMATEX	typedef ptr WAVEFORMATEX

_FACDS	equ 0878h ;/* DirectSound's facility code */

MAKE_DSHRESULT MACRO code:REQ
	EXITM %((1 shl 31) or ((_FACDS and 0fffh) shl 16) or (code and 0ffffh))
ENDM

;// DirectSound Component GUID {47D4D946-62E8-11CF-93BC-444553540000}
CLSID_DirectSound		TEXTEQU <{047d4d946h,062e8h,011cfh,{093h,0bch,044h,045h,053h,054h,000h,000h}}>

;// DirectSound 8.0 Component GUID {3901CC3F-84B5-4FA4-BA35-AA8172B8A09B}
CLSID_DirectSound8		TEXTEQU <{03901cc3fh,084b5h,04fa4h,{0bah,035h,0aah,081h,072h,0b8h,0a0h,09bh}}>

;// DirectSound Capture Component GUID {B0210780-89CD-11D0-AF08-00A0C925CD16}
CLSID_DirectSoundCapture	TEXTEQU <{0b0210780h,089cdh,011d0h,{0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h}}>

;// DirectSound 8.0 Capture Component GUID {E4BCAC13-7F99-4908-9A8E-74E3BF24B6E1}
CLSID_DirectSoundCapture8	TEXTEQU <{0e4bcac13h,07f99h,04908h,{09ah,08eh,074h,0e3h,0bfh,024h,0b6h,0e1h}}>

;// DirectSound Full Duplex Component GUID {FEA4300C-7959-4147-B26A-2377B9E7A91D}
CLSID_DirectSoundFullDuplex	TEXTEQU <{0fea4300ch,07959h,04147h,{0b2h,06ah,023h,077h,0b9h,0e7h,0a9h,01dh}}>

;// DirectSound default playback device GUID {DEF00000-9C6D-47ED-AAF1-4DDA8F2B5C03}
DSDEVID_DefaultPlayback		TEXTEQU <{0def00000h,09c6dh,047edh,{0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h}}>

;// DirectSound default capture device GUID {DEF00001-9C6D-47ED-AAF1-4DDA8F2B5C03}
DSDEVID_DefaultCapture		TEXTEQU <{0def00001h,09c6dh,047edh,{0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h}}>

;// DirectSound default device for voice playback {DEF00002-9C6D-47ED-AAF1-4DDA8F2B5C03}
DSDEVID_DefaultVoicePlayback	TEXTEQU <{0def00002h,09c6dh,047edh,{0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h}}>

;// DirectSound default device for voice capture {DEF00003-9C6D-47ED-AAF1-4DDA8F2B5C03}
DSDEVID_DefaultVoiceCapture	TEXTEQU <{0def00003h,09c6dh,047edh,{0aah,0f1h,04dh,0dah,08fh,02bh,05ch,003h}}>

;//
;// DirectSound 8.0 interfaces.
;//

if DIRECTSOUND_VERSION ge 00800h

;// IDirectSound8, IDirectSoundBuffer8 and IDirectSoundCaptureBuffer8 are the
;// only DirectSound 7.0 interfaces with changed functionality in version 8.0.
;// The other level 8 interfaces as equivalent to their level 7 counterparts:

IDirectSoundCapture8			equ IDirectSoundCapture
IDirectSound3DListener8			equ IDirectSound3DListener
IDirectSound3DBuffer8			equ IDirectSound3DBuffer
IDirectSoundNotify8			equ IDirectSoundNotify
IDirectSoundFXGargle8			equ IDirectSoundFXGargle
IDirectSoundFXChorus8			equ IDirectSoundFXChorus
IDirectSoundFXFlanger8			equ IDirectSoundFXFlanger
IDirectSoundFXEcho8			equ IDirectSoundFXEcho
IDirectSoundFXDistortion8		equ IDirectSoundFXDistortion
IDirectSoundFXCompressor8		equ IDirectSoundFXCompressor
IDirectSoundFXParamEq8			equ IDirectSoundFXParamEq
IDirectSoundFXWavesReverb8		equ IDirectSoundFXWavesReverb
IDirectSoundFXI3DL2Reverb8		equ IDirectSoundFXI3DL2Reverb
IDirectSoundCaptureFXAec8		equ IDirectSoundCaptureFXAec
IDirectSoundCaptureFXNoiseSuppress8	equ IDirectSoundCaptureFXNoiseSuppress
IDirectSoundFullDuplex8			equ IDirectSoundFullDuplex

endif ;// DIRECTSOUND_VERSION >= 0x0800

LPDIRECTSOUND				typedef PTR IDirectSound
LPDIRECTSOUNDBUFFER			typedef PTR IDirectSoundBuffer
LPDIRECTSOUND3DLISTENER			typedef PTR IDirectSound3DListener
LPDIRECTSOUND3DBUFFER			typedef PTR IDirectSound3DBuffer
LPDIRECTSOUNDCAPTURE			typedef PTR IDirectSoundCapture
LPDIRECTSOUNDCAPTUREBUFFER		typedef PTR IDirectSoundCaptureBuffer
LPDIRECTSOUNDNOTIFY			typedef PTR IDirectSoundNotify


if DIRECTSOUND_VERSION ge 00800h

LPDIRECTSOUNDFXGARGLE			typedef PTR IDirectSoundFXGargle
LPDIRECTSOUNDFXCHORUS			typedef PTR IDirectSoundFXChorus
LPDIRECTSOUNDFXFLANGER			typedef PTR IDirectSoundFXFlanger
LPDIRECTSOUNDFXECHO			typedef PTR IDirectSoundFXEcho
LPDIRECTSOUNDFXDISTORTION		typedef PTR IDirectSoundFXDistortion
LPDIRECTSOUNDFXCOMPRESSOR		typedef PTR IDirectSoundFXCompressor
LPDIRECTSOUNDFXPARAMEQ			typedef PTR IDirectSoundFXParamEq
LPDIRECTSOUNDFXWAVESREVERB		typedef PTR IDirectSoundFXWavesReverb
LPDIRECTSOUNDFXI3DL2REVERB		typedef PTR IDirectSoundFXI3DL2Reverb
LPDIRECTSOUNDCAPTUREFXAEC		typedef PTR IDirectSoundCaptureFXAec
LPDIRECTSOUNDCAPTUREFXNOISESUPPRESS	typedef PTR IDirectSoundCaptureFXNoiseSuppress
LPDIRECTSOUNDFULLDUPLEX			typedef PTR IDirectSoundFullDuplex

LPDIRECTSOUND8				typedef PTR IDirectSound8
LPDIRECTSOUNDBUFFER8			typedef PTR IDirectSoundBuffer8
LPDIRECTSOUND3DLISTENER8		typedef PTR IDirectSound3DListener8
LPDIRECTSOUND3DBUFFER8			typedef PTR IDirectSound3DBuffer8
LPDIRECTSOUNDCAPTURE8			typedef PTR IDirectSoundCapture8
LPDIRECTSOUNDCAPTUREBUFFER8		typedef PTR IDirectSoundCaptureBuffer8
LPDIRECTSOUNDNOTIFY8			typedef PTR IDirectSoundNotify8
LPDIRECTSOUNDFXGARGLE8			typedef PTR IDirectSoundFXGargle8
LPDIRECTSOUNDFXCHORUS8			typedef PTR IDirectSoundFXChorus8
LPDIRECTSOUNDFXFLANGER8			typedef PTR IDirectSoundFXFlanger8
LPDIRECTSOUNDFXECHO8			typedef PTR IDirectSoundFXEcho8
LPDIRECTSOUNDFXDISTORTION8		typedef PTR IDirectSoundFXDistortion8
LPDIRECTSOUNDFXCOMPRESSOR8		typedef PTR IDirectSoundFXCompressor8
LPDIRECTSOUNDFXPARAMEQ8			typedef PTR IDirectSoundFXParamEq8
LPDIRECTSOUNDFXWAVESREVERB8		typedef PTR IDirectSoundFXWavesReverb8
LPDIRECTSOUNDFXI3DL2REVERB8		typedef PTR IDirectSoundFXI3DL2Reverb8
LPDIRECTSOUNDCAPTUREFXAEC8		typedef PTR IDirectSoundCaptureFXAec8
LPDIRECTSOUNDCAPTUREFXNOISESUPPRESS8	typedef PTR IDirectSoundCaptureFXNoiseSuppress8
LPDIRECTSOUNDFULLDUPLEX8		typedef PTR IDirectSoundFullDuplex8

;//
;// IID definitions for the unchanged DirectSound 8.0 interfaces
;//

IID_IDirectSoundCapture8		equ IID_IDirectSoundCapture
IID_IDirectSound3DListener8		equ IID_IDirectSound3DListener
IID_IDirectSound3DBuffer8		equ IID_IDirectSound3DBuffer
IID_IDirectSoundNotify8			equ IID_IDirectSoundNotify
IID_IDirectSoundFXGargle8		equ IID_IDirectSoundFXGargle
IID_IDirectSoundFXChorus8		equ IID_IDirectSoundFXChorus
IID_IDirectSoundFXFlanger8		equ IID_IDirectSoundFXFlanger
IID_IDirectSoundFXEcho8			equ IID_IDirectSoundFXEcho
IID_IDirectSoundFXDistortion8		equ IID_IDirectSoundFXDistortion
IID_IDirectSoundFXCompressor8		equ IID_IDirectSoundFXCompressor
IID_IDirectSoundFXParamEq8		equ IID_IDirectSoundFXParamEq
IID_IDirectSoundFXWavesReverb8		equ IID_IDirectSoundFXWavesReverb
IID_IDirectSoundFXI3DL2Reverb8		equ IID_IDirectSoundFXI3DL2Reverb
IID_IDirectSoundCaptureFXAec8		equ IID_IDirectSoundCaptureFXAec
IID_IDirectSoundCaptureFXNoiseSuppress8	equ IID_IDirectSoundCaptureFXNoiseSuppress
IID_IDirectSoundFullDuplex8		equ IID_IDirectSoundFullDuplex

endif ;// DIRECTSOUND_VERSION >= 0x0800

;//
;// Compatibility typedefs
;//

ifndef _LPCWAVEFORMATEX_DEFINED
_LPCWAVEFORMATEX_DEFINED equ 1
LPCWAVEFORMATEX		typedef PTR WAVEFORMATEX
endif ;// _LPCWAVEFORMATEX_DEFINED

ifndef __LPCGUID_DEFINED__
__LPCGUID_DEFINED__ equ 1
LPCGUID			typedef PTR GUID
endif ;// __LPCGUID_DEFINED__

LPLPDIRECTSOUND				typedef PTR LPDIRECTSOUND
LPLPDIRECTSOUNDBUFFER			typedef PTR LPDIRECTSOUNDBUFFER
LPLPDIRECTSOUND3DLISTENER		typedef PTR LPDIRECTSOUND3DLISTENER
LPLPDIRECTSOUND3DBUFFER			typedef PTR LPDIRECTSOUND3DBUFFER
LPLPDIRECTSOUNDCAPTURE			typedef PTR LPDIRECTSOUNDCAPTURE
LPLPDIRECTSOUNDCAPTUREBUFFER		typedef PTR LPDIRECTSOUNDCAPTUREBUFFER
LPLPDIRECTSOUNDNOTIFY			typedef PTR LPDIRECTSOUNDNOTIFY

if DIRECTSOUND_VERSION ge 00800h
LPLPDIRECTSOUND8			typedef PTR LPDIRECTSOUND8
LPLPDIRECTSOUNDBUFFER8			typedef PTR LPDIRECTSOUNDBUFFER8
LPLPDIRECTSOUNDCAPTURE8			typedef PTR LPDIRECTSOUNDCAPTURE8
LPLPDIRECTSOUNDCAPTUREBUFFER8		typedef PTR LPDIRECTSOUNDCAPTUREBUFFER8
endif ;// DIRECTSOUND_VERSION >= 0x0800


;//
;// Structures
;//

_DSCAPS struct
	dwSize				DWORD ?
	dwFlags				DWORD ?
	dwMinSecondarySampleRate	DWORD ?
	dwMaxSecondarySampleRate	DWORD ?
	dwPrimaryBuffers		DWORD ?
	dwMaxHwMixingAllBuffers		DWORD ?
	dwMaxHwMixingStaticBuffers	DWORD ?
	dwMaxHwMixingStreamingBuffers	DWORD ?
	dwFreeHwMixingAllBuffers	DWORD ?
	dwFreeHwMixingStaticBuffers	DWORD ?
	dwFreeHwMixingStreamingBuffers	DWORD ?
	dwMaxHw3DAllBuffers		DWORD ?
	dwMaxHw3DStaticBuffers		DWORD ?
	dwMaxHw3DStreamingBuffers	DWORD ?
	dwFreeHw3DAllBuffers		DWORD ?
	dwFreeHw3DStaticBuffers		DWORD ?
	dwFreeHw3DStreamingBuffers	DWORD ?
	dwTotalHwMemBytes		DWORD ?
	dwFreeHwMemBytes		DWORD ?
	dwMaxContigFreeHwMemBytes	DWORD ?
	dwUnlockTransferRateHwBuffers	DWORD ?
	dwPlayCpuOverheadSwBuffers	DWORD ?
	dwReserved1			DWORD ?
	dwReserved2			DWORD ?
_DSCAPS ends

DSCAPS			typedef _DSCAPS
LPDSCAPS		typedef PTR _DSCAPS
LPCDSCAPS		typedef PTR _DSCAPS

_DSBCAPS struct
	dwSize			DWORD ?
	dwFlags			DWORD ?
	dwBufferBytes		DWORD ?
	dwUnlockTransferRate	DWORD ?
	dwPlayCpuOverhead	DWORD ?
_DSBCAPS ends

DSBCAPS			typedef _DSBCAPS
LPDSBCAPS		typedef PTR _DSBCAPS
LPCDSBCAPS		typedef PTR _DSBCAPS

if DIRECTSOUND_VERSION ge 00800h

_DSEFFECTDESC struct
	dwSize		DWORD ?
	dwFlags		DWORD ?
	guidDSFXClass	GUID <?>
	dwReserved1	DWORD ?
	dwReserved2	DWORD ?
_DSEFFECTDESC ends

DSEFFECTDESC		typedef _DSEFFECTDESC
LPDSEFFECTDESC		typedef PTR _DSEFFECTDESC
LPCDSEFFECTDESC		typedef PTR _DSEFFECTDESC

DSFX_LOCHARDWARE	equ 000000001h
DSFX_LOCSOFTWARE	equ 000000002h

DSFXR_PRESENT		equ 0
DSFXR_LOCHARDWARE	equ 1
DSFXR_LOCSOFTWARE	equ 2
DSFXR_UNALLOCATED	equ 3
DSFXR_FAILED		equ 4
DSFXR_UNKNOWN		equ 5
DSFXR_SENDLOOP		equ 6

_DSCEFFECTDESC struct
	dwSize			DWORD ?
	dwFlags			DWORD ?
	guidDSCFXClass		GUID <?>
	guidDSCFXInstance	GUID <?>
	dwReserved1		DWORD ?
	dwReserved2		DWORD ?
_DSCEFFECTDESC ends

DSCEFFECTDESC		typedef _DSCEFFECTDESC
LPDSCEFFECTDESC		typedef PTR _DSCEFFECTDESC
LPCDSCEFFECTDESC	typedef PTR _DSCEFFECTDESC

DSCFX_LOCHARDWARE	equ 000000001h
DSCFX_LOCSOFTWARE	equ 000000002h

DSCFXR_LOCHARDWARE	equ 000000010h
DSCFXR_LOCSOFTWARE	equ 000000020h

endif ;// DIRECTSOUND_VERSION >= 0x0800

_DSBUFFERDESC struct
	dwSize		DWORD ?
	dwFlags		DWORD ?
	dwBufferBytes	DWORD ?
	dwReserved	DWORD ?
	lpwfxFormat	LPWAVEFORMATEX ?
if DIRECTSOUND_VERSION ge 00700h
	guid3DAlgorithm	GUID <?>
endif
_DSBUFFERDESC ends

DSBUFFERDESC		typedef _DSBUFFERDESC
LPDSBUFFERDESC		typedef PTR _DSBUFFERDESC
LPCDSBUFFERDESC		typedef PTR _DSBUFFERDESC

;// Older version of this structure:

_DSBUFFERDESC1 struct
	dwSize		DWORD ?
	dwFlags		DWORD ?
	dwBufferBytes	DWORD ?
	dwReserved	DWORD ?
	lpwfxFormat	LPWAVEFORMATEX ?
_DSBUFFERDESC1 ends

DSBUFFERDESC1		typedef _DSBUFFERDESC1
LPDSBUFFERDESC1		typedef PTR _DSBUFFERDESC1
LPCDSBUFFERDESC1	typedef PTR _DSBUFFERDESC1

_DS3DBUFFER struct
	dwSize			DWORD	   ?
	vPosition		D3DVECTOR <?>
	vVelocity		D3DVECTOR <?>
	dwInsideConeAngle	DWORD	   ?
	dwOutsideConeAngle	DWORD	   ?
	vConeOrientation	D3DVECTOR <?>
	lConeOutsideVolume	DWORD	   ?
	flMinDistance		D3DVALUE   ?
	flMaxDistance		D3DVALUE   ?
	dwMode			DWORD	   ?
_DS3DBUFFER ends

DS3DBUFFER		typedef _DS3DBUFFER
LPDS3DBUFFER		typedef PTR _DS3DBUFFER
LPCDS3DBUFFER		typedef PTR _DS3DBUFFER

_DS3DLISTENER struct
	dwSize			DWORD	   ?
	vPosition		D3DVECTOR <?>
	vVelocity		D3DVECTOR <?>
	vOrientFront		D3DVECTOR <?>
	vOrientTop		D3DVECTOR <?>
	flDistanceFactor	D3DVALUE   ?
	flRolloffFactor		D3DVALUE   ?
	flDopplerFactor		D3DVALUE   ?
_DS3DLISTENER ends

DS3DLISTENER		typedef _DS3DLISTENER
LPDS3DLISTENER		typedef PTR _DS3DLISTENER
LPCDS3DLISTENER		typedef PTR _DS3DLISTENER

_DSCCAPS struct
	dwSize			DWORD ?
	dwFlags			DWORD ?
	dwFormats		DWORD ?
	dwChannels		DWORD ?
_DSCCAPS ends

DSCCAPS			typedef _DSCCAPS
LPDSCCAPS		typedef PTR _DSCCAPS
LPCDSCCAPS		typedef PTR _DSCCAPS

_DSCBUFFERDESC1 struct
	dwSize		DWORD ?
	dwFlags		DWORD ?
	dwBufferBytes	DWORD ?
	dwReserved	DWORD ?
	lpwfxFormat	LPWAVEFORMATEX ?
_DSCBUFFERDESC1 ends

DSCBUFFERDESC1		typedef _DSCBUFFERDESC1
LPDSCBUFFERDESC1	typedef PTR _DSCBUFFERDESC1

_DSCBUFFERDESC struct
	dwSize		DWORD ?
	dwFlags		DWORD ?
	dwBufferBytes	DWORD ?
	dwReserved	DWORD ?
	lpwfxFormat	LPWAVEFORMATEX ?
if DIRECTSOUND_VERSION ge 00800h
	dwFXCount	LPDSCEFFECTDESC ?
	lpDSCFXDesc	DWORD ?
endif
_DSCBUFFERDESC ends

DSCBUFFERDESC		typedef _DSCBUFFERDESC
LPDSCBUFFERDESC		typedef PTR _DSCBUFFERDESC
LPCDSCBUFFERDESC	typedef PTR _DSCBUFFERDESC

_DSCBCAPS struct
	dwSize		DWORD ?
	dwFlags		DWORD ?
	dwBufferBytes	DWORD ?
	dwReserved	DWORD ?
_DSCBCAPS ends

DSCBCAPS		typedef _DSCBCAPS
LPDSCBCAPS		typedef PTR _DSCBCAPS
LPCDSCBCAPS		typedef PTR _DSCBCAPS

_DSBPOSITIONNOTIFY struct
	dwOffset	DWORD ?
	hEventNotify	DWORD ?
_DSBPOSITIONNOTIFY ends

DSBPOSITIONNOTIFY	typedef _DSBPOSITIONNOTIFY
LPDSBPOSITIONNOTIFY	typedef PTR _DSBPOSITIONNOTIFY
LPCDSBPOSITIONNOTIFY	typedef PTR _DSBPOSITIONNOTIFY

;//
;// DirectSound API
;//

;typedef BOOL (CALLBACK *LPDSENUMCALLBACKA)(LPGUID, LPCSTR, LPCSTR, LPVOID);
LPDSENUMCALLBACKA	typedef PTR DWORD
;typedef BOOL (CALLBACK *LPDSENUMCALLBACKW)(LPGUID, LPCWSTR, LPCWSTR, LPVOID);
LPDSENUMCALLBACKW	typedef PTR DWORD

DirectSoundCreate		PROTO :DWORD,:DWORD,:DWORD
DirectSoundEnumerateA		PROTO :DWORD,:DWORD
DirectSoundEnumerateW		PROTO :DWORD,:DWORD

DirectSoundCaptureCreate	PROTO :DWORD,:DWORD,:DWORD
DirectSoundCaptureEnumerateA	PROTO :DWORD,:DWORD
DirectSoundCaptureEnumerateW	PROTO :DWORD,:DWORD

if DIRECTSOUND_VERSION ge 00800h
DirectSoundCreate8		PROTO :DWORD,:DWORD,:DWORD
DirectSoundCaptureCreate8	PROTO :DWORD,:DWORD,:DWORD
DirectSoundFullDuplexCreate	PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
DirectSoundFullDuplexCreate8	equ DirectSoundFullDuplexCreate
GetDeviceID			PROTO :DWORD,:DWORD
endif ;// DIRECTSOUND_VERSION >= 0x0800

ifdef UNICODE
LPDSENUMCALLBACK		equ LPDSENUMCALLBACKW
DirectSoundEnumerate		equ DirectSoundEnumerateW
DirectSoundCaptureEnumerate	equ DirectSoundCaptureEnumerateW
else ;// UNICODE
LPDSENUMCALLBACK		equ LPDSENUMCALLBACKA
DirectSoundEnumerate		equ DirectSoundEnumerateA
DirectSoundCaptureEnumerate	equ DirectSoundCaptureEnumerateA
endif ;// UNICODE

REFERENCE_TIME			typedef QWORD
LPREFERENCE_TIME		typedef PTR QWORD

comethodAdviseProto		typedef PROTO :DWORD,:QWORD,:QWORD,:DWORD,:DWORD
comethodAdvise			typedef PTR comethodAdviseProto

IID_IReferenceClock	TEXTEQU <{056a86897h,00ad4h,011ceh,{0b0h,03ah,000h,020h,0afh,00bh,0a7h,070h}}>

_vtIReferenceClock MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_GetTime			comethod2 ?
	&CastName&_AdviseTime			comethodAdvise ?
	&CastName&_AdvisePeriodic		comethodAdvise ?
	&CastName&_Unadvise			comethod2 ?
ENDM

IReferenceClock struct
	_vtIReferenceClock	IReferenceClock
IReferenceClock ends

;//
;// IDirectSound
;//

IID_IDirectSound	TEXTEQU <{0279AFA83h,04981h,011CEh,{0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060h}}>

_vtIDirectSound MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_CreateSoundBuffer		comethod4 ?
	&CastName&_GetCaps			comethod2 ?
	&CastName&_DuplicateSoundBuffer		comethod3 ?
	&CastName&_SetCooperativeLevel		comethod3 ?
	&CastName&_Compact			comethod1 ?
	&CastName&_GetSpeakerConfig		comethod2 ?
	&CastName&_SetSpeakerConfig		comethod2 ?
	&CastName&_Initialize			comethod2 ?
ENDM

IDirectSound struct
	_vtIDirectSound	IDirectSound
IDirectSound ends


if DIRECTSOUND_VERSION ge 00800h

;//
;// IDirectSound8
;//

IID_IDirectSound8	TEXTEQU <{0C50A7E93h,0F395h,04834h,{09Eh,0F6h,07Fh,0A9h,09Dh,0E5h,009h,066h}}>

_vtIDirectSound8 MACRO CastName:REQ
	_vtIDirectSound CastName
	&CastName&_VerifyCertification		comethod2 ?
ENDM

IDirectSound8 struct
	_vtIDirectSound8	IDirectSound8
IDirectSound8 ends


endif ;// DIRECTSOUND_VERSION >= 0x0800

;//
;// IDirectSoundBuffer
;//

IID_IDirectSoundBuffer		TEXTEQU <{0279AFA85h,04981h,011CEh,{0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060}}>

_vtIDirectSoundBuffer MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_GetCaps			comethod2 ?
	&CastName&_GetCurrentPosition		comethod3 ?
	&CastName&_GetFormat			comethod4 ?
	&CastName&_GetVolume			comethod2 ?
	&CastName&_GetPan			comethod2 ?
	&CastName&_GetFrequency			comethod2 ?
	&CastName&_GetStatus			comethod2 ?
	&CastName&_Initialize			comethod3 ?
	&CastName&_Lock				comethod8 ?
	&CastName&_Play				comethod4 ?
	&CastName&_SetCurrentPosition		comethod2 ?
	&CastName&_SetFormat			comethod2 ?
	&CastName&_SetVolume			comethod2 ?
	&CastName&_SetPan			comethod2 ?
	&CastName&_SetFrequency			comethod2 ?
	&CastName&_Stop				comethod1 ?
	&CastName&_Unlock			comethod5 ?
	&CastName&_Restore			comethod1 ?
ENDM

IDirectSoundBuffer struct
	_vtIDirectSoundBuffer			IDirectSoundBuffer
IDirectSoundBuffer ends

if DIRECTSOUND_VERSION ge 00800h

;//
;// IDirectSoundBuffer8
;//

IID_IDirectSoundBuffer8		TEXTEQU <{06825a449h,07524h,04d82h,{092h,00fh,050h,0e3h,06ah,0b3h,0abh,01eh}}>
;// Special GUID meaning "select all objects" for use in GetObjectInPath()
GUID_All_Objects		TEXTEQU <{0aa114de5h,0c262h,04169h,{0a1h,0c8h,023h,0d6h,098h,0cch,073h,0b5h}}>

_vtIDirectSoundBuffer8 MACRO CastName:REQ
	_vtIDirectSoundBuffer CastName
	&CastName&_SetFX			comethod4 ?
	&CastName&_AcquireResources		comethod4 ?
	&CastName&_GetObjectInPath		comethod5 ?
ENDM

IDirectSoundBuffer8 struct
	_vtIDirectSoundBuffer8			IDirectSoundBuffer8
IDirectSoundBuffer8 ends

endif ;// DIRECTSOUND_VERSION >= 0x0800

;//
;// IDirectSound3DListener
;//

IID_IDirectSound3DListener	TEXTEQU <{0279AFA84h,04981h,011CEh,{0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060h}}>

_vtIDirectSound3DListener MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_GetAllParameters			comethod2 ?
	&CastName&_GetDistanceFactor			comethod2 ?
	&CastName&_GetDopplerFactor			comethod2 ?
	&CastName&_GetOrientation			comethod3 ?
	&CastName&_GetPosition				comethod2 ?
	&CastName&_GetRolloffFactor			comethod2 ?
	&CastName&_GetVelocity				comethod2 ?
	&CastName&_SetAllParameters			comethod3 ?
	&CastName&_SetDistanceFactor			comethod3 ?
	&CastName&_SetDopplerFactor			comethod3 ?
	&CastName&_SetOrientation			comethod8 ?
	&CastName&_SetPosition				comethod5 ?
	&CastName&_SetRolloffFactor			comethod3 ?
	&CastName&_SetVelocity				comethod5 ?
	&CastName&_CommitDeferredSettings		comethod1 ?
ENDM

IDirectSound3DListener struct
	_vtIDirectSound3DListener	IDirectSound3DListener
IDirectSound3DListener ends

;//
;// IDirectSound3DBuffer
;//

IID_IDirectSound3DBuffer	TEXTEQU <{0279AFA86h,04981h,011CEh,{0A5h,021h,000h,020h,0AFh,00Bh,0E5h,060h}}>

_vtIDirectSound3DBuffer MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_GetAllParameters		comethod2 ?
	&CastName&_GetConeAngles		comethod3 ?
	&CastName&_GetConeOrientation		comethod2 ?
	&CastName&_GetConeOutsideVolume		comethod2 ?
	&CastName&_GetMaxDistance		comethod2 ?
	&CastName&_GetMinDistance		comethod2 ?
	&CastName&_GetMode			comethod2 ?
	&CastName&_GetPosition			comethod2 ?
	&CastName&_GetVelocity			comethod2 ?
	&CastName&_SetAllParameters		comethod3 ?
	&CastName&_SetConeAngles		comethod4 ?
	&CastName&_SetConeOrientation		comethod5 ?
	&CastName&_SetConeOutsideVolume		comethod3 ?
	&CastName&_SetMaxDistance		comethod3 ?
	&CastName&_SetMinDistance		comethod3 ?
	&CastName&_SetMode			comethod3 ?
	&CastName&_SetPosition			comethod5 ?
	&CastName&_SetVelocity			comethod5 ?
ENDM

IDirectSound3DBuffer struct
	_vtIDirectSound3DBuffer		IDirectSound3DBuffer
IDirectSound3DBuffer ends

;//
;// IDirectSoundCapture
;//

IID_IDirectSoundCapture		TEXTEQU <{0b0210781h,089cdh,011d0h,{0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h}}>

_vtIDirectSoundCapture MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_CreateCaptureBuffer		comethod4 ?
	&CastName&_GetCaps			comethod2 ?
	&CastName&_Initialize			comethod2 ?
ENDM

IDirectSoundCapture struct
	_vtIDirectSoundCapture		IDirectSoundCapture
IDirectSoundCapture ends

;//
;// IDirectSoundCaptureBuffer
;//

IID_IDirectSoundCaptureBuffer	TEXTEQU <{0b0210782h,089cdh,011d0h,{0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h}}>

_vtIDirectSoundCaptureBuffer MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_GetCaps			comethod2 ?
	&CastName&_GetCurrentPosition		comethod3 ?
	&CastName&_GetFormat			comethod4 ?
	&CastName&_GetStatus			comethod2 ?
	&CastName&_Initialize			comethod3 ?
	&CastName&_Lock				comethod8 ?
	&CastName&_Start			comethod2 ?
	&CastName&_Stop				comethod1 ?
	&CastName&_Unlock			comethod5 ?
ENDM

IDirectSoundCaptureBuffer struct
	_vtIDirectSoundCaptureBuffer	IDirectSoundCaptureBuffer
IDirectSoundCaptureBuffer ends


if DIRECTSOUND_VERSION ge 00800h

;//
;// IDirectSoundCaptureBuffer8
;//

IID_IDirectSoundCaptureBuffer8	TEXTEQU <{000990df4h,00dbbh,04872h,{083h,03eh,06dh,030h,03eh,080h,0aeh,0b6h}}>

_vtIDirectSoundCaptureBuffer8 MACRO CastName:REQ
	_vtIDirectSoundCaptureBuffer CastName
	&CastName&_GetObjectInPath		comethod5 ?
	&CastName&_GetFXStatus			comethod3 ?
ENDM

IDirectSoundCaptureBuffer8 struct
	_vtIDirectSoundCaptureBuffer8	IDirectSoundCaptureBuffer8
IDirectSoundCaptureBuffer8 ends


endif ;// DIRECTSOUND_VERSION >= 0x0800

;//
;// IDirectSoundNotify
;//

IID_IDirectSoundNotify		TEXTEQU <{0b0210783h,089cdh,011d0h,{0afh,008h,000h,0a0h,0c9h,025h,0cdh,016h}}>

_vtIDirectSoundNotify MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetNotificationPositions	comethod3 ?
ENDM

IDirectSoundNotify struct
	_vtIDirectSoundNotify		IDirectSoundNotify
IDirectSoundNotify ends

;//
;// IKsPropertySet
;//

LPKSPROPERTYSET		typedef PTR IKsPropertySet

KSPROPERTY_SUPPORT_GET			equ 000000001h
KSPROPERTY_SUPPORT_SET			equ 000000002h

IID_IKsPropertySet		TEXTEQU <{031efac30h,0515ch,011d0h,{0a9h,0aah,000h,0aah,000h,061h,0beh,093h}}>

_vtIKsPropertySet MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_Get				comethod8 ?
	&CastName&_Set				comethod7 ?
	&CastName&_QuerySupport			comethod4 ?
ENDM

IKsPropertySet struct
	_vtIKsPropertySet		IKsPropertySet
IKsPropertySet ends

if DIRECTSOUND_VERSION ge 00800h

;//
;// IDirectSoundFXGargle
;//

IID_IDirectSoundFXGargle	TEXTEQU <{0d616f352h,0d622h,011ceh,{0aah,0c5h,000h,020h,0afh,00bh,099h,0a3h}}>

_DSFXGargle struct
dwRateHz	DWORD ? ;// Rate of modulation in hz
dwWaveShape	DWORD ? ;// DSFXGARGLE_WAVE_xxx
_DSFXGargle ends

DSFXGargle		typedef _DSFXGargle
LPDSFXGargle		typedef PTR _DSFXGargle
LPCDSFXGargle		typedef PTR _DSFXGargle

DSFXGARGLE_WAVE_TRIANGLE		equ 0
DSFXGARGLE_WAVE_SQUARE			equ 1

DSFXGARGLE_RATEHZ_MIN			equ 1
DSFXGARGLE_RATEHZ_MAX			equ 1000

_vtIDirectSoundFXGargle MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXGargle struct
	_vtIDirectSoundFXGargle		IDirectSoundFXGargle
IDirectSoundFXGargle ends

;//
;// IDirectSoundFXChorus
;//

IID_IDirectSoundFXChorus	TEXTEQU <{0880842e3h,0145fh,043e6h,{0a9h,034h,0a7h,018h,006h,0e5h,005h,047h}}>

_DSFXChorus struct
	fWetDryMix	FLOAT ?
	fDepth		FLOAT ?
	fFeedback	FLOAT ?
	fFrequency	FLOAT ?
	lWaveform	DWORD ?	;// LFO shape; DSFXCHORUS_WAVE_xxx
	fDelay		FLOAT ?
	lPhase		DWORD ?
_DSFXChorus ends

DSFXChorus		typedef _DSFXChorus
LPDSFXChorus		typedef PTR _DSFXChorus
LPCDSFXChorus		typedef PTR _DSFXChorus

DSFXCHORUS_WAVE_TRIANGLE	equ 0
DSFXCHORUS_WAVE_SIN		equ 1

DSFXCHORUS_WETDRYMIX_MIN	equ 0.0f
DSFXCHORUS_WETDRYMIX_MAX	equ 100.0f
DSFXCHORUS_DEPTH_MIN		equ 0.0f
DSFXCHORUS_DEPTH_MAX		equ 100.0f
DSFXCHORUS_FEEDBACK_MIN		equ -99.0f
DSFXCHORUS_FEEDBACK_MAX		equ 99.0f
DSFXCHORUS_FREQUENCY_MIN	equ 0.0f
DSFXCHORUS_FREQUENCY_MAX	equ 10.0f
DSFXCHORUS_DELAY_MIN		equ 0.0f
DSFXCHORUS_DELAY_MAX		equ 20.0f
DSFXCHORUS_PHASE_MIN		equ 0
DSFXCHORUS_PHASE_MAX		equ 4

DSFXCHORUS_PHASE_NEG_180	equ 0
DSFXCHORUS_PHASE_NEG_90		equ 1
DSFXCHORUS_PHASE_ZERO		equ 2
DSFXCHORUS_PHASE_90		equ 3
DSFXCHORUS_PHASE_180		equ 4

_vtIDirectSoundFXChorus MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXChorus struct
	_vtIDirectSoundFXChorus		IDirectSoundFXChorus
IDirectSoundFXChorus ends

;//
;// IDirectSoundFXFlanger
;//

IID_IDirectSoundFXFlanger	TEXTEQU <{0903e9878h,02c92h,04072h,{09bh,02ch,0eah,068h,0f5h,039h,067h,083h}}>

_DSFXFlanger struct
	fWetDryMix	FLOAT ?
	fDepth		FLOAT ?
	fFeedback	FLOAT ?
	fFrequency	FLOAT ?
	lWaveform	DWORD ?
	fDelay		FLOAT ?
	lPhase		DWORD ?
_DSFXFlanger ends

DSFXFlanger		typedef _DSFXFlanger
LPDSFXFlanger		typedef PTR _DSFXFlanger
LPCDSFXFlanger		typedef PTR _DSFXFlanger

DSFXFLANGER_WAVE_TRIANGLE	equ 0
DSFXFLANGER_WAVE_SIN		equ 1

DSFXFLANGER_WETDRYMIX_MIN	equ 0.0f
DSFXFLANGER_WETDRYMIX_MAX	equ 100.0f
DSFXFLANGER_FREQUENCY_MIN	equ 0.0f
DSFXFLANGER_FREQUENCY_MAX	equ 10.0f
DSFXFLANGER_DEPTH_MIN		equ 0.0f
DSFXFLANGER_DEPTH_MAX		equ 100.0f
DSFXFLANGER_PHASE_MIN		equ 0
DSFXFLANGER_PHASE_MAX		equ 4
DSFXFLANGER_FEEDBACK_MIN	equ -99.0f
DSFXFLANGER_FEEDBACK_MAX	equ 99.0f
DSFXFLANGER_DELAY_MIN		equ 0.0f
DSFXFLANGER_DELAY_MAX		equ 4.0f

DSFXFLANGER_PHASE_NEG_180	equ 0
DSFXFLANGER_PHASE_NEG_90	equ 1
DSFXFLANGER_PHASE_ZERO		equ 2
DSFXFLANGER_PHASE_90		equ 3
DSFXFLANGER_PHASE_180		equ 4

_vtIDirectSoundFXFlanger MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXFlanger struct
	_vtIDirectSoundFXFlanger	IDirectSoundFXFlanger
IDirectSoundFXFlanger ends

;//
;// IDirectSoundFXEcho
;//

IID_IDirectSoundFXEcho		TEXTEQU <{08bd28edfh,050dbh,04e92h,{0a2h,0bdh,044h,054h,088h,0d1h,0edh,042h}}>

_DSFXEcho struct
    FLOAT   fWetDryMix;
    FLOAT   fFeedback;
    FLOAT   fLeftDelay;
    FLOAT   fRightDelay;
    LONG    lPanDelay;
_DSFXEcho ends

DSFXEcho		typedef _DSFXEcho
LPDSFXEcho		typedef PTR _DSFXEcho
LPCDSFXEcho		typedef PTR _DSFXEcho

DSFXECHO_WETDRYMIX_MIN		equ 0.0f
DSFXECHO_WETDRYMIX_MAX		equ 100.0f
DSFXECHO_FEEDBACK_MIN		equ 0.0f
DSFXECHO_FEEDBACK_MAX		equ 100.0f
DSFXECHO_LEFTDELAY_MIN		equ 1.0f
DSFXECHO_LEFTDELAY_MAX		equ 2000.0f
DSFXECHO_RIGHTDELAY_MIN		equ 1.0f
DSFXECHO_RIGHTDELAY_MAX		equ 2000.0f
DSFXECHO_PANDELAY_MIN		equ 0
DSFXECHO_PANDELAY_MAX		equ 1

_vtIDirectSoundFXEcho MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXEcho struct
	_vtIDirectSoundFXEcho	IDirectSoundFXEcho
IDirectSoundFXEcho ends

;//
;// IDirectSoundFXDistortion
;//

IID_IDirectSoundFXDistortion	TEXTEQU <{08ecf4326h,0455fh,04d8bh,{0bdh,0a9h,08dh,05dh,03eh,09eh,03eh,00bh}}>

_DSFXDistortion struct
	fGain			FLOAT ?
	fEdge			FLOAT ?
	fPostEQCenterFrequency	FLOAT ?
	fPostEQBandwidth	FLOAT ?
	fPreLowpassCutoff	FLOAT ?
_DSFXDistortion ends

DSFXDistortion			typedef _DSFXDistortion
LPDSFXDistortion		typedef PTR _DSFXDistortion
LPCDSFXDistortion		typedef PTR _DSFXDistortion

DSFXDISTORTION_GAIN_MIN				equ -60.0f
DSFXDISTORTION_GAIN_MAX				equ 0.0f
DSFXDISTORTION_EDGE_MIN				equ 0.0f
DSFXDISTORTION_EDGE_MAX				equ 100.0f
DSFXDISTORTION_POSTEQCENTERFREQUENCY_MIN	equ 100.0f
DSFXDISTORTION_POSTEQCENTERFREQUENCY_MAX	equ 8000.0f
DSFXDISTORTION_POSTEQBANDWIDTH_MIN		equ 100.0f
DSFXDISTORTION_POSTEQBANDWIDTH_MAX		equ 8000.0f
DSFXDISTORTION_PRELOWPASSCUTOFF_MIN		equ 100.0f
DSFXDISTORTION_PRELOWPASSCUTOFF_MAX		equ 8000.0f

_vtIDirectSoundFXDistortion MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXDistortion struct
	_vtIDirectSoundFXDistortion	IDirectSoundFXDistortion
IDirectSoundFXDistortion ends

;//
;// IDirectSoundFXCompressor
;//

IID_IDirectSoundFXCompressor	TEXTEQU <{04bbd1154h,062f6h,04e2ch,{0a1h,05ch,0d3h,0b6h,0c4h,017h,0f7h,0a0h}}>

_DSFXCompressor struct
	fGain			FLOAT ?
	fAttack			FLOAT ?
	fRelease		FLOAT ?
	fThreshold		FLOAT ?
	fRatio			FLOAT ?
	fPredelay		FLOAT ?
_DSFXCompressor ends

DSFXCompressor			typedef _DSFXCompressor
LPDSFXCompressor		typedef PTR _DSFXCompressor
LPCDSFXCompressor		typedef PTR _DSFXCompressor

DSFXCOMPRESSOR_GAIN_MIN			equ -60.0f
DSFXCOMPRESSOR_GAIN_MAX			equ 60.0f
DSFXCOMPRESSOR_ATTACK_MIN		equ 0.01f
DSFXCOMPRESSOR_ATTACK_MAX		equ 500.0f
DSFXCOMPRESSOR_RELEASE_MIN		equ 50.0f
DSFXCOMPRESSOR_RELEASE_MAX		equ 3000.0f
DSFXCOMPRESSOR_THRESHOLD_MIN		equ -60.0f
DSFXCOMPRESSOR_THRESHOLD_MAX		equ 0.0f
DSFXCOMPRESSOR_RATIO_MIN		equ 1.0f
DSFXCOMPRESSOR_RATIO_MAX		equ 100.0f
DSFXCOMPRESSOR_PREDELAY_MIN		equ 0.0f
DSFXCOMPRESSOR_PREDELAY_MAX		equ 4.0f

_vtIDirectSoundFXCompressor MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXCompressor struct
	_vtIDirectSoundFXCompressor	IDirectSoundFXCompressor
IDirectSoundFXCompressor ends

;//
;// IDirectSoundFXParamEq
;//

IID_IDirectSoundFXParamEq	TEXTEQU <{0c03ca9feh,0fe90h,04204h,{080h,078h,082h,033h,04ch,0d1h,077h,0dah}}>

_DSFXParamEq struct
	fCenter			FLOAT ?
	fBandwidth		FLOAT ?
	fGain			FLOAT ?
_DSFXParamEq ends

DSFXParamEq			typedef _DSFXParamEq
LPDSFXParamEq			typedef PTR _DSFXParamEq
LPCDSFXParamEq			typedef PTR _DSFXParamEq

DSFXPARAMEQ_CENTER_MIN			equ 80.0f
DSFXPARAMEQ_CENTER_MAX			equ 16000.0f
DSFXPARAMEQ_BANDWIDTH_MIN		equ 1.0f
DSFXPARAMEQ_BANDWIDTH_MAX		equ 36.0f
DSFXPARAMEQ_GAIN_MIN			equ -15.0f
DSFXPARAMEQ_GAIN_MAX			equ 15.0f

_vtIDirectSoundFXParamEq MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXParamEq struct
	_vtIDirectSoundFXParamEq	IDirectSoundFXParamEq
IDirectSoundFXParamEq ends

;//
;// IDirectSoundFXI3DL2Reverb
;//

IID_IDirectSoundFXI3DL2Reverb	TEXTEQU <{04b166a6ah,00d66h,043f3h,080h,{0e3h,0eeh,062h,080h,0deh,0e1h,0a4h}}>

_DSFXI3DL2Reverb struct
	lRoom			DWORD ?	;// [-10000, 0]      default: -1000 mB
	lRoomHF			DWORD ?	;// [-10000, 0]      default: 0 mB
	flRoomRolloffFactor	FLOAT ?	;// [0.0, 10.0]      default: 0.0
	flDecayTime		FLOAT ?	;// [0.1, 20.0]      default: 1.49s
	flDecayHFRatio		FLOAT ?	;// [0.1, 2.0]       default: 0.83
	lReflections		DWORD ?	;// [-10000, 1000]   default: -2602 mB
	flReflectionsDelay	FLOAT ?	;// [0.0, 0.3]       default: 0.007 s
	lReverb			DWORD ?	;// [-10000, 2000]   default: 200 mB
	flReverbDelay		FLOAT ?	;// [0.0, 0.1]       default: 0.011 s
	flDiffusion		FLOAT ?	;// [0.0, 100.0]     default: 100.0 %
	flDensity		FLOAT ?	;// [0.0, 100.0]     default: 100.0 %
	flHFReference		FLOAT ?	;// [20.0, 20000.0]  default: 5000.0 Hz
_DSFXI3DL2Reverb ends

DSFXI3DL2Reverb			typedef _DSFXI3DL2Reverb 
LPCDSFXI3DL2Reverb		typedef PTR _DSFXI3DL2Reverb

DSFX_I3DL2REVERB_ROOM_MIN                   equ (-10000)
DSFX_I3DL2REVERB_ROOM_MAX                   equ 0
DSFX_I3DL2REVERB_ROOM_DEFAULT               equ (-1000)

DSFX_I3DL2REVERB_ROOMHF_MIN                 equ (-10000)
DSFX_I3DL2REVERB_ROOMHF_MAX                 equ 0
DSFX_I3DL2REVERB_ROOMHF_DEFAULT             equ (-100)

DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MIN      equ 0.0f
DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_MAX      equ 10.0f
DSFX_I3DL2REVERB_ROOMROLLOFFFACTOR_DEFAULT  equ 0.0f

DSFX_I3DL2REVERB_DECAYTIME_MIN              equ 0.1f
DSFX_I3DL2REVERB_DECAYTIME_MAX              equ 20.0f
DSFX_I3DL2REVERB_DECAYTIME_DEFAULT          equ 1.49f

DSFX_I3DL2REVERB_DECAYHFRATIO_MIN           equ 0.1f
DSFX_I3DL2REVERB_DECAYHFRATIO_MAX           equ 2.0f
DSFX_I3DL2REVERB_DECAYHFRATIO_DEFAULT       equ 0.83f

DSFX_I3DL2REVERB_REFLECTIONS_MIN            equ (-10000)
DSFX_I3DL2REVERB_REFLECTIONS_MAX            equ 1000
DSFX_I3DL2REVERB_REFLECTIONS_DEFAULT        equ (-2602)

DSFX_I3DL2REVERB_REFLECTIONSDELAY_MIN       equ 0.0f
DSFX_I3DL2REVERB_REFLECTIONSDELAY_MAX       equ 0.3f
DSFX_I3DL2REVERB_REFLECTIONSDELAY_DEFAULT   equ 0.007f

DSFX_I3DL2REVERB_REVERB_MIN                 equ (-10000)
DSFX_I3DL2REVERB_REVERB_MAX                 equ 2000
DSFX_I3DL2REVERB_REVERB_DEFAULT             equ (200)

DSFX_I3DL2REVERB_REVERBDELAY_MIN            equ 0.0f
DSFX_I3DL2REVERB_REVERBDELAY_MAX            equ 0.1f
DSFX_I3DL2REVERB_REVERBDELAY_DEFAULT        equ 0.011f

DSFX_I3DL2REVERB_DIFFUSION_MIN              equ 0.0f
DSFX_I3DL2REVERB_DIFFUSION_MAX              equ 100.0f
DSFX_I3DL2REVERB_DIFFUSION_DEFAULT          equ 100.0f

DSFX_I3DL2REVERB_DENSITY_MIN                equ 0.0f
DSFX_I3DL2REVERB_DENSITY_MAX                equ 100.0f
DSFX_I3DL2REVERB_DENSITY_DEFAULT            equ 100.0f

DSFX_I3DL2REVERB_HFREFERENCE_MIN            equ 20.0f
DSFX_I3DL2REVERB_HFREFERENCE_MAX            equ 20000.0f
DSFX_I3DL2REVERB_HFREFERENCE_DEFAULT        equ 5000.0f

DSFX_I3DL2REVERB_QUALITY_MIN                equ 0
DSFX_I3DL2REVERB_QUALITY_MAX                equ 3
DSFX_I3DL2REVERB_QUALITY_DEFAULT            equ 2

_vtIDirectSoundFXI3DL2Reverb MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
	&CastName&_SetPreset			comethod2 ?
	&CastName&_GetPreset			comethod2 ?
	&CastName&_SetQuality			comethod2 ?
	&CastName&_GetQuality			comethod2 ?
ENDM

IDirectSoundFXI3DL2Reverb struct
	_vtIDirectSoundFXI3DL2Reverb	IDirectSoundFXI3DL2Reverb
IDirectSoundFXI3DL2Reverb ends

;//
;// IDirectSoundFXWavesReverb
;//

IID_IDirectSoundFXWavesReverb		TEXTEQU <{046858c3ah,00dc6h,045e3h,{0b7h,060h,0d4h,0eeh,0f1h,06ch,0b3h,025h}}>

_DSFXWavesReverb struct
	fInGain			FLOAT ? ;//[-96.0,0.0]            default: 0.0 dB
	fReverbMix		FLOAT ? ;//[-96.0,0.0]            default: 0.0 db
	fReverbTime		FLOAT ? ;//[0.001,3000.0]         default: 1000.0 ms
	fHighFreqRTRatio	FLOAT ? ;//[0.001,0.999]          default: 0.001
_DSFXWavesReverb ends

DSFXWavesReverb				typedef _DSFXWavesReverb
LPDSFXWavesReverb			typedef PTR _DSFXWavesReverb
LPCDSFXWavesReverb			typedef PTR _DSFXWavesReverb

DSFX_WAVESREVERB_INGAIN_MIN                 equ -96.0f
DSFX_WAVESREVERB_INGAIN_MAX                 equ 0.0f
DSFX_WAVESREVERB_INGAIN_DEFAULT             equ 0.0f
DSFX_WAVESREVERB_REVERBMIX_MIN              equ -96.0f
DSFX_WAVESREVERB_REVERBMIX_MAX              equ 0.0f
DSFX_WAVESREVERB_REVERBMIX_DEFAULT          equ 0.0f
DSFX_WAVESREVERB_REVERBTIME_MIN             equ 0.001f
DSFX_WAVESREVERB_REVERBTIME_MAX             equ 3000.0f
DSFX_WAVESREVERB_REVERBTIME_DEFAULT         equ 1000.0f
DSFX_WAVESREVERB_HIGHFREQRTRATIO_MIN        equ 0.001f
DSFX_WAVESREVERB_HIGHFREQRTRATIO_MAX        equ 0.999f
DSFX_WAVESREVERB_HIGHFREQRTRATIO_DEFAULT    equ 0.001f

_vtIDirectSoundFXWavesReverb MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
ENDM

IDirectSoundFXWavesReverb struct
	_vtIDirectSoundFXWavesReverb	IDirectSoundFXWavesReverb
IDirectSoundFXWavesReverb ends

;//
;// IDirectSoundCaptureFXAec
;//

IID_IDirectSoundCaptureFXAec		TEXTEQU <{0ad74143dh,0903dh,04ab7h,{080h,066h,028h,0d3h,063h,003h,06dh,065h}}>

_DSCFXAec struct
	fEnable			BOOL ?
	fNoiseFill		BOOL ?
	dwMode			DWORD ?
_DSCFXAec ends

DSCFXAec				typedef _DSCFXAec
LPDSCFXAec				typedef PTR _DSCFXAec
LPCDSCFXAec				typedef PTR _DSCFXAec

;// These match the AEC_MODE_* constants in the DDK's ksmedia.h file
DSCFX_AEC_MODE_PASS_THROUGH                     equ 00h
DSCFX_AEC_MODE_HALF_DUPLEX                      equ 01h
DSCFX_AEC_MODE_FULL_DUPLEX                      equ 02h

;// These match the AEC_STATUS_* constants in ksmedia.h
DSCFX_AEC_STATUS_HISTORY_UNINITIALIZED          equ 00h
DSCFX_AEC_STATUS_HISTORY_CONTINUOUSLY_CONVERGED equ 01h
DSCFX_AEC_STATUS_HISTORY_PREVIOUSLY_DIVERGED    equ 02h
DSCFX_AEC_STATUS_CURRENTLY_CONVERGED            equ 08h

_vtIDirectSoundCaptureFXAec MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
	&CastName&_GetStatus			comethod2 ?
	&CastName&_Reset			comethod1 ?
ENDM

IDirectSoundCaptureFXAec struct
	_vtIDirectSoundCaptureFXAec	IDirectSoundCaptureFXAec
IDirectSoundCaptureFXAec ends

;//
;// IDirectSoundCaptureFXNoiseSuppress
;//

IID_IDirectSoundCaptureFXNoiseSuppress	TEXTEQU <{0ed311e41h,0fbaeh,04175h,{096h,025h,0cdh,008h,054h,0f6h,093h,0cah}}>

_DSCFXNoiseSuppress struct
	fEnable			BOOL ?
_DSCFXNoiseSuppress ends

DSCFXNoiseSuppress			typedef _DSCFXNoiseSuppress
LPDSCFXNoiseSuppress			typedef PTR _DSCFXNoiseSuppress
LPCDSCFXNoiseSuppress			typedef PTR _DSCFXNoiseSuppress

_vtIDirectSoundCaptureFXNoiseSuppress MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_SetAllParameters		comethod2 ?
	&CastName&_GetAllParameters		comethod2 ?
	&CastName&_Reset			comethod1 ?
ENDM

IDirectSoundCaptureFXNoiseSuppress struct
	_vtIDirectSoundCaptureFXNoiseSuppress	IDirectSoundCaptureFXNoiseSuppress
IDirectSoundCaptureFXNoiseSuppress ends

;//
;// IDirectSoundFullDuplex
;//


LPDIRECTSOUNDFULLDUPLEX			typedef PTR IDirectSoundFullDuplex

IID_IDirectSoundFullDuplex		TEXTEQU <{0edcb4c7ah,0daabh,04216h,{0a4h,02eh,06ch,050h,059h,06dh,0dch,01dh}}>


_vtIDirectSoundFullDuplex MACRO CastName:REQ
	_vtIUnknown CastName
	&CastName&_Initialize			comethod9 ?
ENDM

IDirectSoundFullDuplex struct
	_vtIDirectSoundFullDuplex	IDirectSoundFullDuplex
IDirectSoundFullDuplex ends

endif ;// DIRECTSOUND_VERSION >= 0x0800

;//
;// Return Codes
;//

;// The function completed successfully
DS_OK				equ S_OK

;// The call succeeded, but we had to substitute the 3D algorithm
DS_NO_VIRTUALIZATION		TEXTEQU MAKE_HRESULT(0, _FACDS, 10)

;// The call failed because resources (such as a priority level)
;// were already being used by another caller
DSERR_ALLOCATED			TEXTEQU MAKE_DSHRESULT(10)

;// The control (vol, pan, etc.) requested by the caller is not available
DSERR_CONTROLUNAVAIL		TEXTEQU MAKE_DSHRESULT(30)

;// An invalid parameter was passed to the returning function
DSERR_INVALIDPARAM		equ E_INVALIDARG

;// This call is not valid for the current state of this object
DSERR_INVALIDCALL		TEXTEQU MAKE_DSHRESULT(50)

;// An undetermined error occurred inside the DirectSound subsystem
DSERR_GENERIC			equ E_FAIL

;// The caller does not have the priority level required for the function to
;// succeed
DSERR_PRIOLEVELNEEDED		TEXTEQU MAKE_DSHRESULT(70)

;// Not enough free memory is available to complete the operation
DSERR_OUTOFMEMORY		equ E_OUTOFMEMORY

;// The specified WAVE format is not supported
DSERR_BADFORMAT			TEXTEQU MAKE_DSHRESULT(100)

;// The function called is not supported at this time
DSERR_UNSUPPORTED		equ E_NOTIMPL

;// No sound driver is available for use
DSERR_NODRIVER			TEXTEQU MAKE_DSHRESULT(120)

;// This object is already initialized
DSERR_ALREADYINITIALIZED	TEXTEQU MAKE_DSHRESULT(130)

;// This object does not support aggregation
DSERR_NOAGGREGATION		equ CLASS_E_NOAGGREGATION

;// The buffer memory has been lost, and must be restored
DSERR_BUFFERLOST		TEXTEQU MAKE_DSHRESULT(150)

;// Another app has a higher priority level, preventing this call from
;// succeeding
DSERR_OTHERAPPHASPRIO		TEXTEQU MAKE_DSHRESULT(160)

;// This object has not been initialized
DSERR_UNINITIALIZED		TEXTEQU MAKE_DSHRESULT(170)

;// The requested COM interface is not available
DSERR_NOINTERFACE		equ E_NOINTERFACE

;// Access is denied
DSERR_ACCESSDENIED		equ E_ACCESSDENIED

;// Tried to create a DSBCAPS_CTRLFX buffer shorter than DSBSIZE_FX_MIN milliseconds
DSERR_BUFFERTOOSMALL		TEXTEQU MAKE_DSHRESULT(180)

;// Attempt to use DirectSound 8 functionality on an older DirectSound object
DSERR_DS8_REQUIRED		TEXTEQU MAKE_DSHRESULT(190)

;// A circular loop of send effects was detected
DSERR_SENDLOOP			TEXTEQU MAKE_DSHRESULT(200)

;// The GUID specified in an audiopath file does not match a valid MIXIN buffer
DSERR_BADSENDBUFFERGUID		TEXTEQU MAKE_DSHRESULT(210)

;// The object requested was not found (numerically equal to DMUS_E_NOT_FOUND)
DSERR_OBJECTNOTFOUND		TEXTEQU MAKE_DSHRESULT(4449)

;// The effects requested could not be found on the system, or they were found
;// but in the wrong order, or in the wrong hardware/software locations.
DSERR_FXUNAVAILABLE		TEXTEQU MAKE_DSHRESULT(220)

;//
;// Flags
;//

DSCAPS_PRIMARYMONO          equ 000000001h
DSCAPS_PRIMARYSTEREO        equ 000000002h
DSCAPS_PRIMARY8BIT          equ 000000004h
DSCAPS_PRIMARY16BIT         equ 000000008h
DSCAPS_CONTINUOUSRATE       equ 000000010h
DSCAPS_EMULDRIVER           equ 000000020h
DSCAPS_CERTIFIED            equ 000000040h
DSCAPS_SECONDARYMONO        equ 000000100h
DSCAPS_SECONDARYSTEREO      equ 000000200h
DSCAPS_SECONDARY8BIT        equ 000000400h
DSCAPS_SECONDARY16BIT       equ 000000800h

DSSCL_NORMAL                equ 000000001h
DSSCL_PRIORITY              equ 000000002h
DSSCL_EXCLUSIVE             equ 000000003h
DSSCL_WRITEPRIMARY          equ 000000004h

DSSPEAKER_DIRECTOUT         equ 000000000h
DSSPEAKER_HEADPHONE         equ 000000001h
DSSPEAKER_MONO              equ 000000002h
DSSPEAKER_QUAD              equ 000000003h
DSSPEAKER_STEREO            equ 000000004h
DSSPEAKER_SURROUND          equ 000000005h
DSSPEAKER_5POINT1           equ 000000006h
DSSPEAKER_7POINT1           equ 000000007h

DSSPEAKER_GEOMETRY_MIN      equ 000000005h ;//   5 degrees
DSSPEAKER_GEOMETRY_NARROW   equ 00000000Ah ;//  10 degrees
DSSPEAKER_GEOMETRY_WIDE     equ 000000014h ;//  20 degrees
DSSPEAKER_GEOMETRY_MAX      equ 0000000B4h ;// 180 degrees

;DSSPEAKER_COMBINED(c, g)    ((DWORD)(((BYTE)(c)) | ((DWORD)((BYTE)(g))) << 16))

DSSPEAKER_COMBINED MACRO c:REQ,g:REQ
	EXITM %((DWORD)(((BYTE)(c)) or ((DWORD)((BYTE)(g))) shl 16))
ENDM

;DSSPEAKER_CONFIG(a)         ((BYTE)(a))
DSSPEAKER_CONFIG MACRO a:REQ
	EXITM %((BYTE)(a))
ENDM

;DSSPEAKER_GEOMETRY(a)       ((BYTE)(((DWORD)(a) >> 16) & 0x000FF))
DSSPEAKER_GEOMETRY MACRO a:REQ
	EXITM %((BYTE)(((DWORD)(a) shr 16) and 0FFh))
ENDM

DSBCAPS_PRIMARYBUFFER       equ 000000001h
DSBCAPS_STATIC              equ 000000002h
DSBCAPS_LOCHARDWARE         equ 000000004h
DSBCAPS_LOCSOFTWARE         equ 000000008h
DSBCAPS_CTRL3D              equ 000000010h
DSBCAPS_CTRLFREQUENCY       equ 000000020h
DSBCAPS_CTRLPAN             equ 000000040h
DSBCAPS_CTRLVOLUME          equ 000000080h
DSBCAPS_CTRLPOSITIONNOTIFY  equ 000000100h
DSBCAPS_CTRLFX              equ 000000200h
DSBCAPS_STICKYFOCUS         equ 000004000h
DSBCAPS_GLOBALFOCUS         equ 000008000h
DSBCAPS_GETCURRENTPOSITION2 equ 000010000h
DSBCAPS_MUTE3DATMAXDISTANCE equ 000020000h
DSBCAPS_LOCDEFER            equ 000040000h

DSBPLAY_LOOPING             equ 000000001h
DSBPLAY_LOCHARDWARE         equ 000000002h
DSBPLAY_LOCSOFTWARE         equ 000000004h
DSBPLAY_TERMINATEBY_TIME    equ 000000008h
DSBPLAY_TERMINATEBY_DISTANCE    equ 0000000010h
DSBPLAY_TERMINATEBY_PRIORITY    equ 0000000020h

DSBSTATUS_PLAYING           equ 000000001h
DSBSTATUS_BUFFERLOST        equ 000000002h
DSBSTATUS_LOOPING           equ 000000004h
DSBSTATUS_LOCHARDWARE       equ 000000008h
DSBSTATUS_LOCSOFTWARE       equ 000000010h
DSBSTATUS_TERMINATED        equ 000000020h

DSBLOCK_FROMWRITECURSOR     equ 000000001h
DSBLOCK_ENTIREBUFFER        equ 000000002h

DSBFREQUENCY_ORIGINAL       equ 0
DSBFREQUENCY_MIN            equ 100
if DIRECTSOUND_VERSION ge 00900h
DSBFREQUENCY_MAX            equ 200000
else
DSBFREQUENCY_MAX            equ 100000
endif

DSBPAN_LEFT                 equ -10000
DSBPAN_CENTER               equ 0
DSBPAN_RIGHT                equ 10000

DSBVOLUME_MIN               equ -10000
DSBVOLUME_MAX               equ 0

DSBSIZE_MIN                 equ 4
DSBSIZE_MAX                 equ 00FFFFFFFh
DSBSIZE_FX_MIN              equ 150  ;// NOTE: Milliseconds, not bytes

DS3DMODE_NORMAL             equ 000000000h
DS3DMODE_HEADRELATIVE       equ 000000001h
DS3DMODE_DISABLE            equ 000000002h

DS3D_IMMEDIATE              equ 000000000h
DS3D_DEFERRED               equ 000000001h

DS3D_MINDISTANCEFACTOR      equ 1.175494351e-38f ;FLT_MIN
DS3D_MAXDISTANCEFACTOR      equ 3.402823466e+38f ;FLT_MAX
DS3D_DEFAULTDISTANCEFACTOR  equ 1.0f

DS3D_MINROLLOFFFACTOR       equ 0.0f
DS3D_MAXROLLOFFFACTOR       equ 10.0f
DS3D_DEFAULTROLLOFFFACTOR   equ 1.0f

DS3D_MINDOPPLERFACTOR       equ 0.0f
DS3D_MAXDOPPLERFACTOR       equ 10.0f
DS3D_DEFAULTDOPPLERFACTOR   equ 1.0f

DS3D_DEFAULTMINDISTANCE     equ 1.0f
DS3D_DEFAULTMAXDISTANCE     equ 1000000000.0f

DS3D_MINCONEANGLE           equ 0
DS3D_MAXCONEANGLE           equ 360
DS3D_DEFAULTCONEANGLE       equ 360

DS3D_DEFAULTCONEOUTSIDEVOLUME equ DSBVOLUME_MAX

;// IDirectSoundCapture attributes

DSCCAPS_EMULDRIVER          equ DSCAPS_EMULDRIVER
DSCCAPS_CERTIFIED           equ DSCAPS_CERTIFIED
DSCCAPS_MULTIPLECAPTURE     equ 000000001h

;// IDirectSoundCaptureBuffer attributes

DSCBCAPS_WAVEMAPPED         equ 080000000h

if DIRECTSOUND_VERSION ge 00800h
DSCBCAPS_CTRLFX             equ 000000200h
endif


DSCBLOCK_ENTIREBUFFER       equ 000000001h

DSCBSTATUS_CAPTURING        equ 000000001h
DSCBSTATUS_LOOPING          equ 000000002h

DSCBSTART_LOOPING           equ 000000001h

DSBPN_OFFSETSTOP            equ 0FFFFFFFFh

DS_CERTIFIED                equ 000000000h
DS_UNCERTIFIED              equ 000000001h


;//
;// Flags for the I3DL2 effects
;//

;//
;// I3DL2 Material Presets
;//

DSFX_I3DL2_MATERIAL_PRESET_SINGLEWINDOW	equ 0
DSFX_I3DL2_MATERIAL_PRESET_DOUBLEWINDOW	equ 1
DSFX_I3DL2_MATERIAL_PRESET_THINDOOR	equ 2
DSFX_I3DL2_MATERIAL_PRESET_THICKDOOR	equ 3
DSFX_I3DL2_MATERIAL_PRESET_WOODWALL	equ 4
DSFX_I3DL2_MATERIAL_PRESET_BRICKWALL	equ 5
DSFX_I3DL2_MATERIAL_PRESET_STONEWALL	equ 6
DSFX_I3DL2_MATERIAL_PRESET_CURTAIN	equ 7

I3DL2_MATERIAL_PRESET_SINGLEWINDOW    TEXTEQU <{-2800,0.71f}>
I3DL2_MATERIAL_PRESET_DOUBLEWINDOW    TEXTEQU <{-5000,0.40f}>
I3DL2_MATERIAL_PRESET_THINDOOR        TEXTEQU <{-1800,0.66f}>
I3DL2_MATERIAL_PRESET_THICKDOOR       TEXTEQU <{-4400,0.64f}>
I3DL2_MATERIAL_PRESET_WOODWALL        TEXTEQU <{-4000,0.50f}>
I3DL2_MATERIAL_PRESET_BRICKWALL       TEXTEQU <{-5000,0.60f}>
I3DL2_MATERIAL_PRESET_STONEWALL       TEXTEQU <{-6000,0.68f}>
I3DL2_MATERIAL_PRESET_CURTAIN         TEXTEQU <{-1200,0.15f}>

DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT		equ 0
DSFX_I3DL2_ENVIRONMENT_PRESET_GENERIC		equ 1
DSFX_I3DL2_ENVIRONMENT_PRESET_PADDEDCELL	equ 2
DSFX_I3DL2_ENVIRONMENT_PRESET_ROOM		equ 3
DSFX_I3DL2_ENVIRONMENT_PRESET_BATHROOM		equ 4
DSFX_I3DL2_ENVIRONMENT_PRESET_LIVINGROOM	equ 5
DSFX_I3DL2_ENVIRONMENT_PRESET_STONEROOM		equ 6
DSFX_I3DL2_ENVIRONMENT_PRESET_AUDITORIUM	equ 7
DSFX_I3DL2_ENVIRONMENT_PRESET_CONCERTHALL	equ 8
DSFX_I3DL2_ENVIRONMENT_PRESET_CAVE		equ 9
DSFX_I3DL2_ENVIRONMENT_PRESET_ARENA		equ 10
DSFX_I3DL2_ENVIRONMENT_PRESET_HANGAR		equ 11
DSFX_I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY	equ 12
DSFX_I3DL2_ENVIRONMENT_PRESET_HALLWAY		equ 13
DSFX_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR	equ 14
DSFX_I3DL2_ENVIRONMENT_PRESET_ALLEY		equ 15
DSFX_I3DL2_ENVIRONMENT_PRESET_FOREST		equ 16
DSFX_I3DL2_ENVIRONMENT_PRESET_CITY		equ 17
DSFX_I3DL2_ENVIRONMENT_PRESET_MOUNTAINS		equ 18
DSFX_I3DL2_ENVIRONMENT_PRESET_QUARRY		equ 19
DSFX_I3DL2_ENVIRONMENT_PRESET_PLAIN		equ 20
DSFX_I3DL2_ENVIRONMENT_PRESET_PARKINGLOT	equ 21
DSFX_I3DL2_ENVIRONMENT_PRESET_SEWERPIPE		equ 22
DSFX_I3DL2_ENVIRONMENT_PRESET_UNDERWATER	equ 23
DSFX_I3DL2_ENVIRONMENT_PRESET_SMALLROOM		equ 24
DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM	equ 25
DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEROOM		equ 26
DSFX_I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL	equ 27
DSFX_I3DL2_ENVIRONMENT_PRESET_LARGEHALL		equ 28
DSFX_I3DL2_ENVIRONMENT_PRESET_PLATE		equ 29


;//
;// I3DL2 Reverberation Presets Values
;//

I3DL2_ENVIRONMENT_PRESET_DEFAULT         TEXTEQU <{-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f,   200, 0.011f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_GENERIC         TEXTEQU <{-1000, -100, 0.0f, 1.49f, 0.83f, -2602, 0.007f,   200, 0.011f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_PADDEDCELL      TEXTEQU <{-1000,-6000, 0.0f, 0.17f, 0.10f, -1204, 0.001f,   207, 0.002f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_ROOM            TEXTEQU <{-1000, -454, 0.0f, 0.40f, 0.83f, -1646, 0.002f,    53, 0.003f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_BATHROOM        TEXTEQU <{-1000,-1200, 0.0f, 1.49f, 0.54f,  -370, 0.007f,  1030, 0.011f, 100.0f,  60.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_LIVINGROOM      TEXTEQU <{-1000,-6000, 0.0f, 0.50f, 0.10f, -1376, 0.003f, -1104, 0.004f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_STONEROOM       TEXTEQU <{-1000, -300, 0.0f, 2.31f, 0.64f,  -711, 0.012f,    83, 0.017f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_AUDITORIUM      TEXTEQU <{-1000, -476, 0.0f, 4.32f, 0.59f,  -789, 0.020f,  -289, 0.030f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_CONCERTHALL     TEXTEQU <{-1000, -500, 0.0f, 3.92f, 0.70f, -1230, 0.020f,    -2, 0.029f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_CAVE            TEXTEQU <{-1000,    0, 0.0f, 2.91f, 1.30f,  -602, 0.015f,  -302, 0.022f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_ARENA           TEXTEQU <{-1000, -698, 0.0f, 7.24f, 0.33f, -1166, 0.020f,    16, 0.030f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_HANGAR          TEXTEQU <{-1000,-1000, 0.0f,10.05f, 0.23f,  -602, 0.020f,   198, 0.030f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_CARPETEDHALLWAY TEXTEQU <{-1000,-4000, 0.0f, 0.30f, 0.10f, -1831, 0.002f, -1630, 0.030f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_HALLWAY         TEXTEQU <{-1000, -300, 0.0f, 1.49f, 0.59f, -1219, 0.007f,   441, 0.011f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR   TEXTEQU <{-1000, -237, 0.0f, 2.70f, 0.79f, -1214, 0.013f,   395, 0.020f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_ALLEY           TEXTEQU <{-1000, -270, 0.0f, 1.49f, 0.86f, -1204, 0.007f,    -4, 0.011f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_FOREST          TEXTEQU <{-1000,-3300, 0.0f, 1.49f, 0.54f, -2560, 0.162f,  -613, 0.088f,  79.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_CITY            TEXTEQU <{-1000, -800, 0.0f, 1.49f, 0.67f, -2273, 0.007f, -2217, 0.011f,  50.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_MOUNTAINS       TEXTEQU <{-1000,-2500, 0.0f, 1.49f, 0.21f, -2780, 0.300f, -2014, 0.100f,  27.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_QUARRY          TEXTEQU <{-1000,-1000, 0.0f, 1.49f, 0.83f,-10000, 0.061f,   500, 0.025f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_PLAIN           TEXTEQU <{-1000,-2000, 0.0f, 1.49f, 0.50f, -2466, 0.179f, -2514, 0.100f,  21.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_PARKINGLOT      TEXTEQU <{-1000,    0, 0.0f, 1.65f, 1.50f, -1363, 0.008f, -1153, 0.012f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_SEWERPIPE       TEXTEQU <{-1000,-1000, 0.0f, 2.81f, 0.14f,   429, 0.014f,   648, 0.021f,  80.0f,  60.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_UNDERWATER      TEXTEQU <{-1000,-4000, 0.0f, 1.49f, 0.10f,  -449, 0.007f,  1700, 0.011f, 100.0f, 100.0f, 5000.0f}>

;//
;// Examples simulating 'musical' reverb presets
;//
;// Name       Decay time   Description
;// Small Room    1.1s      A small size room with a length of 5m or so.
;// Medium Room   1.3s      A medium size room with a length of 10m or so.
;// Large Room    1.5s      A large size room suitable for live performances.
;// Medium Hall   1.8s      A medium size concert hall.
;// Large Hall    1.8s      A large size concert hall suitable for a full orchestra.
;// Plate         1.3s      A plate reverb simulation.
;//

I3DL2_ENVIRONMENT_PRESET_SMALLROOM       TEXTEQU <{-1000, -600, 0.0f, 1.10f, 0.83f,  -400, 0.005f,   500, 0.010f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_MEDIUMROOM      TEXTEQU <{-1000, -600, 0.0f, 1.30f, 0.83f, -1000, 0.010f,  -200, 0.020f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_LARGEROOM       TEXTEQU <{-1000, -600, 0.0f, 1.50f, 0.83f, -1600, 0.020f, -1000, 0.040f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_MEDIUMHALL      TEXTEQU <{-1000, -600, 0.0f, 1.80f, 0.70f, -1300, 0.015f,  -800, 0.030f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_LARGEHALL       TEXTEQU <{-1000, -600, 0.0f, 1.80f, 0.70f, -2000, 0.030f, -1400, 0.060f, 100.0f, 100.0f, 5000.0f}>
I3DL2_ENVIRONMENT_PRESET_PLATE           TEXTEQU <{-1000, -200, 0.0f, 1.30f, 0.90f,     0, 0.002f,     0, 0.010f, 100.0f,  75.0f, 5000.0f}>

;//
;// DirectSound3D Algorithms
;//

;// Default DirectSound3D algorithm {00000000-0000-0000-0000-000000000000}
DS3DALG_DEFAULT			equ GUID_NULL

;// No virtualization (Pan3D) {C241333F-1C1B-11d2-94F5-00C04FC28ACA}
DS3DALG_NO_VIRTUALIZATION	TEXTEQU <{0c241333fh,01c1bh,011d2h,{094h,0f5h,000h,0c0h,04fh,0c2h,08ah,0cah}}>

;// High-quality HRTF algorithm {C2413340-1C1B-11d2-94F5-00C04FC28ACA}
DS3DALG_HRTF_FULL		TEXTEQU <{0c2413340h,01c1bh,011d2h,{094h,0f5h,000h,0c0h,04fh,0c2h,08ah,0cah}}>

;// Lower-quality HRTF algorithm {C2413342-1C1B-11d2-94F5-00C04FC28ACA}
DS3DALG_HRTF_LIGHT		TEXTEQU <{0c2413342h,01c1bh,011d2h,{094h,0f5h,000h,0c0h,04fh,0c2h,08ah,0cah}}>


if DIRECTSOUND_VERSION ge 00800h

;//
;// DirectSound Internal Effect Algorithms
;//


;// Gargle {DAFD8210-5711-4B91-9FE3-F75B7AE279BF}
GUID_DSFX_STANDARD_GARGLE	TEXTEQU <{0dafd8210h,05711h,04b91h,{09fh,0e3h,0f7h,05bh,07ah,0e2h,079h,0bfh}}>

;// Chorus {EFE6629C-81F7-4281-BD91-C9D604A95AF6}
GUID_DSFX_STANDARD_CHORUS	TEXTEQU <{0efe6629ch,081f7h,04281h,{0bdh,091h,0c9h,0d6h,004h,0a9h,05ah,0f6h}}>

;// Flanger {EFCA3D92-DFD8-4672-A603-7420894BAD98}
GUID_DSFX_STANDARD_FLANGER	TEXTEQU <{0efca3d92h,0dfd8h,04672h,{0a6h,003h,074h,020h,089h,04bh,0adh,098h}}>

;// Echo/Delay {EF3E932C-D40B-4F51-8CCF-3F98F1B29D5D}
GUID_DSFX_STANDARD_ECHO		TEXTEQU <{0ef3e932ch,0d40bh,04f51h,{08ch,0cfh,03fh,098h,0f1h,0b2h,09dh,05dh}}>

;// Distortion {EF114C90-CD1D-484E-96E5-09CFAF912A21}
GUID_DSFX_STANDARD_DISTORTION	TEXTEQU <{0ef114c90h,0cd1dh,0484eh,{096h,0e5h,009h,0cfh,0afh,091h,02ah,021h}}>

;// Compressor/Limiter {EF011F79-4000-406D-87AF-BFFB3FC39D57}
GUID_DSFX_STANDARD_COMPRESSOR	TEXTEQU <{0ef011f79h,04000h,0406dh,{087h,0afh,0bfh,0fbh,03fh,0c3h,09dh,057h}}>

;// Parametric Equalization {120CED89-3BF4-4173-A132-3CB406CF3231}
GUID_DSFX_STANDARD_PARAMEQ	TEXTEQU <{0120ced89h,03bf4h,04173h,{0a1h,032h,03ch,0b4h,006h,0cfh,032h,031h}}>

;// I3DL2 Environmental Reverberation: Reverb (Listener) Effect {EF985E71-D5C7-42D4-BA4D-2D073E2E96F4}
GUID_DSFX_STANDARD_I3DL2REVERB	TEXTEQU <{0ef985e71h,0d5c7h,042d4h,{0bah,04dh,02dh,007h,03eh,02eh,096h,0f4h}}>

;// Waves Reverberation {87FC0268-9A55-4360-95AA-004A1D9DE26C}
GUID_DSFX_WAVES_REVERB		TEXTEQU <{087fc0268h,09a55h,04360h,{095h,0aah,000h,04ah,01dh,09dh,0e2h,06ch}}>

;//
;// DirectSound Capture Effect Algorithms
;//


;// Acoustic Echo Canceller {BF963D80-C559-11D0-8A2B-00A0C9255AC1}
;// Matches KSNODETYPE_ACOUSTIC_ECHO_CANCEL in ksmedia.h
GUID_DSCFX_CLASS_AEC		TEXTEQU <{0BF963D80h,0C559h,011D0h,{08Ah,02Bh,000h,0A0h,0C9h,025h,05Ah,0C1h}}>

;// Microsoft AEC {CDEBB919-379A-488a-8765-F53CFD36DE40}
GUID_DSCFX_MS_AEC		TEXTEQU <{0cdebb919h,0379ah,0488ah,{087h,065h,0f5h,03ch,0fdh,036h,0deh,040h}}>

;// System AEC {1C22C56D-9879-4f5b-A389-27996DDC2810}
GUID_DSCFX_SYSTEM_AEC		TEXTEQU <{01c22c56dh,09879h,04f5bh,{0a3h,089h,027h,099h,06dh,0dch,028h,010h}}>

;// Noise Supression {E07F903F-62FD-4e60-8CDD-DEA7236665B5}
;// Matches KSNODETYPE_NOISE_SUPPRESS in post Windows ME DDK's ksmedia.h
GUID_DSCFX_CLASS_NS		TEXTEQU <{0e07f903fh,062fdh,04e60h,{08ch,0ddh,0deh,0a7h,023h,066h,065h,0b5h}}>

;// Microsoft Noise Suppresion {11C5C73B-66E9-4ba1-A0BA-E814C6EED92D}
GUID_DSCFX_MS_NS		TEXTEQU <{011c5c73bh,066e9h,04ba1h,{0a0h,0bah,0e8h,014h,0c6h,0eeh,0d9h,02dh}}>

;// System Noise Suppresion {5AB0882E-7274-4516-877D-4EEE99BA4FD0}
GUID_DSCFX_SYSTEM_NS		TEXTEQU <{05ab0882eh,07274h,04516h,{087h,07dh,04eh,0eeh,099h,0bah,04fh,0d0h}}>

endif ;// DIRECTSOUND_VERSION >= 0x0800

endif ;// __DSOUND_INCLUDED__

