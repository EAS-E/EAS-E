#pragma once

#include "easlib.h"

int XMLOPEN_F(Etxt* schema);
int XMLFINDELEM_F(Etxt* elem);
int XMLFINDCHILD_F(Etxt* elem);
void XMLINTO();
void XMLOUTOF();
int XMLLATTR_F(Etxt* attrname);	// return Logical (bool?) attribute value
int XMLIATTR_F(Etxt* attrname);	// return Integer attribute value
Etxt* XMLTATTR_F(Etxt* attrname);	// return Text attribute value
Etxt* XMLGETDATA_F();				// return Text value
Etxt* XMLGETCHILDDATA_F();		// return Text value
