section .data               
;Canviar Nom i Cognom per les vostres dades.
developer db "_Nom_ _Cognom1_",0

;Constants que també estan definides en C.
ROWDIM  equ 4       ;files de la matriu.
COLDIM  equ 5       ;columnes de la matriu.

section .text            

;Variables definides en Assemblador.
global developer  

;Subrutines d'assemblador que es criden des de C.
global posCurScreenP2, showDigitsP2, updateBoardP2,
global moveCursorP2, calcIndexP2, openCardP2, checkPairsP2
global playP2

;Variables definides en C.
extern mCards, mOpenCards, mMoves

;Funcions de C que es criden des de assemblador
extern clearScreen_C, printBoardP2_C, gotoxyP2_C, getchP2_C, printchP2_C
extern printMessageP2_C


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ATENCIÓ: 
;;   Recordeu que les variables i els paràmetres s'han d'assignar
;;   al tipus de registre que correspon en cada cas:
;;   Variables de tipus 'char', en assemblador s'han d'assignar a 
;;   registres de tipus BYTE (1 byte): 
;;   al, ah, bl, bh, cl, ch, dl, dh, sil, dil, r8b, ..., r15b.
;;   Variables de tipus 'short', en assemblador s'han d'assignar a 
;;   registres de tipus WORD (2 byte): 
;;   ax, bx, cx, dx, si, di, r8w, ..., r15w.
;;   Variables de tipus 'int' en assemblador s'han d'assignar a 
;;   registres de tipus DWORD (4 byte): 
;;   deax, ebx, ecx, edx, esi, edi, r8d, ..., r15d.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Les subrutines en assemblador que heu de modificar per a 
;; implementar el pas de paràmetres són:
;;   posCurScreenP2, showDigitsP2, updateBoardP2,
;;   moveCursorP2, calcIndexP2, openCardP2.
;; La subrutina nova que s'ha d'implementar és:
;;   checkPairsP2.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Aquesta subrutina es dóna feta. NO LA PODEU MODIFICAR.
; Situar el cursor en una fila i una columna de la pantalla
; en funció de la fila (edi) i columna (esi) rebuts com a paràmetres
; cridant a la funció gotoxyP2_C.
;
; Variables globals utilitzades:
; Cap.
; 
; Paràmetres d'entrada : 
; rdi(edi): Fila
; rsi(esi): Columna
;    
; Paràmetres de sortida: 
; Cap.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
gotoxyP2:
   push rbp
   mov  rbp, rsp
   ;guardem l'estat dels registres del processador perquè
   ;les funcions de C no mantenen l'estat dels registres.
   push rax
   push rbx
   push rcx
   push rdx
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   ; Quan cridem la funció gotoxyP2_C(int rowScreen, int colScreen)
   ; des d'assemblador el primer paràmetre (rowScreen) s'ha de passar
   ; pel registre rdi(edi), i el segon  paràmetre (colcreen) s'ha de
   ; passar pel registre rsi(esi).
   call gotoxyP2_C
 
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rcx
   pop rbx
   pop rax

   mov rsp, rbp
   pop rbp
   ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Aquesta subrutina es dóna feta. NO LA PODEU MODIFICAR.
; Mostrar un caràcter (dil) a la pantalla, rebut com a paràmetre, 
; en la posició on està el cursor cridant la funció printchP2_C.
; 
; Variables globals utilitzades:   
; Cap
; 
; Paràmetres d'entrada : 
; rdi(dil): Caràcter que volem mostrar
; 
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
printchP2:
   push rbp
   mov  rbp, rsp
   ;guardem l'estat dels registres del processador perquè
   ;les funcions de C no mantenen l'estat dels registres.
   push rax
   push rbx
   push rcx
   push rdx
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   ; Quan cridem la funció printchP2_C(char c) des d'assemblador, 
   ; el paràmetre (c) s'ha de passar pel registre rdi(dil).
   call printchP2_C
 
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rcx
   pop rbx
   pop rax

   mov rsp, rbp
   pop rbp
   ret
   

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Aquesta subrutina es dóna feta. NO LA PODEU MODIFICAR.
; Llegir una tecla i retornar el caràcter associat (al) sense 
; mostrar-lo per pantalla, cridant la funció getchP2_C
; 
; Variables globals utilitzades:   
; Cap
; 
; Paràmetres d'entrada : 
; Cap
; 
; Paràmetres de sortida: 
; rax(al): Caràcter que llegim de teclat
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
getchP2:
   push rbp
   mov  rbp, rsp
   ;guardem l'estat dels registres del processador perquè
   ;les funcions de C no mantenen l'estat dels registres.
   push rbx
   push rcx
   push rdx
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   mov rax, 0
   ; Cridem la funció (char) getchP2_C() des d'assemblador, 
   ; retorna sobre el registre rax(al) el caràcter llegit
   call getchP2_C
    
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rcx
   pop rbx
      
   mov rsp, rbp
   pop rbp
   ret 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Posicionar el cursor a la pantalla, dins el tauler, en funció de la
