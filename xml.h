#ifndef __XML_H__
#define __XML_H__

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <map>
#include <vector>

using namespace std;

class CXMLNode {
	public:
		CXMLNode(const CXMLNode &source);
		~CXMLNode();

		CXMLNode &operator=(const CXMLNode &source);

		string operator[](string name);
		map<string, string> &get_Attributes();
		vector<CXMLNode> &get_Children();
		string get_InnerText();
		string get_Name();
	protected:
	private:
		map<string, string> mAttributes;
		vector<CXMLNode> mChildren;
		string mInnerText;
		string mName;

		CXMLNode();

		friend class CXML;
};

class CXML {
	public:
		CXML();
		CXML(const string &filename);
		CXML(const CXML &source);
		~CXML();

		CXML &operator=(const CXML &source);

		void Initialize();
		bool Load(const string &filename);
		CXMLNode &get_Root();
	protected:
	private:
		CXMLNode mRoot;
		static bool mFirstUse;

		bool LoadNode(xmlNodePtr source, CXMLNode &destination);
		string xmlChar2string(const xmlChar *value);
};

#endif
