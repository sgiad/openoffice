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
#include "precompiled_comphelper.hxx"

#include "comphelper_module.hxx"

#include <com/sun/star/ucb/XAnyCompareFactory.hpp>
#include <com/sun/star/i18n/XCollator.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/uno/Sequence.h>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <cppuhelper/implbase3.hxx>
#include <cppuhelper/implbase1.hxx>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <comphelper/stl_types.hxx>
#include <map>


using namespace com::sun::star::uno;
using namespace com::sun::star::ucb;
using namespace com::sun::star::lang;
using namespace com::sun::star::i18n;
using namespace rtl;

//=============================================================================

class AnyCompare : public ::cppu::WeakImplHelper1< XAnyCompare >
{
	Reference< XCollator > m_rCollator;

public:
    AnyCompare( Reference< XComponentContext > xContext, const Locale& rLocale ) throw()
    {
        Reference< XMultiComponentFactory > xFactory = xContext->getServiceManager();
        if ( xFactory.is() )
	{
		m_rCollator = Reference< XCollator >(
                xFactory->createInstanceWithContext( OUString::createFromAscii( "com.sun.star.i18n.Collator" ), xContext ),
						UNO_QUERY );
		m_rCollator->loadDefaultCollator( rLocale,
										  0 ); //???
        }

	}

	virtual sal_Int16 SAL_CALL compare( const Any& any1, const Any& any2 ) throw(RuntimeException);
};

//=============================================================================

class AnyCompareFactory : public cppu::WeakImplHelper3< XAnyCompareFactory, XInitialization, XServiceInfo >
{
	Reference< XAnyCompare > 			m_rAnyCompare;
    Reference< XComponentContext >      m_rContext;
	Locale							  	m_Locale;

public:
    AnyCompareFactory( Reference< XComponentContext > xContext ) : m_rContext( xContext )
    {}

	// XAnyCompareFactory
	virtual Reference< XAnyCompare > SAL_CALL createAnyCompareByName ( const OUString& aPropertyName ) throw(::com::sun::star::uno::RuntimeException);

	// XInitialization
    virtual void SAL_CALL initialize( const Sequence< Any >& aArguments )
			throw ( Exception, RuntimeException );

	// XServiceInfo
	virtual OUString SAL_CALL getImplementationName(  ) throw(RuntimeException);
	virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) throw(RuntimeException);
	virtual Sequence< OUString > SAL_CALL getSupportedServiceNames(  ) throw(RuntimeException);

    // XServiceInfo - static versions (used for component registration)
    static ::rtl::OUString SAL_CALL getImplementationName_static();
    static Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames_static();
    static Reference< XInterface > SAL_CALL Create( const Reference< XComponentContext >& );
};

//===========================================================================================

sal_Int16 SAL_CALL AnyCompare::compare( const Any& any1, const Any& any2 ) throw(::com::sun::star::uno::RuntimeException)
{
	sal_Int16 aResult = 0;

	if( m_rCollator.is() )
	{
		OUString aStr1;
		OUString aStr2;

		any1 >>= aStr1;
		any2 >>= aStr2;

		aResult = ( sal_Int16 )m_rCollator->compareString( aStr1, aStr2 );
	}

	return aResult;
}

//===========================================================================================

Reference< XAnyCompare > SAL_CALL AnyCompareFactory::createAnyCompareByName( const OUString& aPropertyName ) throw(::com::sun::star::uno::RuntimeException)
{
	// for now only OUString properties compare is implemented
	// so no check for the property name is done

	if( aPropertyName.equals( OUString::createFromAscii( "Title" ) ) )
		return m_rAnyCompare;

	return Reference< XAnyCompare >();
}

void SAL_CALL AnyCompareFactory::initialize( const Sequence< Any >& aArguments ) throw ( Exception, RuntimeException )
{
	if( aArguments.getLength() )
	{
		if( aArguments[0] >>= m_Locale )
		{
            m_rAnyCompare = new AnyCompare( m_rContext, m_Locale );
			return;
		}
	}

}

OUString SAL_CALL AnyCompareFactory::getImplementationName(  ) throw( RuntimeException )
{
	return getImplementationName_static();
}

OUString SAL_CALL AnyCompareFactory::getImplementationName_static(  )
{
	return rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "AnyCompareFactory" ) );
}

sal_Bool SAL_CALL AnyCompareFactory::supportsService( const OUString& ServiceName ) throw(RuntimeException)
{
	rtl::OUString aServiceName( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.ucb.AnyCompareFactory" ) );
	return aServiceName == ServiceName;
}

Sequence< OUString > SAL_CALL AnyCompareFactory::getSupportedServiceNames(  ) throw(RuntimeException)
{
	return getSupportedServiceNames_static();
}

Sequence< OUString > SAL_CALL AnyCompareFactory::getSupportedServiceNames_static(  )
{
	const rtl::OUString aServiceName( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.ucb.AnyCompareFactory" ) );
	const Sequence< rtl::OUString > aSeq( &aServiceName, 1 );
	return aSeq;
}

Reference< XInterface > SAL_CALL AnyCompareFactory::Create(
                const Reference< XComponentContext >& rxContext )
{
    return (cppu::OWeakObject*)new AnyCompareFactory( rxContext );
}

void createRegistryInfo_AnyCompareFactory()
{
    static ::comphelper::module::OAutoRegistration< AnyCompareFactory > aAutoRegistration;
}
