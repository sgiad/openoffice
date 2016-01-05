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


                                                                                                                             

#ifndef SC_QPROFORM_HXX
#define SC_QPROFORM_HXX

#include <sal/config.h>
#include "formel.hxx"
#include <tools/string.hxx>
#include "qpro.hxx"

#include <compiler.hxx>
typedef OpCode DefTokenId;

enum FUNC_TYPE
{
    FT_Return,  
    FT_FuncFix0,
    FT_FuncFix1,   
    FT_FuncFix2,  
    FT_FuncFix3,    
    FT_FuncFix4,    
    FT_FuncFix5,
    FT_FuncFix6,
    FT_FuncVar,            
    FT_DLL,
    FT_Neg,               
    FT_Op,              
    FT_NotImpl,        
    FT_ConstFloat,  
    FT_Range,   
    FT_Braces,
    FT_ConstInt,    
    FT_ConstString,
    FT_NOP,                 
    FT_Cref               
};
                                                                                                                  
class QProToSc : public ConverterBase
{
    private:
    TokenId mnAddToken;  
    TokenId mnSubToken;  
    TokenId mn0Token;  
    SvStream& maIn; 

    public:
    static const size_t nBufSize = 256;
    QProToSc( SvStream &aStr, const ScAddress& rRefPos );
    ~QProToSc(){ };
    ConvErr Convert( const ScTokenArray*& pArray, sal_uInt16 nLen,
                                                                         const FORMULA_TYPE eFT = FT_CellFormula );
    void DoFunc( DefTokenId eOc, sal_uInt16 nArgs, const sal_Char* pExtString );
    void ReadSRD( ScSingleRefData& rR, sal_Int8 nPage, sal_Int8 nCol, sal_uInt16 rRel ); 
    void IncToken( TokenId &aParam );
    DefTokenId IndexToToken( sal_uInt16 nToken );
    FUNC_TYPE IndexToType( sal_uInt8 nToken );
    DefTokenId IndexToDLLId( sal_uInt16 nIndex );
    const sal_Char* getString( sal_uInt8 nIndex );
};
#endif
