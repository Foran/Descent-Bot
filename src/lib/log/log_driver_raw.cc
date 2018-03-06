/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#include "log_driver_raw.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LOG {

CLogDriverRaw::CLogDriverRaw() 
{
	mLevel = 100;
	mType = LogType_Debug;
	mName = "Default Raw";
}

void CLogDriverRaw::set_Name(const string &name)
{
	mName = name;
}

string CLogDriverRaw::get_Name() const
{
   return mName;
}

string CLogDriverRaw::get_Driver() const
{
   return "Raw";
}

void CLogDriverRaw::set_Type(const string &type)
{
	mType = GetLogType(type);
}

void CLogDriverRaw::set_Type(const LogType &type)
{
	mType = type;
}

LogType CLogDriverRaw::get_Type() const
{
   return mType;
}

void CLogDriverRaw::set_Level(const string &level)
{
	mLevel = atoi(level.c_str());
}

void CLogDriverRaw::set_Level(const int &level)
{
	mLevel = level;
}

int CLogDriverRaw::get_Level() const
{
   return mLevel;
}

void CLogDriverRaw::set_Option(const string &name, const string &value)
{
}

string CLogDriverRaw::get_Option(const string &name)
{
   return "";
}

bool CLogDriverRaw::Write(int level, const string &message)
{
   bool retval = true;
   
   if(level <= mLevel) cout << "[" << mName << ": " << mType << "(" << level << ")]: " <<  message << endl;
   
   return retval;
}

}  // namespace LOG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
