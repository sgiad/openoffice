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



#ifndef SD_PANE_DOCKING_WINDOW_HXX
#define SD_PANE_DOCKING_WINDOW_HXX

#include <sfx2/titledockwin.hxx>
#include <sfx2/viewfrm.hxx>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

class ToolBox;
class SplitWindow;

namespace sd {

    class PaneDockingWindow : public ::sfx2::TitledDockingWindow
{
public:
    /** Create a new docking window.
        @param pBindings
            Used, among others, to determine the ViewShellBase and
            PaneManager that manage the new docking window.
        @param pChildWindow
            This child window is the logical container for the new docking
            window.
        @param pParent
            The parent window of the new docking window.
        @param rResId
            The resource is used to determine initial size and attributes.
        @param rsTitle
            the initial title
    */
    PaneDockingWindow (
        SfxBindings *pBindings,
        SfxChildWindow *pChildWindow,
        ::Window* pParent,
        const ResId& rResId,
        const ::rtl::OUString& rsTitle);

    virtual ~PaneDockingWindow (void);
	virtual void StateChanged( StateChangedType nType );
    virtual void MouseButtonDown (const MouseEvent& rEvent);
    /** When docked the given range is passed to the parent SplitWindow.
    */
    void SetValidSizeRange (const Range aValidSizeRange);

    enum Orientation { HorizontalOrientation, VerticalOrientation, UnknownOrientation };
    /** When the PaneDockingWindow is docked and managed by a split window
        it can derive its orientation from the orientation of the split
        window and return either HorizontalOrientation or
        VerticalOrientation.
        Otherwise UnknownOrientation is returned.
    */
    Orientation GetOrientation (void) const;
    
    /** The current height of the title bar.
    */
    sal_Int32 mnTitleBarHeight;
    
};

} // end of namespace ::sd

#endif
