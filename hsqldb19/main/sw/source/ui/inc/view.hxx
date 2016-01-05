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


#ifndef _SWVIEW_HXX
#define _SWVIEW_HXX

#include <vcl/timer.hxx>
#include <vcl/field.hxx>
#include <svtools/htmlcfg.hxx>
#include <sfx2/viewfac.hxx>
#include <sfx2/viewsh.hxx>
#include <sfx2/objsh.hxx>
#include <editeng/svxenum.hxx>
#include <svx/zoomitem.hxx>
#include <editeng/editstat.hxx>
#include "swdllapi.h"
#include <swtypes.hxx>
#include <shellid.hxx>
#include <layout/layout.hxx>
#include <IMark.hxx>

class SwBaseShell;
class Button;
class ImageButton;
class SwTxtFmtColl;
class SwPageDesc;
class SwFrmFmt;
class SwCharFmt;
class SwNumRule;
class SwViewOption;
class SwGlossaryHdl;
class SwDrawBase;
class SvxRuler;
class SvxLRSpaceItem;
class SwDocShell;
class SwScrollbar;
class SvxVCBrowser;
class SvBorder;
class Ruler;
class OutlinerView;
class SvxSearchItem;
class SearchAttrItemList;
class SvxSearchDialog;
class SdrView;
class Dialog;
class SdrObject;
class SdrPageView;
class SwNaviImageButton;
class SwHlpImageButton;
class Outliner;
class SwView;
class SwEditWin;
class SwWrtShell;
class SwView_Impl;
class XSelectionObject;
struct SwSearchOptions;
class FmFormShell;
class CommandEvent;
class InsCaptionOpt;
class SvGlobalName;
class SvtAccessibilityOptions;
class SwTransferable;
class SwMailMergeConfigItem;
class SwTxtNode; // #i23726#
class SwPrintData;
class SwFormatClipboard;
struct SwConversionArgs;
class Graphic;
class GraphicFilter;
class SwPostItMgr;
class SwFieldBookmark;

namespace com{ namespace sun { namespace star {
	namespace view{ class XSelectionSupplier; }
}}}
namespace sfx2 { class FileDialogHelper; }

const long nLeftOfst = -370;
const long nScrollX	 =	 30;
const long nScrollY	 =	 30;

#define MINZOOM 20
#define MAXZOOM 600

#define MAX_MARKS 5

#define CHILDWIN_LABEL      1
#define CHILDWIN_MAILMERGE  2

enum ShellModes
{
	SHELL_MODE_TEXT,
	SHELL_MODE_FRAME,
	SHELL_MODE_GRAPHIC,
	SHELL_MODE_OBJECT,
	SHELL_MODE_DRAW,
	SHELL_MODE_DRAW_CTRL,
	SHELL_MODE_DRAW_FORM,
	SHELL_MODE_DRAWTEXT,
	SHELL_MODE_BEZIER,
	SHELL_MODE_LIST_TEXT,
	SHELL_MODE_TABLE_TEXT,
	SHELL_MODE_TABLE_LIST_TEXT,
	SHELL_MODE_MEDIA,
    SHELL_MODE_EXTRUDED_CUSTOMSHAPE,
    SHELL_MODE_FONTWORK,
	SHELL_MODE_POSTIT
};

/*--------------------------------------------------------------------
	Beschreibung:	Anwendung einer Vorlage
 --------------------------------------------------------------------*/

struct SwApplyTemplate
{
	union
	{
		SwTxtFmtColl* pTxtColl;
		SwPageDesc*   pPageDesc;
		SwFrmFmt*	  pFrmFmt;
		SwCharFmt*	  pCharFmt;
		SwNumRule*	  pNumRule;
	} aColl;

	int eType;
	sal_uInt16 nColor;
    SwFormatClipboard* pFormatClipboard;
	sal_Bool bUndo;

	SwApplyTemplate() :
		eType(0),
		nColor(0),
        pFormatClipboard(0),
		bUndo(sal_False)
	{
		aColl.pTxtColl = 0;
	}
};


/*--------------------------------------------------------------------
	Beschreibung:	Sicht auf ein Dokument
 --------------------------------------------------------------------*/

class SW_DLLPUBLIC SwView: public SfxViewShell
{
	//Messehack (MA,MBA)
	friend void lcl_SelectShellForDrop( SwView &rView );

