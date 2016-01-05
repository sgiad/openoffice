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



package mod._lng;

import java.io.PrintWriter;

import lib.StatusException;
import lib.TestCase;
import lib.TestEnvironment;
import lib.TestParameters;

import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.uno.XInterface;

/**
 * Test for object which is represented by service
 * <code>com.sun.star.linguistic2.LinguProperties</code>. <p>
 *
 * Object implements the following interfaces :
 * <ul>
 *  <li> <code>com::sun::star::lang::XComponent</code></li>
 *  <li> <code>com::sun::star::lang::XServiceInfo</code></li>
 *  <li> <code>com::sun::star::beans::XFastPropertySet</code></li>
 *  <li> <code>com::sun::star::beans::XPropertySet</code></li>
 *  <li> <code>com::sun::star::linguistic2::LinguProperties</code></li>
 * </ul> <p>
 *
 * This object test <b> is NOT </b> designed to be run in several
 * threads concurently.
 *
 * @see com.sun.star.lang.XComponent
 * @see com.sun.star.lang.XServiceInfo
 * @see com.sun.star.beans.XFastPropertySet
 * @see com.sun.star.beans.XPropertySet
 * @see com.sun.star.linguistic2.LinguProperties
 * @see ifc.lang._XComponent
 * @see ifc.lang._XServiceInfo
 * @see ifc.beans._XFastPropertySet
 * @see ifc.beans._XPropertySet
 * @see ifc.linguistic2._LinguProperties
 */
public class LinguProps extends TestCase {

    /**
     * Creating a Testenvironment for the interfaces to be tested.
     * Creates an instance of the service
     * <code>com.sun.star.linguistic2.LinguProperties</code>.
     */
    public synchronized TestEnvironment createTestEnvironment
            ( TestParameters Param, PrintWriter log )
            throws StatusException {

        XMultiServiceFactory xMSF = (XMultiServiceFactory)Param.getMSF();
        XInterface oObj = null;

        try {
            oObj = (XInterface)xMSF.createInstance
                ("com.sun.star.linguistic2.LinguProperties");
        } catch (com.sun.star.uno.Exception e) {
            e.printStackTrace(log);
            throw new StatusException("Unexpected exception", e);
        }

        String Iname = util.utils.getImplName(oObj);
        log.println("Implementation Name: "+Iname);
        TestEnvironment tEnv = new TestEnvironment(oObj);

        return tEnv;
    }


}    // finish class LinguProps

