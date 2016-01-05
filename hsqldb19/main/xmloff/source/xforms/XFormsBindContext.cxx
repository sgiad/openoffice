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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_xmloff.hxx"

#include "XFormsBindContext.hxx"

#include "xformsapi.hxx"

#include <xmloff/xmlimp.hxx>
#include "xmloff/xmlerror.hxx"
#include <xmloff/xmltoken.hxx>
#include <xmloff/xmltkmap.hxx>
#include "xmloff/xmlnmspe.hxx"
#include <xmloff/nmspmap.hxx>

#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/xforms/XModel.hpp>

#include <tools/debug.hxx>

using rtl::OUString;
using com::sun::star::beans::XPropertySet;
using com::sun::star::uno::Reference;
using com::sun::star::uno::makeAny;
using com::sun::star::uno::UNO_QUERY;
using com::sun::star::uno::UNO_QUERY_THROW;
using com::sun::star::container::XNameContainer;
using com::sun::star::xml::sax::XAttributeList;
using com::sun::star::xforms::XModel;
using namespace xmloff::token;




static struct SvXMLTokenMapEntry aAttributeMap[] =
{
    TOKEN_MAP_ENTRY( NONE, NODESET ),
    TOKEN_MAP_ENTRY( NONE, ID ),
    TOKEN_MAP_ENTRY( NONE, READONLY ),
    TOKEN_MAP_ENTRY( NONE, RELEVANT ),
    TOKEN_MAP_ENTRY( NONE, REQUIRED ),
    TOKEN_MAP_ENTRY( NONE, CONSTRAINT ),
    TOKEN_MAP_ENTRY( NONE, CALCULATE ),
    TOKEN_MAP_ENTRY( NONE, TYPE ),
    XML_TOKEN_MAP_END
};

// helper function; see below
void lcl_fillNamespaceContainer( const SvXMLNamespaceMap&,
                                 Reference<XNameContainer>& );

XFormsBindContext::XFormsBindContext( 
    SvXMLImport& rImport, 
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XPropertySet>& xModel ) :
        TokenContext( rImport, nPrefix, rLocalName, aAttributeMap, aEmptyMap ),
        mxModel( xModel, UNO_QUERY_THROW ),
        mxBinding( NULL )
{
    // attach binding to model
    mxBinding = mxModel->createBinding();
    DBG_ASSERT( mxBinding.is(), "can't create binding" );
    mxModel->getBindings()->insert( makeAny( mxBinding ) );
}

XFormsBindContext::~XFormsBindContext()
{
}

void XFormsBindContext::HandleAttribute( sal_uInt16 nToken, 
                                         const OUString& rValue )
{
    switch( nToken )
    {
    case XML_NODESET:
        lcl_setValue( mxBinding, OUSTRING("BindingExpression"), rValue );
        break;
    case XML_ID:
        lcl_setValue( mxBinding, OUSTRING("BindingID"), rValue );
        break;
    case XML_READONLY:
        lcl_setValue( mxBinding, OUSTRING("ReadonlyExpression"), rValue );
        break;
    case XML_RELEVANT:
        lcl_setValue( mxBinding, OUSTRING("RelevantExpression"), rValue );
        break;
    case XML_REQUIRED:
        lcl_setValue( mxBinding, OUSTRING("RequiredExpression"), rValue );
        break;
    case XML_CONSTRAINT:
        lcl_setValue( mxBinding, OUSTRING("ConstraintExpression"), rValue );
        break;
    case XML_CALCULATE:
        lcl_setValue( mxBinding, OUSTRING("CalculateExpression"), rValue );
        break;
    case XML_TYPE:
        lcl_setValue( mxBinding, OUSTRING("Type"),
                      makeAny( lcl_getTypeName( mxModel->getDataTypeRepository(),
                                       GetImport().GetNamespaceMap(),
                                       rValue ) ) );
        break;
    default:
        DBG_ERROR( "should not happen" );
        break;
    }
}

void XFormsBindContext::StartElement( 
    const Reference<XAttributeList>& xAttributeList )
{
    // we need to register the namespaces
    Reference<XNameContainer> xContainer( 
        mxBinding->getPropertyValue( OUSTRING("BindingNamespaces") ),
        UNO_QUERY );

    DBG_ASSERT( xContainer.is(), "binding should have a namespace container" );
    if( xContainer.is() )
        lcl_fillNamespaceContainer( GetImport().GetNamespaceMap(), xContainer);

    // call super-class for attribute handling
    TokenContext::StartElement( xAttributeList );
}

/** will be called for each child element */
SvXMLImportContext* XFormsBindContext::HandleChild( 
    sal_uInt16,
    sal_uInt16,
    const OUString&,
    const Reference<XAttributeList>& )
{
    DBG_ERROR( "no children supported" );
    return NULL;
}


void lcl_fillNamespaceContainer( 
    const SvXMLNamespaceMap& aMap,
    Reference<XNameContainer>& xContainer )
{
    sal_uInt16 nKeyIter = aMap.GetFirstKey();
    do
    {
        // get prefix and namespace
        const OUString& sPrefix = aMap.GetPrefixByKey( nKeyIter );
        const OUString& sNamespace = aMap.GetNameByKey( nKeyIter );

        // as a hack, we will ignore our own 'default' namespaces
        DBG_ASSERT( sPrefix.getLength() > 0, "no prefix?" );
        if( sPrefix.getStr()[0] != sal_Unicode( '_' )  &&
            nKeyIter >= XML_OLD_NAMESPACE_META_IDX )
        {
            // insert prefix (use replace if already known)
            if( xContainer->hasByName( sPrefix ) )
                xContainer->replaceByName( sPrefix, makeAny( sNamespace ) );
            else
                xContainer->insertByName( sPrefix, makeAny( sNamespace ) );
        }

        // proceed to next
        nKeyIter = aMap.GetNextKey( nKeyIter );
    }
    while( nKeyIter != XML_NAMESPACE_UNKNOWN );
}
