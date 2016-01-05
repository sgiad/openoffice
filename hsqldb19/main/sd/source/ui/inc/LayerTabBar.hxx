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



#ifndef SD_LAYER_TAB_BAR_HXX
#define SD_LAYER_TAB_BAR_HXX

#include <svtools/tabbar.hxx>
#include <svtools/transfer.hxx>

namespace sd {

/*************************************************************************
|*
|* TabBar fuer die Layerverwaltung
|*
\************************************************************************/

class DrawViewShell;

class LayerTabBar
    : public TabBar, 
      public DropTargetHelper
{
public:
    LayerTabBar (
        DrawViewShell* pDrViewSh, 
        ::Window* pParent);
    LayerTabBar (
        DrawViewShell* pDrViewSh, 
        ::Window* pParent,
        const ResId& rResId);
    virtual ~LayerTabBar (void);

    /** Inform all listeners of this control that the current layer has been
        activated.  Call this method after switching the current layer and is
        not done elsewhere (like when using ctrl + page up/down keys).
    */
    void SendActivatePageEvent (void);

    /** Inform all listeners of this control that the current layer has been
        deactivated.  Call this method before switching the current layer
        and is not done elsewhere (like when using ctrl page up/down keys).
    */
    void SendDeactivatePageEvent (void);

protected:
	DrawViewShell* pDrViewSh;

	// TabBar
	virtual void		Select();
	virtual void		DoubleClick();
	virtual void		MouseButtonDown(const MouseEvent& rMEvt);
						
	virtual void		Command(const CommandEvent& rCEvt);
						
	virtual long		StartRenaming();
	virtual long		AllowRenaming();
	virtual void		EndRenaming();
						
	virtual void		ActivatePage();

	// DropTargetHelper
	virtual sal_Int8	AcceptDrop( const AcceptDropEvent& rEvt );
	virtual sal_Int8	ExecuteDrop( const ExecuteDropEvent& rEvt );
};

} // end of namespace sd

#endif
