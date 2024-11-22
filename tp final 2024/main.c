#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "canciones.h"
#include "usuario.h"
#include "playlist.h"
///ARREGLODELISTAS
int alta(stCelda ADL[],int validos,stUsuario A,stCancion C);
int pasarArchivoToADL(char ArchivoUsuario[],stCelda ADL[]);
void mostrarADL(stCelda ADL [],int validos);
void cargarArchivoDecanciones(char ArchivoCancion []);
void cargarArchivoDeUsuario( char ArchivoUsuario[]);
void cargarPlaylistArchivo(char Archivoplaylist[]);
void mostrarArchivoPlaylist(char Archivoplaylist[],stPlaylist nuevaPlaylist);
int pasarArchivoPlaylistToADL(char Archivoplaylist[], stCelda ADL[], int validos, nodoArbolCancion *arbol);
void mostrarADL(stCelda ADL [],int validos);
int pasarArchivoCancionesToADL(char archivoCanciones[], stCelda ADL[], int validos);
int usuarioEscuchaCancion(int idUsuario, int idCancion);
void limpiarArregloDeListas(stCelda ADL[], int validos);
void persistirCancionesEscuchadas(stCelda ADL[], char ArchivoCancionesEscuchadas[], int validos);
void mostrarArchiEscuchadas(char ArchivoCancionesEscuchadas[]);
int main()
{
    stCancion C;
    stUsuario A;
    stPlaylist nuevaPlaylist;
    nodoArbolCancion* arbol=inicarbol();
    //cargarArchivoDecanciones("cancion.dat");
    //MostrarArchivoCanciones("cancion.dat", C);
    //cargarArchivoDeUsuario("usuario.dat");
    //mostrarArchivoUsuario("usuario.dat",A);
    //cargarPlaylistArchivo("playlist.dat");
    //mostrarArchivoPlaylist("playlist.dat", nuevaPlaylist);

//pasarArchiToArbolCanciones("cancion.dat", &arbol);
//inorder(arbol);

    stCelda ADL[100];
    int validos = 0;
    validos = pasarArchivoToADL("usuario.dat", ADL);
    validos = pasarArchivoPlaylistToADL("playlist.dat", ADL, validos, arbol);
    validos = pasarArchivoCancionesToADL("cancion.dat",ADL, validos);

    //limpiarArregloDeListas(ADL, validos);
    //mostrarADL(ADL, validos);
    persistirCancionesEscuchadas(ADL, "escuchadas.dat", validos);
   // mostrarArchiEscuchadas("escuchadas.dat");
    menu();
    return 0;
}
void menu()
{
    stUsuario A;
    stCancion C;
    int validos = 0;
    int user, login, adm, listusuarios, usua;
    int idUsuario,idUsuariobaja,idcancion,idcancionbaja;
    char admin[20];
    char contraAdmin[20];
    nodoArbolCancion* arbol=inicarbol();
    stCelda* ADL = malloc((validos + 1) * sizeof(stCelda));

    do
    {
        puts("\n-----------------Gestion Musica-------------------------");
        printf("\n\nElija el tipo:(1/2/3/0): \n\n1. Administrador\n2. Usuario\n3. Registrarse\n0. Salir\n\nModo de usuario: ");
        fflush(stdin);
        scanf("%d", &user);
        system("cls");

        switch(user)
        {
        case 1: // Modo Administrador
            printf("Usuario de Admin: \n");
            fflush(stdin);
            scanf("%s",admin);
            if(strcmp(admin,"A")==0)
            {
                printf("\nIngrese contrase�a: \n");
                scanf("%s",contraAdmin);
                if(strcmp(contraAdmin,"B")==0)
                {
                    system("cls");
                    puts("\n-_-_-_-_-_-_-_-");
                    printf("Bienvenido Admin\n");
                    do
                    {
                        printf("Elija donde acceder(1/2/0): \n\n1. Usuarios\n2. Canciones\n0. Regresar\n\nOpcion: ");
                        fflush(stdin);
                        scanf("%d", &adm);
                        system("cls");

                        switch(adm)
                        {
                        case 1:
                            do
                            {
                                printf("Admin->Usuario\n");
                                printf("Que quiere hacer(1/2/3/4/5/0): \n\n1. Alta\n2. Baja\n3. Modificacion\n4. Consulta\n5. Listados\n0. Regresar\n\nOpcion: ");
                                fflush(stdin);
                                scanf("%d", &usua);
                                system("cls");

                                switch(usua)
                                {
                                case 1: //Alta Usuario
                                    printf("ingrese el IdUsuario a dar de alta: \n");
                                    scanf("%i",&idUsuario);
                                    int buscar=buscarUsuarioPorID("usuario.dat",idUsuario);
                                    if(buscar==1)
                                    {
                                        A=mostrarDatosUsuarioBuscado("usuario.dat",idUsuario);
                                        if(A.eliminado==1)
                                        {
                                           altaUsuarioArchivo("usuario.dat",idUsuario);
                                            printf("Usuario reactivado correctamente.\n");
                                        }
                                    }
                                    else
                                    {
                                        char t='s';
                                        printf("\nUsuario inexistente.\n\n");
                                        printf("desea registrarlo?(s/n)\n");
                                        scanf(" %c",&t);
                                        if(t=='s')
                                        {
                                            A=cargarUnusuario();
                                            cargarUnusuarioArchivo("usuario.dat",A);
                                            printf("Usuario registrado exitosamente.\n");
                                        }
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 2: //Baja Usuario
                                    printf("ingrese el IdUsuario a dar de baja: \n");
                                    scanf("%i",&idUsuariobaja);
                                    int buscarbaja=buscarUsuarioPorID("usuario.dat",idUsuariobaja);
                                    if(buscarbaja==1)
                                    {
                                        A=mostrarDatosUsuarioBuscado("usuario.dat",idUsuariobaja);
                                        if(A.eliminado==0)
                                        {
                                           bajaUsuarioArchivo("usuario.dat",idUsuariobaja);
                                            printf("Usuario desactivado correctamente.\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\nUsuario inexistente.\n\n");
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 3: //Modificacion Usuario
                                    printf("ingrese el IdUsuario a modificar: \n");
                                    scanf("%i",&idUsuario);
                                    buscar=buscarUsuarioPorID("usuario.dat",idUsuario);
                                    if(buscar==1)
                                    {
                                        modificarDatosUsuario("usuario.dat", idUsuario);
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 4:
                                    printf("ARREGLO DE LISTAS: \n");
                                    fflush(stdin);
                                    validos= pasarArchivoPlaylistToADL("playlist.dat",ADL, validos,arbol);
                                    mostrarADL(ADL, validos);
                                    system("pause");
                                    system("cls");
                                    break;
                                case 5:
                                    // Muestra todos los usuarios registrados en el sistema
                                    mostrarArchivoUsuario("usuario.dat", A);
                                    system("pause");
                                    system("cls");
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("Opci�n no v�lida.\n");
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                            }
                            while (usua != 0);
                            break;

                        case 2: // Modo Administrador - Canciones
                            do
                            {
                                printf("Admin -> Canciones\n");
                                printf("Que quiere hacer(1/2/3/4/5/0): \n\n1. Alta\n2. Baja\n3. Modificacion\n5. Consulta\n6. Listados\n0. Regresar\n\nOpcion: ");
                                fflush(stdin);
                                scanf("%d", &adm);
                                system("cls");

                                switch(adm)
                                {
                                case 1:
                                    // Alta Cancion
                                    printf("ingrese el IdCancion a dar de alta: \n");
                                    scanf("%i",&idcancion);
                                   int buscarC=buscarCancionPorID("cancion.dat",idcancion);
                                    if(buscarC==1)
                                    {

                                        if(C.eliminado==1)
                                        {
                                           altaCancionArchivo("cancion.dat",idcancion);
                                            printf("cancion reactivada correctamente.\n");
                                        }
                                    }
                                    else
                                    {
                                        char r='s';
                                        printf("\cancion inexistente.\n\n");
                                        printf("desea registrarla?(s/n)\n");
                                        scanf(" %c",&r);
                                        if(r=='s')
                                        {
                                            C=cargarUnaCancion();
                                            cargarUnaCancionArchivo("cancion.dat",C);
                                            printf("Cancion registrada exitosamente.\n");
                                        }
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 2:
                                    // Baja Cancion
                                    printf("ingrese el IdCancion a dar de baja: \n");
                                    scanf("%i",&idcancionbaja);
                                   int buscarbaja=buscarCancionPorID("cancion.dat",idcancionbaja);
                                    if(buscarbaja==1)
                                    {

                                        if(C.eliminado==0)
                                        {
                                           bajaCancionesArchivo("cancion.dat",idcancionbaja);
                                            printf("cancion desactivada correctamente.\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("Cancion inexistente.\n");
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                    break;
                                case 3:
                                    // Modificaci�n
                                    printf("ingrese el IDcancion a modificar: \n");
                                    scanf("%i",&idcancion);
                                   buscarC=buscarCancionPorID("cancion.dat",idcancion);
                                    if(buscarC==1)
                                    {
                                        modificarDatosCancion("cancion.dat", idcancion);
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 5:
                                    // Consulta Cancion
                                    break;
                                case 6:
                                    // Listados Canciones
                                    MostrarArchivoCanciones("cancion.dat", C);
                                    system("pause");
                                    system("cls");
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("Opci�n no v�lida.\n");
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                            }
                            while (adm != 0);
                            break;

                        case 0: // Regresar
                            break;

                        default:
                            printf("Opci�n no v�lida.\n");
                            system("pause");
                            system("cls");
                            break;
                        }
                    }
                    while (adm != 0);
                }
                else
                {
                    printf("Contrase�a incorrecta.\n");
                    system("pause");
                    system("cls");
                }
            }
            else
            {
                printf("Usuario de administrador incorrecto.\n");
                system("pause");
                system("cls");
            }
            break;

        case 2: // Modo Usuario
            printf("Modo Usuario a�n no implementado.\n");
            system("pause");
            system("cls");
            break;

        case 3: // Registrarse
            printf("Funcionalidad de registro a�n no implementada.\n");
            system("pause");
            system("cls");
            break;

        case 0: // Salir
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opci�n no v�lida.\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while (user != 0);
}
int alta(stCelda ADL[],int validos,stUsuario A,stCancion C)
{
    nodoListaCancion* aux=crearNodo(C);
    int pos=buscarPosUsuario(ADL,A.idUsuario,validos);
    if(pos==-1)
    {
        A=cargarUsuarioADL(A.idUsuario);
        validos=agregarUsuario(ADL,A,validos);
        pos=validos-1;
    }
    ADL[pos].listaCanciones=AgregarEnOrdenPorNombreCancion(ADL[pos].listaCanciones,aux);
    return validos;
}

void cargarPlaylistArchivo(char Archivoplaylist[])
{
    FILE* archi=fopen("playlist.dat","ab");
    char control='s';
    stPlaylist nuevaPlaylist;
    int i=0;

    if(archi)
    {
        while(control=='s')
        {
            nuevaPlaylist.idPlaylist=i;
            printf("Ingrese el id del Usuario: ");
            fflush(stdin);
            scanf("%i", &nuevaPlaylist.idUsuario);

            int buscar=buscarUsuarioPorID("usuario.dat",nuevaPlaylist.idUsuario);
            if(buscar==1)

            {
                printf("Ingrese el id de la Cancion: ");
                fflush(stdin);
                scanf("%i", &nuevaPlaylist.idCancion);
                fwrite(&nuevaPlaylist, sizeof(stPlaylist), 1, archi);
                i++;
            }
            else
            {
                printf("\nUsuario inexistente");

            }
            printf("\ncargar otro?(s)\n");
            fflush(stdin);
            scanf(" %c",&control);

        }
    }
    fclose(archi);
}
void mostrarArchivoPlaylist(char Archivoplaylist[],stPlaylist nuevaPlaylist)
{
    FILE* archi=fopen("playlist.dat","rb");

    {
        if(archi)
        {
            while(fread(&nuevaPlaylist,sizeof(stPlaylist),1,archi)>0)
            {



                printf("IdPlaylits: %i\n",nuevaPlaylist.idPlaylist);
                printf("IdUsuario: %i\n",nuevaPlaylist.idUsuario);
                printf("IdCancion: %i\n",nuevaPlaylist.idCancion);
                printf("-----------------------------\n");
            }
        }
        fclose(archi);
    }
}


int pasarArchivoToADL(char ArchivoUsuario[], stCelda ADL[])
{
    FILE* archi = fopen(ArchivoUsuario, "rb");
    if (!archi)
    {
        printf("ERROR: No se pudo abrir el archivo de usuarios.\n");
        return 0;
    }

    stUsuario A;
    int validos = 0;
    while (fread(&A, sizeof(stUsuario), 1, archi) > 0)
    {
        if (A.eliminado == 0)
        {
            ADL[validos].A = A;
            ADL[validos].listaCanciones = iniclista();
            validos++;
        }
    }

    fclose(archi);
    return validos;
}

int pasarArchivoPlaylistToADL(char Archivoplaylist[], stCelda ADL[], int validos, nodoArbolCancion *arbol)
{
    FILE * archi = fopen(Archivoplaylist, "rb");
    if (archi == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo de playlists\n");
        return validos;
    }
    stPlaylist playlist;
    while (fread(&playlist, sizeof(stPlaylist), 1, archi) > 0)
    {
        int pos = buscarPosUsuario(ADL, playlist.idUsuario, validos);
        if (pos != -1)
        {
            nodoArbolCancion * cancionBuscada = buscarCancion(arbol, playlist.idCancion);
            if (cancionBuscada != NULL)
            {
                nodoListaCancion * nuevoNodo = crearNodo(cancionBuscada->dato);
                ADL[pos].listaCanciones = AgregarEnOrdenPorNombreCancion(ADL[pos].listaCanciones, nuevoNodo);
            }
        }
    }

    fclose(archi);
    return validos;
}

int pasarArchivoCancionesToADL(char archivoCanciones[], stCelda ADL[], int validos)
{
    FILE *archi = fopen(archivoCanciones, "rb");
    if (!archi)
    {
        printf("Error al abrir el archivo %s \n", archivoCanciones);
        return validos;
    }

    stCancion cancion;
    while (fread(&cancion, sizeof(stCancion), 1, archi) > 0)
    {
        for (int i = 0; i < validos; i++)
        {

            if (usuarioEscuchaCancion(ADL[i].A.idUsuario, cancion.idCancion))
            {
                nodoListaCancion *nuevoNodo = crearNodo(cancion);
                ADL[i].listaCanciones = AgregarEnOrdenPorNombreCancion(ADL[i].listaCanciones, nuevoNodo);
            }
        }
    }

    fclose(archi);
    return validos;
}

int usuarioEscuchaCancion(int idUsuario, int idCancion)
{
    FILE *archi = fopen("playlist.dat", "rb");
    if (archi == NULL)
    {
        return 0;
    }

    stPlaylist playlist;
    while (fread(&playlist, sizeof(stPlaylist), 1, archi) > 0)
    {

        if (playlist.idUsuario == idUsuario && playlist.idCancion == idCancion)
        {
            fclose(archi);
            return 1;
        }
    }

    fclose(archi);
    return 0;
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
        ADL[i].listaCanciones = iniclista();
    }
}

void persistirCancionesEscuchadas(stCelda ADL[], char ArchivoCancionesEscuchadas[], int validos)
{
    FILE *archi = fopen("escuchadas.dat", "ab");

    if (archi == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo %s\n", ArchivoCancionesEscuchadas);
        return;
    }

    for (int i = 0; i < validos; i++)
    {
        nodoListaCancion *aux = ADL[i].listaCanciones;

        while (aux != NULL)
        {
            stCancionesEscuchadas cancionesEscuchadas;
            cancionesEscuchadas.idUsuario = ADL[i].A.idUsuario;
            strcpy(cancionesEscuchadas.nombreUsuario, ADL[i].A.nombreUsuario);

            cancionesEscuchadas.idCancion = aux->dato.idCancion;
            strcpy(cancionesEscuchadas.nombreCancion, aux->dato.titulo);

            fwrite(&cancionesEscuchadas, sizeof(stCancionesEscuchadas), 1, archi);
            aux = aux->siguiente;
        }
    }

    fclose(archi);

}

void mostrarArchiEscuchadas(char ArchivoCancionesEscuchadas[])
{
    FILE *archi = fopen("escuchadas.dat" , "rb");

    if (archi == NULL)
    {
        printf("ERROR: No se pudo abrir el archivo %s\n", ArchivoCancionesEscuchadas);
        return;
    }

    stCancionesEscuchadas cancionesEscuchadas;
    printf("\nArchivo datos de canciones escuchadas:\n");
    printf("---------------------------------\n");

    while (fread(&cancionesEscuchadas, sizeof(stCancionesEscuchadas), 1, archi) > 0)
    {
        printf("ID Usuario: %d\n", cancionesEscuchadas.idUsuario);
        printf("Nombre Usuario: %s\n", cancionesEscuchadas.nombreUsuario);
        printf("ID Canci�n: %d\n", cancionesEscuchadas.idCancion);
        printf("Nombre Canci�n: %s\n", cancionesEscuchadas.nombreCancion);
        printf("-----------------------------\n");
    }

    fclose(archi);

}


void mostrarADL(stCelda ADL[], int validos)
{
    for (int i = 0; i < validos; i++)
    {
        printf("\nID Usuario: %i", ADL[i].A.idUsuario);
        printf("\nNombre de Usuario: %s", ADL[i].A.nombreUsuario);

        if (ADL[i].listaCanciones == NULL)
        {
            printf("\nSin canciones.\n");
        }
        else
        {
            printf("\nCanciones:\n");
            nodoListaCancion *aux = ADL[i].listaCanciones;
            while (aux != NULL)
            {
                printf("  - ID Cancion: %i, Titulo: %s\n", aux->dato.idCancion, aux->dato.titulo);
                aux = aux->siguiente;
            }
        }
        printf("------------------------------------\n");
    }
}

void cargarArchivoDecanciones(char ArchivoCancion [])
{
    FILE* archi=fopen("cancion.dat","ab");
    char control='s';
    stCancion C;
    if(archi)
    {
        while(control=='s')
        {
            C=cargarUnaCancion();
            fwrite(&C,sizeof(stCancion),1,archi);
            printf("cargar mas?(s)\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
    fclose(archi);
}

void cargarArchivoDeUsuario( char ArchivoUsuario[])
{
    FILE* archi=fopen("usuario.dat","ab");
    char control='s';
    stUsuario A;
    if(archi)
    {
        while(control=='s')
        {
            A=cargarUnusuario();
            fwrite(&A,sizeof(stUsuario),1,archi);
            printf("cargar mas?(s)\n");
            fflush(stdin);
            scanf(" %c",&control);
        }
    }
    fclose(archi);
}
