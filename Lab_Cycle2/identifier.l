%{
#include "y.tab.h"
%}

%option noyywrap

%%

[a-zA-Z]    { return LETTER; }
[0-9]       { return DIGIT; }
[ \t\n]     { return 0; }
.           { return yytext[0]; }

%%

