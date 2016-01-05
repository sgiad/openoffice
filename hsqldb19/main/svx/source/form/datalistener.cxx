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
#include "precompiled_svx.hxx"

#include "datalistener.hxx"
#include "datanavi.hxx"

using namespace ::com::sun::star::container;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::dom::events;

//............................................................................
namespace svxform
{
//............................................................................

    DataListener::DataListener( DataNavigatorWindow* pNaviWin ) :

        m_pNaviWin( pNaviWin )

    {
        DBG_ASSERT( m_pNaviWin, "DataListener::Ctor(): no navigator win" );
    }

    DataListener::~DataListener()
    {
    }

    // XContainerListener
    void SAL_CALL DataListener::elementInserted( const ContainerEvent& /*Event*/ ) throw (RuntimeException)
    {
        m_pNaviWin->NotifyChanges();
    }

    void SAL_CALL DataListener::elementRemoved( const ContainerEvent& /*Event*/ ) throw (RuntimeException)
    {
        m_pNaviWin->NotifyChanges();
    }

    void SAL_CALL DataListener::elementReplaced( const ContainerEvent& /*Event*/ ) throw (RuntimeException)
    {
        m_pNaviWin->NotifyChanges();
    }

    // XFrameActionListener
    void SAL_CALL DataListener::frameAction( const FrameActionEvent& rActionEvt ) throw (RuntimeException)
    {
        if ( FrameAction_COMPONENT_ATTACHED == rActionEvt.Action ||
             FrameAction_COMPONENT_REATTACHED == rActionEvt.Action )
        {
            m_pNaviWin->NotifyChanges( FrameAction_COMPONENT_REATTACHED == rActionEvt.Action );
        }
    }

    // xml::dom::events::XEventListener
    void SAL_CALL DataListener::handleEvent( const Reference< XEvent >& /*evt*/ ) throw (RuntimeException)
    {
        m_pNaviWin->NotifyChanges();
    }

    // lang::XEventListener
    void SAL_CALL DataListener::disposing( const EventObject& /*Source*/ ) throw (RuntimeException)
    {
        DBG_ERRORFILE( "disposing" );
    }

//............................................................................
}   // namespace svxform
//............................................................................

