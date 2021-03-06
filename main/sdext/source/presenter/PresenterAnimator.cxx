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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_sdext.hxx"

#include "PresenterAnimator.hxx"

#include "PresenterTimer.hxx"
#include <osl/diagnose.h>
#include <osl/time.h>
#include <vos/timer.hxx>
#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace sdext { namespace presenter {



//===== PresenterAnimator =====================================================

PresenterAnimator::PresenterAnimator (void)
    : maFutureAnimations(),
      maActiveAnimations(),
      mnCurrentTaskId(0),
      mnNextTime(0)
{
}




PresenterAnimator::~PresenterAnimator (void)
{
    PresenterTimer::CancelTask(mnCurrentTaskId);
}





void PresenterAnimator::AddAnimation (const SharedPresenterAnimation& rpAnimation)
{
    ::osl::MutexGuard aGuard (m_aMutex);

    maFutureAnimations.insert(AnimationList::value_type(rpAnimation->GetStartTime(), rpAnimation));
    ScheduleNextRun();
}




void PresenterAnimator::Process (void)
{
    ::osl::MutexGuard aGuard (m_aMutex);

    mnNextTime = 0;
    
    const sal_uInt64 nCurrentTime (GetCurrentTime());

    ActivateAnimations(nCurrentTime);
    
    while ( ! maActiveAnimations.empty())
    {
        sal_uInt64 nRequestedTime (maActiveAnimations.begin()->first);
        SharedPresenterAnimation pAnimation (maActiveAnimations.begin()->second);

        if (nRequestedTime > nCurrentTime)
            break;
        
        maActiveAnimations.erase(maActiveAnimations.begin());
        
        const double nTotalDuration (double(pAnimation->GetEndTime() - pAnimation->GetStartTime()));
        double nProgress (nTotalDuration > 0 ? (nCurrentTime - pAnimation->GetStartTime()) / nTotalDuration : 1);
        if (nProgress <= 0)
            nProgress = 0;
        else if (nProgress >= 1)
            nProgress = 1;

        OSL_TRACE("running animation step at %f (requested was %f) %f\n",
            nCurrentTime/1e6, nRequestedTime/1e6, nProgress);
        pAnimation->Run(nProgress, nCurrentTime);
        
        if (nCurrentTime < pAnimation->GetEndTime())
            maActiveAnimations.insert(
                AnimationList::value_type(
                    nCurrentTime + pAnimation->GetStepDuration(),
                    pAnimation));
        else
            pAnimation->RunEndCallbacks();
    }

    ScheduleNextRun();
}




void PresenterAnimator::ActivateAnimations (const sal_uInt64 nCurrentTime)
{
    while ( ! maFutureAnimations.empty()
        && maFutureAnimations.begin()->first <= nCurrentTime)
    {
        SharedPresenterAnimation pAnimation (maFutureAnimations.begin()->second);
        maActiveAnimations.insert(*maFutureAnimations.begin());
        maFutureAnimations.erase(maFutureAnimations.begin());
        pAnimation->RunStartCallbacks();
    }
}




void PresenterAnimator::ScheduleNextRun (void)
{
    sal_uInt64 nStartTime (0);

    if ( ! maActiveAnimations.empty())
    {
        nStartTime  = maActiveAnimations.begin()->first;
        if ( ! maFutureAnimations.empty())
            if (maFutureAnimations.begin()->first < nStartTime)
                nStartTime = maFutureAnimations.begin()->first;
    }
    else if ( ! maFutureAnimations.empty())
        nStartTime = maFutureAnimations.begin()->first;

    if (nStartTime > 0)
        ScheduleNextRun(nStartTime);
}




void PresenterAnimator::ScheduleNextRun (const sal_uInt64 nStartTime)
{
    if (mnNextTime==0 || nStartTime<mnNextTime)
    {
        mnNextTime = nStartTime;
        ::vos::TTimeValue aTimeValue (GetSeconds(mnNextTime), GetNanoSeconds(mnNextTime));
        PresenterTimer::ScheduleSingleTaskAbsolute (
            ::boost::bind(&PresenterAnimator::Process, this),
            aTimeValue);
    }
}

} } // end of namespace ::sdext::presenter
