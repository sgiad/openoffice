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


#ifndef _SFXECODE_HXX
#define _SFXECODE_HXX

#include <tools/errcode.hxx>

#define ERRCODE_SFX_NOSTDTEMPLATE			(ERRCODE_AREA_SFX|ERRCODE_CLASS_PATH|1)
#define ERRCODE_SFX_NOTATEMPLATE			(ERRCODE_AREA_SFX|ERRCODE_CLASS_FORMAT|2)
#define ERRCODE_SFX_GENERAL					(ERRCODE_AREA_SFX|ERRCODE_CLASS_GENERAL|3)
#define ERRCODE_SFX_DOLOADFAILED			(ERRCODE_AREA_SFX|ERRCODE_CLASS_READ|4)
#define ERRCODE_SFX_DOSAVECOMPLETEDFAILED	(ERRCODE_AREA_SFX|ERRCODE_CLASS_WRITE|5)
#define ERRCODE_SFX_COMMITFAILED			(ERRCODE_AREA_SFX|ERRCODE_CLASS_WRITE|6)
#define ERRCODE_SFX_HANDSOFFFAILED			(ERRCODE_AREA_SFX|ERRCODE_CLASS_GENERAL|7)
#define ERRCODE_SFX_DOINITNEWFAILED			(ERRCODE_AREA_SFX|ERRCODE_CLASS_CREATE|8)
#define ERRCODE_SFX_CANTREADDOCINFO			(ERRCODE_AREA_SFX|ERRCODE_CLASS_FORMAT|9)
#define ERRCODE_SFX_ALREADYOPEN				(ERRCODE_AREA_SFX|ERRCODE_CLASS_ALREADYEXISTS|10)
#define ERRCODE_SFX_WRONGPASSWORD			(ERRCODE_AREA_SFX|ERRCODE_CLASS_READ|11)
#define ERRCODE_SFX_DOCUMENTREADONLY		(ERRCODE_AREA_SFX|ERRCODE_CLASS_WRITE|12)
#define ERRCODE_SFX_OLEGENERAL				(ERRCODE_AREA_SFX|ERRCODE_CLASS_NONE|14)
#define ERRCODE_SFXMSG_STYLEREPLACE			(ERRCODE_WARNING_MASK|ERRCODE_AREA_SFX|ERRCODE_CLASS_NONE|13)
#define ERRCODE_SFX_TEMPLATENOTFOUND		(ERRCODE_AREA_SFX|ERRCODE_CLASS_NOTEXISTS|15)
#define ERRCODE_SFX_ISRELATIVE				(ERRCODE_WARNING_MASK|ERRCODE_AREA_SFX|ERRCODE_CLASS_NOTEXISTS|16)
#define ERRCODE_SFX_FORCEDOCLOAD			(ERRCODE_WARNING_MASK|ERRCODE_AREA_SFX|ERRCODE_CLASS_NONE|17)

