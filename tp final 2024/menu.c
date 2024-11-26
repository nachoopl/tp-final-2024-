#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "canciones.h"
#include "usuario.h"
#include "playlist.h"
#include "menu.h"
void menu()
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

    int cantidadUsuariosActivos = contarUsuariosActivos("usuario.dat");
    stCelda* ADL = (stCelda*) malloc(cantidadUsuariosActivos * sizeof(stCelda));
    int validos = 0;
    validos = pasarArchivoToADL("usuario.dat", ADL);
    validos = pasarArchivoPlaylistToADL("playlist.dat", ADL, validos, arbol);
    validos = pasarArchivoCancionesToADL("cancion.dat",ADL, validos);

    //limpiarArregloDeListas(ADL, validos);
    //mostrarADL(ADL, validos);
    //persistirCancionesEscuchadas(ADL, "escuchadas.dat", validos);
    //mostrarArchiEscuchadas("escuchadas.dat");

    int user, login, adm, listusuarios, usua;
    int idUsuario,idUsuariobaja,idcancion,idcancionbaja;
    char admin[20];
    char contraAdmin[20];
    char dato[20];
    char contraUsuario[20];
    stCancion canciones[100];
    int numCanciones = cargarCanciones("cancion.dat", canciones);

    do
    {
        puts("\n-----------------Gestion Musica-------------------------");
        printf("\n\nElija el tipo:(1/2/3/0): \n\n1. Administrador\n2. Usuario\n3. Registrarse\n0. Salir\n\nModo de usuario: ");
        fflush(stdin);
        scanf("%i", &user);
        system("cls");

        switch(user)
        {
        case 1: // Modo Administrador
            printf("Usuario de Admin: \n");
            fflush(stdin);
            scanf("%s",admin);
            if(strcmp(admin,"A")==0)
            {
                printf("\nIngrese contraseña: \n");
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
                                    fflush(stdin);
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
                                    fflush(stdin);
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
                                    fflush(stdin);
                                    validos= pasarArchivoPlaylistToADL("playlist.dat",ADL, validos,arbol);
                                    persistirCancionesEscuchadas(ADL, "escuchadas.dat", validos);
                                    mostrarArchiEscuchadas("escuchadas.dat");
                                    system("pause");
                                    system("cls");
                                    break;
                                case 5:
                                    // Muestra todos los usuarios registrados en el sistema
                                    listarUsuarios("usuario.dat");
                                    system("pause");
                                    system("cls");
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("Opción no válida.\n");
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
                                scanf("%i", &adm);
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

                                        C = mostrarDatosCancionBuscada("cancion.dat", idcancion);
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
                                    fflush(stdin);
                                    scanf("%i",&idcancionbaja);
                                    int buscarbaja=buscarCancionPorID("cancion.dat",idcancionbaja);
                                    if(buscarbaja==1)
                                    {

                                        C = mostrarDatosCancionBuscada("cancion.dat", idcancionbaja);
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
                                    // Modificación
                                    printf("ingrese el IDcancion a modificar: \n");
                                    fflush(stdin);
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
                                    MostrarArchivoCanciones("cancion.dat", C);
                                    break;
                                case 6:
                                    // Listados Canciones
                                    listarCanciones("cancion.dat");

                                    system("pause");
                                    system("cls");
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("Opción no válida.\n");
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
                            printf("Opción no válida.\n");
                            system("pause");
                            system("cls");
                            break;
                        }
                    }
                    while (adm != 0);
                }
                else
                {
                    printf("Contraseña incorrecta.\n");
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
            puts("\n------------------------------------------");
            printf("\n\nIngresa tu usuario: ");
            fflush(stdin);
            gets(dato);
            int buscar = buscarUsuarioPorNombre("usuario.dat", dato);
            A = UsuarioBuscado("usuario.dat", dato);

            if (buscar == 1)
            {
                printf("Ingresa la contrasenia: \n");
                fflush(stdin);
                gets(contraUsuario);

                while (strcmp(contraUsuario, A.pass) != 0)
                {
                    printf("Contrasenia incorrecta, ingresa nuevamente: \n");
                    fflush(stdin);
                    gets(contraUsuario);
                }

                printf("\nUsuario ingresado correctamente. Bienvenido, %s!\n", A.nombreUsuario);
                system("pause");
                int opcion;
                do
                {
                    system("cls");
                    printf("------ Menu Usuario: %s ------\n", A.nombreUsuario);
                    printf("1. Ver Perfil\n");
                    printf("2. Mostrar Playlist\n");
                    printf("3. Escuchar Cancion\n");
                    printf("4. Canciones Recomendadas\n");
                    printf("0. Cerrar Sesion\n");
                    printf("\nElige una opcion: ");
                    fflush(stdin);
                    scanf("%i", &opcion);

                    switch (opcion)
                    {
                    case 1: // Ver Perfil
                        system("cls");
                        printf("------ Perfil de Usuario ------\n");
                        mostrarUsuario(A);
                        system("pause");
                        break;

                    case 2: // Mostrar Playlist
                        system("cls");
                        mostrarPlaylist("playlist.dat", "cancion.dat", A.idUsuario);
                        system("pause");
                        break;

                    case 3: // Escuchar Cancion
                        system("cls");
                        int idCancionEscuchada;
                        printf("------ Escuchar Cancion ------\n");
                        printf("Ingresa el ID de la cancion: ");
                        fflush(stdin);
                        scanf("%i", &idCancionEscuchada);
                        escucharCancion("playlist.dat", "cancion.dat", A.idUsuario, idCancionEscuchada);
                        system("pause");
                        break;

                    case 4: // Canciones Recomendadas
                        system("cls");
                        cancionesRecomendadas("playlist.dat", "cancion.dat", A.idUsuario);
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
                }
                while (opcion != 0);
            }
            else
            {
                printf("Usuario inexistente.\n");
                system("pause");
            }

            system("cls");
            break;

        case 3: // Registrarse
        {
            char t='s';
            printf("Desea registrarse?(s/n)\n");
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

        case 0: // Salir
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opción no válida.\n");
            system("pause");
            system("cls");
            break;
        }
    }
    while (user != 0);
}

void escucharCancion(char ArchivoPlaylist[], char ArchivoCancion[], int idUsuario, int idCancion)
{
    FILE *archivoPlaylist = fopen(ArchivoPlaylist, "ab");
    FILE *archivoCancion = fopen(ArchivoCancion, "rb");
    stCancion cancion;
    stPlaylist nuevaPlaylist;

    if (archivoPlaylist && archivoCancion)
    {
        int encontrada = 0;

        while (fread(&cancion, sizeof(stCancion), 1, archivoCancion) > 0)
        {
            if (cancion.idCancion == idCancion && cancion.eliminado == 0)
            {
                encontrada = 1;
                printf("\nEscuchando cancion: %s - %s\n", cancion.titulo, cancion.artista);
                nuevaPlaylist.idUsuario = idUsuario;
                nuevaPlaylist.idCancion = idCancion;
                nuevaPlaylist.idPlaylist = obtenerUltimoIdPlaylist(ArchivoPlaylist) + 1;

                fwrite(&nuevaPlaylist, sizeof(stPlaylist), 1, archivoPlaylist);

                printf("La cancion se agregó a tu playlist.\n");
                break;
            }
        }

        if (!encontrada)
        {
            printf("Cancion no encontrada o eliminada.\n");
        }

        fclose(archivoPlaylist);
        fclose(archivoCancion);
    }
}

int obtenerUltimoIdPlaylist(char ArchivoPlaylist[])
{
    FILE *archivo = fopen(ArchivoPlaylist, "rb");
    stPlaylist aux;
    int ultimoId = 0;

    if (archivo)
    {
        while (fread(&aux, sizeof(stPlaylist), 1, archivo) > 0)
        {
            ultimoId = aux.idPlaylist;
        }
        fclose(archivo);
    }

    return ultimoId;
}

void cancionesRecomendadas(char ArchivoPlaylist[], char ArchivoCancion[], int idUsuario)
{
    FILE *archivoPlaylist = fopen(ArchivoPlaylist, "rb");
    FILE *archivoCancion = fopen(ArchivoCancion, "rb");
    stPlaylist playlist;
    stCancion cancion;
    char generoRecomendado[20];
    int encontrado = 0;

    if (archivoPlaylist && archivoCancion)
    {
        printf("\nCanciones recomendadas:\n");

        while (fread(&playlist, sizeof(stPlaylist), 1, archivoPlaylist) > 0)
        {
            if (playlist.idUsuario == idUsuario)
            {
                fseek(archivoCancion, 0, SEEK_SET);
                while (fread(&cancion, sizeof(stCancion), 1, archivoCancion) > 0)
                {
                    if (cancion.idCancion == playlist.idCancion && cancion.eliminado == 0)
                    {
                        strcpy(generoRecomendado, cancion.genero);
                        break;
                    }
                }

                fseek(archivoCancion, 0, SEEK_SET);

                while (fread(&cancion, sizeof(stCancion), 1, archivoCancion) > 0)
                {
                    if (strcmp(cancion.genero, generoRecomendado) == 0 && cancion.eliminado == 0)
                    {
                        if (!estaEnPlaylist(ArchivoPlaylist, idUsuario, cancion.idCancion))
                        {
                            printf("Recomendacion: %s - %s (Genero: %s)\n", cancion.titulo, cancion.artista, cancion.genero);
                            encontrado = 1;
                        }
                    }
                }
            }
        }

        if (!encontrado)
        {
            printf("No se encontraron canciones recomendadas para ti.\n");
        }

        fclose(archivoPlaylist);
        fclose(archivoCancion);
    }

}

int estaEnPlaylist(char ArchivoPlaylist[], int idUsuario, int idCancion)
{
    FILE *archivo = fopen(ArchivoPlaylist, "rb");
    stPlaylist playlist;

    if (archivo)
    {
        while (fread(&playlist, sizeof(stPlaylist), 1, archivo) > 0)
        {
            if (playlist.idUsuario == idUsuario && playlist.idCancion == idCancion)
            {
                fclose(archivo);
                return 1;
            }
        }
        fclose(archivo);
    }

    return 0;
}

int cargarCanciones(char archivoCancion[], stCancion canciones[])
{
    FILE* buffer = fopen("cancion.dat", "rb");
    int i = 0;

    if (buffer)
    {
        while (fread(&canciones[i], sizeof(stCancion), 1, buffer))
        {
            i++;
        }
        fclose(buffer);
    }

    return i;
}
void ordenarPorTitulo(stCancion canciones[], int numCanciones)
{
    int i, j, posMenor;
    stCancion aux;

    for (i = 0; i < numCanciones - 1; i++)
    {
        posMenor = i;
        for (j = i + 1; j < numCanciones; j++)
        {
            if (strcmp(canciones[j].titulo, canciones[posMenor].titulo) < 0)
            {
                posMenor = j;
            }
        }

        aux = canciones[i];
        canciones[i] = canciones[posMenor];
        canciones[posMenor] = aux;
    }
}
void ordenarPorGenero(stCancion canciones[], int numCanciones)
{
    int i, j;
    stCancion aux;

    for (i = 1; i < numCanciones; i++)
    {
        aux = canciones[i];
        j = i - 1;

        while (j >= 0 && strcmp(canciones[j].genero, aux.genero) > 0)
        {
            canciones[j + 1] = canciones[j];
            j--;
        }
        canciones[j + 1] = aux;
    }
}
void mostrarCanciones(stCancion canciones[], int numCanciones)
{
    for (int i = 0; i < numCanciones; i++)
    {
        printf("%i. %s - %s\n", i + 1, canciones[i].titulo, canciones[i].genero);
    }
}

void listarCanciones(char archivo[]) {
    stCancion canciones[100];
    int numCanciones = cargarCanciones(archivo, canciones);

    int opcion;
    printf("Seleccione el criterio de listado:\n");
    printf("1. Por Titulo (Ordenado alfabeticamente)\n");
    printf("2. Por Genero (Ordenado alfabeticamente)\n");
    printf("Opcion: ");
    fflush(stdin);
    scanf("%i", &opcion);

    switch (opcion) {
        case 1:
            ordenarPorTitulo(canciones, numCanciones);
            printf("\nCanciones ordenadas por titulo:\n");
            mostrarCanciones(canciones, numCanciones);
            break;
        case 2:
            ordenarPorGenero(canciones, numCanciones);
            printf("\nCanciones ordenadas por genero:\n");
            mostrarCanciones(canciones, numCanciones);
            break;
        default:
            printf("Opcion no valida.\n");
            break;
    }
}


int cargarUsuarios(char archivo[], stUsuario usuarios[]) {
    FILE* buffer = fopen(archivo, "rb");
    int i = 0;

    if (buffer) {
        while (fread(&usuarios[i], sizeof(stUsuario), 1, buffer)) {
            i++;
        }
        fclose(buffer);
    }

    return i;
}

void ordenarPorNombreUsuario(stUsuario usuarios[], int numUsuarios) {
    int i, j, posMenor;
    stUsuario aux;

    for (i = 0; i < numUsuarios - 1; i++) {
        posMenor = i;
        for (j = i + 1; j < numUsuarios; j++) {
            if (stricmp(usuarios[j].nombreUsuario, usuarios[posMenor].nombreUsuario) < 0) {
                posMenor = j;
            }
        }
        aux = usuarios[i];
        usuarios[i] = usuarios[posMenor];
        usuarios[posMenor] = aux;
    }
}

void mostrarUsuarios(stUsuario usuarios[], int numUsuarios) {
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].eliminado == 0) {
            printf("ID usuario: %i\n", usuarios[i].idUsuario);
            printf("Nombre: %s\n", usuarios[i].nombreUsuario);
            printf("------------------------------------\n");
        }
    }
}

