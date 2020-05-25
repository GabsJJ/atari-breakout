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
    invoke StartDSound,hWnd,2,44100,16

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

WndProc proc hWin:DWORD, uMsg:DWORD, wParam:DWORD, lParam:DWORD

    LOCAL hDC      :DWORD
    LOCAL Ps       :PAINTSTRUCT
    LOCAL rect     :RECT
	 
    .if uMsg == WM_CREATE
		mov barraPos.y, 490
		mov barraPos.x, 200

        mov bolaPos.x, 242
        mov bolaPos.y, 150
		
		invoke CreateEvent,NULL,FALSE,TRUE,NULL
		mov    hEventStart,eax
        invoke SetEvent,hEventStart

		mov    eax,OFFSET ThreadBolaProc
		invoke CreateThread,NULL,NULL,eax,\
		                    NULL,0,\
		                    ADDR ThreadBolaID
		mov    hThreadBola,eax

        mov    eax,OFFSET ThreadCollidProc
		invoke CreateThread,NULL,NULL,eax,\
		                    NULL,0,\
		                    ADDR ThreadCollidID
		mov    hThreadCollid,eax
    
    .elseif uMsg == WM_MOUSEMOVE
        push eax
        push ebx
        mov eax,lParam
    	and eax,0ffffh
    	mov barraPosMouse.x, eax
        mov ebx, barraPosMouse.x
        mov barracenterx, ebx
        add barracenterx, 50
        invoke InvalidateRect,hWnd,NULL,FALSE ;a flag esta como false já que na tread o fundo é redesenhado
        pop ebx
        pop eax
		ret 
    .elseif uMsg == WM_PAINT
        push eax
        invoke BeginPaint,hWin,ADDR Ps
        mov hDC, eax

        invoke Blocos_Proc,hWin,hDC
        invoke Barra_Proc,hWin,hDC
        invoke Bola_Proc,hWin,hDC
        invoke EndPaint,hWin,ADDR Ps
        pop eax
        ret
   .elseif uMsg==WM_COLLISION
        push edx
        push eax
        push edi
        push ebx
        push ecx
        
        ;soma as direções de x e y da bola para movimentar esta
        mov eax, direcaoY
        sub bolaPos.y, eax
        
        mov eax, direcaoX
        add bolaPos.x, eax

        ;#########################################################################
        ;COLISÃO COM AS BORDAS DA TELA

        mov edi, bolaPos.x
        add edi, 25
        .if bolaPos.x < 10   ;verifica se o x é negativo pegando o ponteiro SDWORD do valor
            call Parede
            mov eax, movimentoX
            mov direcaoX, eax
        .elseif edi > 500
            call Parede
            mov eax, movimentoX
            neg eax
            mov direcaoX, eax
        .endif
        
        mov edi, bolaPos.y
        add edi, 45
		.if SDWORD ptr bolaPos.y < 0
            mov eax, movimentoY
            neg eax
            mov direcaoY, eax
            call Parede
        .elseif edi > 600
            mov eax, movimentoY
            mov direcaoY, eax
            call Parede
        .endif

        ;#########################################################################
        ;COLISÃO COM A BARRA

        mov edi, bolaPos.x
        mov ballcenterx, edi
        add ballcenterx, 8

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
                        call Paddle
                        xor eax, eax
                        mov ebx, barracenterx
                        ;se o centro da bola é maior/menor q o centro da barra
                        ;a direção será determinada
                        .if ballcenterx < ebx
                            mov eax, movimentoX
                            neg eax
                            mov direcaoX, eax
                        .else
                            mov eax, movimentoX
                            mov direcaoX, eax
                        .endif

                        mov eax, movimentoY
                        mov direcaoY, eax
                    .endif
                .endif
            .endif
        .endif
        pop eax
        pop edi
        pop ebx
        pop ecx
        pop edx
		invoke InvalidateRect,hWnd,NULL,TRUE
    .elseif uMsg == WM_BOLA_BLOCO
        ;vai ficar verificando se o jogo acabou
        push ebx
        push esi
        mov bl, 0
        mov esi, 0
        .WHILE bl < 25
            .if blocos [esi].break == TRUE
                add esi, TYPE BLOCO ;vai pro proximo bloco
                add bl, 1
            .else
                .BREAK
            .endif  
        .ENDW
        .if bl == 25
            invoke Restaura_Blo, hDC 
        .endif
        pop esi
        pop ebx
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
    push eax
    invoke CreateCompatibleDC,hDC
    mov memDC, eax
	invoke SelectObject,memDC,hBmp2
    mov hOld, eax    

    ;verifica se o mouse esta nas bordas da tela
    ;caso esteja, mesmo que o mouse saia da janela, a barra gruda na borda
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
    pop eax
    ret

Barra_Proc endp

; #########################################################################

Blocos_Proc proc hWin:DWORD, hDC:DWORD

    LOCAL hOld :DWORD
    LOCAL memDC :DWORD
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
            ;desenha o bloco apenas se este não esta quebrado
            .IF blocos [esi].break == FALSE
                INVOKE  TransparentBlt,hDC,blocoPos.x,blocoPos.y,100,16,memDC,0,spriteAtual,32,32,CREF_TRANSPARENT
            .ENDIF

            mov eax, blocoPos.x
            mov blocos [esi].X, eax
            
            mov eax, blocoPos.y
            mov blocos [esi].Y, eax

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