#define ERRCODE_SFX_CANTFINDORIGINAL		(ERRCODE_AREA_SFX|ERRCODE_CLASS_GENERAL|19)
#define ERRCODE_SFX_RESTART					(ERRCODE_AREA_SFX|ERRCODE_CLASS_GENERAL|20)
#define ERRCODE_SFX_CANTCREATECONTENT		(ERRCODE_AREA_SFX|ERRCODE_CLASS_CREATE|21)
#define ERRCODE_SFX_CANTCREATELINK			(ERRCODE_AREA_SFX|ERRCODE_CLASS_CREATE|22)
#define ERRCODE_SFX_WRONGBMKFORMAT			(ERRCODE_AREA_SFX|ERRCODE_CLASS_FORMAT|23)
#define ERRCODE_SFX_WRONGICONFILE			(ERRCODE_AREA_SFX|ERRCODE_CLASS_FORMAT|24)
#define ERRCODE_SFX_CANTDELICONFILE			(ERRCODE_AREA_SFX|ERRCODE_CLASS_ACCESS|25)
#define ERRCODE_SFX_CANTWRITEICONFILE		(ERRCODE_AREA_SFX|ERRCODE_CLASS_ACCESS|26)
#define ERRCODE_SFX_CANTRENAMECONTENT		(ERRCODE_AREA_SFX|ERRCODE_CLASS_ACCESS|27)
#define ERRCODE_SFX_INVALIDBMKPATH			(ERRCODE_AREA_SFX|ERRCODE_CLASS_PATH|28)
#define ERRCODE_SFX_CANTWRITEURLCFGFILE		(ERRCODE_AREA_SFX|ERRCODE_CLASS_ACCESS|29)
#define ERRCODE_SFX_WRONGURLCFGFORMAT		(ERRCODE_AREA_SFX|ERRCODE_CLASS_FORMAT|30)
#define ERRCODE_SFX_NODOCUMENT				(ERRCODE_AREA_SFX|ERRCODE_CLASS_NOTEXISTS|31)
#define ERRCODE_SFX_INVALIDLINK				(ERRCODE_AREA_SFX|ERRCODE_CLASS_NOTEXISTS|32)
#define ERRCODE_SFX_INVALIDTRASHPATH		(ERRCODE_AREA_SFX|ERRCODE_CLASS_PATH|33)
#define ERRCODE_SFX_NOTRESTORABLE			(ERRCODE_AREA_SFX|ERRCODE_CLASS_CREATE|34)
#define ERRCODE_SFX_NOTRASH					(ERRCODE_AREA_SFX|ERRCODE_CLASS_NOTEXISTS|35)
#define ERRCODE_SFX_INVALIDSYNTAX			(ERRCODE_AREA_SFX|ERRCODE_CLASS_PATH|36)
#define ERRCODE_SFX_CANTCREATEFOLDER		(ERRCODE_AREA_SFX|ERRCODE_CLASS_CREATE|37)
#define ERRCODE_SFX_CANTRENAMEFOLDER		(ERRCODE_AREA_SFX|ERRCODE_CLASS_PATH|38)
#define ERRCODE_SFX_WRONG_CDF_FORMAT		(ERRCODE_AREA_SFX| ERRCODE_CLASS_READ | 39)
#define ERRCODE_SFX_EMPTY_SERVER			(ERRCODE_AREA_SFX|ERRCODE_CLASS_NONE|40)
#define ERRCODE_SFX_NO_ABOBOX				(ERRCODE_AREA_SFX| ERRCODE_CLASS_READ | 41)
#define ERRCODE_SFX_CANTGETPASSWD			(ERRCODE_AREA_SFX| ERRCODE_CLASS_READ | 42)
#define ERRCODE_SFX_TARGETFILECORRUPTED		(ERRCODE_AREA_SFX| ERRCODE_CLASS_READ | 43)
#define ERRCODE_SFX_NOMOREDOCUMENTSALLOWED  (ERRCODE_WARNING_MASK | ERRCODE_AREA_SFX | ERRCODE_CLASS_NONE | 44)
#define ERRCODE_SFX_NOFILTER				(ERRCODE_AREA_SFX|ERRCODE_CLASS_NOTEXISTS|45)
#define ERRCODE_SFX_FORCEQUIET				(ERRCODE_WARNING_MASK|ERRCODE_AREA_SFX|ERRCODE_CLASS_NONE|47)
#define ERRCODE_SFX_CONSULTUSER				(ERRCODE_WARNING_MASK|ERRCODE_AREA_SFX|ERRCODE_CLASS_NONE|48)
#define ERRCODE_SFX_NEVERCHECKCONTENT		(ERRCODE_AREA_SFX|ERRCODE_CLASS_NONE|49)
#define ERRCODE_SFX_CANTCREATEBACKUP        (ERRCODE_AREA_SFX | ERRCODE_CLASS_CREATE | 50)
#define ERRCODE_SFX_MACROS_SUPPORT_DISABLED (ERRCODE_WARNING_MASK | ERRCODE_AREA_SFX | ERRCODE_CLASS_NONE | 51)
#define ERRCODE_SFX_DOCUMENT_MACRO_DISABLED (ERRCODE_WARNING_MASK | ERRCODE_AREA_SFX | ERRCODE_CLASS_NONE | 52)
#define ERRCODE_SFX_BROKENSIGNATURE         (ERRCODE_WARNING_MASK | ERRCODE_AREA_SFX | ERRCODE_CLASS_NONE | 53)
#define ERRCODE_SFX_SHARED_NOPASSWORDCHANGE (ERRCODE_WARNING_MASK | ERRCODE_AREA_SFX | ERRCODE_CLASS_NONE | 54)
#define ERRCODE_SFX_INCOMPLETE_ENCRYPTION    (ERRCODE_WARNING_MASK | ERRCODE_AREA_SFX | ERRCODE_CLASS_NONE | 55)



//Dies und das
#define ERRCTX_ERROR					21
#define ERRCTX_WARNING					22

//Documentkontexte
#define ERRCTX_SFX_LOADTEMPLATE			1
#define ERRCTX_SFX_SAVEDOC				2
#define ERRCTX_SFX_SAVEASDOC			3
#define ERRCTX_SFX_DOCINFO				4
#define ERRCTX_SFX_DOCTEMPLATE			5
#define ERRCTX_SFX_MOVEORCOPYCONTENTS	6

//Appkontexte
#define ERRCTX_SFX_DOCMANAGER			50
#define ERRCTX_SFX_OPENDOC				51
#define ERRCTX_SFX_NEWDOCDIRECT			52
#define ERRCTX_SFX_NEWDOC				53

//Organizerkontexte
#define ERRCTX_SFX_CREATEOBJSH			70

//BASIC-Kontexte
#define ERRCTX_SFX_LOADBASIC			80

//Addressbook contexts
#define ERRCTX_SFX_SEARCHADDRESS		90

#endif // #ifndef _SFXECODE_HXX