void listarUsuarios(char archivo[]) {
    stUsuario usuarios[100];
    int numUsuarios = cargarUsuarios(archivo, usuarios);
    ordenarPorNombreUsuario(usuarios, numUsuarios);
    printf("\nUsuarios ordenados por nombre:\n");
    mostrarUsuarios(usuarios, numUsuarios);
}



int cargarPlaylist(char archivoPlaylist[], stPlaylist playlist[], int idUsuario) {
    FILE * archivo = fopen(archivoPlaylist, "rb");
    int i = 0;

    if (archivo) {
        while (fread(&playlist[i], sizeof(stPlaylist), 1, archivo)) {
            if (playlist[i].idUsuario == idUsuario) {
                i++;
            }
        }
        fclose(archivo);
    } else {
        printf("Error al abrir el archivo de playlist.\n");
    }

    return i;
}


void ordenarPorTituloP(stCancion canciones[], int numCanciones) {
    for (int i = 0; i < numCanciones - 1; i++) {
        for (int j = i + 1; j < numCanciones; j++) {
            if (stricmp(canciones[i].titulo, canciones[j].titulo) > 0) {
                stCancion temp = canciones[i];
                canciones[i] = canciones[j];
                canciones[j] = temp;
            }
        }
    }
}

void ordenarPorGeneroP(stCancion canciones[], int numCanciones) {
    for (int i = 0; i < numCanciones - 1; i++) {
        for (int j = i + 1; j < numCanciones; j++) {
            if (stricmp(canciones[i].genero, canciones[j].genero) > 0) {
                stCancion temp = canciones[i];
                canciones[i] = canciones[j];
                canciones[j] = temp;
            }
        }
    }
}

