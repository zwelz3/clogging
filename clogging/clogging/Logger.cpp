#include "stdafx.h"
#include "Logger.h"
#pragma warning(disable : 4996)

using json = nlohmann::json;

namespace clogging {

	Logger::Logger() {		
		
	}	
	
	void Logger::AddFile(string file_name) {

		global_file_name_ = file_name;

		ifstream log_file(file_name);

		if (!log_file) {			
			ofstream log_file_create;
			log_file_create.open(file_name);
			log_file_create.close();			
		}
		log_file.close();		
	}

	/*void Logger::AddFile(string file_name, string path) {

		global_file_name_ = file_name;

		ifstream log_file(file_name);

		if (!log_file) {
			ofstream log_file_create(path);
			log_file_create.open(file_name);
			log_file_create.close();
		}
		log_file.close();
	}*/
	
	void Logger::Clog(string output_msg, Verbosity level, int specify_type) {
		
		switch (specify_type) {
			case 1:
				TXTSyntax(level, output_msg);
				break;
			case 2:
				JSONSyntax(level, output_msg);
				break;			
			default:
				TXTSyntax(level, output_msg);
				break;
		}
	}

	void Logger::Clog(string output_msg, Verbosity level) {
		
		TXTSyntax(level, output_msg);
	}

	void Logger::Clog(string output_msg) {		

		TXTSyntax(Verbosity::DEBUG, output_msg);
	}

	void Logger::Clog() {
		
		string output_msg = "Default placeholder message.";

		TXTSyntax(Verbosity::INFO, output_msg);
	}
	
	void Logger::TXTSyntax(Verbosity level, string output_msg) {

		string level_value = EnumStringValue(level);

		char *current_time = CurrentTimeStamp();		

		ifstream log_file(global_file_name_);
		log_file.close();

		ofstream log_file_out(global_file_name_, ofstream::app);

		if (log_file_out.is_open()) {							
			
			log_file_out << "[" << current_time << "] [" << level_value << "] " << output_msg << "\n";
			log_file_out.close();			
		}
	}

	void Logger::JSONSyntax(Verbosity level, string output_msg) {

		string level_value = EnumStringValue(level);

		char *current_time = CurrentTimeStamp();

		json output_json = {
			{"timestamp", current_time},
			{"verbosity", level_value},
			{"output_message", output_msg}
		};

		string json_dump = output_json.dump();

		ifstream log_file(global_file_name_);
		log_file.close();

		ofstream log_file_out(global_file_name_, ofstream::app);

		if (log_file_out.is_open()) {

			log_file_out << json_dump << "\n";
			log_file_out.close();			
		}
	}

	string Logger::EnumStringValue(Verbosity level) {

		switch (level) {
		case DEBUG:
			return "DEBUG";
			break;
		case INFO:
			return "INFO";
			break;
		case NOTICE:
			return "NOTICE";
			break;
		case WARNING:
			return "WARNING";
			break;
		case ERROR:
			return "ERROR";
			break;
		case CRIT:
			return "CRIT";
			break;
		case ALERT:
			return "ALERT";
			break;
		case EMERGENCY:
			return "EMERGENCY";
			break;
		default:
			break;
		}
		return string();
	}
	
	char *Logger::CurrentTimeStamp() {

		time_t rawtime;
		struct tm * timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		char *current = asctime(timeinfo);
		current[strlen(current) - 1] = '\0';

		return current;
	}	
	Logger::~Logger() {
	}
}
