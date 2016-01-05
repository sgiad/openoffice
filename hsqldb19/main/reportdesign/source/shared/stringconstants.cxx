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


#include "precompiled_reportdesign.hxx"

#include  "stringconstants.hrc"

//============================================================
//= service names
//============================================================
IMPLEMENT_CONSTASCII_USTRING(SERVICE_FIXEDTEXT			, "com.sun.star.report.FixedText");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_FORMATTEDFIELD		, "com.sun.star.report.FormattedField");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_IMAGECONTROL		, "com.sun.star.report.ImageControl");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_FORMATCONDITION	, "com.sun.star.report.FormatCondition");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_REPORTENGINE   	, "com.sun.star.report.ReportEngine");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_FUNCTION          	, "com.sun.star.report.Function");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_REPORTDEFINITION   , "com.sun.star.report.ReportDefinition");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_SHAPE              , "com.sun.star.report.Shape");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_FIXEDLINE          , "com.sun.star.report.FixedLine");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_SECTION            , "com.sun.star.report.Section");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_GROUP              , "com.sun.star.report.Group");
IMPLEMENT_CONSTASCII_USTRING(SERVICE_OLEOBJECT          , "com.sun.star.report.OleObject");

//============================================================
//= property names
//============================================================
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_VISIBLE			, "Visible");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_NAME				, "Name");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_HEIGHT			, "Height");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BACKCOLOR			, "BackColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BACKTRANSPARENT	, "BackTransparent");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CONTROLBACKGROUND	, "ControlBackground");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CONTROLBACKGROUNDTRANSPARENT	, "ControlBackgroundTransparent");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FORCENEWPAGE		, "ForceNewPage");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_NEWROWORCOL		, "NewRowOrCol");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_KEEPTOGETHER		, "KeepTogether");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CANGROW			, "CanGrow");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CANSHRINK			, "CanShrink");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_REPEATSECTION		, "RepeatSection");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_GROUP				, "Group");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_REPORTDEFINITION	, "ReportDefinition");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_HEADER			, "Header");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FOOTER			, "Footer");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_GROUPINTERVAL		, "GroupInterval");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_EXPRESSION		, "Expression");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_GROUPON			, "GroupOn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_SORTASCENDING		, "SortAscending");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_GROUPS			, "Groups");


