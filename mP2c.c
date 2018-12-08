/**
 * Implementació en C de la pràctica, per a què tingueu una
 * versió funcional en alt nivell de totes les funcions que heu 
 * d'implementar en assemblador.
 * Des d'aquest codi es fan les crides a les subrutines de assemblador. 
 * AQUEST CODI NO ES POT MODIFICAR I NO S'HA DE LLIURAR.
 */

#include <stdio.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO

/**
 *Constants
 */
#define ROWDIM  4        //files de la matriu
#define COLDIM  5        //columnes de la matriu

extern int developer;    //Variable declarada en assemblador que indica el nom del programador

/**
 * Definició de variables globals
 */
// Matriu 4x5 amb les targetes del joc.
char mCards[ROWDIM][COLDIM]     = { 
	              {'0','1','2','3','4'},
                  {'S','@','O','#','$'},
                  {'S','#','O','@','$'},
                  {'4','3','2','1','0'} };  

// Matriu 4x5 amb les targetes obertes.       
char mOpenCards[ROWDIM][COLDIM] = { 
	              {'X','X','X','X','X'},
                  {'X','X','X','X','X'},
                  {'X','X','X','X','X'},
                  {'X','X','X','X','X'} };
// Matriu 2x2 on guardarem la fila i la columna dins la matriu de les 
// targetes obertes.
short mMoves[2][2]; // mMoves[0][0] fila i mMoves[0][1] columna de la 1a targeta oberta
                    // mMoves[1][0] fila i mMoves[1][1] columna de la 2a targeta oberta



/**
 * Definició de les funcions de C
 */
void clearscreen_C();
void gotoxyP2_C(int, int);
void printchP2_C(char);
char getchP2_C();

char printMenuP2_C();
void printBoardP2_C();

void posCurScreenP2_C(short[2]);
void showDigitsP2_C(int, int, int);
void updateBoardP2_C(int, int);
void moveCursorP2_C(char, short[2]);
int  openCardP2_C(short[2], int);
int  checkPairsP2_C();

void printMessageP2_C(int);
void playP2_C();


/**
 * Definició de les subrutines d'assemblador que es criden des de C.
 */
void posCurScreenP2(short[2]);
void showDigitsP2(int, int, int);
void updateBoardP2(int, int);
void moveCursorP2(char, short[2]);
int calcIndexP2(int, int);
int openCardP2(short[2], int);
int checkPairsP2();
void playP2();


/**
 * Esborrar la pantalla
 * 
 * Variables globals utilitzades:   
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * Cap.
 *   
 * Paràmetres de sortida: 
 * Cap.
 * 
 * Aquesta funció no es crida des d'assemblador
 * i no hi ha definida una subrutina d'assemblador equivalent.
 */
void clearScreen_C(){
   
    printf("\x1B[2J");
    
}


/**
 * Situar el cursor en una fila i una columna de la pantalla
 * en funció de la fila (rowScreen) i de la columna (colScreen) 
 * rebuts com a paràmetre.
 * 
 * Variables globals utilitzades:   
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * rowScreen  : rdi(edi): Fila
 * colScreen  : rsi(esi): Columna
 * 
 * Paràmetres de sortida: 
 * Cap.
 * 
 * S'ha definit un subrutina en assemblador equivalent 'gotoxyP2' 
 * per a poder cridar aquesta funció guardant l'estat dels registres 
 * del processador. Això es fa perquè les funcions de C no mantenen 
 * l'estat dels registres.
 * El pas de paràmetres és equivalent.
 */
void gotoxyP2_C(int rowScreen, int colScreen){
   
   printf("\x1B[%d;%dH",rowScreen,colScreen);
   
}


/**
 * Mostrar un caràcter (c) a la pantalla, rebut com a paràmetre, 
 * en la posició on està el cursor.
 * 
 * Variables globals utilitzades:   
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * c        : rdi(dil): Caràcter que volem mostrar
 * 
 * Paràmetres de sortida: 
 * Cap.
 * 
 * S'ha definit un subrutina en assemblador equivalent 'printchP2' 
 * per a cridar aquesta funció guardant l'estat dels registres del 
 * processador. Això es fa perquè les funcions de C no mantenen 
 * l'estat dels registres.
 * El pas de paràmetres és equivalent.
 */
void printchP2_C(char c){
   
   printf("%c",c);
   
}


