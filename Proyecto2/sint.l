%{
/*
Integrantes: Díaz González Rivas Ángel Iñaqui, Gayosso Rosillo Sebastian Emiliano, 
Perez Delgado Erandy Estefanya y Siliano Haller Rodrigo 
Fecha de elaboración: 1 de noviembre de 2024

Descripción breve:
Este programa realiza un análisis léxico y sintáctico de un programa fuente escrito en un lenguaje definido. 
Incluye una tabla de símbolos, literales, tokens y errores sintácticos, además de la generación de una cadena 
de átomos como entrada para el análisis sintáctico.

Funciones:
- buscarSimbolo: Busca un símbolo en la tabla de símbolos.
- agregarSimbolo: Agrega un nuevo símbolo a la tabla de símbolos si no existe.
- agregarLiteral: Añade un literal a la tabla de literales.
- guardarTablas: Guarda las tablas de símbolos y literales en archivos.
- guardarErrorLexico: Registra errores léxicos encontrados.
- obtenerAtomo: Retorna el átomo asociado a un token específico.
- guardarToken: Guarda los tokens y los átomos generados en sus respectivos archivos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Programa.c" // Incluir el archivo con el analizador sintáctico

// Estructuras de datos para la tabla de símbolos y literales
typedef struct{
    char nombre[50];
    int tipo;
} Simbolo;

typedef struct {
    int posicion;
    char dato[50];
} Literal;

// Variables globales para las tablas
Simbolo tablaSimbolos[100];
Literal tablaLiterales[100];
int indexSimbolos = 0;
int indexLiterales = 0;

// Archivos para tokens, errores y átomos
FILE *tokensFile;
FILE *erroresFile;
FILE *atomosFile;

// Función que busca un símbolo en la tabla y retorna su índice si existe, -1 si no
int buscarSimbolo(const char *nombre) {
    for (int i = 0; i < indexSimbolos; i++) {
        if (strcmp(tablaSimbolos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

// Agrega un símbolo si no existe en la tabla de símbolos
void agregarSimbolo(const char *nombre) {
    if (buscarSimbolo(nombre) == -1) {
        strcpy(tablaSimbolos[indexSimbolos].nombre, nombre);
        tablaSimbolos[indexSimbolos].tipo = -2;
        indexSimbolos++;
    }
}

// Agrega un literal a la tabla de literales
void agregarLiteral(const char *dato) {
    strcpy(tablaLiterales[indexLiterales].dato, dato);
    tablaLiterales[indexLiterales].posicion = indexLiterales;
    indexLiterales++;
}

// Guarda las tablas de símbolos y literales en archivos
void guardarTablas() {
    FILE *simbolosFile = fopen("tabla_simbolos.txt", "w");
    if (simbolosFile == NULL) {
        perror("Error al crear el archivo de tabla de simbolos");
        return;
    }
    fprintf(simbolosFile, "Tabla de Simbolos:\n");
    for (int i = 0; i < indexSimbolos; i++) {
        fprintf(simbolosFile, "%d\t%s\n", i, tablaSimbolos[i].nombre);
    }
    fclose(simbolosFile);

    FILE *literalesFile = fopen("tabla_literales.txt", "w");
    if (literalesFile == NULL) {
        perror("Error al crear el archivo de tabla de literales");
        return;
    }
    fprintf(literalesFile, "Tabla de Literales:\n");
    for (int i = 0; i < indexLiterales; i++) {
        fprintf(literalesFile, "%d\t%s\n", tablaLiterales[i].posicion, tablaLiterales[i].dato);
    }
    fclose(literalesFile);
}

// Registra errores léxicos en el archivo de errores léxicos
void guardarErrorLexico(const char *error) {
    if (erroresFile == NULL) {
        erroresFile = fopen("errores_lexicos.txt", "a");
    }
    if (erroresFile != NULL) {
        fprintf(erroresFile, "Error léxico: %s\n", error);
    }
}

// Función que obtiene el átomo basado en la clase y valor del token
const char* obtenerAtomo(int clase, const char *valor) {
    switch (clase) {
        // Definición de átomos basados en la clase de token
        case 0: // Palabras reservadas
            if (strcmp(valor, "0") == 0) return "h";
            if (strcmp(valor, "1") == 0) return "g";
            if (strcmp(valor, "2") == 0) return "e";
            if (strcmp(valor, "3") == 0) return "n";
            if (strcmp(valor, "4") == 0) return "f";
            if (strcmp(valor, "5") == 0) return "i";
            if (strcmp(valor, "6") == 0) return "d";
            if (strcmp(valor, "7") == 0) return "b";
            if (strcmp(valor, "8") == 0) return "v";
            if (strcmp(valor, "9") == 0) return "w";
            break;
        case 1: // Operadores aritméticos
            return valor;
        case 2: // Operadores de asignación
            if (strcmp(valor, "~") == 0) return "=";
            if (strcmp(valor, "+~") == 0) return "m";
            if (strcmp(valor, "-~") == 0) return "k";
            if (strcmp(valor, "*~") == 0) return "p";
            if (strcmp(valor, "/~") == 0) return "t";
            if (strcmp(valor, "$~") == 0) return "u";
            break;
        case 3: // Símbolos especiales
            return valor;
        case 4: // Operadores relacionales
            if (strcmp(valor, "<") == 0) return "<";
            if (strcmp(valor, ">") == 0) return ">";
            if (strcmp(valor, "==") == 0) return "?";
            if (strcmp(valor, "<=") == 0) return "|";
            if (strcmp(valor, ">=") == 0) return "y";
            if (strcmp(valor, "!=") == 0) return "¿";
            break;
        case 5: // Identificadores
            return "a";
        case 6: // Constantes numéricas enteras
            return "z";
        case 7: // Constantes numéricas reales
            return "r";
        case 8: // Constantes de cadena
            return "s";
        case 9: // Constante carácter
            return "c";
    }
    return "";
}

// Guarda tokens en el archivo tokens.txt y átomos en atomos.txt
void guardarToken(int clase, const char *valor) {
    if (tokensFile == NULL) {
        tokensFile = fopen("tokens.txt", "a");
    }
    if (tokensFile != NULL) {
        fprintf(tokensFile, "Token (%d, %s)\n", clase, valor);
    }

    if (atomosFile == NULL) {
        atomosFile = fopen("atomos.txt", "a");
    }
    if (atomosFile != NULL) {
        const char* atomo = obtenerAtomo(clase, valor);
        fprintf(atomosFile, "%s", atomo);
    }
}
%}

%%

[ \t\n]+    {}  /* Ignora espacios, tabulaciones y saltos de línea */

"cadena"    { guardarToken(0, "0"); }  /* Token para "cadena" */
"caracter"  { guardarToken(0, "1"); }  /* Token para "caracter" */
"else"      { guardarToken(0, "2"); }  /* Token para "else" */
"entero"    { guardarToken(0, "3"); }  /* Token para "entero" */
"For"       { guardarToken(0, "4"); }  /* Token para "For" */
"if"        { guardarToken(0, "5"); }  /* Token para "if" */
"real"      { guardarToken(0, "6"); }  /* Token para "real" */
"return"    { guardarToken(0, "7"); }  /* Token para "return" */
"void"      { guardarToken(0, "8"); }  /* Token para "void" */
"while"     { guardarToken(0, "9"); }  /* Token para "while" */

[\+\-\*\/\$] { guardarToken(1, yytext); }  /* Tokeniza operadores aritméticos */

"~"|\+~|\-~|\*~|\/~|\$~ { guardarToken(2, yytext); }  /* Operadores de asignación combinada */

"<"|">"|"=="|"<="|">="|"!="|"^^" { guardarToken(4, yytext); }  /* Operadores relacionales */

"("|")"|"{"|"}"|"["|"]"|","|":"|"()"|"{}"|"[]" { guardarToken(3, yytext); }  /* Paréntesis, llaves, corchetes, y otros */


[a-zA-Z][a-zA-Z0-9]{0,4}_ {
    agregarSimbolo(yytext);  /* Agrega identificador a la tabla de símbolos */
    int pos = buscarSimbolo(yytext); /* Busca posición en tabla de símbolos */
    char posStr[10];
    sprintf(posStr, "%d", pos); /* Convierte posición a string */
    guardarToken(5, posStr); /* Guarda el token */
}

[a-zA-Z][0-9]+ {
    guardarErrorLexico(yytext);  /* Error léxico por identificador inválido */
}

-?[0-9]{1,6} {
    agregarLiteral(yytext);  /* Agrega literal a tabla de literales */
    char posStr[10];
    sprintf(posStr, "%d", indexLiterales - 1);
    guardarToken(6, posStr);
}

[0-9]+\.[0-9]*|\.[0-9]+ {
    agregarLiteral(yytext);  /* Agrega literal real */
    char posStr[10];
    sprintf(posStr, "%d", indexLiterales - 1);
    guardarToken(7, posStr);
}

\"([^\"']|(\\\"))*\" {
    agregarLiteral(yytext);  /* Agrega cadena literal */
    char posStr[10];
    sprintf(posStr, "%d", indexLiterales - 1);
    guardarToken(8, posStr);
}

