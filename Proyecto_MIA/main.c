#include <stdio.h>
#include <stdlib.h>

int main() {
    char comando[100];
    char parametro1[20];
    char parametro2[20];
    char parametro3[20];
    char parametro4[20];
    int salida = 1;
    while (salida != 0) {
        printf("**************** PROYECTO MANEJO E IMPLEMENTACION DE ARCHIVOS**************** \n");
        printf("Ingrese el comando:\n");
        fflush(stdin);
        fgets(comando, 100, stdin);
        //scanf("%s",&comando);
        printf("Comando escrito: %s\n", comando);

        Todo_a_Mayusculas(comando); //Se convirte todo a mayusculas porque no se distingue entre mayusculas y minisculas
        printf("Convertido: %s\n", comando);

        int i = 0;
        int fin = 1;
        int estado = 0;
        while (fin != 0) {//inicio del while1
            switch (estado) {
                case 0://Mkdisk
                    if (comando[i] == 'M' && comando[i + 1] == 'K' && comando[i + 2] == 'D' && comando[i + 3] == 'I' && comando[i + 4] == 'S' && comando[i + 5] == 'K') {
                        printf("Comando Mkdisk\n");
                        estado = 1;
                        i = i + 6;
                    } else if (comando[i] == 'S' && comando[i + 1] == 'A' && comando[i + 2] == 'L' && comando[i + 3] == 'I' && comando[i + 4] == 'R') {
                        printf("Comando Salir\n");
                        estado = 10;
                    }else{
                        estado = 11;
                    }
                    break;
                case 1:
                    if(comando[i] == ' '){
                        estado = 1;
                        i++;
                    }else if (comando[i] == '-' && comando[i + 1] == 'S' && comando[i + 2] == 'I' && comando[i + 3] == 'Z' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        printf("Comando Mkdisk -size::\n");
                        estado = 1;
                        i = i + 7;
                        if(comando[i] == ' '){
                            i++;
                        }
                        int contador = 0;
                        while(comando[i] != ' '){
                            if(comando[i] == '-'){
                                break;
                            }
                            parametro1[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    }else if (comando[i] == '+' && comando[i + 1] == 'U' && comando[i + 2] == 'N' && comando[i + 3] == 'I' && comando[i + 4] == 'T' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        printf("Comando Mkdisk +Unit::\n");
                        estado = 1;
                        i = i + 7;
                        if(comando[i] == ' '){
                            i++;
                        }
                        int contador = 0;
                        while(comando[i] != ' '){
                            if(comando[i] == '-'){
                                break;
                            }
                            parametro2[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    }else if (comando[i] == '-' && comando[i + 1] == 'P' && comando[i + 2] == 'A' && comando[i + 3] == 'T' && comando[i + 4] == 'H' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        printf("Comando Mkdisk -path::\n");
                        estado = 1;
                        i = i + 7;
                        if(comando[i] == ' '){
                            i++;
                        }
                        int contador = 0;
                        while(comando[i] != ' '){
                            if(comando[i] == '-'){
                                break;
                            }
                            parametro3[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    }else if (comando[i] == '-' && comando[i + 1] == 'N' && comando[i + 2] == 'A' && comando[i + 3] == 'M' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        printf("Comando Mkdisk -name::\n");
                        estado = 1;
                        i = i + 7;
                        if(comando[i] == ' '){
                            i++;
                        }
                        int contador = 0;
                        while(comando[i] != ' '){
                            if(comando[i] == '-'){
                                break;
                            }
                            parametro4[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    }else{
                        printf("Paramentro 1: %s\n", parametro1);
                        printf("Paramentro 2: %s\n", parametro2);
                        printf("Paramentro 3: %s\n", parametro3);
                        printf("Paramentro 4: %s\n", parametro4);
                        fin = 0;
                    }
                    break;
                case 10:
                    fin = 0;
                    salida = 0;
                    break;
                case 11:
                    printf("Comando invalido\n");
                    fin = 0;
                    break;
            }
        }//fin del while1
    }

    return 0;
}

//Metodo que convierte todo a mayusculas

void Todo_a_Mayusculas(char string[]) {
    int i = 0;
    int desp = 'a' - 'A';
    for (i = 0; string[i] != '\0'; ++i) {
        if (string[i] >= 'a' && string[i] <= 'z') {
            string[i] = string[i] - desp;
        }
    }
}
