#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define LARGEUR_ECRAN 100
#define HAUTEUR_ECRAN 28
#define ESPACE_OBSTACLES 7

void dessinerBordure();
void generateurObstacles(int ind);
void dessinerObstacles(int ind);
void effacerObstacles(int ind);
void dessinerHelicoptere();
void effacerHelicoptere();
int collision();
void Score();
void jouer();
void finPartie();

using namespace std;
HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int PosObstacle[5], PosEcart[5], Obstacles[5], PosHelicoptere=6, score=0;
char helicoptere[4][6]={
					' ',' ','_','_','__',' ',
					' ',' ',' _','_|','_',' ',
					'\\','_',' |',' ',' |','_',
					' ',' ',' |','_','__','_|'
			     };


void gotoxy(int x, int y){
	CursorPosition.X=x;
	CursorPosition.Y=y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size){
	if(size==0){
		size=20;
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible=visible;
	lpCursor.dwSize=size;
	SetConsoleCursorInfo(console, &lpCursor);
}

int main()
{
    setcursor(0, 0);
	char choix;
	do{
		system("cls");
		gotoxy(15, 5);cout<<"Ûßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß   D I R I G E R   ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßÛ";
		gotoxy(15, 6);cout<<"Û                                                                                         Û";
		gotoxy(15, 7);cout<<"Û   Û   Û   ÛßßßÛ   Û       Û   ßßßßÛ   ÛßßßÛ   ÛßßßÛ   ÛßßßÛ   ÛßßßÛ   ÛßßßÛ    ÛßßßÛ    Û";
		gotoxy(15, 8);cout<<"Û   Û   Û   ß       Û       Û   Û       Û   Û   ß   Û     Û     ß       ß   Û    ß        Û";
		gotoxy(15, 9);cout<<"Û   Ûßßßß   Ûßßß    Û       Û   Û       Û   Û   Ûßßßß     Û     Ûßßß    ÛßßßßßÛ  Ûßßß     Û";
		gotoxy(15, 10);cout<<"Û   Û   Û   Û       ß       Û   Û       ß   Û   Û         Û     Û       Û     Û  Û        Û";
		gotoxy(15, 11);cout<<"Û   ß   ß   ßßßßß   ßßßßß   ß   ßßßßß   ßßßßß   ß         ß     ßßßßß   ß     Û  ßßßßß    Û";
		gotoxy(15, 12);cout<<"Û                                                                             Û           Û";
		gotoxy(15, 13);cout<<"ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß ßßßßßßßßßßßßß";
		gotoxy(42, 15);cout<<"1.- COMMENCER\t\t\t 2.- QUITTER";
		gotoxy(35, 17);cout<<"- Copyright HAITI DEVELOPPEURS - Tous droit reserves -";
		choix=getche();
		switch(choix){
			case '1':{
				jouer();
				break;
			}
			case '2':{
				exit(0);
				break;
			}
		}
	}while(1);
    return 0;
}

void dessinerBordure(){
	//hauteur ecran
	for(int i=20; i<LARGEUR_ECRAN; i++){
		gotoxy(54,1);printf("H D    G A M E");
		gotoxy(i, 2);printf("Û"); gotoxy(50,2);printf(" H E L I C O P T E R E ");//bar superieur
		gotoxy(i, HAUTEUR_ECRAN);printf("ß");//bar inferieur
	}
	//largeur ecran
	for(int i=2; i<HAUTEUR_ECRAN; i++){
		gotoxy(20, i);printf("Û");//bar a gauche
		gotoxy(99, i);printf("Û");//bar a droite
	}
	//bar lateral
	for(int i=20; i<99; i++){
		gotoxy(i, 24);printf("Û");//bar au milieu
	}
}

void generateurObstacles(int ind){
	PosEcart[ind]=3 + rand()%14;
}

void dessinerObstacles(int ind){
	if(Obstacles[ind]==true){
			//Obstacle Superieur
		for(int i=2; i<PosEcart[ind];i++){
			gotoxy(95-PosObstacle[ind], i+1);
			printf("±±±±±");
		}
			//Obstacle Inferieur
		for(int i=PosEcart[ind]+ESPACE_OBSTACLES; i<23; i++){
			gotoxy(95-PosObstacle[ind], i+1);
			printf("±±±±±");
		}
	}
}

void effacerObstacles(int ind){
	if(Obstacles[ind]==true){
		for(int i=2; i<PosEcart[ind]; i++){
			gotoxy(95-PosObstacle[ind], i+1);
			printf("     ");
		}
		for(int i=PosEcart[ind]+ESPACE_OBSTACLES; i<23; i++){
			gotoxy(95-PosObstacle[ind], i+1);
			printf("     ");
		}
	}
}

void dessinerHelicoptere(){
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+23, i+PosHelicoptere);
			printf("%c",helicoptere[i][j]);
		}
	}
}

void effacerHelicoptere(){
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+23, i+PosHelicoptere);
			printf(" ");
		}
	}
}

int collision(){
	if(PosObstacle[0]>=61){
		if(PosHelicoptere<PosEcart[0] || PosHelicoptere>PosEcart[0]+ESPACE_OBSTACLES){
			return 1;
		}
	}
	return 0;
}

void Score(){
	gotoxy(27, 26);
	printf("Score: %d",score);
	gotoxy(47, 26);
	printf("Pour diriger l'h%clicopt%cre presser 'backspace'",130,138);
	gotoxy(37, 12);printf("Presser n'importe quelle tourche pour commencer");
	getch();
	gotoxy(37, 12);printf("                                               ");
}

void jouer(){
	PosHelicoptere=9;
	score=0;
	Obstacles[0]=1;Obstacles[1]=0;
	PosObstacle[0]=PosObstacle[1]=2;
	system("cls");
	dessinerBordure();
	generateurObstacles(0);
	Score();

	while(1){
		if(kbhit()){
			char ch=getch();
			if(ch==32){
				if(PosHelicoptere>1)
					PosHelicoptere-=2;
			}
			/* permet de pause le jeu
			if(ch=='r'){
				system("pause");
			}*/
		}
		dessinerHelicoptere();
		dessinerObstacles(0);
		dessinerObstacles(1);
		if(collision()==1){
			finPartie();
			return;
		}
		Sleep(150);
		effacerHelicoptere();
		effacerObstacles(0);
		effacerObstacles(1);
		PosHelicoptere+=1;
		//elle evite l'helicop de quitter la zone d'obstacle
		if(PosHelicoptere > HAUTEUR_ECRAN-8 || PosHelicoptere <= 3){
			finPartie();
			return;
		}
		if(Obstacles[0]==1)
			PosObstacle[0]+=2;
		if(Obstacles[1]==1)
			PosObstacle[1]+=2;
		if(PosObstacle[0] >= 40 && PosObstacle[0] < 42){
			Obstacles[1]=1;
			PosObstacle[1]=4;
			generateurObstacles(1);
		}
		if(PosObstacle[0]>69){
			score++;
			Obstacles[1]=0;
			PosObstacle[0]=PosObstacle[1];
			PosEcart[0]=PosEcart[1];
		}
	}
}

void finPartie(){
	gotoxy(55, 10);printf("T'as perdu!!!");
	gotoxy(53, 12);printf("Ton score est: %d\n",score);
	gotoxy(48, 13);system("pause");
	printf(" ");
}


