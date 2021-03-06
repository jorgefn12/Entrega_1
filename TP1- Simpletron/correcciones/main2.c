
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POS_ARGV0 0
#define POS_ARGV1 1
#define POS_ARGV2 2
#define POS_ARGV3 3
#define POS_ARGV4 4
#define POS_ARGV5 5
#define POS_ARGV6 6
#define POS_ARGV7 7
#define POS_ARGV8 8
#define POS_ARGV9 9
#define POS_ARGV10 10

#define DEFAULT_M 50
#define CANT_MAX_ARG 11
#define CANT_MIN_ARG 2
#define INIT_INSTRUCCIONES 0
#define MIN_PALABRA -9999
#define MAX_PALABRA 9999
#define MAX_INSTRICCIONES 200
#define MAX_STR 200
#define CANT_MAX_M 200

/*ARGUMENTOS*/
#define CLA_AYUDA "-h"
#define CLA_M "-m"
#define CLA_I "-i"
#define CLA_I_DEFAULT "-"
#define CLA_IF "-if"
#define CLA_IF_OPT_TXT "txt"
#define CLA_IF_OPT_BIN "bin"
#define CLA_O "-o"
#define CLA_OF "-of"

#define INICIO_COMENTARIO ";"
#define STR_STDIN "stdin"
#define STR_STDOUT "stdout"
#define FINALIZAR_CARGA "-99999\n"
#define NOMBRE_GENERICO_ARCHIVO_BIN "dump"

/*constantes de ejecutar_codigo*/
#define LEER 10
#define ESCRIBIR 11
#define CARGAR 20
#define GUARDAR 21
#define PCARGAR 22
#define PGUARDAR 23
#define SUMAR 30
#define RESTAR 31
#define DIVIDIR 32
#define MULTIPLICAR 33
#define JMP 40
#define JMPNEG 41
#define JMPZERO 42
#define JNZ 43
#define DJNZ 44
#define HALT 45

/*MENSAJES DE AYUDA*/
#define MSJ_AYUDA_TITULO "------------------------------AYUDA------------------------------"
#define MSJ_AYUDA_M1 "OPCION |N|: Simpletron tiene una memoria de N palabras. Si no se da el argumento, por omisión tendrá 50 palabras. El maximo es de 200 palabras"
#define MSJ_AYUDA_I1 "OPCION |ARCHIVO|: El programa se leerá del archivo pasado como opción, en caso contrario, de stdin."
#define MSJ_AYUDA_IF1 "OPCION |BIN|: El archivo de entrada se entenderá como una secuencia binaria de enteros que representan las palabras que forman el programa."
#define MSJ_AYUDA_IF2 "OPCION |TXT|: El archivo de entrada se interpretará como secuencia de números, cada uno en una única línea."
#define MSJ_AYUDA_O1 "OPCION |ARCHIVO|: El dump se hará en el archivo pasado como opción, si no pasa el argumento, el volcado se hará por stdout."
#define MSJ_AYUDA_OF1 "OPCION |BIN|: El volcado se hará en binario guardando cada elemento de la estructura del Simpletron, además de la memoria."
#define MSJ_AYUDA_OF2 "OPCION |TXT|: El volcado se hará en formato de texto imprimiendo los registros y la memoria."

