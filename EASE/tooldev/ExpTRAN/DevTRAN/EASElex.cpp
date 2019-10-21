#include "stdafx.h"
#include "malloc.h"
#include "libopts.h"
#include "math.h"
#include "EASElex.h"

void EASElex_addTypes() {
#ifdef _TOKEN
addEType(E_TXTLIT_F(_T("TOKEN")), 3002,    1, 0);
#endif
}
EASElex_sys* EASElex;

void EASElex_init() {
EASElex = (EASElex_sys*)E_CREATE_F( 0,3002, sizeof(EASElex_sys));
EASElex_sets();
EASElex_addTypes();
}
void EASElex_sets() {
       return;
}
void d_TOKEN(struct TOKEN*& EPTR) {
       E_TXTASG_R(&EPTR->LEXEME, 0);
       E_DESTROY_R(EPTR);
       EPTR = (struct TOKEN*)0;
       return;
}
struct TOKEN* c_TOKEN() {
struct TOKEN* EPTR= 0;
struct TOKEN* rval = 0;
       EPTR = (struct TOKEN*)E_CREATE_F(3002, 1, Z_TOKEN);
       rval = (struct TOKEN*)EPTR;
goto retlbl;
retlbl:
       return rval;
}
void PRINTLEX() {
int I= 0;
int J= 0;
       OPENO_R(6, E_TXTLIT_F(_T("vlexer.dat")));
       USE_R(6, 2);
       I = 0;
       goto test0001;
next0001:
       I = I+1;
test0001:
       if (I > 7) {
       goto done0001;
       }
       J = 1;
       goto test0002;
next0002:
       J = J+1;
test0002:
       if (J > 16) {
       goto done0002;
       }
       WTI_R(EASElex->CHARTYPE[I*16+J], 1);
       WTS_R(2);
       goto next0002;
done0002:
       WTL_R();
       goto next0001;
done0001:
       WTL_R();
       I = 1;
       goto test0003;
next0003:
       I = I+1;
test0003:
       if (I > 14) {
       goto done0003;
       }
       J = 1;
       goto test0004;
next0004:
       J = J+1;
test0004:
       if (J > 8) {
       goto done0004;
       }
       WTI_R(EASElex->NEXTSTATE[I][J], 2);
       WTS_R(2);
       goto next0004;
done0004:
       WTL_R();
       goto next0003;
done0003:
       WTL_R();
       I = 1;
       goto test0005;
next0005:
       I = I+1;
test0005:
       if (I > 14) {
       goto done0005;
       }
       J = 1;
       goto test0006;
next0006:
       J = J+1;
test0006:
       if (J > 8) {
       goto done0006;
       }
       WTI_R(EASElex->ACTION[I][J], 1);
       WTS_R(2);
       goto next0006;
done0006:
       WTL_R();
       goto next0005;
done0005:
       WTL_R();
       I = 1;
       goto test0007;
next0007:
       I = I+1;
test0007:
       if (I > 14) {
       goto done0007;
       }
       WTI_R(EASElex->TOKENFORM[I], 1);
       WTS_R(2);
       goto next0007;
done0007:
       WTL_R();
       CLOSE_R(6);
       goto retlbl;
retlbl:
       return;
}
void INITLEX(Etxt* SYSDIR) {
int I= 0;
int J= 0;
int I_0001= 0;
int I_0002= 0;
int I_0003= 0;
int I_0004= 0;
int I_0005= 0;
int I_0006= 0;
E_TXTINC_R(SYSDIR);
       EASElex->CHARTYPE = (int*)calloc(128 + 1, sizeof(int));
       EASElex->CHARTYPE[0] = (int)(128);
       I_0001 = 14;
       EASElex->NEXTSTATE = (int**)calloc(I_0001 + 1, sizeof(int*));
       EASElex->NEXTSTATE[0] = (int*)(I_0001);
       I_0003 = 8;
       I_0002 = 1;
       goto test0001;
next0001:
       I_0002 = I_0002+1;
test0001:
       if (I_0002 > I_0001) {
       goto done0001;
       }
       EASElex->NEXTSTATE[I_0002] = (int*)calloc(I_0003 + 1, sizeof(int));
       EASElex->NEXTSTATE[I_0002][0] = (int)(I_0003);
       goto next0001;
done0001:
       I_0004 = 14;
       EASElex->ACTION = (int**)calloc(I_0004 + 1, sizeof(int*));
       EASElex->ACTION[0] = (int*)(I_0004);
       I_0006 = 8;
       I_0005 = 1;
       goto test0002;
next0002:
       I_0005 = I_0005+1;
test0002:
       if (I_0005 > I_0004) {
       goto done0002;
       }
       EASElex->ACTION[I_0005] = (int*)calloc(I_0006 + 1, sizeof(int));
       EASElex->ACTION[I_0005][0] = (int)(I_0006);
       goto next0002;
done0002:
       EASElex->TOKENFORM = (int*)calloc(14 + 1, sizeof(int));
       EASElex->TOKENFORM[0] = (int)(14);
       OPENI_R(5, CONCAT_F(SYSDIR, E_TXTLIT_F(_T("\\lexer.dat"))));
       USE_R(5, 1);
       I = 1;
       goto test0003;
next0003:
       I = I+1;
test0003:
       if (I > 128) {
       goto done0003;
       }
       EASElex->CHARTYPE[I] = (int)RDN_F();
       goto next0003;
done0003:
       I = 1;
       goto test0004;
next0004:
       I = I+1;
test0004:
       if (I > 14) {
       goto done0004;
       }
       J = 1;
       goto test0005;
next0005:
       J = J+1;
test0005:
       if (J > 8) {
       goto done0005;
       }
       EASElex->NEXTSTATE[I][J] = (int)RDN_F();
       goto next0005;
done0005:
       RDL_R();
       goto next0004;
done0004:
       I = 1;
       goto test0006;
next0006:
       I = I+1;
test0006:
       if (I > 14) {
       goto done0006;
       }
       J = 1;
       goto test0007;
next0007:
       J = J+1;
test0007:
       if (J > 8) {
       goto done0007;
       }
       EASElex->ACTION[I][J] = (int)RDN_F();
       goto next0007;
done0007:
       goto next0006;
done0006:
       RDL_R();
       I = 1;
       goto test0008;
next0008:
       I = I+1;
test0008:
       if (I > 14) {
       goto done0008;
       }
       EASElex->TOKENFORM[I] = (int)RDN_F();
       goto next0008;
done0008:
       CLOSE_R(5);
       Dict->F_DICT = (DICTENTRY**)calloc(128 + 1, sizeof(DICTENTRY*));
       Dict->F_DICT[0] = (DICTENTRY*)(128);
       goto retlbl;
retlbl:
E_TXTDEL_R(SYSDIR);
       return;
}
void ANALYZE(Etxt* BUFFER, int BUFFERLEN, int SEEKDICT) {
int STARTPOS= 0;
int CURRPOS= 0;
int CTYPE= 0;
int THISCHAR= 0;
int CURRSTATE= 0;
int NXTSTATE= 0;
int ACTN= 0;
int TOKENTYPE= 0;
E_TXTINC_R(BUFFER);
       CURRPOS = 1;
       STARTPOS = 1;
next0001:
       if ( !  ( CURRPOS <= BUFFERLEN+1 ) ) {
       goto done0001;
       }
       if (CURRPOS > BUFFERLEN) {
       CTYPE = 0;
       }
       else {
       THISCHAR = ACHAR_F(BUFFER, CURRPOS);
       if (THISCHAR > 127) {
       QACHAR_F(BUFFER, CURRPOS, 32);
       THISCHAR = ACHAR_F(BUFFER, CURRPOS);
       }
       if (CURRSTATE != 4 &  ( THISCHAR > 96 & THISCHAR < 123 ) ) {
       QACHAR_F(BUFFER, CURRPOS, THISCHAR-32);
       THISCHAR = ACHAR_F(BUFFER, CURRPOS);
       }
       CTYPE = EASElex->CHARTYPE[THISCHAR+1];
       }
       NXTSTATE = EASElex->NEXTSTATE[CURRSTATE+1][CTYPE+1];
       TOKENTYPE = EASElex->TOKENFORM[CURRSTATE+1];
       ACTN = EASElex->ACTION[CURRSTATE+1][CTYPE+1];
       if (ACTN == 0) {
       STARTPOS = STARTPOS+1;
       goto CONT;
       }
       if (ACTN == 1) {
       goto CONT;
       }
       if (ACTN == 2) {
       MAKETOKEN(BUFFER, STARTPOS, CURRPOS-1, TOKENTYPE, SEEKDICT);
       STARTPOS = CURRPOS;
       goto CONT;
       }
       if (ACTN == 3) {
       MAKETOKEN(BUFFER, STARTPOS, CURRPOS-1, TOKENTYPE, SEEKDICT);
       STARTPOS = CURRPOS+1;
       goto CONT;
       }
       if (ACTN == 4) {
       if (STARTPOS < CURRPOS) {
       MAKETOKEN(BUFFER, STARTPOS, CURRPOS-1, TOKENTYPE, SEEKDICT);
       }
       MAKETOKEN(BUFFER, CURRPOS, CURRPOS, 0, SEEKDICT);
       STARTPOS = CURRPOS+1;
       goto CONT;
       }
       if (ACTN == 5) {
       MAKETOKEN(BUFFER, STARTPOS+1, CURRPOS-1, 4, SEEKDICT);
       STARTPOS = CURRPOS+1;
       goto CONT;
       }
       if (ACTN == 6) {
       MAKETOKEN(BUFFER, STARTPOS, CURRPOS, 0, SEEKDICT);
       STARTPOS = CURRPOS+1;
       goto CONT;
       }
       if (ACTN == 7) {
       STARTPOS = CURRPOS+1;
       goto CONT;
       }
CONT:
       CURRPOS = CURRPOS+1;
       CURRSTATE = NXTSTATE;
       goto next0001;
done0001:
       goto retlbl;
retlbl:
E_TXTDEL_R(BUFFER);
       return;
}
void MAKETOKEN(Etxt* BUFF, int BEGIN, int END, int TTYPE, int SEEKDICT) {
int LEN= 0;
struct TOKEN* ATOKEN= 0;
E_TXTINC_R(BUFF);
next0001:
       if ( !  ( ACHAR_F(BUFF, END) == 46 ) ) {
       goto done0001;
       }
       END = END-1;
       goto next0001;
done0001:
       if (BEGIN > END) {
       if (TTYPE != 4) {
       goto retlbl;
       }
       BEGIN = BEGIN-1;
       END = END+1;
       }
       LEN = END-BEGIN+1;
       ATOKEN= c_TOKEN();
       E_TXTASG_R(&ATOKEN->LEXEME, SUBSTR_F(BUFF, BEGIN, LEN));
       ATOKEN->TOKENTYPE = TTYPE;
       if (TTYPE == 3) {
next0002:
       if ( !  ( LEN > 0 ) ) {
       goto done0002;
       }
       if (ACHAR_F(ATOKEN->LEXEME, LEN) == 46) {
       QACHAR_F(ATOKEN->LEXEME, LEN, 95);
       }
       LEN = LEN-1;
       goto next0002;
done0002:
;      }
       FILETOKEN(ATOKEN);
       if (SEEKDICT != 0) {
       ATOKEN->DICTREF = (struct DICTENTRY*)FINDDICTENTRY_F(ATOKEN->LEXEME);
       }
       goto retlbl;
retlbl:
E_TXTDEL_R(BUFF);
       return;
}
void FILETOKEN(struct TOKEN* ATOKEN) {
       if (EASElex->F_TOKENLIST == 0) {
       EASElex->F_TOKENLIST = (struct TOKEN*)ATOKEN;
       }
       else {
       EASElex->L_TOKENLIST->S_TOKENLIST = (struct TOKEN*)ATOKEN;
       }
       EASElex->L_TOKENLIST = (struct TOKEN*)ATOKEN;
       goto retlbl;
retlbl:
       return;
}
