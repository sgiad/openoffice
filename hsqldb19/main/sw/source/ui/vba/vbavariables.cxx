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


#include "vbavariables.hxx"
#include "vbavariable.hxx"
#include <com/sun/star/beans/XPropertyContainer.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>

using namespace ::ooo::vba;
using namespace ::com::sun::star;

uno::Reference< container::XIndexAccess > createVariablesAccess( const uno::Reference< XHelperInterface >& xParent, const uno::Reference< uno::XComponentContext >& xContext, const uno::Reference< beans::XPropertyAccess >& xUserDefined ) throw ( uno::RuntimeException )
{
    // FIXME: the performance is poor?
    XNamedObjectCollectionHelper< word::XVariable >::XNamedVec mVariables;
    const uno::Sequence< beans::PropertyValue > props = xUserDefined->getPropertyValues();
    sal_Int32 nCount = props.getLength();
    mVariables.reserve( nCount );
    for( sal_Int32 i=0; i < nCount; i++ )
        mVariables.push_back( uno::Reference< word::XVariable > ( new SwVbaVariable( xParent, xContext, xUserDefined, props[i].Name ) ) );

    uno::Reference< container::XIndexAccess > xVariables( new XNamedObjectCollectionHelper< word::XVariable >( mVariables ) );
    return xVariables;
}

SwVbaVariables::SwVbaVariables( const uno::Reference< XHelperInterface >& xParent, const uno::Reference< ::com::sun::star::uno::XComponentContext > & xContext, const uno::Reference< beans::XPropertyAccess >& rUserDefined ): SwVbaVariables_BASE( xParent, xContext, createVariablesAccess( xParent, xContext, rUserDefined ) ),  mxUserDefined( rUserDefined )
{
}
// XEnumerationAccess
uno::Type
SwVbaVariables::getElementType() throw (uno::RuntimeException)
{
	return word::XVariable::static_type(0);
}
uno::Reference< container::XEnumeration >
SwVbaVariables::createEnumeration() throw (uno::RuntimeException)
{
    uno::Reference< container::XEnumerationAccess > xEnumerationAccess( m_xIndexAccess, uno::UNO_QUERY_THROW );
    return xEnumerationAccess->createEnumeration();
}

uno::Any
SwVbaVariables::createCollectionObject( const css::uno::Any& aSource )
{
    return aSource;
}

uno::Any SAL_CALL
SwVbaVariables::Add( const rtl::OUString& rName, const uno::Any& rValue ) throw (uno::RuntimeException)
{
    uno::Any aValue;
    if( rValue.hasValue() )
        aValue = rValue;
    else
        aValue <<= rtl::OUString();
    uno::Reference< beans::XPropertyContainer > xPropertyContainer( mxUserDefined, uno::UNO_QUERY_THROW );
    xPropertyContainer->addProperty( rName, beans::PropertyAttribute::MAYBEVOID | beans::PropertyAttribute::REMOVEABLE, aValue );

    return uno::makeAny( uno::Reference< word::XVariable >( new SwVbaVariable( getParent(), mxContext, mxUserDefined, rName ) ) );
}

rtl::OUString& 
SwVbaVariables::getServiceImplName()
{
	static rtl::OUString sImplName( RTL_CONSTASCII_USTRINGPARAM("SwVbaVariables") );
	return sImplName;
}

css::uno::Sequence<rtl::OUString> 
SwVbaVariables::getServiceNames()
{
	static uno::Sequence< rtl::OUString > sNames;
	if ( sNames.getLength() == 0 )
	{
		sNames.realloc( 1 );
		sNames[0] = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("ooo.vba.word.Variables") );
	}
	return sNames;
}
