#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int main() {

//existe_path("/home/tony/Escritorio/calificacion.sh");

char comando[100]; //comando de entrada
char tamanio[100] = " "; //....................tamaña
char unidades_tamanio[100] = " "; //...........unidades del tamaño
char path[100] = " "; //.......................direccion path
char nombre[100] = " "; //.....................nombre
char tipo[100] = " "; //........................tipo de particion
char ajuste[100] = " "; //......................ajuste para la particion
char delete[100] = " "; //......................borrar parricion
char add[100] = " "; //.........................agregar espacio a la particion
char id[100] = " "; //..........................id del disco

int salida = 1; //.............................Permanecia en el sistema; 0 = salir, 1 = dentro
int aceptar = 1; //............................aceptacion del analizador de comando
int es_delete = 1; //..........................si se esta usando delete en fdisk
int es_add = 1; //.............................si se esta usando add en fdisk

int main() {
    while (salida != 0) {
        printf("**************** PROYECTO MANEJO E IMPLEMENTACION DE ARCHIVOS**************** \n");
        printf("Ingrese el comando:\n");
        limpiar(comando);
        //gets(comando);
        fgets(comando, 100, stdin);
        //printf("Comando escrito: %s\n", comando);
        strcat(comando, " ");
        //Todo_a_Mayusculas(comando); //Se convirte todo a mayusculas porque no se distingue entre mayusculas y minisculas
        //printf("Convertido: %s\n", comando);

        analizador(comando);
    }
    return 0;
}

