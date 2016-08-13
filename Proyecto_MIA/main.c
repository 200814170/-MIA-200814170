#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


char comando[150]; //..........................comando de entrada

//Parametros que piden los diferentes comandos
char tamanio[100] = " "; //.....................tamaño de disco o bien particiones
char unidades_tamanio[100] = " "; //............unidades del tamaño
char path[100] = " "; //........................direccion path
char nombre[100] = " "; //......................nombre de disco o bien particion
char tipo[100] = " "; //........................tipo de particion, primaria, extendida o logica
char ajuste[100] = " "; //......................ajuste para la particion, primer ajuste, peor ajuste, mejor ajuste
char delete[100] = " "; //......................borrar particion
char add[100] = " "; //.........................agregar espacio a la particion
char id[100] = " "; //..........................id del disco, cuando este se monta
char basura[1];
char ids[1000];

//Situaciones del analizador
int salida = 1; //.............................Permanecia en el sistema; 0 = salir, 1 = dentro
int aceptar = 1; //............................aceptacion del analizador de comando;
int es_delete = 1; //..........................si se esta usando delete en fdisk; 1 = desactivado, 0 = activo
int es_add = 1; //.............................si se esta usando add en fdisk; 1 = desactivado, 0 = activo
int contador_archivo = 0;

typedef struct PARTICION {
    char part_status; //1
    char part_type; //1
    char part_fit; //1
    int part_start; //4
    int part_size; //4
    char part_name[16]; //16
} particion;

typedef struct MBR {
    int mbr_tamanio; //4 bytes
    timer_t mbr_fecha_creacion; //8 bytes
    int mbr_disk_signature; //4
    particion mbr_partition_1; //27
    particion mbr_partition_2; //27
    particion mbr_partition_3; //27
    particion mbr_partition_4; //27
} mbr;

typedef struct nodo_lista {
    char id[100];
    char numero_particion[10];
    char letra;
    char path[100];
    char nombre[100];
    struct nodo * siguiente;
} LISTA;

struct nodo_lista * primero;
struct nodo_lista * ultimo;

struct nodo_lista * primer_id;
struct nodo_lista * ultimo_id;

int main() {

    inicializar_lista();
    while (salida != 0) {
        printf("\n**************** PROYECTO MANEJO E IMPLEMENTACION DE ARCHIVOS**************** \n");
        printf("Ingrese el comando:\n");
        limpiar(comando);
        //gets(comando);
        fgets(comando, 150, stdin);

        //printf("Comando escrito: %s\n", comando);
        strcat(comando, " "); //se le agrega al final para que se puedan salir algunos ciclos que recolectan parametros


        //Todo_a_Mayusculas(comando); //Se convirte todo a mayusculas porque no se distingue entre mayusculas y minisculas
        //printf("Convertido: %s\n", comando);

        analizador(comando);
    }
    return 0;
}

//Metodo que analiza el comando de entrada.