/*MENSAJES DE ERRORES*/
#define MSJ_MAS_AYUDA "Ingrese -h para mas ayuda"
#define MSJ_ERROR "Ocurrio un error"
#define MSJ_ERROR_IF_NO_VALIDO "El ingreso de archivo de entrada es invalido"
#define MSJ_ERROR_ARCHIVO_I_NO_INGRESADO "No se ingreso el archivo de entrada"
#define MSJ_ERROR_IF_NO_INGRESADO "No se ingreso el tipo de archivo de entrada"
#define MSJ_ERROR_OF_NO_VALIDO "El ingreso de archivo de salida es invalido"
#define MSJ_ERROR_OF_NO_INGRESADO "No se ingreso el tipo de archivo de salida"
#define MSJ_ERROR_CANT_ARG "La cantidad de argumentos ingresados no es valido"
#define MSJ_ERROR_ARCHIVO_NO_ENCONTRADO "El archivo no existe u ocurrio un error al abrirlo"
#define MSJ_ERROR_PTR_NULO "Puntero nulo"
#define MSJ_ERROR_MEM "Error de memoria"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_ERROR_M_NO_VALIDO "El valor de memoria asignado es invalido"
#define MSJ_ERROR_ESCRIBIR_BIN "Error al escribir el archivo bin"
#define MSJ_ERROR_CAD_NO_ES_ENTERO "La cadena contiene carácteres no numericos"
#define MSJ_ERROR_PALABRA_FUERA_DE_RANGO "La palabra excede el rango admitido por Simpletron [-9999;+9999]"
#define MSJ_ERROR_SEGMENTATION_FAULT "Se intentó acceder a memoria que Simpletron no solicitó"
#define MSJ_ERROR_CAD_NO_LEIDA "No pudo leer el valor ingresado"
#define MSJ_ERROR_OPCODE_INVALIDO "El código de instrucción no es válido"
#define MSJ_ERROR_MAX_INSTR_SUPERADO "La cantidad de instrucciones operadas alcanzó el máximo admitido"

/*EJECUCION CODIGO*/
#define MSJ_COMIENZO_EJECUCION "******** INICIO DE EJECUCION DEL SIMPLETRON *******"
#define MSJ_FIN_EJECUCION "********* FIN DE EJECUCION DEL SIMPLETRON *********"
#define MSJ_INGRESO_PALABRA "Ingrese una palabra: "
#define MSJ_IMPRIMIR_PALABRA "Contenido de la posición"

/*DUMP*/
#define DUMP_MSJ_INICIO "\nREGISTROS:"
#define DUMP_MSJ_ACUMULADOR "acumulador: "
#define DUMP_MSJ_PROGRAM_COUNTER "program counter: "
#define DUMP_MSJ_INSTRUCCION "instruccion: "
#define DUMP_MSJ_OPCODE "opcode: "
#define DUMP_MSJ_OPERANDO "operando: "
#define DUMP_MSJ_MEMORIA "\nMEMORIA"

typedef enum {
    ST_OK,
    ST_HELP,
    ST_ERROR_CANT_ARG,
    ST_ERROR_PTR_NULO,
    ST_ERROR_ARCHIVO_I_NO_INGRESADO,
    ST_ERROR_IF_NO_VALIDO,
    ST_ERROR_IF_NO_INGRESADO,
    ST_ERROR_OF_NO_VALIDO,
    ST_ERROR_OF_NO_INGRESADO,
    ST_ERROR_ARCHIVO_NO_ENCONTRADO,
    ST_ERROR_MEM,
    ST_ERROR_M_INVALIDO,
    /*status de ejecutar_codigo*/
    ST_ERROR_CAD_NO_ES_ENTERO,
    ST_ERROR_PALABRA_FUERA_DE_RANGO,
    ST_ERROR_SEGMENTATION_FAULT,
    ST_ERROR_CAD_NO_LEIDA,
    ST_ERROR_OPCODE_INVALIDO,
    ST_ERROR_MAX_INSTR_SUPERADO,
    ST_ERROR_ESCRIBIR_BIN
} status_t;

typedef enum {
    TRUE, FALSE
} bool_t;

typedef enum {
    ARCHIVO_BIN,
    ARCHIVO_TXT,
    ARCHIVO_DEFAULT
} archivo_t;

typedef struct {
    int * memoria;
    /*opcode, operando*/
    long acumulador;
    int program_counter;
    size_t cantidad_memoria;
    int *opcode;
    int *operando;
    int instruccion; /*memoria[program_counter]*/
} palabras_s;

