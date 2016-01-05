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



#ifndef PANELDECKLISTENERS_HXX
#define PANELDECKLISTENERS_HXX

#include "svtools/toolpanel/toolpaneldeck.hxx"

#include <boost/optional.hpp>
#include <vector>

//........................................................................
namespace svt
{
//........................................................................

    class IToolPanelDeckListener;

	//====================================================================
	//= PanelDeckListeners
	//====================================================================
    /** implements a container for IToolPanelDeckListeners
    */
	class PanelDeckListeners
	{
    public:
        PanelDeckListeners();
        ~PanelDeckListeners();

        // IToolPanelDeckListener equivalents, forward the events to all registered listeners
        void    PanelInserted( const PToolPanel& i_pPanel, const size_t i_nPosition );
        void    PanelRemoved( const size_t i_nPosition );
        void    ActivePanelChanged( const ::boost::optional< size_t >& i_rOldActive, const ::boost::optional< size_t >& i_rNewActive );
        void    LayouterChanged( const PDeckLayouter& i_rNewLayouter );
        void    Dying();

        // listener maintainance
        void    AddListener( IToolPanelDeckListener& i_rListener );
        void    RemoveListener( IToolPanelDeckListener& i_rListener );

    private:
        ::std::vector< IToolPanelDeckListener* >    m_aListeners;
	};

//........................................................................
} // namespace svt
//........................................................................

#endif // PANELDECKLISTENERS_HXX