; posició del cursor dins la matriu, indicada pel vector (rc) 
; rc[0]:fila (0-3) i rc[1]:columna (0-4), de tipus short(WORD) 2 bytes
; a partir de la posició [10, 12] de la pantalla.
; Per a calcular la posició del cursor a pantalla (rScreen) i 
; (cScreen) utilitzar aquestes fórmules:
; rScreen=10+(rc[0]*2)
; cScreen=12+(rc[1]*4)
; Per a posicionar el cursor a la pantalla s'ha de cridar a la subrutina
; gotoxyP2, implementant correctament el pas de paràmetres.
;
; Variables globals utilitzades:	
; Cap
;
; Paràmetres d'entrada : 
; rc: rdi(rdi): Adreça del vector amb la posició del cursor dins la matriu.
;
; Paràmetres de sortida: 
; Cap
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
posCurScreenP2:
   push rbp
   mov  rbp, rsp
   
   posCurScreenSetup:
   mov rax, rdi
   mov rdi, 0
   mov rsi, 0
   
   posCurScreenRow:
   mov di, WORD[rax + 0]
   shl di, 1  ;(rc[0]*2)
   add di, 10 ;10+(rc[0]*2)
   
   posCurScreenCol:
   mov si, WORD[rax + 2]
   shl si, 2 ;(rc[1]*4)
   add si, 12 ;12+(rc[1]*4)
   
   call gotoxyP2
   
   mov rsp, rbp
   pop rbp
   ret



;;;;;
; Converteix un valor (val) de tipus int(4 bytes) (entre 0 i 99) en  
; dos caràcters ASCII que representin aquest valor. (27 -> '2' '7').
; S'ha de dividir el valor entre 10, el quocient representarà les 
; desenes i el residu les unitats, i després s'han de convertir a ASCII
; sumant '0' o 48(codi ASCII de '0') a les unitats i a les desenes.
; Mostra els dígits (caràcter ASCII) a partir de la fila indicada
; per la variable (rScreen) i a la columna indicada per la variable
; (cScreen).
; Per a posicionar el cursor s'ha de cridar a la subrutina gotoxyP2 i 
; per a mostrar els caràcters a la subrutina printchP2,
; implementant correctament el pas de paràmetres.
;
; Variables globals utilitzades:   
; Cap.
;
; Paràmetres d'entrada : 
; rScreen: rdi(edi): Fila de la pantalla on posicionem el cursor.
; cScreen: rsi(esi): Columna de la pantalla on posicionem el cursor.
; val:     rdx(edx): Valor que volem mostrar.
;
; Paràmetres de sortida: 
; Cap.
;;;;;
showDigitsP2:
   push rbp
   mov  rbp, rsp
   
   showDigitsSetup:
   mov eax, edx 
   mov edx, 0
   
   showDigitsDivision: 
   mov ecx, 10 
   div ecx ;Quocient -> EAX ; Residu -> EDX
   
   showDigitsDivisionTenth: 
   add eax, '0'
   
   ShowDigitsPrintTenth:
   push rdi
   call gotoxyP2
   mov edi, eax
   call printchP2
   pop rdi
   
  ShowDigitsDivisionUnit:
   add edx, '0'
  
  ShowDigitsPrintUnit:
   push rdi
   inc rsi ; INC column
   call gotoxyP2
   mov edi, edx
   call printchP2
   pop rdi
   
   
	; PROPOSTA: showDigitsDivisonX i showDigitsPrint es podrien refactoritzar a un altre mètode, on per exemple accepta per paràmetre.
	; de R8 i R9, i allà fer les conversions necessàries per cridar tant gotoxyP2 com printchP2.
	; Penso que seria una manera més net eficient d'implementar aquest codi. No obstant això, no ho faig, ja que no és la finalitat de l'exercici
   mov rsp, rbp
   pop rbp
   ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Mostrar els valors de la matriu (mOpenCards) dins el tauler, 
