#pragma once

void LISTENERINIT_F();
void* ALLOCNEWBLK_F(int size);
void PUTDATA_R(void* data, void* blkaddr, int segcount, int thisseg, int segsize, int datasize);
void GETDATA_R(void* data, void* blkaddr, int segcount, int thisseg, int segsize, int datasize);

void OPENDATA_R(int size);
void* READBLK_F(int offset);
int WRITEBLK_F(void* blkaddr);