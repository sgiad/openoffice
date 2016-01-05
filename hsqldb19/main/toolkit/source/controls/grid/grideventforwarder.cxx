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



#include "precompiled_toolkit.hxx"

#include "grideventforwarder.hxx"
#include "gridcontrol.hxx"

/** === begin UNO includes === **/
/** === end UNO includes === **/

//......................................................................................................................
namespace toolkit
{
//......................................................................................................................

	/** === begin UNO using === **/
	using ::com::sun::star::uno::Reference;
	using ::com::sun::star::uno::XInterface;
	using ::com::sun::star::uno::UNO_QUERY;
	using ::com::sun::star::uno::UNO_QUERY_THROW;
	using ::com::sun::star::uno::UNO_SET_THROW;
	using ::com::sun::star::uno::Exception;
	using ::com::sun::star::uno::RuntimeException;
	using ::com::sun::star::uno::Any;
	using ::com::sun::star::uno::makeAny;
	using ::com::sun::star::uno::Sequence;
	using ::com::sun::star::uno::Type;
    using ::com::sun::star::awt::grid::GridDataEvent;
    using ::com::sun::star::container::ContainerEvent;
    using ::com::sun::star::lang::EventObject;
	/** === end UNO using === **/

	//==================================================================================================================
	//= GridEventForwarder
	//==================================================================================================================
	//------------------------------------------------------------------------------------------------------------------
    GridEventForwarder::GridEventForwarder( UnoGridControl& i_parent )
        :m_parent( i_parent )
    {
    }

	//------------------------------------------------------------------------------------------------------------------
    GridEventForwarder::~GridEventForwarder()
    {
    }

	//------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::acquire() throw()
    {
        m_parent.acquire();
    }

	//------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::release() throw()
    {
        m_parent.release();
    }

    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::rowsInserted( const GridDataEvent& i_event ) throw (RuntimeException)
    {
        Reference< XGridDataListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->rowsInserted( i_event );
    }
    
    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::rowsRemoved( const GridDataEvent& i_event ) throw (RuntimeException)
    {
        Reference< XGridDataListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->rowsRemoved( i_event );
    }
    
    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::dataChanged( const GridDataEvent& i_event ) throw (RuntimeException)
    {
        Reference< XGridDataListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->dataChanged( i_event );
    }
    
    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::rowHeadingChanged( const GridDataEvent& i_event ) throw (RuntimeException)
    {
        Reference< XGridDataListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->rowHeadingChanged( i_event );
    }
    
    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::elementInserted( const ContainerEvent& i_event ) throw (RuntimeException)
    {
        Reference< XContainerListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->elementInserted( i_event );
    }
    
    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::elementRemoved( const ContainerEvent& i_event ) throw (RuntimeException)
    {
        Reference< XContainerListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->elementRemoved( i_event );
    }
    
    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::elementReplaced( const ContainerEvent& i_event ) throw (RuntimeException)
    {
        Reference< XContainerListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->elementReplaced( i_event );
    }

    //------------------------------------------------------------------------------------------------------------------
    void SAL_CALL GridEventForwarder::disposing( const EventObject& i_event ) throw (RuntimeException)
    {
        Reference< XEventListener > xPeer( m_parent.getPeer(), UNO_QUERY );
        if ( xPeer.is() )
            xPeer->disposing( i_event );
    }

//......................................................................................................................
} // namespace toolkit
//......................................................................................................................
