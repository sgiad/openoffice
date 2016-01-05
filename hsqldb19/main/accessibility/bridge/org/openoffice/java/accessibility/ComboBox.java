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


package org.openoffice.java.accessibility;

import com.sun.star.accessibility.*;
import com.sun.star.uno.*;

import javax.accessibility.AccessibleContext;
import javax.accessibility.AccessibleState;
import javax.accessibility.AccessibleStateSet;

import javax.swing.SwingConstants;


/**
 */
public class ComboBox extends Container {
    private XAccessibleAction unoAccessibleAction = null;

    public ComboBox(XAccessible xAccessible, XAccessibleContext xAccessibleContext) {
        super(javax.accessibility.AccessibleRole.COMBO_BOX, xAccessible,
            xAccessibleContext);
    }

    /** Appends the specified component to the end of this container */
    public java.awt.Component add(java.awt.Component c) {
        // List should be always the first child 
        if (c instanceof List) {
            return super.add(c, 0);
        } else {
            return super.add(c);
        }
    }

    /** Creates the AccessibleContext associated with this object */
    public javax.accessibility.AccessibleContext createAccessibleContext() {
        return new AccessibleComboBox();
    }

    protected class AccessibleComboBox extends AccessibleContainer
        implements javax.accessibility.AccessibleAction {
        /**
        * Though the class is abstract, this should be called by all sub-classes
        */
        protected AccessibleComboBox() {
            super();
        }

        /*
        * AccessibleContext
        */

        /** Gets the AccessibleAction associated with this object that supports one or more actions */
        public javax.accessibility.AccessibleAction getAccessibleAction() {
            if (unoAccessibleAction == null) {
                unoAccessibleAction = (XAccessibleAction) UnoRuntime.queryInterface(XAccessibleAction.class,
                        unoAccessibleContext);

                if (unoAccessibleAction == null) {
                    return null;
                }
            }

            return this;
        }

        /*
        * AccessibleAction
        */

        /** Performs the specified Action on the object */
        public boolean doAccessibleAction(int param) {
            if (param == 0) {
                try {
                    return unoAccessibleAction.doAccessibleAction(0);
                } catch (com.sun.star.uno.Exception e) {
                }
            }

            return false;
        }

        /** Returns a description of the specified action of the object */
        public java.lang.String getAccessibleActionDescription(int param) {
            return javax.swing.UIManager.getString("ComboBox.togglePopupText");
        }

        /** Returns the number of accessible actions available in this object */
        public int getAccessibleActionCount() {
            return 1;
        }
    }

    /**
     * Returns whether this Component can be focused.
     *
     * @return <code>true</code> if this Component is focusable;
     *         <code>false</code> otherwise.
     * @see #setFocusable
     * @since 1.4
     */
    public boolean isFocusable() {
        return true;
    }
}
