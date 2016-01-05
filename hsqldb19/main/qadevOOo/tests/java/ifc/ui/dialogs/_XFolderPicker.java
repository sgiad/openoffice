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



package ifc.ui.dialogs;

import lib.MultiMethodTest;

import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.ui.dialogs.XFolderPicker;

/**
* Testing <code>com.sun.star.ui.XFolderPicker</code>
* interface methods :
* <ul>
*  <li><code> setDisplayDirectory()</code></li>
*  <li><code> getDisplayDirectory()</code></li>
* </ul> <p>
* Test is <b> NOT </b> multithread compilant. <p>
* @see com.sun.star.ui.XFolderPicker
*/
public class _XFolderPicker extends MultiMethodTest {

    public XFolderPicker oObj = null;
    private String dir = null ;

    /**
    * Sets the current directory to SOffice temp dir. <p>
    * Has <b>OK</b> status if no exceptions occurred.
    */
    public void _setDisplayDirectory() {
        boolean result = true ;
        dir = util.utils.getOfficeTemp((XMultiServiceFactory)tParam.getMSF()) ;

        log.println("Trying to set dir '" + dir + "'") ;
        try {
            oObj.setDisplayDirectory(dir) ;
        } catch (com.sun.star.lang.IllegalArgumentException e) {
            log.println("Directory '" + dir + "' not found :" + e) ;
            result = false ;
        }

        tRes.tested("setDisplayDirectory()", result) ;
    }

    /**
    * Gets the current directory. <p>
    * Has <b>OK</b> status if get value is equal to set value
    * passed to <code>setDisplayDirectory</code> <p>
    * The following method tests are to be completed successfully before :
    * <ul>
    *  <li> <code> setDisplayDirectory </code>  </li>
    * </ul>
    */
    public void _getDisplayDirectory() {
        requiredMethod("setDisplayDirectory()") ;

        String gDir = oObj.getDisplayDirectory() ;

        log.println("Get dir '" + gDir + "'") ;

        tRes.tested("getDisplayDirectory()", dir.equals(gDir)) ;
    }

    /**
    * Gets the directory chosen by the user. <p>
    * Has <b>OK</b> status if get value is not NULL <p>
    */
    public void _getDirectory() {

        String gDir = oObj.getDirectory() ;

        log.println("Get dir '" + gDir + "'") ;

        tRes.tested("getDirectory()", gDir != null) ;
    }

    /**
    * Sets the Description for the dialog. <p>
    * Has <b>OK</b> status if no error occurs <p>
    */
    public void _setDescription() {

        oObj.setDescription("XFolderPicker") ;
        //to visually check if the method works
        //oObj.execute();
        tRes.tested("setDescription()", true) ;
    }

}


