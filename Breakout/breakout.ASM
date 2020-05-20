    .386
    .model flat, stdcall
    option casemap :none

    include bitblt.inc    ;todos os includes e variaveis
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

    LOCAL wc   :WNDCLASSEX
    LOCAL msg  :MSG

    LOCAL Wwd  :DWORD
    LOCAL Wht  :DWORD
    LOCAL Wtx  :DWORD
    LOCAL Wty  :DWORD

    invoke LoadIcon,hInst,500 
    mov hIcon, eax

    szText szClassName,"BreakoutClass"

    mov wc.cbSize,         sizeof WNDCLASSEX
    mov wc.style,          CS_BYTEALIGNWINDOW
    mov wc.lpfnWndProc,    offset WndProc
    mov wc.cbClsExtra,     NULL
    mov wc.cbWndExtra,     NULL
    m2m wc.hInstance,      hInst
    mov wc.hbrBackground,  COLOR_WINDOW+3
    mov wc.lpszMenuName,   NULL 
    mov wc.lpszClassName,  offset szClassName
    m2m wc.hIcon,          hIcon
    invoke LoadCursor,NULL,IDC_ARROW
    mov wc.hCursor,        eax
    m2m wc.hIconSm,        hIcon
    invoke RegisterClassEx, ADDR wc

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

    LOCAL hDC    :DWORD
    LOCAL Ps     :PAINTSTRUCT
    LOCAL rect   :RECT
	 
    .if uMsg == WM_CREATE
		mov barraPos.y, 490
		mov barraPos.x, 200

        mov bolaPos.x, 242
        mov bolaPos.y, 475
		
		invoke CreateEvent,NULL,FALSE,FALSE,NULL
		mov    hEventStart,eax
		
		mov    eax,OFFSET ThreadBolaProc
		invoke CreateThread,NULL,NULL,eax,\
		                    NULL,NORMAL_PRIORITY_CLASS,\
		                    ADDR ThreadBolaID
		mov    hThreadBola,eax
    
    .elseif uMsg == WM_MOUSEMOVE
        mov eax,lParam
    	and eax,0ffffh
    	mov barraPosMouse.x, eax
        invoke InvalidateRect,hWnd,NULL,FALSE ;a flag esta como false já que na tread o fundo é redesenhado
		
    .elseif uMsg == WM_PAINT
        invoke BeginPaint,hWin,ADDR Ps
        mov hDC, eax
        
        invoke Blocos_Proc,hWin,hDC
        invoke Barra_Proc,hWin,hDC
        invoke Bola_Proc,hWin,hDC
        invoke EndPaint,hWin,ADDR Ps
        return 0
   .elseif uMsg==WM_COLLISION
        push edx
        push eax
        push edi
        push ebx

        mov eax, movimentoY
        sub bolaPos.y, eax

        mov eax, movimentoX
        add bolaPos.x, eax

        ;mov edi, bolaPos.x
        ;invoke wsprintf, offset buffer, offset format, edi
        ;invoke GetClientRect, hWin, ADDR rect
        ;invoke DrawText, hDC, ADDR buffer, -1, ADDR rect, DT_BOTTOM

        ;#########################################################################
        ;COLISÃO COM AS BORDAS DA TELA

        .if bolaPos.x >= 475
            push edi
            mov eax, movimentoX
            mov edi, -1
            imul eax, edi
            mov movimentoX, eax
            pop edi
        .endif
		.if bolaPos.y <= 10
            push edi
            mov eax, movimentoY
            mov edi, -1
            imul eax, edi
            mov movimentoY, eax
            pop edi
		.endif 
        .if bolaPos.y >= 600
            mov bolaPos.x, 242
            mov bolaPos.y, 470
            push edi
            mov eax, movimentoY
            mov edi, -1
            imul eax, edi
            mov movimentoY, eax
            pop edi
        .endif

        ;#########################################################################
        ;COLISÃO COM A BARRA

        mov edi, bolaPos.x
        add ballcenterx, 8
        add ballcenterx, edi

        mov ebx, barraPosMouse.x
        add barracenterx, 50
        add barracenterx, ebx

        xor eax, eax
        mov eax, bolaPos.x ; bolaPos.x + 16
        add eax, 16
        .if eax > barraPosMouse.x
            xor eax, eax
            mov eax, barraPosMouse.x ; barraPos.x + 100
            add eax, 100
            .if bolaPos.x < eax
                xor eax, eax
                mov eax, bolaPos.y ;bolaPos.y + 16
                add eax, 16
                .if eax > barraPos.y
                    xor eax, eax
                    mov eax, barraPos.y ; barraPos.y + 16
                    add eax, 16
                    .if bolaPos.y < eax
                        xor eax, eax
                        ;invoke MessageBox, NULL, addr MsgBoxText, addr MsgBoxCaption, MB_OK

                        mov ebx, barracenterx
                        mov edi, barraPos.x
                        .if bolaPos.x < ebx && ballcenterx != ebx
                            mov eax, movimentoX
                            mov edi, -1
                            imul eax, edi
                            mov movimentoX, eax
                        .endif
                        mov eax, movimentoY
                        mov edi, -1
                        imul eax, edi
                        mov movimentoY, eax
                    .endif
                .endif
            .endif
        .endif
        pop ebx
        pop edi
        pop eax
        pop edx
		invoke InvalidateRect,hWnd,NULL,TRUE
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

    shr sDim, 1
    shr wDim, 1
    mov eax, wDim
    sub sDim, eax

    return sDim

