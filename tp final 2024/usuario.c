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
        if(A.eliminado == 1)
    {
        printf("\n eliminado: si");
    }
    else
        {
        printf("eliminado: no");
        }
    puts("\n-----------------------");
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
                mostrarUsuario(A);
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
                mostrarUsuario(A);
                A.eliminado = 0;
                fseek(archi, (-1) * sizeof(stUsuario), 1);
                fwrite(&A, sizeof(stUsuario), 1, archi);

                break;
            }
        }
        fclose(archi);
    }
}


stUsuario mostrarDatosUsuarioBuscado(char ArchivoUsuario[], int dato) {
    stUsuario A;
    A.idUsuario = -1;
    FILE * buffer = fopen(ArchivoUsuario, "rb");

    if (buffer) {
        while (fread(&A, sizeof(stUsuario), 1, buffer) > 0) {
            if (A.idUsuario == dato) {
                fclose(buffer);
                return A;
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

void modificarDatosUsuario(char ArchivoUsuario[], int dato)
{
    int mod, edad, flag = 0;
    char contra[20];
    char nombre[20];
    FILE* buffer = fopen("usuario.dat", "r+b");
    stUsuario A;

    if (buffer)
    {
        while (fread(&A, sizeof(stUsuario), 1, buffer) == 1)
        {
            if (A.idUsuario == dato)
            {
                do
                {
                    puts("\n-------------------MODIFICAR USUARIO-----------------------");
                    mostrarUsuario(A);
                    printf("Elija el dato a modificar(1/2/3/0): \n\n1. Nombre\n2. Nacimiento\n3.Contrasenia\n0. Regresar\n\nOpcion: ");
                    fflush(stdin);
                    scanf("%d", &mod);

                    switch (mod)
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
                        while (edad > 2010)
                        {
                            printf("\nNo puedes registrarte siendo menor de 14: ");
                            fflush(stdin);
                            scanf("%d", &edad);
                        }
                        A.anioNacimiento = edad;
                        printf("\nLa edad se ha cambiado a: %i\n", A.anioNacimiento);
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        printf("\nIngrese la nueva contrasenia(min 6 caracteres): ");
                        fflush(stdin);
                        scanf("%s", contra);
                        while (strlen(contra) <= 6)
                        {
                            printf("ERROR: La contrasenia debe tener más de 6 caracteres. Ingrese una contrasenia valida: ");
                            fflush(stdin);
                            scanf("%s", contra);
                        }
                        strcpy(A.pass, contra);

                        printf("\nLa contrasenia  se ha cambiado a: %s\n", A.pass);

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
                } while (mod != 0);

                fseek(buffer, -sizeof(stUsuario), SEEK_CUR);
                fwrite(&A, sizeof(stUsuario), 1, buffer);
                flag = 1;
                break;
            }
        }

        fclose(buffer);
    }

}


int buscarUsuarioPorNombre(char ArchivoUsuario[], char nombreUsuario[]) // Funcion que busca un usuario por id en el archivo de usuarios
{
    stUsuario A;
    int flag=0;
    FILE *buffer=fopen(ArchivoUsuario, "rb");
    if(buffer)
    {
        while(fread(&A, sizeof(stUsuario), 1, buffer)>0)
        {
            if(strcmp(A.nombreUsuario,nombreUsuario)==0)
            {
                flag=1;
            }
        }
        fclose(buffer);
    }
    return flag;
}

stUsuario UsuarioBuscado(char ArchivoUsuario[], char usuario[])
{
    stUsuario A;
    FILE *buffer=fopen(ArchivoUsuario, "rb");
    if(buffer)
    {
        while(fread(&A, sizeof(stUsuario), 1, buffer)>0)
        {
            if(strcmp(A.nombreUsuario, usuario) == 0)
            {
                return A;
            }
        }
        fclose(buffer);
    }
    return A;
}


void menuLoginExitoso(stUsuario usuarioLogueado, char ArchivoPlaylist[], char ArchivoCancion[])
{
    int opcion;
    do {
        system("cls");
        printf("------ Menu Usuario: %s ------\n", usuarioLogueado.nombreUsuario);
        printf("1. Ver Perfil\n");
        printf("2. Mostrar Playlist\n");
        printf("3. Escuchar Cancion\n");
        printf("4. Canciones Recomendadas\n");
        printf("0. Cerrar Sesion\n");
        printf("\nElige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
        case 1: // Ver Perfil
            system("cls");
            printf("------ Perfil de Usuario ------\n");
            mostrarUsuario(usuarioLogueado);
            system("pause");
            break;

        case 2: // Mostrar Playlist
            system("cls");
            int ordenarPor;
            printf("------ Mostrar Playlist ------\n");
            printf("1. Ordenar por Nombre\n");
            printf("2. Ordenar por Genero\n");
            printf("Elige una opcion: ");
            fflush(stdin);
            scanf("%i", &ordenarPor);

            if (ordenarPor == 1) {
                //mostrarPlaylistOrdenadaPorNombre(ArchivoPlaylist, ArchivoCancion, usuarioLogueado.idUsuario); // Función que tú implementarías
            } else if (ordenarPor == 2) {
                //mostrarPlaylistOrdenadaPorGenero(ArchivoPlaylist, ArchivoCancion, usuarioLogueado.idUsuario); // Función que tú implementarías
            } else {
                printf("Opcion invalida.\n");
            }
            system("pause");
            break;

        case 3: // Escuchar Cancion
            system("cls");
            printf("------ Escuchar Cancion ------\n");
            printf("Ingresa el ID de la cancion: ");
            int idCancion;
            scanf("%d", &idCancion);
            //agregarCancionAPlaylist(ArchivoPlaylist, usuarioLogueado.idUsuario, idCancion); // Implementar para agregar canciones a la playlist
            system("pause");
            break;

        case 4: // Canciones Recomendadas
            system("cls");
            printf("------ Canciones Recomendadas ------\n");
            //mostrarCancionesRecomendadas(ArchivoPlaylist, ArchivoCancion, usuarioLogueado.idUsuario); // Implementar algoritmo de recomendación
            system("pause");
            break;

        case 0:
            printf("Cerrando sesion...\n");
            break;

        default:
            printf("Opcion invalida. Intenta nuevamente.\n");
            system("pause");
            break;
        }
    } while (opcion != 0);
}
