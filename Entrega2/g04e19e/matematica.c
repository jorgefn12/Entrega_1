#include "matematica.h"
#include "procesamiento_de_estados.h"
#include <stdlib.h>
#include <stdio.h>

double calcular_traza(const double** mat, size_t n){
	size_t i;
	double traza;

	for(i = 0; i < n; i++)
		traza += mat[i][i];
	return traza;
}

void sumar_int_a_matrizd(double** mat, size_t fil, size_t col, int suma){
	size_t i, j;

	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++)
			mat[i][j] += suma;
	}
}

void multip_int_a_matrizd(double** mat, size_t fil, size_t col, int mult){
	size_t i, j;

	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++)
			mat[i][j] *= mult;
	}
}

void trasponer_matrizd(double** mat1, size_t fil, size_t col,double** mat2){
	size_t i,j;

	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++){
			mat2[j][i] = mat1[i][j];
		}
	}
}

void imprimir_positividad_matriz(double ** mat, size_t fil, size_t col){
	status_matriz_t st_matriz;
	size_t i, j;

	st_matriz = ST_MATRIZ_INICIO;
	for(i = 0; i < fil; i++){
		for(j = 0; j < col; j++){
			switch(st_matriz){
				case ST_MATRIZ_INICIO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_POSITIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NEGATIVO;
					else
						st_matriz = ST_MATRIZ_CERO;
					break;
				case ST_MATRIZ_POSITIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_POSITIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					break;
				case ST_MATRIZ_NO_NEGATIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					break;
				case ST_MATRIZ_NEGATIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NEGATIVO;
					else
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					break;
				case ST_MATRIZ_NO_POSITIVO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_INDEFINIDO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					else
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					break;
				case ST_MATRIZ_CERO:
					if(mat[i][j] > 0)
						st_matriz = ST_MATRIZ_NO_NEGATIVO;
					else if(mat[i][j] < 0)
						st_matriz = ST_MATRIZ_NO_POSITIVO;
					else
						st_matriz = ST_MATRIZ_CERO;
					break;
				case ST_MATRIZ_INDEFINIDO:
					puts(MSJ_ST_MATRIZ_INDEFINIDO);
					return;
				default:
					puts(MSJ_ERR_GENERAL);
					return;
			}
		}
	}
	switch(st_matriz){
		case ST_MATRIZ_INICIO:
			puts(MSJ_ST_MATRIZ_INICIO);
			break;
		case ST_MATRIZ_POSITIVO:
			puts(MSJ_ST_MATRIZ_POSITIVO);
			break;
		case ST_MATRIZ_NO_NEGATIVO:
			puts(MSJ_ST_MATRIZ_NO_NEGATIVO);
			break;
		case ST_MATRIZ_NEGATIVO:
			puts(MSJ_ST_MATRIZ_NEGATIVO);
			break;
		case ST_MATRIZ_NO_POSITIVO:
			puts(MSJ_ST_MATRIZ_NO_POSITIVO);
			break;
		case ST_MATRIZ_CERO:
			puts(MSJ_ST_MATRIZ_CERO);
			break;
		case ST_MATRIZ_INDEFINIDO:
			puts(MSJ_ST_MATRIZ_INDEFINIDO);
			break;
		default:
			puts(MSJ_ERR_GENERAL);
	}
}