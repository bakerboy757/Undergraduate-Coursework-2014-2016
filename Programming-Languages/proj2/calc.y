/*
*	Tyler Kelly:tck13
*/
%{
	#include<stdio.h>
	#include<string.h>
	#include<stdlib.h>
	void print_header();
	void print_end();
	FILE *outfile;
	int yyline = 1;
	int yycolumn = 1;
	char string_table[20000];
	typedef struct Table{
	   int value;
	   char name[1000];
	   int init; //boolean
	}Table;
        Table tbl[1000];
        int size=0;//holds location we are at for tbl
%}

%union {
   int sv;
   struct {
      int v;
      char s[1000];
   } attr;
}
%token <sv> ICONSTnumber
%token PROGRAMnumber
%token PRINTnumber
%token ISnumber
%token BEGINnumber
%token ENDnumber
%token VARnumber
%token DIVnumber
%token SEMInumber
%token LPARENnumber
%token MINUSnumber
%token TIMESnumber
%token COMMAnumber
%token RPARENnumber
%token PLUSnumber
%token EQnumber
%token <sv> IDnumber

%type <attr> exp
%type <attr> term
%type <attr> factor
%type <attr> S
%type <attr> I
%type <attr> statement
%type <attr> compoundstatement
%type <attr> declaration

%%
program:           PROGRAMnumber {print_header();} IDnumber ISnumber compoundstatement {print_end();}
	           ;

compoundstatement: BEGINnumber S ENDnumber
		   {
		      
		   }
		   ;

S:                 statement
		   {
		      strcpy($$.s, $1.s);
		   }
		   | S SEMInumber statement 
		   {
		      strcpy($$.s, $3.s);
		   }
		   ;

statement:         IDnumber EQnumber exp
		   {
                      int i = 0;
		      if(inTable(string_table + $1) != -1){
		        i = inTable(string_table + $1);//get location of our var in tbl
			tbl[i].value = $3.v;
			tbl[i].init = 1;
			fprintf(outfile, "%s = %s;\n", tbl[i].name, $3.s);
      		        sprintf($$.s, "%s = %s", tbl[i].name, $3.s); 
		      }                                           
		      else{
			printf("Referencing an undeclared variable on line %d.\n", yyline);
			exit(0);	
		      }
		   }
		   | PRINTnumber exp 
		   {
		      printf("%d\n", $2.v);
		      fprintf(outfile, "cout << %s << endl;\n", $2.s);
		     
		   }
 		   | declaration
		   {
		      strcpy($$.s, $1.s);
		   }
		   ;

declaration:	   VARnumber I
		   {
		      fprintf(outfile, "int %s;\n", $2.s);
		   }
		   ;

I:                 IDnumber
		   {
		      if(inTable(string_table+$1) == -1){
                        strcpy(tbl[size].name, string_table+$1);
			tbl[size].init = 0;
                        size++;
                        strcpy($$.s, string_table+$1);
                      }
		      else{
			printf("Error at line %d; variable \'%s\' already exists!\n", yyline, (string_table+$1));
			exit(0);	
		      }
		   }
		   | I COMMAnumber IDnumber 
		   {
		      if(inTable(string_table+$3) == -1){
                        strcpy(tbl[size].name, string_table+$3);
			tbl[size].init = 0;
                        size++;
		        sprintf($$.s, "%s, %s", $1.s, string_table+$3);
                      }
		      else{ 
                        printf("Error at line %d; variable \'%s\' already exists!\n", yyline, (string_table+$3));
                        exit(0);
                      }
		   }
		   ;

exp:    	   MINUSnumber term
		   {
		      $$.v = -1 * $2.v;
		      sprintf($$.s, "-%s", $2.s);
		   }
		   | term
		   {
 		      $$.v = $1.v;
		      strcpy($$.s, $1.s);
		   }
		   | exp PLUSnumber term
		   {
		      $$.v = $1.v + $3.v;
		      sprintf($$.s, "%s+%s", $1.s, $3.s);
		   }
		   | exp MINUSnumber term
		   {
		      $$.v = $1.v - $3.v;
		      sprintf($$.s, "%s-%s", $1.s, $3.s);
		   }
		   ;

term: 		   factor
		   {
		      $$.v = $1.v; strcpy($$.s, $1.s);
		   }
		   | term TIMESnumber factor
		   {
		      $$.v = $1.v * $3.v;
		      sprintf($$.s, "%s*%s", $1.s, $3.s);
		   }
		   | term DIVnumber factor
		   {
		      if($3.v == 0){
		         printf("Divide by zero error at line %d\n", yyline);
		         exit(0);
		      }
		      $$.v = $1.v / $3.v;
		      sprintf($$.s, "%s/%s", $1.s, $3.s);
		   }
		   ;

factor:		   ICONSTnumber
		   {
		      $$.v = $1;
		      sprintf($$.s, "%d", $1);
		   }
		   | IDnumber
		   {
		      int i = inTable(string_table+$1);
		      if(i >= 0){
			if(tbl[i].init == 1){
		      	  $$.v = tbl[i].value;
		      	  strcpy($$.s, string_table+$1);
		      	}
			else{
			  printf("Referencing an uninitialized variable on line %d.\n", yyline);
			  exit(0); 
			}
 		      }
		      else{
		      	printf("Error at line %d: variable \'%s\' has not yet been declared!\n", yyline, string_table+$1);
		      	exit(0);
		      }
		   }
		   | LPARENnumber exp RPARENnumber
		   {
		      $$.v = $2.v;
		      sprintf($$.s, "(%s)", $2.s);
		   }
		   ;

%%
#include <stdio.h>
int inTable(const char * name){
   int i = 0;
   for(; i < size; i++)
      if(!strcmp(tbl[i].name, name))//strcmp returns 0 on valid
         return i;//return location
   return -1;//not in tbl

}
void print_header(){
   if((outfile = fopen("mya.cpp", "w")) == NULL){
      printf("Can't open file mya.cpp.\n");
      exit(0);
   }

   fprintf(outfile, "#include <iostream>\n");
   fprintf(outfile, "#include <stdio.h>\n");
   fprintf(outfile, "using namespace std;\n");
   fprintf(outfile, "\nint main()\n");
   fprintf(outfile, "{\n");
}
void print_end(){
   fprintf(outfile, "}\n");
   fclose(outfile);
}
int  yyerror(char *msg){return fprintf(stderr, "line %d: %s\n", yyline, msg);}
int main(){
   yyparse();
}
