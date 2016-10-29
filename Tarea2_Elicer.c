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

	//Error base, input invalido
	while( c!='a' || *letra1>7 || *letra1<0 || *letra2>7 || *letra2<0 || *num1>7 || *num1<0 || *num2>7 || *num2<0 || (*letra1==*letra2 && *num1==*num2)){
		printf("Jugada invalida\n");

		fgets(jugada,sizeof(jugada),stdin);
		sscanf(jugada,"%s %c %s",A,&c,B);

		*letra1 = A[0] - 'A';
		*num1 = A[1] - '0';
		*letra2 = B[0] - 'A';
		*num2 = B[1] - '0';
	};

	/*printf("%d %d\n",*letra1,*num1);
	printf("%c\n",c);
	printf("%d %d\n",*letra2,*num2);*/
}

int verificar(int *letra1, int *num1, int *letra2, int *num2, int contador){

	if (contador%2==0) {		//Jugador 1
		if(tablero[*letra1][*num1]-'a'<-32 || tablero[*letra1][*num1]-'a'>-7){//Jugada no corresponde a una pieza del J1.
			printf("Jugada invalida. ");
			if(tablero[*letra1][*num1]-'a'==-51){
				printf("No hay pieza en dicha posicion.\n");
			}
			else{
				printf("No puedes mover una ficha del Jugador 2.\n");
			}
			return 0;
		}
		if(tablero[*letra1][*num1]-'a'==-17){//P - Peon
			if(*letra2-*letra1==1){//Se mueve hacia adelante
				if(*num1-*num2==0){//Al frente
					if(tablero[*letra2][*num2]-'a'<=-7 && tablero[*letra2][*num2]-'a'>=-32){//Pieza jugador 1
						printf("Jugada invalida. Hay una pieza tuya en dicha posicion.\n");
						return 0;
					}else if(tablero[*letra2][*num2]-'a'<=25 && tablero[*letra2][*num2]-'a'>=0){//Pieza jugador 2
						printf("Jugada invalida. Hay una pieza del Jugador 2 en dicha posicion.\n");
						return 0;
					}else{//Jugada valida. ==-51
						return 1;
					}
				}else if(*num1-*num2==1){//Diagonal Izq
					if(tablero[*letra2][*num2]-'a'<=25 && tablero[*letra2][*num2]-'a'>=0){
						return 1;
					}else{
						printf("Jugada invalida. Movimiento no permitido\n");
						return 0;
					}
				}else if(*num1-*num2==-1){//Diagonal Der
					if(tablero[*letra2][*num2]-'a'<=25 && tablero[*letra2][*num2]-'a'>=0){
						return 1;
					}else{
						printf("Jugada invalida. Movimiento no permitido\n");
						return 0;
					}
				}
			}//end if hacia adelante
			printf("Jugada invalida. Movimiento no permitido por un peon\n");
			return 0;
		}//end Peon

		if(tablero[*letra1][*num1]-'a'==-13){//T - Torre



		}//end Torre

		if(tablero[*letra1][*num1]-'a'==-30){//C - Caballo



		}//end Caballo

		if(tablero[*letra1][*num1]-'a'==-32){//A - Alfil



		}//end Alfil

		if(tablero[*letra1][*num1]-'a'==-15){//R - Rey



		}//end Rey

		if(tablero[*letra1][*num1]-'a'==-16){//Q - Queen



		}//end Queen

	}//end Jugador 1
	else {						//Jugador 2
		//
		//
		//
	}

	return 1;
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
	int contador=0, ver;

	iniciar();

	while (!terminado()){
		imprimirTablero(contador);//Imprime tableto.
		jugada(&letra1,&num1,&letra2,&num2);//Ve si el input corresponde a la l�gica del juego.
		ver = verificar(&letra1,&num1,&letra2,&num2,contador);//Valida el movimiento del jugador.
		while(!ver){
			jugada(&letra1,&num1,&letra2,&num2);//Ve si el input corresponde a la l�gica del juego.
			ver = verificar(&letra1,&num1,&letra2,&num2,contador);//Valida el movimiento del jugador.
		}
		mover(letra1,num1,letra2,num2);//Una vez verificado el movimiento, se procede a mover la pieza.
		contador++;
	}

	return 0;
}
