#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char comando[100];//comando de entrada
    char parametro1[100] = " ";//tamaña del disco
    char parametro2[100] = " ";//unidades del tamaño
    char parametro3[100] = " ";//direccion donde se crea el archivo que simula el disco
    char parametro4[100] = " ";//nombre del disco
    int salida = 1;//Permanecia en el sistema; 0 = salir, 1 = dentro
    int aceptar = 1;//aceptacion del analizador de comando

    while (salida != 0) {
        printf("**************** PROYECTO MANEJO E IMPLEMENTACION DE ARCHIVOS**************** \n");
        printf("Ingrese el comando:\n");
        limpiar(comando);
        //gets(comando);
        fgets(comando, 100, stdin);
        //printf("Comando escrito: %s\n", comando);
        strcat(comando, " ");
        Todo_a_Mayusculas(comando); //Se convirte todo a mayusculas porque no se distingue entre mayusculas y minisculas
        //printf("Convertido: %s\n", comando);

        int i = 0;
        int fin = 1;
        int estado = 0;
        while (fin != 0) {//inicio del while1
            switch (estado) {
                case 0://Mkdisk
                    if (comando[i] == 'M' && comando[i + 1] == 'K' && comando[i + 2] == 'D' && comando[i + 3] == 'I' && comando[i + 4] == 'S' && comando[i + 5] == 'K') {
                        //printf("Comando Mkdisk\n");
                        estado = 1;
                        i = i + 6;
                        limpiar(parametro1);
                        limpiar(parametro2);
                        limpiar(parametro3);
                        limpiar(parametro4);
                        aceptar = 1;
                    } else if (comando[i] == 'S' && comando[i + 1] == 'A' && comando[i + 2] == 'L' && comando[i + 3] == 'I' && comando[i + 4] == 'R') {
                        //printf("Comando Salir\n");
                        estado = 10;
                    } else {
                        estado = 11;
                    }
                    break;
                case 1:
                    if (comando[i] == ' ') {
                        estado = 1;
                        i++;
                    }else if (comando[i] == '\\') {
                        estado = 1;
                        i++;
                    } else if (comando[i] == '-' && comando[i + 1] == 'S' && comando[i + 2] == 'I' && comando[i + 3] == 'Z' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando Mkdisk -size::\n");
                        estado = 1;
                        i = i + 7;
                        int contador = 0;
                        while (comando[i] != ' ') {
                            if (comando[i] == '-') {
                                break;
                            }
                            parametro1[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '+' && comando[i + 1] == 'U' && comando[i + 2] == 'N' && comando[i + 3] == 'I' && comando[i + 4] == 'T' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando Mkdisk +Unit::\n");
                        estado = 1;
                        i = i + 7;
                        int contador = 0;
                        while (comando[i] != ' ') {
                            if (comando[i] == '-') {
                                break;
                            }
                            parametro2[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '-' && comando[i + 1] == 'P' && comando[i + 2] == 'A' && comando[i + 3] == 'T' && comando[i + 4] == 'H' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando Mkdisk -path::\n");
                        estado = 1;
                        i = i + 7;
                        if (comando[i] == '"') {
                            i++;
                            int contador = 0;
                            while (comando[i] != '-') {
                                if (comando[i] == '"') {
                                    i++;
                                    break;
                                }
                                parametro3[contador] = comando[i];
                                contador++;
                                i++;
                            }
                        } else {
                            estado = 11; //Estado de error
                        }
                    } else if (comando[i] == '-' && comando[i + 1] == 'N' && comando[i + 2] == 'A' && comando[i + 3] == 'M' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando Mkdisk -name::\n");
                        estado = 1;
                        i = i + 7;
                        if (comando[i] == '"') {
                            i++;
                            int contador = 0;
                            while (comando[i] != '-') {
                                if (comando[i] == '"') {
                                    i++;
                                    if(parametro4[contador - 4] == '.' && parametro4[contador - 3] == 'D' && parametro4[contador - 2] == 'S' && parametro4[contador - 1] == 'K'){
                                        break;
                                    }else{
                                        printf("Comando invalido debe de escribir el nombre del disco con extension .dsk.\n");
                                        parametro4[0] = ' ';
                                        break;
                                    }
                                }
                                parametro4[contador] = comando[i];
                                contador++;
                                i++;
                            }
                        } else {
                            estado = 11; //Estado de error
                        }
                    } else {
                        if (parametro1[0] == ' ') {// == 'N' && parametro1[1] == 'a' && parametro1[2] == 'd' && parametro1[3] == 'a'){
                            printf("Comando invalido debe de escribir el tamaño del disco.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (parametro2[0] == ' ') {// == 'N' && parametro2[1] == 'a' && parametro2[2] == 'd' && parametro2[3] == 'a'){
                            printf("No se especifico la unidad de tamaño, el disco se creara en Megabytes.\n");
                            parametro2[0] = 'M';
                        }
                        if (parametro3[0] == ' ') {// == 'N' && parametro3[1] == 'a' && parametro3[2] == 'd' && parametro3[3] == 'a'){
                            printf("Comando invalido debe de escribir el path de almacenamiento del disco.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (parametro4[0] == ' ') {// == 'N' && parametro4[1] == 'a' && parametro4[2] == 'd' && parametro4[3] == 'a'){
                            printf("Comando invalido debe de escribir el nombre del disco.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (aceptar == 1) {
                            printf("Paramentro 1: %s\n", parametro1);
                            printf("Paramentro 2: %s\n", parametro2);
                            printf("Paramentro 3: %s\n", parametro3);
                            printf("Paramentro 4: %s\n", parametro4);
                            //llamar al metodo para crear el disco
                            fin = 0;
                        }
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

void Todo_a_Mayusculas(char a_mayusculas[]) {
    int i = 0;
    int desp = 'a' - 'A';
    for (i = 0; a_mayusculas[i] != '\0'; ++i) {
        if (a_mayusculas[i] >= 'a' && a_mayusculas[i] <= 'z') {
            a_mayusculas[i] = a_mayusculas[i] - desp;
        }
    }
}

void limpiar(char a_limpiar[]){
    int i = 0;
    for(i = 0; i < strlen(a_limpiar); i++){
        a_limpiar[i] = ' ';
    }
}