	friend class TestTemplateItem;
    friend class SwHHCWrapper;
	friend class SwHyphWrapper;
	friend class SwView_Impl;
	friend class SwClipboardChangeListener;

	//suchen & ersetzen
	static SvxSearchDialog *pSrchDlg;
	static SvxSearchItem   *pSrchItem;

	static sal_uInt16			nInsertCtrlState;
	static sal_uInt16			nWebInsertCtrlState;
	static sal_uInt16			nInsertObjectCtrlState;
	static sal_uInt16			nInsertFieldCtrlState;
	static sal_uInt16			nMoveType; // fuer Buttons unter dem Scrollbar (viewmdi)
    static sal_Int32        nActMark; // aktuelle Sprungmarke fuer unbenannte Merker

	static sal_Bool             bExtra;
	static sal_Bool             bFound;
	static sal_Bool				bJustOpened;

	static SearchAttrItemList* pSrchList;
	static SearchAttrItemList* pReplList;


    SvxHtmlOptions      aHTMLOpt;
	Timer				aTimer;			//Fuer verzoegerte ChgLnks waehrend
										//einer Aktion
	String				aPageStr;		//Statusanzeige, aktuelle Seite
	String 				sSwViewData,
	//and the new cursor position if the user double click in the PagePreView
						sNewCrsrPos;
    // to support keyboard the number of the page to go to can be set too
    sal_uInt16              nNewPage;
	sal_uInt16			nOldPageNum;
	String			nOldSectionName;
	Point				aTabColFromDocPos;	//Verschieben von Tabellenspalten aus
											//aus dem Dokument heraus.
    SwTxtNode           * pNumRuleNodeFromDoc; // Moving indent of numrule #i23726#

	Size				aDocSz;			// aktuelle Dokumentgroesse
	Rectangle			aVisArea;		// sichtbarer Bereich

	SwEditWin			*pEditWin;
	SwWrtShell			*pWrtShell;

	SfxShell			*pShell;		//aktuelle SubShell auf dem Dispatcher
	FmFormShell			*pFormShell;	// DB-FormShell

	SwView_Impl			*pViewImpl;		// Impl-Daten fuer UNO + Basic


	SwScrollbar	   		*pHScrollbar,	// MDI Bedienelemente
						*pVScrollbar;

	Window		   		*pScrollFill;	// Dummy-Window zum Fuellen der rechten
										// unteren Ecke, wenn beide Scrollbars
										// aktiv sind

    SvxRuler            *pHRuler,
                        *pVRuler;
	ImageButton	   		*pTogglePageBtn;

	SwHlpImageButton 	*pPageUpBtn,
						*pPageDownBtn;

	SwNaviImageButton 	*pNaviBtn;
	SwGlossaryHdl  		*pGlosHdl;			// Henkel Textbausteine
	SwDrawBase			*pDrawActual;

	const SwFrmFmt		*pLastTableFormat;

    SwFormatClipboard   *pFormatClipboard; //holds data for format paintbrush

	SwPostItMgr			*mpPostItMgr;

	int					nSelectionType;

    static const int MASTERENUMCOMMANDS = 6;

    String			aCurrShapeEnumCommand[ MASTERENUMCOMMANDS ];

    sal_uInt16          nPageCnt;

	// Aktueller Drawmode
	sal_uInt16			nDrawSfxId;
    String          sDrawCustom; //some drawing types are marked with strings!
	sal_uInt16			nFormSfxId;
	sal_uInt16			nLastPasteDestination;

    // save the border distance status from SwView::StateTabWin to re-use it in SwView::ExecTabWin()
    sal_uInt16          nLeftBorderDistance;
    sal_uInt16          nRightBorderDistance;

