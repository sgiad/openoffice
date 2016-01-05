#**************************************************************
#  
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#  
#    http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing,
#  software distributed under the License is distributed on an
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
#  specific language governing permissions and limitations
#  under the License.
#  
#**************************************************************



PRJ=..$/..

PRJNAME=codemaker
TARGET=cppumaker
TARGETTYPE=CUI
LIBTARGET=NO

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------
.INCLUDE : settings.mk
.INCLUDE : $(PRJ)$/codemaker.pmk

# --- Files --------------------------------------------------------

.IF "$(GUI)"=="WNT"
.IF "$(COM)"!="GCC"
CFLAGSNOOPT+=-Ob0
.ENDIF
.ENDIF

OBJFILES=   $(OBJ)$/cppumaker.obj	\
            $(OBJ)$/cppuoptions.obj \
            $(OBJ)$/cpputype.obj \
            $(OBJ)$/dumputils.obj \
            $(OBJ)$/includes.obj

NOOPTFILES= \
            $(OBJ)$/cpputype.obj

APP1TARGET= $(TARGET)
APP1RPATH=SDK
APP1OBJS=   $(OBJFILES)

APP1DEPN= $(OUT)$/lib$/$(CODEMAKERLIBDEPN) $(OUT)$/lib$/$(COMMONCPPLIBDEPN)
APP1STDLIBS= $(SALLIB) $(SALHELPERLIB) $(REGLIB) $(CODEMAKERLIBST) $(COMMONCPPLIBST)

.INCLUDE :  target.mk
