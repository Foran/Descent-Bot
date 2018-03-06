/****************************************************
 * Copyright 2018 Ben M. Ward
 *
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#include "src/lib/config/xml.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {

using ::std::string;
using ::std::vector;
using ::std::map;

bool CXML::mFirstUse = true;

/**
 * @see CXML(const string &filename) Simple direct file constructor
 * @see CXML(const CXML &source) Default copy constructor
 **************************************************/
CXML::CXML() {
  Initialize();
}


/**
 * Load the specified xml on construction of the object
 * @filename Filename of the xml you wish to load
 * @see CXML() Default constructor
 * @see CXML(const CXML &source) Default copy constructor
 **************************************************/
CXML::CXML(const string &filename) {
  Initialize();
}

CXML::CXML(const CXML &source) {
  Initialize();
  *this = source;
}

CXML::~CXML() {
}

CXML &CXML::operator=(const CXML &source) {
  return *this;
}

void CXML::Initialize() {
  if (mFirstUse) {
    mFirstUse = false;
    LIBXML_TEST_VERSION
  }
}

bool CXML::Load(const string &filename) {
  bool retval = false;

  xmlDocPtr document = xmlReadFile(filename.c_str(), nullptr, 0);
  if (nullptr != document) {
    xmlNodePtr root = xmlDocGetRootElement(document);
    retval = LoadNode(root, &mRoot);
    xmlFreeDoc(document);
  }

  return retval;
}

bool CXML::LoadNode(xmlNodePtr source, CXMLNode *destination) {
  bool retval = false;

  if (source != nullptr) {
    retval = true;
    destination->mName = xmlChar2string(source->name);

    for (xmlAttr *attribute = source->properties;
         nullptr != attribute; attribute = attribute->next) {
      xmlChar *value = xmlGetProp(source, attribute->name);
      if (value != nullptr) {
        destination->mAttributes[xmlChar2string(attribute->name)] =
          xmlChar2string(value);
        xmlFree(value);
      }
    }

    for (xmlNodePtr node = source->children;
         nullptr != node; node = node->next) {
      if (XML_ELEMENT_NODE == node->type) {
        CXMLNode child;
        retval &= LoadNode(node, child);
        if (retval) {
          destination->mChildren.push_back(child);
        }
      }
    }
  }

  return retval;
}

string CXML::xmlChar2string(const xmlChar *value) {
  return static_cast<string>((const char *)value);
}

CXMLNode &CXML::get_Root() {
  return mRoot;
}

CXMLNode::CXMLNode() {
}

CXMLNode::CXMLNode(const CXMLNode &source) {
  *this = source;
}

CXMLNode::~CXMLNode() {
}

CXMLNode &CXMLNode::operator=(const CXMLNode &source) {
  mAttributes = source.mAttributes;
  mChildren = source.mChildren;
  mInnerText = source.mInnerText;
  mName = source.mName;

  return *this;
}

/**
 * Allows the use of array indexing to
 * lookup attributes.
 * @param name The name of the attribute to extract.
 * @return The value of the specified attribute.
 * @see get_Attributes()
 ************************************/
string CXMLNode::operator[](string name) {
  return mAttributes[name];
}

/**
 * Get property for the attributes list.
 * Primarly used for enumerating through
 * all attributes.
 * @return A reference to the internal attribute map
 * @see operator[](string name)
 ************************************/
map<string, string> &CXMLNode::get_Attributes() {
  return mAttributes;
}

vector<CXMLNode> &CXMLNode::get_Children() {
  return mChildren;
}

string CXMLNode::get_InnerText() {
  return mInnerText;
}

string CXMLNode::get_Name() {
  return mName;
}

int CXMLNode::StringToInt(const string &value) {
  return atoi(value.c_str());
}

}  // namespace CONFIG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
