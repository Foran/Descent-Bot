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

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {

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
		::std::string operator[](::std::string name);
		/// Retrieves a dictionary of all attributes
		::std::map<::std::string, ::std::string> &get_Attributes();
		/// Retrieves the list of child nodes
		::std::vector<CXMLNode> &get_Children();
		/// Retrieves the node's inner text
		::std::string get_InnerText();
		/// Retrieves the tag's name
		::std::string get_Name();
		/// Converts a string into an integer
		int StringToInt(const ::std::string &value);
	protected:
	private:
		::std::map<::std::string, ::std::string> mAttributes; ///< Internal dictionary of Attributes
		::std::vector<CXMLNode> mChildren; ///< Internal list of child node
		::std::string mInnerText; ///< Internal container for inner text
		::std::string mName; ///< Internal container for tag name

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
		CXML(const ::std::string &filename);
		/// Default copy constructor
		CXML(const CXML &source);
		/// Destructor
		~CXML();

		/// Default assignment operator
		CXML &operator=(const CXML &source);

		/// Load an xml from a file
		bool Load(const ::std::string &filename);
		/// Get the root XML Node as a CXMLNode object
		CXMLNode &get_Root();
	protected:
	private:
		CXMLNode mRoot; /// The root node
		static bool mFirstUse; /// Tracks first use to initialize LibXML2

		/// Common class initialization
		void Initialize();
		/// Load a CXMLNode from xmlNodePtr
		bool LoadNode(::xmlNodePtr source, CXMLNode &destination);
		/// Converts a xmlChar to a C++ string
		::std::string xmlChar2string(const ::xmlChar *value);
};

}  // namespace CONFIG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif
