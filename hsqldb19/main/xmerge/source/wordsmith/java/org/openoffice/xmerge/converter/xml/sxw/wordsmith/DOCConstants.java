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

/**
 *  Constants used for encoding and decoding the WordSmith format.
 *
 *  @author   Herbie Ong, David Proulx
 */
interface DOCConstants {

    /** Constant for uncompressed version. */
    public static final short UNCOMPRESSED = 1;

    /** Constant for compressed version. */
    public static final short COMPRESSED = 2;

    /** Constant used for spare fields. */
    public static final int SPARE = 0;

    /** WordSmith record size. */
    public static final short TEXT_RECORD_SIZE = 4096;

    /** Constant for encoding scheme. */
    public static final String ENCODING = "8859_1";

    /** Constant for TAB character. */
    public final static char TAB_CHAR = '\t';

    /** Constant for EOL character. */
    public final static char EOL_CHAR = '\n';

    /** Constant for SPACE character. */
    public final static char SPACE_CHAR = ' ';
}

