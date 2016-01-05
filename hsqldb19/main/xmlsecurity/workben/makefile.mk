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



PRJ=..

PRJNAME=xmlsecurity
TARGET=signaturetest
LIBTARGET=NO
TARGETTYPE=GUI

# --- Settings -----------------------------------------------------

.INCLUDE :	settings.mk
.INCLUDE :	$(PRJ)$/util$/target.pmk


# --- Files --------------------------------------------------------

OBJFILES=		$(OBJ)$/signaturetest.obj
EXCEPTIONSFILES=$(OBJ)$/signaturetest.obj

APP1NOSAL=		TRUE
APP1TARGET= 	$(TARGET)
APP1OBJS=		$(OBJFILES)

APP1STDLIBS=	$(CPPULIB)			\
				$(CPPUHELPERLIB)	\
				$(COMPHELPERLIB)	\
				$(UCBHELPERLIB)	    \
				$(UNOTOOLSLIB)	    \
				$(VCLLIB)			\
				$(TOOLSLIB) 		\
				$(SVTOOLLIB) 		\
				$(SALLIB)			\
				$(VOSLIB)			\
				$(SOTLIB)			\
				$(VCLLIB)			\
				$(SFXLIB)			\
				$(XMLOFFLIB)		\
				$(SVXLIB)



# --- Targets ------------------------------------------------------

.INCLUDE :	target.mk

