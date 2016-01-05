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

PRJNAME=sc
TARGET=scslots
SVSDIINC=$(PRJ)$/source$/ui$/inc

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Files --------------------------------------------------------

.IF "$(L10N_framework)"==""
SDI1NAME=$(TARGET)
#SIDHRCNAME=SCSLOTS.HRC
SDI1EXPORT=scalc

SVSDI1DEPEND= \
        $(SOLARINCXDIR)$/sfx2/sfx.sdi \
        $(SOLARINCXDIR)$/sfx2/sfxitems.sdi \
        $(SOLARINCXDIR)$/svx/svx.sdi \
        $(SOLARINCXDIR)$/svx/svxitems.sdi \
        $(SOLARINCXDIR)$/svx/xoitems.sdi \
        scalc.sdi \
	app.sdi \
	auditsh.sdi \
	docsh.sdi \
	drawsh.sdi \
	drtxtob.sdi \
	drformsh.sdi \
	editsh.sdi \
	pivotsh.sdi \
	prevwsh.sdi \
	tabvwsh.sdi \
	formatsh.sdi\
	cellsh.sdi  \
	oleobjsh.sdi\
	chartsh.sdi \
	graphsh.sdi \
	mediash.sdi \
	pgbrksh.sdi \
	scslots.hrc \
	$(INC)$/sc.hrc 
.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk
