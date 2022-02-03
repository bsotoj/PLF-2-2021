#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
int cantidadTerminales = 35;


/*para pasar a mayuscula una palabra se evalua caracter por caracter ya que existen
casos particulares que son los caracteres con acento en donde el arreglo tiene una posicion
para el caracter y para el acento por separado 
*/

//al añadir por ejemplo (int) estamos forzando una variable de cierto tipo a convertirla en entero (castear)
//todas las vocales que van con acento tienen un valor igual a -61 y el acento varia dependiendo de la vocal que lo acompañe:
/*
Si es a : -95
Si es e : -87
Si es i : -83
Si es o : -77
Si es u : -70

*/
char *pasarAMayuscula(char *palabra){
	char *palabraMayuscula = (char *)malloc(sizeof(char)*30);
	strcpy(palabraMayuscula,"");
    char caracterResultante[3] = "";
	for(int i = 0; i < strlen(palabra); i++){
		if(((int)palabra[i] == -61) && ((int)palabra[i+1] == -95) ){
			//pasar al siguiente caracter despues del acento
			i++;
			char caracterMayuscula[2] = "Á";
			caracterResultante[0] = caracterMayuscula[0];
			caracterResultante[1] = caracterMayuscula[1];
			strcat(palabraMayuscula,caracterResultante);
		}
		else if(((int)palabra[i] == -61) && ((int)palabra[i+1] == -87) ){
			i++;
			char caracterMayuscula[2] = "É";
			caracterResultante[0] = caracterMayuscula[0];
			caracterResultante[1] = caracterMayuscula[1];
			strcat(palabraMayuscula,caracterResultante);
		}
		else if(((int)palabra[i] == -61) && ((int)palabra[i+1] == -83) ){
			i++;
			char caracterMayuscula[2] = "Í";
			caracterResultante[0] = caracterMayuscula[0];
			caracterResultante[1] = caracterMayuscula[1];
			strcat(palabraMayuscula,caracterResultante);
		}
	    else if(((int)palabra[i] == -61) && ((int)palabra[i+1] == -77) ){
	    	i++;
			char caracterMayuscula[2] = "Ó";
			caracterResultante[0] = caracterMayuscula[0];
			caracterResultante[1] = caracterMayuscula[1];
			strcat(palabraMayuscula,caracterResultante);
	    }
	    else if(((int)palabra[i] == -61) && ((int)palabra[i+1] == -70) ){
	    	i++;
			char caracterMayuscula[2] = "Ú";
			caracterResultante[0] = caracterMayuscula[0];
			caracterResultante[1] = caracterMayuscula[1];
			strcat(palabraMayuscula,caracterResultante);
	    }

	    else{
	        char caracterResultante[3] = "";
	    	caracterResultante[0] = (char)toupper(palabra[i]);
	    	strcat(palabraMayuscula,caracterResultante);
	    }	
	}
	return palabraMayuscula;
}
int buscarTerminalEnPalabra(char *palabra, char **terminales, int *posicionTerminalEncontrado){

	//primero verifica si existe una coincidencia directa
	//palabra = dedo
	//terminal[i] = dedo
	for(int i = 0; i < cantidadTerminales; i++){
		if(strlen(palabra) == strlen(terminales[i])){
			//si los strings son iguales entonces retornar 0
			if(strcmp(palabra,terminales[i]) == 0){
				*posicionTerminalEncontrado = i;
				return 0;
			}
		}
	}

	//caso contrario busca si existe algun prefijo dentro de la palabra
	//requisito enunciado: "si un terminal de su gramática contiene a otro terminal como prefijo
	//prefiera leer el terminal de mayor longitud" 

	//ejemplos:
	//palabra = dedo
	//terminales[0] = de
	//terminales[1] = ded
	//terminales[2] = am
	//prefijo = ded 
	//largoPrefijo = 3

	//palabra = mako
	//terminales[0] = de
	//terminales[1] = ded
	//terminales[2] = am
	//prefijo = 
	//largoPrefijo = 0


	int largoPrefijo = 0;

	for(int i = 0; i < cantidadTerminales; i++){
		if(strlen(palabra) > strlen(terminales[i])){
			int largoPrefijoActual = strlen(terminales[i]); 
			int coincidenciasEncontradas = 0;  

		
			for(int j = 0; j < strlen(terminales[i]); j++){
				//busqueda de caracter con acento
				if(((int)palabra[j] == -61) && ((int)palabra[j+1] == -95) ){
					j++;
					coincidenciasEncontradas++;
		
				}
				else if(((int)palabra[j] == -61) && ((int)palabra[j+1] == -87) ){
					j++;
					coincidenciasEncontradas++;
				}
				else if(((int)palabra[j] == -61) && ((int)palabra[j+1] == -83) ){
					j++;
					coincidenciasEncontradas++;
				}
	    		else if(((int)palabra[j] == -61) && ((int)palabra[j+1] == -77) ){
	    			j++;
					coincidenciasEncontradas++;
	   			 }
	    		else if(((int)palabra[j] == -61) && ((int)palabra[j+1] == -70) ){
	    			j++;
					coincidenciasEncontradas++;
	   			 }

	   			//comparar caracteres sin acento 
				else if((int)palabra[j] == (int)terminales[i][j]){
					coincidenciasEncontradas++; 
				}
				else{
					break;
				}
			}


			if(coincidenciasEncontradas == largoPrefijoActual){
				if(largoPrefijoActual > largoPrefijo){
					largoPrefijo = largoPrefijoActual;
					*posicionTerminalEncontrado = i; 
				}
			}
		
		}

	}
	//1: la palabra no pertenece a la gramatica
	//0: la palabra pertenece a la gramatica 

	if(largoPrefijo == 0){
		return 1;
	}

	else{
		return 0;
	}


}

