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



#ifndef INCLUDED_unotools_OPTIONS_HXX
#define INCLUDED_unotools_OPTIONS_HXX

#include "sal/config.h"
#include "unotools/unotoolsdllapi.h"

/*
	The class utl::detail::Options provides a kind of multiplexer. It implements a ConfigurationListener
	that is usually registered at a ConfigItem class. At the same time it implements a ConfigurationBroadcaster
	that allows further ("external") listeners to register.
	Once the class deriving from Options is notified about
	configuration changes by the ConfigItem if its content has been changed by calling some of its methods,
	a call of the Options::NotifyListeners() method will send out notifications to all external listeners.
*/

namespace utl {

    class ConfigurationBroadcaster;
    class IMPL_ConfigurationListenerList;

	// interface for configuration listener
    class UNOTOOLS_DLLPUBLIC ConfigurationListener
    {
    public:
        virtual void ConfigurationChanged( ConfigurationBroadcaster* p, sal_uInt32 nHint=0 ) = 0;
    };

	// complete broadcasting implementation
    class UNOTOOLS_DLLPUBLIC ConfigurationBroadcaster
    {
        IMPL_ConfigurationListenerList* mpList;
		sal_Int32               m_nBroadcastBlocked;     // broadcast only if this is 0
		sal_uInt32				m_nBlockedHint;

    public:
        void AddListener( utl::ConfigurationListener* pListener );
        void RemoveListener( utl::ConfigurationListener* pListener );

		// notify listeners; nHint is an implementation detail of the particular class deriving from ConfigurationBroadcaster
        void NotifyListeners( sal_uInt32 nHint );
        ConfigurationBroadcaster();
        virtual ~ConfigurationBroadcaster();
        virtual void BlockBroadcasts( bool bBlock );
    };

namespace detail {

// A base class for the various option classes supported by
// unotools/source/config/itemholderbase.hxx (which must be public, as it is
// shared between unotools, svl and svt)
// It also provides an implementation for a Configuration Listener and inherits a broadcaster implementation

class UNOTOOLS_DLLPUBLIC Options : public utl::ConfigurationBroadcaster, public utl::ConfigurationListener
{
public:
    Options();

    virtual ~Options() = 0;

private:
    UNOTOOLS_DLLPRIVATE Options(Options &); // not defined
    UNOTOOLS_DLLPRIVATE void operator =(Options &); // not defined

protected:
    virtual void ConfigurationChanged( ::utl::ConfigurationBroadcaster* p, sal_uInt32 nHint=0 );
};

} }

#endif
