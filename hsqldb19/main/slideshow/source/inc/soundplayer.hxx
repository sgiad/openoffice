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



#ifndef INCLUDED_SLIDESHOW_SOUNDPLAYER_HXX
#define INCLUDED_SLIDESHOW_SOUNDPLAYER_HXX

#include <rtl/ustring.hxx>

#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/media/XManager.hpp>
#include <com/sun/star/media/XPlayer.hpp>

#include <boost/shared_ptr.hpp>

#include "pauseeventhandler.hxx"
#include "disposable.hxx"
#include "eventmultiplexer.hxx"


/* Definition of SoundPlayer class */

namespace slideshow
{
    namespace internal
    {
        /** Little class that plays a sound from a URL.
            TODO:
            Must be explicitly disposed (as long as enable_shared_ptr_from_this
            isn't available)!
         */
        class SoundPlayer : public PauseEventHandler,
                            public Disposable
        {
        public:
            /** Create a sound player object.

            	@param rSoundURL
                URL to a sound file. 

                @param rComponentContext
                Reference to a component context, used to create the
                needed services

                @throws ::com::sun::star::lang::NoSupportException, if
                the sound file is invalid, or not supported by the
                player service.
             */
            static ::boost::shared_ptr<SoundPlayer> create(
                EventMultiplexer & rEventMultiplexer,
                const ::rtl::OUString& rSoundURL,
                const ::com::sun::star::uno::Reference< 
                ::com::sun::star::uno::XComponentContext>& rComponentContext );

            virtual ~SoundPlayer();

            /** Query duration of sound playback.

            	If the sound is already playing, this method
            	returns the remaining playback time.

                @return the playback duration in seconds.
             */
            double getDuration() const;

            bool startPlayback();
            bool stopPlayback();

			void setPlaybackLoop( bool bLoop );

            // PauseEventHandler:
            virtual bool handlePause( bool bPauseShow );

            // Disposable
            virtual void dispose();

        private:
            SoundPlayer(
                EventMultiplexer & rEventMultiplexer,
                const ::rtl::OUString& rSoundURL,
                const ::com::sun::star::uno::Reference< 
                ::com::sun::star::uno::XComponentContext>& rComponentContext );

            EventMultiplexer & mrEventMultiplexer;
            // TODO(Q3): obsolete when boost::enable_shared_ptr_from_this
            //           is available
            ::boost::shared_ptr<SoundPlayer> mThis;
            ::com::sun::star::uno::Reference< ::com::sun::star::media::XPlayer > mxPlayer;
        };        

        typedef ::boost::shared_ptr< SoundPlayer > SoundPlayerSharedPtr;
    }
}

#endif /* INCLUDED_SLIDESHOW_SOUNDPLAYER_HXX */