; a les posicions corresponents, els moviments i les parelles fetes. 
; S'ha de recórrer tota la matriu (mOpenCards), cada posició és de 
; tipus char(BYTE)1byte, i per a cada element de la matriu fer:
; Posicionar el cursor en el tauler en funció de les variables 
; (rScreen) fila i (cScreen) columan cridant la subrutina gotoxyP2, 
; implementant correctament el pas de paràmetres.
; Les variables (rScreen) i (cScreen) s'inicialitzaran, a 10 i 14,
; respectivament i que és la posició a pantalla de la casella [0][0].
; Mostrar els caràcters de cada posició de la matriu (mOpenCards) 
; cridant la subrutina printchP2, implementant correctament el pas de 
; paràmetres.
; Després, mostrar els moviments (moves) de tipus int(DWORD)4bytes, 
; a partir de la posició [21,14] de la pantalla i mostrar les parelles
; fetes (pairs) de tipus int(DWORD)4bytes, a partir de la 
; posició [21,25] de la pantalla cridant la subrutina showDigitsP2, 
; implementant correctament el pas de paràmetres.
;
; Variables globals utilitzades:   
; mOpenCards   : Matriu on guardem les targetes del joc.
;
; Paràmetres d'entrada : 
; moves: rdi(edi): Parelles que s'han intentat fer amb èxit o sense.
; pairs: rsi(esi): Parelles que s'han fet.
;
; Paràmetres de sortida: 
; Cap.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
updateBoardP2:
   push rbp
   mov  rbp, rsp
    
   updateBoardSetup:
   push rdi ; Save in stack the moves
   push rsi  ; SAve in stack the pairs
   
   mov r8d, 0 ; Value for I  
   mov r9d, 0 ; Value for J 
   mov r10d, 0 ; Byte to move in the matrix
   mov rdi, 10 ; Row
    
   updateBoardIterationI:
   cmp r8d, ROWDIM
   JGE updateBoardEndIterationI
   mov rsi, 12 ; col
    
   updateBoardIterationJ:
   cmp r9d, COLDIM
   JGE updateBoardEndIterationJ
    
	   updateBoardGoAndPrint:
	   call gotoxyP2
	   push rdi
	   mov edi, DWORD[mOpenCards + r10d]
	   inc r10d
	   call printchP2
	   pop rdi
   
   add rsi, 4
   inc r9d
   jmp updateBoardIterationJ
    
   updateBoardEndIterationJ:
   add rdi, 2
   mov r9d, 0 ; Reset J
   inc r8d
   jmp updateBoardIterationI
   
   
   updateBoardEndIterationI:
   updateBoardShowPairs:
   pop rdx ; saved stack coming from pairs
   mov rdi, 19
   mov rsi, 24
   call showDigitsP2
   
   updateBoardShowMoves:
   pop rdx ; saved stack coming from moves
   mov  rsi, 15
   call showDigitsP2
   
   mov rsp, rbp
   pop rbp
   ret


