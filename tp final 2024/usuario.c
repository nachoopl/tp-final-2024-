#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "usuario.h"
stUsuario cargarUnusuario()
{
    stUsuario A;


    printf("\nIngrese IdUsuario: ");
    while (scanf("%i", &A.idUsuario) != 1)
    {
        printf("ERROR. Ingrese un numero entero para IdUsuario: ");
        fflush(stdin);
    }

    printf("\nIngrese el nombre de usuario: ");
    while (scanf("%s", A.nombreUsuario) != 1)
    {
        printf("ERROR. Ingrese un nombre de usuario valido: ");
        fflush(stdin);
    }

    printf("\nIngrese contrasenia: ");
    while (scanf("%s", A.pass) != 1 || strlen(A.pass) <= 6)
    {
        printf("ERROR: La contrasenia debe tener mas de 6 caracteres. Ingrese una contrasenia valida: ");
        fflush(stdin);
    }


    printf("\nIngrese anio nacimiento(14 o mas): ");
    while (scanf("%i", &A.anioNacimiento) != 1 && A.anioNacimiento >2010 )
    {
        printf("ERROR Por favor, ingrese un anio de nacimiento valido: ");
        fflush(stdin);
    }


    printf("\nIngrese genero(f/m): ");
    while (scanf(" %c", &A.genero) != 1 || (A.genero != 'f' && A.genero != 'm'))
    {
        printf("ERROR. Ingrese 'f' para femenino o 'm' para masculino: ");
        fflush(stdin);
    }


    printf("\nIngrese pais: ");
    while (scanf("%s", A.pais) != 1)
    {
        printf("ERROR. Ingrese un pais valido: ");
        fflush(stdin);
    }


    printf("\ningrese eliminado(1/0): ");
    while (scanf("%i", &A.eliminado) != 1 || (A.eliminado != 0 && A.eliminado != 1))
    {
        printf("ERROR. Por favor, ingrese 1 para eliminado o 0 para no eliminado: ");
        fflush(stdin);
    }

    return A;
}
void mostrarUsuario(stUsuario A)
{
    char m[]= {"Masculino"};
    char f[]= {"Femenino"};
    printf("ID de Usuario: %d\n", A.idUsuario);
    printf("Nombre de Usuario: %s\n", A.nombreUsuario);
    printf("Contrasena: %s\n", A.pass);
    printf("Ano de Nacimiento: %d", A.anioNacimiento);
    if(A.genero=='m')
        printf("\nGenero: %s\n",m);
    else if(A.genero=='f')
        printf("\nGenero: %s\n",f);
    printf("Pais: %s\n", A.pais);
    printf("Eliminado: %i\n", A.eliminado);
    puts("-----------------------");
}

///ARCHIVOS

void cargarUnusuarioArchivo(char ArchivoUsuario[],stUsuario A)
{
    FILE* archi=fopen("usuario.dat","ab");
    if(archi)
    {
        fwrite(&A,sizeof(stUsuario),1,archi);
        fclose(archi);
    }
}

void mostrarArchivoUsuario(char ArchivoUsuario[], stUsuario A) {
    FILE* archi = fopen(ArchivoUsuario, "rb");
    if (archi) {
        while (fread(&A, sizeof(stUsuario), 1, archi) > 0) {
            mostrarUsuario(A);
        }
        fclose(archi);
    } else {
        printf("ERROR: No se pudo abrir el archivo %s.\n", ArchivoUsuario);
    }
}

