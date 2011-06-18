#include "xml.h"

bool CXML::mFirstUse = true;

CXML::CXML() {
	Initialize();
}

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
	if(mFirstUse) {
		mFirstUse = false;
		LIBXML_TEST_VERSION
	}
}

bool CXML::Load(const string &filename) {
	bool retval = false;

	xmlDocPtr document = xmlReadFile(filename.c_str(), NULL, 0);
	if(NULL != document) {
		xmlNodePtr root = xmlDocGetRootElement(document);
		retval = LoadNode(root, mRoot);
		xmlFreeDoc(document);
	}

	return retval;
}

bool CXML::LoadNode(xmlNodePtr source, CXMLNode &destination) {
	bool retval = false;

	if(source != NULL) {
		retval = true;
		destination.mName = xmlChar2string(source->name);

		for(xmlAttr *attribute = source->properties; NULL != attribute; attribute = attribute->next) {
			xmlChar *value = xmlGetProp(source, attribute->name);
			if(value != NULL) {
				destination.mAttributes[xmlChar2string(attribute->name)] = xmlChar2string(value);
				xmlFree(value);
			}
		}

		for(xmlNodePtr node = source->children; NULL != node; node = node->next) {
			if(XML_ELEMENT_NODE == node->type) {
				CXMLNode child;
				retval &= LoadNode(node, child);
				if(retval) {
					destination.mChildren.push_back(child);
				}
			}
		}
	}

	return retval;
}

string CXML::xmlChar2string(const xmlChar *value)
{
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

string CXMLNode::operator[](string name) {
	return mAttributes[name];
}

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
