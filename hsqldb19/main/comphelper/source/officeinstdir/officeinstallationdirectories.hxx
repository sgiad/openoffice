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



#ifndef INCLUDED_OFFICEINSTALLATIONDIRECTORIES_HXX
#define INCLUDED_OFFICEINSTALLATIONDIRECTORIES_HXX

#include "osl/mutex.hxx"
#include "cppuhelper/implbase2.hxx"

#include "com/sun/star/lang/XServiceInfo.hpp"
#include "com/sun/star/uno/XComponentContext.hpp"
#include "com/sun/star/util/XOfficeInstallationDirectories.hpp"

namespace comphelper {

//=========================================================================

typedef cppu::WeakImplHelper2<
            com::sun::star::util::XOfficeInstallationDirectories,
            com::sun::star::lang::XServiceInfo > UnoImplBase;

struct mutex_holder
{
    osl::Mutex m_aMutex;
};

class OfficeInstallationDirectories : public mutex_holder, public UnoImplBase
{
public:
    OfficeInstallationDirectories(
        const com::sun::star::uno::Reference<
            com::sun::star::uno::XComponentContext > & xCtx );
    virtual ~OfficeInstallationDirectories();

    // XOfficeInstallationDirectories
    virtual ::rtl::OUString SAL_CALL
    getOfficeInstallationDirectoryURL()
        throw (::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL
    getOfficeUserDataDirectoryURL()
        throw (::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL
    makeRelocatableURL( const ::rtl::OUString& URL )
        throw (::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL
    makeAbsoluteURL( const ::rtl::OUString& URL )
        throw (::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL
    getImplementationName()
        throw (::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL
    supportsService( const ::rtl::OUString& ServiceName )
        throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL
    getSupportedServiceNames()
        throw (::com::sun::star::uno::RuntimeException);

    // XServiceInfo - static versions (used for component registration)
    static ::rtl::OUString SAL_CALL
        getImplementationName_static();
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL
        getSupportedServiceNames_static();
    static ::rtl::OUString SAL_CALL
        getSingletonName_static();
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL
        Create( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& );

private:
    void initDirs();

    rtl::OUString                                   m_aOfficeBrandDirMacro;
    rtl::OUString                                   m_aOfficeBaseDirMacro;
    rtl::OUString                                   m_aUserDirMacro;
    com::sun::star::uno::Reference<
        com::sun::star::uno::XComponentContext >    m_xCtx;
    rtl::OUString *                                 m_pOfficeBrandDir;
    rtl::OUString *                                 m_pOfficeBaseDir;
    rtl::OUString *                                 m_pUserDir;
};

} // namespace comphelper

#endif /* !INCLUDED_OFFICEINSTALLATIONDIRECTORIES_HXX */