/**
 * Llegir una tecla i retornar el caràcter associat 
 * sense mostrar-lo per pantalla. 
 * 
 * Variables globals utilitzades:   
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * Cap.
 * 
 * Paràmetres de sortida: 
 * c        : rax(al): Caràcter llegit de teclat
 * 
 * S'ha definit un subrutina en assemblador equivalent 'getchP2' per a
 * cridar aquesta funció guardant l'estat dels registres del processador.
 * Això es fa perquè les funcions de C no mantenen l'estat dels 
 * registres.
 * El pas de paràmetres és equivalent.
 */
char getchP2_C(){

   int c;   

   static struct termios oldt, newt;

   /*tcgetattr obtenir els paràmetres del terminal
   STDIN_FILENO indica que s'escriguin els paràmetres de l'entrada estàndard (STDIN) sobre oldt*/
   tcgetattr( STDIN_FILENO, &oldt);
   /*es copien els paràmetres*/
   newt = oldt;

   /* ~ICANON per a tractar l'entrada de teclat caràcter a caràcter no com a línia sencera acabada amb /n
      ~ECHO per a què no mostri el caràcter llegit*/
   newt.c_lflag &= ~(ICANON | ECHO);          

   /*Fixar els nous paràmetres del terminal per a l'entrada estàndard (STDIN)
   TCSANOW indica a tcsetattr que canvii els paràmetres immediatament.*/
   tcsetattr( STDIN_FILENO, TCSANOW, &newt);

   /*Llegir un caràcter*/
   c=getchar();                 
    
   /*restaurar els paràmetres originals*/
   tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

   /*Retornar el caràcter llegit*/
   return (char)c;
   
}



/**
 * Mostrar a la pantalla el menú del joc i demana una opció.
 * Només accepta una de les opcions correctes del menú ('0'-'9')
 * 
 * Variables globals utilitzades:   
 * developer:((char;)&developer): variable definida en el codi assemblador.
 * 
 * Paràmetres d'entrada : 
 * Cap.
 * 
 * Paràmetres de sortida: 
 * charac   : rax(al): Opció triada del menú, llegida de teclat.
 * 
 * Aquesta funció no es crida des d'assemblador
 * i no hi ha definida una subrutina d'assemblador equivalent.
 */
char printMenuP2_C(){
   clearScreen_C();
   gotoxyP2_C(1,1);
   printf("                                 \n");
   printf("       P2 Developed by:          \n");
   printf("       ( %s )   \n",(char *)&developer);
   printf(" _______________________________ \n");
   printf("|                               |\n");
   printf("|           MAIN MENU           |\n");
   printf("|_______________________________|\n");
   printf("|                               |\n");
   printf("|        1. PosCurScreen        |\n");
   printf("|        2. ShowDigits          |\n");
   printf("|        3. UpdateBoard         |\n");
   printf("|        4. moveCursor          |\n");
   printf("|        5. CalcIndexMat        |\n");
   printf("|        6. OpenCard            |\n");
   printf("|        7. CheckPairs          |\n");
   printf("|        8. Play Game           |\n");
   printf("|        9. Play Game C         |\n");
   printf("|        0. Exit                |\n");
   printf("|_______________________________|\n");
   printf("|                               |\n");
   printf("|           OPTION:             |\n");
   printf("|_______________________________|\n"); 

   char charac =' ';
   while (charac < '0' || charac > '9') {
     gotoxyP2_C(21,21);          //posicionar el cursor
     charac = getchP2_C();       //Llegir una opció
     printchP2_C(charac);        //Mostrar opció
   }
   return charac;
}


/**
 * Mostrar el tauler de joc a la pantalla. Les línies del tauler.
 * 
 * Variables globals utilitzades:   
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * Cap.
 *   
 * Paràmetres de sortida: 
 * Cap.
 *  
 * Aquesta funció es crida des de C i des d'assemblador,
 * i no hi ha definida una subrutina d'assemblador equivalent.
 */