	sal_Bool			bCenterCrsr : 1,
					bTopCrsr : 1,
					bAllwaysShowSel : 1,
					bTabColFromDoc : 1,
                    bNumIndentFromDoc : 1, // #i23726#
                    bTabRowFromDoc : 1,
					bSetTabColFromDoc : 1 ,
                    bSetTabRowFromDoc : 1,
					bAttrChgNotified : 1,
					bAttrChgNotifiedWithRegistrations : 1,
					bVerbsActive : 1,
					bDrawRotate : 1,
					bDrawSelMode : 1,
					bShowAtResize : 1,
					bInOuterResizePixel : 1,
                    bInInnerResizePixel : 1,
					bPasteState : 1,
                    bPasteSpecialState : 1,
                    bInMailMerge : 1,
                    bInDtor : 1, //detect destructor to prevent creating of sub shells while closing
                    bOldShellWasPagePreView : 1,
                    bIsPreviewDoubleClick : 1, // #i114045#
                    bMakeSelectionVisible : 1 // #b6330459# transport the bookmark selection
					;

	// Methoden fuers Suchen
	// Suchkontext setzen
	SW_DLLPRIVATE sal_Bool   			SearchAndWrap(sal_Bool bApi = sal_False);
	SW_DLLPRIVATE sal_Bool 			SearchAll(sal_uInt16* pFound = 0);
	SW_DLLPRIVATE sal_uLong			FUNC_Search( const SwSearchOptions& rOptions );
	SW_DLLPRIVATE void 			Replace();

	sal_Bool		                        IsDocumentBorder();

	SW_DLLPRIVATE sal_Bool			IsTextTool() const;

	// Bedienelemente verwalten anlegen
	SW_DLLPRIVATE void			CreateBtns();
	SW_DLLPRIVATE DECL_LINK( BtnPage, Button * );

	SW_DLLPRIVATE DECL_LINK( TimeoutHdl, Timer * );
    SW_DLLPRIVATE DECL_LINK( UpdatePercentHdl, GraphicFilter* );

	SW_DLLPRIVATE DECL_LINK( HtmlOptionsHdl, void * );

	inline long		GetXScroll() const;
	inline long		GetYScroll() const;
	SW_DLLPRIVATE  Point	AlignToPixel(const Point& rPt) const;
	SW_DLLPRIVATE 	void		CalcPt(	Point* pPt,const Rectangle& rRect,
							sal_uInt16 nRangeX = USHRT_MAX,
							sal_uInt16 nRangeY = USHRT_MAX);

	SW_DLLPRIVATE sal_Bool			GetPageScrollUpOffset(SwTwips& rOff) const;
	SW_DLLPRIVATE sal_Bool			GetPageScrollDownOffset(SwTwips& rOff) const;

	// Scrollbar Movements
	SW_DLLPRIVATE long			PageUp();
	SW_DLLPRIVATE long			PageDown();
	SW_DLLPRIVATE long			PageUpCrsr(sal_Bool bSelect);
	SW_DLLPRIVATE long			PageDownCrsr(sal_Bool bSelect);
	SW_DLLPRIVATE long			PhyPageUp();
	SW_DLLPRIVATE long			PhyPageDown();

    SW_DLLPRIVATE int               _CreateScrollbar( sal_Bool bHori );
	SW_DLLPRIVATE DECL_LINK( ScrollHdl, SwScrollbar * );
	SW_DLLPRIVATE DECL_LINK( EndScrollHdl, SwScrollbar * );
	SW_DLLPRIVATE sal_Bool			UpdateScrollbars();
	SW_DLLPRIVATE void			CalcVisArea( const Size &rPixelSz );

    SW_DLLPRIVATE void            CreatePageButtons(sal_Bool bShow);

	// Linguistik-Funktionen
	SW_DLLPRIVATE void			HyphenateDocument();
	SW_DLLPRIVATE sal_Bool			IsDrawTextHyphenate();
	SW_DLLPRIVATE void			HyphenateDrawText();
	SW_DLLPRIVATE void			StartThesaurus();

    // text conversion
    SW_DLLPRIVATE void          StartTextConversion( LanguageType nSourceLang, LanguageType nTargetLang, const Font *pTargetFont, sal_Int32 nOptions, sal_Bool bIsInteractive );

    // used for spell checking and text conversion
    SW_DLLPRIVATE void          SpellStart( SvxSpellArea eSpell, sal_Bool bStartDone,
                                        sal_Bool bEndDone, SwConversionArgs *pConvArgs = 0 );
    SW_DLLPRIVATE void          SpellEnd( SwConversionArgs *pConvArgs = 0 );

