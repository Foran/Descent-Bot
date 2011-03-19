#include "log_driver_file.h"

CLogDriverFile::CLogDriverFile() 
{
}

void CLogDriverFile::set_Name(const string &name)
{
}

string CLogDriverFile::get_Name() const
{
   return "";
}

string CLogDriverFile::get_Driver() const
{
   return "File";
}

void CLogDriverFile::set_Type(const string &type)
{
}

void CLogDriverFile::set_Type(const LogType &type)
{
}

LogType CLogDriverFile::get_Type() const
{
   return LogType_Error;
}

void CLogDriverFile::set_Level(const string &level)
{
}

void CLogDriverFile::set_Level(const int &level)
{
}

int CLogDriverFile::get_Level() const
{
   return 0;
}

void CLogDriverFile::set_Option(const string &name, const string &value)
{
}

string CLogDriverFile::get_Option(const string &name)
{
   return "";
}

bool CLogDriverFile::Write(LogType type, int level, const string &message)
{
   bool retval = true;
   
   cout << type << "(" << level << "): " <<  message << endl;
   
   return retval;
}