void printBoardP2_C(){

   gotoxyP2_C(1,1);                                     //Files
                                                        //Tauler                                  
   printf(" _____________________________________ \n"); //01
   printf("|                                     |\n"); //02
   printf("|         M  E  M  O  R  Y   v_1.0    |\n"); //03
   printf("|                                     |\n"); //04
   printf("|  Choose 2 cards and turn them over. |\n"); //05
   printf("|    Try to match all the pairs!      |\n"); //06
   printf("|                                     |\n"); //07
 //Columnes Tauler   12  16  20  24   28         
   printf("|          0   1   2   3   4          |\n"); //08
   printf("|        +---+---+---+---+---+        |\n"); //09
   printf("|      0 |   |   |   |   |   |        |\n"); //10
   printf("|        +---+---+---+---+---+        |\n"); //11
   printf("|      1 |   |   |   |   |   |        |\n"); //12
   printf("|        +---+---+---+---+---+        |\n"); //13
   printf("|      2 |   |   |   |   |   |        |\n"); //14
   printf("|        +---+---+---+---+---+        |\n"); //15
   printf("|      3 |   |   |   |   |   |        |\n"); //16
   printf("|        +---+---+---+---+---+        |\n"); //17
  //Columnes dígits      15       24                 
   printf("|           +----+   +----+           |\n"); //18
   printf("|     Moves |    |   |    | Pairs     |\n"); //19
   printf("|           +----+   +----+           |\n"); //20 
   printf("| (ESC) Exit        Turn Over (Space) |\n"); //21
   printf("| (i)Up    (j)Left  (k)Down  (l)Right |\n"); //22
   printf("|                                     |\n"); //23
   printf("| [                                 ] |\n"); //24
   printf("|_____________________________________|\n"); //25
                          
}


/**
 * Posicionar el cursor a la pantalla, dins el tauler, en funció de la
 * posició del cursor dins la matriu, indicada pel vector (rc) 
 * rc[0]:fila (0-3) i rc[1]:columna (0-4), de tipus short (WORD) 2 bytes
 * a partir de la posició [10,12] de la pantalla.
 * Per a calcular la posició del cursor a pantalla (rowScreen) i 
 * (colScreen) utilitzar aquestes fórmules:
 * rScreen=10+(rc[0]*2)
 * cScreen=12+(rc[1]*4)
 * Per a posicionar el cursor a la pantalla s'ha de cridar a la funció 
 * gotoxyP2_C implementant correctament el pas de paràmetres.
 * 
 * Variables globals utilitzades:   
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * rc: rdi(edi): Adreça del vector amb la posició del cursor dins la matriu.
 * 
 * Paràmetres de sortida: 
 * Cap.
 * 
 * Aquesta funció no es crida des d'assemblador.
 * A la subrutina d'assemblador equivalent 'posCurScreenP2',  
 * el pas de paràmetres és equivalent.
 */
void posCurScreenP2_C(short rc[2]) {

   int rScreen=10+(rc[0]*2);
   int cScreen=12+(rc[1]*4);
   gotoxyP2_C(rScreen, cScreen);
   
}


/**
 * Converteix un valor (val) de tipus int(4 bytes) (entre 0 i 99) en  
 * dos caràcters ASCII que representin aquest valor. (27 -> '2' '7').
 * S'ha de dividir el valor entre 10, el quocient representarà les 
 * desenes i el residu les unitats, i després s'han de convertir a ASCII
 * sumant '0' o 48(codi ASCII de '0') a les unitats i a les desenes.
 * Mostra els dígits (caràcter ASCII) a partir de la fila indicada
 * per la variable (rScreen) i a la columna indicada per la variable
 * (cScreen).
 * Per a posicionar el cursor s'ha de cridar a la funció gotoxyP2_C i 
 * per a mostrar els caràcters a la funció printchP2_C
 * implementant correctament el pas de paràmetres.
 * 
 * Variables globals utilitzades:   
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * rScreen: rdi(edi): Fila de la pantalla on posicionem el cursor.
 * cScreen: rsi(esi): Columna de la pantalla on posicionem el cursor.
 * val:     rdx(edx): Valor que volem mostrar.
 * 
 * Paràmetres de sortida: 
 * Cap.
 * 
 * Aquesta funció no es crida des d'assemblador.
 * Hi ha un subrutina en assemblador equivalent 'showDigitsP2',
 * el pas de paràmetres és equivalent.  
 */
 void showDigitsP2_C(int rScreen, int cScreen, int val) {
	
	char d, u;
	d = val / 10;      //Desenes
	d = d + '0';
    gotoxyP2_C(rScreen, cScreen);   
	printchP2_C(d);

	u = val % 10;      //Unitats
	u = u + '0';
    cScreen++;
	gotoxyP2_C(rScreen, cScreen);   
	printchP2_C(u);
	
}


