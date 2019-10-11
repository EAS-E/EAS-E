#include "stdafx.h"
#include "malloc.h"
#include "easlib.h"
#include "libopts.h"
#ifdef EASsets
#include "easeSets.h"
#endif

struct uib {
	int rlen;
	int col;
	int openerr;
	int eof;
	int unit;
	bool out;
	FILE* file;
	TCHAR buffer[256];
	uib* s_uibs;
};

uib* f_uibws;
uib* f_uibrs;
uib* uib_w;
uib* uib_r;

void E_ERROR_R(int E_ERRNO) {
	;
}

typeInfo* f_typeInfos;


void iRefDel(iRef* iref) {
	iRef* last;
	typeInfo* info;

	WTX_R(E_TXTLIT_F(_T("Deleting: ")));
	WTI_R(iref->persistId, 4);
	WTL_R();

	info = f_typeInfos;
	while (info) {
		if (info->ssId == iref->ssId & info->entId == iref->typeId)
			break;
		info = info->s_typeInfo;
	}
	if (iref->maddr)
		delete iref->maddr;
	if (iref == info->f_irefs)
		info->f_irefs = iref->s_irefs;
	else {
		last = info->f_irefs;
		while (last) {
			if (last->s_irefs == iref) {
				last->s_irefs = iref->s_irefs;
					break;
			}
			last = last->s_irefs;
		}
	}
#ifdef EASpersist
	deleteInstance(iref); // tell the custodian to 'release' iref->dbid
#endif
	delete iref;
}

char* fetch(iRef* iref) {
	char* buff;

	if (iref == NULL)
		return NULL;
#ifdef EASpersist
	if (iref->maddr == NULL)
		persistFetch(iref);		// unpack retrieved instance, allocate and fill iref->maddr
#endif
	return (char*)iref->maddr;
}




iRef* E_PCREATE_F(int subsysid, int entId, int size) {
	iRef* iref = NULL;
	eInstHdr* instance;
	typeInfo* info;

	iref = (iRef*)calloc(1, sizeof(iRef));
	iref->ssId = subsysid;
	iref->typeId = entId;
#ifdef EASpersist
	newInstance(iref);			// get new Id from 'custodian'
#endif
	info = f_typeInfos;
	while (info) {
		if (info->ssId == subsysid & info->entId == entId)
			break;
		info = info->s_typeInfo;
	}
	iref->s_irefs = info->f_irefs;
	info->f_irefs = iref;
	iref->refcount = -1;	// signify persistent
	instance = (eInstHdr*)calloc(1, size);
	instance->entID = entId;
	instance->DBID = subsysid;
	iref->maddr = instance;
	return iref;
}


eInstHdr* E_CREATE_F(int subsysid, int entId, int size) {
	eInstHdr* instance;

	instance = (eInstHdr*)calloc(1, size);
	instance->entID = entId;
	instance->DBID = subsysid;

	return instance;
}


void E_DESTROY_R(void* ptr) {
	free(ptr);
	return;
}

void E_PDESTROY_R(void* ptr) {
	iRef* iref;

	iref = (iRef*)ptr;
	if (iref->refcount > 1)
		iref->refcount = 0;	// just so as I can break here for debug!
	//free(iref->maddr);
	iRefDel(iref);
	return;
}

#ifdef EASsets

void E_DELSET_R(void* set) {
	E_SET* x;
	x = (E_SET*)set;
	if (x->F_MEMBERS)
		E_ERROR_R(100);
	free(set);
}

void E_PDELSET_R(void* set) {
	E_PSET* x = 0;

	easg((char*)&x, (iRef*)set);
	if (x->F_PMEMBERS)
		E_ERROR_R(100);
	iRefDel((iRef*)set);
}

void E_FRANK_R(void* SET, void* ENT, int(fn)(void*, void*)) {
	void* X;
	E_SET* set;
	set = (E_SET*)SET;
	X = F_EASSET_F(SET);
	if (X == NULL) {
		E_FFIRST_R(set, (eInstHdr*)ENT);
		return;
	}
	while (fn(ENT, X) < 0) {
		X = S_EASSET_F(X, set->SETNAME);
		if (X == NULL)
			break;
	}
	if (X == NULL) {
		E_FLAST_R(SET, ENT);
		return;
	}
	E_FBEFOR_R(SET, ENT, X);
}

