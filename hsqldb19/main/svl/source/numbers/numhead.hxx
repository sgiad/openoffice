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



#ifndef NF_NUMHEAD_HXX
#define NF_NUMHEAD_HXX

#include <tools/stream.hxx>

// -----------------------------------------------------------------------

		//	"Automatischer" Record-Header mit Groessenangabe

/* 						wird fuer SvNumberFormatter nicht gebraucht
class SvNumReadHeader
{
private:
	SvStream&	rStream;
	sal_uLong		nDataEnd;

public:
	SvNumReadHeader(SvStream& rNewStream);
	~SvNumReadHeader();

	sal_uLong	BytesLeft() const;
};

class SvNumWriteHeader
{
private:
	SvStream&	rStream;
	sal_uLong		nDataPos;
	sal_uLong		nDataSize;

public:
	SvNumWriteHeader(SvStream& rNewStream, sal_uLong nDefault = 0);
	~SvNumWriteHeader();
};

*/

		//	Header mit Groessenangaben fuer mehrere Objekte

class ImpSvNumMultipleReadHeader
{
private:
	SvStream&		rStream;
	char*			pBuf;
	SvMemoryStream*	pMemStream;
	sal_uLong			nEndPos;
	sal_uLong			nEntryEnd;

public:
	ImpSvNumMultipleReadHeader(SvStream& rNewStream);
	~ImpSvNumMultipleReadHeader();

	void	StartEntry();
	void	EndEntry();
	sal_uLong	BytesLeft() const;

	static void Skip( SvStream& );		// komplett ueberspringen
};

class ImpSvNumMultipleWriteHeader
{
private:
	SvStream&		rStream;
	SvMemoryStream	aMemStream;
	sal_uLong			nDataPos;
	sal_uInt32		nDataSize;
	sal_uLong			nEntryStart;

public:
	ImpSvNumMultipleWriteHeader(SvStream& rNewStream, sal_uLong nDefault = 0);
	~ImpSvNumMultipleWriteHeader();

	void	StartEntry();
	void	EndEntry();
};

#endif


