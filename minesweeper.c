#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
//function declaration
void menu();
void bombGenerator(int *playField);
void showFieldGenerator(char *showField);
void display(char *showField);
void firstStep(int *playField);
void countBombAround(int *playField);
void bombCount(int *playField);
void openCells(int *playField, char *showField);
void openZeroBlock(int *playField, char *showField);
void openBlock(int m, int n, int *playField, char *showField);
int loseCheck(int *playField, char *showField);
int victoryCheck(int *playField, char *showField);
void displayRules();
//declaration of constants
int x=10,ch,win=0,lose=0,nbomb,a,b;
//main program
int main()
{
	//declaration arrays
	int playField[x*x],i,j;
	char showField[x*x];
	//declaration rand for bomb generator
	srand(time(0));
	//
	while(1)
	{
		//show start menu on display
		menu();
		//menu buttons
		switch(ch)
		{
			//first button - game
			case 49:
				bombGenerator(playField);//create bomb on fild
				showFieldGenerator(showField);//create close field for show
				display(showField);//show close fild for first step
				//first move reading
				printf("Input line and colum to open:\nLine - ");
				do{
				    a=getch();
				    if(a==27)break;
			    }while(a<48 || a>57);
			    if(a==27)break;
			    printf("%c\nColumn - ",a);
			    do{
				    b=getch();
				    if(b==27)break;
			    }while(b<48 || b>57);
			    if(b==27)break;
			    printf("%c",b);
			    a=a-48;
			    b=b-48;
			    
				firstStep(playField);//function removes bombs (for the first move)
				countBombAround(playField);//recording the number of bombs around the cell
				bombCount(playField);//counting bombs to test for victory
				
				//game cycle
				while(1)
				{
				    openCells(playField,showField);//replacement of closed cells with open ones
				    
				    ch=victoryCheck(playField,showField);//win check
					if(ch==1) break;
					
				    display(showField);//show playing field on display
				    //reading of moves
				    printf("Input line and colum to open:\nLine - ");
				    do{
				        a=getch();
				        if(a==27)break;
			        }while(a<48 || a>57);
			        if(a==27)break;
			        printf("%c\nColumn - ",a);
			        do{
				        b=getch();
				        if(b==27)break;
			        }while(b<48 || b>57);
			        if(b==27)break;
			        printf("%c",b);
			        a=a-48;
			        b=b-48;
			        //lose check
					ch=loseCheck(playField,showField);
					if(ch==1) break;
				}
				
				break;
				//second buton - rulse
			case 50:
				displayRules();//show ruls on display
				break;
				//third button - exit from a program
			case 27:
				return 0;
		}
	}
}

void menu()
{
	do{
		system("cls");
        printf("Wins: %i  Lose: %i\n",win,lose);
        printf("1. Start game\n");
        printf("2. Rules\n");
        printf("ESC - Exit\n");
        ch=getch();
	}while(ch!=49&&ch!=50&&ch!=27);
}

void bombGenerator(int *playField)
{
	int i,j,n;
	for(i=0;i<x;i++){
		for(j=0;j<x;j++){
			if(1+rand()%6==6){
				*(playField+(i*x)+j)=8;
				n++;
			}else{
				*(playField+(i*x)+j)=0;
			}
		}
	}
}

void showFieldGenerator(char *showField)
{
	int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<x;j++){
			*(showField+(i*x)+j)=35;
		}
	}
}

void display(char *showField)
{
	int i,j;
	system("cls");
	printf(" | 0 1 2 3 4 5 6 7 8 9\n");
	printf("-+--------------------\n");
	for(i=0;i<x;i++){
		printf("%i|",i);
        for(j=0;j<x;j++){
            printf("%2c",showField[i*x+j]);
        }
        printf("\n");
    }
}

void firstStep(int *playField)
{
	*(playField+a*x+b)=0;
	if(a>0 && b>0) *(playField+(a-1)*x+b-1)=0;
	if(a>0) *(playField+(a-1)*x+b)=0;
	if(a>0 && b<x-1) *(playField+(a-1)*x+b+1)=0;
	if(b>0) *(playField+a*x+b-1)=0;
	if(b<x-1) *(playField+a*x+b+1)=0;
	if(a<x-1 && b>0) *(playField+(a+1)*x+b-1)=0;
	if(a<x-1) *(playField+(a+1)*x+b)=0; 
	if(a<x-1 && b<x-1) *(playField+(a+1)*x+b+1)=0;
}

void countBombAround(int *playField)
{
	int i,j,count;
	for(i=0;i<x;i++){
		for(j=0;j<x;j++){
			if(*(playField+i*x+j)==8) continue;
			count=0;
			if(i>0 && j>0){
				if(*(playField+(i-1)*x+j-1)==8) count++;
			}
			if(i>0){
				if(*(playField+(i-1)*x+j)==8) count++;
			}
			if(i>0 && j<x-1){
				if(*(playField+(i-1)*x+j+1)==8) count++;
			}
			if(j>0){
				if(*(playField+i*x+j-1)==8) count++;
			}
			if(j<x-1){
				if(*(playField+i*x+j+1)==8) count++;
			}
			if(i<x-1 && j>0){
				if(*(playField+(i+1)*x+j-1)==8) count++;
			}
			if(i<x-1){
				if(*(playField+(i+1)*x+j)==8) count++;
			}
			if(i<x-1 && j<x-1){
				if(*(playField+(i+1)*x+j+1)==8) count++;
			}
			*(playField+i*x+j)=count;
		}
	}
}

