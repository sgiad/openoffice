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



package ifc.linguistic2;

import lib.MultiMethodTest;

import com.sun.star.beans.PropertyValue;
import com.sun.star.lang.Locale;
import com.sun.star.linguistic2.XMeaning;
import com.sun.star.linguistic2.XThesaurus;

/**
* Testing <code>com.sun.star.linguistic2.XThesaurus</code>
* interface methods:
* <ul>
*   <li><code>queryMeanings()</code></li>
* </ul> <p>
* @see com.sun.star.linguistic2.XThesaurus
*/
public class _XThesaurus extends MultiMethodTest {

    public XThesaurus oObj = null;

    /**
    * Test calls the method for one of supported language and checks
    * returned value. <p>
    * Has <b> OK </b> status if returned array is not empty
    * and no exceptions were thrown. <p>
    */
    public void _queryMeanings() {
        boolean res = true;
        try {
            XMeaning[] mean = oObj.queryMeanings(
                "survive",new Locale("en","US",""), new PropertyValue[0]);
            res = (mean.length > 0);
        } catch (com.sun.star.lang.IllegalArgumentException ex) {
            log.println("Exception while checking 'queryMeanings'");
            res = false;
            ex.printStackTrace(log);
        }
        tRes.tested("queryMeanings()",res);
    }


}  // finish class