    SW_DLLPRIVATE void          HyphStart( SvxSpellArea eSpell );
	SW_DLLPRIVATE sal_Bool			CheckSpecialCntnt();
	SW_DLLPRIVATE void			SpellKontext(sal_Bool bOn = sal_True)
							{ bCenterCrsr = bOn; bAllwaysShowSel = bOn; }

	// Methoden fuers Printing
	SW_DLLPRIVATE virtual	SfxPrinter* 	GetPrinter( sal_Bool bCreate = sal_False );
			SfxTabPage* 	CreatePrintOptionsPage( Window* pParent,
													const SfxItemSet& rSet);
	// fuer Readonly-Umschaltung
	SW_DLLPRIVATE virtual void	Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
	SW_DLLPRIVATE void			_CheckReadonlyState();
	SW_DLLPRIVATE void			_CheckReadonlySelection();

	// Methode fuer PageDesc drehen
	SW_DLLPRIVATE void			SwapPageMargin(const SwPageDesc&, SvxLRSpaceItem& rLR);

	SW_DLLPRIVATE void			_SetZoom( const Size &rEditSz,
							  SvxZoomType eZoomType,
							  short nFactor = 100,
							  sal_Bool bViewOnly = sal_False);
	SW_DLLPRIVATE void			CalcAndSetBorderPixel( SvBorder &rToFill, sal_Bool bInner );

	SW_DLLPRIVATE void		    ShowAtResize();

	SW_DLLPRIVATE virtual void	Move();

public: // #123922# Needs to be called from a 2nd place now as a helper method
    SW_DLLPRIVATE sal_Bool          InsertGraphicDlg( SfxRequest& );

protected:

	SwView_Impl*	GetViewImpl() {return pViewImpl;}

	void ImpSetVerb( int nSelType );

	int				GetSelectionType() const { return nSelectionType; }
	void			SetSelectionType(int nSet) { nSelectionType = nSet;}

	// fuer die SwWebView
	void			SetShell( SfxShell* pS ) 			{ pShell = pS; }
	void 			SetFormShell( FmFormShell* pSh )	{ pFormShell = pSh; }

	virtual void	SelectShell();

	virtual void	Activate(sal_Bool);
	virtual void 	Deactivate(sal_Bool);
	virtual void 	InnerResizePixel( const Point &rOfs, const Size &rSize );
	virtual void 	OuterResizePixel( const Point &rOfs, const Size &rSize );
	virtual Size	GetOptimalSizePixel() const;

	void			SetImageButtonColor(Color& rColor);

	const SwFrmFmt* GetLastTblFrmFmt() const {return pLastTableFormat;}
	void 			SetLastTblFrmFmt(const SwFrmFmt* pSet) {pLastTableFormat = pSet;}

    // form letter execution
    void    GenerateFormLetter(sal_Bool bUseCurrentDocument);

    using SfxShell::GetDispatcher;

public:

	SFX_DECL_VIEWFACTORY(SwView);
	SFX_DECL_INTERFACE(SW_VIEWSHELL)
	TYPEINFO();

	SfxDispatcher 	&GetDispatcher();

	void                    GotFocus() const;
	virtual SdrView*		GetDrawView() const;
	virtual	sal_Bool		HasUIFeature( sal_uInt32 nFeature );
	virtual	void			ShowCursor( FASTBOOL bOn = sal_True );
	virtual ErrCode			DoVerb( long nVerb );

	virtual sal_uInt16			SetPrinter(	SfxPrinter* pNew,
                                        sal_uInt16 nDiff = SFX_PRINTER_ALL, bool bIsAPI=false);
	ShellModes				GetShellMode();

	com::sun::star::view::XSelectionSupplier*		GetUNOObject();

	String					GetSelectionTextParam( sal_Bool bCompleteWords,
												   sal_Bool bEraseTrail );
	virtual sal_Bool			HasSelection( sal_Bool  bText ) const;
	virtual String			GetSelectionText( sal_Bool bCompleteWords = sal_False );
	virtual sal_uInt16			PrepareClose( sal_Bool bUI = sal_True, sal_Bool bForBrowsing = sal_False );
	virtual	void			MarginChanged();

    // replace word/selection with text from the thesaurus
    // (this code has special handling for "in word" character)
    void                    InsertThesaurusSynonym( const String &rSynonmText, const String &rLookUpText, bool bValidSelection );
    bool                    IsValidSelectionForThesaurus() const;
    String                  GetThesaurusLookUpText( bool bSelection ) const;

