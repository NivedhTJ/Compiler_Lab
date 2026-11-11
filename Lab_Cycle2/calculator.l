%{
#include <stdlib.h>
#include "y.tab.h"
%}

%option noyywrap

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]       ;
\n          { return '\n'; }
.           { return yytext[0]; }

%%
