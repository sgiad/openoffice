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



#ifndef SC_FIELDUNO_HXX
#define SC_FIELDUNO_HXX

#include "address.hxx"
#include "mutexhlp.hxx"
 
#include <svl/lstner.hxx>
#include <svl/itemprop.hxx>
#include <editeng/editdata.hxx>
#include <com/sun/star/text/XTextField.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/container/XContainer.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>
#include <com/sun/star/container/XEnumerationAccess.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/util/XRefreshable.hpp>
#include <cppuhelper/component.hxx>
#include <cppuhelper/implbase5.hxx>
#include <osl/mutex.hxx>

class SvxEditSource;
class SvxFieldItem;
class ScCellFieldObj;
class ScHeaderFieldObj;
class ScHeaderFooterContentObj;
class ScDocShell;


//------------------------------------------------------------------


class ScCellFieldsObj : public cppu::WeakImplHelper5<
							com::sun::star::container::XEnumerationAccess,
							com::sun::star::container::XIndexAccess,
							com::sun::star::container::XContainer,
                            com::sun::star::util::XRefreshable,
							com::sun::star::lang::XServiceInfo >,
						public SfxListener
{
private:
	ScDocShell*				pDocShell;
	ScAddress				aCellPos;
	SvxEditSource*			pEditSource;
    ///	List of refresh listeners.
	cppu::OInterfaceContainerHelper* mpRefreshListeners;
    /// mutex to lock the InterfaceContainerHelper
    osl::Mutex              aMutex;

	ScCellFieldObj*			GetObjectByIndex_Impl(sal_Int32 Index) const;

public:
							ScCellFieldsObj(ScDocShell* pDocSh, const ScAddress& rPos);
	virtual					~ScCellFieldsObj();

	virtual void			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

							// XIndexAccess
	virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index )
								throw(::com::sun::star::lang::IndexOutOfBoundsException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);

							// XEnumerationAccess
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XEnumeration > SAL_CALL
							createEnumeration() throw(::com::sun::star::uno::RuntimeException);

							// XElementAccess
	virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
								throw(::com::sun::star::uno::RuntimeException);
	virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

							// XContainer
	virtual void SAL_CALL	addContainerListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::container::XContainerListener >& xListener )
									throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removeContainerListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::container::XContainerListener >& xListener )
									throw(::com::sun::star::uno::RuntimeException);

                            // XRefreshable
    virtual void SAL_CALL refresh(  ) 
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL addRefreshListener( const ::com::sun::star::uno::Reference< 
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeRefreshListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);

							// XServiceInfo
	virtual ::rtl::OUString SAL_CALL getImplementationName()
								throw(::com::sun::star::uno::RuntimeException);
	virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
								throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
								throw(::com::sun::star::uno::RuntimeException);
};