///ARREGLODELISTAS
int buscarPosUsuario(stCelda ADL[],int IDusuario,int validos)
{
    int i=0;
    int pos=-1;
    while(i<validos && pos==-1)
    {
        if(ADL[i].A.idUsuario==IDusuario)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}
int agregarUsuario(stCelda ADL[],stUsuario A,int validos)
{

    ADL[validos].A=A;
    ADL[validos].listaCanciones=iniclista();
    validos++;
    return validos;
}
stUsuario cargarUsuarioADL(int idUsuario)
{
    stUsuario A;

    A.idUsuario=idUsuario;
    return A;
}
void bajaUsuarioArchivo(char nombreArchivo[], int idUsuario) // Funcion que da de baja un usuario por su id
{
    FILE* archi = fopen(nombreArchivo,"r+b");
    stUsuario A;
    if(archi)
    {
        while(fread(&A, sizeof(stUsuario), 1, archi) > 0)
        {
            if(idUsuario == A.idUsuario)
            {
                A.eliminado = 1;
                fseek(archi,-sizeof(stUsuario),SEEK_CUR);
                fwrite(&A, sizeof(stUsuario), 1, archi);
                fclose(archi);
                break;
            }
        }
        fclose(archi);

    }
}


void bajaLogicaUsuario(char nombreArchivo[], int idUsuario)
{
    int flag = 0;
    char darBaja;
    do
    {
        printf("Esta seguro que desea darse de baja en el sistema(s/n/0)?\n\ns. Si\nn. No\n0. Regresar\n\nOpcion: ");
        fflush(stdin);
        scanf(" %c", &darBaja);
        system("cls");
        switch(darBaja)
        {
        case 's':
            system("cls");
            bajaUsuarioArchivo("usuarios.dat", idUsuario);
            printf("\nEl usuario fue dado de baja correctamente\n");
            system("pause");
            system("cls");
            break;
        case 'n':
            system("cls");
            printf("\nDada de baja cancelada.\n");
            system("pause");
            system("cls");
            break;
        case '0':
            system("cls");
            break;
        default:
            printf("Caracter erroneo, ingrese uno valido\n\n");
            break;
        }

    }
    while(darBaja!='0');
}

void altaLogicaUsuario(char nombreArchivo[], int idUsuario)
{
    char darAlta;
    do
    {
        printf("Esta seguro que desea darse de alta en el sistema(s/n/0)?\n\ns. Si\nn. No\n0. Regresar\n\nOpcion: ");
        fflush(stdin);
        scanf(" %c",&darAlta);
        switch(darAlta)
        {
        case 's':
            system("cls");
            altaUsuarioArchivo("usuario.dat", idUsuario);
            printf("\nEl usuario fue dado de alta correctamente\n");
            system("pause");
            system("cls");
            break;
        case 'n':
            system("cls");
            printf("\nDada de alta cancelada.\n");
            system("pause");
            system("cls");
            break;
        case '0':
            system("cls");
            break;
        default:
            printf("Caracter erroneo, ingrese uno valido\n\n");
            break;
        }
    }
    while(darAlta!='0');

}

void altaUsuarioArchivo(char ArchivoUsuario[], int idUsuario)
{
    FILE * archi = fopen(ArchivoUsuario,"r+b");
    stUsuario A;

    if(archi)
    {
        while(fread(&A, sizeof(stUsuario), 1, archi) > 0)
        {
            if(idUsuario == A.idUsuario)
            {
                A.eliminado = 0;
                fseek(archi, (-1) * sizeof(stUsuario), 1);
                fwrite(&A, sizeof(stUsuario), 1, archi);

                break;
            }
        }
        fclose(archi);
    }
}


stUsuario mostrarDatosUsuarioBuscado(char ArchivoUsuario[], int dato) // Funcion que muestra un usuario buscado por id en el archivo de usuarios
{
    stUsuario A;
    FILE *buffer=fopen(ArchivoUsuario, "rb");
    if(buffer)
    {
        while(fread(&A, sizeof(stUsuario), 1, buffer)>0)
        {
            if(A.idUsuario==dato)
            {
                printf("\nYa estas registrado, los datos del usuario registrado con dicho Idusuario:\n");
                mostrarUsuario(A);
            }
        }
        fclose(buffer);
    }
    return A;
}
int buscarUsuarioPorID(char ArchivoUsuario[], int dato) // Funcion que busca un usuario por id en el archivo de usuarios
{
    stUsuario A;
    int flag=0;
    FILE *buffer=fopen(ArchivoUsuario, "rb");
    if(buffer)
    {
        while(fread(&A, sizeof(stUsuario), 1, buffer)>0)
        {
            if(A.idUsuario==dato)
            {
                flag=1;
            }
        }
        fclose(buffer);
    }
    return flag;
}
void modificarDatosUsuario(char ArchivoUsuario[], int dato) // Funcion que modifica los datos de un usuario ingresado
{

    int mod, edad, flag=0;
    char contra[20];
    char nombre[20];
    FILE* buffer=fopen("usuario.dat", "r+b");
    stUsuario A;
    if(buffer)
    {
        while(flag==0 && fread(&A, sizeof(stUsuario), 1, buffer) == 1)
        {
            if(A.idUsuario==dato)
            {
                do
                {
                    puts("\n-------------------MODIFICAR USUARIO-----------------------");
                    mostrarUsuario(A);
                    printf("Elija el dato a modificar(1/2/3/0): \n\n1. Nombre\n2. Nacimiento\n3.Contrasenia\n0. Regresar\n\nOpcion: ");
                    fflush(stdin);
                    scanf("%d", &mod);
                    switch(mod)
                    {
                    case 1:
                        printf("\nIngrese el nuevo nombre: ");
                        fflush(stdin);
                        gets(nombre);
                        strcpy(A.nombreUsuario, nombre);
                        printf("\nEl nuevo nombre se ha cambiado a: %s\n", A.nombreUsuario);
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        printf("\nIngrese el nuevo anio nacimiento: ");
                        fflush(stdin);
                        scanf("%d", &edad);
                        while(edad > 2010)
                        {
                            printf("\nNo puedes registrarte siendo menor de 14: ");
                            fflush(stdin);
                            scanf("%d", &edad);
                        }
                        A.anioNacimiento=edad;
                        printf("\nLa edad se ha cambiado a: %d\n", A.anioNacimiento);
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        printf("\nIngrese la nueva contrasenia(min 6 caracteres): ");
                        fflush(stdin);
                        scanf("%s",contra);
                        while ( strlen(contra) <= 6)
                        {
                            printf("ERROR: La contrasenia debe tener más de 6 caracteres. Ingrese una contrasenia valida: ");
                            fflush(stdin);
                            scanf("%s",contra);
                        }
                        strcpy(A.pass,contra);

                        printf("\nLa contrasenia  se ha cambiado a: %s\n",A.pass);

                        system("pause");
                        system("cls");
                        break;
                    case 0:
                        system("cls");
                        break;
                    default:
                        printf("Numero erroneo, ingrese uno valido\n\n");
                        break;
                    }
                }
                while(mod!=0);
                break;
            }
        }
        fseek(buffer, (-1) * sizeof(stUsuario), SEEK_CUR);
        fwrite(&A, sizeof(stUsuario), 1, buffer);
        fclose(buffer);
    }
}


void limpiarArregloDeListas(stCelda ADL[], int validos)
{
    for(int i = 0; i < validos; i++)
    {
        nodoListaCancion * aux = ADL[i].listaCanciones;
        while(aux != NULL)
        {
            nodoListaCancion * aBorrar = aux;
            aux = aux->siguiente;
            free(aBorrar);
        }
        ADL[i].listaCanciones = iniclista;
    }
}

/*void persistirCancionesEscuchadas(stCelda ADL[], int validos, char ArchivoEscuchadas[])
{
FILE * archi = fopen(ArchivoEscuchadas, "ab");
if(archi)
    {
    for(int i = 0; i < validos; i++)
        {
        nodoListaCancion * aux = ADL[i].listaCanciones;
        while(aux != NULL)
            {
            fwrite(&)
            }
        }
    }
}*/