void bombCount(int *playField)
{
	int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<x;j++){
			if(*(playField+i*x+j)==8) nbomb++;
		}
	}
}

void openCells(int *playField, char *showField)
{
	if(*(playField+a*x+b)==8){
		*(showField+a*x+b)=66;
	}
	else if(*(playField+a*x+b)==0){
	    *(showField+a*x+b)=48;
		openZeroBlock(playField,showField);	
	}
	else{
		*(showField+a*x+b)=*(playField+a*x+b)+48;
	}
}

void openZeroBlock(int *playField, char *showField)
{
	int i,j;
	openBlock(a,b,playField,showField);
	i=1;
	while(*(playField+a*x+b+i)==0 && b+i>-1 && b+i<x){
		openBlock(a,b+i,playField,showField);
		j=1;
		while(*(playField+(a+j)*x+b+i)==0 && a+j>-1 && a+j<x && b+i>-1 && b+i<x){
			openBlock(a+j,b+i,playField,showField);
			j++;
		}
		j=1;
		while(*(playField+(a-j)*x+b+i)==0 && a-j>-1 && a-j<x && b+i>-1 && b+i<x){
			openBlock(a-j,b+i,playField,showField);
			j++;
		}
		i++;
	}
	i=1;
	while(*(playField+a*x+b-i)==0 && b-i>-1 && b-i<x){
		openBlock(a,b-i,playField,showField);
		j=1;
		while(*(playField+(a+j)*x+b-i)==0 && a+j>-1 && a+j<x && b-i>-1 && b-i<x){
			openBlock(a+j,b-i,playField,showField);
			j++;
		}
		j=1;
		while(*(playField+(a-j)*x+b-i)==0 && a-j>-1 && a-j<x && b-i>-1 && b-i<x){
			openBlock(a-j,b-i,playField,showField);
			j++;
		}
		i++;
	}
	i=1;
	while(*(playField+(a+i)*x+b)==0 && a+i>-1 && a+i<x){
		openBlock(a+i,b,playField,showField);
		j=1;
		while(*(playField+(a+i)*x+b+j)==0 && a+i>-1 && a+i<x && b+j>-1 && b+j<x){
			openBlock(a+i,b+j,playField,showField);
			j++;
		}
		j=1;
		while(*(playField+(a+i)*x+b-j)==0 && a+i>-1 && a+i<x && b-j>-1 && b-j<x){
			openBlock(a+i,b-j,playField,showField);
			j++;
		}
		i++;
	}
	i=1;
	while(*(playField+(a-i)*x+b)==0 && a-i>-1 && a-i<x){
	    openBlock(a-i,b,playField,showField);
	    j=1;
	    while(*(playField+(a-i)*x+b+j)==0 && a-i>-1 && a-i<x && b+j>-1 && b+j<x){
	            openBlock(a-i,b+j,playField,showField);
	            j++;
	    }
	    j=1;
	    while(*(playField+(a-i)*x+b-j)==0 && a-i>-1 && a-i<x && b-j>-1 && b-j<x){
	            openBlock(a-i,b-j,playField,showField);
	            j++;
	    }
	    i++;
	}	
}

void openBlock(int m, int n, int *playField, char *showField)
{
	if(m>0 && n>0){
	    *(showField+(m-1)*x+n-1)=*(playField+(m-1)*x+n-1)+48;
	}
    if(m>0){
        *(showField+(m-1)*x+n)=*(playField+(m-1)*x+n)+48;
    }
    if(m>0 && n<x-1){
        *(showField+(m-1)*x+n+1)=*(playField+(m-1)*x+n+1)+48;
    }
    if(n>0){
        *(showField+m*x+n-1)=*(playField+m*x+n-1)+48;
    }
    if(n<x-1){
        *(showField+m*x+n+1)=*(playField+m*x+n+1)+48;
    }
    if(m<x-1 && n>0){
        *(showField+(m+1)*x+n-1)=*(playField+(m+1)*x+n-1)+48;
    }
    if(m<x-1){
        *(showField+(m+1)*x+n)=*(playField+(m+1)*x+n)+48;
    }
    if(m<x-1 && n<x-1){
        *(showField+(m+1)*x+n+1)=*(playField+(m+1)*x+n+1)+48;
    }
}

int loseCheck(int *playField, char *showField)
{
	if(*(playField+a*x+b)==8){
		*(showField+a*x+b)=66;
		display(showField);
		printf("Game Over!\npress any key to continue");
		lose++;
		int a=getch();
		return 1;
	}else{
		return 0;
	}
}

int victoryCheck(int *playField, char *showField)
{
	int i,j,closeCell=0;
	for(i=0;i<x;i++){
		for(j=0;j<x;j++){
			if(*(showField+i*x+j)==35) closeCell++;
		}
	}
	if(closeCell<=nbomb){
		for(i=0;i<x;i++){
			for(j=0;j<x;j++){
				if(*(showField+i*x+j)==35){
					*(showField+i*x+j)=66;
				}
			}
		}
		system("cls");
		display(showField);
		printf("Victory!!!\npress any key to continue");
		win++;
		i=getch();
		return 1;
	}else{
		return 0;
	}
}

void displayRules()
{
	do{
		system("cls");
		printf("The rule of the game is simple, the number on a block shows the number of mines adjacent to it!");
		printf("\nYou need to open all the cells to win!");
		printf("\nIf you hit a bomb - defeat!");
		printf("\nESC - back to menu");
		ch=getch();
	}while(ch!=27);
}
