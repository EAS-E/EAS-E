#include "stdafx.h"
#include "malloc.h"
#include "easlib.h"
#include "easeSets.h"



struct uib {
	int eof;
	int rlen;
	int col;
	int unit;
	bool out;
	FILE* file;
	TCHAR buffer[256];
};


uib* uib_w;
uib* uib_r;

void err() {
	;
}

//iRef* f_irefs;
typeInfo* f_typeInfos;

char* dbfetch(int id) {
	return NULL;
}

int iRefLastId = 1;

int dbnew(int ssid, int entid) {
	return iRefLastId++;
}

void iRefDel(iRef* iref) {
	iRef* last;
	typeInfo* info;

	WTX_R(E_TXTLIT_F(_T("Deleting: ")));
	WTI_R(iref->dbId, 4);
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
	// tell the custodian to 'release' iref->dbid
	delete iref;
}

char* fetch(iRef* iref) {
	char* buff;
	if (iref->maddr == NULL) {
		buff = dbfetch(iref->dbId);
		// unpack instance from buff
		// allocate and fill iref->maddr
	}
	return (char*)iref->maddr;
}


//eInstHdr* F_EASSET_F(void* set) {
//	LIFO_SET* setent;
//
//	setent = (LIFO_SET*)set;
//	if (setent->f_members)
//		return setent->f_members->member;
//	return NULL;
//}
//
//eInstHdr* S_EASSET_F(void* ent, Etxt* setname) {
//	LIFO_SET* setent;
//	eInstHdr* mement;
//	membership* aCard = NULL;
//
//	mement = (eInstHdr*)ent;
//	aCard = mement->f_memberships;
//	while (aCard) {
//		if (_tcscmp(aCard->owningSet->setName->tValue, setname->tValue) == 0) {
//			setent = (LIFO_SET*)aCard->owningSet;
//			break;
//		}
//		aCard = aCard->s_memberships;
//	}
//	if (aCard) {
//		if (aCard->s_members)
//			return aCard->s_members->member;
//	}
//	return NULL;
//}

//int N_EASSET_F(void* set) {
//	int count = 0;
//	LIFO_SET* setent;
//	membership* aCard;
//
//	setent = (LIFO_SET*)set;
//	aCard = setent->f_members;
//	while (aCard) {
//		aCard = aCard->s_members;
//		count++;
//	}
//	return count;
//}

eInstHdr* E_INITSET_F(Etxt* setname, int dbId, int entId) {
	E_SETHDR* set;
	set = (E_SETHDR*)E_CREATE_F(dbId, entId, Z_E_SETHDR);
	E_TXTASG_R(&set->SETNAME, setname);
	return (eInstHdr*)set;
}

iRef* E_PINITSET_F(Etxt* setname, int dbId, int entId) {
	E_PSETHDR* set;
	iRef* iref;
	iref = E_PCREATE_F(dbId, entId, Z_E_PSETHDR);
	set = (E_PSETHDR*)iref->maddr;
	E_TXTASG_R(&set->PSETNAME, setname);
	return iref;
}

//iRef* c_E_PCARD() {
//	iRef* EPTR = 0;
//	iRef* rval = 0;
//	EPTR = (struct iRef*)E_PCREATE_F(0, 2, sizeof(E_PCARD));
//	rval = (iRef*)EPTR;
//	goto ret;
//ret:
//	return rval;
//}




void E_DELSET_R(void* set) {
	LIFO_SET* x;
	x = (LIFO_SET*)set;
	if (x->f_members)
		err();
	free(set);
}

void E_PDELSET_R(void* set) {
	E_PSETHDR* x  = 0;

	easg((char*)&x, (iRef*)set);
	if (x->F_PMEMBERS)
		err();
	iRefDel((iRef*)set);
}


iRef* E_PCREATE_F(int dbId, int entId, int size) {
	iRef* iref = NULL;
	eInstHdr* instance;
	typeInfo* info;

	iref = (iRef*)calloc(1, sizeof(iRef));
	iref->dbId = dbnew(entId, dbId);	// get new Id from 'custodian'
	iref->ssId = dbId;
	iref->typeId = entId;

	info = f_typeInfos;
	while (info) {
		if (info->ssId == dbId & info->entId == entId)
			break;
		info = info->s_typeInfo;
	}
	iref->s_irefs = info->f_irefs;
	info->f_irefs = iref;
	iref->refcount = -1;	// signify persistent
	instance = (eInstHdr*)calloc(1, size);
	instance->entID = entId;
	instance->DBID = dbId;
	iref->maddr = instance;
	return iref;
}


