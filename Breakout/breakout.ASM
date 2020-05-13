; #########################################################################

    .386
    .model flat, stdcall  ; 32 bit memory model
    option casemap :none  ; case sensitive

    include bitblt.inc    ; local includes for this file

	; código de link para imagem no arquivo RC
	b2			equ		111

	CREF_TRANSPARENT  EQU 0FF00FFh
	CREF_TRANSPARENT2 EQU 0FF0000h


; #########################################################################

.code

start:
    invoke GetModuleHandle, NULL
    mov hInstance, eax
 
    invoke LoadBitmap,hInstance, b2
    mov hBmp2, eax

    invoke GetCommandLine
    mov CommandLine, eax

    invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
    invoke ExitProcess,eax

; #########################################################################

WinMain proc hInst     :DWORD,
             hPrevInst :DWORD,
             CmdLine   :DWORD,
             CmdShow   :DWORD

    ;====================
    ; Put LOCALs on stack
    ;====================

    LOCAL wc   :WNDCLASSEX
    LOCAL msg  :MSG

    LOCAL Wwd  :DWORD
    LOCAL Wht  :DWORD
    LOCAL Wtx  :DWORD
    LOCAL Wty  :DWORD

    ;==================================================
    ; Fill WNDCLASSEX structure with required variables
    ;==================================================

    invoke LoadIcon,hInst,500    ; icon ID
    mov hIcon, eax

    szText szClassName,"BreakoutClass"

    mov wc.cbSize,         sizeof WNDCLASSEX
    mov wc.style,          CS_BYTEALIGNWINDOW
    mov wc.lpfnWndProc,    offset WndProc
    mov wc.cbClsExtra,     NULL
    mov wc.cbWndExtra,     NULL
    m2m wc.hInstance,      hInst
    mov wc.hbrBackground,  COLOR_WINDOW+3
    mov wc.lpszMenuName,   NULL   ;OFFSET MenuName
    mov wc.lpszClassName,  offset szClassName
    m2m wc.hIcon,          hIcon
    invoke LoadCursor,NULL,IDC_ARROW
    mov wc.hCursor,        eax
    m2m wc.hIconSm,        hIcon
    invoke RegisterClassEx, ADDR wc

    ;================================
    ; Centre window at following size
    ;================================

    mov Wwd, 500
    mov Wht, 600

    invoke GetSystemMetrics,SM_CXSCREEN
    invoke TopXY,Wwd,eax
    mov Wtx, eax

    invoke GetSystemMetrics,SM_CYSCREEN
    invoke TopXY,Wht,eax
    mov Wty, eax

    invoke CreateWindowEx,WS_EX_LEFT,
                          ADDR szClassName,
                          ADDR szDisplayName,
                          WS_OVERLAPPED + WS_CAPTION + WS_SYSMENU + WS_MINIMIZEBOX,
                          Wtx,Wty,Wwd,Wht,
                          NULL,NULL,
                          hInst,NULL
    mov   hWnd,eax

    invoke ShowWindow,hWnd,SW_SHOWNORMAL
    invoke UpdateWindow,hWnd

    ;===================================
    ; Loop until PostQuitMessage is sent
    ;===================================

    StartLoop:
      invoke GetMessage,ADDR msg,NULL,0,0
      cmp eax, 0
      je ExitLoop
      invoke TranslateMessage, ADDR msg
      invoke DispatchMessage,  ADDR msg
      jmp StartLoop
    ExitLoop:

      return msg.wParam

WinMain endp

; #########################################################################

WndProc proc hWin   :DWORD,
             uMsg   :DWORD,
             wParam :DWORD,
             lParam :DWORD

    LOCAL var    :DWORD
    LOCAL caW    :DWORD
    LOCAL caH    :DWORD
    LOCAL Rct    :RECT
    LOCAL hDC    :DWORD
    LOCAL Ps     :PAINTSTRUCT

    .if uMsg == WM_COMMAND
    ;======== menu commands ========
		mov eax,wParam
		 
    .elseif uMsg == WM_CREATE
		mov barraPos.y, 490
		mov barraPos.x, 200; 180

        mov bolaPos.x, 100
        mov bolaPos.y, 300
		
		invoke CreateEvent,NULL,FALSE,FALSE,NULL
		mov    hEventStart,eax
		
		mov    eax,OFFSET ThreadBolaProc
		invoke CreateThread,NULL,NULL,eax,\
		                    NULL,NORMAL_PRIORITY_CLASS,\
		                    ADDR ThreadID
		mov    hThread,eax
		
    .elseif uMsg == WM_SIZE
