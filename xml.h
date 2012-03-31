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

#ifdef _WIN32
#define LIBXML_STATIC
#endif

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <map>
#include <vector>

using namespace std;

/// This class represents a node tree in a xml document
/**************************************//**
 * This class can only be instantiated by CXML
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
/**************************************//**
 * The class provides simple access to an
 * XML document
 *****************************************/
class CXML {
	public:
		/// Default constructor
		CXML();
		/// Simple direct file constructor
		CXML(const string &filename);
		/// Default copy constructor
		CXML(const CXML &source);
		/// Destructor
		~CXML();

		/// Default assignment operator
		CXML &operator=(const CXML &source);

		/// Load an xml from a file
		bool Load(const string &filename);
		/// Get the root XML Node as a CXMLNode object
		CXMLNode &get_Root();
	protected:
	private:
		CXMLNode mRoot; /// The root node
		static bool mFirstUse; /// Tracks first use to initialize LibXML2

		/// Common class initialization
		void Initialize();
		/// Load a CXMLNode from xmlNodePtr
		bool LoadNode(xmlNodePtr source, CXMLNode &destination);
		/// Converts a xmlChar to a C++ string
		string xmlChar2string(const xmlChar *value);
};

#endif
