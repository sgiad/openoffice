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


#ifndef RPTUI_COLORCHANGER_HXX
#define RPTUI_COLORCHANGER_HXX

namespace rptui
{
	//=====================================================================
	//= ColorChanger
	//=====================================================================
	class ColorChanger
	{
	protected:
		OutputDevice*	m_pDev;

	public:
		ColorChanger( OutputDevice* _pDev, const Color& _rNewLineColor)
			:m_pDev( _pDev )
		{
			m_pDev->Push( PUSH_LINECOLOR );
			m_pDev->SetLineColor( _rNewLineColor );
		}
		ColorChanger( OutputDevice* _pDev, const Color& _rNewLineColor, const Color& _rNewFillColor )
			:m_pDev( _pDev )
		{
			m_pDev->Push( PUSH_LINECOLOR | PUSH_FILLCOLOR );
			m_pDev->SetLineColor( _rNewLineColor );
			m_pDev->SetFillColor( _rNewFillColor );
		}
		ColorChanger( OutputDevice* _pDev, const Color& _rNewLineColor, const Color& _rNewFillColor, const Color& _rNewTextColor )
			:m_pDev( _pDev )
		{
			m_pDev->Push( PUSH_LINECOLOR | PUSH_FILLCOLOR | PUSH_TEXTCOLOR);
			m_pDev->SetLineColor( _rNewLineColor );
			m_pDev->SetFillColor( _rNewFillColor );
			m_pDev->SetTextColor( _rNewTextColor );
		}

		~ColorChanger()
		{
			m_pDev->Pop();
		}
	};
}
#endif //RPTUI_COLORCHANGER_HXX