void analizador(char a_analizar[]) {
    int i = 0; //contador que cuenta en que posicion del comando se esta
    int fin = 1; //situacion de analisis; 1 = analizando, 0 = fin del analisis
    int estado = 0; //Estado del automata
    while (fin != 0) {//inicio del while_1
        switch (estado) {
            case 0:
                //mkdisk
                if ((a_analizar[i] == 'm' || a_analizar[i] == 'M') &&
                        (a_analizar[i + 1] == 'k' || a_analizar[i + 1] == 'K') &&
                        (a_analizar[i + 2] == 'd' || a_analizar[i + 2] == 'D') &&
                        (a_analizar[i + 3] == 'i' || a_analizar[i + 3] == 'I') &&
                        (a_analizar[i + 4] == 's' || a_analizar[i + 4] == 'S') &&
                        (a_analizar[i + 5] == 'k' || a_analizar[i + 5] == 'K')) {
                    //printf("Comando Mkdisk\n");
                    estado = 1;
                    i = i + 6;

                    limpiar(tamanio);
                    limpiar(unidades_tamanio);
                    limpiar(path);
                    limpiar(nombre);

                    aceptar = 1; //estado de aceptacion correcto, pero puede cambiar despues si no existe algun parametro
                    //rmdisk
                } else if ((a_analizar[i] == 'r' || a_analizar[i] == 'R') &&
                        (a_analizar[i + 1] == 'm' || a_analizar[i + 1] == 'M') &&
                        (a_analizar[i + 2] == 'd' || a_analizar[i + 2] == 'D') &&
                        (a_analizar[i + 3] == 'i' || a_analizar[i + 3] == 'I') &&
                        (a_analizar[i + 4] == 's' || a_analizar[i + 4] == 'S') &&
                        (a_analizar[i + 5] == 'k' || a_analizar[i + 5] == 'K')) {
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
                } else if ((a_analizar[i] == 'm' || a_analizar[i] == 'M')&&
                        (a_analizar[i + 1] == 'o' || a_analizar[i + 1] == 'O') &&
                        (a_analizar[i + 2] == 'u' || a_analizar[i + 2] == 'U') &&
                        (a_analizar[i + 3] == 'n' || a_analizar[i + 3] == 'N') &&
                        (a_analizar[i + 4] == 't' || a_analizar[i + 4] == 'T')) {
                    printf("Comando mount\n");
                    estado = 4;
                    i = i + 6;
                    limpiar(path);
                    limpiar(nombre);
                    aceptar = 1;
                    //ummount
                } else if ((a_analizar[i] == 'u' || a_analizar[i] == 'U') &&
                        (a_analizar[i + 1] == 'm' || a_analizar[i + 1] == 'M') &&
                        (a_analizar[i + 2] == 'o' || a_analizar[i + 2] == 'O') &&
                        (a_analizar[i + 3] == 'u' || a_analizar[i + 3] == 'U') &&
                        (a_analizar[i + 4] == 'n' || a_analizar[i + 4] == 'N') &&
                        (a_analizar[i + 5] == 't' || a_analizar[i + 5] == 'T')) {
                    printf("Comando umount\n");
                    estado = 5;
                    i = i + 6;
                    limpiar(path);
                    limpiar(nombre);
                    aceptar = 1;
                    //exec
                } else if ((a_analizar[i] == 'e' || a_analizar[i] == 'E') &&
                        (a_analizar[i + 1] == 'x' || a_analizar[i + 1] == 'X') &&
                        (a_analizar[i + 2] == 'e' || a_analizar[i + 2] == 'E') &&
                        (a_analizar[i + 3] == 'c' || a_analizar[i + 3] == 'C')) {
                    printf("Comando exec\n");
                    estado = 6;
                    i = i + 4;
                    limpiar(path);
                    aceptar = 1;
                    //rep
                } else if ((a_analizar[i] == 'r' || a_analizar[i] == 'R') &&
                        (a_analizar[i + 1] == 'e' || a_analizar[i + 1] == 'E') &&
                        (a_analizar[i + 2] == 'p' || a_analizar[i + 2] == 'P')) {
                    printf("Comando rep\n");
                    estado = 8;
                    i = i + 3;
                    limpiar(nombre);
                    limpiar(path);
                    limpiar(id);
                    aceptar = 1;
                    //salir
                } else if ((a_analizar[i] == 's' || a_analizar[i] == 'S') &&
                        (a_analizar[i + 1] == 'a' || a_analizar[i + 1] == 'A') &&
                        (a_analizar[i + 2] == 'l' || a_analizar[i + 2] == 'L') &&
                        (a_analizar[i + 3] == 'i' || a_analizar[i + 3] == 'I') &&
                        (a_analizar[i + 4] == 'r' || a_analizar[i + 4] == 'R')) {
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
                    estado = 1; //se ignoran estos simbolos
                    i++;
                } else if (a_analizar[i] == '-' &&
                        (a_analizar[i + 1] == 'S' || a_analizar[i + 1] == 's') &&
                        (a_analizar[i + 2] == 'I' || a_analizar[i + 2] == 'i') &&
                        (a_analizar[i + 3] == 'Z' || a_analizar[i + 3] == 'z') &&
                        (a_analizar[i + 4] == 'E' || a_analizar[i + 4] == 'e') &&
                        a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando Mkdisk -size::\n");
                    estado = 1;
                    i = i + 7; //se aumenta en 7 el contador i para llegar al parametro ingresado
                    int contador = 0;
                    //while que recorre el char a_analizar para que vaya guardando el parametro
                    while (a_analizar[i] != ' ') {
                        if (a_analizar[i] == '-') {
                            break;
                        }
                        tamanio[contador] = a_analizar[i]; //se guarda el parametro en el char tamanio extraido del char a_analizar
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
                            } else {//si no se escribieron los valores aceptados
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
                    if (tamanio[0] == ' ') {//En caso no se haya escrito el parametro size el comando es invalido, se finaliza todo
                        printf("Comando invalido debe de escribir el tamaño del disco.\n");
                        fin = 0; //fin del ciclo while_1
                        aceptar = 0; //estado de aceptacion 0, no se acepta el comando
                    }
                    if (unidades_tamanio[0] == ' ') {//En caso no se haya escrito el parametro unit, pero como es opcional se colocan en megas
                        printf("No se especifico la unidad de tamaño, el disco se creara en Megabytes.\n");
                        unidades_tamanio[0] = 'M';
                    }
                    if (unidades_tamanio[0] == '@') {//si no se escribio los valores aceptados en unit se invalida el comando por no estar bien escrito
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
                        //llamar al metodo para crear el disco nuevo
                        Nuevo_disco(tamanio, unidades_tamanio, path, nombre);
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
                                if (tamanio[contador - 4] == '.' && (tamanio[contador - 3] == 'D' || tamanio[contador - 3] == 'd') && (tamanio[contador - 2] == 'S' || tamanio[contador - 2] == 's') && (tamanio[contador - 1] == 'K' || tamanio[contador - 1] == 'k')) {
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
                        if ((a_analizar[0] == 'S' || a_analizar[0] == 's')) {
                            printf("Paramentro 1: %s\n", tamanio);
                            //llamar al metodo eliminar disco
                            fin = 0;
                        }
                        if ((a_analizar[0] == 'N' || a_analizar[0] == 'n')) {
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
                                if (path[contador - 4] == '.' && (path[contador - 3] == 'D' || path[contador - 3] == 'd') && (path[contador - 2] == 'S' || path[contador - 2] == 's') && (path[contador - 1] == 'K' || path[contador - 1] == 'k')) {
                                    i++;
                                    break;
                                } else {
                                    printf("Comando invalido debe de escribir el path, con el nombre del disco con extension .dsk.\n");
                                    path[0] = ' ';
                                    break;
                                }
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
                            if (tipo[0] == 'P' || tipo[0] == 'E' || tipo[0] == 'L') {//valores permitidos para type
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
                            if (((ajuste[0] == 'B' || ajuste[0] == 'b') && (ajuste[1] == 'F' || ajuste[1] == 'f')) || ((ajuste[0] == 'F' || ajuste[0] == 'f') && (ajuste[1] == 'F' || ajuste[1] == 'f')) || ((ajuste[0] == 'W' || ajuste[0] == 'w') && (ajuste[1] == 'F' || ajuste[1] == 'f'))) {//valores permitidos para fit
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
                    es_delete = 0; //se activa que se esta utilizando delete
                    i = i + 9;
                    int contador = 0;
                    while (a_analizar[i] != '\0') {
                        if (a_analizar[i] == '-' || a_analizar[i] == ' ') {
                            if (((delete[0] == 'F' || delete[0] == 'f') && (delete[1] == 'U' || delete[1] == 'u') && (delete[2] == 'L' || delete[2] == 'l') && (delete[3] == 'L' || delete[3] == 'l')) || ((delete[0] == 'F' || delete[0] == 'f') && (delete[1] == 'A' || delete[1] == 'a') && (delete[2] == 'S' || delete[2] == 's') && (delete[3] == 'T' || delete[3] == 't'))) {//valores permitidos para delete
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
                    es_add = 0; //se activa que se esta utilizando add
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
                    if (es_delete == 0) {//si se esta utilizando delete
                        if (tamanio[0] != ' ') {//delete no usa size
                            printf("Comando invalido para usar delete no se especifica un tamaño.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (unidades_tamanio[0] != ' ') {//delete no usa unit
                            printf("Comando invalido para usar delete no se especifica la unidad de tamaño.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (path[0] == ' ') {//path de delete
                            printf("Comando invalido debe de escribir el path de almacenamiento donde se encuentra la particion.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (nombre[0] == ' ') {//name del delete
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
                        if (delete[0] == '@' || delete[0] == ' ') {//por si a delete se le escribieron valores no permitidos
                            fin = 0;
                            aceptar = 0;
                        }
                        if (add[0] != ' ') {//no se puede usar delete y add al mismo tiempo
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
                            //llamar al metodo para crear particiones nuevas
                            particion_nueva(tamanio, unidades_tamanio, path, nombre, ajuste, tipo);
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
                        Montar_particion(path, nombre);
                        fin = 0;
                    } else {
                        if (primer_id == NULL) {
                            printf("Aun no se han montado particiones.\n");
                        } else {
                            printf("Particiones montadas hasta el momento:\n");
                            imprimir_ids();
                        }
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
                    if (path[contador] == 'h' && path[contador - 1] == 's' && path[contador - 2] == '.') {//el archivo script debe tener su extension .sh
                        if (aceptar == 1) {
                            char * temp = &path[0];
                            printf("Paramentro 1: %s\n", temp);
                            cargar_script(temp); //se llama al metodo cargar_script
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
            case 8:
                if (a_analizar[i] == ' ' || a_analizar[i] == '\\' || a_analizar[i] == '\n') {
                    estado = 8;
                    i++;
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'I' || a_analizar[i + 1] == 'i') && (a_analizar[i + 2] == 'D' || a_analizar[i + 2] == 'd') && a_analizar[i + 3] == ':' && a_analizar[i + 4] == ':') {
                    //printf("Comando rep -id::)
                    i = i + 5;
                    estado = 8;
                    int contador = 0;
                    while (a_analizar[i] != ' ') {
                        id[contador] = a_analizar[i];
                        contador++;
                        i++;
                    }
                } else if (a_analizar[i] == '-' && (a_analizar[i + 1] == 'P' || a_analizar[i + 1] == 'p') && (a_analizar[i + 2] == 'A' || a_analizar[i + 2] == 'a') && (a_analizar[i + 3] == 'T' || a_analizar[i + 3] == 't') && (a_analizar[i + 4] == 'H' || a_analizar[i + 4] == 'h') && a_analizar[i + 5] == ':' && a_analizar[i + 6] == ':') {
                    //printf("Comando rep -path::\n");
                    estado = 8;
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
                    //printf("Comando rep -name::\n");
                    estado = 8;
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
                    if (id[0] == ' ') {
                        printf("Comando invalido debe de escribir el id.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (path[0] == ' ') {
                        printf("Comando invalido debe de escribir el path.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (nombre[0] == ' ') {
                        printf("Comando invalido debe de escribir el nombre.\n");
                        fin = 0;
                        aceptar = 0;
                    }
                    if (aceptar == 1) {
                        printf("Paramentro 1: %s\n", nombre);
                        printf("Paramentro 2: %s\n", path);
                        printf("Paramentro 3: %s\n", id);
                        if ((nombre[0] == 'm' || nombre[0] == 'M') && (nombre[1] == 'b' || nombre[1] == 'B') && (nombre[2] == 'r' || nombre[2] == 'R')) {
                            //llamar al metodo que genera el reporte del MBR
                            reporte_MBR(path, id);
                            //reporte_MBR("/home/tony/disquitos/Disco1.dsk","mbr");
                        }
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

void cargar_script(char direccion_archivo[]) {
    FILE * archivo;
    char caracter;
    char comando_ejecutar[100] = " ";
    limpiar(comando_ejecutar);
    int hay_diagonal = 0; //Hay diagonal invertida, 0 = no hay, 1 = si hay

    int contador = 0;
    int contador_transacciones = 1;

    archivo = fopen(direccion_archivo, "r");
    if (archivo == NULL) {
        printf("\nEl archivo no se pudo abrir, puede que la ruta no exista o bien esta mal escrita. \n\n");
    } else {
        printf("******************************** Scripts ******************************** \n");
        while (feof(archivo) == 0) {
            caracter = fgetc(archivo); //se lee caracter por caracter el archivo
            comando_ejecutar[contador] = caracter; //se agrega a un arreglo de chars
            contador++;
            if (caracter == '\n') {//se ejecuta una linea de comando a la vez
                int temporal = 0;
                while (comando_ejecutar[temporal] != '\0') {
                    if (comando_ejecutar[temporal] == '\\') {
                        contador = temporal - 1;
                        hay_diagonal = 1;
                    }
                    temporal++;
                }
                if (hay_diagonal == 1) {
                    hay_diagonal = 0;
                } else {
                    if (comando_ejecutar[0] != '\n') {
                        printf("\n************************************* No. %i ************************************* \n", contador_transacciones);
                        printf("%s\n", comando_ejecutar);
                        analizador(comando_ejecutar);
                        limpiar(comando_ejecutar);
                        contador = 0;
                        contador_transacciones++;
                        hay_diagonal = 0;
                    }
                }
            }
        }
    }
    fclose(archivo);
}

void Nuevo_disco(char tamanio[], char unidades_tamanio[], char path[], char nombre[]) {

    char path_completo[100];
    sprintf(path_completo, "%s%s", path, nombre);

    struct stat datosFichero;
    if (lstat(path, &datosFichero) == -1) {
        printf("El directorio %s no existia, se creo.\n", path);
        char temporal[100];
        sprintf(temporal, "%s%s", "mkdir ", path);
        char * temp = &temporal[0];
        system(temp);
    }

    mbr nuevo_disco;
    nuevo_disco.mbr_disk_signature = 1;
    //nuevo_disco.mbr_fecha_creacion = 12 / 12 / 2016;
    nuevo_disco.mbr_tamanio = atoi(tamanio);
    nuevo_disco.mbr_partition_1.part_size = 0;
    nuevo_disco.mbr_partition_2.part_size = 0;
    nuevo_disco.mbr_partition_3.part_size = 0;
    nuevo_disco.mbr_partition_4.part_size = 0;


    FILE *f = fopen(path_completo, "w+b");
    if (unidades_tamanio[0] == 'k' || unidades_tamanio[0] == 'K') {
        for (contador_archivo = 0; contador_archivo < atoi(tamanio); contador_archivo++)
            fwrite(basura, sizeof (basura), 1024, f);
    }

    if (unidades_tamanio[0] == 'm' || unidades_tamanio[0] == 'M') {
        for (contador_archivo = 0; contador_archivo < (atoi(tamanio) * 1024); contador_archivo++)
            fwrite(basura, sizeof (basura), 1024, f);
    }

    rewind(f);
    fwrite(&nuevo_disco, sizeof (nuevo_disco), 1, f);
    fclose(f);
    printf("Se creo el disco %s satisfactoriamente en la diereccion %s%s.\n", path, nombre);

}

void particion_nueva(char tamanio[], char unidades_tamanio[], char path[], char nombre[], char fit[], char type[]) {

    struct stat datosFichero;
    if (lstat(path, &datosFichero) == -1) {
        printf("El directorio %s no existia, se creo.\n", path);
        char temporal[100];
        sprintf(temporal, "%s%s", "mkdir ", path);
        char * temp = &temporal[0];
        system(temp);
    }


    mbr temporal1;

    FILE * f = fopen(path, "rb+");

    fseek(f, 0, SEEK_SET);
    //rewind(f);
    fread(&temporal1, sizeof (temporal1), 1, f);
    fclose(f);

    particion nueva_particion;

    nueva_particion.part_status = '0'; //1 = activa, 0 = no activa;
    nueva_particion.part_type = type[0]; //p = primaria, e = extendida

    if ((fit[0] == 'B' || fit[0] == 'b')&&(fit[1] == 'F' || fit[1] == 'f')) {//1 = BF, 2 = FF, 3 = WF
        nueva_particion.part_fit = '1';
    } else if ((fit[0] == 'F' || fit[0] == 'f')&&(fit[1] == 'F' || fit[1] == 'f')) {
        nueva_particion.part_fit = '2';
    } else if ((fit[0] == 'W' || fit[0] == 'w')&&(fit[1] == 'F' || fit[1] == 'f')) {
        nueva_particion.part_fit = '3';
    }

    nueva_particion.part_start = (int) sizeof (temporal1);
    nueva_particion.part_size = atoi(tamanio);

    if (temporal1.mbr_partition_1.part_size == 0) {//verifica si la particion 1 ya fue creada, si su tamaño = 0, aqui se crea la nueva particion
        temporal1.mbr_partition_1.part_status = nueva_particion.part_status;
        temporal1.mbr_partition_1.part_type = nueva_particion.part_type;
        temporal1.mbr_partition_1.part_fit = nueva_particion.part_fit;
        temporal1.mbr_partition_1.part_start = nueva_particion.part_start;
        temporal1.mbr_partition_1.part_size = nueva_particion.part_size;

        int contador = 0;
        while (contador < 16) {
            temporal1.mbr_partition_1.part_name[contador] = nombre[contador];
            contador++;
        }
        FILE * f2 = fopen(path, "rb+");
        rewind(f2);
        fwrite(&temporal1, sizeof (temporal1), 1, f2);
        fclose(f2);
    } else if (temporal1.mbr_partition_2.part_size == 0) {//verifica si la particion 2 ya fue creada, si su tamaño = 0, aqui se crea la nueva particion
        temporal1.mbr_partition_2.part_status = nueva_particion.part_status;
        temporal1.mbr_partition_2.part_type = nueva_particion.part_type;
        temporal1.mbr_partition_2.part_fit = nueva_particion.part_fit;
        temporal1.mbr_partition_2.part_start = nueva_particion.part_start;
        temporal1.mbr_partition_2.part_size = nueva_particion.part_size;

        int contador = 0;
        while (contador < 16) {
            temporal1.mbr_partition_2.part_name[contador] = nombre[contador];
            contador++;
        }
        FILE * f2 = fopen(path, "rb+");
        rewind(f2);
        fwrite(&temporal1, sizeof (temporal1), 1, f2);
        fclose(f2);
    } else if (temporal1.mbr_partition_3.part_size == 0) {//verifica si la particion 3 ya fue creada, si su tamaño = 0, aqui se crea la nueva particion
        temporal1.mbr_partition_3.part_status = nueva_particion.part_status;
        temporal1.mbr_partition_3.part_type = nueva_particion.part_type;
        temporal1.mbr_partition_3.part_fit = nueva_particion.part_fit;
        temporal1.mbr_partition_3.part_start = nueva_particion.part_start;
        temporal1.mbr_partition_3.part_size = nueva_particion.part_size;

        int contador = 0;
        while (contador < 16) {
            temporal1.mbr_partition_3.part_name[contador] = nombre[contador];
            contador++;
        }
        FILE * f2 = fopen(path, "rb+");
        rewind(f2);
        fwrite(&temporal1, sizeof (temporal1), 1, f2);
        fclose(f2);
    } else if (temporal1.mbr_partition_4.part_size == 0) {//verifica si la particion 4 ya fue creada, si su tamaño = 0, aqui se crea la nueva particion
        temporal1.mbr_partition_4.part_status = nueva_particion.part_status;
        temporal1.mbr_partition_4.part_type = nueva_particion.part_type;
        temporal1.mbr_partition_4.part_fit = nueva_particion.part_fit;
        temporal1.mbr_partition_4.part_start = nueva_particion.part_start;
        temporal1.mbr_partition_4.part_size = nueva_particion.part_size;

        int contador = 0;
        while (contador < 16) {
            temporal1.mbr_partition_4.part_name[contador] = nombre[contador];
            contador++;
        }

        FILE * f2 = fopen(path, "rb+");
        rewind(f2);
        fwrite(&temporal1, sizeof (temporal1), 1, f2);
        fclose(f2);
    }


    //Lectura temporal en consola de como estan las particiones
    mbr temporal3;
    FILE *f3 = fopen(path, "rb+");
    rewind(f3);
    fread(&temporal3, sizeof (temporal3), 1, f3);
    fclose(f3);

    printf("\nNombre ---------------------- Valor\n");
    printf("mbr_tamaño ------------------ %d\n", temporal3.mbr_tamanio);
    //printf("mbr_fecha_creacion ---------- %s", temporal3.mbr_fecha_creacion);
    printf("mbr_disk_signature ---------- %d\n", temporal3.mbr_disk_signature);

    printf("\tpart_status_1 --------------- %c\n", temporal3.mbr_partition_1.part_status);
    printf("\tpart_type_1 -----------------%c\n", temporal3.mbr_partition_1.part_type);
    printf("\tpart_fit_1 -----------------%c\n", temporal3.mbr_partition_1.part_fit);
    printf("\tpart_start_1 -----------------%d\n", temporal3.mbr_partition_1.part_start);
    printf("\tpart_zise_1 -----------------%d\n", temporal3.mbr_partition_1.part_size);
    printf("\tpart_name_1 -----------------%s\n", temporal3.mbr_partition_1.part_name);

    printf("part_status_2 --------------- %d\n", temporal3.mbr_partition_2.part_size);

    printf("\tpart_status_2 --------------- %c\n", temporal3.mbr_partition_2.part_status);
    printf("\tpart_type_2 -----------------%c\n", temporal3.mbr_partition_2.part_type);
    printf("\tpart_fit_2 -----------------%c\n", temporal3.mbr_partition_2.part_fit);
    printf("\tpart_start_2 -----------------%d\n", temporal3.mbr_partition_2.part_start);
    printf("\tpart_zise_2 -----------------%d\n", temporal3.mbr_partition_2.part_size);
    printf("\tpart_name_2 -----------------%s\n", temporal3.mbr_partition_2.part_name);

    printf("part_status_3 --------------- %d\n", temporal3.mbr_partition_3.part_size);

    printf("\tpart_status_3 --------------- %c\n", temporal3.mbr_partition_3.part_status);
    printf("\tpart_type_3 -----------------%c\n", temporal3.mbr_partition_3.part_type);
    printf("\tpart_fit_3 -----------------%c\n", temporal3.mbr_partition_3.part_fit);
    printf("\tpart_start_3 -----------------%d\n", temporal3.mbr_partition_3.part_start);
    printf("\tpart_zise_3 -----------------%d\n", temporal3.mbr_partition_3.part_size);
    printf("\tpart_name_3 -----------------%s\n", temporal3.mbr_partition_3.part_name);

    printf("part_status_4 --------------- %d\n", temporal3.mbr_partition_4.part_size);

    printf("\tpart_status_4 --------------- %c\n", temporal3.mbr_partition_4.part_status);
    printf("\tpart_type_4 -----------------%c\n", temporal3.mbr_partition_4.part_type);
    printf("\tpart_fit_4 -----------------%c\n", temporal3.mbr_partition_4.part_fit);
    printf("\tpart_start_4 -----------------%d\n", temporal3.mbr_partition_4.part_start);
    printf("\tpart_zise_4 -----------------%d\n", temporal3.mbr_partition_4.part_size);
    printf("\tpart_name_4 -----------------%s\n", temporal3.mbr_partition_4.part_name);

}

void Montar_particion(char path[], char nombre[]) {
    struct stat datosFichero;
    if (lstat(path, &datosFichero) == -1) {
        printf("El directorio %s no existe.\n", path);
    } else {
        int continuar = 1;
        struct nodo_lista * temporal = primero;
        while (temporal != NULL) {
            int i = 0;
            while (i < strlen(path)) {
                if (temporal->path[i] == path[i]) {
                    continuar = 1;
                    i++;
                } else {
                    continuar = 0;
                    i = strlen(path);
                    if (temporal->path[0] == ' ') {
                        strcpy(temporal->path, path);
                        strcpy(temporal->nombre, nombre);
                        break;
                    }
                }
            }
            if (continuar == 0) {
                break;
            } else {
                temporal = temporal->siguiente;
            }
        }

        struct nodo_lista * temporal_id = primer_id;
        int ii = 0;
        while (temporal_id != NULL) {
            while (ii < strlen(path)) {
                if (temporal_id->path[ii] == path[ii]) {
                    continuar = 0;
                    ii++;
                } else {
                    continuar = 1;
                    break;
                }
            }
            if (continuar == 0) {
                break;
            } else {
                temporal_id = temporal_id->siguiente;
            }
        }

        if (continuar == 0) {
            int contador = 0;
            while (contador < 11) {
                if (temporal->numero_particion[contador] == ' ') {
                    if (temporal->numero_particion[0] == ' ') {
                        temporal->numero_particion[0] = 1;
                    } else {
                        temporal->numero_particion[contador] = (temporal->numero_particion[contador - 1]) + 1;
                    }
                    contador = temporal->numero_particion[contador];

                    mbr temporal1;
                    FILE * f = fopen(path, "rb+");
                    fseek(f, 0, SEEK_SET);
                    fread(&temporal1, sizeof (temporal1), 1, f);
                    fclose(f);


                    int i = 0;
                    while (i < strlen(nombre)) {
                        if (temporal1.mbr_partition_1.part_name[i] == nombre[i]) {
                            continuar = 0;
                            i++;
                        } else {
                            continuar = 1;
                            break;
                        }
                    }

                    if (continuar == 0) {
                        temporal1.mbr_partition_1.part_status = '1';
                        FILE * f2 = fopen(path, "rb+");
                        rewind(f2);
                        fwrite(&temporal1, sizeof (temporal1), 1, f2);
                        fclose(f2);
                        printf("Particion Montada, id: vd%c%d\n", temporal->letra, contador);
                        sampar_id(path, nombre, temporal->letra, contador);
                        break;
                    }

                    i = 0;
                    while (i < strlen(nombre)) {
                        if (temporal1.mbr_partition_2.part_name[i] == nombre[i]) {
                            continuar = 0;
                            i++;
                        } else {
                            continuar = 1;
                            break;
                        }
                    }
                    if (continuar == 0) {
                        temporal1.mbr_partition_2.part_status = '1';
                        FILE * f2 = fopen(path, "rb+");
                        rewind(f2);
                        fwrite(&temporal1, sizeof (temporal1), 1, f2);
                        fclose(f2);
                        printf("Particion Montada, id: vd%c%d\n", temporal->letra, contador);
                        sampar_id(path, nombre, temporal->letra, contador);
                        break;
                    }

                    i = 0;
                    while (i < strlen(nombre)) {
                        if (temporal1.mbr_partition_3.part_name[i] == nombre[i]) {
                            continuar = 0;
                            i++;
                        } else {
                            continuar = 1;
                            break;
                        }
                    }

                    if (continuar == 0) {
                        temporal1.mbr_partition_3.part_status = '1';
                        FILE * f2 = fopen(path, "rb+");
                        rewind(f2);
                        fwrite(&temporal1, sizeof (temporal1), 1, f2);
                        fclose(f2);
                        printf("Particion Montada, id: vd%c%d\n", temporal->letra, contador);
                        sampar_id(path, nombre, temporal->letra, contador);
                        break;
                    }

                    i = 0;
                    while (i < strlen(nombre)) {
                        if (temporal1.mbr_partition_4.part_name[i] == nombre[i]) {
                            continuar = 0;
                            i++;
                        } else {
                            continuar = 1;
                            break;
                        }
                    }

                    if (continuar == 0) {
                        temporal1.mbr_partition_4.part_status = '1';
                        FILE * f2 = fopen(path, "rb+");
                        rewind(f2);
                        fwrite(&temporal1, sizeof (temporal1), 1, f2);
                        fclose(f2);
                        printf("Particion Montada, id: vd%c%d\n", temporal->letra, contador);
                        sampar_id(path, nombre, temporal->letra, contador);
                        break;
                    } else {
                        printf("La particion ingresada no existe.\n");
                    }
                }
                contador++;
            }
        }
    }
}

void reporte_MBR(char path[], char id[]) {

    char * cadena;
    int continuar = 0;
    struct nodo_lista * actual = primer_id;
    while (actual != NULL) {
        int contador = 0;
        while (contador < strlen(id)) {
            if (actual->id[contador] == id[contador]) {
                continuar = 1;
                contador++;
                break;
            } else {
                continuar = 0;
                break;
            }
        }
        if (continuar == 1) {
            mbr temporal3;
            FILE *f3 = fopen(actual->path, "rb+");
            rewind(f3);
            fread(&temporal3, sizeof (temporal3), 1, f3);
            fclose(f3);

            FILE *fp;
            fp = fopen("/home/tony/Escritorio/otra_tabla.dot", "w");

            fputs("digraph Tabla { \n", fp);
            fputs("node [shape=plaintext, fontsize=50];\n", fp);
            fputs("{rank = same; \"MBR Disco1.dsk\";}\n", fp);
            fputs("\"MBR Disco1.dsk\"  -> Nodo1[color = white];\n", fp);
            fputs("Nodo1[shape=record, width= 6, fontsize=20, label = \"", fp);
            fputs("{{Nombre|Valor}|", fp);
            fputs("{mbr_tamaño|", fp);
            fputs(temporal3.mbr_tamanio, fp);
            //sprintf(cadena, "%d", temporal3.mbr_tamanio);
            fputs(cadena, fp);
            fputs("}{mbr_fecha_creacion|", fp);
            sprintf(cadena, temporal3.mbr_fecha_creacion);
            fputs(cadena, fp);
            fputs("}{mbr_disk_signature|", fp);
            sprintf(cadena, temporal3.mbr_disk_signature);
            fputs(cadena, fp);
            if(temporal3.mbr_partition_1.part_status == '1'){
                fputs("}{part_status_1|", fp);
                sprintf(cadena, temporal3.mbr_partition_1.part_status);
                fputs(cadena, fp);
                fputs("}{part_type_1|", fp);
                sprintf(cadena, temporal3.mbr_partition_1.part_type);
                fputs(cadena, fp);
                fputs("}{part_fit_1|", fp);
                sprintf(cadena, temporal3.mbr_partition_1.part_fit);
                fputs(cadena, fp);
                fputs("}{part_start_1|", fp);
                sprintf(cadena, temporal3.mbr_partition_1.part_start);
                fputs(cadena, fp);
                fputs("}{part_size_1|", fp);
                sprintf(cadena, temporal3.mbr_partition_1.part_size);
                fputs(cadena, fp);
                fputs("}{part_name_1|", fp);
                sprintf(cadena, temporal3.mbr_partition_1.part_name);
                fputs(cadena, fp);
                fputs("}}", fp);
            }
            /*fputs("");
            fputs("");
            fputs("");
            fputs("");
            fputs("");
            fputs("");
            fputs("");*/

            fclose(fp);



            printf("\nNombre ---------------------- Valor\n");
            printf("mbr_tamaño ------------------ %d\n", temporal3.mbr_tamanio);
            //printf("mbr_fecha_creacion ---------- %s", temporal3.mbr_fecha_creacion);
            printf("mbr_disk_signature ---------- %d\n", temporal3.mbr_disk_signature);

            printf("\tpart_status_1 --------------- %c\n", temporal3.mbr_partition_1.part_status);
            printf("\tpart_type_1 -----------------%c\n", temporal3.mbr_partition_1.part_type);
            printf("\tpart_fit_1 -----------------%c\n", temporal3.mbr_partition_1.part_fit);
            printf("\tpart_start_1 -----------------%d\n", temporal3.mbr_partition_1.part_start);
            printf("\tpart_zise_1 -----------------%d\n", temporal3.mbr_partition_1.part_size);
            printf("\tpart_name_1 -----------------%s\n", temporal3.mbr_partition_1.part_name);

            printf("part_status_2 --------------- %d\n", temporal3.mbr_partition_2.part_size);

            printf("\tpart_status_2 --------------- %c\n", temporal3.mbr_partition_2.part_status);
            printf("\tpart_type_2 -----------------%c\n", temporal3.mbr_partition_2.part_type);
            printf("\tpart_fit_2 -----------------%c\n", temporal3.mbr_partition_2.part_fit);
            printf("\tpart_start_2 -----------------%d\n", temporal3.mbr_partition_2.part_start);
            printf("\tpart_zise_2 -----------------%d\n", temporal3.mbr_partition_2.part_size);
            printf("\tpart_name_2 -----------------%s\n", temporal3.mbr_partition_2.part_name);

            printf("part_status_3 --------------- %d\n", temporal3.mbr_partition_3.part_size);

            printf("\tpart_status_3 --------------- %c\n", temporal3.mbr_partition_3.part_status);
            printf("\tpart_type_3 -----------------%c\n", temporal3.mbr_partition_3.part_type);
            printf("\tpart_fit_3 -----------------%c\n", temporal3.mbr_partition_3.part_fit);
            printf("\tpart_start_3 -----------------%d\n", temporal3.mbr_partition_3.part_start);
            printf("\tpart_zise_3 -----------------%d\n", temporal3.mbr_partition_3.part_size);
            printf("\tpart_name_3 -----------------%s\n", temporal3.mbr_partition_3.part_name);

            printf("part_status_4 --------------- %d\n", temporal3.mbr_partition_4.part_size);

            printf("\tpart_status_4 --------------- %c\n", temporal3.mbr_partition_4.part_status);
            printf("\tpart_type_4 -----------------%c\n", temporal3.mbr_partition_4.part_type);
            printf("\tpart_fit_4 -----------------%c\n", temporal3.mbr_partition_4.part_fit);
            printf("\tpart_start_4 -----------------%d\n", temporal3.mbr_partition_4.part_start);
            printf("\tpart_zise_4 -----------------%d\n", temporal3.mbr_partition_4.part_size);
            printf("\tpart_name_4 -----------------%s\n", temporal3.mbr_partition_4.part_name);
        } else {
            actual = actual->siguiente;
        }
    }
}

void sampar(char letra, char path[], char nombre[], char numero[], char id[]) {
    LISTA * nuevo_nodo = (LISTA *) malloc(sizeof (LISTA));
    if (primero == NULL) {
        primero = nuevo_nodo;
        ultimo = nuevo_nodo;
        strcpy(nuevo_nodo->id, id);
        strcpy(nuevo_nodo->numero_particion, numero);
        nuevo_nodo->letra = letra;
        strcpy(nuevo_nodo->path, path);
        strcpy(nuevo_nodo->nombre, nombre);
    } else {
        ultimo->siguiente = nuevo_nodo;
        ultimo = nuevo_nodo;
        strcpy(nuevo_nodo->id, id);
        strcpy(nuevo_nodo->numero_particion, numero);
        nuevo_nodo->letra = letra;
        strcpy(nuevo_nodo->path, path);
        strcpy(nuevo_nodo->nombre, nombre);
    }
}

void sampar_id(char path[], char nombre[], char letra, int contador) {
    char temporal[100];
    sprintf(temporal, "vd%c%d", letra, contador);

    LISTA * nuevo_nodo = (LISTA *) malloc(sizeof (LISTA));
    if (primer_id == NULL) {
        primer_id = nuevo_nodo;
        ultimo_id = nuevo_nodo;
        strcpy(nuevo_nodo->id, temporal);
        strcpy(nuevo_nodo->path, path);
        strcpy(nuevo_nodo->nombre, nombre);
    } else {
        ultimo_id->siguiente = nuevo_nodo;
        ultimo_id = nuevo_nodo;
        strcpy(nuevo_nodo->id, temporal);
        strcpy(nuevo_nodo->path, path);
        strcpy(nuevo_nodo->nombre, nombre);
    }
}

void imprimir() {
    struct nodo_lista * temporal = primero;
    while (temporal != NULL) {
        printf("nodo %s\n", temporal->id);
        printf("nodo %s\n", temporal->numero_particion);
        printf("nodo %c\n", temporal->letra);
        printf("nodo %s\n", temporal->path);
        printf("nodo %s\n\n", temporal->nombre);
        temporal = temporal->siguiente;
    }
}

void imprimir_ids() {
    struct nodo_lista * temporal = primer_id;
    while (temporal != NULL) {
        printf("id %s ", temporal->id);
        printf(" -path \"%s ", temporal->path);
        printf("\" -name \"%s\"\n", temporal->nombre);
        temporal = temporal->siguiente;
    }
}

void inicializar_lista() {
    char letras[28] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    int contador = 0;
    while (contador < 26) {
        sampar(letras[contador], " ", " ", " ", " ");
        contador++;
    }
    //mount -path::"/home/disquitos/Disco1.dsk" -name::"Part_02"
    //Montar_particion("/home/tony/disquitos/Disco1.dsk", "Part_02");
    //imprimir_ids();

}
