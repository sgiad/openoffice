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


#ifndef _NDGRF_HXX
#define _NDGRF_HXX
#include <sfx2/lnkbase.hxx>
#include <svtools/grfmgr.hxx>
#include <ndnotxt.hxx>
#include <com/sun/star/embed/XStorage.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
class SwAsyncRetrieveInputStreamThreadConsumer;

class SwGrfFmtColl;
class SwDoc;
class GraphicAttr;
class SvStorage;


class SW_DLLPUBLIC SwGrfNode: public SwNoTxtNode
{
    friend class SwNodes;

    GraphicObject maGrfObj;
    GraphicObject* mpReplacementGraphic;
    ::sfx2::SvBaseLinkRef refLink;       // falls Grafik nur als Link, dann Pointer gesetzt
    Size nGrfSize;
    sal_Bool bInSwapIn :1;

    sal_Bool bGrafikArrived :1;
    sal_Bool bChgTwipSize :1;
    sal_Bool bChgTwipSizeFromPixel :1;
    sal_Bool bLoadLowResGrf :1;
    sal_Bool bFrameInPaint :1;  // Um Start-/EndActions im Paint (ueber SwapIn zu verhindern.
    sal_Bool bScaleImageMap :1; // Image-Map in SetTwipSize skalieren

    boost::shared_ptr< SwAsyncRetrieveInputStreamThreadConsumer > mpThreadConsumer;
    bool mbLinkedInputStreamReady;
    com::sun::star::uno::Reference<com::sun::star::io::XInputStream> mxInputStream;
    sal_Bool mbIsStreamReadOnly;

	SwGrfNode( const SwNodeIndex& rWhere,
			   const String& rGrfName, const String& rFltName,
			   const Graphic* pGraphic,
			   SwGrfFmtColl* pGrfColl,
			   SwAttrSet* pAutoAttr = 0 );
	// Ctor fuer Einlesen (SW/G) ohne Grafik
	SwGrfNode( const SwNodeIndex& rWhere,
			   const String& rGrfName, const String& rFltName,
			   SwGrfFmtColl* pGrfColl,
			   SwAttrSet* pAutoAttr = 0 );
	SwGrfNode( const SwNodeIndex& rWhere,
			   const GraphicObject& rGrfObj,
			   SwGrfFmtColl* pGrfColl,
			   SwAttrSet* pAutoAttr = 0 );

	void InsertLink( const String& rGrfName, const String& rFltName );
	sal_Bool ImportGraphic( SvStream& rStrm );
    void _GetStreamStorageNames( String& rStrmName, String& rStgName ) const;
	void DelStreamName();
	DECL_LINK( SwapGraphic, GraphicObject* );

    /** helper method to determine stream for the embedded graphic.

        OD 2005-05-04 #i48434#
        Important note: caller of this method has to handle the thrown exceptions
        OD, MAV 2005-08-17 #i53025#
        Storage, which should contain the stream of the embedded graphic, is
        provided via parameter. Otherwise the returned stream will be closed
        after the the method returns, because its parent stream is closed and deleted.
        Proposed name of embedded graphic stream is also provided by parameter.

        @author OD

        @param _refPics
        input parameter - reference to storage, which should contain the
        embedded graphic stream.

        @param _aStrmName
        input parameter - proposed name of the embedded graphic stream.

        @return SvStream*
        new created stream of the embedded graphic, which has to be destroyed
        after its usage. Could be NULL, if the stream isn't found.
    */
    SvStream* _GetStreamForEmbedGrf(
            const ::com::sun::star::uno::Reference< ::com::sun::star::embed::XStorage >& _refPics,
            String& _aStrmName ) const;

    /** helper method to get a substorage of the document storage for readonly access.

        OD, MAV 2005-08-17 #i53025#
        A substorage with the specified name will be opened readonly. If the provided
        name is empty the root storage will be returned.

        @param _aStgName
        input parameter - name of substorage. Can be empty.

        @return XStorage
        reference to substorage or the root storage
    */
    ::com::sun::star::uno::Reference< ::com::sun::star::embed::XStorage > _GetDocSubstorageOrRoot(
                                                const String& aStgName ) const;

    /// allow reaction on change of content of GraphicObject, so always call
    /// when GraphicObject content changes
    void onGraphicChanged();

public:
	virtual ~SwGrfNode();
	const Graphic& 			GetGrf() const  	{ return maGrfObj.GetGraphic(); }
	const GraphicObject&	GetGrfObj() const  	{ return maGrfObj; }
    const GraphicObject* GetReplacementGrfObj() const;
    virtual SwCntntNode *SplitCntntNode( const SwPosition & );

    /// isolated only way to set GraphicObject to allow more actions when doing so
    void SetGraphic(const Graphic& rGraphic, const String& rLink);

