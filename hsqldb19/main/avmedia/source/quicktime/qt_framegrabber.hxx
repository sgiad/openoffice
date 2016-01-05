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


#ifndef QT_FRAMEGRABBER_HXX
#define QT_FRAMEGRABBER_HXX

#include "qt_common.hxx"

#include "com/sun/star/media/XFrameGrabber.hdl"

namespace avmedia { namespace quicktime {

// ----------------
// - FrameGrabber -
// ----------------

class FrameGrabber : public ::cppu::WeakImplHelper2 < ::com::sun::star::media::XFrameGrabber,
                                                      ::com::sun::star::lang::XServiceInfo >
{
public:

            FrameGrabber( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& rxMgr );
            ~FrameGrabber();

    bool    create( const ::rtl::OUString& rURL );

    // XFrameGrabber
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::graphic::XGraphic > SAL_CALL grabFrame( double fMediaTime ) throw (::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw (::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw (::com::sun::star::uno::RuntimeException);

private:

    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >    mxMgr;
    ::rtl::OUString                                                                     maURL;
	QTMovie*                                                                            mpMovie; 
    sal_Bool																			mbInitialized;
    long																				mnVersion;
};

} // namespace quicktime
} // namespace avmedia

#endif // QT_FRAMEGRABBER_HXX