/**
 * Mostrar els valors de la matriu (mOpenCards) dins el tauler, 
 * a les posicions corresponents, els moviments (moves) i les parelles 
 * fetes (pairs). 
 * S'ha de recórrer tota la matriu (mOpenCards), cada posició és de 
 * tipus char(BYTE)1byte, i per a cada element de la matriu fer:
 * Posicionar el cursor en el tauler en funció de les variables 
 * (rScreen) fila i (cScreen) columna cridant la funció gotoxyP2_C 
 * implementant correctament el pas de paràmetres.
 * Les variables (rScreen) i (cScreen) s'inicialitzaran a 10 i 14
 * respectivament, que és la posició a pantalla de la casella [0][0].
 * Mostrar els caràcters de cada posició de la matriu (mOpenCards) cridant
 * la funció printchP2_C implementant correctament el pas de paràmetres.
 * Després, mostrar els moviments (moves) de tipus int(DWORD)4bytes, 
 * a partir de la posició [19,15] de la pantalla i mostrar les parelles
 * fetes (pairs) de tipus int(DWORD)4bytes, a partir de la 
 * posició [19,24] de la pantalla cridant la funció showDigitsP2_C 
 * implementant correctament el pas de paràmetres.
 * 
 * Variables globals utilitzades:	
 * mOpenCards   : Matriu on guardem les targetes del joc.
 * 
 * Paràmetres d'entrada : 
 * moves: rdi(edi): Parelles que s'han intentat fer amb èxit o sense.
 * pairs: rsi(esi): Parelles que s'han fet.
 * 
 * Paràmetres de sortida: 
 * Cap.
 * 
 * Aquesta funció no es crida des d'assemblador.
 * Hi ha una subrutina en assemblador equivalent 'updateBoardP2',
 * el pas de paràmetres és equivalent.  
 */
void updateBoardP2_C(int moves, int pairs){
   
   int i,j;
   int c;
   int rScreen, cScreen;
   rScreen = 10;
   for (i=0;i<ROWDIM;i++){
	  cScreen = 12;
      for (j=0;j<COLDIM;j++){
         gotoxyP2_C(rScreen, cScreen);
         c = mOpenCards[i][j];
         printchP2_C(c);
         cScreen = cScreen + 4;
      }
      rScreen = rScreen + 2;
   }
   
   showDigitsP2_C(19, 15, moves);
   showDigitsP2_C(19, 24, pairs);
   
}


/**
 * Actualitzar la posició del cursor dins la matriu actualitzant el 
 * vector (rc): vector de tipus short(WORD)2bytes, amb la fila 
 * (rc[0]) i la columna rc[1] de la posició del cursor dins
 * la matriu, en funció de la tecla premuda que tenim a la 
 * variable (c), de tipus char(BYTE)1byte,
 * (i: amunt, j:esquerra, k:avall, l:dreta).
 * Comprovar que no sortim de la matriu, el vector (rc) només
 * pot prendre els valors de les posicions dins de la matriu.
 * Les files i les columnes s'incrementen de 1 en 1 perquè cada
 * posició de la matriu és de tipus char(BYTE)1byte.
 * Si s'ha de sortir de la matriu, no fer el moviment.
 * NO s'ha de posicionar el cursor a la pantalla cridant UpdateBoardP2_C.
 * 
 * Variables globals utilitzades:	
 * Cap.
 * 
 * Pràmetres d'entrada:
 * c : rdi(dil): caràcter llegit de teclat.
 * rc: rsi(rsi): Vector per a indicar la posició del cursor dins la matriu.
 * 
 * Paràmetres de sortida: 
 * Cap.
 * 
 * Aquesta funció no es crida des d'assemblador.
 * Hi ha una subrutina en assemblador equivalent 'moveCursorP2',
 * el pas de paràmetres és equivalent.  
 */
void moveCursorP2_C(char c, short rc[2]){
 
   switch(c){
      case 'i': //amunt
         if (rc[0]>0) rc[0]=rc[0]-1;
      break;
      case 'k': //avall
         if (rc[0]<(ROWDIM-1)) rc[0]=rc[0]+1;
      break;
      case 'j': //esquerra
         if (rc[1]>0) rc[1]=rc[1]-1;
      break;
      case 'l': //dreta
         if (rc[1]<(COLDIM-1)) rc[1]=rc[1]+1;
      break;
      
   }

}