class ScCellFieldObj : public ScMutexHelper,
						public ::cppu::OComponentHelper,
						public ::com::sun::star::text::XTextField,
						public ::com::sun::star::beans::XPropertySet,
						public ::com::sun::star::lang::XUnoTunnel,
						public ::com::sun::star::lang::XServiceInfo,
						public SfxListener
{
private:
	const SfxItemPropertySet*		pPropSet;
	ScDocShell*				pDocShell;
	ScAddress				aCellPos;
	SvxEditSource*			pEditSource;
	ESelection				aSelection;

	String					aUrl;				// Inhalt, wenn noch nicht eingefuegt (nur dann!)
	String					aRepresentation;
	String					aTarget;

	ScCellFieldObj(); // disabled
public:
							ScCellFieldObj(ScDocShell* pDocSh, const ScAddress& rPos,
											const ESelection& rSel);
	virtual					~ScCellFieldObj();

	virtual void			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

							// per getImplementation gerufen:
	void					DeleteField();
	sal_Bool					IsInserted() const		{ return pEditSource != NULL; }
	SvxFieldItem			CreateFieldItem();
	void					InitDoc( ScDocShell* pDocSh, const ScAddress& rPos,
										const ESelection& rSel );

	virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation(
								const ::com::sun::star::uno::Type & rType )
									throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Any SAL_CALL queryInterface(
								const ::com::sun::star::uno::Type & rType )
									throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	acquire() throw();
	virtual void SAL_CALL	release() throw();

							// XTextField
	virtual ::rtl::OUString SAL_CALL getPresentation( sal_Bool bShowCommand )
								throw(::com::sun::star::uno::RuntimeException);

							// XTextContent
	virtual void SAL_CALL	attach( const ::com::sun::star::uno::Reference<
								::com::sun::star::text::XTextRange >& xTextRange )
									throw(::com::sun::star::lang::IllegalArgumentException,
											::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange > SAL_CALL
							getAnchor() throw(::com::sun::star::uno::RuntimeException);

							// XComponent
	virtual void SAL_CALL	dispose() throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	addEventListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::lang::XEventListener >& xListener )
									throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removeEventListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::lang::XEventListener >& aListener )
									throw(::com::sun::star::uno::RuntimeException);

							// XPropertySet
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
							SAL_CALL getPropertySetInfo()
								throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	setPropertyValue( const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Any& aValue )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::beans::PropertyVetoException,
									::com::sun::star::lang::IllegalArgumentException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
									const ::rtl::OUString& PropertyName )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XPropertyChangeListener >& xListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XPropertyChangeListener >& aListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	addVetoableChangeListener( const ::rtl::OUString& PropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XVetoableChangeListener >& aListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XVetoableChangeListener >& aListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);

							// XUnoTunnel
	virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence<
									sal_Int8 >& aIdentifier )
								throw(::com::sun::star::uno::RuntimeException);

	static const com::sun::star::uno::Sequence<sal_Int8>& getUnoTunnelId();
	static ScCellFieldObj* getImplementation( const com::sun::star::uno::Reference<
									com::sun::star::text::XTextContent> xObj );

							// XServiceInfo
	virtual ::rtl::OUString SAL_CALL getImplementationName()
								throw(::com::sun::star::uno::RuntimeException);
	virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
								throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
								throw(::com::sun::star::uno::RuntimeException);

							// XTypeProvider
	virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
								throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
								throw(::com::sun::star::uno::RuntimeException);
};

//------------------------------------------------------------------

