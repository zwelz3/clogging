// clogging.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"

int main()
{	
	INIT_CLOGGING;	
		
	string test_msg = "this is my message";
	ToLog.Clog(test_msg, DEBUG, LOG);
	
    return 0;
}