void E_PFRANK_R(void* SET, void* ENT, int(fn)(void*, void*)) {
	E_PINSTH* ent = 0;
	E_PSET* set = 0;
	void* X = 0;
	easg((char*)&set, (iRef*)SET);
	easg((char*)&ent, (iRef*)ENT);
	X = F_PEASSET_F(SET);
	if (X == NULL) {
		E_PFFIRST_R(set, ent);
		return;
	}
	while (fn(ENT, X) < 0) {
		X = S_PEASSET_F(X, ((struct E_PSET*)fetch((iRef*)set))->PSETNAME);
		if (X == NULL)
			break;
	}
	if (X == NULL) {
		E_PFLAST_R(set, ent);
		return;
	}
	E_PFBEFOR_R(set, ent, X);
}

#endif

void E_TXTINC_R(Etxt* txt) {

	if (txt != NULL) {
		txt->refCount++;
	}
}

void E_TXTDEL_R(Etxt* txt) {

	if (txt != NULL) {
		if (txt->refCount > 1)
			txt->refCount--;
		else {
			free(txt->tValue);
			free(txt);
			txt = NULL;
		}
	}
}

void E_TXTD_R(Etxt*& txt) {

	if (txt != NULL) {
		if (txt->refCount > 1)
			txt->refCount--;
		else {
			free(txt->tValue);
			free(txt);
			txt = NULL;
		}
	}
}

void E_TXTASG_R(Etxt** dest, Etxt* src) {

	if (*dest != NULL)
		E_TXTD_R(*dest);
		*dest = src;
		if (src != NULL) {
			src->refCount++;
	}
}

int ACHAR_F(Etxt* txt, int index) {
	int val = 0;
	if (txt != NULL) {
		if (index <= txt->tLength)
			val = txt->tValue[index - 1];
		txt->refCount++;
		E_TXTDEL_R(txt);
	}
	return val;
}
void QACHAR_F(Etxt* txt, int index, int val) {
	if (txt != NULL) {
		if (index <= txt->tLength)
			txt->tValue[index - 1] = val;
		txt->refCount++;
		E_TXTDEL_R(txt);
	}
}

int LENGTH_F(Etxt* txt) {
	int len = 0;
	if (txt != NULL) {
		len = txt->tLength;
		txt->refCount++;
		E_TXTDEL_R(txt);
	}
	return len;
}
Etxt* E_TXTLIT_F(TCHAR* lit) {
	
	int len;
	Etxt* eTxt = NULL;
	
	len = _tcslen(lit);
	if (len > 0) {
		eTxt = (Etxt*)calloc(1, sizeof(Etxt));
		eTxt->tLength = len;
		eTxt->tValue = (TCHAR*)calloc(len + 1, sizeof(TCHAR));
		eTxt->tValue[len] = 0;
		for (len; len > 0; len--)
			eTxt->tValue[len-1] = lit[len-1];
	}
	return eTxt;
}

int E_TXTEQL_F(Etxt* txt1, Etxt* txt2) {
	int len1 = 0;
	int len2 = 0;
	int eql = 1;

	if (txt1 != NULL) {
		len1 = txt1->tLength;
		txt1->refCount++;
	}
	if (txt2 != NULL) {
		len2 = txt2->tLength;
		txt2->refCount++;
	}
	if (len1 != len2)
		eql = 0;
	else {
		for (len1; len1 > 0; len1--) {
			if (txt1->tValue[len1 - 1] != txt2->tValue[len1 - 1]) {
				eql = 0;
				break;
			}
		}
	}
	E_TXTDEL_R(txt1);
	E_TXTDEL_R(txt2);
	return eql;
}

int E_TXTNEQ_F(Etxt* txt1, Etxt* txt2) {
	if (E_TXTEQL_F(txt1, txt2) == 1)
		return 0;
	return 1;
}

Etxt* CONCAT_F(Etxt* txt1, Etxt* txt2) {

	int len1 = 0;
	int len2 = 0;
	Etxt* result = 0;

	if (txt1 != NULL) {
		len1 = txt1->tLength;
		txt1->refCount++;
	}
	if (txt2 != NULL) {
		len2 = txt2->tLength;
		txt2->refCount++;
	}
	if (len1 + len2 != 0) {
		result = (Etxt*)calloc(1, sizeof(Etxt));
		result->tLength = len1 + len2;
		result->tValue = (TCHAR*)calloc(len1 + len2 + 1, sizeof(TCHAR));
		for (len2; len2 > 0; len2--)
			result->tValue[len1 + len2 - 1] = txt2->tValue[len2 - 1];
		for (len1; len1 > 0; len1--)
			result->tValue[len1 - 1] = txt1->tValue[len1 - 1];
	}
	E_TXTDEL_R(txt1);
	E_TXTDEL_R(txt2);
	return result;
}

