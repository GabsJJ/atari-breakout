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
  Paint_Proc   PROTO :DWORD,:DWORD
  Blocos_Proc  PROTO :DWORD,:DWORD
  Bola_Proc  PROTO :DWORD,:DWORD

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
  szDisplayName db "Atari Breakout",0
  CommandLine   dd 0
  hWnd          dd 0
  hInstance     dd 0
  hIcon         dd 0
  hBmp          dd 0
  hBmp2         dd 0
  memDC2        DWORD 0 
  x	 		        dd 0
  trasp		      dd  0
  achou		      dd  0
  lRect         RECT <>
  hitpoint 	    POINT <>
  posicao       POINT <>
  ThreadID 	    dd 0
	ExitCode 	    dd 0
	hThread 	    dd 0
	hEventStart   dd 0
  barraPos      POINT <>
  blocoPos      POINT <>
  bolaPos       POINT <>
  spriteAtual   dd 0
	hThreadFlag	  dd 0
	ThreadFlagID  dd 0
  ClassName     db "BreakoutClass",0
  AppName       db "Atari Breakout",0
	EventStop     BOOL FALSE
  char WPARAM   20h

.const
	IDM_TEST equ 1     
	WM_FINISH equ WM_USER+100h