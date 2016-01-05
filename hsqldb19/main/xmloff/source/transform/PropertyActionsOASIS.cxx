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
#include "precompiled_xmloff.hxx"
#include "xmloff/xmlnmspe.hxx"
#include "PropType.hxx"
#include "FamilyType.hxx"
#include "PropertyActionsOASIS.hxx"

using namespace ::xmloff::token;

#define NO_PARAMS 0, 0, 0

XMLTransformerActionInit aGraphicPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_SVG, XML_STROKE_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_MARKER_START_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_MARKER_END_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_SHADOW_OFFSET_X, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_SHADOW_OFFSET_Y, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_SHADOW_OPACITY, 
				XML_ATACTION_RENAME_NEG_PERCENT, 
				XMLTransformerActionInit::QNameParam( XML_NAMESPACE_DRAW,
			   								  XML_SHADOW_TRANSPARENCY), 0, 0 },
	{ XML_NAMESPACE_DRAW, XML_GUIDE_OVERHANG, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_START_GUIDE, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_END_GUIDE, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_CAPTION_ESCAPE, XML_ATACTION_CAPTION_ESCAPE_OASIS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_CAPTION_LINE_LENGTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DR3D, XML_DEPTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_SVG, XML_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_SVG, XML_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MAX_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MAX_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_SHADOW, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS },
	{ XML_NAMESPACE_FO, XML_CLIP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
//	{ XML_NAMESPACE_STYLE, XML_WRAP_DYNAMIC_TRESHOLD, XML_ATACTION_REMOVE, 
//	  	NO_PARAMS }, /* generated entry */ // TODO
	{ XML_NAMESPACE_DRAW, XML_VISIBLE_AREA_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_VISIBLE_AREA_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_VISIBLE_AREA_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_VISIBLE_AREA_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_START_LINE_SPACING_HORIZONTAL, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_START_LINE_SPACING_VERTICAL, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_END_LINE_SPACING_HORIZONTAL, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_END_LINE_SPACING_VERTICAL, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_LINE_DISTANCE, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_GUIDE_DISTANCE, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_CAPTION_GAP, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_SVG, XML_X, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_SVG, XML_Y, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_STROKE_DASH, XML_ATACTION_DECODE_STYLE_NAME_REF,
		XML_FAMILY_TYPE_STROKE_DASH, 0, 0 },
	{ XML_NAMESPACE_DRAW, XML_MARKER_START, XML_ATACTION_DECODE_STYLE_NAME_REF,
		XML_FAMILY_TYPE_MARKER, 0, 0 },
	{ XML_NAMESPACE_DRAW, XML_MARKER_END, XML_ATACTION_DECODE_STYLE_NAME_REF,
		XML_FAMILY_TYPE_MARKER, 0, 0 },
	{ XML_NAMESPACE_DRAW, XML_FILL_GRADIENT_NAME, XML_ATACTION_DECODE_STYLE_NAME_REF,
		XML_FAMILY_TYPE_GRADIENT, 0, 0 },

	// #i25616#
	{ XML_NAMESPACE_DRAW, XML_OPACITY, XML_OPTACTION_OPACITY, NO_PARAMS },
	{ XML_NAMESPACE_DRAW, XML_IMAGE_OPACITY, XML_OPTACTION_IMAGE_OPACITY, NO_PARAMS },

	{ XML_NAMESPACE_DRAW, XML_STROKE_LINEJOIN, XML_ATACTION_RENAME, 
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_SVG,
			   								  XML_STROKE_LINEJOIN), 0, 0 },
	{ XML_NAMESPACE_DRAW, XML_OPACITY_NAME, 
				XML_ATACTION_RENAME_DECODE_STYLE_NAME_REF,
				XMLTransformerActionInit::QNameParam( XML_NAMESPACE_DRAW,
			   								  XML_TRANSPARENCY_NAME), 
				XML_FAMILY_TYPE_GRADIENT, 0 },
	{ XML_NAMESPACE_DRAW, XML_FILL_HATCH_NAME, XML_ATACTION_DECODE_STYLE_NAME_REF,
		XML_FAMILY_TYPE_HATCH, 0, 0 },
	{ XML_NAMESPACE_DRAW, XML_FILL_IMAGE_NAME, XML_ATACTION_DECODE_STYLE_NAME_REF,
		XML_FAMILY_TYPE_FILL_IMAGE, 0, 0 },

	// Font work properties
	{ XML_NAMESPACE_DRAW, XML_FONTWORK_DISTANCE, XML_ATACTION_IN2INCH, NO_PARAMS },
	{ XML_NAMESPACE_DRAW, XML_FONTWORK_START, XML_ATACTION_IN2INCH, NO_PARAMS },
	{ XML_NAMESPACE_DRAW, XML_FONTWORK_SHADOW_OFFSET_X, XML_ATACTION_IN2INCH, NO_PARAMS },
	{ XML_NAMESPACE_DRAW, XML_FONTWORK_SHADOW_OFFSET_Y, XML_ATACTION_IN2INCH, NO_PARAMS },

	{ XML_NAMESPACE_DRAW, XML_AUTO_GROW_WIDTH, XML_ATACTION_RENAME,
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_DRAW,
			   								  XML_AUTO_GROW_HEIGHT	), 0, 0 },
	{ XML_NAMESPACE_DRAW, XML_AUTO_GROW_HEIGHT, XML_ATACTION_RENAME,
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_DRAW,
			   								  XML_AUTO_GROW_WIDTH	), 0, 0 },
    { XML_NAMESPACE_PRESENTATION, XML_DURATION, XML_ATACTION_RNG2ISO_DATETIME, NO_PARAMS },
    { XML_NAMESPACE_TEXT, XML_ANIMATION_DELAY, XML_ATACTION_RNG2ISO_DATETIME, NO_PARAMS },

	{ XML_NAMESPACE_STYLE, XML_PROTECT, XML_ATACTION_DECODE_PROTECT, NO_PARAMS },
	{ XML_NAMESPACE_STYLE, XML_MIRROR, XML_ATACTION_DRAW_MIRROR_OASIS, NO_PARAMS },
	{ XML_NAMESPACE_DRAW, XML_GAMMA, XML_ATACTION_GAMMA_OASIS, NO_PARAMS },
	{ XML_NAMESPACE_SVG, XML_STROKE_OPACITY, XML_ATACTION_OPACITY_FIX, NO_PARAMS },

	{ XML_NAMESPACE_STYLE, XML_FLOW_WITH_TEXT, XML_ATACTION_REMOVE, 
		NO_PARAMS },
	{ XML_NAMESPACE_DRAW, XML_WRAP_INFLUENCE_ON_POSITION, XML_ATACTION_REMOVE, 
		NO_PARAMS },

	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aDrawingPagePropertyOASISAttrActionTable[] =
{
	// style-graphic-fill-properties-attlist
	{ XML_NAMESPACE_DRAW, XML_FILL_GRADIENT_NAME, XML_ATACTION_DECODE_STYLE_NAME_REF,
		NO_PARAMS  },
	{ XML_NAMESPACE_DRAW, XML_FILL_HATCH_NAME, XML_ATACTION_DECODE_STYLE_NAME_REF, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_FILL_IMAGE_NAME, XML_ATACTION_DECODE_STYLE_NAME_REF,
		NO_PARAMS  },
	{ XML_NAMESPACE_DRAW, XML_FILL_IMAGE_WIDTH, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_DRAW, XML_FILL_IMAGE_HEIGHT, XML_ATACTION_IN2INCH, NO_PARAMS }, /* generated entry */

	{ XML_NAMESPACE_PRESENTATION, XML_DISPLAY_HEADER, XML_ATACTION_REMOVE, NO_PARAMS },
	{ XML_NAMESPACE_PRESENTATION, XML_DISPLAY_FOOTER, XML_ATACTION_REMOVE, NO_PARAMS },
	{ XML_NAMESPACE_PRESENTATION, XML_DISPLAY_PAGE_NUMBER, XML_ATACTION_REMOVE, NO_PARAMS },
	{ XML_NAMESPACE_PRESENTATION, XML_DISPLAY_DATE_TIME, XML_ATACTION_REMOVE, NO_PARAMS },

	{ XML_NAMESPACE_SMIL, XML_TYPE, XML_ATACTION_REMOVE, NO_PARAMS },
	{ XML_NAMESPACE_SMIL, XML_SUBTYPE, XML_ATACTION_REMOVE, NO_PARAMS },
	{ XML_NAMESPACE_SMIL, XML_DIRECTION, XML_ATACTION_REMOVE, NO_PARAMS },
	{ XML_NAMESPACE_SMIL, XML_FADECOLOR, XML_ATACTION_REMOVE, NO_PARAMS },

	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aPageLayoutPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_FO, XML_PAGE_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PAGE_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_SHADOW, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS },
	{ XML_NAMESPACE_STYLE, XML_FOOTNOTE_MAX_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_LAYOUT_GRID_BASE_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_LAYOUT_GRID_RUBY_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_REGISTER_TRUTH_REF_STYLE_NAME, XML_ATACTION_DECODE_STYLE_NAME_REF, XML_FAMILY_TYPE_PARAGRAPH, 0, 0 },
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aHeaderFooterPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_SVG, XML_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MIN_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_SHADOW, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS },
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aTextPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_FO, XML_FONT_SIZE, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_FONT_SIZE_ASIAN, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_FONT_SIZE_COMPLEX, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_FONT_SIZE_REL, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_FONT_SIZE_REL_ASIAN, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_FONT_SIZE_REL_COMPLEX, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_LETTER_SPACING, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_TEXT_SHADOW, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS },
	{ XML_NAMESPACE_STYLE, XML_TEXT_UNDERLINE_TYPE, 
		XML_OPTACTION_UNDERLINE_TYPE, NO_PARAMS }, /* new attribute */
	{ XML_NAMESPACE_STYLE, XML_TEXT_UNDERLINE_STYLE,
		XML_OPTACTION_UNDERLINE_STYLE, NO_PARAMS }, /* new attribute */
	{ XML_NAMESPACE_STYLE, XML_TEXT_UNDERLINE_WIDTH, 
		XML_OPTACTION_UNDERLINE_WIDTH, NO_PARAMS }, /* new attribute */
	{ XML_NAMESPACE_STYLE, XML_TEXT_UNDERLINE_MODE, 
		XML_OPTACTION_LINE_MODE, NO_PARAMS },
	{ XML_NAMESPACE_STYLE, XML_TEXT_LINE_THROUGH_TYPE, 
		XML_OPTACTION_LINETHROUGH_TYPE, NO_PARAMS }, /* new entry*/
	{ XML_NAMESPACE_STYLE, XML_TEXT_LINE_THROUGH_STYLE, 
		XML_OPTACTION_LINETHROUGH_STYLE, NO_PARAMS }, /* new entry*/
	{ XML_NAMESPACE_STYLE, XML_TEXT_LINE_THROUGH_WIDTH, 
		XML_OPTACTION_LINETHROUGH_WIDTH, NO_PARAMS }, /* new entry*/
	{ XML_NAMESPACE_STYLE, XML_TEXT_LINE_THROUGH_COLOR, 
		XML_ATACTION_REMOVE, NO_PARAMS }, /* new entry*/
	{ XML_NAMESPACE_STYLE, XML_TEXT_LINE_THROUGH_TEXT, 
		XML_OPTACTION_LINETHROUGH_TEXT, NO_PARAMS }, /* new entry*/
	{ XML_NAMESPACE_STYLE, XML_TEXT_LINE_THROUGH_TEXT_STYLE, 
		XML_ATACTION_REMOVE, NO_PARAMS }, /* new entry*/
	{ XML_NAMESPACE_STYLE, XML_TEXT_LINE_THROUGH_MODE,
		XML_OPTACTION_LINE_MODE, NO_PARAMS },
	{ XML_NAMESPACE_FO, XML_BACKGROUND_COLOR, XML_ATACTION_RENAME, 
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_STYLE,
			   								  XML_TEXT_BACKGROUND_COLOR	), 0, 0 },
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aParagraphPropertyOASISAttrActionTable[] =
{
    { XML_NAMESPACE_FO, XML_TEXT_ALIGN, XML_OPTACTION_CONTROL_TEXT_ALIGN,
        NO_PARAMS },
	{ XML_NAMESPACE_FO, XML_LINE_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_LINE_HEIGHT_AT_LEAST, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_LINE_SPACING, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_TAB_STOP_DISTANCE, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_TEXT_INDENT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_SHADOW, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS },
	{ XML_NAMESPACE_FO, XML_KEEP_WITH_NEXT, XML_OPTACTION_KEEP_WITH_NEXT, 
	  	NO_PARAMS },
    { XML_NAMESPACE_FO, XML_KEEP_TOGETHER, XML_OPTACTION_KEEP_TOGETHER,
        NO_PARAMS },
//	{ XML_NAMESPACE_STYLE, XML_WRITING_MODE, XML_OPTACTION_DRAW_WRITING_MODE, 0 },
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aSectionPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_FO, XML_MARGIN_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aTablePropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_STYLE, XML_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_KEEP_WITH_NEXT, XML_OPTACTION_KEEP_WITH_NEXT, 
	  	NO_PARAMS },
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aTableColumnPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_STYLE, XML_COLUMN_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aTableRowPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_STYLE, XML_ROW_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_MIN_ROW_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aTableCellPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_STYLE, XML_VERTICAL_ALIGN, XML_ATACTION_RENAME, 
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_FO,
			   								  XML_VERTICAL_ALIGN ), 0, 0 },
	{ XML_NAMESPACE_FO, XML_BORDER, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_BORDER_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_TOP, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_BOTTOM, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_LEFT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_BORDER_LINE_WIDTH_RIGHT, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_DIAGONAL_BL_TR, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_DIAGONAL_BL_TR_WIDTH, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_DIAGONAL_TL_BR, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_DIAGONAL_TL_BR_WIDTH, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_TOP, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_BOTTOM, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_PADDING_RIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_MARGIN_LEFT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_DIRECTION, XML_ATACTION_RENAME, 
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_FO,
			   								  XML_DIRECTION), 0, 0 },
	{ XML_NAMESPACE_STYLE, XML_SHADOW, XML_ATACTION_INS2INCHS, 
	  	NO_PARAMS },
	{ XML_NAMESPACE_STYLE, XML_REPEAT_CONTENT, XML_ATACTION_REMOVE, 
        NO_PARAMS }, /* new entry*/
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aListLevelPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_TEXT, XML_SPACE_BEFORE, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_TEXT, XML_MIN_LABEL_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_TEXT, XML_MIN_LABEL_DISTANCE, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_FO, XML_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};