Etxt* SUBSTR_F(Etxt* txt, int begin, int len) {

	Etxt* result = 0;
	int i;

	begin--;		// EAS is 1-based, not zero-based
	if (begin < 0)
		return NULL;

	if (txt != NULL) {
		txt->refCount++;
		if (len > 0 & begin <= txt->tLength) {
			result = (Etxt*)calloc(1, sizeof(Etxt));
			result->tLength = len;
			result->tValue = (TCHAR*)calloc(len + 1, sizeof(TCHAR));
			for (i = 0; i < len; i++) {
				result->tValue[i] = txt->tValue[begin + i];
			}
		}
	}
	E_TXTDEL_R(txt);
	return result;
}

void QSUBSTR_F(Etxt* txt, int begin, int len, Etxt* val) {

	Etxt* result = 0;
	int i;

	if (len <= 0)
		return;

	if (begin < 1)
		return;

	begin--;		// C is zero-based

	if (txt != NULL) {
		txt->refCount++;
		if (val != NULL) {
			val->refCount++;
			for (i = 0; i < len; i++) {
				if (begin + i == txt->tLength)
					break;
				txt->tValue[begin + i] = val->tValue[i];
			}
			E_TXTDEL_R(val);
		}
		E_TXTDEL_R(txt);
	}
	return;
}

uib* finduibw(int unit, bool create) {
	uib* auib;
	auib = f_uibws;
	while (auib) {
		if (auib->unit == unit)
			break;
		auib = auib->s_uibs;
	}
	if (auib == NULL & create) {
		auib = (uib*)calloc(1, sizeof(uib));
		auib->unit = unit;
		auib->out = true;
		auib->s_uibs = f_uibws;
		f_uibws = auib;
	}
	return auib;
}

uib* finduibr(int unit, bool create) {
	uib* auib;
	auib = f_uibrs;
	while (auib) {
		if (auib->unit == unit)
			break;
		auib = auib->s_uibs;
	}
	if (auib == NULL & create == true) {
		auib = (uib*)calloc(1, sizeof(uib));
		auib->unit = unit;
		auib->s_uibs = f_uibrs;
		f_uibrs = auib;
	}
	return auib;
}

void OPENO_R(int unit, Etxt* filename) {

	uib* auib;
	errno_t ferr;
	int i;

	auib = finduibw(unit, true);
	if (auib->file != NULL)		// already open?
		E_ERROR_R(201);
	if (filename != NULL & unit != 0) {
		filename->refCount++;
//		auib->file = _wfopen(filename->tValue, _T("w"));
		ferr = _wfopen_s(&auib->file, filename->tValue, _T("w"));
		for (i = 0; i < 255; i++)
			auib->buffer[i] = *(_T(" "));
		E_TXTDEL_R(filename);
	}
}

void OPENI_R(int unit, Etxt* filename) {

	uib* auib;
	errno_t ferr;

	auib = finduibr(unit, true);
	if (auib->file != NULL)		// already open?
		E_ERROR_R(201);
	if (filename != NULL & unit != 0) {
		filename->refCount++;
		ferr = _wfopen_s(&auib->file, filename->tValue, _T("r"));
//		auib->file = _wfopen(filename->tValue, _T("r"));
		auib->eof = 0;
		auib->openerr = 0;
		if (ferr != 0)
			auib->openerr = 1;
		E_TXTDEL_R(filename);
//		RDL_R();  .. not yet.. READ.V not set
	}
}

void CLOSE_R(int unit) {
	uib* auib;
	errno_t ferr;

	auib = finduibr(unit, false);
	if (auib == NULL)
		auib = finduibw(unit, false);

	if (auib) {
		if (auib->file)
			ferr = fclose(auib->file);
		auib->file = NULL;
		auib->col = 0;
		auib->rlen = 0;
	}
}

