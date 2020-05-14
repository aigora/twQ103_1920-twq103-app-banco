#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include<Windows.h>


struct TAcliente{
	char usuario[50];
	char nombre[50];
	char apellidos[100];
	int dni;
	int pin;
	float dinero;
};

int menu();
int Numpin(int n); // funcion para comprobar el tamaño del PIN y del DNI

int main(){
	
	FILE*pfichero;
	
	int opcionusuario;
    struct TAcliente cuenta[200];
	int opcionmenu;
	int encontradoU=0, encontradoC=0;
	int contador=0, i=0, n=0, j=0; // numero de clientes
	char user[50]; 
	int pass;
	int correct=0; // comprobar pin y dni
	float dinerosum = 0;
	char Uexistente=1;
	
    printf("\n");
    printf("\n"); 
    printf("\n");
    printf("\n");   
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                      BANABANK\n");	
	printf("------------------------------------------------------------------------------------------------------------------------\n");	
	Sleep(3000);
	system("cls");
	
	// Miramos cuantos usuarios están registrados
	pfichero = fopen("clientes.txt", "r");
	
	if(pfichero == NULL){
		printf("No se ha podido abrir el fichero\n");
		return -1;
	}
				
	while(fscanf(pfichero, "%s %d %f", cuenta[contador].usuario, &cuenta[contador].pin, &cuenta[contador].dinero) != EOF){
		contador++;
	}
	fclose(pfichero);
	
    printf("\n");
    printf("\n"); 
    printf("\n");
    printf("\n");  
	printf("                                                      1.Registro\n");
	printf("                                                      2.Iniciar sesion\n");
	scanf("%d", &opcionusuario);
	
	system("cls");
	    
	switch(opcionusuario){
		case 1:			
			do{
				fflush(stdin);
				printf("Teclee su nombre de USUARIO:\n");
				gets(cuenta[contador].usuario);
				j=contador;
				pfichero = fopen("clientes.txt", "r");
				if(pfichero == NULL){
					printf("No se ha podido abrir el fichero\n");
					return -1;
				}
				
				for(n=0; n<contador; n++){
					while(fscanf(pfichero, "%s %d %f", cuenta[n].usuario, &cuenta[n].pin, &cuenta[n].dinero) != EOF){
						Uexistente=strcmp(cuenta[n].usuario, cuenta[j].usuario);
						if(Uexistente==0){
							printf("El nombre de usuario ya existe\n");
							return 0;
						}
					}
				}
			}while(Uexistente==0);
			
			printf("Teclee su NOMBRE:\n");
			gets(cuenta[contador].nombre);
			printf("Teclee sus APELLIDOS:\n");
			gets(cuenta[contador].apellidos);
			
			do{
				fflush(stdin);
				printf("Teclee su DNI sin letra:\n");
				scanf("%d", &cuenta[contador].dni);
				
				correct=Numpin(cuenta[contador].dni);
				
				if(correct<8){
					printf("Su codigo DNI es demasiado corto.\n");
				}
				if(correct>=9){
					printf("Su codigo DNI sobrepasa el numero de cifras admitido.\n");
				}
			
			}while(correct>=9 || correct<8);
			
			do{
				printf("Teclee una PIN de 4 digitos:\n");
				scanf("%d", &cuenta[contador].pin);
				
				correct=Numpin(cuenta[contador].pin);
				
				if(correct<4){
					printf("Su PIN es demasiado corto.\n");
				}
				if(correct>=5){
					printf("Su PIN sobrepasa el numero de cifras admitido.\n");
				}
			
			}while(correct>=5 || correct<4);
			
			printf("Usuario registrado con exito!\n");
			Sleep(1000);
			system("cls");
			
			printf("Introduzca cuanto dinero desea tener en la cuenta: \n");
			scanf("%f", &cuenta[contador].dinero);
			
			contador++;
			
			pfichero = fopen("clientes.txt","w");
			if(pfichero==NULL){
				printf("Error al abrir el fichero\n");
				return -1;	
			}
			n=0;
			while(n<contador){
				fprintf(pfichero,"%s %d %f\n", cuenta[n].usuario, cuenta[n].pin, cuenta[n].dinero); 
				n++;
			}	
			fclose(pfichero);
			n=contador-1;			
			break;
		
		case 2:
			pfichero = fopen("clientes.txt", "r");
			if(pfichero == NULL){
				printf("No se ha podido abrir el fichero\n");
				return -1;
			}
			
			do{
				fflush(stdin);
				printf("Introduzca el nombre de USUARIO:\n");
				gets(user);
				for(n=0; n<contador; n++){
					encontradoU=strcmp(user, cuenta[n].usuario);
					if(encontradoU==0)
						break;
					
				}
				if(encontradoU==0){
					do{
						printf("Introduzca el PIN:\n");
						scanf("%d", &pass);
						
						if(pass==cuenta[n].pin){
							printf("Inicio de sesion correcto!");
							Sleep(2000);
							system("cls");
							break;
						} else{							
							encontradoC=1;
							printf("PIN incorrecto\n");
						}
					}while(encontradoC==1);				
				} else{
					printf("Usuario no existe\n");
					break;
				}	
			}while(encontradoU!=0);
			
			fclose(pfichero);
			break;
		
		default: 
    		printf("Opcion no valida\n");
    		break;
	}

	system("cls");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                      BANABANK\n");	
	printf("------------------------------------------------------------------------------------------------------------------------\n");	
	printf("                                                 BIENVENID@ AL BANCO %s\n", cuenta[n].usuario);
	printf("\n");
	Sleep(2000);
	system("cls");
	
	do{
		opcionmenu = menu();
		
		switch(opcionmenu){
			case 1:
				printf("Su saldo actual es: %f\n", cuenta[n].dinero);
				Sleep(1000);
				system("cls");
				break;
			case 2:
				printf("Transferencias:\n");
				system("cls");
				break;
			case 3:
				printf("Prestamos:\n");
		        printf("Introduzca la cantidad de dinero que desea recibir en su cuenta: \n");
		        scanf("%f", &dinerosum);
		        cuenta[n].dinero += dinerosum;
		        printf("Su saldo actual es: %f\n", cuenta[n].dinero);
		        Sleep(1000);
			    system("cls");
				break;
			case 4:
				break;
			default:
				printf("Opcion no valida\n");
				Sleep(1000);
			    system("cls");
			}
			
	}while(opcionmenu!=4);
	
	// copiamos los usuarios en el fichero
	pfichero = fopen("clientes.txt","w");
	if(pfichero==NULL){
		printf("Error al abrir el fichero\n");
		return -1;	
	}
	n=0;
	while(n<contador){
		fprintf(pfichero,"%s %d %f\n", cuenta[n].usuario, cuenta[n].pin, cuenta[n].dinero);
		n++; 
	}	
	fclose(pfichero);
	
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                  HASTA PRONTO %s \n", cuenta[n].usuario);
	printf("------------------------------------------------------------------------------------------------------------------------\n");
}

int Numpin(int n){
	int pin2=0;
	
	do{
		pin2++;
		n=n/10;
	}while(n>0);
	
	return pin2;
}

int menu(){
	int opcion;
	
	printf("\n");
    printf("\n"); 
    printf("\n");
    printf("\n");  
	printf("                                                      Introduzca una opcion\n");
	printf("\n");
	printf("                                                      1.Saldo actual.\n");
	printf("                                                      2.Transferencias.\n");
	printf("                                                      3.Prestamos.\n");
	printf("                                                      4.Cerrar sesion.\n");
	fflush(stdin);
	scanf("%i", &opcion);
	return opcion;
}

