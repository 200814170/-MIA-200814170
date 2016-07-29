#include <stdio.h>
#include <stdlib.h>

int main()
{
    char comando[20] = "";
    int salida = 1;
    while(salida != 0){
        printf("**************** PROYECTO MANEJO E IMPLEMENTACION DE ARCHIVOS**************** \n");
        printf("Ingrese el comando:\n");
        fflush(stdin);
        scanf("%s", &comando);
        printf("Comando escrito: %s\n", comando);

        if(comando[0] == 's' && comando[1] == 'a' && comando[2] == 'l' && comando[3] == 'i' && comando[4] == 'r'){
            salida = 0;
        }
    }

    return 0;
}
