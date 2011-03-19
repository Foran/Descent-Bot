#include "config.h"

CConfig global_Config;

unsigned int CConfig::mReferences = 0;

CConfig::CConfig()
{
   Init();
   Reset();
}

CConfig::CConfig(const string filename)
{
   Init();
   Load(filename);
}

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
   xmlDocPtr document = NULL;
   xmlNodePtr node = NULL;
   
   Reset();
   document = xmlReadFile(filename.c_str(), NULL, 0);
   if(NULL != document) {
      retval = true;
      node = xmlDocGetRootElement(document);
      if(NULL != node && static_cast<string>("Configuration") == xmlChar2string(node->name) && NULL == node->next) {
	 for(xmlNodePtr cur_node = node->children; NULL != cur_node; cur_node = cur_node->next) {
	    if(XML_ELEMENT_NODE == cur_node->type) {
	       if(static_cast<string>("Logging") == xmlChar2string(cur_node->name)) retval &= Logging.Load_Logging(cur_node);
	    }
	 }
      }
      xmlFreeDoc(document);
   }
      
   return retval;
}

LogType CConfig_Logging::get_LogType(const xmlNodePtr node)
{
   LogType retval = LogType_Fatal;
   if(XML_ELEMENT_NODE == node->type && static_cast<string>("Logger") == CConfig::xmlChar2string(node->name)) {
      xmlChar *xmlType = const_cast<xmlChar *>(xmlGetProp(node, (const xmlChar *)("Type")));
      string type = CConfig::xmlChar2string(xmlType);

      if(type == "Fatal") retval = LogType_Fatal;
      else if(type == "Error") retval = LogType_Error;
      else if(type == "Warning") retval = LogType_Warning;
      else if(type == "Debug") retval = LogType_Debug;
      else if(type == "Info") retval = LogType_Info;
   }
   
   return retval;
}

bool CConfig_Logging::Load_Logging(const xmlNodePtr node)
{
   bool retval = false;
   
   if(NULL != node && static_cast<string>("Logging") == CConfig::xmlChar2string(node->name)) {
      retval = true;
      for(xmlNode *cur_node = node->children; NULL != cur_node; cur_node = cur_node->next) {
	 if(XML_ELEMENT_NODE == cur_node->type && static_cast<string>("Logger") == CConfig::xmlChar2string(cur_node->name)) {
	    cout << "Scanning Configuration->Logging->" << cur_node->name << " for attributes" << endl;
	    for(xmlAttr *attr = cur_node->properties; NULL != attr; attr = attr->next) {
	       cout << "Configuration->Logging->" << cur_node->name << "[" << attr->name << "]=" << xmlGetProp(cur_node, attr->name) << endl;
	    }
	    for(xmlNode *option_node = cur_node->children; NULL != option_node; option_node = option_node->next) {
	       if(XML_ELEMENT_NODE == option_node->type && static_cast<string>("Option") == CConfig::xmlChar2string(option_node->name)) {
		  cout << "Option " << xmlGetProp(option_node, (xmlChar *)"Name") << " = " << xmlGetProp(option_node, (xmlChar *)"Value") << endl;
	       }
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

string CConfig::xmlChar2string(const xmlChar *value)
{
   return static_cast<string>((const char *)value);
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
