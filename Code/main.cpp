
/*GIOCO DI SNAKE*/
#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>


#define MAXDIM 1580       //DA FILE              //valore max che il verme deve raggiungere
#define MAX_X 69          //DA FILE
#define MAX_Y 23          //DA FILE

int food_x;
int food_y;
int head_x;
int head_y;
int direzione;
int old_direzione;
int dim;
int snake_x[MAXDIM];
int snake_y[MAXDIM];
int oldsnake_x[MAXDIM];
int oldsnake_y[MAXDIM];
int record;

//FUNCTION
void ctrl_snake(void);
void gotoxy(int x, int y);
void bordi(void);
int get_direction(void);
void food_gen(void);
void inizializer(void);
int read_record(void);
void game(void);
void start(void);
void snake(void);
void game_over(int val);
void print_snake(void);
void border_snake(void);
int random(void);
void remove_cursor(void);
void write_record(int val);
int main(void);

void write_record(int val){
     FILE *writePtr;
     if((writePtr=fopen("record.txt" , "w"))==NULL){
        val=0;
        fprintf(writePtr,"%d" ,val);
        }else{
              fprintf(writePtr,"%d" ,val);
              }
     fclose(writePtr);
}
int read_record(){
    int rcd=0;
    FILE *readPtr;
    if((readPtr=fopen("record.txt" , "r"))==NULL){
        rcd=10000;
        return rcd;
        }else{
              fscanf(readPtr, "%d", &rcd);
              return rcd;
              }
    fclose(readPtr);
}

//Stampa iniziale di partenza gioco
void start(void){
     bordi();
     gotoxy(13,4);
     printf("------   |\\    |      /\\      |  /    ------");
     gotoxy(13,5);
     printf("|        | \\   |     /  \\     | /     |      ");
     gotoxy(13,6);
     printf("|_____   |  \\  |    /    \\    |/      |_____");
     gotoxy(13,7);
     printf("      |  |   \\ |   /______\\   | \\     |      ");
     gotoxy(13,8);
     printf("______|  |    \\|  /        \\  |  \\    |_____");
     gotoxy(MAX_X/3+3,MAX_Y/2+5);
     printf("Push ENTER to start");
     int btn=0; 
     while(btn!=13){
                if (kbhit()) {
        			btn = getch();
        		}
            }
     system("cls");
     bordi();
     }

//Acquisisce la direzione a seconda del tasto premuto, ritorna la direzione
int get_direction(void){

if (kbhit()) {
			int tasto = getch();
			if (tasto == 0) tasto = getch();
			
                           
    			switch (tasto) {
    			case'w':
    				direzione = 1;
    				break;
    			case's':
    				direzione = 2;
    				break;
    			case'd':
    				direzione = 3;
    				break;
    			case'a':
    				direzione = 4;
    			default:
                     direzione;
    				break;
    			}
}
if((old_direzione==4 && direzione==3) || (old_direzione==3 && direzione==4 || (old_direzione==1 && direzione==2) || (old_direzione==2 && direzione==1))){
                     direzione=old_direzione;
                     }
        old_direzione=direzione;             
return direzione;
}

//Posizione il cursore per scrivere
void gotoxy(int x, int y)
{

	COORD coord;

	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
}

//Controlla la collisione con i bordi
void border_snake(void){
    switch (get_direction()){
           
           case 1:
                head_y-=1;
                if(head_y==0)head_y=24;
                break;
           case 2:
                head_y+=1;
                 if(head_y==25)head_y=1;
                break;
           case 3:
                head_x+=1;
                 if(head_x==70)head_x=1;
                break;
           case 4:
                head_x-=1;
                 if(head_x==0)head_x=69;
                break;
           }
}

//Aggiorna costantemente gli array snake_x e snake_y delle cordinate 
void snake(void){
    snake_x[0]=head_x;
    snake_y[0]=head_y; 
    
    for(int i=1;i<=MAXDIM;i++){
            snake_x[i]=oldsnake_x[i-1];
            snake_y[i]=oldsnake_y[i-1];
            oldsnake_x[i-1]=snake_x[i-1];
            oldsnake_y[i-1]=snake_y[i-1];
            } 
            
}

//Funzione di fine gioco
void game_over(int val){
    
    bordi();
    if(val==0){
    gotoxy(MAX_X/2-4,MAX_Y/2);
    printf("GAME OVER");
    if(record<dim){
     record=dim;              
    write_record(dim);              
    }
    gotoxy(MAX_X/3+1,MAX_Y/2+5);
    printf("Push ENTER to restart");
    }else{
    gotoxy(MAX_X/2-20,MAX_Y/2);
    printf("WINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    gotoxy(MAX_X/3+3,MAX_Y/2+5);
    printf("Push ENTER to restart");
    }
    int btn=0; 
    while(btn!=13){
                if (kbhit()) {
        			btn = getch();
        		}
            }
    main();
}
    
//Stampa lo snake e fa alcuni controlli
void print_snake(){
    for(int i=0;i<MAXDIM;i++){
            if(snake_x[i]==food_x && snake_y[i]==food_y){
                                  dim+=1;
                                  if(dim==MAXDIM){
                                                  game_over(1);
                                                  }
                                  food_gen();
                                  }
                                  
            
            for(int x=1;x<dim;x++){
                      if(snake_x[x]==head_x && snake_y[x]==head_y  ){
                                  game_over(0);
                                  }
                      }
                          
                          
                          
            if(i<dim){
            gotoxy(snake_x[i],snake_y[i]);
            putch('*');
            }else{
                  
                  gotoxy(snake_x[i],snake_y[i]);
                  putch(' ');
                  break;
                  }
    }
  gotoxy(0,0);
  putch('#'); 
   
}

//Disegna i bordi del campo
void bordi(void){
    
 for(int i=0;i<=70;i++){
         gotoxy(i,0);
         putch('#');
         }
 for(int i=0;i<=70;i++){
         gotoxy(i,25);
         putch('#');
         } 
 for(int i=0;i<=25;i++){
         gotoxy(0,i);
         putch('#');
         } 
 for(int i=0;i<=25;i++){
         gotoxy(70,i);
         putch('#');
         }    
}

//ciclo principale del gioco
void game(void){
    food_gen();
    while(1){
        border_snake();
        snake();
        print_snake();
        gotoxy(4,26);
        printf("Score: %d", dim);
        gotoxy(4,28);
        printf("Record: %d", record);
        //gotoxy(20,26);
        //printf("Finish at: %d", MAXDIM);
        Sleep(80);
        
    }
}

//Funzione random per generare il cibo
int random(int maxnum) {
    int gen;
	gen = rand()%maxnum;
	return gen;
}

//Genera il cibo random
void food_gen(void){
   
     food_x=1+random(MAX_X);
     food_y=1+random(MAX_Y);
     gotoxy(food_x,food_y);
     putch('@');
     }
     
//Rimuove il cursore 
void removeCursor(void) 
{ 
    CONSOLE_CURSOR_INFO curInfo; 
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); 
    curInfo.bVisible=0; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo); 
}

//Inizializza variabili generali e configura il prompt
void inizializer(void){
removeCursor();
system("color 84");
system("cls");
head_x=10;
head_y=10;
direzione=3;                   
old_direzione=0;
dim=1;                 
record=read_record();
srand(time(NULL));
bordi();
}

///////////////////////////////////////
int main(void){
    inizializer();                             
    start();
    game();
}