/**
 * Obrir la targeta de la matriu (mCards) de la posició indicada pel
 * cursor dins la matriu i que tenim al vector (rc). 
 * rc[0] fila i rc[1] columna.
 * Guardar la posició de la targeta que estem obrint i que tenim al
 * vector (rc) de tipus short(WORD)2bytes a la matriu (mMoves),
 * matriu de tipus short(WORD)2bytes, on la fila 0 és per a guardar la 
 * posició de la 1a targeta que girem (quan status=0) i la fila 1 és per
 * a guardar la posició de la 2a targeta que girem (quan status=1), la 
 * columna 0 és per a la fila(rc[0]) i la columna 1 és per a la columna(rc[1]).
 * Per a accedir a la matriu (mMoves[i][j]) des d'assemblador, s'ha de
 * calcular l'índex i cal fer la següent operació: index=(i*4)+j, es 
 * multiplica per 4 perquè cada fila ocupa 4 bytes.
 * Si la targeta no està girada (!='x') posar-la a la matriu (mOpenCards)
 * per a que es mostri.
 * Marcar-la amb una 'x'(minúscula) a la mateixa posició de la matriu 
 * (mCards) per a saber que està girada.
 * Passar al següent estat (status++)
 * 
 * NO s'ha de mostrar la matriu amb els canvis, es fa a updateBoardP2_C().
 * 
 * Variables globals utilitzades:
 * mMoves     : Matriu amb les posicions de les targetes obertes.
 * mCards     : Matriu on guardem les targetes del joc.
 * mOpenCards : Matriu on tenim les targetes obertes del joc.
 * 
 * Paràmetres d'entrada:
 * rc     :rdi(rdi): Vector on tenim la posició del cursor dins la matriu.
 * status :rsi(esi): Estat del joc.
 * 
 * Paràmetres de sortida: 
 * status :rax(eax): Estat del joc.
 * 
 * Aquesta funció no es crida des d'assemblador.
 * Hi ha una subrutina en assemblador equivalent 'openCardP2'.
 */
int openCardP2_C(short rc[2], int status){

   char aux;
   int i = rc[0];
   int j = rc[1];
   mMoves[status][0] = i;
   mMoves[status][1] = j;
   
   if (mCards[i][j] != 'x') {
      mOpenCards[i][j] = mCards[i][j];
      mCards[i][j] = 'x';
      status++;
   }
   return status;
}


/**
 * Comprovar si les dues targetes obertes són iguals.
 * Si les targetes són iguals canviar a l'estat de 'hi ha parella' (status=3).
 * Si no són iguals tornar a girar-les. Per a fer-ho cal tornar a posar
 * els valors de les targetes que ara tenim a la matriu (mOpenCards), a la 
 * matriu (mCards) i a la matriu (mOpenCards) posar-hi una 'X'(majúscula) per
 * a indicar que estan tapades. Canviar a l'estat de 'no hi ha parelles' (status=4).
 * La matriu (mMoves) de tipus short(WORD)2bytes conté la fila i 
 * la columna de les targetes obertes.
 * mMoves[0][0]:[mMoves+0]: Fila de la 1a targeta;
 * mMoves[0][1]:[mMoves+2]: Columna de la 1a targeta;
 * mMoves[1][0]:[mMoves+4]: Fila de la 2a targeta;
 * mMoves[1][1]:[mMoves+6]: Columna de la 2a targeta;
 * 
 * Variables globals utilitzades:
 * mMoves     : Matriu amb les posicions de les targetes obertes.
 * mCards     : Matriu on guardem les targetes del joc.
 * mOpenCards : Matriu on tenim les targetes obertes del joc.
 * 
 * Paràmetres d'entrada:
 * Cap
 * 
 * Paràmetres de sortida: 
 * status :rax(eax): Estat del joc.
 * 
 * Aquesta funció no es crida des d'assemblador.
 * Hi ha una subrutina en assemblador equivalent 'checkPairsP2'.
 */