void mostrarPlaylist(char archivoPlaylist[], char archivoCancion[], int idUsuario) {
    stPlaylist playlist[100];  // Almacena canciones de la playlist del usuario
    stCancion canciones[100];  // Almacena todas las canciones disponibles
    stCancion cancionesPlaylist[100]; // Almacena solo las canciones de la playlist
    int numPlaylist = cargarPlaylist(archivoPlaylist, playlist, idUsuario);
    int numCanciones = cargarCanciones(archivoCancion, canciones);
    int numCancionesPlaylist = 0;

    if (numPlaylist == 0) {
        printf("No tienes canciones en tu playlist.\n");
        return;
    }

    // Copiar las canciones de la playlist al arreglo temporal
    for (int i = 0; i < numPlaylist; i++) {
        for (int j = 0; j < numCanciones; j++) {
            if (playlist[i].idCancion == canciones[j].idCancion) {
                cancionesPlaylist[numCancionesPlaylist++] = canciones[j];
            }
        }
    }

    // Solicitar al usuario el criterio de ordenamiento
    int opcion = seleccionarCriterioOrdenamiento();

    // Ordenar según la opción seleccionada
    if (opcion == 1) {
        ordenarPorTituloP(cancionesPlaylist, numCancionesPlaylist);
        printf("\nCanciones ordenadas por nombre:\n");
    } else if (opcion == 2) {
        ordenarPorGeneroP(cancionesPlaylist, numCancionesPlaylist);
        printf("\nCanciones ordenadas por genero:\n");
    }

    // Mostrar las canciones de la playlist
    printf("Canciones en la Playlist:\n");
    printf("------------------------------------\n");
    for (int i = 0; i < numCancionesPlaylist; i++) {
        printf("ID Cancion: %i\n", cancionesPlaylist[i].idCancion);
        printf("Titulo    : %s\n", cancionesPlaylist[i].titulo);
        printf("Artista   : %s\n", cancionesPlaylist[i].artista);
        printf("Genero    : %s\n", cancionesPlaylist[i].genero);
        printf("------------------------------------\n");
    }
}

