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
    mostrarADL(ADL, validos);
    persistirCancionesEscuchadas(ADL, "escuchadas.dat", validos);
    //mostrarArchiEscuchadas("escuchadas.dat");

    int user, login, adm, listusuarios, usua;
    int idUsuario,idUsuariobaja,idcancion,idcancionbaja;
    char admin[20];
    char contraAdmin[20];
    char dato[20];
    char contraUsuario[20];

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

    if (buscar == 1) {
        printf("Ingresa la contrasenia: \n");
        fflush(stdin);
        gets(contraUsuario);

        while (strcmp(contraUsuario, A.pass) != 0) {
            printf("Contrasenia incorrecta, ingresa nuevamente: \n");
            fflush(stdin);
            gets(contraUsuario);
        }

        printf("\nUsuario ingresado correctamente. Bienvenido, %s!\n", A.nombreUsuario);
        system("pause");
            int opcion;
    do {
        system("cls");
        printf("------ Menu Usuario: %s ------\n", A.nombreUsuario);
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
            mostrarUsuario(A);
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
                int pos = buscarPosUsuario(ADL, A.idUsuario, validos);
                ordenamientoAlfabeticoUsuarionombre("usuario.dat", A, pos);
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
    } else {
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


