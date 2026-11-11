%{
#include "y.tab.h"
%}

%%

[0-9]+              { return NUMBER; }
[ \t]+              ;
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"("                 { return '('; }
")"                 { return ')'; }
\n                  { return 0; }
.                   { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}