class ScHeaderFieldsObj : public cppu::WeakImplHelper5<
							com::sun::star::container::XEnumerationAccess,
							com::sun::star::container::XIndexAccess,
							com::sun::star::container::XContainer,
                            com::sun::star::util::XRefreshable,
							com::sun::star::lang::XServiceInfo >
{
private:
	ScHeaderFooterContentObj*	pContentObj;
	sal_uInt16						nPart;
	sal_uInt16						nType;
	SvxEditSource*				pEditSource;

    ///	List of refresh listeners.
	cppu::OInterfaceContainerHelper* mpRefreshListeners;
    /// mutex to lock the InterfaceContainerHelper
    osl::Mutex                  aMutex;

	ScHeaderFieldObj*		GetObjectByIndex_Impl(sal_Int32 Index) const;

public:
							ScHeaderFieldsObj(ScHeaderFooterContentObj* pContent,
												sal_uInt16 nP, sal_uInt16 nT);
	virtual					~ScHeaderFieldsObj();

							// XIndexAccess
	virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index )
								throw(::com::sun::star::lang::IndexOutOfBoundsException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);

							// XEnumerationAccess
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XEnumeration > SAL_CALL
							createEnumeration() throw(::com::sun::star::uno::RuntimeException);

							// XElementAccess
	virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
								throw(::com::sun::star::uno::RuntimeException);
	virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

							// XContainer
	virtual void SAL_CALL	addContainerListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::container::XContainerListener >& xListener )
									throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removeContainerListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::container::XContainerListener >& xListener )
									throw(::com::sun::star::uno::RuntimeException);

                            // XRefreshable
    virtual void SAL_CALL refresh(  ) 
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL addRefreshListener( const ::com::sun::star::uno::Reference< 
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeRefreshListener( const ::com::sun::star::uno::Reference<
                                ::com::sun::star::util::XRefreshListener >& l )
                                    throw (::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
	virtual ::rtl::OUString SAL_CALL getImplementationName()
								throw(::com::sun::star::uno::RuntimeException);
	virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
								throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
								throw(::com::sun::star::uno::RuntimeException);
};


class ScHeaderFieldObj : public ScMutexHelper,
							public ::cppu::OComponentHelper,
							public ::com::sun::star::text::XTextField,
							public ::com::sun::star::beans::XPropertySet,
							public ::com::sun::star::lang::XUnoTunnel,
							public ::com::sun::star::lang::XServiceInfo
{
private:
	const SfxItemPropertySet*   pPropSet;
	ScHeaderFooterContentObj*	pContentObj;
	sal_uInt16						nPart;
	sal_uInt16						nType;
	SvxEditSource*				pEditSource;
	ESelection					aSelection;
	sal_Int16					nFileFormat;		// enum SvxFileFormat, valid if not inserted

    ScHeaderFieldObj(); // disabled 
public:
							ScHeaderFieldObj(ScHeaderFooterContentObj* pContent, sal_uInt16 nP,
											sal_uInt16 nT, const ESelection& rSel);
	virtual					~ScHeaderFieldObj();

							// per getImplementation gerufen:
	void					DeleteField();
	sal_Bool					IsInserted() const		{ return pEditSource != NULL; }
	SvxFieldItem			CreateFieldItem();
	void					InitDoc( ScHeaderFooterContentObj* pContent, sal_uInt16 nP,
										const ESelection& rSel );

	virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation(
								const ::com::sun::star::uno::Type & rType )
									throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Any SAL_CALL queryInterface(
								const ::com::sun::star::uno::Type & rType )
									throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	acquire() throw();
	virtual void SAL_CALL	release() throw();

							// XTextField
	virtual ::rtl::OUString SAL_CALL getPresentation( sal_Bool bShowCommand )
								throw(::com::sun::star::uno::RuntimeException);

							// XTextContent
	virtual void SAL_CALL	attach( const ::com::sun::star::uno::Reference<
								::com::sun::star::text::XTextRange >& xTextRange )
									throw(::com::sun::star::lang::IllegalArgumentException,
											::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange > SAL_CALL
							getAnchor() throw(::com::sun::star::uno::RuntimeException);

							// XComponent
	virtual void SAL_CALL	dispose() throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	addEventListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::lang::XEventListener >& xListener )
									throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removeEventListener( const ::com::sun::star::uno::Reference<
								::com::sun::star::lang::XEventListener >& aListener )
									throw(::com::sun::star::uno::RuntimeException);

							// XPropertySet
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo >
							SAL_CALL getPropertySetInfo()
								throw(::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	setPropertyValue( const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Any& aValue )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::beans::PropertyVetoException,
									::com::sun::star::lang::IllegalArgumentException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
									const ::rtl::OUString& PropertyName )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XPropertyChangeListener >& xListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XPropertyChangeListener >& aListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	addVetoableChangeListener( const ::rtl::OUString& PropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XVetoableChangeListener >& aListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL	removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
									const ::com::sun::star::uno::Reference<
										::com::sun::star::beans::XVetoableChangeListener >& aListener )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);

							// XUnoTunnel
	virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence<
									sal_Int8 >& aIdentifier )
								throw(::com::sun::star::uno::RuntimeException);

	static const com::sun::star::uno::Sequence<sal_Int8>& getUnoTunnelId();
	static ScHeaderFieldObj* getImplementation( const com::sun::star::uno::Reference<
									com::sun::star::text::XTextContent> xObj );

							// XServiceInfo
	virtual ::rtl::OUString SAL_CALL getImplementationName()
								throw(::com::sun::star::uno::RuntimeException);
	virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
								throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
								throw(::com::sun::star::uno::RuntimeException);

							// XTypeProvider
	virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
								throw(::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
								throw(::com::sun::star::uno::RuntimeException);
};

#endif

