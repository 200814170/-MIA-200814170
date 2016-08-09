#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
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
                case 0:
                    //Mkdisk
                    if (comando[i] == 'M' && comando[i + 1] == 'K' && comando[i + 2] == 'D' && comando[i + 3] == 'I' && comando[i + 4] == 'S' && comando[i + 5] == 'K') {
                        //printf("Comando Mkdisk\n");
                        estado = 1;
                        i = i + 6;
                        limpiar(tamanio);
                        limpiar(unidades_tamanio);
                        limpiar(path);
                        limpiar(nombre);
                        aceptar = 1;
                        //rmdisk
                    } else if (comando[i] == 'R' && comando[i + 1] == 'M' && comando[i + 2] == 'D' && comando[i + 3] == 'I' && comando[i + 4] == 'S' && comando[i + 5] == 'K') {
                        //printf("Comando Rmdisk\n");
                        estado = 2;
                        i = i + 6;
                        limpiar(tamanio);
                        aceptar = 1;
                        //fdisk
                    } else if (comando[i] == 'F' && comando[i + 1] == 'D' && comando[i + 2] == 'I' && comando[i + 3] == 'S' && comando[i + 4] == 'K') {
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
                    } else if (comando[i] == 'M' && comando[i + 1] == 'O' && comando[i + 2] == 'U' && comando[i + 3] == 'N' && comando[i + 4] == 'T') {
                        printf("Comando mount\n");
                        estado = 4;
                        i = i + 6;
                        limpiar(path);
                        limpiar(nombre);
                        aceptar = 1;
                        //salir
                    } else if (comando[i] == 'U' && comando[i + 1] == 'M' && comando[i + 2] == 'O' && comando[i + 3] == 'U' && comando[i + 4] == 'N' && comando[i + 5] == 'T') {
                        printf("Comando umount\n");
                        estado = 5;
                        i = i + 6;
                        limpiar(path);
                        limpiar(nombre);
                        aceptar = 1;
                        //salir
                    } else if (comando[i] == 'S' && comando[i + 1] == 'A' && comando[i + 2] == 'L' && comando[i + 3] == 'I' && comando[i + 4] == 'R') {
                        //printf("Comando Salir\n");
                        estado = 10;
                    } else {
                        estado = 11;
                    }
                    break;
                case 1:
                    if (comando[i] == ' ' || comando[i] == '\\' || comando[i] == '\n') {
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
                            tamanio[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '+' && comando[i + 1] == 'U' && comando[i + 2] == 'N' && comando[i + 3] == 'I' && comando[i + 4] == 'T' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando Mkdisk +Unit::\n");
                        estado = 1;
                        i = i + 7;
                        int contador = 0;
                        while (comando[i] != '\0') {
                            if (comando[i] == '-' || comando[i] == ' ') {
                                if (unidades_tamanio[0] == 'K' || unidades_tamanio[0] == 'M') {
                                    break;
                                } else {
                                    printf("Comando invalido, las unidades de tamaño deben ser en Megabytes (M) o en kilobytes(K).\n");
                                    unidades_tamanio[0] = '@';
                                    break;
                                }
                            }
                            unidades_tamanio[contador] = comando[i];
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
                                path[contador] = comando[i];
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
                                    if (nombre[contador - 4] == '.' && nombre[contador - 3] == 'D' && nombre[contador - 2] == 'S' && nombre[contador - 1] == 'K') {
                                        break;
                                    } else {
                                        printf("Comando invalido debe de escribir el nombre del disco con extension .dsk.\n");
                                        nombre[0] = ' ';
                                        break;
                                    }
                                }
                                nombre[contador] = comando[i];
                                contador++;
                                i++;
                            }
                        } else {
                            estado = 11; //Estado de error
                        }
                    } else {
                        if (tamanio[0] == ' ') {// == 'N' && parametro1[1] == 'a' && parametro1[2] == 'd' && parametro1[3] == 'a'){
                            printf("Comando invalido debe de escribir el tamaño del disco.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (unidades_tamanio[0] == ' ') {// == 'N' && parametro2[1] == 'a' && parametro2[2] == 'd' && parametro2[3] == 'a'){
                            printf("No se especifico la unidad de tamaño, el disco se creara en Megabytes.\n");
                            unidades_tamanio[0] = 'M';
                        }
                        if (unidades_tamanio[0] == '@') {
                            fin = 0;
                            aceptar = 0;
                        }
                        if (path[0] == ' ') {// == 'N' && parametro3[1] == 'a' && parametro3[2] == 'd' && parametro3[3] == 'a'){
                            printf("Comando invalido debe de escribir el path de almacenamiento del disco.\n");
                            fin = 0;
                            aceptar = 0;
                        }
                        if (nombre[0] == ' ') {// == 'N' && parametro4[1] == 'a' && parametro4[2] == 'd' && parametro4[3] == 'a'){
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
                            fin = 0;
                        }
                    }
                    break;
                case 2:
                    if (comando[i] == ' ' || comando[i] == '\\' || comando[i] == '\n') {
                        estado = 2;
                        i++;
                    } else if (comando[i] == '-' && comando[i + 1] == 'P' && comando[i + 2] == 'A' && comando[i + 3] == 'T' && comando[i + 4] == 'H' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando rmdisk -path::\n");
                        estado = 2;
                        i = i + 7;
                        if (comando[i] == '"') {
                            i++;
                            int contador = 0;
                            while (comando[i] != '-') {
                                if (comando[i] == '"') {
                                    i++;
                                    if (tamanio[contador - 4] == '.' && tamanio[contador - 3] == 'D' && tamanio[contador - 2] == 'S' && tamanio[contador - 1] == 'K') {
                                        break;
                                    } else {
                                        printf("Comando invalido debe de escribir el nombre del disco con extension .dsk.\n");
                                        tamanio[0] = ' ';
                                        break;
                                    }
                                }
                                tamanio[contador] = comando[i];
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
                            limpiar(comando);
                            fgets(comando, 100, stdin);
                            strcat(comando, " ");
                            Todo_a_Mayusculas(comando);
                            if (comando[0] == 'S') {
                                printf("Paramentro 1: %s\n", tamanio);
                                //llamar al metodo eliminar disco
                                fin = 0;
                            }
                            if (comando[0] == 'N') {
                                fin = 0;
                            }
                        }
                    }
                    break;
                case 3:
                    if (comando[i] == ' ' || comando[i] == '\\' || comando[i] == '\n') {
                        estado = 3;
                        i++;
                    } else if (comando[i] == '-' && comando[i + 1] == 'S' && comando[i + 2] == 'I' && comando[i + 3] == 'Z' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando fdisk -size::\n");
                        estado = 3;
                        i = i + 7;
                        int contador = 0;
                        while (comando[i] != ' ') {
                            if (comando[i] == '-') {
                                break;
                            }
                            tamanio[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '+' && comando[i + 1] == 'U' && comando[i + 2] == 'N' && comando[i + 3] == 'I' && comando[i + 4] == 'T' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando fdisk +Unit::\n");
                        estado = 3;
                        i = i + 7;
                        int contador = 0;
                        while (comando[i] != '\0') {
                            if (comando[i] == '-' || comando[i] == ' ') {
                                if (unidades_tamanio[0] == 'B' || unidades_tamanio[0] == 'K' || unidades_tamanio[0] == 'M') {
                                    break;
                                } else {
                                    printf("Comando invalido, las unidades de tamaño deben ser en Megabytes (M) o en kilobytes(K) o en bytes(B).\n");
                                    unidades_tamanio[0] = '@';
                                    break;
                                }
                            }
                            unidades_tamanio[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '-' && comando[i + 1] == 'P' && comando[i + 2] == 'A' && comando[i + 3] == 'T' && comando[i + 4] == 'H' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando fdisk -path::\n");
                        estado = 3;
                        i = i + 7;
                        if (comando[i] == '"') {
                            i++;
                            int contador = 0;
                            while (comando[i] != '-') {
                                if (comando[i] == '"') {
                                    i++;
                                    break;
                                }
                                path[contador] = comando[i];
                                contador++;
                                i++;
                            }
                        } else {
                            estado = 11; //Estado de error
                        }
                    } else if (comando[i] == '-' && comando[i + 1] == 'N' && comando[i + 2] == 'A' && comando[i + 3] == 'M' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando fdisk -name::\n");
                        estado = 3;
                        i = i + 7;
                        if (comando[i] == '"') {
                            i++;
                            int contador = 0;
                            while (comando[i] != '-') {
                                if (comando[i] == '"') {
                                    i++;
                                    break;
                                }
                                nombre[contador] = comando[i];
                                contador++;
                                i++;
                            }
                        } else {
                            estado = 11; //Estado de error
                        }
                    } else if (comando[i] == '+' && comando[i + 1] == 'T' && comando[i + 2] == 'Y' && comando[i + 3] == 'P' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando fdisk +type::\n");
                        estado = 3;
                        i = i + 7;
                        int contador = 0;
                        while (comando[i] != '\0') {
                            if (comando[i] == '-' || comando[i] == ' ') {
                                if (tipo[0] == 'P' || tipo[0] == 'E' || tipo[0] == 'L') {
                                    break;
                                } else {
                                    printf("Comando invalido, los tipos de discos deben ser Primarias (P) o Extendidas (E) o Logicas (L).\n");
                                    tipo[0] = '@';
                                    break;
                                }
                            }
                            tipo[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '+' && comando[i + 1] == 'F' && comando[i + 2] == 'I' && comando[i + 3] == 'T' && comando[i + 4] == ':' && comando[i + 5] == ':') {
                        //printf("Comando fdisk +fit::\n");
                        estado = 3;
                        i = i + 6;
                        int contador = 0;
                        while (comando[i] != '\0') {
                            if (comando[i] == '-' || comando[i] == ' ') {
                                if ((ajuste[0] == 'B' && ajuste[1] == 'F') || (ajuste[0] == 'F' && ajuste[1] == 'F') || (ajuste[0] == 'W' && ajuste[1] == 'F')) {
                                    break;
                                } else {
                                    printf("Comando invalido, los tipos de ajustes deben ser: Mejor Ajuste (BF) o Primer Ajuste (FF) o Pero Ajuste (WF).\n");
                                    ajuste[0] = '@';
                                    break;
                                }
                            }
                            ajuste[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '+' && comando[i + 1] == 'D' && comando[i + 2] == 'E' && comando[i + 3] == 'L' && comando[i + 4] == 'E' && comando[i + 5] == 'T' && comando[i + 6] == 'E' && comando[i + 7] == ':' && comando[i + 8] == ':') {
                        //printf("Comando fdisk +delete::\n");
                        estado = 3;
                        es_delete = 0;
                        i = i + 9;
                        int contador = 0;
                        while (comando[i] != '\0') {
                            if (comando[i] == '-' || comando[i] == ' ') {
                                if ((delete[0] == 'F' && delete[1] == 'U' && delete[2] == 'L' && delete[3] == 'L') || (delete[0] == 'F' && delete[1] == 'A' && delete[2] == 'S' && delete[3] == 'T')) {
                                    break;
                                } else {
                                    printf("Comando invalido, los tipos de eliminacion deben ser: full o fast.\n");
                                    delete[0] = '@';
                                    break;
                                }
                            }
                            delete[contador] = comando[i];
                            contador++;
                            i++;
                        }
                    } else if (comando[i] == '+' && comando[i + 1] == 'A' && comando[i + 2] == 'D' && comando[i + 3] == 'D' && comando[i + 4] == ':' && comando[i + 5] == ':') {
                        //printf("Comando fdisk +add::\n");
                        estado = 3;
                        es_add = 0;
                        i = i + 6;
                        int contador = 0;
                        while (comando[i] != '\0') {
                            if (comando[i] == '-' || comando[i] == ' ') {
                                break;
                            }
                            add[contador] = comando[i];
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
                    if (comando[i] == ' ' || comando[i] == '\\' || comando[i] == '\n') {
                        estado = 4;
                        i++;
                    } else if (comando[i] == '-' && comando[i + 1] == 'P' && comando[i + 2] == 'A' && comando[i + 3] == 'T' && comando[i + 4] == 'H' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando mount -path::\n");
                        estado = 4;
                        i = i + 7;
                        if (comando[i] == '"') {
                            i++;
                            int contador = 0;
                            while (comando[i] != '-') {
                                if (comando[i] == '"') {
                                    i++;
                                    break;
                                }
                                path[contador] = comando[i];
                                contador++;
                                i++;
                            }
                        } else {
                            estado = 11; //Estado de error
                        }
                    } else if (comando[i] == '-' && comando[i + 1] == 'N' && comando[i + 2] == 'A' && comando[i + 3] == 'M' && comando[i + 4] == 'E' && comando[i + 5] == ':' && comando[i + 6] == ':') {
                        //printf("Comando mount -name::\n");
                        estado = 4;
                        i = i + 7;
                        if (comando[i] == '"') {
                            i++;
                            int contador = 0;
                            while (comando[i] != '-') {
                                if (comando[i] == '"') {
                                    i++;
                                    break;
                                }
                                nombre[contador] = comando[i];
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
                            //llamar al metodo para crear particiones
                            fin = 0;
                        } else {
                            //mostrar todas las particiones montadas
                        }
                    }
                    break;
                case 5:
                    if (comando[i] == ' ' || comando[i] == '\\' || comando[i] == '\n') {
                        estado = 5;
                        i++;
                    } else if (comando[i] == '-' && comando[i + 1] == 'I' && comando[i + 2] == 'D' && (comando[i + 3] == '1' || comando[i + 3] == '2'
                            || comando[i + 3] == '3' || comando[i + 3] == '4' || comando[i + 3] == '5' || comando[i + 3] == '6'
                            || comando[i + 3] == '7' || comando[i + 3] == '8' || comando[i + 3] == '9') && comando[i + 4] == ':' && comando[i + 5] == ':') {
                        i = i + 6;
                        estado = 5;
                        int contador = 0;
                        while (comando[i] != ' ') {
                            id[contador] = comando[i];
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

void limpiar(char a_limpiar[]) {
    int i = 0;
    for (i = 0; i < strlen(a_limpiar); i++) {
        a_limpiar[i] = ' ';
    }
}