void USE_R(int unit, int inout) {

	if (inout == 1) {
		uib_r = finduibr(unit, false);
		easlib->UIB_R = (UIB_R*)uib_r;
		easlib->UIB_R->EOF_V = uib_r->eof;
		easlib->UIB_R->ROPENERR_V = uib_r->openerr;
		easlib->READ_V = uib_r->unit;
		if (uib_r->openerr != 0)
			return;
		if (uib_r->col == 0 & uib_r->eof != 2)
			RDL_R();
	}
	if (inout == 2) {
		uib_w = finduibw(unit, true);	// kludge to allow write to console - see WTL_R
		easlib->UIB_W = (UIB_W*)uib_w;
		easlib->WRITE_V = uib_w->unit;
	}
}

void WTB_R(int col) {

	if (col < 1)
		return;

	uib_w->col = col - 1;
}

void WTX_R(Etxt* txt) {

	int i;

	if (txt) {
		txt->refCount++;
		for (i = 0; i < txt->tLength; i++) {
			uib_w->buffer[uib_w->col] = txt->tValue[i];
			uib_w->col++;
		}
		E_TXTDEL_R(txt);
	}
}

void WTS_R(int spcs) {				// write as S n
	int i;
	for (i = 0; i < spcs; i++) {
		uib_w->buffer[uib_w->col] = *(_T(" "));
		uib_w->col++;
	}
}

void WTI_R(int value, int width) {	// write as I n

	int digit;
	int rem = 0;
	int zero = 48;			// ascii "0"
	int i = 1;

	if (width <= 0)
		return;

	i = width - 1;
	uib_w->buffer[uib_w->col + i] = zero;
	while (value > 0) {
		rem = value / 10;
		digit = value - rem *(int)10;
		uib_w->buffer[uib_w->col + i] = zero + digit;
		i--;
		value = rem;
		if (i < 0)
			break;
	}
	if (rem > 0)
		uib_w->buffer[uib_w->col] = '!';	// field width overflow warning

	uib_w->col = uib_w->col + width;
}

int RDI_F(int width) {	// read as I n

	int value = 0;
	int digit;
	int sign = 0;
	int zero = 48;			// ascii "0"
	int i = 0;

	while (i < width) {
		digit = uib_r->buffer[uib_r->col-1];

		if (digit >= zero) 
			value = value * 10 + digit - zero;
		else
		{
			if (sign == 0) {
				if (uib_r->buffer[uib_r->col + i] == 45)
					sign = 1;
			}
		}
		i++;
		uib_r->col++;
	}
	if (sign != 0)
		value = -value;
	return value;
}

void WTT_R(Etxt* txt, int width) {	// write as T n

	int i;

	if (txt == NULL)
		return;

	txt->refCount++;
	for (i = 0; i < width; i++) {
		if (i < txt->tLength)
			uib_w->buffer[uib_w->col] = txt->tValue[i];
		else
			uib_w->buffer[uib_w->col] = *(_T(" "));
		uib_w->col++;
	}
	E_TXTDEL_R(txt);
}

void WTL_R() {

	int i;

	if (uib_w->file == 0) {				// console ?
		uib_w->buffer[uib_w->col] = 0;
		_tprintf(uib_w->buffer);
		printf("\n");
		for (i = 0; i < uib_w->col + 1; i++) {
			uib_w->buffer[i] = *(_T(" "));
		}
		uib_w->col = 0;
		return;
	}

	uib_w->buffer[uib_w->col] = *(_T("\n"));
	for (i = 0; i < uib_w->col+1; i++) {
		_fputtc(uib_w->buffer[i], uib_w->file);
		uib_w->buffer[i] = *(_T(" "));
	}
	fflush(uib_w->file);
	uib_w->col = 0;
}

void RDB_R(int rcol) {
	if (rcol < uib_r->rlen)
		uib_r->col = rcol;
}



void RDL_R() {

	int i;
	TCHAR ch;
	bool done = false;


	uib_r->col = 0;
	uib_r->rlen = 0;

	for (i = 0; i < 256; i++) {
		ch = _fgettc(uib_r->file);
		if (ch == EOF | ch == WEOF) {	// end-of-file?...
			if (i == 0) {		// ... with nothing read?
				if (uib_r->eof == 0)
					E_ERROR_R(99);
				uib_r->eof = 2;
			}
			done = true;
		}
		else {
			if (ch != (int)10)			// end of record
				uib_r->buffer[i] = ch;
			else
				done = true;
		}

		if (done)
			break;
	}
	uib_r->rlen = i;
	if (uib_r->rlen > 0)
		uib_r->col = 1;
}