/*Validacion*/
status_t validacion_cla(int argc, char **argv, size_t *m, char *archivo_i, archivo_t *tipo_archivo_i, char *archivo_f, archivo_t *tipo_archivo_f);
/*Carga de estructura*/
status_t leer_archivo(char *nombre_archivo_entrada, const archivo_t tipo_archivo_entrada, palabras_s *palabra);
status_t cargar_estructura_txt(palabras_s** palabra, char *nombre_archivo_entrada);
status_t cargar_estructura_bin(palabras_s* palabra, char* nombre_archivo_entrada);
status_t cargar_estructura_stdin(palabras_s *palabras);
/*Imprimir*/
void imprimir_ayuda();
void imprimir_errores(status_t status);
status_t imprimir_dump_por_stdout_o_txt(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida);
status_t dump(archivo_t tipo_archivo_salida, char* nombre_archivo_salida, palabras_s palabra);
status_t imprimir_dump_bin(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida);
/*Acumulador*/
status_t ejecutar_codigo();

int main(int argc, char** argv) {
    status_t status;
    char archivo_entrada[MAX_STR], archivo_salida[MAX_STR];
    archivo_t tipo_archivo_entrada, tipo_archivo_salida;
    palabras_s palabra;

    palabra.program_counter = 0;
    palabra.acumulador = 0;

    status = validacion_cla(argc, argv, &palabra.cantidad_memoria, archivo_entrada, &tipo_archivo_entrada, archivo_salida, &tipo_archivo_salida);
    if (status != ST_OK) {
        imprimir_errores(status);
        return EXIT_FAILURE;
    }

    printf("nombre archivo f = %s\n", archivo_salida);

    status = leer_archivo(archivo_entrada, tipo_archivo_entrada, &palabra);
    if (status != ST_OK)
        imprimir_errores(status);
    else {
        status = dump(tipo_archivo_salida, archivo_salida, palabra);
        if (status != ST_OK)
            imprimir_errores(status);
    }
    free(palabra.memoria);

    return EXIT_SUCCESS;
}

/*Esta funcion valida los argumentos pasados por la linea de comandos
 *El ingreso de argumentos en este caso no deben tener un orden especifico*/
