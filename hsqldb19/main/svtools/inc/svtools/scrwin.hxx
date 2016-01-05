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



#ifndef _SCRWIN_HXX
#define _SCRWIN_HXX

#include "svtools/svtdllapi.h"

#ifndef _SCRBAR_HXX //autogen
#include <vcl/scrbar.hxx>
#endif

class DataChangedEvent;

// -------------------------
// - ScrollableWindow-Type -
// -------------------------

typedef sal_uInt16 ScrollableWindowFlags;

#define SCRWIN_THUMBDRAGGING 1
#define SCRWIN_VCENTER		 2
#define SCRWIN_HCENTER		 4
#define SCRWIN_DEFAULT		 (SCRWIN_THUMBDRAGGING | SCRWIN_VCENTER | SCRWIN_HCENTER)

// --------------------
// - ScrollableWindow -
// --------------------

class SVT_DLLPUBLIC ScrollableWindow: public Window
{
private:
	Point			aPixOffset; 		// offset to virtual window (pixel)
	Size			aTotPixSz;			// total size of virtual window (pixel)
	long			nLinePixH;			// size of a line/column (pixel)
	long			nColumnPixW;

	ScrollBar		aVScroll;			// the scrollbars
	ScrollBar		aHScroll;
	ScrollBarBox	aCornerWin; 		// window in the bottom right corner
	sal_Bool			bScrolling:1,		// user controlled scrolling
					bHandleDragging:1,	// scroll window while dragging
					bHCenter:1,
					bVCenter:1;

#ifdef _SVT_SCRWIN_CXX
	SVT_DLLPRIVATE void			ImpInitialize( ScrollableWindowFlags nFlags );
	DECL_DLLPRIVATE_LINK( ScrollHdl, ScrollBar * );
	DECL_DLLPRIVATE_LINK( EndScrollHdl, ScrollBar * );
#endif

public:
					ScrollableWindow( Window* pParent, WinBits nBits = 0,
									  ScrollableWindowFlags = SCRWIN_DEFAULT );
					ScrollableWindow( Window* pParent, const ResId& rId,
									  ScrollableWindowFlags = SCRWIN_DEFAULT );

	virtual void	Resize();
	virtual void	Command( const CommandEvent& rCEvt );
	virtual void	DataChanged( const DataChangedEvent& rDEvt );

	virtual void	StartScroll();
	virtual void	EndScroll( long nDeltaX, long nDeltaY );

    using OutputDevice::SetMapMode;
	virtual void	SetMapMode( const MapMode& rNewMapMode );
	virtual MapMode	GetMapMode() const;

	void			SetTotalSize( const Size& rNewSize );
	Size			GetTotalSize() { return PixelToLogic( aTotPixSz ); }

	void			SetVisibleSize( const Size& rNewSize );
	sal_Bool			MakeVisible( const Rectangle& rTarget, sal_Bool bSloppy = sal_False );
	Rectangle		GetVisibleArea() const;

	void			SetLineSize( sal_uLong nHorz, sal_uLong nVert );
    using Window::Scroll;
	virtual void	Scroll( long nDeltaX, long nDeltaY, sal_uInt16 nFlags = 0 );
	void			ScrollLines( long nLinesX, long nLinesY );
	void			ScrollPages( long nPagesX, sal_uLong nOverlapX,
								 long nPagesY, sal_uLong nOverlapY );

private:
	SVT_DLLPRIVATE Size			GetOutputSizePixel() const;
	SVT_DLLPRIVATE Size			GetOutputSize() const;
};

#endif
