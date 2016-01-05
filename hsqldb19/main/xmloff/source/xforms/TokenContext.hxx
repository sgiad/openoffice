/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _XMLOFF_TOKENCONTEXT_HXX
#define _XMLOFF_TOKENCONTEXT_HXX


//
// include for parent class and members
//

#include <xmloff/xmlictxt.hxx>


//
// forward declarations
//

namespace com { namespace sun { namespace star {
    namespace xml { namespace sax { class XAttributeList; } }
    namespace uno { template<typename T> class Reference; }
} } }
namespace rtl { class OUString; }
class SvXMLImport;

#define TOKEN_MAP_ENTRY(NAMESPACE,TOKEN) { XML_NAMESPACE_##NAMESPACE, xmloff::token::XML_##TOKEN, xmloff::token::XML_##TOKEN }

extern struct SvXMLTokenMapEntry aEmptyMap[1];

/** handle attributes through an SvXMLTokenMap */
class TokenContext : public SvXMLImportContext
{
protected:
    const SvXMLTokenMapEntry* mpAttributes;    /// static token map
    const SvXMLTokenMapEntry* mpChildren;      /// static token map

public:

    TokenContext( SvXMLImport& rImport, 
                  sal_uInt16 nPrefix,
                  const ::rtl::OUString& rLocalName,
                  const SvXMLTokenMapEntry* pAttributes = NULL,
                  const SvXMLTokenMapEntry* pChildren = NULL );

    virtual ~TokenContext();


    //
    // implement SvXMLImportContext methods:
    //

    /** call HandleAttribute for each attribute in the token map;
     * create a warning for all others. Classes that wish to override
     * StartElement need to call the parent method. */
	virtual void StartElement( 
        const com::sun::star::uno::Reference<com::sun::star::xml::sax::XAttributeList>& xAttrList );

    /** call HandleChild for each child element in the token map;
     * create a warning for all others. Classes that wish to override
     * CreateChildCotnenxt may want to call the parent method for
     * handling of defaults. */
	virtual SvXMLImportContext* CreateChildContext( 
        sal_uInt16 nPrefix,
        const rtl::OUString& rLocalName,
        const com::sun::star::uno::Reference<com::sun::star::xml::sax::XAttributeList>& xAttrList );

    /** Create a warning for all non-namespace character
     * content. Classes that wish to deal with character content have
     * to overload this method anyway, and will thus get rid of the
     * warnings. */
	virtual void Characters( const ::rtl::OUString& rChars );

protected:
    /** will be called for each attribute */
    virtual void HandleAttribute( 
        sal_uInt16 nToken, 
        const rtl::OUString& rValue ) = 0;

    /** will be called for each child element */
    virtual SvXMLImportContext* HandleChild( 
        sal_uInt16 nToken,

        // the following attributes are mainly to be used for child
        // context creation
        sal_uInt16 nPrefix,
        const rtl::OUString& rLocalName,
        const com::sun::star::uno::Reference<com::sun::star::xml::sax::XAttributeList>& xAttrList ) = 0;
};

#endif
