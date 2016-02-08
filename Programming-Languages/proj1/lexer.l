/*
	Tyler Kelly : tck13
*/
%{
	int yyline = 1, yycolumn = 1, yylval = 0;
        char string_table[20000];
%}

%%
;                                {yycolumn+=yyleng;return SEMInumber;}
[(][*][^*]*[*]+([^*)][^*]*[*]+)*[)]   {yycolumn+=yyleng;}
\(                               {yycolumn+=yyleng;return LPARENnumber;}
[0-9]*                           {yycolumn+=yyleng;yylval = atoi(yytext);return ICONSTnumber;}
[Bb][Ee][Gg][Ii][Nn]             {yycolumn+=yyleng;return BEGINnumber;}
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]     {yycolumn+=yyleng;return PROGRAMnumber;}
\-                               {yycolumn+=yyleng;return MINUSnumber;}
\*                               {yycolumn+=yyleng;return TIMESnumber;}
[Vv][Aa][Rr]                     {yycolumn+=yyleng;return VARnumber;}
<<EOF>>                          {yycolumn+=yyleng;return EOFnumber;}
,                                {yycolumn+=yyleng;return COMMAnumber;}
\)                               {yycolumn+=yyleng;return RPARENnumber;}
[Ee][Nn][Dd]                     {yycolumn+=yyleng;return ENDnumber;}
[Ii][Ss]                         {yycolumn+=yyleng;return ISnumber;}
\+                               {yycolumn+=yyleng;return PLUSnumber;}
[Dd][Ii][Vv]                     {yycolumn+=yyleng;return DIVnumber;}
[Pp][Rr][Ii][Nn][Tt]             {yycolumn+=yyleng;return PRINTnumber;}
=                                {yycolumn+=yyleng;return EQnumber;}
[a-zA-Z]+[0-9]*                  {yycolumn+=yyleng;yylval = put_string(yytext, yyleng); return IDnumber;}
\n                               {yyline++; yycolumn = 1;}
[\t]+                            {yycolumn+=yyleng;}
[ ]+                             {yycolumn+=yyleng;}
.                                {printf("Unknown character %s, line = %d, column = %d\n", yytext, yyline, yycolumn);}
%%
int put_string(char * value, int length){
      	if(!value || length < 0){
		printf("Invalid parameters passes");
		exit(0);
	}
	int loc = strlen(string_table);
	if(loc + length > 20000){
		printf("Unable to add any more characters; string_table capacity exceeded");
                exit(0);
	}
        strcat(string_table, value);
	return loc;
}