;;;;;  
; Actualitzar la posició del cursor dins la matriu actualitzant el 
; vector (rc): vector de tipus short(WORD)2bytes, amb la fila 
; (rowcol[0]) i la columna rowcol[1] de la posició del cursor dins
; la matriu, en funció de la tecla premuda que tenim a la 
; variable (c), de tipus char(BYTE)1byte,
; (i: amunt, j:esquerra, k:avall, l:dreta).
; Comprovar que no sortim de la matriu, el vector (rc) només
; pot prendre els valors de les posicions dins de la matriu.
; Les files i les columnes s'incrementen de 1 en 1 perquè cada
; posició de la matriu és de tipus char(BYTE)1byte.
; Si s'ha de sortir de la matriu, no fer el moviment.
; NO S'ha de posicionar el cursor a la pantalla cridant UpdateBoardP1_C.
;
; Variables globals utilitzades:   
; Cap.
;
; Paràmetres d'entrada : 
; c : rdi(dil): caràcter llegit de teclat
; rc: rsi(rsi): Vector per a indicar la posició del cursor dins la matriu.
;
; Paràmetres de sortida: 
; Cap.
;;;;;
moveCursorP2:  
   push rbp
   mov  rbp, rsp

   moveCurorSwitch:
   mov al, dil
   
   cmp al, 'i' ; UP
   jne moveCursorCaseK
   
   cmp WORD[rsi], 0
   jle moveCursorEndSwitch
   dec WORD[rsi]
   jmp moveCursorEndSwitch
    
   
   moveCursorCaseK:
   cmp al, 'k'  ; DOWN
   jne moveCursorCaseJ
   
   cmp WORD[rsi], ROWDIM - 1 
   jge moveCursorEndSwitch
   inc WORD[rsi]
   jmp moveCursorEndSwitch
   
   
   moveCursorCaseJ:
   cmp al, 'j' ; LEFT
   jne moveCursorCaseL
   
   cmp WORD[rsi + 2], 0
   jle moveCursorEndSwitch
   dec WORD[rsi + 2]
   jmp moveCursorEndSwitch
   
   
   moveCursorCaseL:
   cmp al, 'l'
   jne moveCursorEndSwitch
    
   cmp WORD[rsi + 2], COLDIM - 1
   jge moveCursorEndSwitch
   inc WORD[rsi + 2]
   jmp moveCursorEndSwitch
   
         
   moveCursorEndSwitch:

   mov rsp, rbp
   pop rbp
   ret


;;;;;  
; Calcular el valor de l'índex (eax) per a accedir a una matriu 
; (4x5) de ROWDIM * COLDIM posicions de tipus char(BYTE)1byte, cadascuna,
; que guardarem al registre (eax) a partir de la fila (edi) i la 
; columna (esi), rebuts com a paràmetre.
; eax=((edi*COLDIM)+(esi))
; m[i][j] en C, és equivalent a BYTE[m+eax] en assemblador, 
; si eax = ((edi*COLDIM)+(esi)). 
; m[1][2] en C, és DWORD[m+7] en assemblador.
;
; Aquesta subrutina no té una funció en C equivalent.
;
; Variables globals utilitzades:   
; Cap.
;
; Paràmetres d'entrada : 
; rdi(edi): Fila de la matriu (4x5).
; rsi(esi): Columna de la matriu (4x5).
;
; Paràmetres de sortida: 
; rax(eax) : Índex per a accedir a la matriu (4x5).
;;;;;  
calcIndexP2:
   push rbp
   mov  rbp, rsp
   
   mov rax, 0
   mov edx, edi ; Current row 
   mov al, COLDIM ; Implicit multiplier
   
   mul dl ; Result in AL since it's not a huge number => row*COLDIM 
   
   mov ecx, esi 
   add al, cl ; (row*COLDIM) + col
   
         
   mov rsp, rbp
   pop rbp
   ret


