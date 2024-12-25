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

FILE *atomosFile;       // Archivo de entrada con la cadena de átomos
FILE *erroresSintacticosFile; // Archivo para errores sintácticos detectados
char c;                 // Átomo actual leído desde la cadena de átomos

// Funciones para cada no terminal en la gramática
void Programa();
void ListaD();
void SerieF();
void otraF();
void D();
void Tipo();
void L();
void Valor();
void IP();
void V();
void A();
void AP();
void I();
void FP();
void B();
void W();
void For();
void Return();
void Z();
void E();
void EP();
void T();
void TP();
void F();
void R();
void RP();
void S();
void SP();
void otraS();
void Func();
void TipoFun();

// Función de manejo de errores sintácticos
// Recibe el átomo esperado y el encontrado para registrar en el archivo de errores
char error(const char *espera, char c) {
    fprintf(erroresSintacticosFile, "Error sintáctico en el átomo %c, se esperaba %s\n", c, espera);
    long int posicionActual = ftell(atomosFile);  // Guarda la posición actual
    fseek(atomosFile, posicionActual, SEEK_SET);  // Reinicia la lectura desde la posición después del error
    c = fgetc(atomosFile);  // Lee el siguiente carácter de la cadena de átomos
    return c;  // Retorna el siguiente carácter para continuar el análisis
}

// Función principal del analizador sintáctico basada en la producción <Programa>
void Programa() {
    if (c == 'g' || c == 'n' || c == 'd' || c == 'h' || c == '[') {
        ListaD();  // Llama a ListaD si el átomo actual es parte de <ListaD>
        
        // Verifica y consume el carácter '['
        if (c == '[') {
            c = fgetc(atomosFile);
        } else {
            char espera[] = "[";  // Define el carácter esperado para el mensaje de error
            c = error(espera, c); // Maneja el error si el carácter no es '['
        }
        
        SerieF();  // Llama a SerieF, correspondiente a <SerieF> en la gramática
        
        // Verifica y consume el carácter ']'
        if (c == ']') {
            c = fgetc(atomosFile);
        } else {
            char espera[] = "]";  // Define el carácter esperado
            c = error(espera, c); // Registra el error si no encuentra ']'
        }
        return;
    } else {
        // Si el átomo no corresponde a la producción <Programa>, genera un error
        char espera[] = "g, n, d, h";
        c = error(espera, c);
    }
}

// Función que procesa la producción <ListaD>
// Recorre la lista de declaraciones en el programa
void ListaD() {
    if (c == 'g' || c == 'n' || c == 'd' || c == 'h') {
        D();      // Llama a D si el átomo actual es parte de <D>
        ListaD(); // Llama recursivamente a ListaD para procesar múltiples declaraciones
        return;
    } else if (c == '[' || c == 'a' || c == 'i' || c == 'w' || c == 'f' || c == 'b') {
        // Caso de salida: ninguno de los caracteres requiere procesamiento adicional
        return;
    } else {
        // Genera error si el átomo actual no es compatible con la producción
        char espera[] = "g, n, d, h, [, a, i, w, f, b";
        c = error(espera, c);
    }
}

