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



package org.openoffice.xmerge.converter.xml.sxw.wordsmith;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.*;
import java.io.UnsupportedEncodingException;
import java.util.List;
import java.util.ArrayList;
import java.util.Vector;

import org.openoffice.xmerge.converter.palm.*;

/**
 *  This class is used by {@link
 *  org.openoffice.xmerge.converter.xml.sxw.wordsmith.DocumentDeserializerImpl
 *  DocumentDeserializerImpl} to encode the WordSmith format.
 *
 *  @author   David Proulx
 */

// DJP: replace 4096 w/ a defined constant

final class WSEncoder {

    /* DJP: These should probably go somewhere else! */
    /** Constant for uncompressed version. */
    public static final short UNCOMPRESSED = 1;

    /** Constant for compressed version. */
    public static final short COMPRESSED = 2;

    /** Constant used for spare fields. */
    public static final int SPARE = 0;

    /* WordSmith Header information. */
    private short version;
    private int textLen;
    private short maxRecSize;
    private int textRecCount = 0;


    /* WordSmith document elements. */
    WseHeader header = null;
    WseFontTable ft = null;
    WseColorTable ct = null;
    private Vector elements;  // paragraphs & text runs

    /* Totals for the WordSmith document. */
    int nrParagraphs = 0;
    int nrAtoms = 0;
    int nrChars = 0;


    /**
     *  Default constructor creates a header and
     *  a text buffer for holding all the text in
     *  the WordSmith database.
     */
    WSEncoder() {
        version = 1;
        textLen = 0;
        maxRecSize = 4096;
        elements = new Vector();
    }


    /**
     *  This method adds a new element to the WordSmith document.
     *
     *  @param  elem  WordSmith document element to add
     */
    void addElement(Wse elem) {
        if (elem.getClass() == WseHeader.class)
            header = (WseHeader)elem;
        else if (elem.getClass() == WseFontTable.class)
            ft = (WseFontTable)elem;
        else if (elem.getClass() == WseColorTable.class)
            ct = (WseColorTable)elem;
        else
            elements.addElement(elem);
    }


    /**
     *  This method encodes the information given to
     *  an array of palm Records in the WordSmith database format.
     *
     *  @return  <code>Record</code> array holding WordSmith contents.
     *
     *  @throws  IOException  If any I/O error occurs.
     */
    Record[] getRecords() throws IOException {

        Vector allRecs = new Vector();
        int nElements = elements.size();
        
        // Count up the number of paragraphs, atoms, and characters.
        int currElement = 0;
        while (currElement < nElements) {
            Wse e = (Wse)elements.elementAt(currElement++);
            if (e.getClass() == WsePara.class) 
                nrParagraphs++;
            if (e.getClass() == WseTextRun.class) {
                nrAtoms++;
                nrChars += ((WseTextRun)e).getText().length();
            }
        }

        byte[] currRec = new byte[4096];
        int currRecLen = 0;

        // This code assumes that the WordSmith header, font table,
        // and color table total less than 4096 bytes.
        header = new WseHeader(nrParagraphs, nrAtoms, nrChars, ft, ct);
        System.arraycopy(header.getBytes(), 0,
                         currRec, currRecLen, header.getByteCount());
        currRecLen += header.getByteCount();

        if (ft != null) {
            System.arraycopy(ft.getBytes(), 0, currRec, currRecLen, 
                             ft.getByteCount());
            currRecLen += ft.getByteCount();
        }
        if (ct != null) {
            System.arraycopy(ct.getBytes(), 0, currRec, currRecLen, 
                             ct.getByteCount());
            currRecLen += ct.getByteCount();
        }

        currElement = 0;
        while (currElement < nElements) {
            Wse e = (Wse)elements.elementAt(currElement++);
            int length = e.getByteCount();
            if ((length + currRecLen) <= 4096) {
                System.arraycopy(e.getBytes(), 0, currRec, currRecLen, length);
                currRecLen += length;
        } else {
                // Copy in enough to get to full size, then create a 
                // new Record and add it to the Vector.
                int firstPartLen = 4096 - currRecLen;
                System.arraycopy(e.getBytes(), 0, currRec, currRecLen, 
                                 firstPartLen);
                Record r = new Record(currRec);
                allRecs.addElement(r);

                // Put the remainder at the beginning of the next record
                currRecLen = 0;
                System.arraycopy(e.getBytes(), firstPartLen, currRec,
                                 currRecLen, length - firstPartLen);
                currRecLen += length - firstPartLen;
            }
        }

        // Processed all the elements.  Write out any remaining partial record.
        if (currRecLen > 0) {
            byte[] partial = new byte[currRecLen];
            System.arraycopy(currRec, 0, partial, 0, currRecLen);
            Record rr = new Record(partial);
            allRecs.addElement(rr);
        }


        // Record 0 is the WordSmith header.  Do it last since it
        // contains totals for the entire document.  It goes 
        // before everything else.
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);
        dos.writeShort(version);
        dos.writeShort(0);
        dos.writeInt(textLen);
        dos.writeShort(allRecs.size());
        dos.writeShort(maxRecSize);
        dos.writeInt(0);
        allRecs.insertElementAt(new Record(bos.toByteArray()), 0);

        // Convert Vector of Records to an array and return it.
        int nRecs = allRecs.size();
        Record recs[] = new Record[nRecs];
        for (int i = 0; i < nRecs; i++)
        recs[i] = (Record)allRecs.elementAt(i);
        return recs;
    }

}

