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
#include <xmloff/xmlimp.hxx>


#include <xmloff/xmlprcon.hxx>

using ::rtl::OUString;
using ::rtl::OUStringBuffer;

using namespace ::com::sun::star;
using namespace ::std;

SvXMLPropertySetContext::SvXMLPropertySetContext(
	SvXMLImport& rImp, sal_uInt16 nPrfx,
	const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList,
	sal_uInt32 nFam,
	vector< XMLPropertyState > &rProps,
	const UniReference < SvXMLImportPropertyMapper >  &rMap,
	sal_Int32 nSIdx, sal_Int32 nEIdx )
:	SvXMLImportContext( rImp, nPrfx, rLName )
,	mnStartIdx( nSIdx )
,	mnEndIdx( nEIdx )
,	mnFamily( nFam )
,	mrProperties( rProps )
,	mxMapper( rMap )
{
	mxMapper->importXML( mrProperties, xAttrList,
						GetImport().GetMM100UnitConverter(),
						GetImport().GetNamespaceMap(), mnFamily, 
						mnStartIdx, mnEndIdx );
}

SvXMLPropertySetContext::~SvXMLPropertySetContext()
{
}

SvXMLImportContext *SvXMLPropertySetContext::CreateChildContext(
	sal_uInt16 nPrefix,
	const OUString& rLocalName,
	const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
	UniReference< XMLPropertySetMapper > aSetMapper(
			mxMapper->getPropertySetMapper() );
	sal_Int32 nEntryIndex = aSetMapper->GetEntryIndex( nPrefix, rLocalName,
													   mnFamily, mnStartIdx );

	if( ( nEntryIndex != -1 ) && (-1 == mnEndIdx || nEntryIndex < mnEndIdx ) &&
		( 0 != ( aSetMapper->GetEntryFlags( nEntryIndex )
				 		& MID_FLAG_ELEMENT_ITEM_IMPORT ) ) )
	{
		XMLPropertyState aProp( nEntryIndex );
		return CreateChildContext( nPrefix, rLocalName, xAttrList,
								   mrProperties, aProp );
	}
	else
	{
		return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
	}
}

/** This method is called from this instance implementation of
	CreateChildContext if the element matches an entry in the
	SvXMLImportItemMapper with the mid flag MID_FLAG_ELEMENT
*/
SvXMLImportContext *SvXMLPropertySetContext::CreateChildContext(
	sal_uInt16 nPrefix,
	const rtl::OUString& rLocalName,
	const uno::Reference< xml::sax::XAttributeList >&,
	::std::vector< XMLPropertyState > &,
	const XMLPropertyState& )
{
	return new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
}


