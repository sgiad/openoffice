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
#include "precompiled_idlc.hxx"
#include <idlc/fehelper.hxx>
#include <idlc/errorhandler.hxx>
#include <idlc/astarray.hxx>
#include "idlc/idlc.hxx"

using namespace ::rtl;

FeDeclarator::FeDeclarator(const OString& name, DeclaratorType declType, AstDeclaration* pComplPart)
	: m_pComplexPart(pComplPart)
	, m_name(name)
	, m_declType(declType)
{
}	

FeDeclarator::~FeDeclarator()
{
}	

sal_Bool FeDeclarator::checkType(AstDeclaration const * type)
{
	OString tmp(m_name);
	sal_Int32 count = m_name.lastIndexOf( ':' );
    if( count != -1 )
        tmp = m_name.copy( count+1 );

	if (tmp == type->getLocalName())
		return sal_False;
	else
		return sal_True;
}	

AstType const * FeDeclarator::compose(AstDeclaration const * pDecl)
{
	AstArray*	pArray;
	AstType*	pType;

    if ( pDecl == 0 )
    {
        return NULL;
    }
	if ( !pDecl->isType() ) 
	{
		idlc()->error()->noTypeError(pDecl);
		return NULL;
	}
	pType = (AstType*)pDecl;
	if (m_declType == FD_simple || m_pComplexPart == NULL) 
		return pType;

	if (m_pComplexPart->getNodeType() == NT_array) 
	{
		pArray = (AstArray*)m_pComplexPart;
		pArray->setType(pType);

		// insert array type in global scope
		AstScope* pScope = idlc()->scopes()->bottom();
		if ( pScope )
		{
			AstDeclaration* pDecl2 = pScope->addDeclaration(pArray);
			if ( (AstDeclaration*)pArray != pDecl2 )
			{
				delete m_pComplexPart;
				return (AstType*)pDecl2;
			}
		}
		return pArray;
	}

	return NULL; // return through this statement should not happen
}	

FeInheritanceHeader::FeInheritanceHeader(
    NodeType nodeType, ::rtl::OString* pName, ::rtl::OString* pInherits,
    std::vector< rtl::OString > * typeParameters)
	: m_nodeType(nodeType)
	, m_pName(pName)
	, m_pInherits(NULL)
{
    if (typeParameters != 0) {
        m_typeParameters = *typeParameters;
    }
	initializeInherits(pInherits);
}

void FeInheritanceHeader::initializeInherits(::rtl::OString* pInherits)
{
	if ( pInherits )
	{
		AstScope* pScope = idlc()->scopes()->topNonNull();
		AstDeclaration* pDecl = pScope->lookupByName(*pInherits);
        if ( pDecl )
        {
            AstDeclaration const * resolved = resolveTypedefs(pDecl);
            if ( resolved->getNodeType() == getNodeType()
                 && (resolved->getNodeType() != NT_interface
                     || static_cast< AstInterface const * >(
                         resolved)->isDefined()) )
            {
                if ( idlc()->error()->checkPublished( pDecl ) )
                {
                    m_pInherits = pDecl;
                }
            }
            else
            {
                idlc()->error()->inheritanceError(
                    getNodeType(), getName(), pDecl);
            }
        }
        else
        {
            idlc()->error()->lookupError(*pInherits);
        }
	}
}
