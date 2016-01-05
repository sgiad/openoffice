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


#ifndef _SECTFRM_HXX
#define _SECTFRM_HXX
#include <tools/mempool.hxx>

#include "layfrm.hxx"
#include "flowfrm.hxx"

class SwSection;
class SwSectionFmt;
class SwAttrSetChg;
class SwFtnContFrm;
class SwLayouter;

#define FINDMODE_ENDNOTE 1
#define FINDMODE_LASTCNT 2
#define FINDMODE_MYLAST  4

class SwSectionFrm: public SwLayoutFrm, public SwFlowFrm
{
	SwSection* pSection;

	void _UpdateAttr( const SfxPoolItem*, const SfxPoolItem*, sal_uInt8 &,
					  SwAttrSetChg *pa = 0, SwAttrSetChg *pb = 0 );
	void _Cut( sal_Bool bRemove );
	// Is there a FtnContainer?
	// An empty sectionfrm without FtnCont is superfluous
	sal_Bool IsSuperfluous() const { return !ContainsAny() && !ContainsFtnCont(); }
	void CalcFtnAtEndFlag();
	void CalcEndAtEndFlag();
	const SwSectionFmt* _GetEndSectFmt() const;
	sal_Bool IsEndnoteAtMyEnd() const;
protected:
	virtual void MakeAll();
	virtual sal_Bool ShouldBwdMoved( SwLayoutFrm *pNewUpper, sal_Bool bHead, sal_Bool &rReformat );
	virtual void Format( const SwBorderAttrs *pAttrs = 0 );
	virtual	void Modify( const SfxPoolItem*, const SfxPoolItem* );
	virtual void SwClientNotify( const SwModify&, const SfxHint& );

public:
	SwSectionFrm( SwSection &, SwFrm* );				 //Inhalt wird nicht erzeugt!
    SwSectionFrm( SwSectionFrm &, sal_Bool bMaster );//_Nur_ zum Erzeugen von Master/Follows
	~SwSectionFrm();

    void Init();
    virtual void  CheckDirection( sal_Bool bVert );

	virtual void Cut();
	virtual void Paste( SwFrm* pParent, SwFrm* pSibling = 0 );

	inline const SwSectionFrm *GetFollow() const;
	inline		 SwSectionFrm *GetFollow();
    SwSectionFrm* FindMaster() const;

                 SwCntntFrm *FindLastCntnt( sal_uInt8 nMode = 0 );
	inline const SwCntntFrm *FindLastCntnt( sal_uInt8 nMode = 0 ) const;
	inline SwSection* GetSection() { return pSection; }
	inline const SwSection* GetSection() const { return pSection; }
	inline void ColLock()		{ bColLocked = sal_True; }
	inline void ColUnlock()   	{ bColLocked = sal_False; }

	void CalcFtnCntnt();
	void SimpleFormat();
	sal_Bool IsDescendantFrom( const SwSectionFmt* pSect ) const;
	sal_Bool HasToBreak( const SwFrm* pFrm ) const;
	void MergeNext( SwSectionFrm* pNxt );
	//Zerlegt den pFrm umgebenden SectionFrm in zwei Teile,
	//pFrm an den Anfang des 2. Teils
	sal_Bool SplitSect( SwFrm* pFrm, sal_Bool bApres );
	void DelEmpty( sal_Bool bRemove ); 	// wie Cut(), Follow-Verkettung wird aber mitgepflegt
	sal_Bool IsToIgnore() const			// Keine Groesse, kein Inhalt, muss ignoriert werden
	{ return !Frm().Height() && !ContainsCntnt(); }
    SwFtnContFrm* ContainsFtnCont( const SwFtnContFrm* pCont = NULL ) const;
	sal_Bool Growable() const;
    SwTwips _Shrink( SwTwips, sal_Bool bTst );
    SwTwips _Grow  ( SwTwips, sal_Bool bTst );

	// A sectionfrm has to maximize, if he has a follow or a ftncontainer at
	// the end of the page. A superfluous follow will be ignored,
	// if bCheckFollow is set.
	sal_Bool ToMaximize( sal_Bool bCheckFollow ) const;
	inline sal_Bool _ToMaximize() const
		{ if( !pSection ) return sal_False; return ToMaximize( sal_False );	}
	sal_Bool MoveAllowed( const SwFrm* ) const;
	sal_Bool CalcMinDiff( SwTwips& rMinDiff ) const;
	// Uebergibt man kein bOverSize bzw. sal_False, so ist der Returnwert
	// >0 fuer Undersized-Frames, ==0 sonst.
	// Uebergibt man sal_True, so kann es auch einen negativen Returnwert geben,
	// wenn der SectionFrm nicht vollstaendig ausgefuellt ist, was z.B. bei
	// SectionFrm mit Follow meist vorkommt. Benoetigt wird dies im
	// FormatWidthCols, um "Luft" aus den Spalten zu lassen.
	long Undersize( sal_Bool bOverSize = sal_False );
	// Groesse an die Umgebung anpassen
	void _CheckClipping( sal_Bool bGrow, sal_Bool bMaximize );

	void InvalidateFtnPos();
	void CollectEndnotes( SwLayouter* pLayouter );
	const SwSectionFmt* GetEndSectFmt() const
		{ if( IsEndnAtEnd() ) return _GetEndSectFmt(); return NULL; }

	static void MoveCntntAndDelete( SwSectionFrm* pDel, sal_Bool bSave );

    bool IsBalancedSection() const;

	DECL_FIXEDMEMPOOL_NEWDEL(SwSectionFrm)
};

typedef SwSectionFrm* SwSectionFrmPtr;
SV_DECL_PTRARR_SORT( SwDestroyList, SwSectionFrmPtr, 1, 5)

inline const SwSectionFrm *SwSectionFrm::GetFollow() const
{
	return (const SwSectionFrm*)SwFlowFrm::GetFollow();
}
inline SwSectionFrm *SwSectionFrm::GetFollow()
{
	return (SwSectionFrm*)SwFlowFrm::GetFollow();
}
inline const SwCntntFrm *SwSectionFrm::FindLastCntnt( sal_uInt8 nMode ) const
{
	return ((SwSectionFrm*)this)->FindLastCntnt( nMode );
}


#endif	//_SECTFRM_HXX
