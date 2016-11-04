#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
//
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

//Mayus - 'a' = [-32,-7] -> [A,Z]
//Minus - 'a' = [0,25] -> [a, z]
//' ' - 'a' = -65

int max,min,i;

/*-------------------------------Piezas-------------------------------*/
int torre(char *tablero, int letra1, int num1, int letra2, int num2, int J, int print){

	if(J==1){
		max=-7;
		min=-32;
	}
	else{
		max=25;
		min=0;
	}

	if(num1==num2){//Movimiento recto vertical
		if(letra1-letra2>0){//Hacia arriba
			for(i=letra1-1;i>letra2;i--){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[i*8+num1]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la torre\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[i*8+num1]-'a'>=min && tablero[i*8+num1]-'a'<=max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin arriba
		else{//Hacia abajo
			for(i=letra1+1;i<letra2;i++){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[i*8+num1]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la torre\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[i*8+num1]-'a'>=min && tablero[i*8+num1]-'a'<=max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin abajo
	}//fin if vertical
	else if(letra1==letra2){//Movimiento recto horizontal
		if(num1-num2>0){//Hacia izquierda
			for(i=num1-1;i>num2;i--){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[letra1*8+i]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la torre\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[letra1*8+i]-'a'>=min && tablero[letra1*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin izquierda
		else{//Hacia derecha
			for(i=num1+1;i<num2;i++){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[letra1*8+i]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la torre\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[letra1*8+i]-'a'>=min && tablero[letra1*8+i]-'a'<=-max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin derecha
	}//fin if horizontal
	else{
		if(print){
			printf("Jugada invalida. Movimiento no permitido por una torre\n");
		}
		return 0;
	}
}//end torre

int caballo(char *tablero, int letra1, int num1, int letra2, int num2, int J, int print){

	if(J==1){
		max=-7;
		min=-32;
	}
	else{
		max=25;
		min=0;
	}

	if(letra1-letra2==2 || letra1-letra2==-2){//2 abajo o 2 arriba
		if(num1-num2==1 || num1-num2==-1){
			if(tablero[letra2*8+num2]-'a'>=min && tablero[letra2*8+num2]-'a'<=max){
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}
			else{
				return 1;
			}
		}
	}//end if abajo/arriba
	else if(num1-num2==2 || num1-num2==-2){//2 der o 2 izq
		if(letra1-letra2==1 || letra1-letra2==-1){
			if(tablero[letra2*8+num2]-'a'>=min && tablero[letra2*8+num2]-'a'<=max){
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}
			else{
				return 1;
			}
		}
	}//end if der/izq
	if(print){
		printf("Jugada invalida. Movimiento no permitido por un caballo\n");
	}
	return 0;
}

int alfil(char *tablero, int letra1, int num1, int letra2, int num2, int J, int print){

	if(J==1){
		max=-7;
		min=-32;
	}
	else{
		max=25;
		min=0;
	}

	if(abs(letra1-letra2)==abs(num1-num2)){
		if(letra2-letra1>0){//Hacia abajo
			if(num2-num1>0){//Abajo DER
				for(i=num1+1;i<num2;i++){
					if(tablero[(letra1+i-num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino del alfil\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1+i-num1)*8+i]-'a'>=min && tablero[(letra1+i-num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Abajo DER
			else{//Abajo IZQ
				for(i=num1-1;i>num2;i--){
					if(tablero[(letra1-i+num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino del alfil\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1-i+num1)*8+i]-'a'>=min && tablero[(letra1-i+num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Abajo IZQ
		}//end abajo
		else{//Hacia arriba
			if(num2-num1>0){//Arriba DER
				for(i=num1+1;i<num2;i++){
					if(tablero[(letra1-i+num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino del alfil\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1-i+num1)*8+i]-'a'>=min && tablero[(letra1-i+num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Arriba DER
			else{//Arriba IZQ
				for(i=num1-1;i>num2;i--){
					if(tablero[(letra1+i-num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino del alfil\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1+i-num1)*8+i]-'a'>=min && tablero[(letra1+i-num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Arriba IZQ
		}//end arriba
	}//end if alfil
	if(print){
		printf("Jugada invalida. Movimiento no permitido por un alfil\n");
	}
	return 0;
}

int rey(char *tablero, int letra1, int num1, int letra2, int num2, int J, int print){

	if(J==1){
		max=-7;
		min=-32;
	}
	else{
		max=25;
		min=0;
	}

	if(abs(num1-num2)==1 && abs(letra1-letra2)==1){
		if(tablero[letra2*8+num2]-'a'>=min && tablero[letra2*8+num2]-'a'<=max){
			if(print){
				printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
			}
			return 0;
		}
		else{//Elimina pieza Jugador rival o avanza normalmente.
			return 1;
		}
	}
	else if(abs(num1-num2)==1 && abs(letra1-letra2)==0){
		if(tablero[letra2*8+num2]-'a'>=min && tablero[letra2*8+num2]-'a'<=max){
			if(print){
				printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
			}
			return 0;
		}
		else{//Elimina pieza Jugador rival o avanza normalmente.
			return 1;
		}
	}
	else if(abs(num1-num2)==0 && abs(letra1-letra2)==1){
		if(tablero[letra2*8+num2]-'a'>=min && tablero[letra2*8+num2]-'a'<=max){
			if(print){
				printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
			}
			return 0;
		}
		else{//Elimina pieza Jugador rival o avanza normalmente.
			return 1;
		}
	}
	else{
		if(print){
			printf("Jugada invalida. Movimiento no permitido por el rey\n");
		}
		return 0;
	}

}

int queen(char *tablero, int letra1, int num1, int letra2, int num2, int J, int print){
	if(J==1){
		max=-7;
		min=-32;
	}
	else{
		max=25;
		min=0;
	}

	if(num1==num2){//Movimiento recto vertical
		if(letra1-letra2>0){//Hacia arriba
			for(i=letra1-1;i>letra2;i--){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[i*8+num1]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[i*8+num1]-'a'>=min && tablero[i*8+num1]-'a'<=max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin arriba
		else{//Hacia abajo
			for(i=letra1+1;i<letra2;i++){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[i*8+num1]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[i*8+num1]-'a'>=min && tablero[i*8+num1]-'a'<=max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin abajo
	}//fin if vertical
	else if(letra1==letra2){//Movimiento recto horizontal
		if(num1-num2>0){//Hacia izquierda
			for(i=num1-1;i>num2;i--){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[letra1*8+i]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[letra1*8+i]-'a'>=min && tablero[letra1*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin izquierda
		else{//Hacia derecha
			for(i=num1+1;i<num2;i++){//Verifica si la torre se topa con otra pieza antes de llegar
				if(tablero[letra1*8+i]-'a'!=-65){// !=' '
					if(print){
						printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
					}
					return 0;
				}
			}//end for i
			if(tablero[letra1*8+i]-'a'>=min && tablero[letra1*8+i]-'a'<=-max){//Pieza Jugador 1 en dicha posicion
				if(print){
					printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
				}
				return 0;
			}else{//Elimina pieza Jugador rival o avanza normalmente.
				return 1;
			}
		}//fin derecha
	}//fin if horizontal
	else if(abs(letra1-letra2)==abs(num1-num2)){
		if(letra2-letra1>0){//Hacia abajo
			if(num2-num1>0){//Abajo DER
				for(i=num1+1;i<num2;i++){
					if(tablero[(letra1+i-num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1+i-num1)*8+i]-'a'>=min && tablero[(letra1+i-num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Abajo DER
			else{//Abajo IZQ
				for(i=num1-1;i>num2;i--){
					if(tablero[(letra1-i+num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1-i+num1)*8+i]-'a'>=min && tablero[(letra1-i+num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Abajo IZQ
		}//end abajo
		else{//Hacia arriba
			if(num2-num1>0){//Arriba DER
				for(i=num1+1;i<num2;i++){
					if(tablero[(letra1-i+num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1-i+num1)*8+i]-'a'>=min && tablero[(letra1-i+num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Arriba DER
			else{//Arriba IZQ
				for(i=num1-1;i>num2;i--){
					if(tablero[(letra1+i-num1)*8+i]-'a'!=-65){// !=' '
						if(print){
							printf("Jugada invalida. Otra pieza obstruye el camino de la reina\n");
						}
						return 0;
					}
				}//end for i
				if(tablero[(letra1+i-num1)*8+i]-'a'>=min && tablero[(letra1+i-num1)*8+i]-'a'<=max){//Pieza Jugador 1 en dicha posicion
					if(print){
						printf("Jugada invalida. Una pieza tuya ya está en dicha posición\n");
					}
					return 0;
				}else{//Elimina pieza Jugador rival o avanza normalmente.
					return 1;
				}
			}//end Arriba IZQ
		}//end arriba
	}//end if alfil
	if(print){
		printf("Jugada invalida. Movimiento no permitido por una reina\n");
	}
	return 0;
}
/*-------------------------------Piezas-------------------------------*/
/*-----------------------------Funciones------------------------------*/
void iniciar(char *tablero) {
	strcpy(tablero, "TCARQACTPPPPPPPP                                pppppppptcarqact");
}

void imprimirTablero(char *tablero, int contador) {
	int i, j, k;

	if (contador==1) {
		k = 1;
	}
	else {
		k = 2;
	}

	printf("\nJugando jugador: %d\n",k);
	printf("\n  |");
	for (i = 0;i<8;i++) {
		printf(" %c |",'A'+i);
	}
	printf("\n");
	printf("--|-------------------------------|\n");

	for (i = 0;i<8;i++) {
		printf("%d |",i);
		for (j = 0;j<8;j++) {
			printf(" %c |",tablero[8*i+j]);
		}
		printf("\n");
		printf("--|-------------------------------|\n");
	}
}

void jugada(int *letra1, int *num1, int *letra2, int *num2){
	char jugada[10],A[4],B[4],c;

	fgets(jugada,sizeof(jugada),stdin);
	sscanf(jugada,"%s %c %s",A,&c,B);

	*letra1 = A[1] - '0';
	*num1 = A[0] - 'A';
	*letra2 = B[1] - '0';
	*num2 = B[0] - 'A';

	//Error base, input invalido
	while( c!='a' || *letra1>7 || *letra1<0 || *letra2>7 || *letra2<0 || *num1>7 || *num1<0 || *num2>7 || *num2<0 || (*letra1==*letra2 && *num1==*num2)){
		printf("Jugada invalida\n");

		fgets(jugada,sizeof(jugada),stdin);
		sscanf(jugada,"%s %c %s",A,&c,B);

		*letra1 = A[1] - '0';
		*num1 = A[0] - 'A';
		*letra2 = B[1] - '0';
		*num2 = B[0] - 'A';
	};
}

int verificar(char *tablero, int letra1, int num1, int letra2, int num2, int contador){
	//Jugador 1
	if (contador==1) {
		//Jugada no corresponde a una pieza del J1.
		if(tablero[letra1*8+num1]-'a'<-32 || tablero[letra1*8+num1]-'a'>-7){
			printf("Jugada invalida. ");
			if(tablero[letra1*8+num1]-'a'==-65){
				printf("No hay pieza en dicha posicion.\n");
			}
			else{
				printf("No puedes mover una pieza del Jugador 2.\n");
			}
			return 0;
		}
		//P - Peon J1
		if(tablero[letra1*8+num1]-'a'==-17){
			if(letra2-letra1==1){//Se mueve hacia abajo
				if(num1-num2==0){//Al frente
					if(tablero[letra2*8+num2]-'a'<=-7 && tablero[letra2*8+num2]-'a'>=-32){//Pieza jugador 1
						printf("Jugada invalida. Hay una pieza tuya en dicha posicion.\n");
						return 0;
					}else if(tablero[letra2*8+num2]-'a'<=25 && tablero[letra2*8+num2]-'a'>=0){//Pieza jugador 2
						printf("Jugada invalida. Hay una pieza del Jugador 2 en dicha posicion.\n");
						return 0;
					}else{//Jugada valida. ==-65
						return 1;
					}
				}else if(num1-num2==1){//Diagonal Izq
					if(tablero[letra2*8+num2]-'a'<=25 && tablero[letra2*8+num2]-'a'>=0){
						return 1;
					}else{
						printf("Jugada invalida. Movimiento no permitido\n");
						return 0;
					}
				}else if(num1-num2==-1){//Diagonal Der
					if(tablero[letra2*8+num2]-'a'<=25 && tablero[letra2*8+num2]-'a'>=0){
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
		//--------------------------------------------------
		//T - Torre
		else if(tablero[letra1*8+num1]-'a'==-13){
			return torre(tablero,letra1,num1,letra2,num2,1,1);
		}
		//C - Caballo
		else if(tablero[letra1*8+num1]-'a'==-30){
			return caballo(tablero,letra1,num1,letra2,num2,1,1);
		}
		//A - Alfil
		else if(tablero[letra1*8+num1]-'a'==-32){
			return alfil(tablero,letra1,num1,letra2,num2,1,1);
		}
		//R - Rey
		else if(tablero[letra1*8+num1]-'a'==-15){
			return rey(tablero,letra1,num1,letra2,num2,1,1);
		}
		//Q - Queen
		else if(tablero[letra1*8+num1]-'a'==-16){
			return queen(tablero,letra1,num1,letra2,num2,1,1);
		}
	}//end Jugador 1
	//Jugador 2
	else {
		//Jugada no corresponde a una pieza del J2.
		if(tablero[letra1*8+num1]-'a'<0 || tablero[letra1*8+num1]-'a'>25){
			printf("Jugada invalida. ");
			if(tablero[letra1*8+num1]-'a'==-65){
				printf("No hay pieza en dicha posicion.\n");
			}
			else{
				printf("No puedes mover una pieza del Jugador 1.\n");
			}
			return 0;
		}
		//p - Peon J2
		if(tablero[letra1*8+num1]-'a'==15){
			if(letra2-letra1==-1){//Se mueve hacia arriba
				if(num1-num2==0){//Al frente
					if(tablero[letra2*8+num2]-'a'<=25 && tablero[letra2*8+num2]-'a'>=0){//Pieza jugador 1
						printf("Jugada invalida. Hay una pieza tuya en dicha posicion.\n");
						return 0;
					}else if(tablero[letra2*8+num2]-'a'<=-7 && tablero[letra2*8+num2]-'a'>=-32){//Pieza jugador 2
						printf("Jugada invalida. Hay una pieza del Jugador 1 en dicha posicion.\n");
						return 0;
					}else{//Jugada valida. ==-65
						return 1;
					}
				}else if(num1-num2==1){//Diagonal Izq
					if(tablero[letra2*8+num2]-'a'<=-7 && tablero[letra2*8+num2]-'a'>=-32){
						return 1;
					}else{
						printf("Jugada invalida. Movimiento no permitido\n");
						return 0;
					}
				}else if(num1-num2==-1){//Diagonal Der
					if(tablero[letra2*8+num2]-'a'<=-7 && tablero[letra2*8+num2]-'a'>=-32){
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
		//--------------------------------------------------
		//t - Torre
		else if(tablero[letra1*8+num1]-'a'==19){
			return torre(tablero,letra1,num1,letra2,num2,2,1);
		}
		//c - Caballo
		else if(tablero[letra1*8+num1]-'a'==2){
			return caballo(tablero,letra1,num1,letra2,num2,2,1);
		}
		//a - Alfil
		else if(tablero[letra1*8+num1]-'a'==0){
			return alfil(tablero,letra1,num1,letra2,num2,2,1);
		}
		//r - Rey
		else if(tablero[letra1*8+num1]-'a'==17){
			return rey(tablero,letra1,num1,letra2,num2,2,1);
		}
		//q - Queen
		else if(tablero[letra1*8+num1]-'a'==16){
			return queen(tablero,letra1,num1,letra2,num2,2,1);
		}
	}
	printf("No debería aparecer este mensaje\n");
	return 1;
}//end verificar

void mover(char *tablero, int letra1, int num1, int letra2, int num2) {
	char c, pieza[50];
	int k=1;

	tablero[letra2*8+num2] = tablero[letra1*8+num1];
	if(tablero[letra2*8+num2]-'a'==-17 && letra2==7){//Peon J1 llega al otro lado
		printf("Peon tuyo llegó al otro extremo del tablero, eliga una pieza (t,c,a,q): ");
		while(k){
			fgets(pieza,sizeof(pieza),stdin);
			sscanf(pieza,"%c",&c);
			while(strlen(pieza)>2){
				printf("Ingrese una pieza valida (t,c,a,q): ");
				fgets(pieza,sizeof(pieza),stdin);
				sscanf(pieza,"%c",&c);
			}
			if(toupper(c)-'a'==-13){//T - Torre
				tablero[letra2*8+num2]='T';
				k=0;
			}
			else if(toupper(c)-'a'==-30){//C - Caballo
				tablero[letra2*8+num2]='C';
				k=0;
			}
			else if(toupper(c)-'a'==-32){//A - Alfil
				tablero[letra2*8+num2]='A';
				k=0;
			}
			else if(toupper(c)-'a'==-16){//Q - Queen
				tablero[letra2*8+num2]='Q';
				k=0;
			}
			else{
				printf("Ingrese una pieza valida (t,c,a,q): ");
			}
		}//end while
	}
	else if(tablero[letra2*8+num2]-'a'==15 && letra2==0){//Peon J2 llega al otro lado
		printf("Peon tuyo llegó al otro extremo del tablero, eliga una pieza (t,c,a,q): ");
		while(k){
			fgets(pieza,sizeof(pieza),stdin);
			sscanf(pieza,"%c",&c);
			while(strlen(pieza)>2){
				printf("Ingrese una pieza valida (t,c,a,q): ");
				fgets(pieza,sizeof(pieza),stdin);
				sscanf(pieza,"%c",&c);
			}
			if(toupper(c)-'a'==-13){//T - Torre
				tablero[letra2*8+num2]='t';
				k=0;
			}
			else if(toupper(c)-'a'==-30){//C - Caballo
				tablero[letra2*8+num2]='c';
				k=0;
			}
			else if(toupper(c)-'a'==-32){//A - Alfil
				tablero[letra2*8+num2]='a';
				k=0;
			}
			else if(toupper(c)-'a'==-16){//Q - Queen
				tablero[letra2*8+num2]='q';
				k=0;
			}
			else{
				printf("Ingrese una pieza valida (t,c,a,q): ");
			}
		}
	}
	tablero[letra1*8+num1] = ' ';
}

int jaqueMate() {
	//
	return 0;
}

int checkJaque(char *tablero, int contador){
	int i,j,king;
	int letra, num;

	if (contador==1){//J1
		//rival
		max=25;
		min=0;

		king=-15;
	}
	else{//J2
		//rival
		max=-7;
		min=-32;

		king=17;
	}

	for(i=0;i<8;i++){//Encontrar posición Rey
		for(j=0;j<8;j++){
			if(tablero[i*8+j]-'a'==king){
				letra=i;
				num=j;
				//break;
			}
		}
	}//end for

	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(tablero[i*8+j]-'a'>=min && tablero[i*8+j]-'a'<=max){//Es pieza rival
				//P - Peon J1
				if(tablero[i*8+j]-'a'==-17){
					if(letra-i==1){//Se mueve hacia abajo
						if(num-j==0){//Al frente
							if(tablero[letra*8+num]-'a'<=-7 && tablero[letra*8+num]-'a'>=-32){//Pieza jugador 1
								//
							}else if(tablero[letra*8+num]-'a'<=25 && tablero[letra*8+num]-'a'>=0){//Pieza jugador 2
								//
							}else{//Jugada valida. ==-65
								return 1;
							}
						}else if(j-num==1){//Diagonal Izq
							if(tablero[letra*8+num]-'a'<=25 && tablero[letra*8+num]-'a'>=0){
								return 1;
							}else{
								//
							}
						}else if(j-num==-1){//Diagonal Der
							if(tablero[letra*8+num]-'a'<=25 && tablero[letra*8+num]-'a'>=0){
								return 1;
							}else{
								//
							}
						}
					}//end if hacia adelante
					//
				}//end Peon
				//T - Torre
				else if(tablero[i*8+j]-'a'==-13){
					if(torre(tablero,i,j,letra,num,1,0)==1){
						return 1;
					}
				}
				//C - Caballo
				else if(tablero[i*8+j]-'a'==-30){
					if(caballo(tablero,i,j,letra,num,1,0)==1){
						return 1;
					}
				}
				//A - Alfil
				else if(tablero[i*8+j]-'a'==-32){
					if(alfil(tablero,i,j,letra,num,1,0)==1){
						return 1;
					}
				}
				//R - Rey
				else if(tablero[i*8+j]-'a'==-15){
					if(rey(tablero,i,j,letra,num,1,0)==1){
						return 1;
					}
				}
				//Q - Queen
				else if(tablero[i*8+j]-'a'==-16){
					if(queen(tablero,i,j,letra,num,1,0)==1){
						return 1;
					}
				}
				//--------------------------------------------------
				//p - Peon J2
				else if(tablero[i*8+j]-'a'==15){
					if(letra-i==-1){//Se mueve hacia arriba
						if(j-num==0){//Al frente
							if(tablero[letra*8+num]-'a'<=25 && tablero[letra*8+num]-'a'>=0){//Pieza jugador 1
								//
							}else if(tablero[letra*8+num]-'a'<=-7 && tablero[letra*8+num]-'a'>=-32){//Pieza jugador 2
								//
							}else{//Jugada valida. ==-65
								return 1;
							}
						}else if(j-num==1){//Diagonal Izq
							if(tablero[letra*8+num]-'a'<=-7 && tablero[letra*8+num]-'a'>=-32){
								return 1;
							}else{
								//
							}
						}else if(j-num==-1){//Diagonal Der
							if(tablero[letra*8+num]-'a'<=-7 && tablero[letra*8+num]-'a'>=-32){
								return 1;
							}else{
								//
							}
						}
					}//end if hacia adelante
					return 0;
				}//end Peon
				//t - Torre
				else if(tablero[i*8+j]-'a'==19){
					if(torre(tablero,i,j,letra,num,2,0)==1){
						return 1;
					}
				}
				//c - Caballo
				else if(tablero[i*8+j]-'a'==2){
					if(caballo(tablero,i,j,letra,num,2,0)==1){
						return 1;
					}
				}
				//a - Alfil
				else if(tablero[i*8+j]-'a'==0){
					if(alfil(tablero,i,j,letra,num,2,0)==1){
						return 1;
					}
				}
				//r - Rey
				else if(tablero[i*8+j]-'a'==17){
					if(rey(tablero,i,j,letra,num,2,0)==1){
						return 1;
					}
				}
				//q - Queen
				else if(tablero[i*8+j]-'a'==16){
					if(queen(tablero,i,j,letra,num,2,0)==1){
						return 1;
					}
				}
			}//end if grande
		}
	}//end for grande

	return 0;
}//end checkJaque

/*-----------------------------Funciones------------------------------*/
/*-------------------------------Main---------------------------------*/
int main(){
	int letra1, num1;
	int letra2, num2;
	int contador=1, ver;
	int pipePadre[2], pipeHijo[2], id, jake = 0;
	char leer[15];

	char *tablero = mmap(NULL, sizeof(char)*66, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);		//tablero de ajedrez

	pipe(pipePadre);
	pipe(pipeHijo);

	iniciar(tablero);

	id = fork();
	if (id > 0){			//id Padre = 1 ; id Hijo = 0
		id = 1;
	}

	while (!jaqueMate()){
		if(contador==id){//ZC
			imprimirTablero(tablero,contador);//Imprime tablero.

			jake = checkJaque(tablero,contador);

			if(jake){
				printf("Tu Rey se encuentra en Jaque\n");
			}
			jugada(&letra1,&num1,&letra2,&num2);//Ve si el input corresponde a la lógica del juego.
			ver = verificar(tablero,letra1,num1,letra2,num2,contador);//Valida el movimiento del jugador.
			if(ver && jake){
				mover(tablero,letra1,num1,letra2,num2);
				jake = checkJaque(tablero,contador);
				mover(tablero,letra2,num2,letra1,num1);
			}

			while(!ver || jake){
				if(jake){
					printf("Jugada invalida, tu Rey sigue en Jaque\n");
				}
				jugada(&letra1,&num1,&letra2,&num2);//Ve si el input corresponde a la lógica del juego.
				ver = verificar(tablero, letra1,num1,letra2,num2,contador);//Valida el movimiento del jugador.
				if(ver && jake){
					mover(tablero,letra1,num1,letra2,num2);
					jake = checkJaque(tablero,contador);
					mover(tablero,letra2,num2,letra1,num1);
				}
			}//end while

			mover(tablero,letra1,num1,letra2,num2);//Una vez verificado el movimiento, se procede a mover la pieza.

			if(id==1){//Padre
				close(pipePadre[0]);
				write(pipePadre[1],"0",(strlen("0")+1));
			}
			else{//Hijo
				close(pipeHijo[0]);
				write(pipeHijo[1],"1",(strlen("1")+1));
			}
		}//end ZC

		if(id==1){
			close(pipeHijo[1]);
			read(pipeHijo[0],leer,sizeof(leer));
			contador=atoi(leer);
		}
		else{
			close(pipePadre[1]);
			read(pipePadre[0],leer,sizeof(leer));
			contador=atoi(leer);
		}

	}

	wait(NULL);
	munmap(tablero, sizeof(char)*66);
	return 0;
}
/*-------------------------------Main---------------------------------*/
