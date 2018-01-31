#pragma once

#include <time.h>
#include <string>
#include <string.h>
#include <ctime>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Macros.h"

using namespace std;

namespace clogging {	
	
	class Logger {
	private:
		char *CurrentTimeStamp();
		const char *global_file_name_;

	public:		
		bool CreateLogFile();								

		template <typename T>
		void Clog(T output_msg, string level, int specify_type);

		/*template <typename T>
		void Clog(T output_msg, string level);

		template <typename T>
		void Clog(T output_msg);*/
		
		bool TXTSyntax(string level, string output_msg);				
		bool JSONSyntax(string level, string output_msg);

		Logger();
		~Logger();
	};
}



