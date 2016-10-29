#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char tablero[8][8];

void iniciar() {
	int i, j;
	char piezas[] = "TCARQACT";

	for (i = 0;i<8;i++) {
		tablero[0][i] = piezas[i];
		tablero[1][i] = 'P';

		for (j = 2;j<6;j++) {
			tablero[j][i] = '.';
		}

		tablero[6][i] = 'p';
		tablero[7][i] = tolower(piezas[i]);

	}
}

void imprimirTablero(int contador) {
	int i, j, k;

	if (contador%2==0) {
		k = 1;
	}
	else {
		k = 2;
	}

	printf("Jugando jugador: %d\n",k);
	printf("\n |");
	for (i = 0;i<8;i++) {
		printf("%d",i);
	}
	printf("\n");
	printf("-|--------\n");

	for (i = 0;i<8;i++) {
		printf("%c|",'A'+i);
		for (j = 0;j<8;j++) {
			printf("%c",tablero[i][j]);
		}
		printf("\n");
	}

}

void jugada(int *letra1, int *num1, int *letra2, int *num2){
	char jugada[10],A[4],B[4],c;
	
	fgets(jugada,sizeof(jugada),stdin);
	sscanf(jugada,"%s %c %s",A,&c,B);		
		
	*letra1 = A[0] - 'A';
	*num1 = A[1] - '0';
	*letra2 = B[0] - 'A';
	*num2 = B[1] - '0';
	
	while( c!='a' || *letra1>7 || *letra1<0 || *letra2>7 || *letra2<0 || *num1>7 || *num1<0 || *num2>7 || *num2<0 || (*letra1==*letra2 && *num1==*num2)){
		printf("Jugada invalida\n");
		
		fgets(jugada,sizeof(jugada),stdin);
		sscanf(jugada,"%s %c %s",A,&c,B);		
	
		*letra1 = A[0] - 'A';
		*num1 = A[1] - '0';
		*letra2 = B[0] - 'A';
		*num2 = B[1] - '0';	
	};
	printf("%d %d\n",*letra1,*num1);
	printf("%c\n",c);
	printf("%d %d\n",*letra2,*num2);
}

void mover(int letra1, int num1, int letra2, int num2) {
	tablero[letra2][num2] = tablero[letra1][num1];
	tablero[letra1][num1] = '.';

}

int terminado() {
	//
	return 0;
}


int main()
{
	int letra1, num1;
	int letra2, num2;
	int contador=0;

	iniciar();

	while (!terminado()){
		
		imprimirTablero(contador);
		
		jugada(&letra1,&num1,&letra2,&num2);
		
		//mover(letra1,num1,letra2,num2);
		contador++;
	}

	return 0;
}