;;;;;  
; Obrir la targeta de la matriu (mCards) de la posició indicada pel
; cursor dins la matriu i que tenim al vector (rc). rc[0] fila i 
; rc[1] columna.
; Guardar la posició de la targeta que estem obrint i que tenim al 
; vector (rc) de tipus short(WORD)2bytes a la matriu (mMoves),
; matriu de tipus short(WORD)2bytes, on la fila 0 és per guardar la 
; posició de la 1a targeta que girem (quan status=0) i la fila 1 és per
; a guardar la posició de la 2a targeta que girem (quan status=1), la 
; columna 0 és per la fila(rc[0]) i la columna 1 és per la columna(rc[1]).
; Per a accedir a la matriu (mMoves[i][j]) des d'assemblador, s'ha de
; calcular l'índex i cal fer la següent operació: index=(i*4)+j, es 
; multiplica per 4 perquè cada fila ocupa 4 bytes.
; Si la targeta no està girada (!='x') posar-la a la matriu (mOpenCards)
; per a que es mostri.
; Marcar-la amb una 'x'(minúscula) a la mateixa posició de la matriu 
; (mCards) per a saber que està girada.
; Passar al següent estat (state++).
; Per accedir a les matrius (mOpenCards) i (mCards) en assemblador
; s'ha de calcular l'índex cridant la subrutina calcIndexP2, 
; implementant correctament el pas de paràmetres.
; 
; No s'ha de mostrar la matriu amb els canvis, es fa a updateBoardP2_C().
; 
; Variables globals utilitzades:
; mMoves     : Matriu amb les posicions de les targetes obertes.
; mCards     : Matriu on guardem les targetes del joc.
; mOpenCards : Matriu on tenim les targetes obertes del joc.
; 
; Paràmetres d'entrada:
; rc     :rdi(rdi): Vector on tenim la posició del cursor dins la matriu.
; status :rsi(esi): Estat del joc.
; 
; Paràmetres de sortida: 
; status :rax(eax): Estat del joc.
;;;;;
openCardP2:  
   push rbp
   mov  rbp, rsp

   openCardSetVariables: 
   push rsi ; status
   mov r10w, WORD[rdi] ;row
   mov r11w, WORD[rdi + 2] ;col
   
   openCardManageMMoves:   ; pointing concrete direction based on the bit status
     openCardManageMMovesIf:
     cmp esi, 0
     je openCardManageMMovesElse
     mov r12d, 4
     jmp openCardManageMMovesEndIf
     
     openCardManageMMovesElse:
     mov r12d, 0
     
     openCardManageMMovesEndIf:
     
   mov WORD[mMoves + r12d ], r10w
   add r12d, 2 ;  -> pointing to [x][1]
   mov WORD[mMoves + r12d], r11w
   
   openCardSetupCalcIndex:
   mov edi , r10d
   mov esi , r11d
   call calcIndexP2 ; Get Index with the register RAX
   
   
   openCardIfStatement:
   cmp BYTE[mCards + eax], 'x'
   je openCardEndIf
   mov ecx, DWORD[mCards+eax]
   mov BYTE[mOpenCards + eax], cl  ;  mOpenCards[i][j] = mCards[i][j];
   mov BYTE[mCards+eax], 'x' ; mCards[i][j] = 'x';
   
   pop rsi
   inc rsi
   
   openCardEndIf:
   mov rax, rsi
         
   mov rsp, rbp
   pop rbp
   ret


;;;;;  
; Comprovar si les dues targetes obertes són iguals.
; Si les targetes són iguals canviat l'estat 'hi ha parella' (status=3).
; Si no són iguals tornar a girar-les. Per fer-ho cal tornar a posar
; els  valors de targetes que ara tenim a la matriu (mOpenCards) a la 
; matriu (mCards) i a la matriu (mOpenCards) posar-hi una 'X' per a 
; indicar que estan tapades. Canviar l'estat a 'no hi ha parelles' (status=4).
; La matriu (mMoves) de tipus short(WORD)2bytes conté la fila i 
; la columna de les targetes obertes. 
; mMoves[0][0]:[mMoves+0]: Fila de la 1a targeta;
; mMoves[0][1]:[mMoves+2]: Columna de la 1a targeta;
; mMoves[1][0]:[mMoves+4]: Fila de la 2a targeta;
; mMoves[1][1]:[mMoves+6]: Columna de la 2a targeta;
; Per accedir a les matrius (mOpenCards) i (mCards) en assemblador
; s'ha de calcular l'índex cridant la subrutina calcIndexP2, 
; implementant correctament el pas de paràmetres.
; 
; Variables globals utilitzades:
; mMoves     : Matriu amb les posicions de les targetes obertes.
; mCards     : Matriu on guardem les targetes del joc.
; mOpenCards : Matriu on tenim les targetes obertes del joc.
; 
; Paràmetres d'entrada:
; Cap
; 
; Paràmetres de sortida: 
; status :rax(eax): Estat del joc.
;;;;;  
checkPairsP2:
   push rbp
   mov  rbp, rsp

   
   
   mov rsp, rbp
   pop rbp
   ret   