; ########################################################################

ThreadCollidProc PROC USES ecx Param:DWORD
    LOCAL overL    : SDWORD
    LOCAL overR    : SDWORD
    LOCAL overT    : SDWORD
    LOCAL overB    : SDWORD
    LOCAL minOverX : SDWORD
    LOCAL minOverY : SDWORD
    invoke WaitForSingleObject, hEventStart, 40

    push edx
    push eax
    push edi
    push ebx
    push ecx

    ;#########################################################################
    ;COLISÃO BOLA-BLOCO

    mov bl, 0
    mov esi, 0
    .WHILE bl < 25
        .if blocos[esi].break == FALSE
            xor eax, eax
            mov eax, bolaPos.x ; bolaPos.x + 16
            add eax, 16
            .if eax > blocos[esi].X
                xor eax, eax
                mov eax, blocos[esi].X ; blocoPos.x + 100
                add eax, 100
                .if bolaPos.x < eax
                    xor eax, eax
                    mov eax, bolaPos.y ;bolaPos.y + 16
                    add eax, 16
                    .if eax > blocos[esi].Y
                        xor eax, eax
                        xor edx, edx
                        mov eax, blocos[esi].Y ; blocoPos.y + 16
                        add eax, 16
                        .if bolaPos.y < eax
                            mov blocos[esi].break, TRUE
                            ;overL = bola.right - bloco.left
                            mov eax, bolaPos.x
                            add eax, 16
                            sub eax, blocos[esi].X
                            mov overL, SDWORD PTR eax
                            ;overR = bloco.right - bola.left
                            mov eax, blocos[esi].X
                            add eax, 100
                            sub eax, bolaPos.x
                            mov overR, SDWORD PTR eax
                            ;overT = bola.bottom - bloco.top
                            mov eax, bolaPos.y
                            add eax, 16
                            sub eax, blocos[esi].Y
                            mov overT, SDWORD PTR eax
                            ;overB = bloco.bottom - bola.top
                            mov eax, blocos[esi].Y
                            add eax, 16
                            sub eax, bolaPos.y
                            mov overB, SDWORD PTR eax
                            
                            ; bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
                            ; float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
                            mov eax, overL
                            mov edx, overR
                            .if SDWORD PTR eax < 0
                                neg eax
                            .endif
                            .if SDWORD PTR edx < 0
                                neg edx
                            .endif
                            .if eax < edx
                                mov eax, overL
                                mov minOverX, SDWORD PTR eax
                            .else 
                                mov eax, overR
                                mov minOverX, SDWORD PTR eax
                            .endif

                            ; bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
                            ; float minOverlapY{ballFromTop ? overlapTop : overlapBottom};
                            mov eax, overT
                            mov edx, overB
                            .if SDWORD PTR eax < 0
                                neg eax
                            .endif
                            .if SDWORD PTR edx < 0
                                neg edx
                            .endif
                            .if eax < edx
                                mov eax, overT
                                mov minOverY, eax
                            .else 
                                mov eax, overB
                                mov minOverY, eax
                            .endif

                            ;daq pra baixo ele vai calcular pra que lado a bola vai ir depois da colisão
                            ;tudo isso comparando os overlaps
                            mov eax, minOverX
                            mov edx, minOverY
                            .if SDWORD PTR eax < 0
                                neg eax
                            .endif
                            .if SDWORD PTR edx < 0
                                neg edx
                            .endif
                            .if eax < edx
                                mov eax, overL
                                mov edx, overR
                                .if SDWORD PTR eax < 0
                                    neg eax
                                .endif
                                .if SDWORD PTR edx < 0
                                    neg edx
                                .endif
                                .if eax < edx
                                    mov eax, movimentoX
                                    neg eax
                                    mov direcaoX, eax
                                .else 
                                    mov eax, movimentoX
                                    mov direcaoX, eax
                                .endif
                            .else
                                mov eax, overT
                                mov edx, overB
                                .if SDWORD PTR eax < 0
                                    neg eax
                                .endif
                                .if SDWORD PTR edx < 0
                                    neg edx
                                .endif
                                .if eax < edx
                                    mov eax, movimentoY
                                    mov direcaoY, eax
                                    call Brick
                                .else 
                                    mov eax, movimentoY
                                    neg eax
                                    mov direcaoY, eax
                                    call Brick
                                .endif
                            .endif
                        .endif
                    .endif
                .endif
            .endif
        .endif
        add esi, TYPE BLOCO ;vai pro proximo bloco
        add bl, 1
    .ENDW 
    
    pop eax
    pop edi
    pop ebx
    pop ecx
    pop edx
    
    invoke PostMessage,hWnd,WM_BOLA_BLOCO,NULL,NULL
    jmp   ThreadCollidProc
    ret
ThreadCollidProc ENDP

; #########################################################################

Restaura_Blo PROC p1:DWORD
    push ebx
    push esi

    mov bl, 0
    mov esi, 0
    .WHILE bl < 25
        mov blocos[esi].break, FALSE
        add esi, TYPE BLOCO ;vai pro proximo bloco
        add bl, 1
    .ENDW
    mov bolaPos.x, 242
    mov bolaPos.y, 150
    pop esi
    pop ebx

    ret
Restaura_Blo ENDP

; #########################################################################

include TocaSonsProc.asm
include TocaSonsJogo.asm
end start