XMLTransformerActionInit aChartPropertyOASISAttrActionTable[] =
{
	{ XML_NAMESPACE_CHART, XML_SYMBOL_WIDTH, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_CHART, XML_SYMBOL_HEIGHT, XML_ATACTION_IN2INCH, 
	  	NO_PARAMS }, /* generated entry */
	{ XML_NAMESPACE_STYLE, XML_DIRECTION, XML_ATACTION_RENAME,
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_FO,
			   								  XML_DIRECTION ), 0, 0 },
	{ XML_NAMESPACE_CHART, XML_INTERPOLATION, XML_OPTACTION_INTERPOLATION, NO_PARAMS },
	{ XML_NAMESPACE_STYLE, XML_ROTATION_ANGLE, XML_ATACTION_RENAME,
		XMLTransformerActionInit::QNameParam( XML_NAMESPACE_TEXT,
			   								  XML_ROTATION_ANGLE ), 0, 0 },
    { XML_NAMESPACE_CHART, XML_INTERVAL_MAJOR, XML_OPTACTION_INTERVAL_MAJOR, NO_PARAMS },
    { XML_NAMESPACE_CHART, XML_INTERVAL_MINOR_DIVISOR, XML_OPTACTION_INTERVAL_MINOR_DIVISOR,
      NO_PARAMS },
 	{ XML_NAMESPACE_CHART, XML_JAPANESE_CANDLE_STICK, XML_ATACTION_RENAME,
      XMLTransformerActionInit::QNameParam( XML_NAMESPACE_CHART,
                                            XML_STOCK_UPDOWN_BARS ), 0, 0 },
	{ XML_NAMESPACE_CHART, XML_SYMBOL_TYPE, XML_OPTACTION_SYMBOL_TYPE, NO_PARAMS },
	{ XML_NAMESPACE_CHART, XML_SYMBOL_NAME, XML_OPTACTION_SYMBOL_NAME, NO_PARAMS },

	{ XML_NAMESPACE_OFFICE, XML_TOKEN_INVALID, XML_ATACTION_EOT, NO_PARAMS }
};