void encontrarTerminalesGramatica(char **terminales,char *archivoEntrada, char *archivoSalida, int cantidadPalabrasArchivo){

	int iterador;
	FILE *entrada = fopen(archivoEntrada,"r");

	//creación archivo de salida
	FILE *salida = fopen(archivoSalida,"w");
	

	for(iterador = 0; iterador < cantidadPalabrasArchivo; iterador++){
		char *palabraArchivoActual = (char *)malloc(sizeof(char)*30);
		fscanf(entrada, "%s", palabraArchivoActual);

		//posicion del terminal en el arreglo terminales que se encuentró dentro de la palabra actual
		int posicionTerminalEncontrado = 0;
		
		if(buscarTerminalEnPalabra(palabraArchivoActual,terminales, &posicionTerminalEncontrado) == 0){

			char *terminalMayus = (char *)malloc(sizeof(char)*30);
			strcpy(terminalMayus,terminales[posicionTerminalEncontrado]);

			//terminal encontrado se pasa a mayuscula para posterior escritura
			terminalMayus = pasarAMayuscula(terminalMayus);

			//escritura en el archivo de salida
			fprintf(salida, "%s\n", terminalMayus);
			
			//liberar memoria reservada para el terminal encontrado
			free (terminalMayus);
		}
		//liberar memoria reservada para la palabra actual del archivo 
		free(palabraArchivoActual);
	}
	fclose(entrada);
	fclose(salida);

	return;  


}


int contarPalabrasArchivo(char *nombreArchivo){
	int cantidadPalabrasArchivo = 0;
	FILE *archivo = fopen(nombreArchivo, "r"); 
	char caracterActual; 
	while((caracterActual = fgetc(archivo)) != EOF){
		if( caracterActual == ' '){
			cantidadPalabrasArchivo++; 
		}
	}

	fclose(archivo);
	cantidadPalabrasArchivo++; 
	return cantidadPalabrasArchivo;
}

char **generarTerminales(char **simbolosTerminales){
	
	simbolosTerminales = (char **)malloc(sizeof(char *)*cantidadTerminales);

	//definición de los 35 símbolos terminales en la gramática 
	simbolosTerminales[0]= "el";
	simbolosTerminales[1]= "los";
	simbolosTerminales[2]= "la"; 
	simbolosTerminales[3]= "pintura"; 
	simbolosTerminales[4]= "historia";
	simbolosTerminales[5]= "técnica"; 
	simbolosTerminales[6]= "mezcla";
	simbolosTerminales[7]= "obra"; 
	simbolosTerminales[8]= "representación"; 
	simbolosTerminales[9]= "retrato"; 
	simbolosTerminales[10]= "género"; 
	simbolosTerminales[11]= "paisaje";
	simbolosTerminales[12]= "arte";
	simbolosTerminales[13]= "realismo";
	simbolosTerminales[14]= "pigmentos"; 
	simbolosTerminales[15]= "colores"; 
	simbolosTerminales[16]= "trazos"; 
	simbolosTerminales[17]= "artistas";
	simbolosTerminales[18]= "encáustica"; 
	simbolosTerminales[19]= "aguada"; 
	simbolosTerminales[20]= "fresco"; 
	simbolosTerminales[21]= "temple";
	simbolosTerminales[22]= "gobelino";
	simbolosTerminales[23]= "vitral";
	simbolosTerminales[24]= "acuarela";
	simbolosTerminales[25]= "óleo";
	simbolosTerminales[26]= "disueltos";
	simbolosTerminales[27]= "mezclados";
	simbolosTerminales[28]= "diluidos";
	simbolosTerminales[29]= "combinados";
	simbolosTerminales[30]= "extravagantes"; 
	simbolosTerminales[31]= "de"; 
	simbolosTerminales[32]= "extraordinaria"; 
	simbolosTerminales[33]= "acrílico"; 
	simbolosTerminales[34]= "aerosol"; 

	return simbolosTerminales;

}

int verificarExistenciaArchivo(char *nombreArchivo){
	FILE *lectura = fopen(nombreArchivo, "r");
	if(lectura != NULL){
		fclose(lectura);
		return 0;
	}

	else{
		return 1;
	}
}

int detectarErrores(int cantidadArgumentos, char *argumentosEntrada[]){

	if(cantidadArgumentos == 1){
		printf("Error: Faltan par%cmetros.\n",160);
		printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
		return 0; 
	}

	if(cantidadArgumentos == 2){
		printf("Error: Falta par%cmetro.\n",160);
		printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
		return 0;
	}

	if(cantidadArgumentos > 3){
		printf("Error: Demasiados par%cmetros.\n",160);
		printf("Uso: lexico.exe archivo_entrada archivo_salida\n");
		return 0;

	}

	if(verificarExistenciaArchivo(argumentosEntrada[1]) == 1){
		printf("Error: El archivo de entrada no existe.\n");
		return 0;
	}

	if(verificarExistenciaArchivo(argumentosEntrada[2]) == 0){
		printf("Error: El archivo de salida ya existe.\n");
		return 0;
	}

	return 1;

}




int main(int argc, char *argv[]){
	
	if(detectarErrores(argc,argv) == 0){
		return 0;
	}

	else{

		int largoArchivo = contarPalabrasArchivo(argv[1]);
		char **terminales = generarTerminales(terminales);
		encontrarTerminalesGramatica(terminales,argv[1],argv[2],largoArchivo);
		//liberar memoria reservada para la lectura del archivo
		for(int i = 0; i < cantidadTerminales; i++){
			free(terminales[i]);
		}
		free(terminales);
		return 0;

	}
	



}