int seleccionarCriterioOrdenamiento() {
    int opcion;
    do {
        printf("Seleccione el criterio de ordenamiento:\n");
        printf("1. Ordenar por Nombre de Cancion\n");
        printf("2. Ordenar por Genero\n");
        printf("Ingrese su opcion (1 o 2): ");
        fflush(stdin);
        scanf("%i", &opcion);

        if (opcion != 1 && opcion != 2) {
            printf("Opción invalida. Intente nuevamente.\n");
        }
    } while (opcion != 1 && opcion != 2);

    return opcion;
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
    FILE *archi = fopen("escuchadas.dat", "wb");

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
    FILE *archi = fopen("escuchadas.dat", "rb");

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
        printf("ID Cancion: %d\n", cancionesEscuchadas.idCancion);
        printf("Nombre Cancion: %s\n", cancionesEscuchadas.nombreCancion);
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

int contarUsuariosActivos(char ArchivoUsuario[])
{
    FILE* archi = fopen("usuario.dat", "rb");
    int cantidad = 0;

    if(archi)
    {
        stUsuario usuario;
        while (fread(&usuario, sizeof(stUsuario), 1, archi) > 0)
        {
            if (usuario.eliminado == 0)
            {
                cantidad++;
            }
        }

        fclose(archi);
    }
    return cantidad;
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