status_t validacion_cla(int argc, char **argv, size_t *m, char *archivo_i, archivo_t *tipo_archivo_i, char *archivo_f, archivo_t *tipo_archivo_f) {
    size_t i;
    char * p;
    bool_t encontrado = FALSE, encontrado_of = FALSE;

    if (argc > CANT_MAX_ARG || argc < CANT_MIN_ARG)
        return ST_ERROR_CANT_ARG;

    if (argv == NULL || m == NULL || archivo_i == NULL || tipo_archivo_i == NULL || archivo_f == NULL || tipo_archivo_f == NULL)
        return ST_ERROR_PTR_NULO;

    /*-----------------------------AYUDA-----------------------------
     * simpletron -h
     * Cuando se pide una ayuda solo se debe ingresar el comando de ayuda y nada mas*/
    if (argc == CANT_MIN_ARG && (strcmp(argv[POS_ARGV1], CLA_AYUDA)) == 0)
        return ST_HELP;

    /*-----------------------------MEMORIA-----------------------------
     * ./simpletron -m 23...
     * Si no se ingresa este argumento, por defecto sera de 50 palabras*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-m" en argv*/
        if (strcmp(argv[i], CLA_M) == 0) {
            *m = strtol(argv[i + 1], &p, 10);
            /* Se comprueba que sea un entero positivo menor al maximo*/
            if (*m > CANT_MAX_M || *m < 0) {
                return ST_ERROR_M_INVALIDO;
            }
            break;
        } else {
            /*Si no se encuentra se asigna 50 por default*/
            *m = DEFAULT_M;
        }
    }

    /*-----------------------------ARCHIVO I-----------------------------
     * Se obtiene el archivo pasado por linea de comandos*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-i" en argv*/
        if ((strcmp(argv[i], CLA_I)) == 0) {
            if ((strcmp(argv[i + 1], CLA_I_DEFAULT)) == 0) {
                *tipo_archivo_i = ARCHIVO_DEFAULT;
                memcpy(archivo_i, STR_STDIN, strlen(STR_STDIN) + 1);
            } else {
                /*Guardo el nombre del archivo*/
                memcpy(archivo_i, argv[i + 1], strlen(argv[i + 1]) + 1);
            }
            encontrado = TRUE;
            break;
        }
    }
    /*Si no se encontro el argumento -i*/
    if (encontrado != TRUE)
        return ST_ERROR_ARCHIVO_I_NO_INGRESADO;
    encontrado = FALSE;


    /*-----------------------------IF-----------------------------
     * Se obtiene si el tipo de archivo de entrada sera interpretado como bin o txt*/
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-if" en argv*/
        if (strcmp(argv[i], CLA_IF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_OPT_BIN)) == 0) {
                *tipo_archivo_i = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_OPT_TXT)) == 0) {
                *tipo_archivo_i = ARCHIVO_TXT;
            } else
                return ST_ERROR_IF_NO_VALIDO;
            encontrado = TRUE;
            break;
        }
    }

    if (encontrado != TRUE)
        /*Si no se encuentra el argumento "-if"*/
        return ST_ERROR_IF_NO_INGRESADO;
    encontrado = FALSE;

    /*-----------------------------O-----------------------------
     * No es obligatorio ingresar esta opcion */
    for (i = 1; i < argc; i++) {
        /*Se busca el argumento "-o" en argv*/
        if ((strcmp(argv[i], CLA_O)) == 0) {
            /*Copio el nombre del archivo de salida*/
            memcpy(archivo_f, argv[i + 1], strlen(argv[i + 1]) + 1);
            encontrado = TRUE;
            break;
        }
    }

    /*Si no se encontro el argumento o se tomara como default stdout*/
    if (encontrado != TRUE) {
        puts("no encontrado o");
        *tipo_archivo_f = ARCHIVO_DEFAULT;
        memcpy(archivo_f, STR_STDOUT, strlen(STR_STDOUT) + 1);
    }

    /*-----------------------------OF-----------------------------
     * Se obtiene si el tipo de archivo de salida sera interpretado como bin o txt*/
    /*Si se ingreso -o, se debe ingresar -of*
     *si no se ingreso -o, se puede ingresar -of*/
    for (i = 0; i < argc; i++) {
        /*Se busca el argumento "-of" en argv*/
        if (strcmp(argv[i], CLA_OF) == 0) {
            /*Se busca el tipo de archivo de entrada: txt, bin*/
            if ((strcmp(argv[i + 1], CLA_IF_OPT_BIN)) == 0) {
                *tipo_archivo_f = ARCHIVO_BIN;
            } else if ((strcmp(argv[i + 1], CLA_IF_OPT_TXT)) == 0) {
                *tipo_archivo_f = ARCHIVO_TXT;
            } else
                return ST_ERROR_OF_NO_VALIDO;
            encontrado_of = TRUE;
            break;
        }
    }
    if (encontrado != TRUE && encontrado_of != TRUE)
        *tipo_archivo_f = ARCHIVO_DEFAULT; /*por defecto se interpreta como stdout,
                                        sólamente si no se ingreso -o"*/

    else if (encontrado == TRUE && encontrado_of != TRUE)
        /*Si no se encuentra el argumento "-of" y sí se ingresa "-o"*/
        return ST_ERROR_OF_NO_INGRESADO;

    return ST_OK;
}