int checkPairsP2_C(){

   char aux;
   int status;
   
   int i0 = mMoves[0][0];
   int j0 = mMoves[0][1];
   int i1 = mMoves[1][0];
   int j1 = mMoves[1][1];
   if ( mOpenCards[i0][j0] == mOpenCards[i1][j1] ) {
      status = 3; //Hi ha parella
   } else {  //girar targetes
	  mCards[i0][j0]     = mOpenCards[i0][j0];
      mOpenCards[i0][j0] = 'X';
      mCards[i1][j1]     = mOpenCards[i1][j1];
      mOpenCards[i1][j1] = 'X';
      status = 4; //No hi ha parella
   }
   return status;
}


/**
 * Mostra un missatge a sota del tauler segons el valor de la variable 
 * (state) 0: 0 targetes obertes.
 *         1: 1 Targeta oberta.
 *         2: 2 Targetes obertes.
 *         3: Hi ha parella.
 *         4: No hi ha parella.
 *         5: Sortir, hem premut la tecla 'ESC' per a sortir.
 *         6: Guanya, totes les parelles fetes.
 *         7: Perd, s'han exhaurits els moviments .
 * Si (state>1) demanar que es premi una tecla per a poder-la llegir.
 *  
 * Variables globals utilitzades:	
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * status    : Estat del joc.
 * 
 * Paràmetres de sortida: 
 * Cap.
 *  
 * S'ha definit un subrutina en assemblador equivalent 'printMessageP2' per
 * a cridar aquesta funció guardant l'estat dels registres del processador.
 * Això es fa perquè les funcions de C no mantenen l'estat dels 
 * registres.
 * El pas de paràmetres és equivalent.
 */
void printMessageP2_C(int status) {

   gotoxyP2_C(24,4);
   switch(status){
	  case 0:
         printf("...  Turn Over FIRST card !!! ...");
      break;
      case 1:
         printf("...  Turn Over SECOND card!!! ...");
      break; 
      case 3:
         printf("PERFECT! New pair. Press any key.");
      break;
      case 4:
         printf("Ooooh! Not a pair. Press any key.");
      break; 
      case 5:
         printf("<<<<<< EXIT: (ESC) Pressed >>>>>>");
      break;
      case 6:
         printf("FINISH. You WIN! Congratulations.");
      break; 
      case 7:
         printf("GAME OVER. Ooh!!! Not more moves.");
      break;
   }
   if (status > 1) getchP2_C();     
}


/**
 * Joc del Memory
 * Funció principal del joc.
 * Trobar totes les parelles del tauler (10 parelles), girant les
 * targetes de dues en dues. Com a màxim es poden fer 15 intents.
 * 
 * Pseudo-codi:
 * Inicialitzar l'estat del joc, (state=0).
 * Esborrar la pantalla  (cridar la funció clearScreen_C).
 * Mostrar el tauler de joc (cridar la funció printBoardP2_C).
 * Actualitzar el tauler de joc i els valors dels moviments fets (moves)
 * i de les parelles fetes (pairs) cridant la funció updateBoardP2_C.
 * Mentre (state<3) fer:
 *   Mostrar un missatge,  segons el valor de la variable (state),
 *   per a indicar que s'ha de fer, cridant la funció printMessageP2_C.
 *   Actualitzar la posició del cursor a la pantalla a partir del vector
 *   ([rowcol]) (fila (rowcol[0]) i la columna (rowcol[1])) amb la posicio
 *   del cursor dins la matriu, cridant la funció posCurScreenP2_C.
 *   Llegir una tecla, cridar la funció getchP2_C. 
 *   Segons la tecla llegida cridarem a les subrutines que corresponguin.
 *     - ['i','j','k' o 'l'] desplaçar el cursor segons la direcció 
 *       triada, cridant la funció moveCursorP2_C).
 *     - '<SPACE>'(codi ASCII 32) girar la targeta on hi ha el cursor
 *       cridant la funció openCardP2_C.
 *       Actualitzar el tauler de joc i els valors dels moviments fets (moves)
 *       i de les parelles fetes (pairs) cridant la funció updateBoardP2_C.
 *       Si s'han girat dues targetes (state>1) incrementar els moviments (moves)
 *       Verificar si les dues targetes que s'han girant són iguales
 *       cridant la funció checkPairsP2_C.
 *       Si son iguals (state==3) incrementar les parelles (pairs).
 *       Si s'han fet 15 moviments canviar a l'estat de moviments exhaurits (state=7). 
 *       Si s'han fet 10 parelles canviar a l'estat de joc guanyat (state=6).
 *       Mostrar un missatge,  segons el valor de la variable (state),
 *       per a indicar que ha passat, cridant la funció printMessageP2_C. 
 *       Si no hem de sortir (state<5) posar (state=0) per a tornar a 
 *       intentar fer una nova parella.
 *       Actualitzar el tauler de joc i els valors dels moviments fets (moves)
 *       i de les parelles fetes (pairs) cridant la funció updateBoardP2_C.
 *    - '<ESC>'  (codi ASCII 27) posar (state = 5) per a sortir.
 *       No sortira si només s'ha girat una targeta (state!=1).
 * Fi mentre.
 * Sortir: S'acaba el joc.
 *  
 * Variables globals utilitzades:	
 * Cap.
 * 
 * Paràmetres d'entrada : 
 * Cap.
 * 
 * Paràmetres de sortida: 
 * Cap.
 * 
 * Aquesta funció no es crida des d'assemblador.
 * S'ha definit una subrutina d'assemblador equivalent 'playP1' per a cridar
 * les subrutines del joc definides en assemblador.
 */
