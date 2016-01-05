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



#ifndef _SVX_ACTIONDESCRIPTIONPROVIDER_HXX
#define _SVX_ACTIONDESCRIPTIONPROVIDER_HXX

#include "svx/svxdllapi.h"

// header for class OUString
#include <rtl/ustring.hxx>

//-----------------------------------------------------------------------------
/** This class provides localized descriptions for some basic actions done with objects.
The strings are intended to be provided to the user e.g. as description for undo actions in the menu.
The name of the object acted on and the type of action needs to be given as input parameter.
*/

class SVX_DLLPUBLIC ActionDescriptionProvider
{
public:
    enum ActionType
    {
        INSERT
        , DELETE
        , CUT
        , MOVE
        , RESIZE
        , ROTATE
        , TRANSFORM
        , FORMAT
        , MOVE_TOTOP
        , MOVE_TOBOTTOM
        , POS_SIZE
    };

public:
    static ::rtl::OUString createDescription( ActionType eActionType
                        , const ::rtl::OUString& rObjectName );
};

#endif