//void RDL_R() {
//
//	int i;
//	TCHAR ch;
//
//	for (i = 0; i < 256; i++) {
//		ch = _fgettc(uib_r->file);
//		if (ch == EOF | ch == WEOF) {
//			easlib->UIB_R->EOF_V = 2;
//			return;
//		}
//
//		if (ch != (int)10)
//			uib_r->buffer[i] = ch;
//		else
//			break;
//	}
//	uib_r->rlen = i;
//	if (uib_r->rlen > 0)
//		uib_r->col = 1;
//	else
//		uib_r->col = 0;
//	easlib->UIB_R->RRECLEN_V = i;
//}

Etxt* RDX_F() {

	Etxt* str;
	int start = 0;
	int len;
	int i;

	while (uib_r->rlen == 0) {
		RDL_R();
		if (uib_r->eof == 2)
			return 0;
	}

	while (uib_r->col <= uib_r->rlen) {
		if (uib_r->buffer[uib_r->col - 1] != 32) {	// found a non-space
			start = uib_r->col;
			while (uib_r->buffer[uib_r->col - 1] != 32) {	
				uib_r->col++;
				if (uib_r->col > uib_r->rlen) {
					uib_r->rlen = 0;
					break;
				}
			}
		}
		if (start) {
			len = uib_r->col - start;
			str = (Etxt*)calloc(1, sizeof(Etxt));
			str->tLength = len;
			str->tValue = (TCHAR*)calloc(str->tLength + 1, sizeof(TCHAR));
			for (i = 0; i < str->tLength; i++) {
				str->tValue[i] = uib_r->buffer[start-1];
				start++;
			}
			return str;
		}
		uib_r->col++;
		if (uib_r->col > uib_r->rlen) {		// all blanks?
			uib_r->rlen = 0;
			while (uib_r->rlen == 0) {
				RDL_R();
				if (uib_r->eof == 2)
					return 0;
			}
		}
	}
	return NULL;
}

Etxt* RDT_F(int width) {

	Etxt* str = NULL;
	int i;

	if (uib_r->col == 0)
		return NULL;
	if (width <= 0)
		return NULL;

	str = (Etxt*)calloc(1, sizeof(Etxt));
	str->tLength = width;
	str->tValue = (TCHAR*)calloc(str->tLength + 1, sizeof(TCHAR));
	for (i = 0; i < str->tLength; i++) {
		str->tValue[i] = uib_r->buffer[uib_r->col-1];
		uib_r->col++;
	}
	return str;
}


Etxt* RDS_F() {		// read as T * - 'free-format'

	Etxt* str = NULL;
	int i;
	int delim;
	int len;

	while (uib_r->rlen == 0) {
		RDL_R();
		if (uib_r->eof == 2)
			return NULL;
	}
	//if (uib_r->col == 0)
	//	return NULL;

	while (uib_r->buffer[uib_r->col-1] == 32 & uib_r->col < uib_r->rlen)
		uib_r->col++;
	delim = uib_r->buffer[uib_r->col - 1];
	i = uib_r->col;
	while (uib_r->buffer[i] != delim & i < uib_r->rlen)
		i++;
	len = i - uib_r->col;
	if (len) {
		str = (Etxt*)calloc(1, sizeof(Etxt));
		str->tLength = len;
		str->tValue = (TCHAR*)calloc(str->tLength + 1, sizeof(TCHAR));
		for (i = 0; i < str->tLength; i++) {
			str->tValue[i] = uib_r->buffer[uib_r->col];
			uib_r->col++;
		}
		uib_r->col = uib_r->col + 2;
	}
	return str;
}

void* RES_F(int dim, int hdr) {
	return NULL;
}


