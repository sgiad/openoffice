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



#ifndef INCLUDED_SLIDESHOW_VIEW_HXX
#define INCLUDED_SLIDESHOW_VIEW_HXX

#include "viewlayer.hxx"

#include <boost/shared_ptr.hpp>
#include <vector>


namespace basegfx { class B2DRange; class B2DVector; }


/* Definition of View interface */

namespace slideshow
{
    namespace internal
    {
        class View : public ViewLayer
        {
        public:
            /** Create a new view layer for this view
            
                @param rLayerBounds
                Specifies the bound rect of the layer relative to the
                user view coordinate system.

            	This method sets the bounds of the view layer in
            	document coordinates (i.e. 'logical' coordinates). The
            	resulting transformation is then concatenated with the
            	underlying view transformation, returned by the
            	getTransformation() method.
             */
            virtual ViewLayerSharedPtr createViewLayer( const basegfx::B2DRange& rLayerBounds ) const = 0;

            /** Update screen representation from backbuffer
             */
            virtual bool updateScreen() const = 0;

            /** Paint screen content unconditionally from backbuffer
             */
            virtual bool paintScreen() const = 0;

            /** Set the size of the user view coordinate system.

            	This method sets the width and height of the view in
            	document coordinates (i.e. 'logical' coordinates). The
            	resulting transformation is then concatenated with the
            	underlying view transformation, returned by the
            	getTransformation() method.
            */
            virtual void setViewSize( const ::basegfx::B2DVector& ) = 0;

            /** Change the view's mouse cursor.
                
            	@param nPointerShape
                One of the ::com::sun::star::awt::SystemPointer
                constant group members.
             */
            virtual void setCursorShape( sal_Int16 nPointerShape ) = 0;
        };

        typedef ::boost::shared_ptr< View > 	ViewSharedPtr;
        typedef ::std::vector< ViewSharedPtr >	ViewVector;
    }
}

#endif /* INCLUDED_SLIDESHOW_VIEW_HXX */
