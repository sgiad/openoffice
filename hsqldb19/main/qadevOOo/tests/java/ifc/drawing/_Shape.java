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



package ifc.drawing;

import lib.MultiPropertyTest;

import com.sun.star.style.XStyle;

/**
* Testing <code>com.sun.star.drawing.Shape</code>
* service properties :
* <ul>
*  <li><code> ZOrder</code></li>
*  <li><code> LayerID</code></li>
*  <li><code> LayerName</code></li>
*  <li><code> Printable</code></li>
*  <li><code> MoveProtect</code></li>
*  <li><code> Name</code></li>
*  <li><code> SizeProtect</code></li>
*  <li><code> Style</code></li>
*  <li><code> Transformation</code></li>
* </ul> <p>
* This test needs the following object relations :
* <ul>
*  <li> <code>'Style1', 'Style2'</code>
*   (of type <code>com.sun.star.style.XStyle</code>):
*    relations used to change property 'Style'</li>
* <ul> <p>
* Properties testing is automated by <code>lib.MultiPropertyTest</code>.
* @see com.sun.star.drawing.Shape
*/
public class _Shape extends MultiPropertyTest {

    XStyle style1 = null;
    XStyle style2 = null;

    /**
     * Custom tester which switches between two styles.
     */
    protected PropertyTester StyleTester = new PropertyTester() {
        protected Object getNewValue(String propName, Object oldValue)
                throws java.lang.IllegalArgumentException {
            if (util.ValueComparer.equalValue(oldValue,style1))
                return style2; else
                return style1;
        }
    } ;

    /**
     * Custom tester for 'LayerName' property which switches two
     * Strings ('layout' and 'controls').
     */
    protected PropertyTester StringTester = new PropertyTester() {
        protected Object getNewValue(String propName, Object oldValue)
                throws java.lang.IllegalArgumentException {
            if (util.ValueComparer.equalValue(oldValue,"layout"))
                return "controls"; else
                return "layout";
        }
    } ;

    /**
     * Tested with custom StyleTester which switches between two
     * styles.
     */
    public void _Style() {
        log.println("Testing with custom Property tester") ;
        style1 = (XStyle) tEnv.getObjRelation("Style1");
        style2 = (XStyle) tEnv.getObjRelation("Style2");
        testProperty("Style", StyleTester) ;
    }

    /**
     * Tested with custom StringTester which switches two
     * Strings ('layout' and 'controls')
     */
    public void _LayerName() {
        if (tEnv.getTestCase().getObjectName().equals("SwXShape")) {
            log.println("There is only one Layer for SwXShape");
            log.println("Therefore this property can't be changed");
            tRes.tested("LayerName",true);
        } else if (tEnv.getTestCase().getObjectName().equals("ScShapeObj")) {
            log.println("There is only one Layer for ScShapeObj");
            log.println("Therefore this property can't be changed");
            tRes.tested("LayerName",true); 
        } else if (tEnv.getTestCase().getObjectName().equals("ScAnnotationShapeObj")) {
            log.println("There is only one Layer for ScAnnotationShapeObj");
            log.println("Therefore this property can't be changed");
            String aName = null;
            try {
                aName = (String) oObj.getPropertyValue ("LayerName");
                log.println("LayerName: '"+aName+"'");
            } catch (Exception e) {
                e.printStackTrace (log);
            }
            tRes.tested("LayerName",aName != null);             
        } else {
            log.println("Testing with custom Property tester") ;
            testProperty("LayerName", StringTester) ;
        }
    }

    public void _ZOrder() {
        if (tEnv.getTestCase().getObjectName().equals("ScAnnotationShapeObj")) {
            log.println("There is only one Layer for ScAnnotationShapeObj");
            log.println("Therefore this property can't be changed");
            tRes.tested("ZOrder",true);        
        } else {
            testProperty("ZOrder", new Integer(0), new Integer(1));
        }
    }
    
    public void _LayerID() {
        if (tEnv.getTestCase().getObjectName().equals("ScAnnotationShapeObj")) {
            log.println("There is only one Layer for ScAnnotationShapeObj");
            log.println("Therefore this property can't be changed");
            Short aID = null;
            try {
                aID = (Short) oObj.getPropertyValue ("LayerID");
                log.println("LayerID: '"+aID.intValue ()+"'");
            } catch (Exception e) {
                e.printStackTrace (log);
            }
            tRes.tested("LayerID",aID != null);             
        } else {
            log.println("Testing with custom Property tester") ;
            testProperty("LayerID");
        }
    }


}

