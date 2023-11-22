/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/

#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <stdio.h>
#define MAXELEM 40000
void ordenar(char palabras[][TAMTOKEN], int iEstadisticas[], int num) {
    int pasada, posicion;
    char aux[TAMTOKEN];
    int auxEstadisticas;

    for (pasada = 0; pasada < num - 1; pasada++) {
        for (posicion = 0; posicion < num - 1; posicion++) {
            if (strcmp(palabras[posicion], palabras[posicion + 1]) > 0) {
                // Realizar el intercambio para las palabras
                strcpy_s(aux, palabras[posicion]);
                strcpy_s(palabras[posicion], palabras[posicion + 1]);
                strcpy_s(palabras[posicion + 1], aux);

                // Tambi?n realizar el intercambio para las estad?sticas
                auxEstadisticas = iEstadisticas[posicion];
                iEstadisticas[posicion] = iEstadisticas[posicion + 1];
                iEstadisticas[posicion + 1] = auxEstadisticas;
            }
        }
    }
}

//Funciones publicas del proyecto
/*****************************************************************************************************************
    DICCIONARIO: Esta funcion crea el diccionario completo
    char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
    char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
    int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
    int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
    FILE* fp;
    char valores[MAXELEM];
    char pala[MAXELEM];
    iNumElementos = 0;
    int a = 0;
    int paal = 0;

    if (fopen_s(&fp, szNombre, "r") != 0) {
        printf("No se pudo abrir el archivo.\n");
        // Salir con c?digo de error
    }

    while (fgets(valores, sizeof(valores), fp) != NULL) {
        for (int i = 0; i < (strlen(valores)); i++) {
            if (valores[i] != ' ' && valores[i] != '(' && valores[i] != ')' && valores[i] != ',' &&
                valores[i] != ';' && valores[i] != '.' &&
                valores[i] != '*' && valores[i] != '}' &&
                valores[i] != '\n' &&
                valores[i] != '>' && valores[i] != '<') {
                pala[a] = valores[i];
                a++;


            }
            else if (a > 0) {
                pala[a] = '\0';
                _strlwr_s(pala);

                // Buscar si la palabra ya est? en el arreglo szPalabras
                int repetida = 0;
                for (int j = 0; j < iNumElementos; j++) {
                    if (strcmp(szPalabras[j], pala) == 0) {
                        repetida = 1;
                        iEstadisticas[j]++;
                        paal++;
                        break;
                    }
                }

                // Si no es repetida, agregarla al arreglo
                if (!repetida) {
                    strcpy_s(szPalabras[iNumElementos], pala);
                    iEstadisticas[iNumElementos] = 1;
                    iNumElementos++;
                    paal++;

                }

                a = 0;
            }
        }
    }

    int o = 0;
    ordenar(szPalabras, iEstadisticas, iNumElementos);
    fclose(fp);

}


/*****************************************************************************************************************
    ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
    Regresa las palabras ordenadas por su peso
    char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
    int		iNumSugeridas,						//Lista de palabras clonadas
    char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
    int		iEstadisticas[],					//Lista de las frecuencias de las palabras
    int		iNumElementos,						//Numero de elementos en el diccionario
    char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
    int		iPeso[],							//Peso de las palabras en la lista final
    int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void compararPalabras(char arreglo1[][50], int longitud1, char arreglo2[][50], int longitud2,char resultado[3300][TAMTOKEN]) {
    int k = 0;

    // Iterar sobre cada arreglo en arreglo1
    for (int i = 0; i < longitud1; i++) {
        // Iterar sobre cada palabra en el arreglo actual de arreglo1
        for (int j = 0; j < longitud2; j++) {
            // Comparar la palabra actual en arreglo1 con todas las palabras en arreglo2
            if (strcmp(arreglo1[i], arreglo2[j]) == 0) {
                // Si la palabra es igual, copiarla al resultado
                strcpy(resultado[k], arreglo1[i]);
                k++;
            }
        }
    }
}

void	ListaCandidatas(
    char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
    int		iNumSugeridas,						//Lista de palabras clonadas
    char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
    int		iEstadisticas[],					//Lista de las frecuencias de las palabras
    int		iNumElementos,						//Numero de elementos en el diccionario
    char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
    int		iPeso[],							//Peso de las palabras en la lista final
    int& iNumLista)							//Numero de elementos en la szListaFinal
{
    
    compararPalabras(szPalabrasSugeridas, iNumSugeridas, szPalabras, iNumElementos, szListaFinal);


}


/*****************************************************************************************************************
    ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
    char *	szPalabraLeida,						// Palabra a clonar
    char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
    int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void CopiaPalabrasGeneradas(
    char szPalabrasSugeridas[][TAMTOKEN], // Lista de palabras clonadas
    int iNumSugeridas,                    // N?mero de elementos en la lista
    char szPalabrasCopia[][TAMTOKEN],     // Nuevo arreglo de arreglos (destino)
    int& iNumCopia)                       // N?mero de elementos en la nueva lista (se actualizar?)
{
    iNumCopia = 0;

    for (int i = 0; i < iNumSugeridas; ++i)
    {
        strcpy(szPalabrasCopia[i], szPalabrasSugeridas[i]);
        iNumCopia++;
    }
}
void copiar(char* szpalabraleida, char aux[TAMTOKEN])
{
    int i;
    for (i = 0; i <= (strlen(szpalabraleida)); i++)
    {
        szpalabraleida[i] = aux[i];
    }
    szpalabraleida[i] = '\0';

}

void	ClonaPalabras(
    char* szPalabraLeida,						// Palabra a clonar
    char	szPalabrasSugeridas[][TAMTOKEN],//Lista de palabras clonadas
    int& iNumSugeridas)						//Numero de elementos en la lista
{
    char	szPalabras[3300][TAMTOKEN];
    char aux[TAMTOKEN];
    int i;
    int j = 0;
    iNumSugeridas = 0;
    int pasadas = 0;
    char abecedario[TAMTOKEN] = "abcdefghijklmn�opqrstuvwxyz�����";
    int longitud = strlen(szPalabraLeida);

    for (i = 0; i < longitud; i++)
    {
        aux[i] = szPalabraLeida[i];
    }
    aux[i] = '\0';
    //elimina una letra
    for (pasadas = 0; pasadas < longitud; pasadas++)
    {

        copiar(szPalabraLeida, aux);
        for (i = 0; i < longitud; i++)
        {
            if (i != pasadas)
            {
                szPalabraLeida[j] = aux[i];
                j++;
            }


        }
        szPalabraLeida[i - 1] = '\0';
        strcpy_s(szPalabras[iNumSugeridas], szPalabraLeida);
        iNumSugeridas++;
        j = 0;
    }
    //cambia de posicion las palabras
  
    
  
        for (j = 0; j < strlen(szPalabraLeida); j = j + 2)
        {
            if ((szPalabraLeida[j+1])=='\0')
            {
                j = j - 1;
                copiar(szPalabraLeida, aux);
                szPalabraLeida[j] = aux[j + 1];
                szPalabraLeida[j + 1] = aux[j];
                strcpy_s(szPalabras[iNumSugeridas], szPalabraLeida);
                iNumSugeridas++;
                
            }
            else
            {
                copiar(szPalabraLeida, aux);
                szPalabraLeida[j] = aux[j + 1];
                szPalabraLeida[j + 1] = aux[j];
                strcpy_s(szPalabras[iNumSugeridas], szPalabraLeida);
                iNumSugeridas++;
            }
            
        }
    //PONE UNA LETRA DEL ABECEARIO EN CADA UNA DE LAS LETRAS EXISTENTES
    for (pasadas = 0; pasadas < strlen(szPalabraLeida); pasadas++)
    {

        copiar(szPalabraLeida, aux);
        for (i = 0; i < strlen(abecedario); i++)
        {
            copiar(szPalabraLeida, aux);
            szPalabraLeida[pasadas] = abecedario[i];
            szPalabraLeida[j + 1] = '\0';
            strcpy_s(szPalabras[iNumSugeridas], szPalabraLeida);
            iNumSugeridas++;

        }


    }
    //PONE UNA LETRA DEL ABECEDARIO EN UN ESPACIO MAS DE LOS QUE ESTABAN
    for (pasadas = 0; pasadas < strlen(szPalabraLeida); pasadas++)
    {

        for (j = 0; j < strlen(abecedario); j++)
        {
            int a = 0;

            copiar(szPalabraLeida, aux);

            for (i = 0; i < strlen(szPalabraLeida) +1; i++)
            {
                if (i != pasadas)
                {
                    szPalabraLeida[i] = aux[a];
                    a++;
                }
                else
                {
                    szPalabraLeida[i] = abecedario[j];
                }


            }
            szPalabraLeida[strlen(szPalabraLeida) + 1] = '\0';
            strcpy_s(szPalabras[iNumSugeridas], szPalabraLeida);
            iNumSugeridas++;
        }


    }
    CopiaPalabrasGeneradas(szPalabras, iNumSugeridas, szPalabrasSugeridas, iNumSugeridas);
}