IMPLEMENT_CONSTASCII_USTRING(PROPERTY_MASTERFIELDS			, "MasterFields");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_DETAILFIELDS			, "DetailFields");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_REPORTHEADER			, "ReportHeader");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_REPORTFOOTER			, "ReportFooter");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAGEHEADER			, "PageHeader");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAGEFOOTER			, "PageFooter");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_DETAIL				, "Detail");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CAPTION				, "Caption");	 
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BACKGRAPHICURL		, "BackGraphicURL");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_COMMAND				, "Command");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BACKGRAPHICLOCATION	, "BackGraphicLocation");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ORIENTATION			, "Orientation");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAPERFORMAT			, "PaperFormat");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAPERSIZE				, "Size");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_GROUPKEEPTOGETHER		, "GroupKeepTogether");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAGEHEADEROPTION		, "PageHeaderOption");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAGEFOOTEROPTION		, "PageFooterOption");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_COMMANDTYPE			, "CommandType");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_REPORTHEADERON		, "ReportHeaderOn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_REPORTFOOTERON		, "ReportFooterOn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAGEHEADERON			, "PageHeaderOn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAGEFOOTERON			, "PageFooterOn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_HEADERON				, "HeaderOn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FOOTERON				, "FooterOn");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_WIDTH					, "Width");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_POSITIONX				, "PositionX");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_POSITIONY				, "PositionY");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_DATAFIELD				, "DataField");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PARAADJUST			, "ParaAdjust");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ALIGN					, "Align");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTDESCRIPTOR		, "FontDescriptor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTDESCRIPTORASIAN	, "FontDescriptorAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTDESCRIPTORCOMPLEX , "FontDescriptorComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CONTROLTEXTEMPHASISMARK		, "ControlTextEmphasis");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARRELIEF			, "CharRelief");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARCOLOR				, "CharColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_VERTICALALIGN			, "VerticalAlign");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_IMAGEPOSITION			, "ImagePosition");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_IMAGEURL				, "ImageURL");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARUNDERLINECOLOR	, "CharUnderlineColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LABEL					, "Label");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_EFFECTIVEDEFAULT		, "EffectiveDefault");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_EFFECTIVEMAX			, "EffectiveMax");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_EFFECTIVEMIN			, "EffectiveMin");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FORMATKEY				, "FormatKey");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_MAXTEXTLEN			, "MaxTextLen");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LISTSOURCE			, "ListSource");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FORMATSSUPPLIER		, "FormatsSupplier");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CONTROLBORDER			, "ControlBorder");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CONTROLBORDERCOLOR	, "ControlBorderColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BORDER			    , "Border");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BORDERCOLOR	        , "BorderColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_DEFAULTCONTROL		, "DefaultControl");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LEFTMARGIN			, "LeftMargin");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_RIGHTMARGIN			, "RightMargin");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TOPMARGIN				, "TopMargin");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BOTTOMMARGIN			, "BottomMargin");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PRINTREPEATEDVALUES	, "PrintRepeatedValues");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CONDITIONALPRINTEXPRESSION	, "ConditionalPrintExpression");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_SHAPE             	, "Shape");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_STARTNEWCOLUMN		, "StartNewColumn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_RESETPAGENUMBER		, "ResetPageNumber");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PRINTWHENGROUPCHANGE		, "PrintWhenGroupChange");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_STATE					, "State");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TIME_STATE			, "TimeState");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_DATE_STATE			, "DateState");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TRISTATE				, "TriState");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LISTSOURCETYPE		, "ListSourceType");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTCHARWIDTH,	"FontCharWidth");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTCHARSET,		"CharFontCharSet");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTFAMILY,		"CharFontFamily");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTHEIGHT,	"CharHeight");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTHEIGHT,		"FontHeight");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTKERNING,		"FontKerning");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONT,			    "FontDescriptor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTNAME,			"FontName");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTORIENTATION,	"CharRotation");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTPITCH,		"CharFontPitch");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTSLANT,		"FontSlant");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARSTRIKEOUT,	"CharStrikeout");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTSTRIKEOUT,	"FontStrikeout");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTSTYLENAME,	"CharFontStyleName");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTUNDERLINE,	"CharUnderline");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTWEIGHT,		"CharWeight");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTWIDTH,		"FontWidth");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTWORDLINEMODE,	"FontWordLineMode");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTTYPE,			"FontType"); 

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ENABLED	,		"Enabled"); 

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHAREMPHASIS,		"CharEmphasis");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTNAME,		"CharFontName");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTSTYLENAME,"CharFontStyleName");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTFAMILY,	"CharFontFamily");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTCHARSET,	"CharFontCharSet");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTPITCH,	"CharFontPitch");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARHEIGHT,		"CharHeight");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARUNDERLINE,	"CharUnderline");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARWEIGHT,		"CharWeight");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARPOSTURE,		"CharPosture");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARWORDMODE,		"CharWordMode");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARROTATION,		"CharRotation");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARSCALEWIDTH,	"CharScaleWidth");

// Asian
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHAREMPHASISASIAN,		"CharEmphasisAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTNAMEASIAN,		"CharFontNameAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTSTYLENAMEASIAN,   "CharFontStyleNameAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTFAMILYASIAN,	    "CharFontFamilyAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTCHARSETASIAN,	    "CharFontCharSetAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTPITCHASIAN,	    "CharFontPitchAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARHEIGHTASIAN,		    "CharHeightAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARUNDERLINEASIAN,	    "CharUnderlineAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARWEIGHTASIAN,		    "CharWeightAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARPOSTUREASIAN,		    "CharPostureAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARWORDMODEASIAN,		"CharWordModeAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARROTATIONASIAN,		"CharRotationAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARSCALEWIDTHASIAN,	    "CharScaleWidthAsian");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARLOCALEASIAN,           "CharLocaleAsian");

