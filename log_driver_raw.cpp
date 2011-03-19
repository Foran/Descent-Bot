#include "log_driver_raw.h"

CLogDriverRaw::CLogDriverRaw() 
{
}

void CLogDriverRaw::set_Name(const string &name)
{
}

string CLogDriverRaw::get_Name() const
{
   return "";
}

string CLogDriverRaw::get_Driver() const
{
   return "Raw";
}

void CLogDriverRaw::set_Type(const string &type)
{
}

void CLogDriverRaw::set_Type(const LogType &type)
{
}

LogType CLogDriverRaw::get_Type() const
{
   return LogType_Error;
}

void CLogDriverRaw::set_Level(const string &level)
{
}

void CLogDriverRaw::set_Level(const int &level)
{
}

int CLogDriverRaw::get_Level() const
{
   return 0;
}

void CLogDriverRaw::set_Option(const string &name, const string &value)
{
}

string CLogDriverRaw::get_Option(const string &name)
{
   return "";
}

bool CLogDriverRaw::Write(LogType type, int level, const string &message)
{
   bool retval = true;
   
   cout << type << "(" << level << "): " <<  message << endl;
   
   return retval;
}
