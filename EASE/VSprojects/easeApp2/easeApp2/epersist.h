#pragma once
#include "easlib.h"

void E_PCONNECT_R(Etxt* server);
void E_PDISCONNECT_R(Etxt* server);

int registerType(int ssId, int etypeId);
int newInstance(iRef* iref);
int recordInstance(iRef* iref, int len);
int retrieveInstance(iRef* iref);
int deleteInstance(iRef* iref);
int commitChanges();

int ebuffpack(int* eptr, const int* mapptr);
int* ebuffunpack(const int* mapptr);

void E_RECORD_R();
void persistFetch(iRef* iref);
iRef* iRefMatch(iRef* iref);


