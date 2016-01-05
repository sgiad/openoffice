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


#ifndef CHART_WRAPPED_IGNORE_PROPERTY_HXX
#define CHART_WRAPPED_IGNORE_PROPERTY_HXX

#include "WrappedProperty.hxx"
#include "charttoolsdllapi.hxx"

#include <vector>

//.............................................................................
namespace chart
{
//.............................................................................

class OOO_DLLPUBLIC_CHARTTOOLS WrappedIgnoreProperty : public WrappedProperty
{
public:
    WrappedIgnoreProperty( const ::rtl::OUString& rOuterName, const ::com::sun::star::uno::Any& rDefaultValue );
    virtual ~WrappedIgnoreProperty();

    virtual void setPropertyValue( const ::com::sun::star::uno::Any& rOuterValue, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& xInnerPropertySet ) const
                        throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

    virtual ::com::sun::star::uno::Any getPropertyValue( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& xInnerPropertySet ) const
                        throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

SAL_DLLPRIVATE virtual void setPropertyToDefault( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyState >& xInnerPropertyState ) const
                        throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::uno::RuntimeException);

SAL_DLLPRIVATE virtual ::com::sun::star::uno::Any getPropertyDefault( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyState >& xInnerPropertyState ) const
                        throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);

SAL_DLLPRIVATE virtual ::com::sun::star::beans::PropertyState getPropertyState( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyState >& xInnerPropertyState ) const
                        throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::uno::RuntimeException);

protected:
    ::com::sun::star::uno::Any          m_aDefaultValue;
    mutable ::com::sun::star::uno::Any  m_aCurrentValue;
};

class OOO_DLLPUBLIC_CHARTTOOLS WrappedIgnoreProperties
{
public:
    static void addIgnoreLineProperties( std::vector< WrappedProperty* >& rList );

    static void addIgnoreFillProperties( std::vector< WrappedProperty* >& rList );
    SAL_DLLPRIVATE static void addIgnoreFillProperties_without_BitmapProperties( std::vector< WrappedProperty* >& rList );
    SAL_DLLPRIVATE static void addIgnoreFillProperties_only_BitmapProperties( std::vector< WrappedProperty* >& rList );
};

//.............................................................................
} //namespace chart
//.............................................................................

// CHART_WRAPPED_IGNORE_PROPERTY_HXX
#endif