void playP2_C(){

   int state  = 0;// 0: 0 Targetes obertes.
                  // 1: 1 Targeta oberta.
                  // 2: 2 Targetes obertes.
                  // 3: Hi ha parella.
                  // 4: No hi ha parell.
                  // 5: Sortir, hem premut la tecla 'ESC' per a sortir.
                  // 6: Guanya, totes les parelles fetes.
                  // 7: Perd, s'han exhaurits els moviments .


   //char  charac;    //Caràcter llegit de teclat i per a escriure a pantalla.

  
   //int   rowScreen; //Fila on volem posicionar el cursor a la pantalla.
   //int   colScreen; //Columna on volem posicionar el cursor a la pantalla.

   short rowcol[2]; //Vector de dues posicions de tipus short(2 bytes) on  
                    //tenim la fila (rowcol[0]) i la columna (rowcol[1]) 
                    //per a indicar la posició del cursor dins la matriu.
                  
   int   moves;     //Parelles que s'han intentat fer amb èxit o sense.
   int   pairs;     //Parelles que s'han fet.
   char  charac;    //Caràcter llegit de teclat i per a escriure a pantalla.

   state = 0;       //Estat per a començar a jugar.
   moves = 0;
   pairs = 0;  
   rowcol[0] = 2;   //Posició inicial del cursor dins la matriu.
   rowcol[1] = 1;
   
   
   clearScreen_C();
   printBoardP2_C();
   updateBoardP2_C(moves, pairs);
   
   while (state < 3) {        //Bucle principal.
	  printMessageP2_C(state);
      posCurScreenP2_C(rowcol);     
      charac = getchP2_C();   
   
      if (charac>='i' && charac<='l') {
         moveCursorP2_C(charac, rowcol);
      }
      if (charac==32) {
         state = openCardP2_C(rowcol, state);
         updateBoardP2_C(moves, pairs);
         
         if (state > 1) {
			moves++;
			state = checkPairsP2_C();
			if (state == 3) pairs++;
			
            if (moves == 15) state = 7;
            if (pairs == 10) state = 6;
			printMessageP2_C(state);
            if (state < 5) state = 0;
            updateBoardP2_C(moves, pairs);
         }
      }  
      if ( (charac==27) && (state!=1) ) {
         state = 5;
      }
   }
   
}