	// Shell sofort wechseln ->  fuer GetSelectionObject
	void		StopShellTimer();

	inline SwWrtShell&		GetWrtShell   () const { return *pWrtShell; }
	inline SwWrtShell*		GetWrtShellPtr() const { return  pWrtShell; }

	inline 		 SwEditWin &GetEditWin() 	    { return *pEditWin; }
	inline const SwEditWin &GetEditWin () const { return *pEditWin; }

#if defined WNT || defined UNX
	void ScannerEventHdl( const ::com::sun::star::lang::EventObject& rEventObject );
#endif

	//Handler fuer Textbausteine an die Textshell rausreichen, gfs. anlegen
	SwGlossaryHdl*			GetGlosHdl();

	inline const Rectangle&	GetVisArea() const { return aVisArea; }

	sal_Bool			IsScroll(const Rectangle& rRect) const;
	void			Scroll(	const Rectangle& rRect,
							sal_uInt16 nRangeX = USHRT_MAX,
							sal_uInt16 nRangeY = USHRT_MAX);

	long		SetVScrollMax(long lMax);
	long		SetHScrollMax(long lMax);

	DECL_LINK( SpellError, LanguageType * );
	sal_Bool 			ExecSpellPopup( const Point& rPt );
    sal_Bool            ExecFieldPopup( const Point& rPt, sw::mark::IFieldmark *fieldBM );
    // SMARTTAGS
    sal_Bool            ExecSmartTagPopup( const Point& rPt );

	DECL_LINK( OnlineSpellCallback, SpellCallbackInfo*);
	sal_Bool			ExecDrwTxtSpellPopup(const Point& rPt);

	void			SetTabColFromDocPos( const Point &rPt ) { aTabColFromDocPos = rPt; }
	void			SetTabColFromDoc( sal_Bool b ) { bTabColFromDoc = b; }
    sal_Bool            IsTabColFromDoc() const    { return bTabColFromDoc; }
    void            SetTabRowFromDoc( sal_Bool b ) { bTabRowFromDoc = b; }
    sal_Bool            IsTabRowFromDoc() const    { return bTabRowFromDoc; }

    // -> #i23726#
    void            SetNumRuleNodeFromDoc( SwTxtNode * pNumRuleNode )
                    { pNumRuleNodeFromDoc = pNumRuleNode; }
    void            SetNumIndentFromDoc(sal_Bool b) { bNumIndentFromDoc = b; }
    sal_Bool            IsNumIndentFromDoc() const { return NULL != pNumRuleNodeFromDoc; }
    // <- #i23726#

    void	DocSzChgd( const Size& rNewSize );
	const 	Size&	GetDocSz() const { return aDocSz; }
	virtual void	SetVisArea( const Rectangle&, sal_Bool bUpdateScrollbar = sal_True);
			void	SetVisArea( const Point&, sal_Bool bUpdateScrollbar = sal_True);
			void	CheckVisArea();

	void RecheckBrowseMode();
    static LAYOUT_NS Dialog* GetSearchDialog();

	static sal_uInt16	GetMoveType();
	static void		SetMoveType(sal_uInt16 nSet);
    DECL_STATIC_LINK( SwView, MoveNavigationHdl, bool* ); // #i75416#
	static void		SetActMark(sal_Int32 nSet);

	sal_Bool 			HandleWheelCommands( const CommandEvent& );

	// Rahmen einfuegen
	void			InsFrmMode(sal_uInt16 nCols);

	void			SetZoom( SvxZoomType eZoomType, short nFactor = 100, sal_Bool bViewOnly = sal_False);
	virtual void	SetZoomFactor( const Fraction &rX, const Fraction & );

    void            SetViewLayout( sal_uInt16 nColumns, bool bBookMode, sal_Bool bViewOnly = sal_False );

    void            ShowHScrollbar(sal_Bool bShow);
    sal_Bool        IsHScrollbarVisible()const;

    void            ShowVScrollbar(sal_Bool bShow);
    sal_Bool        IsVScrollbarVisible()const;

    int             CreateVLineal();
    int             KillVLineal();
    int             CreateTab();
    int             KillTab();

