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



#ifndef INCLUDED_DRAWINGLAYER_ATTRIBUTE_FONTATTRIBUTE_HXX
#define INCLUDED_DRAWINGLAYER_ATTRIBUTE_FONTATTRIBUTE_HXX

#include <drawinglayer/drawinglayerdllapi.h>
//////////////////////////////////////////////////////////////////////////////
// predefines

class String;

namespace drawinglayer { namespace attribute {
	class ImpFontAttribute;
}}

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace attribute
	{
        /** FontAttribute class

            This attribute class is able to hold all parameters needed/used
            to completely define the parametrisation of a text portion.
         */
		class DRAWINGLAYER_DLLPUBLIC FontAttribute
		{
        private:
            ImpFontAttribute*               mpFontAttribute;

		public:
            /// constructors/assignmentoperator/destructor
			/// TODO: pair kerning and CJK kerning
			FontAttribute(
                const String& rFamilyName,
                const String& rStyleName,
                sal_uInt16 nWeight,
                bool bSymbol = false,
                bool bVertical = false,
                bool bItalic = false,
                bool bMonospaced = false,
                bool bOutline = false,
                bool bRTL = false,
                bool bBiDiStrong = false);
			FontAttribute();
			FontAttribute(const FontAttribute& rCandidate);
			FontAttribute& operator=(const FontAttribute& rCandidate);
			~FontAttribute();

            // checks if the incarnation is default constructed
            bool isDefault() const;

            // compare operator
			bool operator==(const FontAttribute& rCandidate) const;

            /// data read access
            const String& getFamilyName() const;
            const String& getStyleName() const;
            sal_uInt16 getWeight() const;
            bool getSymbol() const;
            bool getVertical() const;
            bool getItalic() const;
            bool getOutline() const;
            bool getRTL() const;
            bool getBiDiStrong() const;
            bool getMonospaced() const;
		};
	} // end of namespace attribute
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

#endif //INCLUDED_DRAWINGLAYER_ATTRIBUTE_FONTATTRIBUTE_HXX

// eof
