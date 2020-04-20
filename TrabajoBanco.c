#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct TAcliente{
	char usuario[50];
	char nombre[50];
	char apellidos[100];
	int dni;
	char contrasena[40];
};

int main(){
	
	FILE*pfichero;
	int opcionusuario;
    struct TAcliente cuenta[200];
	int opcionmenu, encontradoU=0, encontradoC=0;
	int contador=0; // numero de clientes
	char user[50], pass[40];

	printf("1. Registro\n");
	printf("2. Iniciar sesion\n");
	scanf("%d", &opcionusuario);
	
	system("cls");
	    
	switch(opcionusuario){
		case 1:
			fflush(stdin);
			printf("Teclee su nombre de USUARIO:\n");
			gets(cuenta[contador].usuario);
			printf("Teclee su NOMBRE:\n");
			gets(cuenta[contador].nombre);
			printf("Teclee sus APELLIDOS:\n");
			gets(cuenta[contador].apellidos);
			printf("Teclee su DNI:\n");
			scanf("%d", &cuenta[contador].dni);
			fflush(stdin);
			printf("Teclee una CLAVE:\n");
			gets(cuenta[contador].contrasena);
			
			pfichero = fopen("clientes.txt","w");
			if(pfichero==NULL){
				printf("Error al abrir el fichero\n");
				return 0;	
			}
		    else{
				fprintf(pfichero,"%s %s\n", cuenta[contador].usuario, cuenta[contador].contrasena); 
				contador++;	
			}	
			fclose(pfichero);
			
			break;
		
		case 2:
			pfichero = fopen("clientes.txt", "r");
			if(pfichero == NULL){
				printf("No se ha podido abrir el fichero\n");
				return 0;
			}
			
			while(fscanf(pfichero, "%s %s", cuenta[contador].usuario, cuenta[contador].contrasena) != EOF){
			
			}
			
			fflush(stdin);
			printf("Introduzca el nombre de USUARIO:");
			gets(user);
			encontradoU=strcmp(user, cuenta[contador].usuario);
			if(encontradoU==0){
				fflush(stdin);
				printf("Introduzca la CONTRASENA:\n");
				gets(pass);
				encontradoC=strcmp(pass, cuenta[contador].contrasena);
				if(encontradoC==0){
					
				} else{
					printf("Contraseña incorrecta\n");
				}
			} else{
				printf("Usuario no existe\n");
				break;
			}
			
			fclose(pfichero);
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
				system("cls");
				break;
			default:
				printf("Opcion no valida\n");
		}
	}while(opcionmenu!=4);
}


