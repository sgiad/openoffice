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



#ifndef SD_FRAMEWORK_FULL_SCREEN_PANE_HXX
#define SD_FRAMEWORK_FULL_SCREEN_PANE_HXX

#include "FrameWindowPane.hxx"
#include <com/sun/star/frame/XLayoutManager.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <vcl/vclevent.hxx>
#include <boost/scoped_ptr.hpp>

namespace css = ::com::sun::star;

class WorkWindow;

namespace sd { class ViewShellBase; }

namespace sd { namespace framework {

/** The full screen pane creates a pane that covers the complete application
    window, i.e. that hides menu bar, tool bars, status bars.
*/
class FullScreenPane
    : public FrameWindowPane
{
public:
    /** Create a new full screen pane.
        @param rxComponentContext
            Used for creating a new canvas.
        @param rxPaneId
            The resource id of the new pane.
        @param pViewShellWindow
            The top-level parent of this window is used to obtain title and
            icon for the new top-level window.
    */
	FullScreenPane (
        const css::uno::Reference<css::uno::XComponentContext>& rxComponentContext,
        const css::uno::Reference<css::drawing::framework::XResourceId>& rxPaneId,
        const ::Window* pViewShellWindow);
    virtual ~FullScreenPane (void) throw();

    virtual void SAL_CALL disposing (void);

    //----- XPane -------------------------------------------------------------

    virtual sal_Bool SAL_CALL isVisible (void)
        throw (cssu::RuntimeException);

    virtual void SAL_CALL setVisible (sal_Bool bIsVisible)
        throw (cssu::RuntimeException);

    virtual cssu::Reference<css::accessibility::XAccessible> SAL_CALL getAccessible (void)
        throw (cssu::RuntimeException);

    virtual void SAL_CALL setAccessible (
        const cssu::Reference<css::accessibility::XAccessible>& rxAccessible)
        throw (cssu::RuntimeException);

    
    //-------------------------------------------------------------------------

    DECL_LINK(WindowEventHandler, VclWindowEvent*);

protected:
    virtual ::com::sun::star::uno::Reference<com::sun::star::rendering::XCanvas>
        CreateCanvas (void)
        throw (::com::sun::star::uno::RuntimeException);

private:
    css::uno::Reference<css::uno::XComponentContext> mxComponentContext;
    ::boost::scoped_ptr<WorkWindow> mpWorkWindow;

    void ExtractArguments (
        const css::uno::Reference<css::drawing::framework::XResourceId>& rxPaneId,
        sal_Int32& rnScreenNumberReturnValue);
};

} } // end of namespace sd::framework

#endif