// Complex
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHAREMPHASISCOMPLEX,		"CharEmphasisComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTNAMECOMPLEX,		"CharFontNameComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTSTYLENAMECOMPLEX, "CharFontStyleNameComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTFAMILYCOMPLEX,	"CharFontFamilyComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTCHARSETCOMPLEX,	"CharFontCharSetComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFONTPITCHCOMPLEX,	    "CharFontPitchComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARHEIGHTCOMPLEX,		"CharHeightComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARUNDERLINECOMPLEX,	    "CharUnderlineComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARWEIGHTCOMPLEX,		"CharWeightComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARPOSTURECOMPLEX,		"CharPostureComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARWORDMODECOMPLEX,		"CharWordModeComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARROTATIONCOMPLEX,		"CharRotationComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARSCALEWIDTHCOMPLEX,	"CharScaleWidthComplex");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARLOCALECOMPLEX,        "CharLocaleComplex");


IMPLEMENT_CONSTASCII_USTRING(PROPERTY_STATUSINDICATOR,	"StatusIndicator");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_SECTION,	        "Section");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FILTER,	        "Filter");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_MULTILINE,	    "MultiLine");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ESCAPEPROCESSING,	"EscapeProcessing");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ACTIVECONNECTION,	"ActiveConnection");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_DATASOURCENAME,	"DataSourceName");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FORMULA,	        "Formula");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_INITIALFORMULA,	"InitialFormula");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PREEVALUATED,	    "PreEvaluated");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_DEEPTRAVERSING,	"DeepTraversing");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_MIMETYPE,	        "MimeType");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_BACKGROUNDCOLOR,  "BackgroundColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TEXT,             "Text");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TEXTCOLOR,        "TextColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TEXTLINECOLOR	,   "TextLineColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTRELIEF	,   "FontRelief");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_FONTEMPHASISMARK, "FontEmphasisMark");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ZORDER,           "ZOrder");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_OPAQUE,           "Opaque");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TRANSFORMATION,    "Transformation");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CUSTOMSHAPEENGINE, "CustomShapeEngine");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CUSTOMSHAPEDATA,   "CustomShapeData");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CUSTOMSHAPEGEOMETRY,"CustomShapeGeometry");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_NUMBERINGTYPE,     "NumberingType");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PAGESTYLELAYOUT,   "PageStyleLayout");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ISLANDSCAPE,       "IsLandscape");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_TYPE            ,  "Type");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LINESTYLE       ,  "LineStyle");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LINEDASH        ,  "LineDash");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LINECOLOR       ,  "LineColor");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LINETRANSPARENCE,  "LineTransparence");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_LINEWIDTH       ,  "LineWidth");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_PRESERVEIRI     ,  "PreserveIRI");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_SCALEMODE       ,  "ScaleMode");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARFLASH,            "CharFlash");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARESCAPEMENTHEIGHT, "CharEscapementHeight");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARLOCALE,           "CharLocale");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARESCAPEMENT,       "CharEscapement");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARCASEMAP,          "CharCaseMap");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARCOMBINEISON,      "CharCombineIsOn");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARCOMBINEPREFIX,    "CharCombinePrefix");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARCOMBINESUFFIX,    "CharCombineSuffix");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARHIDDEN,           "CharHidden");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARSHADOWED,         "CharShadowed");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARCONTOURED,        "CharContoured");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARAUTOKERNING,		"CharAutoKerning");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_CHARKERNING,          "CharKerning");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_HYPERLINKURL        , "HyperLinkURL");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_HYPERLINKTARGET     , "HyperLinkTarget");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_HYPERLINKNAME       , "HyperLinkName");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_VISITEDCHARSTYLENAME, "VisitedCharStyleName");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_UNVISITEDCHARSTYLENAME, "UnvisitedCharStyleName");

IMPLEMENT_CONSTASCII_USTRING(PROPERTY_ORDER,                "Order");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_APPLYFILTER,          "ApplyFilter");
IMPLEMENT_CONSTASCII_USTRING(PROPERTY_MAXROWS,              "MaxRows");