    int             StatVLineal() const { return ((Window*)pVRuler)->IsVisible(); }
	void			ChangeVLinealMetric(FieldUnit eUnit);
    void            GetVLinealMetric(FieldUnit& rToFill) const;

    int             StatTab() const { return ((Window*)pHRuler)->IsVisible(); }
    SvxRuler&       GetHLineal()    { return *pHRuler; }
    SvxRuler&       GetVLineal()    { return *pVRuler; }
	void			InvalidateRulerPos();
	void			ChangeTabMetric(FieldUnit eUnit);
    void            GetHLinealMetric(FieldUnit& rToFill) const;

		// Handler
	void			Execute(SfxRequest&);
	void			ExecPageMove(SfxRequest&);
	void			ExecStyle(SfxRequest&);
	void			ExecLingu(SfxRequest&);
	void			ExecDataBase(SfxRequest&);
	void			ExecDlg(SfxRequest&);
	void			ExecDlgExt(SfxRequest&);
	void			ExecDBDlg(SfxRequest &);
	void			ExecColl(SfxRequest&);
	void			ExecutePrint(SfxRequest&);
	void 			ExecDraw(SfxRequest&);
	void 			ExecTabWin(SfxRequest&);
	void			ExecuteStatusLine(SfxRequest&);
	DECL_LINK( ExecRulerClick, Ruler * );
	void 			ExecSearch(SfxRequest&, sal_Bool bNoMessage = sal_False);
    void            ExecViewOptions(SfxRequest &);

    void            StateViewOptions(SfxItemSet &);
    void            StateSearch(SfxItemSet &);
	void			GetState(SfxItemSet&);
	void			StateStatusLine(SfxItemSet&);


	// Funktionen fuer Drawing
	void			SetDrawFuncPtr(SwDrawBase* pFuncPtr);
	inline SwDrawBase* GetDrawFuncPtr(/*sal_Bool bBuf = sal_False*/) const	{ return pDrawActual; }
	void 			GetDrawState(SfxItemSet &rSet);
	void			ExitDraw();
	inline sal_Bool		IsDrawRotate()		{ return bDrawRotate; }
	inline void		FlipDrawRotate()	{ bDrawRotate = !bDrawRotate; }
	inline sal_Bool		IsDrawSelMode() 	{ return bDrawSelMode; }
	void			SetSelDrawSlot();
	inline void		FlipDrawSelMode()	{ bDrawSelMode = !bDrawSelMode; }
	void			NoRotate();		// Rotate-Mode abschalten
	sal_Bool			EnterDrawTextMode(const Point& aDocPos);
    void            LeaveDrawCreate()   { nDrawSfxId = nFormSfxId = USHRT_MAX; sDrawCustom.Erase();}
	sal_Bool			IsDrawMode()		{ return (nDrawSfxId != USHRT_MAX || nFormSfxId != USHRT_MAX); }
	sal_Bool			IsFormMode() const;
	sal_Bool			IsBezierEditMode();
	sal_Bool			AreOnlyFormsSelected() const;
	sal_Bool			HasDrwObj(SdrObject *pSdrObj) const;
	sal_Bool			HasOnlyObj(SdrObject *pSdrObj, sal_uInt32 eObjInventor) const;
	sal_Bool			BeginTextEdit(	SdrObject* pObj, SdrPageView* pPV=NULL,
									Window* pWin=NULL, bool bIsNewObj=false, bool bSetSelectionToStart=false );

	void			StateTabWin(SfxItemSet&);

	// Attribute haben sich geaendert
	DECL_LINK( AttrChangedNotify, SwWrtShell * );

    // form control has been activated
    DECL_LINK( FormControlActivated, FmFormShell* );

	// Links bearbeiten
	void			EditLinkDlg();
	void			AutoCaption(const sal_uInt16 nType, const SvGlobalName *pOleId = 0);
	void			InsertCaption(const InsCaptionOpt *pOpt);

	// Async Aufruf durch Core
	void        UpdatePageNums(sal_uInt16 nPhyNum, sal_uInt16 nVirtNum, const String& rPgStr);

	String 		GetPageStr(sal_uInt16 nPhyNum, sal_uInt16 nVirtNum, const String& rPgStr);

