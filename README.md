# Aplicacion de banco

Descripción breve del proyecto a realizar (2-3 frases).

## Integrantes del equipo

Covadonga González González ()
Carlota Stocks Galván ()
Sonia Somolinos Bravo ()


## Objetivos del trabajo

Lista de los objetivos que se persiguen con el trabajo propuesto.

##Codigo del trabajo
#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int opcionusuario;
	char usuario[100], contrasena[100];
	int opcionmenu;

	printf("1. Registro\n");
	printf("2. Iniciar sesion\n");
	scanf("%i", &opcionusuario);
	    
	switch(opcionusuario){
		case 1:
			printf("Teclee un nombre de USUARIO:\n");
			gets(usuario);
			printf("Teclee la CONTRASENA:\n");
			gets(contrasena);
			printf("Vuelva a introducir la contrasena:\n");
			
			break;
		
		case 2:
			printf("Introduzca el nombre de USUARIO:");
			gets(usuario);
			printf("Introduzca la CONTRASENA:\n");
			gets(contrasena);
			break;
		
		default: 
    		printf("Opcion no valida\n");
    		break;
	}

	system("cls");
	
	printf("BIENVENIDO AL BANCO\n");
	printf("\n");
	
	do{
		printf("Introduzca una opcion\n");
		printf("\n");
		printf("1.Saldo actual.\n");
		printf("2.Resumen de movimientos.\n");
		printf("3.Transferencias/Bizum.\n");
		printf("4.Cerrar sesion.\n");
		scanf("%i", &opcionmenu);
		
		switch(opcionmenu){
			case 1:
				printf("Su saldo actual es:\n");
				system("cls");
				break;
			case 2:
				printf("Movimientos:\n");
				system("cls");
				break;
			case 3:
				printf("Transferencias/bizum\n");
				system("cls");
				break;
			case 4:
				printf("Cerrar sesion");
				break;
			default:
				system("cls");
				printf("Opcion no valida\n");
		}
	}while(opcionmenu!=4);
}