'[^']*' {
    agregarLiteral(yytext);  /* Agrega carácter literal */
    char posStr[10];
    sprintf(posStr, "%d", indexLiterales - 1);
    guardarToken(9, posStr);
}

[a-zA-Z0-9_]{5,} {
    guardarErrorLexico(yytext);  /* Guarda el error léxico */
}

. {
    guardarErrorLexico(yytext);  /* Error léxico para cualquier otro carácter */
}


%%

int yywrap() {
    return 1;  // Finalización de entrada
}

int main(int argc, char *argv[]) {
    // Revisa que haya al menos un archivo de entrada especificado
    if (argc < 2) {
        printf("Uso: %s <archivo de entrada>\n", argv[0]);
        return 1;
    }

    // Abre el archivo fuente para análisis léxico
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return 1;
    }

    yyin = file;  // Establece el archivo para yylex
    tokensFile = fopen("tokens.txt", "w");  // Archivo para guardar tokens
    erroresFile = fopen("errores_lexicos.txt", "w");  // Archivo para errores léxicos
    atomosFile = fopen("atomos.txt", "w");  // Archivo para la cadena de átomos

    yylex();  // Inicia el análisis léxico

    fclose(file);  // Cierra el archivo fuente
    guardarTablas();  // Guarda las tablas de símbolos y literales

    if (tokensFile != NULL) fclose(tokensFile);  // Cierra archivo de tokens
    if (erroresFile != NULL) fclose(erroresFile);  // Cierra archivo de errores
    if (atomosFile != NULL) fclose(atomosFile);  // Cierra archivo de átomos
    main_sintactico();  // Llama al análisis sintáctico en Programa.c

    return 0;  // Finaliza el programa
}
