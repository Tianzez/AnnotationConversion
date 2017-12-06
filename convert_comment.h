#ifndef __CONVERT_COMMENT_H__
#define __CONVERT_COMMENT_H__

#include <stdio.h>
#include <windows.h>

#define INPUTFILE "input.c"
#define OUTPUTFILE "output.c"

enum 
{
	CSTATUS, //C×¢ÊÍ
	CPPSTATUS, //C++×¢ÊÍ
	NULLSTATUS, //ÆÕÍ¨×´Ì¬
	EOFSTATUS  //½áÊø×´Ì¬
};

void convert_comment();
void convert_work(FILE *ifp, FILE *ofp); 

#endif