%option noyywrap

%{
	#include <stdio.h>
	#include <stdlib.h>
%}


%%

\n {;}
. {;}
el {fprintf(yyout,"EL\n");}
los {fprintf(yyout,"LOS\n");}
la {fprintf(yyout,"LA\n");}
pintura {fprintf(yyout,"PINTURA\n");}
historia {fprintf(yyout,"HISTORIA\n");}
técnica {fprintf(yyout,"TÉCNICA\n");}
mezcla {fprintf(yyout,"MEZCLA\n");}
obra {fprintf(yyout,"OBRA\n");}
representación {fprintf(yyout,"REPRESENTACIÓN\n");}
retrato {fprintf(yyout,"RETRATO\n");}
género {fprintf(yyout,"GÉNERO\n");}
paisaje {fprintf(yyout,"PAISAJE\n");}
arte {fprintf(yyout,"ARTE\n");}
realismo {fprintf(yyout,"REALISMO\n");}
pigmentos {fprintf(yyout,"PIGMENTOS\n");}
colores {fprintf(yyout,"COLORES\n");}
trazos {fprintf(yyout,"TRAZOS\n");}
artistas {fprintf(yyout,"ARTISTAS\n");}
encáustica {fprintf(yyout,"ENCÁUSTICA\n");}
aguada {fprintf(yyout,"AGUADA\n");}
fresco {fprintf(yyout,"FRESCO\n");}
temple {fprintf(yyout,"TEMPLE\n");}
gobelino {fprintf(yyout,"GOBELINO\n");}
vitral {fprintf(yyout,"VITRAL\n");}
acuarela {fprintf(yyout,"ACUARELA\n");}
óleo {fprintf(yyout,"ÓLEO\n");}
disueltos {fprintf(yyout,"DISUELTOS\n");}
mezclados {fprintf(yyout,"MEZCLADOS\n");}
diluidos {fprintf(yyout,"DILUIDOS\n");}
combinados {fprintf(yyout,"COMBINADOS\n");}
extravagantes {fprintf(yyout,"EXTRAVAGANTES\n");}
de {fprintf(yyout,"DE\n");}
extraordinaria {fprintf(yyout,"EXTRAORDINARIA\n");}
acrílico {fprintf(yyout,"ACRÍLICO\n");}
aerosol {fprintf(yyout,"AEROSOL\n");}



%%


int main(int argc, char *argv[]){
	if(argc == 1){
		printf("Error:Faltan par%cmetros.\nUso: lexico.exe archivo_entrada archivo_salida\n", 160);
		return 0;	
	}
	if(argc == 2){
		printf("Error:Falta par%cmetro.\nUso: lexico archivo_entrada archivo_salida\n",160);
		return 0;
	}
	if(argc > 3){
		printf("Error:Demasiados par%cmetros.\nUso: lexico.exe archivo_entrada archivo_salida", 160);
		return 0;
	}
	if(argc == 3){
		yyin = fopen(argv[1],"r");
		if(yyin == NULL){
			printf("Error:El archivo de entrada no existe.");
			return 0;
		}
		yyout = fopen(argv[2],"r");
		if(yyout != NULL){
			printf("Error:El archivo de salida ya existe.");
			return 0;
		}
		fclose(yyout);
		yyout = fopen(argv[2],"w");
		yylex();
	}

	fclose(yyin);
	fclose(yyout);
	return 0;
}