void analizador(char a_analizar[]) {
    int i = 0;
    int fin = 1;
    int estado = 0;
    while (fin != 0) {//inicio del while1
        switch (estado) {
            case 0:
                //mkdisk
                if ((a_analizar[i] == 'm' || a_analizar[i] == 'M') && (a_analizar[i + 1] == 'k' || a_analizar[i + 1] == 'K') && (a_analizar[i + 2] == 'd' || a_analizar[i + 2] == 'D') && (a_analizar[i + 3] == 'i' || a_analizar[i + 3] == 'I') && (a_analizar[i + 4] == 's' || a_analizar[i + 4] == 'S') && (a_analizar[i + 5] == 'k' || a_analizar[i + 5] == 'K')) {
                    //printf("Comando Mkdisk\n");
                    estado = 1;
                    i = i + 6;
                    limpiar(tamanio);
                    limpiar(unidades_tamanio);
                    limpiar(path);
                    limpiar(nombre);
                    aceptar = 1;
                    //rmdisk
                } else if ((a_analizar[i] == 'r' || a_analizar[i] == 'R') && (a_analizar[i + 1] == 'm' || a_analizar[i + 1] == 'M') && (a_analizar[i + 2] == 'd' || a_analizar[i + 2] == 'D') && (a_analizar[i + 3] == 'i' || a_analizar[i + 3] == 'I') && (a_analizar[i + 4] == 's' || a_analizar[i + 4] == 'S') && (a_analizar[i + 5] == 'k' || a_analizar[i + 5] == 'K')) {
                    //printf("Comando rmdisk\n");
                    estado = 2;
                    i = i + 6;
                    limpiar(tamanio);
                    aceptar = 1;
                    //fdisk
                } else if ((a_analizar[i] == 'f' || a_analizar[i] == 'F') &&
                        (a_analizar[i + 1] == 'd' || a_analizar[i + 1] == 'D') &&
                        (a_analizar[i + 2] == 'i' || a_analizar[i + 2] == 'I') &&
                        (a_analizar[i + 3] == 's' || a_analizar[i + 3] == 'S') &&
                        (a_analizar[i + 4] == 'k' || a_analizar[i + 4] == 'K')) {
                    //printf("Comando fdisk\n");
                    estado = 3;
                    i = i + 6;
                    limpiar(tamanio);
                    limpiar(unidades_tamanio);
                    limpiar(path);
                    limpiar(nombre);
                    limpiar(tipo);
                    limpiar(ajuste);
                    limpiar(delete);
                    limpiar(add);
                    aceptar = 1;
                    es_delete = 1;
                    //mount
                } else if ((a_analizar[i] == 'm' || a_analizar[i] == 'M')&& (a_analizar[i + 1] == 'o' || a_analizar[i + 1] == 'O') && (a_analizar[i + 2] == 'u' || a_analizar[i + 2] == 'U') && (a_analizar[i + 3] == 'n' || a_analizar[i + 3] == 'N') && (a_analizar[i + 4] == 't' || a_analizar[i + 4] == 'T')) {
                    printf("Comando mount\n");
                    estado = 4;
                    i = i + 6;
                    limpiar(path);
                    limpiar(nombre);
                    aceptar = 1;
                    //ummount
                } else if ((a_analizar[i] == 'u' || a_analizar[i] == 'U') && (a_analizar[i + 1] == 'm' || a_analizar[i + 1] == 'M') && (a_analizar[i + 2] == 'o' || a_analizar[i + 2] == 'O') && (a_analizar[i + 3] == 'u' || a_analizar[i + 3] == 'U') && (a_analizar[i + 4] == 'n' || a_analizar[i + 4] == 'N') && (a_analizar[i + 5] == 't' || a_analizar[i + 5] == 'T')) {
                    printf("Comando umount\n");
                    estado = 5;
                    i = i + 6;
                    limpiar(path);
                    limpiar(nombre);
                    aceptar = 1;
                    //exec
                } else if ((a_analizar[i] == 'e' || a_analizar[i] == 'E') && (a_analizar[i + 1] == 'x' || a_analizar[i + 1] == 'X') && (a_analizar[i + 2] == 'e' || a_analizar[i + 2] == 'E') && (a_analizar[i + 3] == 'c' || a_analizar[i + 3] == 'C')) {
                    printf("Comando exec\n");
                    estado = 6;
                    i = i + 4;
                    limpiar(path);
                    aceptar = 1;
                    //salir
                } else if ((a_analizar[i] == 's' || a_analizar[i] == 'S') && (a_analizar[i + 1] == 'a' || a_analizar[i + 1] == 'A') && (a_analizar[i + 2] == 'l' || a_analizar[i + 2] == 'L') && (a_analizar[i + 3] == 'i' || a_analizar[i + 3] == 'I') && (a_analizar[i + 4] == 'r' || a_analizar[i + 4] == 'R')) {
                    //printf("Comando Salir\n");
                    estado = 10;
                    //comanetarios
                } else if (a_analizar[i] == '#') {
                    estado = 7;
                    i++;
                } else {
                    estado = 11;
                }
                break;
            case 1:
                if (a_analizar[i] == ' ' || a_analizar[i] == '\\' || a_analizar[i] == '\n') {
                    estado = 1;
                    i++;
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'S' || a_analizar[i + 1] == 's') && (a_analizar[i + 2] == 'I' || a_analizar[i + 2] == 'i') && (a_analizar[i + 3] == 'Z' || a_analizar[i + 3] == 'z') && (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando Mkdisk -size::\n");
                    estado = 1;
                    i = i + 7;
                    int contador = 0;
                    while (a_analizar[i] != ' ') {
                        if (a_analizar[i] == '-') {
                            break;
                        }
                        tamanio[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '+' && (a_analizar[i + 1] == 'U' || a_analizar[i + 1] == 'u') && (a_analizar[i + 2] == 'N' || a_analizar[i + 2] == 'n') && (a_analizar[i + 3] == 'I' || a_analizar[i + 3] == 'i') && (a_analizar[i + 4] == 'T' || a_analizar[i + 4] == 't') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando Mkdisk +Unit::\n");
                    estado = 1;
                    i = i + 7;
                    int contador = 0;
                    while (a_analizar[i] != '\0') {
                        if (a_analizar[i] == '-' || a_analizar[i] == ' ') {
                            if (unidades_tamanio[0] == 'K' || unidades_tamanio[0] == 'M' || unidades_tamanio[0] == 'k' || unidades_tamanio[0] == 'm') {
                                break;
                            } else {
                                printf("Comando invalido, las unidades de tamaño deben ser en Megabytes (M) o en kilobytes(K).\n");
                                unidades_tamanio[0] = '@';
                                break;
                            }
                        }
                        unidades_tamanio[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'P' || a_analizar[i + 1] == 'p') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'T' || a_analizar[i + 3] == 't') && (a_analizar[i + 4] == 'H' || a_analizar[i + 4] == 'h') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando Mkdisk -path::\n");
                    estado = 1;
                    i = i + 7;
                    if (a_analizar[i] == '"') {
                        i++;
                        int contador = 0;
                        while (a_analizar[i] != '-') {
                            if (a_analizar[i] == '"') {
                                i++;
                                break;
                            }
                            path[contador] = a_analizar[i];
                            contador++;
                            i++;
                        }
                    } else {
                        estado = 11; //Estado de error
                    }
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'N' || a_analizar[i + 1] == 'n') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'M' || a_analizar[i + 3] == 'm') && (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando Mkdisk -name::\n");
                    estado = 1;
                    i = i + 7;
                    if (a_analizar[i] == '"') {
                        i++;
                        int contador = 0;
                        while (a_analizar[i] != '-') {
                            if (a_analizar[i] == '"') {
                                i++;
                                if (nombre[contador - 4] == '.' && (nombre[contador - 3] == 'D' || nombre[contador - 3] == 'd') && (nombre[contador - 2] == 'S' || nombre[contador - 2] == 's') && (nombre[contador - 1] == 'K' || nombre[contador - 1] == 'k')) {
                                    break;
                                } else {
                                    printf("Comando invalido debe de escribir el nombre del disco con extension .dsk.\n");
                                    nombre[0] = ' ';
                                    break;
                                }
                            }
                            nombre[contador] = a_analizar[i];
                            contador++;
                            i++;
                        }
                    } else {
                        estado = 11; //Estado de error
                    }
                } else {
                    if (tamanio[0] == ' ') {
                        printf("Comando invalido debe de escribir el tamaño del disco.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (unidades_tamanio[0] == ' ') {
                        printf("No se especifico la unidad de tamaño, el disco se creara en Megabytes.\n");
                        unidades_tamanio[0] = 'M';
                    }
                    if (unidades_tamanio[0] == '@') {
                        fin = 0;
                        aceptar = 0;
                    }
                    if (path[0] == ' ') {
                        printf("Comando invalido debe de escribir el path de almacenamiento del disco.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (nombre[0] == ' ') {
                        printf("Comando invalido debe de escribir el nombre del disco.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (aceptar == 1) {
                        printf("Paramentro 1: %s\n", tamanio);
                        printf("Paramentro 2: %s\n", unidades_tamanio);
                        printf("Paramentro 3: %s\n", path);
                        printf("Paramentro 4: %s\n", nombre);
                        //llamar al metodo para crear el disco
                        printf("Se creo el disco %s satisfactoriamente.\n");
                        fin = 0;
                    }
                }
                break;
            case 2:
                if (a_analizar[i] == ' ' || a_analizar[i] == '\\' || a_analizar[i] == '\n') {
                    estado = 2;
                    i++;
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'P' || a_analizar[i + 1] == 'p') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'T' || a_analizar[i + 3] == 't') && (a_analizar[i + 4] == 'H' || a_analizar[i + 4] == 'h') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando rmdisk -path::\n");
                    estado = 2;
                    i = i + 7;
                    if (a_analizar[i] == '"') {
                        i++;
                        int contador = 0;
                        while (a_analizar[i] != '-') {
                            if (a_analizar[i] == '"') {
                                i++;
                                if (tamanio[contador - 4] == '.' && (tamanio[contador - 3] == 'D'||tamanio[contador - 3] == 'd') && (tamanio[contador - 2] == 'S'||tamanio[contador - 2] == 's') && (tamanio[contador - 1] == 'K'||tamanio[contador - 1] == 'k')) {
                                    break;
                                } else {
                                    printf("Comando invalido debe de escribir el nombre del disco con extension .dsk.\n");
                                    tamanio[0] = ' ';
                                    break;
                                }
                            }
                            tamanio[contador] = a_analizar[i];
                            contador++;
                            i++;
                        }
                    } else {
                        estado = 11; //Estado de error
                    }
                } else {
                    if (tamanio[0] == ' ') {
                        printf("Comando invalido debe de escribir el path de almacenamiento del disco.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (aceptar == 1) {
                        printf("Esta seguro que desea eliminar S/N\n");
                        limpiar(a_analizar);
                        fgets(a_analizar, 100, stdin);
                        strcat(a_analizar, " ");
                        Todo_a_Mayusculas(a_analizar);
                        if (a_analizar[0] == 'S') {
                            printf("Paramentro 1: %s\n", tamanio);
                            //llamar al metodo eliminar disco
                            fin = 0;
                        }
                        if (a_analizar[0] == 'N') {
                            fin = 0;
                        }
                    }
                }
                break;
            case 3:
                if (a_analizar[i] == ' ' || a_analizar[i] == '\\' || a_analizar[i] == '\n') {
                    estado = 3;
                    i++;
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'S' || a_analizar[i + 1] == 's') && (a_analizar[i + 2] == 'I' || a_analizar[i + 2] == 'i') && (a_analizar[i + 3] == 'Z' || a_analizar[i + 3] == 'z') && (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando fdisk -size::\n");
                    estado = 3;
                    i = i + 7;
                    int contador = 0;
                    while (a_analizar[i] != ' ') {
                        if (a_analizar[i] == '-') {
                            break;
                        }
                        tamanio[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '+' && (a_analizar[i + 1] == 'U' || a_analizar[i + 1] == 'u') && (a_analizar[i + 2] == 'N' || a_analizar[i + 2] == 'n') && (a_analizar[i + 3] == 'I' || a_analizar[i + 3] == 'i') && (a_analizar[i + 4] == 'T' || a_analizar[i + 4] == 't') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando fdisk +Unit::\n");
                    estado = 3;
                    i = i + 7;
                    int contador = 0;
                    while (a_analizar[i] != '\0') {
                        if (a_analizar[i] == '-' || a_analizar[i] == ' ') {
                            if (unidades_tamanio[0] == 'B' || unidades_tamanio[0] == 'K' || unidades_tamanio[0] == 'M' || unidades_tamanio[0] == 'b' || unidades_tamanio[0] == 'k' || unidades_tamanio[0] == 'm') {
                                break;
                            } else {
                                printf("Comando invalido, las unidades de tamaño deben ser en Megabytes (M) o en kilobytes(K) o en bytes(B).\n");
                                unidades_tamanio[0] = '@';
                                break;
                            }
                        }
                        unidades_tamanio[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'P' || a_analizar[i + 1] == 'p') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'T' || a_analizar[i + 3] == 't') && (a_analizar[i + 4] == 'H' || a_analizar[i + 4] == 'h') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando fdisk -path::\n");
                    estado = 3;
                    i = i + 7;
                    if (a_analizar[i] == '"') {
                        i++;
                        int contador = 0;
                        while (a_analizar[i] != '-') {
                            if (a_analizar[i] == '"') {
                                i++;
                                break;
                            }
                            path[contador] = a_analizar[i];
                            contador++;
                            i++;
                        }
                    } else {
                        estado = 11; //Estado de error
                    }
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'N' || a_analizar[i + 1] == 'n') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'M' || a_analizar[i + 3] == 'm') && (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando fdisk -name::\n");
                    estado = 3;
                    i = i + 7;
                    if (a_analizar[i] == '"') {
                        i++;
                        int contador = 0;
                        while (a_analizar[i] != '-') {
                            if (a_analizar[i] == '"') {
                                i++;
                                break;
                            }
                            nombre[contador] = a_analizar[i];
                            contador++;
                            i++;
                        }
                    } else {
                        estado = 11; //Estado de error
                    }
                } else if (a_analizar[i] == '+' && (a_analizar[i + 1] == 'T' || a_analizar[i + 1] == 't') && (a_analizar[i + 2] == 'Y' || a_analizar[i + 2] == 'y') && (a_analizar[i + 3] == 'P' || a_analizar[i + 3] == 'p') && (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando fdisk +type::\n");
                    estado = 3;
                    i = i + 7;
                    int contador = 0;
                    while (a_analizar[i] != '\0') {
                        if (a_analizar[i] == '-' || a_analizar[i] == ' ') {
                            if (tipo[0] == 'P' || tipo[0] == 'E' || tipo[0] == 'L') {
                                break;
                            } else {
                                printf("Comando invalido, los tipos de discos deben ser Primarias (P) o Extendidas (E) o Logicas (L).\n");
                                tipo[0] = '@';
                                break;
                            }
                        }
                        tipo[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '+' && (a_analizar[i + 1] == 'F' || a_analizar[i + 1] == 'f') && (a_analizar[i + 2] == 'I' || a_analizar[i + 2] == 'i') && (a_analizar[i + 3] == 'T' || a_analizar[i + 3] == 't') && a_analizar[i + 4] == ':' && a_analizar[i + 5] == ':') {
                    //printf("Comando fdisk +fit::\n");
                    estado = 3;
                    i = i + 6;
                    int contador = 0;
                    while (a_analizar[i] != '\0') {
                        if (a_analizar[i] == '-' || a_analizar[i] == ' ') {
                            if (((ajuste[0] == 'B' || ajuste[0] == 'b') && (ajuste[1] == 'F' || ajuste[1] == 'f')) || ((ajuste[0] == 'F' || ajuste[0] == 'f') && (ajuste[1] == 'F' || ajuste[1] == 'f')) || ((ajuste[0] == 'W' || ajuste[0] == 'w') && (ajuste[1] == 'F' || ajuste[1] == 'f'))) {
                                break;
                            } else {
                                printf("Comando invalido, los tipos de ajustes deben ser: Mejor Ajuste (BF) o Primer Ajuste (FF) o Pero Ajuste (WF).\n");
                                ajuste[0] = '@';
                                break;
                            }
                        }
                        ajuste[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '+' && (a_analizar[i + 1] == 'D' || a_analizar[i + 1] == 'd') && (a_analizar[i + 2] == 'E' || a_analizar[i + 2] == 'e') && (a_analizar[i + 3] == 'L' || a_analizar[i + 3] == 'l') && (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') && (a_analizar[i + 5] == 'T' || a_analizar[i + 5] == 't') && (a_analizar[i + 6] == 'E' || a_analizar[i + 6] == 'e') && a_analizar[i + 7] == ':' && a_analizar[i + 8] == ':') {
                    //printf("Comando fdisk +delete::\n");
                    estado = 3;
                    es_delete = 0;
                    i = i + 9;
                    int contador = 0;
                    while (a_analizar[i] != '\0') {
                        if (a_analizar[i] == '-' || a_analizar[i] == ' ') {
                            if (((delete[0] == 'F' || delete[0] == 'f') && (delete[1] == 'U' || delete[1] == 'u') && (delete[2] == 'L' || delete[2] == 'l') && (delete[3] == 'L' || delete[3] == 'l')) || ((delete[0] == 'F' || delete[0] == 'f') && (delete[1] == 'A' || delete[1] == 'a') && (delete[2] == 'S' || delete[2] == 's') && (delete[3] == 'T' || delete[3] == 't'))) {
                                break;
                            } else {
                                printf("Comando invalido, los tipos de eliminacion deben ser: full o fast.\n");
                                delete[0] = '@';
                                break;
                            }
                        }
                        delete[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '+' && (a_analizar[i + 1] == 'A' || a_analizar[i + 1] == 'a') && (a_analizar[i + 2] == 'D' || a_analizar[i + 2] == 'd') && (a_analizar[i + 3] == 'D' || a_analizar[i + 3] == 'd') && a_analizar[i + 4] == ':' && a_analizar[i + 5] == ':') {
                    //printf("Comando fdisk +add::\n");
                    estado = 3;
                    es_add = 0;
                    i = i + 6;
                    int contador = 0;
                    while (a_analizar[i] != '\0') {
                        if (a_analizar[i] == '-' || a_analizar[i] == ' ') {
                            break;
                        }
                        add[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else {
                    if (es_delete == 0) {
                        if (tamanio[0] != ' ') {
                            printf("Comando invalido para usar delete no se especifica un tamaño.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (unidades_tamanio[0] != ' ') {
                            printf("Comando invalido para usar delete no se especifica la unidad de tamaño.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (path[0] == ' ') {
                            printf("Comando invalido debe de escribir el path de almacenamiento donde se encuentra la particion.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (nombre[0] == ' ') {
                            printf("Comando invalido debe de escribir el nombre de la particion a eliminar.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (tipo[0] != ' ') {
                            printf("Comando invalido para usar delete no se especifica el tipo de particion.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (ajuste[0] != ' ') {
                            printf("Comando invalido para usar delete no se especifica el ajuste.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (delete[0] == '@' || delete[0] == ' ') {
                            fin = 0;
                            aceptar = 0;
                        }
                        if (add[0] != ' ') {
                            printf("Comando invalido se esta usando delete, no se puede uitlizar add.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (aceptar == 1) {
                            printf("Paramentro 1: %s\n", path);
                            printf("Paramentro 2: %s\n", nombre);
                            printf("Paramentro 3: %s\n", delete);
                            //llamar al metodo para eliminar particiones
                            fin = 0;
                        }
                    } else if (es_add == 0) {
                        if (tamanio[0] != ' ') {
                            printf("Comando invalido para usar add no se especifica un tamaño.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (unidades_tamanio[0] == ' ') {
                            printf("No se especifico la unidad de tamaño, seran en kilobytes.\n");
                            unidades_tamanio[0] = 'K';
                        }
                        if (path[0] == ' ') {
                            printf("Comando invalido debe de escribir el path de almacenamiento.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (nombre[0] == ' ') {
                            printf("Comando invalido debe de escribir el nombre de la particion.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (tipo[0] != ' ') {
                            printf("Comando invalido para usar add no se especifica el tipo de particion.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (ajuste[0] != ' ') {
                            printf("Comando invalido para usar add no se especifica el ajuste.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (delete[0] != ' ') {
                            printf("Comando invalido se esta usando add, no se puede uitlizar delete.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (aceptar == 1) {
                            printf("Paramentro 1: %s\n", path);
                            printf("Paramentro 2: %s\n", nombre);
                            printf("Paramentro 3: %s\n", unidades_tamanio);
                            printf("Paramentro 4: %s\n", add);
                            //llamar al metodo para hacer mas grande la particion
                            fin = 0;
                        }
                    } else {
                        if (tamanio[0] == ' ') {
                            printf("Comando invalido debe de escribir el tamaño de la particion.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (unidades_tamanio[0] == ' ') {
                            printf("No se especifico la unidad de tamaño, la particion se creara en Kilobytes.\n");
                            unidades_tamanio[0] = 'K';
                        }
                        if (unidades_tamanio[0] == '@') {
                            fin = 0;
                            aceptar = 0;
                        }
                        if (path[0] == ' ') {
                            printf("Comando invalido debe de escribir el path de almacenamiento del disco que desea particionar.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (nombre[0] == ' ') {
                            printf("Comando invalido debe de escribir el nombre de la particion nueva.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (tipo[0] == ' ') {
                            printf("No se especifico el tipo de particion, se creara como primaria.\n");
                            tipo[0] = 'P';
                            fin = 0;
                        }
                        if (tipo[0] == '@') {
                            fin = 0;
                            aceptar = 0;
                        }
                        if (ajuste[0] == ' ') {
                            printf("No se especifico el ajuste para asignar el espacio, sera el peor ajuste.\n");
                            ajuste[0] = 'W';
                            ajuste[1] = 'F';
                            fin = 0;
                        }
                        if (ajuste[0] == '@') {
                            fin = 0;
                            aceptar = 0;
                        }
                        if (aceptar == 1) {
                            printf("Paramentro 1: %s\n", tamanio);
                            printf("Paramentro 2: %s\n", unidades_tamanio);
                            printf("Paramentro 3: %s\n", path);
                            printf("Paramentro 4: %s\n", nombre);
                            printf("Paramentro 5: %s\n", tipo);
                            printf("Paramentro 6: %s\n", ajuste);
                            //llamar al metodo para crear particiones
                            fin = 0;
                        }
                    }
                }
                break;
            case 4:
                if (a_analizar[i] == ' ' || a_analizar[i] == '\\' || a_analizar[i] == '\n') {
                    estado = 4;
                    i++;
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'P' || a_analizar[i + 1] == 'p') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'T' || a_analizar[i + 3] == 't') && (a_analizar[i + 4] == 'H' || a_analizar[i + 4] == 'h') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando mount -path::\n");
                    estado = 4;
                    i = i + 7;
                    if (a_analizar[i] == '"') {
                        i++;
                        int contador = 0;
                        while (a_analizar[i] != '-') {
                            if (a_analizar[i] == '"') {
                                i++;
                                break;
                            }
                            path[contador] = a_analizar[i];
                            contador++;
                            i++;
                        }
                    } else {
                        estado = 11; //Estado de error
                    }
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'N' || a_analizar[i + 1] == 'n') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'M' || a_analizar[i + 3] == 'm') && (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando mount -name::\n");
                    estado = 4;
                    i = i + 7;
                    if (a_analizar[i] == '"') {
                        i++;
                        int contador = 0;
                        while (a_analizar[i] != '-') {
                            if (a_analizar[i] == '"') {
                                i++;
                                break;
                            }
                            nombre[contador] = a_analizar[i];
                            contador++;
                            i++;
                        }
                    } else {
                        estado = 11; //Estado de error
                    }
                } else {
                    if (path[0] == ' ') {
                        printf("Comando invalido debe de escribir el path de almacenamiento del disco que desea particionar.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (nombre[0] == ' ') {
                        printf("Comando invalido debe de escribir el nombre de la particion nueva.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (aceptar == 1) {
                        printf("Paramentro 1: %s\n", path);
                        printf("Paramentro 2: %s\n", nombre);
                        //llamar al metodo para montar las particiones
                        fin = 0;
                    }
                }
                break;
            case 5:
                if (a_analizar[i] == ' ' || a_analizar[i] == '\\' || a_analizar[i] == '\n') {
                    estado = 5;
                    i++;
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'I' || a_analizar[i + 1] == 'i') && (a_analizar[i + 2] == 'D' || a_analizar[i + 2] == 'd') && (a_analizar[i + 3] == '1' || a_analizar[i + 3] == '2'
                        || a_analizar[i + 3] == '3' || a_analizar[i + 3] == '4' || a_analizar[i + 3] == '5' || a_analizar[i + 3] == '6'
                        || a_analizar[i + 3] == '7' || a_analizar[i + 3] == '8' || a_analizar[i + 3] == '9') && a_analizar[i + 4] == ':' && a_analizar[i + 5] == ':') {
                    i = i + 6;
                    estado = 5;
                    int contador = 0;
                    while (a_analizar[i] != ' ') {
                        id[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else {
                    if (id[0] == ' ') {
                        printf("Comando invalido debe de escribir el id de la particion.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (aceptar == 1) {
                        printf("Paramentro 1: %s\n", id);
                        //llamar al metodo para desmontar las particiones
                        fin = 0;
                    }
                }
                break;
            case 6:
                if (a_analizar[i] == ' ' || a_analizar[i] == '\\' || a_analizar[i] == '\n') {
                    estado = 6;
                    i++;
                } else {
                    //printf("Comando exec \n");
                    int contador = 0;
                    strcat(a_analizar, "@");
                    while (a_analizar[i] != '@') {
                        if (a_analizar[i] == '.' && a_analizar[i + 1] == 's' && a_analizar[i + 2] == 'h') {
                            path[contador] = '.';
                            path[contador + 1] = 's';
                            path[contador + 2] = 'h';
                            contador = contador + 2;
                            break;
                        }
                        path[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                    if (path[0] == ' ') {
                        printf("Comando invalido debe de escribir el path de almacenamiento del disco que desea particionar.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (path[contador] == 'h' && path[contador - 1] == 's' && path[contador - 2] == '.') {
                        if (aceptar == 1) {
                            char * temp = &path[0];
                            printf("Paramentro 1: %s\n", temp);
                            cargar_script(temp);
                            //llamar a este metodo
                            fin = 0;
                        }
                    } else {
                        printf("Comando invalido debe de escribir el nombre del script con terminacio .sh\n");
                        fin = 0;
                    }
                }
                break;
            case 7:
                if (a_analizar[i] == 'a' || a_analizar[i] == 'b' || a_analizar[i] == 'c' || a_analizar[i] == 'd' || a_analizar[i] == 'e'
                        || a_analizar[i] == 'f' || a_analizar[i] == 'g' || a_analizar[i] == 'h' || a_analizar[i] == 'i' || a_analizar[i] == 'j'
                        || a_analizar[i] == 'k' || a_analizar[i] == 'l' || a_analizar[i] == 'm' || a_analizar[i] == 'n' || a_analizar[i] == 'o'
                        || a_analizar[i] == 'p' || a_analizar[i] == 'q' || a_analizar[i] == 'r' || a_analizar[i] == 's' || a_analizar[i] == 't'
                        || a_analizar[i] == 'u' || a_analizar[i] == 'v' || a_analizar[i] == 'w' || a_analizar[i] == 'x' || a_analizar[i] == 'y'
                        || a_analizar[i] == 'z' || a_analizar[i] == 'A' || a_analizar[i] == 'B' || a_analizar[i] == 'C' || a_analizar[i] == 'D'
                        || a_analizar[i] == 'E' || a_analizar[i] == 'F' || a_analizar[i] == 'G' || a_analizar[i] == 'H' || a_analizar[i] == 'I'
                        || a_analizar[i] == 'J' || a_analizar[i] == 'K' || a_analizar[i] == 'L' || a_analizar[i] == 'M' || a_analizar[i] == 'N'
                        || a_analizar[i] == 'O' || a_analizar[i] == 'P' || a_analizar[i] == 'Q' || a_analizar[i] == 'R' || a_analizar[i] == 'S'
                        || a_analizar[i] == 'T' || a_analizar[i] == 'U' || a_analizar[i] == 'V' || a_analizar[i] == 'W' || a_analizar[i] == 'X'
                        || a_analizar[i] == 'Y' || a_analizar[i] == 'Z' || a_analizar[i] == '0' || a_analizar[i] == '1' || a_analizar[i] == '2'
                        || a_analizar[i] == '3' || a_analizar[i] == '4' || a_analizar[i] == '5' || a_analizar[i] == '6' || a_analizar[i] == '7'
                        || a_analizar[i] == '8' || a_analizar[i] == '9' || a_analizar[i] == '_' || a_analizar[i] == '°' || a_analizar[i] == '|'
                        || a_analizar[i] == '¬' || a_analizar[i] == '!' || a_analizar[i] == '"' || a_analizar[i] == '#' || a_analizar[i] == '$'
                        || a_analizar[i] == '%' || a_analizar[i] == '&' || a_analizar[i] == '/' || a_analizar[i] == '(' || a_analizar[i] == ')'
                        || a_analizar[i] == '?' || a_analizar[i] == '\\' || a_analizar[i] == '¡' || a_analizar[i] == '¿' || a_analizar[i] == '´'
                        || a_analizar[i] == '+' || a_analizar[i] == '*' || a_analizar[i] == '~' || a_analizar[i] == '{' || a_analizar[i] == '}'
                        || a_analizar[i] == '[' || a_analizar[i] == ']' || a_analizar[i] == '_' || a_analizar[i] == '-' || a_analizar[i] == ':'
                        || a_analizar[i] == '.' || a_analizar[i] == ',' || a_analizar[i] == ';' || a_analizar[i] == ' ' || a_analizar[i] == 'á'
                        || a_analizar[i] == 'é' || a_analizar[i] == 'í' || a_analizar[i] == 'ó' || a_analizar[i] == 'ú' || a_analizar[i] == 'Á'
                        || a_analizar[i] == 'É' || a_analizar[i] == 'Í' || a_analizar[i] == 'Ó' || a_analizar[i] == 'Ú') {
                    estado = 7;
                    i++;
                } else if (a_analizar[i] == '\n') {
                    printf("Comentario.\n");
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

//Metodo para limpiar variables

void limpiar(char a_limpiar[]) {
    int i = 0;
    for (i = 0; i < strlen(a_limpiar); i++) {
        a_limpiar[i] = ' ';
    }
}

//metodo que verifica si existe el archivo en el path

int cargar_script(char a_buscar[]) {
    FILE * archivo;
    char caracter;
    char comando_ejecutar[100] = " ";
    limpiar(comando_ejecutar);
    int contador = 0;
    int contador_transacciones = 1;
    archivo = fopen(a_buscar, "r");
    if (archivo == NULL) {
        printf("\nError al intentar abrir el archivo. \n\n");
    } else {
        printf("******************************** Scripts ******************************** \n");
        while (feof(archivo) == 0) {
            caracter = fgetc(archivo);
            comando_ejecutar[contador] = caracter;
            contador++;
            if (caracter == '\n') {
                printf("************************************* %i ************************************* \n", contador_transacciones);
                printf("%s", comando_ejecutar);
                analizador(comando_ejecutar);
                limpiar(comando_ejecutar);
                contador = 0;
                contador_transacciones++;
            }
        }
    }
    fclose(archivo);
}
