#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <Windows.h>


struct TAcliente{
	char usuario[50];
	char nombre[50];
	char apellidos[100];
	int Ndni;
	char Ldni;
	int pin;
	float dinero;
};


int menu();
int Contar(int n); // funcion para comprobar el tamaño del PIN y del DNI


int main(){
	
	FILE*pfichero;
	
	int opcionusuario;
    struct TAcliente cuenta[200];
	int opcionmenu;
	int encontradoU=0, encontradoC=0; // inicio sesion
	int contador=0, i=0, n=0, j=0; // numero de clientes
	char user[50]; 
	int pass;
	int correct=0, dni0=0, t, f; // comprobar pin y dni
	float dinerosum = 0;
	int Uexistente=1;
	float dineroT=0;
	char transferencia[50];
	int k, v=0; // para realizar transferencia
	int encontradoT=1;
	int intentos=0; // maximo de 3 intentos para iniciar sesion
	int CambioPin, PinNuevo, NuevoPin, CPin; // cambio pin
	
	
	system("color 6");
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
				
				n=0;
				while(fscanf(pfichero, "%s %d %f", cuenta[n].usuario, &cuenta[n].pin, &cuenta[n].dinero) != EOF){
					Uexistente=strcmp(cuenta[n].usuario, cuenta[j].usuario);
					if(Uexistente==0){
						printf("El nombre de usuario ya existe\n");
						return 0;
					}
					n++;
				}
	
			}while(Uexistente==0);
			
			printf("Teclee su NOMBRE:\n");
			gets(cuenta[contador].nombre);
			printf("Teclee sus APELLIDOS:\n");
			gets(cuenta[contador].apellidos);
			
			do{
				fflush(stdin);
				printf("Teclee su DNI:\n");
				scanf("%d%c", &cuenta[contador].Ndni, &cuenta[contador].Ldni);
				
				correct=Contar(cuenta[contador].Ndni);
				
				if(correct!=8){
					printf("Su codigo DNI ha sido mal introducido.\n");
				}else if(cuenta[contador].Ldni>'Z' || cuenta[contador].Ldni<'A'){
					printf("La letra del dni ha sido mal introducida.\n");
				}
			
			}while(correct!=8 || cuenta[contador].Ldni>'Z' || cuenta[contador].Ldni<'A');
			
			do{
				printf("Teclee una PIN de 4 digitos:\n");
				scanf("%d", &cuenta[contador].pin);
				
				correct=Contar(cuenta[contador].pin);
				
				if(correct!=4){
					printf("PIN no valido.\n");
				}
				
			}while(correct!=4);
			
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
				fprintf(pfichero,"%s %d %.2f\n", cuenta[n].usuario, cuenta[n].pin, cuenta[n].dinero); 
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
			
			fflush(stdin);
			do{
				printf("Introduzca el nombre de USUARIO:\n");
				gets(user);
				printf("Buscanco usuario...\n");
				Sleep(1000);
				for(n=0; n<contador; n++){
					encontradoU=strcmp(user, cuenta[n].usuario);
					if(encontradoU==0)
						break;
				}
				if(encontradoU==0){
					intentos=0;
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
							intentos++;
							if(intentos==3){
								return 0;
							}
						}
					}while(encontradoC==1);				
				} else{
					printf("Usuario no existe\n");
					Sleep(1000);
					intentos++;
					if(intentos==3){
						printf("Pruebe a registrarse\n");
						Sleep(1000);
						return 0;
					}
					system("cls");
				}
			}while(encontradoU!=0);	
			
			fclose(pfichero);
			break;
		
		default: 
    		printf("Opcion no valida\n");
    		break;
	}

	system("cls");
	printf("\n");
	printf("\n"); 
	printf("\n");
	printf("\n");
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
				pfichero = fopen("clientes.txt", "r");
				if(pfichero == NULL){
					printf("No se ha podido abrir el fichero\n");
					return -1;
				}
				
				printf("Estos son los usuarios del banco\n");
				i=0;		
				while(fscanf(pfichero, "%s %d %f", cuenta[i].usuario, &cuenta[i].pin, &cuenta[i].dinero) != EOF){
					printf("%s\n", cuenta[i].usuario);
					i++;
				}
					
				do{
					fflush(stdin);
					
					printf("Introduzca el nombre de USUARIO al que desea realizar una tranferencia:\n");			
					gets(transferencia);
					for(k=0; k<contador; k++){
						encontradoT=strcmp(transferencia, cuenta[k].usuario);
						if(encontradoT==0)
							break;
					}
					if(encontradoT==0){
						do{
							printf("Introduzca la cantidad de dinero que desea ingresar a %s:\n", cuenta[k].usuario);
							scanf("%f", &dineroT);	
							if(dineroT>cuenta[n].dinero){
								printf("No dispone de tanto dinero en la cuenta, no se puede realizar la tranferencia\n");
							}else{
								v=1;
							}
						}while(dineroT>cuenta[n].dinero);			
					} else{
						printf("Usuario no existe\n");
					}	
				}while(encontradoT!=0);
				
				if(v==1){
					cuenta[n].dinero=cuenta[n].dinero-dineroT;
					cuenta[k].dinero=cuenta[k].dinero+dineroT;
				}
				
				fclose(pfichero);
				
				system("cls");
				printf("\n");
			    printf("\n"); 
			    printf("\n");
			    printf("\n");
				printf("Estamos realizando su tranferencia...\n");
				Sleep(1000);
				printf("Su saldo actual es: %.2f\n", cuenta[n].dinero);
				Sleep(1000);
				
				system("cls");
				break;
			case 3:
				printf("Prestamos:\n");
		        printf("Introduzca la cantidad de dinero que desea recibir en su cuenta: \n");
		        scanf("%f", &dinerosum);
		        cuenta[n].dinero += dinerosum;
		        printf("Un momento por favor\n");
				Sleep(1000);
		        printf("Su saldo actual es: %.2f\n", cuenta[n].dinero);
		        Sleep(1000);
			    system("cls");
				break;
			case 4:
				intentos=0;
				do{
					printf("Introduzca su PIN actual\n");
					scanf("%d", &CambioPin);
					
					CPin=cuenta[n].pin;
					
					if(CambioPin==cuenta[n].pin){
						printf("Introduzca su nuevo PIN\n");
						scanf("%d", &PinNuevo);
						printf("Vuelva a introducir su PIN\n");
						scanf("%d", &NuevoPin);
						if(PinNuevo==NuevoPin){
							printf("Su PIN ha sido correctamente actualizado\n");
							cuenta[n].pin=PinNuevo;
							Sleep(1000);
							break;
						} else{
							printf("No coinciden los codigos introducidos\n");
							printf("Vuelva a empezar el proceso\n");
							Sleep(1000);
							system("cls");
						}
					}else{
						printf("PIN incorrecto\n");
						intentos++;
						Sleep(1000);
						if(intentos==3){
							printf("Usted ha sobrepasado el numero de intentos\n");
							printf("Por la seguridad de nuestros usuarios, esta sesion se cerrara automaticamente\n");
							Sleep(3000);
							return 0;
						}
					}
				}while(CambioPin!=CPin);
				
				system("cls");
				break;
			case 5:
				
				break;
			default:
				printf("Opcion no valida\n");
				Sleep(1000);
			    system("cls");
			}
			
	}while(opcionmenu!=5);
	
	system("cls");
	printf("\n");
    printf("\n"); 
    printf("\n");
    printf("\n"); 
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                                  HASTA PRONTO %s \n", cuenta[n].usuario);
	printf("------------------------------------------------------------------------------------------------------------------------\n");


	// copiamos los usuarios en el fichero
	pfichero = fopen("clientes.txt","w");
	if(pfichero==NULL){
		printf("Error al abrir el fichero\n");
		return -1;	
	}
	
	n=0;
	while(n<contador){
		fprintf(pfichero,"%s %d %.2f\n", cuenta[n].usuario, cuenta[n].pin, cuenta[n].dinero);
		n++; 
	}
	
	fclose(pfichero);
}


int Contar(int n){
	int pin2=0;
	
	while(n>0){
		pin2++;
		n=n/10;	
	}

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
	printf("                                                      4.Cambiar PIN.\n");
	printf("                                                      5.Cerrar sesion.\n");
	fflush(stdin);
	scanf("%i", &opcion);
	return opcion;
}

