#include "config.h"

/***************************************
* Global instance of the CConfig class
**************************************/
CConfig global_Config;

unsigned int CConfig::mReferences = 0;

/*******************************************
* Default constructor of the CConfig class
******************************************/
CConfig::CConfig()
{
	Init();
	Reset();
}

/********************************************
* Constructor to load the config from a file
********************************************/
CConfig::CConfig(const string filename)
{
	Init();
	Load(filename);
}

/***************************************
* Copy Constructor
**************************************/
CConfig::CConfig(const CConfig &source)
{
	Init();
	*this = source;
}

CConfig::~CConfig()
{
	if(0 == --mReferences) {
		xmlCleanupParser();
	}
}

CConfig &CConfig::operator=(const CConfig &source)
{
	Reset();

	return *this;
}

void CConfig::Init() 
{
	if(0 == mReferences++) {
		LIBXML_TEST_VERSION
	}
}

bool CConfig::Load(const string filename)
{
	bool retval = false;
	CXML document;

	Reset();
	if(document.Load(filename)) {
		retval = true;
		if(static_cast<string>("Configuration") == document.get_Root().get_Name()) {
			cout << "Found root config node (" << document.get_Root().get_Name() << ")" << endl;
			for(vector<CXMLNode>::iterator child = document.get_Root().get_Children().begin(); child != document.get_Root().get_Children().end(); child++) {
				cout << "Found child node (" << child->get_Name() << ")" << endl;
				if(static_cast<string>("Logging") == child->get_Name()) retval &= Logging.Load_Logging(*child);
			}
		}
	}

	return retval;
}

LogType CConfig_Logging::get_LogType(CXMLNode &node)
{
	LogType retval = LogType_Fatal;
	if(static_cast<string>("Logger") == node.get_Name()) {
		if(node["Type"] == "Fatal") retval = LogType_Fatal;
		else if(node["Type"] == "Error") retval = LogType_Error;
		else if(node["Type"] == "Warning") retval = LogType_Warning;
		else if(node["Type"] == "Debug") retval = LogType_Debug;
		else if(node["Type"] == "Info") retval = LogType_Info;
	}

	return retval;
}

bool CConfig_Logging::Load_Logging(CXMLNode &node)
{
	bool retval = false;

	if(static_cast<string>("Logging") == node.get_Name()) {
		retval = true;
		for(vector<CXMLNode>::iterator child = node.get_Children().begin(); child != node.get_Children().end(); child++) {
			if(static_cast<string>("Logger") == child->get_Name()) {
				CConfig_Logging_Logger logger(*child);
				if(logger.is_Valid()) {
					retval &= true;
				}
				else {
					retval &= false;
				}
			}
		}
	}
	global_Log.add_Logger(LogType_Debug, new CLogDriverRaw());

	return retval;
}

void CConfig::Reset()
{
}

CConfig_Logging::CConfig_Logging()
{
}

CConfig_Logging::CConfig_Logging(const CConfig_Logging &source)
{
	*this = source;
}

CConfig_Logging::~CConfig_Logging()
{
	for(map<string, CConfig_Logging_Logger *>::iterator i = mLoggers.begin(); i != mLoggers.end(); i++) {
		delete (*i).second;
	}
}

CConfig_Logging &CConfig_Logging::operator=(const CConfig_Logging &source)
{
	return *this;
}

CConfig_Logging_Logger::CConfig_Logging_Logger()
{
	mLevel = 0;
}

CConfig_Logging_Logger::CConfig_Logging_Logger(CXMLNode &node)
{
	if(static_cast<string>("Logger") == node.get_Name()) {
		cout << "Scanning Configuration->Logging->" << node.get_Name() << " for attributes" << endl;
		for(map<string, string>::iterator i = node.get_Attributes().begin(); i != node.get_Attributes().end(); i++) {
			cout << "Configuration->Logging->" << node.get_Name() << "[" << i->first << "]=" << i->second << endl;
		}
		for(vector<CXMLNode>::iterator child = node.get_Children().begin(); child != node.get_Children().end(); child++) {
			if(static_cast<string>("Option") == child->get_Name()) {
				cout << "Option " << (*child)["Name"] << " = " << (*child)["Value"] << endl;
			}
		}
	}
	else {
		cout << "Was passed a node not of type Logger but of type " << node.get_Name() << endl;
	}
}

string CConfig_Logging_Logger::get_Name() const
{
	return mName;
}

LogType CConfig_Logging_Logger::get_Type() const
{
	return mType;
}

int CConfig_Logging_Logger::get_Level() const
{
	return mLevel;
}

string CConfig_Logging_Logger::get_Driver() const
{
	return mDriver;
}

string CConfig_Logging_Logger::operator[](const string &key)
{
	return mOptions[key];
}

vector<string> CConfig_Logging_Logger::get_Option_Names()
{
	vector<string> retval;

	for(map<string, string>::iterator i = mOptions.begin(); i != mOptions.end(); i++) {
		retval.push_back((*i).first);
	}   

	return retval;
}

CConfig_Logging_Logger::~CConfig_Logging_Logger() 
{
}

bool CConfig_Logging_Logger::is_Valid() const
{
	bool retval = false;

	return retval;
}
