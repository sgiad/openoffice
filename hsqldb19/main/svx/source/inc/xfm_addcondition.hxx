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



#ifndef SVX_SOURCE_INC_XFM_ADDCONDITION_HXX
#define SVX_SOURCE_INC_XFM_ADDCONDITION_HXX

/** === begin UNO includes === **/
#include <com/sun/star/xforms/XModel.hpp>
/** === end UNO includes === **/
#include <svtools/genericunodialog.hxx>
#include <comphelper/proparrhlp.hxx>

//........................................................................
namespace svxform
{
//........................................................................

	//====================================================================
	//= OAddConditionDialog
	//====================================================================
    typedef ::svt::OGenericUnoDialog OAddConditionDialogBase;
    class OAddConditionDialog
		    :public OAddConditionDialogBase
		    ,public ::comphelper::OPropertyArrayUsageHelper< OAddConditionDialog >
    {
    private:
        // <properties>
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
                                m_xBinding;
        ::rtl::OUString         m_sFacetName;
        ::rtl::OUString         m_sConditionValue;
        ::com::sun::star::uno::Reference< ::com::sun::star::xforms::XModel >
                                m_xWorkModel;
        // </properties>

    public:
        static ::com::sun::star::uno::Reference< com::sun::star::uno::XInterface >
            SAL_CALL Create( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& );

    protected:
	    OAddConditionDialog( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB );

	    // XTypeProvider
        virtual com::sun::star::uno::Sequence<sal_Int8> SAL_CALL getImplementationId(  ) throw(com::sun::star::uno::RuntimeException);
		
	    // XServiceInfo
	    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(com::sun::star::uno::RuntimeException);
	    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(com::sun::star::uno::RuntimeException);

	    // XPropertySet
	    virtual com::sun::star::uno::Reference<com::sun::star::beans::XPropertySetInfo>  SAL_CALL getPropertySetInfo() throw(com::sun::star::uno::RuntimeException);
	    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

	    // OPropertyArrayUsageHelper
	    virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

    protected:
        // OGenericUnoDialog overridables
	    virtual Dialog*	createDialog(Window* _pParent);
		virtual void executedDialog(sal_Int16 _nExecutionResult);
    };

//........................................................................
} // namespace svxform
//........................................................................

#endif // SVX_SOURCE_INC_XFM_ADDCONDITION_HXX

