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


#include "precompiled_connectivity.hxx"
#include "ParameterSubstitution.hxx"
#include "connectivity/sqlparse.hxx"
#include <comphelper/sequenceashashmap.hxx>

namespace connectivity
{
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::sdbc;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star;

    ParameterSubstitution::ParameterSubstitution(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& _rxContext ) : m_xContext(_rxContext)
    {
    }
    void SAL_CALL ParameterSubstitution::initialize( const uno::Sequence< uno::Any >& _aArguments ) throw (uno::Exception, uno::RuntimeException)
    {
        ::osl::MutexGuard aGuard(m_aMutex);
        comphelper::SequenceAsHashMap aArgs(_aArguments);
        uno::Reference< sdbc::XConnection > xConnection;
        xConnection = aArgs.getUnpackedValueOrDefault(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ActiveConnection")),xConnection);
        m_xConnection = xConnection;
    }
    //------------------------------------------------------------------------------
	rtl::OUString ParameterSubstitution::getImplementationName_Static(  ) throw(RuntimeException)
	{
		return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("org.openoffice.comp.helper.ParameterSubstitution"));
	}
	//------------------------------------------------------------------------------
	::rtl::OUString SAL_CALL ParameterSubstitution::getImplementationName(  ) throw(RuntimeException)
	{
		return getImplementationName_Static();
	}
	//------------------------------------------------------------------
	sal_Bool SAL_CALL ParameterSubstitution::supportsService( const ::rtl::OUString& _rServiceName ) throw(RuntimeException)
	{
		Sequence< ::rtl::OUString > aSupported(getSupportedServiceNames());
		const ::rtl::OUString* pSupported = aSupported.getConstArray();
		const ::rtl::OUString* pEnd = pSupported + aSupported.getLength();
		for (;pSupported != pEnd && !pSupported->equals(_rServiceName); ++pSupported)
			;

		return pSupported != pEnd;
	}
	//------------------------------------------------------------------
	Sequence< ::rtl::OUString > SAL_CALL ParameterSubstitution::getSupportedServiceNames(  ) throw(RuntimeException)
	{
		return getSupportedServiceNames_Static();
	}
    //------------------------------------------------------------------
    Sequence< ::rtl::OUString > ParameterSubstitution::getSupportedServiceNames_Static(  ) throw (RuntimeException)
	{
		Sequence< ::rtl::OUString > aSNS( 1 );
		aSNS[0] = ::rtl::OUString::createFromAscii("com.sun.star.sdb.ParameterSubstitution");
		return aSNS;
	}

	//------------------------------------------------------------------
    Reference< XInterface >  ParameterSubstitution::create(const Reference< XComponentContext >& _xContext)
    {
        return *(new ParameterSubstitution(_xContext));
    }
	//------------------------------------------------------------------
    ::rtl::OUString SAL_CALL ParameterSubstitution::substituteVariables( const ::rtl::OUString& _sText, ::sal_Bool /*bSubstRequired*/ ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::uno::RuntimeException)
    {
        ::rtl::OUString sRet = _sText;
        uno::Reference< sdbc::XConnection > xConnection = m_xConnection;
        if ( xConnection.is() )
        {
            try
		    {
                uno::Reference< XMultiServiceFactory> xFac(m_xContext->getServiceManager(),uno::UNO_QUERY_THROW);
			    OSQLParser aParser( xFac );
			    ::rtl::OUString sErrorMessage;
			    ::rtl::OUString sNewSql;
			    OSQLParseNode* pNode = aParser.parseTree(sErrorMessage,_sText);
			    if(pNode)
			    {	// special handling for parameters
				    OSQLParseNode::substituteParameterNames(pNode);
				    pNode->parseNodeToStr( sNewSql, xConnection );
				    delete pNode;
				    sRet = sNewSql;
			    }
		    }
		    catch(const Exception&)
		    {
		    }
        }
        return sRet;
    }
	//------------------------------------------------------------------
    ::rtl::OUString SAL_CALL ParameterSubstitution::reSubstituteVariables( const ::rtl::OUString& _sText ) throw (::com::sun::star::uno::RuntimeException)
    {
        return _sText;
    }
	//------------------------------------------------------------------
    ::rtl::OUString SAL_CALL ParameterSubstitution::getSubstituteVariableValue( const ::rtl::OUString& /*variable*/ ) throw (::com::sun::star::container::NoSuchElementException, ::com::sun::star::uno::RuntimeException)
    {
        throw container::NoSuchElementException();
    }
    //------------------------------------------------------------------


// ==================================
} // connectivity
// ==================================