	// Shell rausreichen
				 SfxShell		*GetCurShell()	{ return pShell; }
				 SwDocShell		*GetDocShell();
	inline const SwDocShell		*GetDocShell() const;
	inline		 FmFormShell	*GetFormShell()	{ return pFormShell; }
	inline const FmFormShell    *GetFormShell()	const { return pFormShell; }

	//damit in DToren der SubShells ggf. pShell zurueckgesetzt werden kann
	void ResetSubShell() 	{ pShell = 0; }

	virtual void	WriteUserData(String &, sal_Bool bBrowse = sal_False );
	virtual void	ReadUserData(const String &, sal_Bool bBrowse = sal_False );
    virtual void    ReadUserDataSequence ( const com::sun::star::uno::Sequence < com::sun::star::beans::PropertyValue >&, sal_Bool bBrowse );
    virtual void    WriteUserDataSequence ( com::sun::star::uno::Sequence < com::sun::star::beans::PropertyValue >&, sal_Bool bBrowse );

	void SetCrsrAtTop( sal_Bool bFlag, sal_Bool bCenter = sal_False )
		{ bTopCrsr = bFlag, bCenterCrsr = bCenter; }
	sal_Bool IsCrsrAtTop() const 					{ return bTopCrsr; }
	sal_Bool IsCrsrAtCenter() const 				{ return bCenterCrsr; }

	sal_Bool JumpToSwMark( const String& rMark );

	long InsertDoc( sal_uInt16 nSlotId, const String& rFileName,
					const String& rFilterName, sal_Int16 nVersion = 0 );

    void ExecuteInsertDoc( SfxRequest& rRequest, const SfxPoolItem* pItem );
    long InsertMedium( sal_uInt16 nSlotId, SfxMedium* pMedium, sal_Int16 nVersion );
    DECL_LINK( DialogClosedHdl, sfx2::FileDialogHelper * );

    // status methods for clipboard.
	// Status changes now notified from the clipboard.
	sal_Bool IsPasteAllowed();
	sal_Bool IsPasteSpecialAllowed();

    // Enable mail merge - mail merge field dialog enabled
    void EnableMailMerge(sal_Bool bEnable = sal_True);
    //apply Accessiblity options
    void ApplyAccessiblityOptions(SvtAccessibilityOptions& rAccessibilityOptions);

	SwView(SfxViewFrame* pFrame, SfxViewShell*);
	~SwView();

    void NotifyDBChanged();

    SfxObjectShellLock & GetTmpSelectionDoc();
    SfxObjectShellLock & GetOrCreateTmpSelectionDoc();

    void        AddTransferable(SwTransferable& rTransferable);

    // store MailMerge data while "Back to Mail Merge Wizard" FloatingWindow is active
    // or to support printing
    void   SetMailMergeConfigItem(SwMailMergeConfigItem*  pConfigItem, sal_uInt16 nRestart, sal_Bool bIsSource);
    SwMailMergeConfigItem*  GetMailMergeConfigItem();
    sal_uInt16              GetMailMergeRestartPage() const;
    sal_Bool                IsMailMergeSourceView() const;

    void ExecFormatPaintbrush(SfxRequest &);
    void StateFormatPaintbrush(SfxItemSet &);

    //public fuer D&D
    int     InsertGraphic( const String &rPath, const String &rFilter,
                            sal_Bool bLink = sal_True, GraphicFilter *pFlt = 0,
                            Graphic* pPreviewGrf = 0,
                            sal_Bool bRule = sal_False );

	void ExecuteScan( SfxRequest& rReq );

	SwPostItMgr* GetPostItMgr() { return mpPostItMgr;}
    const SwPostItMgr* GetPostItMgr() const { return mpPostItMgr;}
};

// ----------------- inline Methoden ----------------------

inline long SwView::GetXScroll() const
{
	return aVisArea.GetWidth() * nScrollX / 100L;
}

inline long SwView::GetYScroll() const
{
	return aVisArea.GetHeight() * nScrollY / 100L;
}

inline const SwDocShell	*SwView::GetDocShell() const
{
	return ((SwView*)this)->GetDocShell();
}

//***********************************************************

SfxTabPage* CreatePrintOptionsPage(	Window *pParent,
									const SfxItemSet &rOptions,
									sal_Bool bPreview);

#endif

