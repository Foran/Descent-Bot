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
#ifndef __XML_H__
#define __XML_H__

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <map>
#include <vector>

using namespace std;

/// This class represents a node tree in a xml document
/**************************************//**
 * This class can only be instanciated by CXML
 *****************************************/
class CXMLNode {
	public:
		/// Copy constructor
		CXMLNode(const CXMLNode &source);
		/// Destructor
		~CXMLNode();

		/// Assignment operator
		CXMLNode &operator=(const CXMLNode &source);

		/// Attribute accessor
		string operator[](string name);
		/// Retrieves a dictionary of all attributes
		map<string, string> &get_Attributes();
		/// Retrieves the list of child nodes
		vector<CXMLNode> &get_Children();
		/// Retrieves the node's inner text
		string get_InnerText();
		/// Retrieves the tag's name
		string get_Name();
		/// Converts a string into an integer
		int StringToInt(const string &value);
	protected:
	private:
		map<string, string> mAttributes; ///< Internal dictionary of Attributes
		vector<CXMLNode> mChildren; ///< Internal list of child node
		string mInnerText; ///< Internal container for inner text
		string mName; ///< Internal container for tag name

		/// Private default constructor to restrict node creation access
		CXMLNode();

		friend class CXML;
};

/// This class represents a xml document
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
