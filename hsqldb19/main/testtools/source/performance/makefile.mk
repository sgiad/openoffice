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

PRJNAME=testtools
TARGET=performancetest
ENABLE_EXCEPTIONS=TRUE
USE_DEFFILE=TRUE
LIBTARGET=NO

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# ------------------------------------------------------------------

LIB1TARGET=$(SLB)$/perftest.lib
LIB1OBJFILES= \
		$(SLO)$/ubtest.obj

SHL1TARGET = perftest.uno

SHL1VERSIONMAP = $(SOLARENV)$/src$/component.map

SHL1STDLIBS= \
		$(CPPULIB)		\
		$(CPPUHELPERLIB)	\
		$(SALLIB)

SHL1LIBS=	$(LIB1TARGET)
SHL1DEF=	$(MISC)$/$(SHL1TARGET).def
DEF1NAME=	$(SHL1TARGET)

# ---- test object ----

LIB2TARGET=$(SLB)$/perfobj.lib
LIB2OBJFILES= \
		$(SLO)$/ubobject.obj

SHL2TARGET = perfobj.uno

SHL2VERSIONMAP = $(SOLARENV)$/src$/component.map

SHL2STDLIBS= \
		$(CPPULIB)		\
		$(CPPUHELPERLIB)	\
		$(SALLIB)

SHL2LIBS=	$(LIB2TARGET)
SHL2DEF=	$(MISC)$/$(SHL2TARGET).def
DEF2NAME=	$(SHL2TARGET)

# ---- pseudo uno bridge ----

LIB3TARGET=$(SLB)$/pseudo.lib
LIB3OBJFILES= \
		$(SLO)$/pseudo.obj

SHL3TARGET=pseudo_uno_uno

SHL3VERSIONMAP = pseudo_uno_uno.map

SHL3STDLIBS= \
		$(CPPULIB)		\
		$(SALLIB)

SHL3LIBS=	$(LIB3TARGET)
SHL3DEF=	$(MISC)$/$(SHL3TARGET).def
DEF3NAME=	$(SHL3TARGET)

# --- Targets ------------------------------------------------------

.INCLUDE :	target.mk