eInstHdr* E_CREATE_F(int dbId, int entId, int size) {
	eInstHdr* instance;

	instance = (eInstHdr*)calloc(1, size);
	instance->entID = entId;
	instance->DBID = dbId;

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

//void E_FFIRST_R(void* SET, void* ENT) {
//	membership* aCard = NULL;
//	membership* lCard = NULL;
//	eInstHdr* aEnt;
//	LIFO_SET* set;
//
//	set = (LIFO_SET*)SET;
//
//	aCard = (membership*)calloc(1, sizeof(membership));
//	aCard->owningSet = set;
//	//aCard->ownerSetName = set->setName;
//	if (set->f_members == NULL)
//		set->l_members = aCard;
//	else {
//		set->f_members->p_members = aCard;
//		aCard->s_members = set->f_members;
//	}
//	set->f_members = aCard;
//	set->membercount++;
//
//	aEnt = (eInstHdr*)ENT;
//	aCard->member = aEnt;
//	if (aEnt->f_memberships == NULL)
//		aEnt->l_memberships = aCard;
//	else
//		aEnt->f_memberships->p_memberships = aCard;
//	aCard->s_memberships = aEnt->f_memberships;
//	aEnt->f_memberships = aCard;
//}


//void E_FLAST_R(void* SET, void* ENT) {
//	membership* aCard = NULL;
//	eInstHdr* aEnt;
//	E_SETHDR* set;
//
//	set = (E_SETHDR*)SET;
//
//	aCard = (membership*)calloc(1, sizeof(membership));
//
//	aCard->owningSet = set;
//	//aCard->ownerSetName = set->name;
//	if (set->l_members != NULL) {
//		set->l_members->s_members = aCard;
//		aCard->p_members = set->l_members;
//	}
//	else
//		set->f_members = aCard;
//	set->l_members = aCard;
//	set->membercount++;
//
//	aEnt = (eInstHdr*)ENT;
//	aCard->member = aEnt;
//	if (aEnt->f_memberships != NULL)
//		aEnt->f_memberships->p_memberships = aCard;
//	aCard->s_memberships = aEnt->f_memberships;
//	aEnt->f_memberships = aCard;
//}

//void E_FBEFOR_R(void* SET, void* ENT, void* TGT) {
//	membership* aCard = NULL;
//	membership* tCard = NULL;
//	eInstHdr* aEnt;
//	LIFO_SET* set;
//
//	set = (LIFO_SET*)SET;
//
//	aEnt = (eInstHdr*)TGT;
//	tCard = aEnt->f_memberships;
//	while (tCard != NULL) {
//		if (_tcscmp(tCard->owningSet->setName->tValue, set->setName->tValue) == 0)
//			break;
//	}
//	aCard = (membership*)calloc(1, sizeof(membership));
//	aCard->owningSet = set;
//	aCard->s_members = tCard;
//	if (tCard->p_members != NULL) {
//		aCard->p_members = tCard->p_members;
//		aCard->p_members->s_members = aCard;
//	}
//	else
//		set->f_members = aCard;
//	tCard->p_members = aCard;
//
//	aEnt = (eInstHdr*)ENT;
//	aCard->member = aEnt;
//	if (aEnt->f_memberships != NULL)
//		aEnt->f_memberships->p_memberships = aCard;
//	aCard->s_memberships = aEnt->f_memberships;
//	aEnt->f_memberships = aCard;
//}

void E_FRANK_R(void* SET, void* ENT, int(fn)(void*, void*)) {
	void* X;
	E_SETHDR* set;
	set = (E_SETHDR*)SET;
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
	E_PSETHDR* set = 0;
	E_PINSTH* X = 0;
	easg((char*)&set, (iRef*)SET);
	easg((char*)&ent, (iRef*)ENT);
	X = F_PEASSET_F(SET);
	if (X == NULL) {
		E_PFFIRST_R(set, ent);
		return;
	}
	while (fn(ENT, X) < 0) {
		X = S_PEASSET_F(X, ((struct E_PSETHDR*)fetch((iRef*)set))->PSETNAME);
		if (X == NULL)
			break;
	}
	if (X == NULL) {
		E_PFLAST_R(set, ent);
		return;
	}
	E_PFBEFOR_R(set, ent, X);
}


//eInstHdr* E_RMVFRST_F(void* SET) {
//	E_CARD* aCard = NULL;
//	E_CARD* lCard = NULL;
//	E_INSTH* aEnt;
//	E_SETHDR* set;
//
//	set = (E_SETHDR*)SET;
//
//	aCard = set->F_MEMBERS;
//	if (aCard == NULL)
//		return 0;
//	set->MCOUNT--;
//	set->F_MEMBERS = aCard->S_MEMBERS;
//
//	aEnt = (E_INSTH*)aCard->MEMBER;
//	lCard = aEnt->F_MSHIPS;
//	if (lCard == aCard)
//		aEnt->F_MSHIPS = lCard->S_MSHIPS;
//	else {
//		while (lCard != NULL) {
//			if (lCard->S_MSHIPS == aCard) {
//				lCard->S_MSHIPS = aCard->S_MSHIPS;
//				break;
//			}
//			lCard = lCard->S_MSHIPS;
//		}
//	}
//	if (lCard) {
//		free(lCard);
//		return (eInstHdr*)aEnt;
//	}
//	return NULL;
//}


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


void OPENO_R(int unit, Etxt* filename) {

	int i;

	if (filename != NULL & unit != 0) {
		filename->refCount++;
		uib_w = (uib*)calloc(1, sizeof(uib));
		uib_w->unit = unit;
		uib_w->file = _wfopen(filename->tValue, _T("w"));
		for (i = 0; i < 255; i++)
			uib_w->buffer[i] = *(_T(" "));
	}
	E_TXTDEL_R(filename);
}

void OPENI_R(int unit, Etxt* filename) {

	if (filename != NULL & unit != 0) {
		filename->refCount++;
		uib_r = (uib*)calloc(1, sizeof(uib));
		uib_r->unit = unit;
		uib_r->file = _wfopen(filename->tValue, _T("r"));
		easlib->UIB_R = (UIB*)uib_r;
		easlib->UIB_R->EOF_V = 0;
	}
	RDL_R();
	E_TXTDEL_R(filename);
}

void CLOSE_R(int unit) {
	if (uib_w) {
		if (uib_w->unit == unit)
			fclose(uib_w->file);
	}
	if (uib_r) {
		if (uib_r->unit == unit)
			fclose(uib_r->file);
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
	int rem;
	int zero = 48;			// ascii "0"
	int i = 1;

	if (width <= 0)
		return;
	
	uib_w->col = uib_w->col + width;
	while (value > 0) {
		rem = value / 10;
		digit = value - rem *(int)10;
		uib_w->buffer[uib_w->col - i] = zero + digit;
		i++;
		value = rem;
	}
}

int RDI_F(int width) {	// write as I n

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
	uib_w->buffer[uib_w->col] = *(_T("\n"));
	for (i = 0; i < uib_w->col+1; i++) {
		_fputtc(uib_w->buffer[i], uib_w->file);
		uib_w->buffer[i] = *(_T(" "));
	}
	fflush(uib_w->file);
	uib_w->col = 0;
}

void RDB_R(int col) {

}
void RDL_R() {

	int i;
	TCHAR ch;

	uib_r->buffer[0] = 32;		// free-format read needs this
	for (i = 0; i < 256; i++) {
		ch = _fgettc(uib_r->file);
		if (ch == EOF | ch == WEOF) {
			easlib->UIB_R->EOF_V = 2;
			return;
		}

		if (ch != (int)10)
			uib_r->buffer[i] = ch;
		else
			break;
	}
	uib_r->rlen = i;
	uib_r->col = 1;
	easlib->UIB_R->RRECLEN_V = i;
}

Etxt* RDX_F() {

	Etxt* str;
	int i;

	str = (Etxt*)calloc(1, sizeof(Etxt));
	str->tLength = uib_r->rlen;
	str->tValue = (TCHAR*)calloc(str->tLength + 1, sizeof(TCHAR));
	for (i = 0; i < str->tLength; i++)
		str->tValue[i] = uib_r->buffer[i];
	return str;
}

Etxt* RDT_F(int width) {

	Etxt* str = NULL;
	int i;

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


Etxt* RDS_F() {

	Etxt* str = NULL;
	int i;
	int delim;
	int len;

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

int RDN_F() {				// read an int

	int value = 0;
	int digit;
	int sign = 0;
	int zero = 48;			// ascii "0"
	int i;
	int width;

	if (uib_r->col > uib_r->rlen)
		RDL_R();

	while (uib_r->col - 1 < uib_r->rlen) {
		if (uib_r->buffer[uib_r->col - 1] != 32)		// eat spaces
			break;
		uib_r->col++;
		if (uib_r->col >= uib_r->rlen)
			RDL_R();
	}

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
		if (uib_r->col > uib_r->rlen)
			break;
	}
	if (sign != 0)
		value = -value;
	return value;
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

void txtasg(char* to, char* from) {
	Etxt** dest;
	Etxt* src;

	dest = (Etxt**)to;
	src = (Etxt*)from;
	E_TXTASG_R(dest, src);
}

char* dref(char* eptr, int offset) {
	int* v;
	//	void* x;
	v = (int*)(char*)(fetch((iRef*)eptr) + (int)offset);
	//	x = (void*)(*v);
	return (char*)(*(int*)(char*)(fetch((iRef*)eptr) + (int)offset));
}

void* aref(char* eptr, int offset) {
	int* v;
	v = (int*)(char*)(fetch((iRef*)eptr) + (int)offset);
	return (void*)(v);
}

void* apref(char* eptr, int offset) {
	int* v;
	v = (int*)(char*)(fetch((iRef*)eptr) + (int)offset);
	if (*v)
		(*v) = 0;
	return (void*)(v);
}

void* lasg(char* eptr) {
	if (*eptr)
		(*eptr) = 0;
	return (void*)eptr;
}


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

//void createset(Etxt* name, char* setp) {
//	LIFO_SET** sp;
//	LIFO_SET* set;
//	sp = (LIFO_SET**)setp;
//	set = (LIFO_SET*)(*sp);
//	(*sp) = (LIFO_SET*)E_INITSET_F(name);
//}

void filefirst(char* setp, char* ent) {
	eInstHdr* aEnt;
	membership* aCard;
	LIFO_SET* set;

	set = (LIFO_SET*)setp;
	aEnt = (eInstHdr*)ent;

	E_FFIRST_R(&set, aEnt);

}

char* removefirst(char* setp) {
	return NULL;
}

void E_RECORD_R() {
	iRef* iref;
	int* mapptr;
	int* eptr;
	int i;
	int j;
	int offset;
	typeInfo* info;

	WTX_R(E_TXTLIT_F(_T("Now recording persistent entity instances:")));
	WTL_R();

	info = f_typeInfos;
	while (info) {

		iref = info->f_irefs;
		while (iref) {
			WTX_R(E_TXTLIT_F(_T("iRef: ")));
			WTI_R(iref->dbId, 4);

			mapptr = (int*)info->emap;
			offset = *mapptr;
			mapptr++;
			eptr = (int*)iref->maddr;
			WTX_R(E_TXTLIT_F(_T("  Schema ID: ")));
			WTI_R(*eptr, 4);
			eptr++;
			WTX_R(E_TXTLIT_F(_T("  Entity ID: ")));
			WTI_R(*eptr, 4);
			eptr++;
			eptr++;
			eptr++;

			i = (*mapptr);	// count
			mapptr++;
			while (i) {
				j = (*mapptr); // map value
				if (j == 3) {
					WTS_R(2);
					WTX_R((Etxt*)*eptr);
				}
				mapptr++;
				eptr++;
				i--;
			}
			iref = iref->s_irefs;
			WTL_R();
		}
		info = info->s_typeInfo;
	}
	WTX_R(E_TXTLIT_F(_T("End of recording")));
	WTL_R();
}

//iRef* F_PEASSET_F(void* set) {
//	E_PSETHDR* setent;
//
//	setent = (E_PSETHDR*)set;
//	if (setent->F_PMEMBERS)
//		return (iRef*)setent->F_PMEMBERS->PMEMBER;
//	return NULL;
//}

void addPtype(int ssid, int entid, const int* map) {

	typeInfo* info;

	info = (typeInfo*)calloc(1, sizeof(typeInfo));
	info->ssId = ssid;
	info->entId = entid;
	info->emap = map;
	info->s_typeInfo = f_typeInfos;
	f_typeInfos = info;
}