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


#ifndef SC_VBA_PAGEBREAKS_HXX
#define SC_VBA_PAGEBREAKS_HXX

#include <cppuhelper/implbase1.hxx>
#include <ooo/vba/excel/XHPageBreaks.hpp>
#include <ooo/vba/excel/XHPageBreak.hpp>
#include <ooo/vba/excel/XVPageBreaks.hpp>
#include <ooo/vba/excel/XVPageBreak.hpp>
#include <ooo/vba/excel/XRange.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/script/BasicErrorException.hpp>
#include <com/sun/star/sheet/XSheetPageBreak.hpp>
#include <com/sun/star/sheet/TablePageBreakData.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/table/XColumnRowRange.hpp>
#include <vbahelper/vbahelperinterface.hxx>
#include <vbahelper/vbacollectionimpl.hxx>

typedef CollTestImplHelper< ov::excel::XHPageBreaks > ScVbaHPageBreaks_BASE;

class ScVbaHPageBreaks : public ScVbaHPageBreaks_BASE
{
	css::uno::Reference< css::sheet::XSheetPageBreak > mxSheetPageBreak;
public:
	ScVbaHPageBreaks( const css::uno::Reference< ov::XHelperInterface >& xParent, 
                    const css::uno::Reference< css::uno::XComponentContext >& xContext,
            		css::uno::Reference< css::sheet::XSheetPageBreak >& xSheetPageBreak) throw (css::uno::RuntimeException);
	virtual ~ScVbaHPageBreaks(){}

    // XHPageBreaks 
    virtual css::uno::Any SAL_CALL Add( const css::uno::Any& Before) throw ( css::script::BasicErrorException, css::uno::RuntimeException);

	// XEnumerationAccess
	virtual css::uno::Type SAL_CALL getElementType() throw (css::uno::RuntimeException);
	virtual css::uno::Reference< css::container::XEnumeration > SAL_CALL createEnumeration() throw (css::uno::RuntimeException);	
	virtual css::uno::Any createCollectionObject(const css::uno::Any&);

	// XHelperInterface
	virtual rtl::OUString& getServiceImplName();
	virtual css::uno::Sequence<rtl::OUString> getServiceNames();
};

//VPageBreaks
typedef CollTestImplHelper< ov::excel::XVPageBreaks > ScVbaVPageBreaks_BASE;

class ScVbaVPageBreaks : public ScVbaVPageBreaks_BASE
{
	css::uno::Reference< css::sheet::XSheetPageBreak > mxSheetPageBreak;

public:
	ScVbaVPageBreaks( const css::uno::Reference< ov::XHelperInterface >& xParent, 
					  const css::uno::Reference< css::uno::XComponentContext >& xContext,
            		  css::uno::Reference< css::sheet::XSheetPageBreak >& xSheetPageBreak ) throw ( css::uno::RuntimeException );

	virtual ~ScVbaVPageBreaks();

	// XVPageBreaks 
	virtual css::uno::Any SAL_CALL Add( const css::uno::Any& Before ) throw ( css::script::BasicErrorException, css::uno::RuntimeException );

	// XEnumerationAccess
	virtual css::uno::Type SAL_CALL getElementType() throw ( css::uno::RuntimeException );
	virtual css::uno::Reference< css::container::XEnumeration > SAL_CALL createEnumeration() throw ( css::uno::RuntimeException );	
	virtual css::uno::Any createCollectionObject( const css::uno::Any& );

	// XHelperInterface
	virtual rtl::OUString& getServiceImplName();
	virtual css::uno::Sequence<rtl::OUString> getServiceNames();
};

#endif
