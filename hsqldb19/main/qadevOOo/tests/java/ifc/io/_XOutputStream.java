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



package ifc.io;

import lib.MultiMethodTest;
import lib.Status;
import lib.StatusException;

import com.sun.star.io.XInputStream;
import com.sun.star.io.XOutputStream;

/**
* Testing <code>com.sun.star.io.XOutputStream</code>
* interface methods:
* <ul>
*   <li><code>writeBytes()</code></li>
*   <li><code>flush()</code></li>
*   <li><code>closeOutput()</code></li>
* </ul> <p>
* This test needs the following object relations :
* <ul>
*  <li> <code>'ByteData'</code> : Data that is written on the stream.
*  </li>
*  <li> <code>'XOutputStream.StreamChecker'</code> : <code>
*    _XOutputStream.StreamChecker</code> interface implementation
*    which can reset streams and return input stream for check if the
*    data was successfully written.</li>
* <ul> <p>
* After test completion object environment has to be recreated.
* @see com.sun.star.io.XOutputStream
*/
public class _XOutputStream extends MultiMethodTest {

    public XOutputStream oObj = null;
    StreamChecker checker = null;
    byte[] data = null;

    public static interface StreamChecker {
        public XInputStream getInStream();
        public void resetStreams();
    }

    protected void before() {
        checker = (StreamChecker)
            tEnv.getObjRelation("XOutputStream.StreamChecker");
        if (checker == null) throw
            new StatusException(Status.failed(
                "Couldn't get relation 'XOutputStream.StreamChecker'"));

        data = (byte[])tEnv.getObjRelation("ByteData");
        if (data == null) throw
            new StatusException(Status.failed(
                "Couldn't get relation 'ByteData'"));
    }
    /**
    * Test writes data to stream. <p>
    * Has <b> OK </b> status if the method successfully returns
    * and no exceptions were thrown. <p>
    */
    public void _writeBytes() {
        boolean res = true;
        try {
            oObj.writeBytes(data);
         } catch (com.sun.star.io.IOException e) {
            e.printStackTrace(log) ;
            res = false;
        }

        XInputStream xInStream = checker.getInStream();
        byte[][] readData = new byte[1][data.length];
        try {
            xInStream.readBytes(readData, data.length);
        } catch(com.sun.star.io.IOException e) {
            log.println("Couldn't read data:" + e);
            res = false;
        }

        for(int i = 0; i < readData[0].length; i++) {
            log.println("Expected: "+data[i]+", actual is "+readData[0][i]);
            res &= readData[0][i] == data[i];
        }

        tRes.tested("writeBytes()", res);
    }

    /**
    * Test flushes out data from stream. <p>
    * Has <b> OK </b> status if the method successfully returns
    * and no exceptions were thrown. <p>
    * The following method tests are to be completed successfully before :
    * <ul>
    *  <li> <code> writeBytes() </code></li>
    * </ul>
    */
    public void _flush() {
        requiredMethod("writeBytes()");

        boolean res;
        try {
            oObj.flush();
            res = true;
        } catch (com.sun.star.io.IOException e) {
            e.printStackTrace(log) ;
            res = false;
        }

        tRes.tested("flush()", res);
    }

    /**
    * Test calls the method. <p>
    * Has <b> OK </b> status if the method successfully returns
    * and no exceptions were thrown. <p>
    * The following method tests are to be completed successfully before :
    * <ul>
    *  <li> <code> writeBytes() </code></li>
    * </ul>
    * The following method tests are to be executed before :
    * <ul>
    *  <li><code> flush() </code></li>
    * </ul>
    */
    public void _closeOutput() {
        requiredMethod("writeBytes()");
        executeMethod("flush()");

        boolean res;
        try {
            oObj.closeOutput();
            res = true;
        } catch (com.sun.star.io.IOException e) {
            e.printStackTrace(log);
            res = false;
        }

        log.println("This method is called in main module");

        tRes.tested("closeOutput()", res);
    }

    /**
    * Forces object environment recreation.
    */
    public void after() {
        this.disposeEnvironment() ;
    }
}

