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
#include <com/sun/star/util/XCloneable.hpp>
#include "IgnoreTContext.hxx"
#ifndef _XMLOFF_TRANSFORMERBASE_HXX
#include "TransformerBase.hxx"
#endif
#include "MutableAttrList.hxx"
#include <xmloff/nmspmap.hxx>
#include "PersAttrListTContext.hxx"

using ::rtl::OUString;

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::xml::sax;

TYPEINIT1( XMLPersAttrListTContext, XMLTransformerContext );

void XMLPersAttrListTContext::AddAttribute(
		sal_uInt16 nAPrefix,
	   	::xmloff::token::XMLTokenEnum eAToken,
	   	::xmloff::token::XMLTokenEnum eVToken )
{
	OUString aAttrValue( ::xmloff::token::GetXMLToken( eVToken ) );
    AddAttribute( nAPrefix, eAToken, aAttrValue );
}

void XMLPersAttrListTContext::AddAttribute(
    sal_uInt16 nAPrefix,
    ::xmloff::token::XMLTokenEnum eAToken,
    const ::rtl::OUString & rValue )
{
	OUString aAttrQName( GetTransformer().GetNamespaceMap().GetQNameByKey(
				nAPrefix, ::xmloff::token::GetXMLToken( eAToken ) ) );
	OUString aAttrValue( rValue );

	XMLMutableAttributeList *pMutableAttrList;
	if( m_xAttrList.is() )
	{
		pMutableAttrList =
			static_cast< XMLMutableAttributeList * >( m_xAttrList.get() );
	}
	else
	{
		pMutableAttrList = new XMLMutableAttributeList ;
		m_xAttrList = pMutableAttrList;
	}

	pMutableAttrList->AddAttribute( aAttrQName, aAttrValue );
}

XMLPersAttrListTContext::XMLPersAttrListTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName ) :
	XMLTransformerContext( rImp, rQName ),
	m_aElemQName( rQName ),
	m_nActionMap( INVALID_ACTIONS )
{
}

XMLPersAttrListTContext::XMLPersAttrListTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName,
	   sal_uInt16 nActionMap ) :
	XMLTransformerContext( rImp, rQName ),
	m_aElemQName( rQName ),
	m_nActionMap( nActionMap )
{
}

XMLPersAttrListTContext::XMLPersAttrListTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName,
	    sal_uInt16 nPrefix,
		::xmloff::token::XMLTokenEnum eToken ) :
	XMLTransformerContext( rImp, rQName ),
	m_aElemQName( rImp.GetNamespaceMap().GetQNameByKey( nPrefix, 
							::xmloff::token::GetXMLToken( eToken ) ) ),
	m_nActionMap( INVALID_ACTIONS )
{
}

XMLPersAttrListTContext::XMLPersAttrListTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName,
	    sal_uInt16 nPrefix,
		::xmloff::token::XMLTokenEnum eToken,
	   sal_uInt16 nActionMap ) :
	XMLTransformerContext( rImp, rQName ),
	m_aElemQName( rImp.GetNamespaceMap().GetQNameByKey( nPrefix, 
							::xmloff::token::GetXMLToken( eToken ) ) ),
	m_nActionMap( nActionMap )
{
}

XMLPersAttrListTContext::~XMLPersAttrListTContext()
{
}

XMLTransformerContext *XMLPersAttrListTContext::CreateChildContext(
		sal_uInt16 /*nPrefix*/,
		const OUString& /*rLocalName*/,
		const OUString& rQName,
		const Reference< XAttributeList >& )
{
	// ignore all child elements
	return  new XMLIgnoreTransformerContext( GetTransformer(), 
											 rQName, sal_True, sal_True );
}

void XMLPersAttrListTContext::StartElement( 
	const Reference< XAttributeList >& rAttrList )
{
	XMLMutableAttributeList *pMutableAttrList = 0;

	Reference< XAttributeList > xAttrList( rAttrList );
	if( m_nActionMap != INVALID_ACTIONS )
	{
		pMutableAttrList = 
			GetTransformer().ProcessAttrList( xAttrList, m_nActionMap,
				   							  sal_True );
	}

	if( m_xAttrList.is() )
	{
		static_cast< XMLMutableAttributeList * >( m_xAttrList.get() )
				->AppendAttributeList( xAttrList );
	}
	else if( pMutableAttrList )
	{
		m_xAttrList = xAttrList;
	}
	else
	{
		m_xAttrList = new XMLMutableAttributeList( rAttrList, sal_True );
	}
}

void XMLPersAttrListTContext::EndElement()
{
	// ignore for now
}

void XMLPersAttrListTContext::Characters( const OUString& )
{
}

sal_Bool XMLPersAttrListTContext::IsPersistent() const
{
	return sal_True;
}

void XMLPersAttrListTContext::Export()
{
	GetTransformer().GetDocHandler()->startElement( m_aElemQName, m_xAttrList );
	ExportContent();
	GetTransformer().GetDocHandler()->endElement( m_aElemQName );
}

void XMLPersAttrListTContext::ExportContent()
{
	// nothing to export
}

Reference< XAttributeList > XMLPersAttrListTContext::GetAttrList() const
{
    return m_xAttrList;
}