;;;;;
; Aquesta subrutina es dóna feta. NO LA PODEU MODIFICAR.
; Mostra un missatge a sota del tauler cridant la funció printMessageP2_C(state)
; segons el valor de la variable (state)
;         0: 0 targetes obertes.
;         1: 1 Targeta oberta.
;         2: 2 Targetes obertes.
;         3: Hi ha parella.
;         4: No hi ha parella.
;         5: Sortir, hem premut la tecla 'ESC' per a sortir.
;         6: Guanya, totes les parelles fetes.
;         7: Perd, s'han exhaurits els moviments .
; Si (state>1) demana que es premi una tecla per a poder-lo llegir.
;  
; Variables globals utilitzades:	
; Cap.
; 
; Paràmetres d'entrada : 
; status    : rdi(edi): Estat del joc.
; 
; Paràmetres de sortida: 
; Cap.
;;;;;
printMessageP2:
   push rbp
   mov  rbp, rsp
   ;guardem l'estat dels registres del processador perquè
   ;les funcions de C no mantenen l'estat dels registres.
   push rax
   push rbx
   push rcx
   push rdx
   push rsi
   push rdi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15

   ; Quan cridem la funció printMessageP2_C(int status) des d'assemblador, 
   ; el paràmetre (status) s'ha de passar pel registre rdi(edi).
   call printMessageP2_C
 
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rcx
   pop rbx
   pop rax

   mov rsp, rbp
   pop rbp
   ret