TopXY endp

; #########################################################################

Barra_Proc proc hWin:DWORD, hDC:DWORD

    LOCAL hOld:DWORD
    LOCAL memDC :DWORD
    invoke CreateCompatibleDC,hDC
    mov memDC, eax
	invoke SelectObject,memDC,hBmp2
    mov hOld, eax    

    .if barraPosMouse.x != NULL
        INVOKE  TransparentBlt,hDC,barraPosMouse.x,barraPos.y,100,16,memDC,0,352,32,32,CREF_TRANSPARENT
    .endif
    .if barraPosMouse.x <= 400
        INVOKE  TransparentBlt,hDC,barraPosMouse.x,barraPos.y,100,16,memDC,0,352,32,32,CREF_TRANSPARENT
    .else
        INVOKE  TransparentBlt,hDC,400,barraPos.y,100,16,memDC,0,352,32,32,CREF_TRANSPARENT
    .endif  

    invoke SelectObject,hDC,hOld
    invoke DeleteDC,memDC

    return 0

Barra_Proc endp

; #########################################################################

Blocos_Proc proc hWin:DWORD, hDC:DWORD

    LOCAL hOld :DWORD
    LOCAL memDC :DWORD
    LOCAL aux :DWORD
    invoke CreateCompatibleDC,hDC
    mov memDC, eax
	invoke SelectObject,memDC,hBmp2
    mov hOld, eax

    push esi
    push eax

    mov esi, 0 ;indice do vetor de posiçoes x
    mov blocoPos.x, 0
    mov blocoPos.y, 50
    mov spriteAtual, 384
    .WHILE blocoPos.y <= 130
        .WHILE blocoPos.x <= 400
            .IF blocos [esi].break == TRUE
                INVOKE  TransparentBlt,hDC,blocoPos.x,blocoPos.y,100,16,memDC,0,spriteAtual,32,32,CREF_TRANSPARENT
            .ENDIF

            mov eax, blocoPos.x
            mov blocos [esi].X, eax
            
            mov eax, blocoPos.y
            mov blocos [esi].X, eax

            add blocoPos.x, 100
            add esi, TYPE BLOCO
        .ENDW
        add blocoPos.y, 16
        add spriteAtual, 32
        mov blocoPos.x, 0
    .ENDW

    pop eax
    pop esi

    invoke SelectObject,hDC,hOld
    invoke DeleteDC,memDC

    return 0
Blocos_Proc endp

; #########################################################################

Bola_Proc proc hWin:DWORD, hDC:DWORD
    LOCAL hOld:DWORD
    LOCAL memDC :DWORD
 
    invoke CreateCompatibleDC,hDC
    mov memDC, eax
    
	invoke SelectObject,memDC,hBmp2
    mov hOld, eax

    INVOKE  TransparentBlt,hDC,bolaPos.x,bolaPos.y,16,16,memDC,0,352,32,32,CREF_TRANSPARENT

    invoke SelectObject,hDC,hOld
    invoke DeleteDC,memDC

    return 0
Bola_Proc endp

; ########################################################################

ThreadBolaProc PROC USES ecx Param:DWORD

    invoke WaitForSingleObject,hEventStart,40
	.IF eax == WAIT_TIMEOUT	
	    invoke PostMessage,hWnd,WM_COLLISION,NULL,NULL
	    jmp   ThreadBolaProc     
	.ELSEIF eax == WAIT_OBJECT_0	
	    invoke PostMessage,hWnd,WM_COLLISION,NULL,NULL
	    jmp   ThreadBolaProc
    .ENDIF
        
    jmp   ThreadBolaProc
        
    ret
ThreadBolaProc ENDP

end start