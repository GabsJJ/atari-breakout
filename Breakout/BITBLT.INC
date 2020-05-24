; #########################################################################

;     include files
;     ~~~~~~~~~~~~~
  include \MASM32\INCLUDE\windows.inc
  include \MASM32\INCLUDE\masm32.inc
  include \MASM32\INCLUDE\gdi32.inc
  include \MASM32\INCLUDE\gdiplus.inc
  include \MASM32\INCLUDE\user32.inc
  include \MASM32\INCLUDE\kernel32.inc
  include \MASM32\INCLUDE\Comctl32.inc
  include \MASM32\INCLUDE\comdlg32.inc
  include \MASM32\INCLUDE\shell32.inc

  INCLUDE \Masm32\Include\msimg32.inc
  INCLUDE \Masm32\Include\oleaut32.inc
  INCLUDE \Masm32\Macros\macros.asm



;     libraries
;     ~~~~~~~~~
  includelib \MASM32\LIB\masm32.lib
  includelib \MASM32\LIB\gdi32.lib
  includelib \MASM32\LIB\gdiplus.lib
  includelib \MASM32\LIB\user32.lib
  includelib \MASM32\LIB\kernel32.lib
  includelib \MASM32\LIB\Comctl32.lib
  includelib \MASM32\LIB\comdlg32.lib
  includelib \MASM32\LIB\shell32.lib

  INCLUDELIB \Masm32\Lib\msimg32.lib
  INCLUDELIB \Masm32\Lib\oleaut32.lib
  INCLUDELIB \Masm32\Lib\msvcrt.lib
  INCLUDELIB \Masm32\Lib\masm32.lib

; #########################################################################

  ;=================
  ; Local prototypes
  ;=================
  WinMain      PROTO :DWORD,:DWORD,:DWORD,:DWORD
  WndProc      PROTO :DWORD,:DWORD,:DWORD,:DWORD
  TopXY        PROTO :DWORD,:DWORD
  FillBuffer   PROTO :DWORD,:DWORD,:BYTE
  Barra_Proc   PROTO :DWORD,:DWORD
  Blocos_Proc  PROTO :DWORD,:DWORD
  Bola_Proc    PROTO :DWORD,:DWORD
  Restaura_Blo PROTO :DWORD,:DWORD

  ;=============
  ; Local macros
  ;=============

  szText MACRO Name, Text:VARARG
    LOCAL lbl
      jmp lbl
        Name db Text,0
      lbl:
  ENDM

  m2m MACRO M1, M2
    push M2
    pop  M1
  ENDM

  return MACRO arg
    mov eax, arg
    ret
  ENDM

.data
  POINTSI STRUCT
    x  SDWORD ?
    y  SDWORD ?
  POINTSI ENDS

  szDisplayName db "Atari Breakout",0
  ClassName     db "BreakoutClass",0
  AppName       db "Atari Breakout",0
  CommandLine   dd 0
  hWnd          dd 0
  hInstance     dd 0
  hIcon         dd 0
  hBmp          dd 0
  hBmp2         dd 0
  ThreadBolaID 	dd 0
  ThreadCollidID dd 0
	ExitCode 	    dd 0
	hThreadBola 	dd 0
  hThreadCollid dd 0
	hEventStart   dd 0
  hEvent2Start  dd 0
  spriteAtual   dd      0
  movimentoY    dd      10
  movimentoX    dd      10
  direcaoX      SDWORD  10
  direcaoY      SDWORD  -10
  ballcenterx   dd      0
  barracenterx  dd      0
  EventStop     BOOL    FALSE
  barraPosMouse POINT   <>
  barraPos      POINT   <>
  blocoPos      POINT   <>
  bolaPos       POINTSI <>
  lRect         RECT    <>

  teste SDWORD 2
  t3    SDWORD 5

  MsgBoxCaption  db "Iczelion Tutorial No.2",0
  MsgBoxText     db "Win32 Assembly is Great!",0

  BLOCO struct ; STRUCT DE CADA BLOCO
    X     DWORD ? 
    Y     DWORD ?
    break BOOL TRUE 
  BLOCO ends
  blocos      BLOCO 25 DUP(<>) 

.const
	IDM_TEST          EQU 1     
	WM_COLLISION      EQU WM_USER+100h
  WM_BOLA_BLOCO     EQU WM_USER+101h
  b2			          EQU 111
	CREF_TRANSPARENT  EQU 0FF00FFh
	CREF_TRANSPARENT2 EQU 0FF0000h