#ifndef __LOG_DRIVER_H__
#define __LOG_DRIVER_H__

#include <string>
#include <iostream>

using namespace std;

enum LogType 
{
	LogType_Fatal,
	LogType_Error,
	LogType_Warning,
	LogType_Debug,
	LogType_Info
};

typedef struct iLogDriver
{
	virtual void set_Name(const string &name) = 0;
	virtual string get_Name() const = 0;
	virtual string get_Driver() const = 0;
	virtual void set_Type(const string &type) = 0;
	virtual void set_Type(const LogType &type) = 0;
	virtual LogType get_Type() const = 0;
	virtual void set_Level(const string &level) = 0;
	virtual void set_Level(const int &level) = 0;
	virtual int get_Level() const = 0;
	virtual void set_Option(const string &name, const string &value) = 0;
	virtual string get_Option(const string &name) = 0;
	virtual bool Write(int level, const string &message) = 0;
} iLogDriver;

extern ostream &operator<<(ostream &output, const LogType &type);

extern LogType GetLogType(string type);

#endif
