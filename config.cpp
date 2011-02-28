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
	       if(static_cast<string>("Logging") == xmlChar2string(cur_node->name)) retval &= Load_Logging(cur_node);
	    }
	 }
      }
      xmlFreeDoc(document);
   }
      
   return retval;
}

bool CConfig::Load_Logging(const xmlNodePtr node)
{
   bool retval = false;
   
   if(NULL != node && static_cast<string>("Logging") == xmlChar2string(node->name)) {
      retval = true;
      for(xmlNode *cur_node = node->children; NULL != cur_node; cur_node = cur_node->next) {
	 if(XML_ELEMENT_NODE == cur_node->type) {
	    cout << "Scanning Configuration->Logging->" << cur_node->name << " for attributes" << endl;
	    for(xmlAttr *attr = cur_node->properties; NULL != attr; attr = attr->next) {
	       cout << "Configuration->Logging->" << cur_node->name << "[" << attr->name << "]=" << xmlGetProp(cur_node, attr->name) << endl;
	    }
	 }
      }
   }
      
   return retval;
}

void CConfig::Reset()
{
//   global_Log.add_Logger(LogType_Debug, new CLogDriverRaw());
}

string CConfig::xmlChar2string(const xmlChar *value)
{
   return static_cast<string>((const char *)value);
}

CConfig_Logging_Logger::CConfig_Logging_Logger()
{
   mLevel = 0;
}

string CConfig_Logging_Logger::get_Name() const
{
   return mName;
}

string CConfig_Logging_Logger::get_Type() const
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