int RDN_F() {				// free-form read an int

	int value = 0;
	int digit;
	int sign = 0;
	int zero = 48;			// ascii "0"
	int i;

	while (uib_r->rlen == 0) {
		RDL_R();
		if (uib_r->eof == 2)
			return 0;
	}

	while (uib_r->col <= uib_r->rlen) {
		if (uib_r->buffer[uib_r->col - 1] != 32) {	// found a non-space
			while (uib_r->buffer[uib_r->col - 1] > 47 & uib_r->buffer[uib_r->col - 1] < 58) {	// digits 0-9
				digit = uib_r->buffer[uib_r->col - 1];
				if (digit >= zero)
					value = value * 10 + digit - zero;
				else
				{
					if (sign == 0) {
						if (uib_r->buffer[uib_r->col - 1] == 45)
							sign = 1;
					}
				}
				uib_r->col++;
				if (uib_r->col > uib_r->rlen) {
					uib_r->rlen = 0;
					break;
				}
			}
			if (sign != 0)
				value = -value;
			return value;
		}
		uib_r->col++;
		if (uib_r->col > uib_r->rlen) {		// all blanks?
			uib_r->rlen = 0;
			while (uib_r->rlen == 0) {
				RDL_R();
				if (uib_r->eof == 2)
					return 0;
			}
		}
	}
	return 0;
}


Etxt* ITOT_F(int value) {

	Etxt* result;
	int digit;
	int rem;
	int zero = 48;			// ascii "0"
	int i = 1;
	bool minus = 0;
	TCHAR buff[12];
	int len;
	int j;

	if (value < 0) {
		minus = 1;
		value = -value;
	}
	while (value > 0) {
		rem = value / 10;
		digit = value - rem *(int)10;
		buff[12 - i] = zero + digit;
		i++;
		value = rem;
	}
	if (minus) {
		buff[12 - i] = 45;
		i--;
	}
	len = i - 1;
	j = 12 - len;
	result = (Etxt*)calloc(1, sizeof(Etxt));
	result->tLength = len;
	result->tValue = (TCHAR*)calloc(len + 1, sizeof(TCHAR));
	for (i = 0; i < len; i++) {
		result->tValue[i] = buff[j + i];
	}
	result->tValue[len + 1] = 0;
	return result;
}

//char* dref(char* eptr, int offset) {
//	int* v;
//	//	void* x;
//	v = (int*)(char*)(fetch((iRef*)eptr) + (int)offset);
//	//	x = (void*)(*v);
//	return (char*)(*(int*)(char*)(fetch((iRef*)eptr) + (int)offset));
//}
//
//void* aref(char* eptr, int offset) {
//	int* v;
//	v = (int*)(char*)(fetch((iRef*)eptr) + (int)offset);
//	return (void*)(v);
//}
//
//void* apref(char* eptr, int offset) {
//	int* v;
//	v = (int*)(char*)(fetch((iRef*)eptr) + (int)offset);
//	if (*v)
//		(*v) = 0;
//	return (void*)(v);
//}
//
//void* lasg(char* eptr) {
//	if (*eptr)
//		(*eptr) = 0;
//	return (void*)eptr;
//}


void easg(char* oldiref, iRef* newiref) {
	iRef* iref;
	iRef** iptr;

	iptr = (iRef**)oldiref;
	iref = (iRef*)(*iptr);
	if (iref != NULL) {
		iref->refcount--;
		if (iref->refcount == 0)
			iRefDel(iref);
	}
	if (newiref == 0) {
		(*iptr) = NULL;
		return;
	}
	iref = (iRef*)newiref;
	if (iref->refcount < 0) {			// this is a newly created instance
		iref->refcount = 1;
	}
	else 
		iref->refcount++;

	iptr = (iRef**)oldiref;
	(*iptr) = iref;
	iref = (iRef*)(*oldiref);	// just for debug inspection!
}

void eunasg(char* oldiref) {
	iRef* iref;
	iRef** iptr;

	iptr = (iRef**)oldiref;
	iref = (iRef*)(*iptr);
	if (iref != NULL) {
		iref->refcount--;
		if (iref->refcount == 0)
			iRefDel(iref);
	}
}


void addEType(Etxt* ename, int ssid, int entid, const int* map) {

	typeInfo* info;

	info = (typeInfo*)calloc(1, sizeof(typeInfo));
	E_TXTASG_R(&info->ename, ename);
	info->ssId = ssid;
	info->entId = entid;
	info->emap = map;
	info->s_typeInfo = f_typeInfos;
	f_typeInfos = info;
}

Etxt* E_TYPENAME_F(void* eptr) {

	typeInfo* info;
	eInstHdr* hdr;

	hdr = (eInstHdr*)eptr;

	info = f_typeInfos;
	while (info) {
		if (hdr->DBID == info->ssId & hdr->entID == info->entId)
			break;
		info = info->s_typeInfo;
	}
	if (info)
		return info->ename;
	return NULL;
}