;    // obter o tamanho da janela
    
    .elseif uMsg == WM_LBUTTONDOWN

    .elseif uMsg==WM_CHAR
        push wParam
        pop  char
        invoke InvalidateRect,hWnd,NULL,TRUE
		
    .elseif uMsg == WM_PAINT
        invoke BeginPaint,hWin,ADDR Ps
        mov hDC, eax
        
        invoke TextOut,hDC,0,0,ADDR barraPos.x,1
        
        invoke Blocos_Proc,hWin,hDC
        invoke Paint_Proc,hWin,hDC
        invoke EndPaint,hWin,ADDR Ps
        return 0
   .elseif uMsg==WM_FINISH
        ; QUANDO ATINGIR O BLOCO PROGRAMAR AQUI (QUANDO ATINGIR CHAMAR INVALIDRECT)
		sub bolaPos.y, 1
		
		.if bolaPos.y <= 0
			mov bolaPos.y,20
			mov bolaPos.x,20
		.endif 
		;invoke InvalidateRect,hWnd,NULL,TRUE

    .elseif uMsg == WM_DESTROY
    	mov  EventStop,TRUE
        invoke PostQuitMessage,NULL
        return 0 
    .endif

    invoke DefWindowProc,hWin,uMsg,wParam,lParam

    ret

WndProc endp

; ########################################################################

TopXY proc wDim:DWORD, sDim:DWORD

    shr sDim, 1      ; divide screen dimension by 2
    shr wDim, 1      ; divide window dimension by 2
    mov eax, wDim    ; copy window dimension into eax
    sub sDim, eax    ; sub half win dimension from half screen dimension

    return sDim

TopXY endp

; #########################################################################

Paint_Proc proc hWin:DWORD, hDC:DWORD

    LOCAL hOld:DWORD
    LOCAL memDC :DWORD
 
    invoke CreateCompatibleDC,hDC
    mov memDC, eax
    
	invoke SelectObject,memDC,hBmp2  ; selecionei o novo bitmap
    mov hOld, eax         

    .if char == 61h || char == 41h ;left
        .if barraPos.x != NULL
            sub barraPos.x, 20
            INVOKE  TransparentBlt,hDC,barraPos.x,barraPos.y,100,15,memDC,0,352,32,32,CREF_TRANSPARENT
        .else
            INVOKE  TransparentBlt,hDC,barraPos.x,barraPos.y,100,15,memDC,0,352,32,32,CREF_TRANSPARENT
        .endif
    .elseif char == 64h || char == 44h ;right
        .if barraPos.x != 400
            add barraPos.x, 20
            INVOKE  TransparentBlt,hDC,barraPos.x,barraPos.y,100,15,memDC,0,352,32,32,CREF_TRANSPARENT
        .else
            INVOKE  TransparentBlt,hDC,barraPos.x,barraPos.y,100,15,memDC,0,352,32,32,CREF_TRANSPARENT
        .endif
    .else ;n apertou nada
        INVOKE  TransparentBlt,hDC,barraPos.x,barraPos.y,100,15,memDC,0,352,32,32,CREF_TRANSPARENT
    .endif 

    invoke SelectObject,hDC,hOld
    invoke DeleteDC,memDC

    return 0

Paint_Proc endp

Blocos_Proc proc hWin:DWORD, hDC:DWORD

    LOCAL hOld:DWORD
    LOCAL memDC :DWORD
 
    invoke CreateCompatibleDC,hDC
    mov memDC, eax
    
	invoke SelectObject,memDC,hBmp2  ; selecionei o novo bitmap
    mov hOld, eax

    mov blocoPos.x, 0
    mov blocoPos.y, 50
    mov spriteAtual, 384
    .WHILE blocoPos.y <= 110
        .WHILE blocoPos.x <= 450
            INVOKE  TransparentBlt,hDC,blocoPos.x,blocoPos.y,50,15,memDC,0,spriteAtual,32,32,CREF_TRANSPARENT
            add blocoPos.x, 50
        .ENDW
        add blocoPos.y, 15
        add spriteAtual, 32
        mov blocoPos.x, 0
    .ENDW

    invoke SelectObject,hDC,hOld
    invoke DeleteDC,memDC

    return 0
Blocos_Proc endp

Bola_Proc proc hWin:DWORD, hDC:DWORD
    LOCAL hOld:DWORD
    LOCAL memDC :DWORD
 
    invoke CreateCompatibleDC,hDC
    mov memDC, eax
    
	invoke SelectObject,memDC,hBmp2  ; selecionei o novo bitmap
    mov hOld, eax

    INVOKE  TransparentBlt,hDC,bolaPos.x,bolaPos.y,32,32,memDC,0,352,32,32,CREF_TRANSPARENT

    invoke SelectObject,hDC,hOld
    invoke DeleteDC,memDC

    return 0
Bola_Proc endp
; ########################################################################

ThreadBolaProc PROC USES ecx Param:DWORD

    invoke WaitForSingleObject,hEventStart,10 ;INFINITE

	.IF eax == WAIT_TIMEOUT	
	    invoke PostMessage,hWnd,WM_FINISH,NULL,NULL
	    jmp   ThreadBolaProc     
	.ELSEIF eax == WAIT_OBJECT_0	
	    invoke PostMessage,hWnd,WM_FINISH,NULL,NULL
	    jmp   ThreadBolaProc
    .ENDIF
        
    jmp   ThreadBolaProc
        
    ret
ThreadBolaProc ENDP

end start