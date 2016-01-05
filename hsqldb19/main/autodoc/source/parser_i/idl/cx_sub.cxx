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

#include <precomp.h>
#include <s2_luidl/cx_sub.hxx>



// NOT FULLY DECLARED SERVICES
#include <s2_luidl/tokrecv.hxx>
#include <../../parser/inc/tokens/parseinc.hxx>
#include <x_parse2.hxx>
#include <s2_luidl/tk_const.hxx>



namespace csi
{
namespace uidl
{

bool
Cx_Base::PassNewToken()
{
	if (pNewToken)
	{
		rReceiver.Receive(*pNewToken.Release());
		return true;
	}
	return false;
}

TkpContext &
Cx_Base::FollowUpContext()
{
	csv_assert(pFollowUpContext != 0);
	return *pFollowUpContext;
}

void
Context_MLComment::ReadCharChain( CharacterSource &	io_rText )
{
	char cNext = NULCH;

	do {
	    do {
	        cNext = jumpTo(io_rText,'*','\n');
	        if (cNext == '\n')
            {
                Receiver().Increment_CurLine();
                cNext = io_rText.MoveOn();
            }
	        else if (cNext == NULCH)
    			throw X_AutodocParser(X_AutodocParser::x_UnexpectedEOF);
        } while (cNext != '*');

		cNext = jumpOver(io_rText,'*');
		if (cNext == NULCH)
			throw X_AutodocParser(X_AutodocParser::x_UnexpectedEOF);
	} while (cNext != '/');
	io_rText.MoveOn();
	io_rText.CutToken();
	SetToken(0);
}

void
Context_SLComment::ReadCharChain( CharacterSource &	io_rText )
{
	jumpToEol(io_rText);
	if (io_rText.CurChar() != NULCH)
		jumpOverEol(io_rText);
	io_rText.CutToken();
	SetToken(0);

    Receiver().Increment_CurLine();
}

void
Context_Praeprocessor::ReadCharChain( CharacterSource &	io_rText )
{
	jumpToEol(io_rText);
	if (io_rText.CurChar() != NULCH)
		jumpOverEol(io_rText);
	io_rText.CutToken();
	SetToken(0);

    Receiver().Increment_CurLine();
}

void
Context_Assignment::ReadCharChain( CharacterSource &	io_rText )
{
    // KORR_FUTURE
    // How to handle new lines within this, so he y get realised by
    //  ParserInfo?

	char cNext = NULCH;
	do {
		if ( (cNext = jumpTo(io_rText,';',',','"','}')) == NULCH )
			throw X_AutodocParser(X_AutodocParser::x_UnexpectedEOF);
		if (cNext == '"')
		{
			cNext = io_rText.MoveOn();
			while (cNext != '"')
			{
				if ( (cNext = jumpTo(io_rText,'"','\\')) == NULCH )
					throw X_AutodocParser(X_AutodocParser::x_UnexpectedEOF);
				if (cNext == '\\')
					io_rText.MoveOn();
			}
			cNext = io_rText.MoveOn();
		}	// endif (cNext == '"')
	} while (cNext != ';' AND cNext != ',' AND cNext != '}');

	if (cNext == ',' OR cNext == ';')
		io_rText.MoveOn();
	SetToken(new TokAssignment(io_rText.CutToken()));
}


}   // namespace uidl
}   // namespace csi