void imprimir_errores(status_t status) {
    switch (status) {
        case ST_ERROR_CANT_ARG:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_CANT_ARG, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_I_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ARCHIVO_I_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_IF_NO_VALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_IF_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_IF_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OF_NO_VALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OF_NO_INGRESADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OF_NO_INGRESADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_ARCHIVO_NO_ENCONTRADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ARCHIVO_NO_ENCONTRADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_PTR_NULO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_PTR_NULO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_MEM:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_MEM, MSJ_MAS_AYUDA);
        case ST_HELP:
            imprimir_ayuda();
            break;
        case ST_ERROR_M_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_M_NO_VALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_CAD_NO_ES_ENTERO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_CAD_NO_ES_ENTERO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_PALABRA_FUERA_DE_RANGO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_PALABRA_FUERA_DE_RANGO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_SEGMENTATION_FAULT:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_SEGMENTATION_FAULT, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_CAD_NO_LEIDA:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_CAD_NO_LEIDA, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_OPCODE_INVALIDO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_OPCODE_INVALIDO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_MAX_INSTR_SUPERADO:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_MAX_INSTR_SUPERADO, MSJ_MAS_AYUDA);
            break;
        case ST_ERROR_ESCRIBIR_BIN:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR_ESCRIBIR_BIN, MSJ_MAS_AYUDA);
            break;
        default:
            fprintf(stderr, "%s. %s\n", MSJ_ERROR, MSJ_MAS_AYUDA);
    }
}
status_t leer_archivo(char *nombre_archivo_entrada, const archivo_t tipo_archivo_entrada, palabras_s *palabra) {
    status_t status;

    switch (tipo_archivo_entrada) {
        case ARCHIVO_BIN:
            /*ENTRADA stdin*/
            if (strcmp(nombre_archivo_entrada, STR_STDIN) == 0) {
                /*
                                status = cargar_estructura_stdin(palabra, &palabra->program_counter);
                 */
                break;
            }

            /*ENTRADA archivo*/
                status = cargar_estructura_bin(palabra, nombre_archivo_entrada);

            break;
        case ARCHIVO_TXT:
            /*ENTRADA stdin*/
            if (strcmp(nombre_archivo_entrada, STR_STDIN) == 0) {
                status = cargar_estructura_stdin(palabra);
                break;
            } else
                status = cargar_estructura_txt(&palabra, nombre_archivo_entrada);
            break;
        default:
            status = ST_ERROR_ARCHIVO_NO_ENCONTRADO;
    }

    return status;
}
status_t cargar_estructura_txt(palabras_s** palabra, char *nombre_archivo_entrada) {
    char * pch, *linea;
    status_t status = ST_OK;
    FILE * archivo_entrada;
    int i = 0, j;

    linea = (char*) malloc(sizeof (char)*MAX_STR);
    if (linea == NULL)
        return ST_ERROR_MEM;

    if ((archivo_entrada = fopen(nombre_archivo_entrada, "r")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    if (((*palabra)->memoria = (int*) malloc(sizeof (int))) == NULL)
        return ST_ERROR_MEM;

    while (!feof(archivo_entrada) && (i < (*palabra)->cantidad_memoria)) {
        if ((fgets(linea, MAX_STR, archivo_entrada)) != NULL) {
            /*Descarto los comentarios*/
            pch = strtok(linea, INICIO_COMENTARIO);

            /*Guardo la palabra en la estructura*/
            (*palabra)->memoria[i] = strtol(linea, &pch, 10);
            i += 1; /*Poner uno en define?*/
            if (((*palabra)->memoria = (int*) realloc((*palabra)->memoria, sizeof (int)*(i + 1))) == NULL)
                return ST_ERROR_MEM;
        }
    }

    /*Cargo el resto de la memoria pedida con ceros*/
    for (j = i; j < (*palabra)->cantidad_memoria; j++) {
        if (((*palabra)->memoria = (int*) realloc((*palabra)->memoria, sizeof (int)*(j + 1))) == NULL)
            return ST_ERROR_PTR_NULO;
        (*palabra)->memoria[j] = 0;
    }
    
    fclose(archivo_entrada);
    free(linea);
    return status;
}

status_t cargar_estructura_bin(palabras_s* palabra, char* nombre_archivo_entrada) {
    /*El archivo esta compuesto por enteros*/
    int i = 0,j;
    FILE * archivo_entrada_bin;

    palabra->memoria = (int*) malloc(sizeof (int));

    if ((archivo_entrada_bin = fopen(nombre_archivo_entrada, "rb")) == NULL)
                return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
    
    while (!feof(archivo_entrada_bin) && (i < palabra->cantidad_memoria)) {
        palabra->memoria = (int*) realloc(palabra->memoria, sizeof (int)*(i + 1));
        if ((fread(&palabra->memoria[i], sizeof (int), 1, archivo_entrada_bin)) == 1)
            i++;
    }

    /*Cargo el resto de la memoria pedida con ceros*/
    for (j = i; j < palabra->cantidad_memoria; j++) {
        if ((palabra->memoria = (int*) realloc(palabra->memoria, sizeof (int)*(j + 1))) == NULL)
            return ST_ERROR_PTR_NULO;
        palabra->memoria[j] = 0;
    }

    fclose(archivo_entrada_bin);
    return ST_OK;
}

status_t cargar_estructura_stdin(palabras_s *palabras) {
    char *palabra_ingresada, *pch;
    int i = 0;

    if ((palabra_ingresada = (char*) malloc(sizeof (char)*MAX_STR)) == NULL)
        return ST_ERROR_MEM;
    if ((palabras->memoria = (int*) malloc(sizeof (int*))) == NULL)
        return ST_ERROR_MEM;

    printf("%s ", MSJ_INGRESO_PALABRA);
    fgets(palabra_ingresada, MAX_STR, stdin);

    while (i < palabras->cantidad_memoria) {
        if ((strcmp(palabra_ingresada, FINALIZAR_CARGA)) != 0) {
            /*Pido memoria para guardar una palabra*/
            palabras->memoria[i] = strtol(palabra_ingresada, &pch, 10);

            if (strlen(pch) == 0)
                fprintf(stdout, "%s\n", MSJ_ERROR_INGRESO_PALABRA);
            else {
                i++;
                if ((palabras->memoria = (int*) realloc(palabras->memoria, sizeof (int)*(i + 1))) == NULL)
                    return ST_ERROR_MEM;

                printf("%s ", MSJ_INGRESO_PALABRA);
                fgets(palabra_ingresada, MAX_STR, stdin);
            }
        } else
            break;
    }

    palabras->cantidad_memoria = i;
    free(palabra_ingresada);

    return ST_OK;
}

void imprimir_ayuda() {
    fprintf(stderr, "%s\n", MSJ_AYUDA_TITULO);
    fprintf(stderr, "%s    %s\n\n", CLA_M, MSJ_AYUDA_M1);
    fprintf(stderr, "%s    %s\n\n", CLA_I, MSJ_AYUDA_I1);
    fprintf(stderr, "%s   %s\n", CLA_IF, MSJ_AYUDA_IF1);
    fprintf(stderr, "      %s\n\n", MSJ_AYUDA_IF2);
    fprintf(stderr, "%s    %s\n\n", CLA_O, MSJ_AYUDA_O1);
    fprintf(stderr, "%s   %s\n", CLA_OF, MSJ_AYUDA_OF1);
    fprintf(stderr, "      %s\n\n", MSJ_AYUDA_OF2);
}

status_t dump(archivo_t tipo_archivo_salida, char* nombre_archivo_salida, palabras_s palabra) {
    status_t status = ST_OK;

    switch (tipo_archivo_salida) {
        case ARCHIVO_TXT:
            status = imprimir_dump_por_stdout_o_txt(palabra, nombre_archivo_salida, tipo_archivo_salida);
            break;
        case ARCHIVO_BIN:
            if (strcmp(nombre_archivo_salida, STR_STDOUT) == 0) {
                memcpy(nombre_archivo_salida, NOMBRE_GENERICO_ARCHIVO_BIN, strlen(NOMBRE_GENERICO_ARCHIVO_BIN) + 1);
            }
            status = imprimir_dump_bin(palabra, nombre_archivo_salida, tipo_archivo_salida);
            break;
        case ARCHIVO_DEFAULT:
            /*No se ingreso -o ni -of*/
            status = imprimir_dump_por_stdout_o_txt(palabra, nombre_archivo_salida, tipo_archivo_salida);
            break;
        default:
            puts("default");
            break;
    }

    return status;
}

status_t imprimir_dump_por_stdout_o_txt(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida) {
    int i, j;
    FILE *archivo_salida;

    if (tipo_archivo_salida == ARCHIVO_DEFAULT)
        archivo_salida = stdout;
    else if (tipo_archivo_salida == ARCHIVO_TXT) {
        archivo_salida = fopen(nombre_archivo_salida, "w+");
        if (archivo_salida == NULL) {
            return ST_ERROR_ARCHIVO_NO_ENCONTRADO;
        }
    }

    puts("dumping..........");
    fprintf(archivo_salida, "%s\n", DUMP_MSJ_INICIO);
    fprintf(archivo_salida, "%s: %ld\n", DUMP_MSJ_ACUMULADOR, palabra.acumulador);
    fprintf(archivo_salida, "%s: %d\n", DUMP_MSJ_PROGRAM_COUNTER, palabra.program_counter);
    fprintf(archivo_salida, "%s: %d\n", DUMP_MSJ_INSTRUCCION, palabra.memoria[palabra.program_counter]);
    /*
        fprintf(archivo_salida, "%s: %d\n", DUMP_MSJ_OPCODE, palabra.opcode[palabra.program_counter]);
        fprintf(archivo_salida, "%s: %d\n", DUMP_MSJ_OPERANDO, palabra.operando[palabra.program_counter]);
     */
    fprintf(archivo_salida, "%s\n", DUMP_MSJ_MEMORIA);


    for (i = 0; i < 10; i++)
        fprintf(archivo_salida, "%6d", i);
    fprintf(archivo_salida, "\n");
    for (i = 0, j = 0; i < palabra.cantidad_memoria; i++) {
        if (i % 10 == 0) {
            if (i != 0)
                fprintf(archivo_salida, "\n");
            fprintf(archivo_salida, "%d", j * 10);
            j++;
        }

        fprintf(archivo_salida, "%6d",palabra.memoria[i]);
    }
    puts("\n");

    if (tipo_archivo_salida == ARCHIVO_TXT)
        fclose(archivo_salida);
    return ST_OK;
}

status_t imprimir_dump_bin(palabras_s palabra, char *nombre_archivo_salida, archivo_t tipo_archivo_salida) {
    int i;
    FILE *archivo_salida;

    if ((archivo_salida = fopen(nombre_archivo_salida, "w")) == NULL)
        return ST_ERROR_ARCHIVO_NO_ENCONTRADO;

    for (i = 0; i < palabra.cantidad_memoria; i++) {
        if ((fwrite(&(palabra.memoria[i]), sizeof (int), 1, archivo_salida)) != 1)
            return ST_ERROR_ESCRIBIR_BIN;
    }

    fclose(archivo_salida);
    return ST_OK;
}

status_t ejecutar_codigo() {
    char* codigo_lms[] = {"+1009", "+1010", "+2009", "+3010", "+2111", "+1111", "+4500", "+0000", "+0000", "+0000", "+0000", "+0000"};
    char aux[MAX_STR]; /*Aca guardo todo lo que ingresa el usuario*/
    int temp; /*Guardo enteros para validar antes de guardarlos en memoria*/
    int cantidad_palabras; /*Guarda la cantidad maxima de palabras que contiene la memoria*/
    char* p; /*Puntero auxiliar*/

    int* codigo_lms_int; /*Aca se transforma el vector de cadenas en vector de enteros*/
    int instruccion;
    size_t program_counter, i;
    int opcode, operando;
    long acumulador = 0;

    /*Se crea el vector de enteroos*/
    cantidad_palabras = sizeof (codigo_lms) / sizeof (char*);
    codigo_lms_int = (int*) malloc(sizeof (int)* cantidad_palabras);
    /*Valida que todos los enteros estén dentro del rango aceptado*/
    for (i = 0; i < cantidad_palabras; i++) {
        codigo_lms_int[i] = strtol(codigo_lms[i], &p, 10);
        if (*p != '\n' && *p != '\0' && *p != EOF) {
            return ST_ERROR_CAD_NO_ES_ENTERO;
        }
        if (codigo_lms_int[i] < MIN_PALABRA || codigo_lms_int[i] > MAX_PALABRA) {
            return ST_ERROR_PALABRA_FUERA_DE_RANGO;
        }
    }
    /*Comienza ejecución*/
    puts(MSJ_COMIENZO_EJECUCION);
    for (program_counter = 0; program_counter < MAX_INSTRICCIONES; program_counter++) {
        instruccion = codigo_lms_int[program_counter];
        operando = instruccion % 100;
        opcode = instruccion / 100;

        if (operando > cantidad_palabras || operando < INIT_INSTRUCCIONES) {
            puts(MSJ_FIN_EJECUCION);
            return ST_ERROR_SEGMENTATION_FAULT;
        }

        switch (opcode) {
            case 
                
                R:
                printf(MSJ_INGRESO_PALABRA);
                if (fgets(aux, MAX_STR, stdin) == NULL) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_CAD_NO_LEIDA;
                }
                if ((temp = strtol(aux, &p, 10)) < MIN_PALABRA || temp > MAX_PALABRA) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_PALABRA_FUERA_DE_RANGO;
                }
                if (*p != '\n' && *p != '\0' && *p != EOF) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_CAD_NO_ES_ENTERO;
                }

                codigo_lms_int[operando] = temp;
                break;
            case ESCRIBIR:
                printf("%s %i: %i\n", MSJ_IMPRIMIR_PALABRA, operando, codigo_lms_int[operando]);
                break;
            case CARGAR:
                acumulador = codigo_lms_int[operando];
                break;
            case GUARDAR:
                if (acumulador < MIN_PALABRA || acumulador > MAX_PALABRA) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_PALABRA_FUERA_DE_RANGO;
                }
                codigo_lms_int[operando] = acumulador;
                break;
            case PCARGAR:
                if (codigo_lms_int[operando] > cantidad_palabras || codigo_lms_int[operando] < INIT_INSTRUCCIONES) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_SEGMENTATION_FAULT;
                }
                acumulador = codigo_lms_int[codigo_lms_int[operando]];
                break;
            case PGUARDAR:
                if (codigo_lms_int[operando] > cantidad_palabras || codigo_lms_int[operando] < INIT_INSTRUCCIONES) {
                    puts(MSJ_FIN_EJECUCION);
                    return ST_ERROR_SEGMENTATION_FAULT;
                }
                codigo_lms_int[codigo_lms_int[operando]] = acumulador;
                break;
            case SUMAR:
                acumulador += codigo_lms_int[operando];
                break;
            case RESTAR:
                acumulador -= codigo_lms_int[operando];
                break;
            case DIVIDIR:
                acumulador /= codigo_lms_int[operando];
                break;
            case MULTIPLICAR:
                acumulador *= codigo_lms_int[operando];
                break;
            case JMP:
                program_counter = operando;
                break;
            case JMPNEG:
                if (acumulador < 0)
                    program_counter = operando;
                break;
            case JMPZERO:
                if (!acumulador)
                    program_counter = operando;
                break;
            case JNZ:
                if (acumulador)
                    program_counter = operando;
                break;
            case DJNZ:
                acumulador--;
                if (acumulador)
                    program_counter = operando;
                break;
            case HALT:
                puts(MSJ_FIN_EJECUCION);
                return ST_OK;
            default:
                puts(MSJ_FIN_EJECUCION);
                return ST_ERROR_OPCODE_INVALIDO;
        }
    }
    puts(MSJ_FIN_EJECUCION);
    return ST_ERROR_MAX_INSTR_SUPERADO;
}