/**
 * Programa Principal
 * 
 * ATENCIÓ: Podeu provar la funcionalita de les subrutines que s'han de
 * desenvolupar treient els comentaris de la crida a la funció 
 * equivalent implementada en C que hi ha sota a cada opció.
 * Per al joc complet hi ha una opció per la versió en assemblador i 
 * una opció pel joc en C.
*/
int main(void){
   
   int   op=0;
   int   state = 0;    
   short rowcol[2];
   int   moves = 0;
   int   pairs = 0;
   char  charac;
   
   while (op!='0') {
      clearScreen_C();
      op = printMenuP2_C();    //Mostrar menú i demana opció
      switch(op){
          case '1': //Posicionar el cursor a la pantalla, dins el tauler.
            printf(" %c",op);
            clearScreen_C();    
            printBoardP2_C();   
            gotoxyP2_C(26,12);
            printf(" Press any key ");
            rowcol[0]=3;
            rowcol[1]=4;
            //=======================================================        
            posCurScreenP2(rowcol);
            //posCurScreenP2_C(rowcol);
            //=======================================================
            getchP2_C();
         break; //Converteix un valor (entre 0 i 99) en 2 dos caràcters ASCII.
         case '2': //Mostra 
            printf(" %c",op);
            clearScreen_C();    
            printBoardP2_C();
            int rowScreen = 19;
            int colScreen = 15;
            int value = 99;
            //=======================================================        
            showDigitsP2(rowScreen, colScreen, value);
            //showDigitsP2_C(rowScreen, colScreen, value);
            //=======================================================
            gotoxyP2_C(26,12);
            printf(" Press any key ");
            getchP2_C();
         break;
         case '3': //Actualitzar el contingut del tauler.
            clearScreen_C();       
            printBoardP2_C();      
            //=======================================================
            updateBoardP2(15, 10);
            //updateBoardP2_C(15, 10);
            //=======================================================
            gotoxyP2_C(26,12);
            printf(" Press any key ");
            getchP2_C();
         break;
         case '4': //Actualitzar posició del cursor al tauler. 
            clearScreen_C();
            printBoardP2_C();
            updateBoardP2_C(moves, pairs);
            gotoxyP2_C(26,12);
            printf(" Press i,j,k,l ");
            rowcol[0]=3;
            rowcol[1]=0;
            posCurScreenP2_C(rowcol);
            charac = getchP2_C();   
            if (charac>='i' && charac<='l') {
			//=======================================================
            moveCursorP2(charac, rowcol);
            //moveCursorP2_C(charac, rowcol);  
            //=======================================================
            }
            gotoxyP2_C(26,12);
            printf(" Press any key ");
            posCurScreenP2_C(rowcol);
            getchP2_C();
         break;
         case '5': //Calcular l'índex per a accedir a la matriu 4x5.
            clearScreen_C();
            printBoardP2_C();
            rowcol[0]=2;
            rowcol[1]=4;
            
            int row=2;
            int col=4;
            //===Cridem subrutina calIndexP2 en assemblador===========
              int indexMat = calcIndexP2(row, col);
              charac = mCards[indexMat/5][indexMat%5];
            //=======================================================
            openCardP2_C(rowcol, state);
            updateBoardP2_C(moves, pairs); 
            gotoxyP2_C(26,1);
            printf("Index: C: mCards[%i][%i] - Assembler: [ mCards + %i ] = %c  >Press any key<",indexMat/5, indexMat%5, indexMat, mOpenCards[indexMat/5][indexMat%5]);           
            getchP2_C();
       break;
       case '6': //Obrir una targeta on hi ha el cursor
            clearScreen_C();
            printBoardP2_C();
            gotoxyP2_C(26,12);
            printf("Press <space> ");
            updateBoardP2_C(moves, pairs);
            rowcol[0]=1;
            rowcol[1]=2;
            posCurScreenP2_C(rowcol);
            state=0;
            charac = getchP2_C(); 
            if (charac>=' ') {
			//=======================================================
               state = openCardP2(rowcol, state);
               //state = openCardP2_C(rowcol, state);
            //=======================================================
            }
            updateBoardP2_C(moves, pairs);
            printMessageP2_C(state);
            gotoxyP2_C(26,12);
            printf(" Press any key ");
            getchP2_C();
         break;
         case '7': //Comprovar si les dues targetes obertes són iguals
            clearScreen_C();
            printBoardP2_C();
            state = 0;
            rowcol[0]=1;
            rowcol[1]=1;
            state = openCardP2(rowcol, state);
            printMessageP2_C(state);
            rowcol[0]=2; 
            rowcol[1]=1;//Si es vol fer una parella posar 3
            state = openCardP2(rowcol, state);
            gotoxyP2_C(26,12);
            printf("Press <space> ");
            updateBoardP2_C(moves, pairs);
            posCurScreenP2_C(rowcol);
            charac = getchP2_C(); 
            if (charac>=' ') {
			//=======================================================
               state = checkPairsP2();
               //state = checkPairsP2_C();;
            //=======================================================
            }
            updateBoardP2_C(moves, pairs);
            printMessageP2_C(state);
         break;
         case '8': //Joc complet en Assemblador  
            //=======================================================
            playP2();
            //=======================================================
         break;
         case '9': //Joc complet en C
            //=======================================================
            playP2_C();
            //=======================================================
         break;
     }
   }
   printf("\n\n");
   
   return 0;
   
}
