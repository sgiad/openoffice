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



#ifndef INSPECTORMODELBASE_HXX
#define INSPECTORMODELBASE_HXX

/** === begin UNO includes === **/
#include <com/sun/star/inspection/XObjectInspectorModel.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
/** === end UNO includes === **/

#include <cppuhelper/implbase3.hxx>
#include <cppuhelper/propshlp.hxx>

#include <comphelper/broadcasthelper.hxx>
#include <comphelper/componentcontext.hxx>
#include <comphelper/uno3.hxx>

#include <memory>

//........................................................................
namespace pcr
{
//........................................................................

    class InspectorModelProperties;
    //====================================================================
	//= ImplInspectorModel
	//====================================================================
    typedef ::cppu::WeakImplHelper3 <   ::com::sun::star::inspection::XObjectInspectorModel
                                    ,   ::com::sun::star::lang::XInitialization
                                    ,   ::com::sun::star::lang::XServiceInfo
                                    >   ImplInspectorModel_Base;
    typedef ::cppu::OPropertySetHelper  ImplInspectorModel_PBase;

    class ImplInspectorModel
            :public ::comphelper::OMutexAndBroadcastHelper
            ,public ImplInspectorModel_Base
            ,public ImplInspectorModel_PBase
	{
    protected:
        ::comphelper::ComponentContext                                  m_aContext;
        ::std::auto_ptr< InspectorModelProperties >                     m_pProperties;

    protected:
        ~ImplInspectorModel();

    public:
        ImplInspectorModel( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& _rxContext );

        DECLARE_XINTERFACE()
        DECLARE_XTYPEPROVIDER()

        // ::com::sun::star::beans::XPropertySet and friends
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::cppu::IPropertyArrayHelper & SAL_CALL getInfoHelper();
        virtual sal_Bool SAL_CALL convertFastPropertyValue( ::com::sun::star::uno::Any & rConvertedValue, ::com::sun::star::uno::Any & rOldValue, sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue ) throw (::com::sun::star::lang::IllegalArgumentException);
        virtual void SAL_CALL setFastPropertyValue_NoBroadcast( sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue ) throw (::com::sun::star::uno::Exception);
        virtual void SAL_CALL getFastPropertyValue( ::com::sun::star::uno::Any& rValue, sal_Int32 nHandle ) const;

        // ::com::sun::star::inspection::XObjectInspectorModel
        virtual ::sal_Bool SAL_CALL getHasHelpSection() throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Int32 SAL_CALL getMinHelpTextLines() throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Int32 SAL_CALL getMaxHelpTextLines() throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL getIsReadOnly() throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setIsReadOnly( ::sal_Bool _IsReadOnly ) throw (::com::sun::star::uno::RuntimeException);

        // ::com::sun::star::lang::XServiceInfo
        virtual ::sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw (::com::sun::star::uno::RuntimeException);

    protected:
        void enableHelpSectionProperties( sal_Int32 _nMinHelpTextLines, sal_Int32 _nMaxHelpTextLines );

    private:
        using ImplInspectorModel_PBase::getFastPropertyValue;
	};

//........................................................................
} // namespace pcr
//........................................................................

#endif // INSPECTORMODELBASE_HXX

