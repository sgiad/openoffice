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



PRJ=..$/..$/..$/..

PROJECTPCH=sd
PROJECTPCHSOURCE=$(PRJ)$/util$/sd
PRJNAME=sd
TARGET=slsview
ENABLE_EXCEPTIONS=TRUE
AUTOSEG=true
PRJINC=..$/..

IMGLST_SRS=$(SRS)$/$(TARGET).srs

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/util$/makefile.pmk

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =	\
	SlsResource.src

SLOFILES =      							\
	$(SLO)$/SlideSorterView.obj				\
	$(SLO)$/SlsButtonBar.obj				\
	$(SLO)$/SlsFontProvider.obj				\
	$(SLO)$/SlsFramePainter.obj				\
	$(SLO)$/SlsInsertAnimator.obj			\
	$(SLO)$/SlsInsertionIndicatorOverlay.obj\
	$(SLO)$/SlsLayeredDevice.obj			\
	$(SLO)$/SlsLayouter.obj					\
	$(SLO)$/SlsPageObjectLayouter.obj		\
	$(SLO)$/SlsPageObjectPainter.obj		\
	$(SLO)$/SlsTheme.obj					\
	$(SLO)$/SlsToolTip.obj					\
	$(SLO)$/SlsViewCacheContext.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