    /// wrappers for non-const calls at GraphicObject
    void ReleaseGraphicFromCache() { maGrfObj.ReleaseFromCache(); }
    void StartGraphicAnimation(OutputDevice* pOut, const Point& rPt, const Size& rSz, long nExtraData = 0, const GraphicAttr* pAttr = NULL, sal_uLong nFlags = GRFMGR_DRAW_STANDARD, OutputDevice* pFirstFrameOutDev = NULL) { maGrfObj.StartAnimation(pOut, rPt, rSz, nExtraData, pAttr, nFlags, pFirstFrameOutDev); }
    void StopGraphicAnimation(OutputDevice* pOut = NULL, long nExtraData = 0) { maGrfObj.StopAnimation(pOut, nExtraData); }

    virtual Size GetTwipSize() const;
#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
	void SetTwipSize( const Size& rSz );

	sal_Bool IsTransparent() const;

	inline sal_Bool IsAnimated() const				{ return maGrfObj.IsAnimated(); }

	inline sal_Bool IsChgTwipSize() const			{ return bChgTwipSize; }
	inline sal_Bool IsChgTwipSizeFromPixel() const	{ return bChgTwipSizeFromPixel; }
	inline void SetChgTwipSize( sal_Bool b, sal_Bool bFromPx=sal_False ) 		{ bChgTwipSize = b; bChgTwipSizeFromPixel = bFromPx; }

	inline sal_Bool IsGrafikArrived() const			{ return bGrafikArrived; }
	inline void SetGrafikArrived( sal_Bool b ) 		{ bGrafikArrived = b; }

	inline sal_Bool IsFrameInPaint() const			{ return bFrameInPaint; }
	inline void SetFrameInPaint( sal_Bool b )		{ bFrameInPaint = b; }

	inline sal_Bool IsScaleImageMap() const			{ return bScaleImageMap; }
	inline void SetScaleImageMap( sal_Bool b )		{ bScaleImageMap = b; }
#endif
		// steht in ndcopy.cxx
	virtual SwCntntNode* MakeCopy( SwDoc*, const SwNodeIndex& ) const;
#ifndef _FESHVIEW_ONLY_INLINE_NEEDED

    // erneutes Einlesen, falls Graphic nicht Ok ist. Die
    // aktuelle wird durch die neue ersetzt.
	sal_Bool ReRead( const String& rGrfName, const String& rFltName,
                 const Graphic* pGraphic = 0,
                 const GraphicObject* pGrfObj = 0,
                 sal_Bool bModify = sal_True );
    // Laden der Grafik unmittelbar vor der Anzeige
    short SwapIn( sal_Bool bWaitForData = sal_False );
    // Entfernen der Grafik, um Speicher freizugeben
    short SwapOut();

    sal_Bool HasEmbeddedStreamName() const { return maGrfObj.HasUserData(); }
    // applying new stream name for embedded graphic - needed as saving the document might change this stream name
    void ApplyNewEmbeddedStreamName( const String& r )
    {
        maGrfObj.SetUserData( r );
    }

    // is this node selected by any shell?
    sal_Bool IsSelected() const;
#endif

		// Der Grafik sagen, dass sich der Node im Undobereich befindet
	virtual sal_Bool SavePersistentData();
	virtual sal_Bool RestorePersistentData();

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
		// Abfrage der Link-Daten
	sal_Bool IsGrfLink() const 					{ return refLink.Is(); }
	inline sal_Bool IsLinkedFile() const;
	inline sal_Bool IsLinkedDDE() const;
    ::sfx2::SvBaseLinkRef GetLink() const    { return refLink; }
	sal_Bool GetFileFilterNms( String* pFileNm, String* pFilterNm ) const;
	void ReleaseLink();

	// Skalieren einer Image-Map: Die Image-Map wird um den Faktor
	// zwischen Grafik-Groesse und Rahmen-Groesse vergroessert/verkleinert
	void ScaleImageMap();

	// returns the with our graphic attributes filled Graphic-Attr-Structure
	GraphicAttr& GetGraphicAttr( GraphicAttr&, const SwFrm* pFrm ) const;

#endif
    boost::weak_ptr< SwAsyncRetrieveInputStreamThreadConsumer > GetThreadConsumer();
    bool IsLinkedInputStreamReady() const;
    void TriggerAsyncRetrieveInputStream();
    void ApplyInputStream(
        com::sun::star::uno::Reference<com::sun::star::io::XInputStream> xInputStream,
        const sal_Bool bIsStreamReadOnly );
    void UpdateLinkWithInputStream();
    bool IsAsyncRetrieveInputStreamPossible() const;
};


// ----------------------------------------------------------------------
// Inline Metoden aus Node.hxx - erst hier ist der TxtNode bekannt !!
inline       SwGrfNode	 *SwNode::GetGrfNode()
{
	 return ND_GRFNODE == nNodeType ? (SwGrfNode*)this : 0;
}
inline const SwGrfNode   *SwNode::GetGrfNode() const
{
	 return ND_GRFNODE == nNodeType ? (const SwGrfNode*)this : 0;
}

#ifndef _FESHVIEW_ONLY_INLINE_NEEDED
inline sal_Bool SwGrfNode::IsLinkedFile() const
{
	return refLink.Is() && OBJECT_CLIENT_GRF == refLink->GetObjType();
}
inline sal_Bool SwGrfNode::IsLinkedDDE() const
{
	return refLink.Is() && OBJECT_CLIENT_DDE == refLink->GetObjType();
}
#endif


#endif