;;;;;
; Joc del Memory
; Funció principal del joc.
; Trobat totes les parelles del tauler (10 parelles), girant les
; targetes de dues en dues. Com a màxim es poden fer 15 intents.
; 
; Pseudo-codi:
; Inicialitzar l'estat del joc, (state=0).
; Esborrar la pantalla  (cridar la funció clearScreen_C).
; Mostrar el tauler de joc (cridar la funció printBoardP2_C).
; Actualitzar el tauler de joc i els valors dels moviments fets (moves)
; i de les parelles fetes (pairs) cridant la subrutina updateBoardP2.
; Mentre (state<3) fer:
;   Mostrar un missatge,  segons el valor de la variable (state),
;   per a indicar que s'ha de fer, cridant la subrutina printMessageP2.
;   Actualitzar la posició del cursor a la pantalla a partir del vector
;   ([rowcol]) (fila (rowcol[0]) i la columna (rowcol[1])) amb la posicio
;   del cursor dins la matriu, cridant la subrutina posCurScreenP2.
;   Llegir una tecla, cridar la subrutina getchP2. 
;   Segons la tecla llegida cridarem a les subrutines que corresponguin.
;     - ['i','j','k' o 'l'] desplaçar el cursor segons la direcció 
;       triada, cridant la subrutina moveCursorP2_C).
;     - '<SPACE>'(codi ASCII 32) girar la targeta on hi ha el cursor
;       cridant la funció openCardP2_C.
;       Actualitzar el tauler de joc i els valors dels moviments fets (moves)
;       i de les parelles fetes (pairs) cridant la subrutina updateBoardP2.
;       Si s'han girat dues targetes (state>1) incrementar el moviments (moves)
;       Verificar si les dues targetes que s'ha girant són iguales
;       cridant la subrutina checkPairsP2.
;       Si son iguals (state==3) incrementar les parelles (pairs)
;       Si s'han fet 15 moviments canviar a l'estat de moviments exhaurits (state=7). 
;       Si s'han fet 10 parelles canviar a l'estat de joc guanyat (state=6).
;       Mostrar un missatge,  segons el valor de la variable (state),
;       per a indicar que ha passat, cridant la subrutina printMessageP2. 
;       Si ho hem de sortir (state<5) posar (state=0) per a tornar a 
;       intentar fer una nova parella.
;       Actualitzar el tauler de joc i els valors dels moviments fets (moves)
;       i de les parelles fetes (pairs) cridant la funció updateBoardP2_C.
;    - '<ESC>'  (codi ASCII 27) posar (state = 5) per a sortir.
;       No sortira si només s'ha girat una targeta (state!=1).
; Fi mentre.
; Sortir: S'acaba el joc.
; Cal implementar correctament el pas de paràmetres tant a les crides de
; les funcions en C, com a les crides de les subrutines en assemblador.
; 
; Variables globals utilitzades:	
; Cap.
; 
; Paràmetres d'entrada : 
; Cap.
; 
; Paràmetres de sortida: 
; Cap.
;;;;;  
playP2:
   push rbp
   mov  rbp, rsp
   
					;Declaració de variables locals.
   sub  rsp, 8      ;Reservem espai per al vector rowcol.
                    
   push rax
   push rbx
   push rdx         
   push rsi
   push rdi
   push r8
   push r9
   
   call clearScreen_C
   call printBoardP2_C   ;printBoard2_C();
      
   mov edx, 0       ;state = 0;//Estat per a començar a jugar
   mov r8d, 0       ;moves = 0;
   mov r9d, 0       ;pairs = 0;   
   mov edi, r8d
   mov esi, r9d
   
   mov rbx, rbp
   sub rbx, 8
   mov WORD[rbx+0], 2 ;rowcol[0] = 2;   //Posició inicial del cursor dins la matriu.
   mov WORD[rbx+2], 1 ;rowcol[1] = 2;
    
   call updateBoardP2  
   
   playP2_Loop:                    ;while  {  //Bucle principal.
   cmp  edx, 3                    ;(state < 3)
   jge  playP2_End
      
      mov  edi, edx
      
      call printMessageP2     ;printMessageP2_C(state);
      
      mov  rdi, rbx
      
      call posCurScreenP2     ;posCurScreenP2_C(rowcol); 
      push rbp    
      call getchP2            ;al = charac = getchP2_C();   
      pop rbp
      cmp al, 'i'             ;if (charac>='i' && charac<='l') {
      jl  playP2_TurnUp
      cmp al, 'l'
      jg  playP2_TurnUp
         mov dil, al
         mov  rsi, rbx
         
      call moveCursorP2    ;moveCursorP2_C(charac, rowcol);
      playP2_TurnUp:
      cmp al, 32              ;if (charac==32) {
      jne playP2_Esc
         mov  rdi, rbx
         
         mov  esi, edx
         call openCardP2      ;state = openCardP2_C(rowcol, state);
         mov  edx, eax
         mov edi, r8d
         mov esi, r9d
         
         call updateBoardP2   ;updateBoardP2_C(moves, pairs);
         
         cmp edx, 1           ;if (state > 1) {
         jle playP2_Esc
			inc r8d           ;moves++;
			call checkPairsP2 ;state = checkPairsP2_C();
			mov edx, eax
			cmp edx, 3        ;if (state == 3) 
			jne playP2_Moves
			   inc r9d        ;pairs++;
			playP2_Moves:
            cmp r8d, 15       ;if (moves == 15) 
            jne playP2_Pairs
               mov edx, 7     ;state = 7;
            playP2_Pairs:
            cmp r9d, 10       ;if (pairs == 10) 
            jne playP2_Message
               mov edx, 6     ;state = 6;
            playP2_Message:
            mov edi, edx
			call printMessageP2;printMessageP2_C(state);
            cmp edx, 5        ;if (state < 5) 
            jge playP2_UpdateBoard
               mov edx, 0     ;state = 0;
            playP2_UpdateBoard:
			mov edi, r8d
            mov esi, r9d
            call updateBoardP2;updateBoardP2_C(moves, pairs);
      playP2_Esc:
      cmp al, 27              ;if ( (charac==27) && (state!=1) ) {
      jne playP2_EndLoop
      cmp edx, 1
      je  playP2_EndLoop
         mov edx, 5          ;state = 5;
      playP2_EndLoop:
   jmp playP2_Loop
   
   playP2_End:
   pop r9
   pop r8
   pop rdi
   pop rsi
   pop rdx
   pop rbx
   pop rax  
   
   mov rsp, rbp
   pop rbp
   ret
