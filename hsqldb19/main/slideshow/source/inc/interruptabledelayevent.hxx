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



#ifndef INCLUDED_SLIDESHOW_INTERRUPTABLEDELAYEVENT_HXX
#define INCLUDED_SLIDESHOW_INTERRUPTABLEDELAYEVENT_HXX

#include "delayevent.hxx"

namespace slideshow
{
    namespace internal
    {
        /** Event, which delays calling passed Event's fire() method
            the given amount of time.

            This is actually a facade around the passed event object,
            that passes on all calls to that object, and the sole
            contribution of itself is the delay.
        */
        class DelayFacade : public Event
        {
        public:
            DelayFacade( const EventSharedPtr& 	rEvent,
                         double					nTimeout	) :
#if OSL_DEBUG_LEVEL > 1
                Event(::rtl::OUString::createFromAscii("DelayFacade")),
#endif
                mpEvent( rEvent ),
                mnTimeout( nTimeout )
            {
            }

            virtual bool fire()
            {
                if( mpEvent && isCharged() )
                {
                    // pass on directly - we're supposed to be called
                    // from EventQueue here, anyway - and if not,
                    // we're only keeping that incorrect transitively.
                    return mpEvent->fire();
                }

                return false;
            }

            virtual bool isCharged() const
            {
                // pass on to wrappee - this ensures that we return
                // false on isCharged(), even if the other event has
                // been fired outside our own fire() method
                return !mpEvent ? false : mpEvent->isCharged();
            }

            virtual double getActivationTime( double nCurrentTime ) const
            {
                // enforce _our_ timeout to our clients (this
                // overrides any timeout possibly set at the wrappee!)
                return nCurrentTime + mnTimeout;
            }

            virtual void dispose()
            {
                mpEvent.reset();
            }

        private:
            EventSharedPtr	mpEvent;
            double			mnTimeout;	
        };

        /// Return value for makeInterruptableDelay()
        struct InterruptableEventPair
        {
            /** This member contains a pointer to the timeout
                event. When enqueued, this event will fire the
                requested action only after the specified timeout.
             */
            EventSharedPtr	mpTimeoutEvent;

            /** This member contains a pointer to the interruption
                event. When enqueued, this event will fire
                immediately, interrupting a potentially waiting
                timeout event.
             */
            EventSharedPtr	mpImmediateEvent;
        };

        /** Generate an interruptable delay event.

        	This function generates a pair of events, that are
        	especially tailored to achieve the following behaviour: By
        	default, the given functor is called after the specified
        	timeout (after insertion of the event into the EventQueue,
        	of course). But optionally, when the interruption event
        	InterruptableEventPair::mpImmediateEvent is fired, the
        	given functor is called <em>at once</em>, and the delay is
        	ignored (that means, the given functor is guaranteed to be
        	called at utmost once, and never twice. Furthermore, it is
        	ensured that both events return false on isCharged(), once
        	anyone of them has been fired already).

        	@param rFunctor
            Functor to call when the event fires.

            @param nTimeout
            Timeout in seconds, to wait until functor is called.

			@returns a pair of events, where the first one waits the
			specified amount of time, and the other fires the given
			functor immediately.
         */
        template< typename Functor > InterruptableEventPair makeInterruptableDelay( const Functor& 	rFunctor,
                                                                                    double			nTimeout	)
        {
            InterruptableEventPair aRes;

            aRes.mpImmediateEvent = makeEvent( rFunctor, "makeInterruptableDelay");
            aRes.mpTimeoutEvent.reset( new DelayFacade( aRes.mpImmediateEvent,
                                                        nTimeout ) );

            return aRes;
        }
    }
}

#endif /* INCLUDED_SLIDESHOW_INTERRUPTABLEDELAYEVENT_HXX */