// Se repite el mismo procedimiento para las demás funciones de los no terminales
void SerieF(){
	if(c=='g'||c=='n'||c=='d'||c=='h'||c=='v'){
		Func();
		otraF();
		return;
	}else{
		char espera[]= "g,n,d,h,v";
		c=error(espera,c);
	}
}
void otraF(){
	if(c=='g'||c=='n'||c=='d'||c=='h'||c=='v'){
		Func();
		otraF();
		return;
	}else if(c==']'){
			return;
		
	}else{
		char espera[]= "g,n,d,h,v,]";
		c=error(espera,c);
	}
}
void D(){
	if(c=='g'||c=='n'||c=='d'||c=='h'){
		Tipo();
		L();
		if(c==':'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ":";
			c=error(espera,c);
		}
		return;
	}else{
		char espera[]= "g,n,d,h";
		c=error(espera,c);
	}
}
void Tipo(){
	if(c=='g'){
		c=fgetc(atomosFile);
		return;
	}else if(c=='n'){
		c=fgetc(atomosFile);
		return;
	}else if(c=='d'){
		c=fgetc(atomosFile);
		return;
	}else if(c=='h'){
		c=fgetc(atomosFile);
		return;
	}else{
		char espera[]= "g,n,d,h";
		c=error(espera,c);
	}
}
void L(){
	if(c=='a'){
		c=fgetc(atomosFile);
		Valor();
		IP();
		return;
	}else{
		char espera[]= "a";
		c=error(espera,c);
	}
}
void IP(){
	if(c==','){
		c=fgetc(atomosFile);
		if(c=='a'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "a";
			c=error(espera,c);
		}
		Valor();
		IP();
		return;
	}else if(c==':'){
			return;
		
	}else{
		char espera[]= "',',:";
		c=error(espera,c);
	}
}
void Valor(){
	if(c=='='){
		c=fgetc(atomosFile);
		V();
		return;
	}else if(c==','||c==EOF){
			return;
	}else{
		char espera[]= "=,',',fin de cadena";
		c=error(espera,c);
	}
}
void V(){
	if(c=='c'){
		c=fgetc(atomosFile);
		return;
	}else if(c=='s'){
		c=fgetc(atomosFile);
		return;
	}else if(c=='z'){
		c=fgetc(atomosFile);
		return;
	}else if(c=='r'){
		c=fgetc(atomosFile);
		return;
	}else{
		char espera[]= "c,s,z,r";
		c=error(espera,c);
	}
}
void A(){
	if(c=='a'){
		c=fgetc(atomosFile);
		AP();
		if(c==':'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ":";
			c=error(espera,c);
		}
		return;
	}else{
		char espera[]= "a";
		c=error(espera,c);
	}
}
void AP(){
	if(c=='='){
		c=fgetc(atomosFile);
		E();
		return;
	}else if(c=='m'){
		c=fgetc(atomosFile);
		E();
		return;
	}else if(c=='k'){
		c=fgetc(atomosFile);
		E();
		return;
	}else if(c=='p'){
		c=fgetc(atomosFile);
		E();
		return;
	}else if(c==EOF){
		c=fgetc(atomosFile);
		E();
		return;
	}else if(c=='u'){
		c=fgetc(atomosFile);
		E();
		return;
	}else{
		char espera[]= "=,m,k,p,u,fin de cadena";
		c=error(espera,c);
	}
}
void I(){
	if(c=='i'){
		c=fgetc(atomosFile);
		if(c=='['){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "[";
			c=error(espera,c);
		}
		R();
		if(c==']'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "]";
			c=error(espera,c);
		}
		FP();
		return;
	}else{
		char espera[]= "i";
		c=error(espera,c);
	}
}
void FP(){
	if(c=='('){
		c=fgetc(atomosFile);
		S();
		if(c==')'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ")";
			c=error(espera,c);
		}
		B();
		return;
	}else{
		char espera[]= "(";
		c=error(espera,c);
	}
}
void B(){
	if(c=='e'){
		c=fgetc(atomosFile);
		if(c=='('){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "(";
			c=error(espera,c);
		}
		S();
		if(c==')'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ")";
			c=error(espera,c);
		}
		return;
	}else if(c=='a'||c=='i'||c=='w'||c=='f'||c=='b'||c=='['||c==EOF){
			return;
		
	}else{
		char espera[]= "e,[,a,i,w,f,b,fin de cadena";
		c=error(espera,c);
	}
}
void W(){
	if(c=='w'){
		c=fgetc(atomosFile);
		if(c=='['){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "[";
			c=error(espera,c);
		}
		R();
		if(c==']'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ")";
			c=error(espera,c);
		}
		if(c=='('){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "(";
			c=error(espera,c);
		}
		S();
		if(c==')'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ")";
			c=error(espera,c);
		}
		return;
	}else{
		char espera[]= "w";
		c=error(espera,c);
	}
}
void For(){
	if(c=='f'){
		c=fgetc(atomosFile);
		if(c=='['){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "[";
			c=error(espera,c);
		}
		E();
		if(c==']'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "]";
			c=error(espera,c);
		}
		if(c=='('){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "(";
			c=error(espera,c);
		}
		S();
		if(c==')'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ")";
			c=error(espera,c);
		}
		return;
	}else{
		char espera[]= "f";
		c=error(espera,c);
	}
}
void Return(){
	if(c=='b'){
		c=fgetc(atomosFile);
		Z();
	}else{
		char espera[]= "b";
		c=error(espera,c);
	}
}
void Z(){
	if(c=='['){
		c=fgetc(atomosFile);
		E();
		if(c==']'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "]";
			c=error(espera,c);
		}
		if(c==':'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ":";
			c=error(espera,c);
		}
		return;
	}else if(c==':'){
			c=fgetc(atomosFile);
	}else{
		char espera[]= "[,:";
		c=error(espera,c);
	}
}
void E(){
	if(c=='('||c=='a'||c=='z'||c=='r'||c=='['){
		T();
		EP();
		return;
	}else{
		char espera[]= "(,a,z,r,[";
		c=error(espera,c);
	}
}
void EP(){
	if(c=='+'){
		c=fgetc(atomosFile);
		T();
		EP();
		return;
	}else if(c=='-'){
		c=fgetc(atomosFile);
		T();
		EP();
		return;
	}else
		if(c==':'||c==']'||c==')'||c=='>'||c=='<'||c=='?'||c=='y'){
			return;
		
	}else{
		char espera[]= "+,-,:,],),>,<,?,y";
		c=error(espera,c);
	}
}
void T(){
	if(c=='('||c=='a'||c=='z'||c=='r'||c=='['){
		F();
		TP();
		return;
	}else{
		char espera[]= "(,a,z,r,[";
		c=error(espera,c);
	}
}
void TP(){
	if(c=='*'){
		c=fgetc(atomosFile);
		F();
		TP();
		return;
	}else
		if(c=='/'){
			c=fgetc(atomosFile);
			F();
			TP();
			return;
		
	}else
		if(c=='$'){
			c=fgetc(atomosFile);
			F();
			TP();
			return;
		
	}else
		if(c=='+'||c=='-'||c==EOF){
			return;
		
	}else{
		char espera[]= "*,/,$,+,-,fin de cadena";
		c=error(espera,c);
	}
}
void F(){
	if(c=='('){
		c=fgetc(atomosFile);
		E();
		if(c==')'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ")";
			c=error(espera,c);
		}
		return;
	}else
		if(c=='a'){
		c=fgetc(atomosFile);
		return;
	}else
		if(c=='z'){
		c=fgetc(atomosFile);
		return;
	}else
		if(c=='r'){
		c=fgetc(atomosFile);
		return;
	}else
		if(c=='['){
		c=fgetc(atomosFile);
		if(c=='a'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "a";
			c=error(espera,c);
		}
		if(c==']'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "]";
			c=error(espera,c);
		}
		return;
	}else{
		char espera[]= "(,a,z,r,[";
		c=error(espera,c);
	}
}
void R(){
	if(c=='('||c=='a'||c=='z'||c=='r'||c=='['){
		E();
		RP();
		return;
	}else{
		char espera[]= "(,a,z,r,[";
		c=error(espera,c);
	}
}
void RP(){
	if(c=='>'){
		c=fgetc(atomosFile);
		E();
		return;
	}else
		if(c=='<'){
		c=fgetc(atomosFile);
		E();
		return;
	}else
		if(c=='?'){
		c=fgetc(atomosFile);
		E();
		return;
	}else
		if(c=='y'){
		c=fgetc(atomosFile);
		E();
		return;
	}else
		if(c=='|'){
		c=fgetc(atomosFile);
		E();
		return;
	}else
		if(c==(char)191){
		c=fgetc(atomosFile);
		E();
		return;
	}else{
		char espera[]= ">,<,?,y,|,¿";
		c=error(espera,c);
	}
}
void S(){
	if(c=='a'||c=='i'||c=='w'||c=='f'||c=='b'||c=='['){
		SP();
		otraS();
		return;
	}else{
		char espera[]= "a,i,w,f,b,[";
		c=error(espera,c);
	}
}
void SP(){
	if(c=='a'){
		A();
		return;
	}else
		if(c==';'){
		I();
		return;
	}else
		if(c=='w'){
		W();
		return;
	}else
		if(c=='f'){
		For();
		return;
	}else
		if(c=='b'){
		Return();
		return;
	}else
		if(c=='['){
		c=fgetc(atomosFile);
		if(c=='a'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "a";
			c=error(espera,c);
		}
		if(c==']'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "]";
			c=error(espera,c);
		}
		if(c==':'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ":";
			c=error(espera,c);
		}
		return;
	}else{
		char espera[]= "a,;,w,f,b,[";
		c=error(espera,c);
	}
}
void otraS(){
	if(c=='a'||c=='i'||c=='w'||c=='f'||c=='b'||c=='['){
		SP();
		otraS();
		return;
	}else
		if(c==')'){
			return;
		
	}else{
		char espera[]= "a,i,w,f,b,[,)";
		c=error(espera,c);
	}
}
void Func(){
	if(c=='g'||c=='n'||c=='d'||c=='h'||c=='v'){
		TipoFun();
		if(c=='a'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "a";
			c=error(espera,c);
		}
		if(c=='('){
			c=fgetc(atomosFile);
		}else{
			char espera[]= "(";
			c=error(espera,c);
		}
		ListaD();
		S();
		if(c==')'){
			c=fgetc(atomosFile);
		}else{
			char espera[]= ")";
			c=error(espera,c);
		}
		return;
	}else{
		char espera[]= "g,n,d,h,v";
		c=error(espera,c);
	}
}
void TipoFun(){
	if(c=='g'||c=='n'||c=='d'||c=='h'){
		Tipo();
		return;
	}else if(c=='v'){
			c=fgetc(atomosFile);
	}else{
		char espera[]= "g,n,d,h,v";
		c=error(espera,c);
	}
}

// Función main_sintactico: Configura y controla el análisis sintáctico principal
int main_sintactico() {
    // Abre archivo de átomos en modo lectura
    atomosFile = fopen("atomos.txt", "r");
    if (atomosFile == NULL) {
        perror("Error al abrir el archivo de átomos");
        return 1;
    }

    // Crea o abre el archivo de errores sintácticos en modo escritura
    erroresSintacticosFile = fopen("errores_sintacticos.txt", "w");
    if (erroresSintacticosFile == NULL) {
        perror("Error al crear el archivo de errores sintácticos");
        fclose(atomosFile);
        return 1;
    }

    c = fgetc(atomosFile);  // Lee el primer átomo desde el archivo de átomos
    Programa();             // Llama a la función principal <Programa> para iniciar el análisis

    // Cierra los archivos utilizados
    fclose(atomosFile);
    fclose(erroresSintacticosFile);

    return 0;
}

