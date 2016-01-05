#**************************************************************
#  
#  Licensed to the Apache Software Foundation (ASF) under one
#  or more contributor license agreements.  See the NOTICE file
#  distributed with this work for additional information
#  regarding copyright ownership.  The ASF licenses this file
#  to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance
#  with the License.  You may obtain a copy of the License at
#  
#    http://www.apache.org/licenses/LICENSE-2.0
#  
#  Unless required by applicable law or agreed to in writing,
#  software distributed under the License is distributed on an
#  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
#  KIND, either express or implied.  See the License for the
#  specific language governing permissions and limitations
#  under the License.
#  
#**************************************************************



PRJ=..$/..$/..$/..

PRJNAME=offapi

TARGET=csssheet
PACKAGE=com$/sun$/star$/sheet

# --- Settings -----------------------------------------------------
.INCLUDE :  $(PRJ)$/util$/makefile.pmk

# ------------------------------------------------------------------------

IDLFILES=\
	AccessibleCell.idl\
	AccessibleCsvCell.idl\
	AccessibleCsvRuler.idl\
	AccessibleCsvTable.idl\
	AccessiblePageHeaderFooterAreasView.idl\
	AccessibleSpreadsheet.idl\
	AccessibleSpreadsheetDocumentView.idl\
	AccessibleSpreadsheetPageView.idl\
	ActivationEvent.idl\
	AddressConvention.idl\
	AddIn.idl\
	Border.idl\
	CellAnnotation.idl\
	CellAnnotationShape.idl\
	CellAnnotations.idl\
	CellAnnotationsEnumeration.idl\
	CellAreaLink.idl\
	CellAreaLinks.idl\
	CellAreaLinksEnumeration.idl\
	CellDeleteMode.idl\
	CellFlags.idl\
	CellFormatRanges.idl\
	CellFormatRangesEnumeration.idl\
	CellInsertMode.idl\
	Cells.idl\
	CellsEnumeration.idl\
	ComplexReference.idl\
	ConditionOperator.idl\
	ConsolidationDescriptor.idl\
	DDEItemInfo.idl\
	DDELink.idl\
	DDELinkInfo.idl\
	DDELinkMode.idl\
	DDELinks.idl\
	DDELinksEnumeration.idl\
	DataImportMode.idl\
	DataPilotDescriptor.idl\
	DataPilotField.idl\
	DataPilotFieldAutoShowInfo.idl\
	DataPilotFieldFilter.idl\
	DataPilotFieldGroup.idl\
	DataPilotFieldGroupBy.idl\
	DataPilotFieldGroupEnumeration.idl\
	DataPilotFieldGroupInfo.idl\
	DataPilotFieldGroupItem.idl\
	DataPilotFieldGroups.idl\
	DataPilotFieldGroupsEnumeration.idl\
	DataPilotFieldLayoutInfo.idl\
	DataPilotFieldLayoutMode.idl\
	DataPilotFieldOrientation.idl\
	DataPilotFieldReference.idl\
	DataPilotFieldReferenceItemType.idl\
	DataPilotFieldReferenceType.idl\
	DataPilotFieldShowItemsMode.idl\
	DataPilotFieldSortInfo.idl\
	DataPilotFieldSortMode.idl\
	DataPilotFields.idl\
	DataPilotFieldsEnumeration.idl\
	DataPilotItem.idl\
	DataPilotItems.idl\
	DataPilotItemsEnumeration.idl\
	DataPilotOutputRangeType.idl\
	DataPilotSource.idl\
	DataPilotSourceDimension.idl\
	DataPilotSourceDimensions.idl\
	DataPilotSourceHierarchies.idl\
	DataPilotSourceHierarchy.idl\
	DataPilotSourceLevel.idl\
	DataPilotSourceLevels.idl\
	DataPilotSourceMember.idl\
	DataPilotSourceMembers.idl\
	DataPilotTable.idl\
	DataPilotTableHeaderData.idl\
	DataPilotTablePositionData.idl\
	DataPilotTablePositionType.idl\
	DataPilotTableResultData.idl\
	DataPilotTables.idl\
	DataPilotTablesEnumeration.idl\
	DataResult.idl\
	DataResultFlags.idl\
	DatabaseImportDescriptor.idl\
	DatabaseRange.idl\
	DatabaseRanges.idl\
	DatabaseRangesEnumeration.idl\
    DimensionFlags.idl\
	DocumentSettings.idl\
 	ExternalDocLink.idl\
 	ExternalDocLinks.idl\
	ExternalLinkType.idl\
	ExternalLinkInfo.idl\
	ExternalReference.idl\
 	ExternalSheetCache.idl\
	FillDateMode.idl\
	FillDirection.idl\
	FillMode.idl\
	FilterConnection.idl\
	FilterFormulaParser.idl\
	FilterOperator.idl\
	FilterOperator2.idl\
	FormulaLanguage.idl\
	FormulaMapGroup.idl\
	FormulaMapGroupSpecialOffset.idl\
	FormulaOpCodeMapEntry.idl\
	FormulaParser.idl\
	FormulaResult.idl\
	FormulaToken.idl\
	FunctionAccess.idl\
	FunctionArgument.idl\
	FunctionCategory.idl\
	FunctionDescription.idl\
	FunctionDescriptionEnumeration.idl\
	FunctionDescriptions.idl\
	GeneralFunction.idl\
	GlobalSheetSettings.idl\
	GoalResult.idl\
	HeaderFooterContent.idl\
	LabelRange.idl\
	LabelRanges.idl\
	LabelRangesEnumeration.idl\
	LocalizedName.idl\
	MemberResult.idl\
	MemberResultFlags.idl\
	MoveDirection.idl\
	NamedRange.idl\
	NamedRangeFlag.idl\
	NamedRanges.idl\
	NamedRangesEnumeration.idl\
	NoConvergenceException.idl\
	PasteOperation.idl\
	RangeSelectionArguments.idl\
	RangeSelectionEvent.idl\
	RecentFunctions.idl\
	ReferenceFlags.idl\
	ResultEvent.idl\
	Scenario.idl\
	Scenarios.idl\
	ScenariosEnumeration.idl\
	Shape.idl\
	SheetCell.idl\
	SheetCellCursor.idl\
	SheetCellRange.idl\
	SheetCellRanges.idl\
	SheetCellRangesEnumeration.idl\
	SheetFilterDescriptor.idl\
	SheetLink.idl\
	SheetLinkMode.idl\
	SheetLinks.idl\
	SheetLinksEnumeration.idl\
	SheetRangesQuery.idl\
	SheetSortDescriptor.idl\
	SheetSortDescriptor2.idl\
	SingleReference.idl\
    Solver.idl\
    SolverConstraint.idl\
    SolverConstraintOperator.idl\
	Spreadsheet.idl\
	SpreadsheetDocument.idl\
	SpreadsheetDocumentSettings.idl\
	SpreadsheetDrawPage.idl\
	SpreadsheetView.idl\
	SpreadsheetViewObjectsMode.idl\
	SpreadsheetViewPane.idl\
	SpreadsheetViewPanesEnumeration.idl\
	SpreadsheetViewSettings.idl\
	Spreadsheets.idl\
	SpreadsheetsEnumeration.idl\
	StatusBarFunction.idl\
	SubTotalColumn.idl\
	SubTotalDescriptor.idl\
	SubTotalField.idl\
	SubTotalFieldsEnumeration.idl\
	TableAutoFormat.idl\
	TableAutoFormatEnumeration.idl\
	TableAutoFormatField.idl\
	TableAutoFormats.idl\
	TableAutoFormatsEnumeration.idl\
	TableCellStyle.idl\
	TableCellStyle.idl\
	TableConditionalEntry.idl\
	TableConditionalEntryEnumeration.idl\
	TableConditionalFormat.idl\
	TableFilterField.idl\
	TableFilterField2.idl\
	TableOperationMode.idl\
	TablePageBreakData.idl\
	TablePageStyle.idl\
	TableValidation.idl\
	TableValidationVisibility.idl\
	UniqueCellFormatRanges.idl\
	UniqueCellFormatRangesEnumeration.idl\
	ValidationAlertStyle.idl\
	ValidationType.idl\
	VolatileResult.idl\
	XActivationBroadcaster.idl\
	XActivationEventListener.idl\
	XAddIn.idl\
	XAreaLink.idl\
	XAreaLinks.idl\
	XArrayFormulaRange.idl\
	XArrayFormulaTokens.idl\
	XCalculatable.idl\
	XCellAddressable.idl\
	XCellFormatRangesSupplier.idl\
	XCellRangeAddressable.idl\
	XCellRangeData.idl\
	XCellRangeFormula.idl\
	XCellRangeMovement.idl\
	XCellRangeReferrer.idl\
	XCellRangesAccess.idl\
	XCellRangesQuery.idl\
	XCellSeries.idl\
	XCompatibilityNames.idl\
	XConsolidatable.idl\
	XConsolidationDescriptor.idl\
	XDDELink.idl\
	XDDELinkResults.idl\
	XDDELinks.idl\
	XDataPilotDataLayoutFieldSupplier.idl\
	XDataPilotDescriptor.idl\
	XDataPilotField.idl\
	XDataPilotFieldGrouping.idl\
	XDataPilotMemberResults.idl\
	XDataPilotResults.idl\
	XDataPilotTable.idl\
	XDataPilotTable2.idl\
	XDataPilotTables.idl\
	XDataPilotTablesSupplier.idl\
	XDatabaseRange.idl\
	XDatabaseRanges.idl\
	XDimensionsSupplier.idl\
	XDocumentAuditing.idl\
	XDrillDownDataSupplier.idl\
	XEnhancedMouseClickBroadcaster.idl\
	XExternalDocLink.idl\
	XExternalDocLinks.idl\
	XExternalSheetCache.idl\
	XExternalSheetName.idl\
	XFillAcrossSheet.idl\
	XFilterFormulaParser.idl\
	XFormulaOpCodeMapper.idl\
	XFormulaParser.idl\
	XFormulaQuery.idl\
	XFormulaTokens.idl\
	XFunctionAccess.idl\
	XFunctionDescriptions.idl\
	XGoalSeek.idl\
	XHeaderFooterContent.idl\
	XHierarchiesSupplier.idl\
	XLabelRange.idl\
	XLabelRanges.idl\
	XLevelsSupplier.idl\
	XMembersSupplier.idl\
	XMultiFormulaTokens.idl\
	XMultipleOperation.idl\
	RangeScopeName.idl\
	XNamedRange.idl\
	XNamedRanges.idl\
	XNamedRange2.idl\
	XNamedRanges2.idl\
	XPrintAreas.idl\
	XRangeSelection.idl\
	XRangeSelectionChangeListener.idl\
	XRangeSelectionListener.idl\
	XRecentFunctions.idl\
	XResultListener.idl\
	XScenario.idl\
	XScenarioEnhanced.idl\
	XScenarios.idl\
	XScenariosSupplier.idl\
	XSheetAnnotation.idl\
	XSheetAnnotationAnchor.idl\
	XSheetAnnotationShapeSupplier.idl\
	XSheetAnnotations.idl\
	XSheetAnnotationsSupplier.idl\
	XSheetAuditing.idl\
	XSheetCellCursor.idl\
	XSheetCellRange.idl\
	XSheetCellRangeContainer.idl\
	XSheetCellRanges.idl\
	XSheetCondition.idl\
	XSheetConditionalEntries.idl\
	XSheetConditionalEntry.idl\
	XSheetFilterDescriptor.idl\
	XSheetFilterDescriptor2.idl\
	XSheetFilterable.idl\
	XSheetFilterableEx.idl\
	XSheetLinkable.idl\
	XSheetOperation.idl\
	XSheetOutline.idl\
	XSheetPageBreak.idl\
	XSheetPastable.idl\
    XSolver.idl\
    XSolverDescription.idl\
	XSpreadsheet.idl\
	XSpreadsheetDocument.idl\
	XSpreadsheetView.idl\
	XSpreadsheets.idl\
	XSubTotalCalculatable.idl\
	XSubTotalDescriptor.idl\
	XSubTotalField.idl\
	XUniqueCellFormatRangesSupplier.idl\
	XUsedAreaCursor.idl\
	XViewFreezable.idl\
	XViewPane.idl\
	XViewPanesSupplier.idl\
	XViewSplitable.idl\
	XVolatileResult.idl\
	_NamedRange.idl

# ------------------------------------------------------------------

.INCLUDE :  target.mk
.INCLUDE :  $(PRJ)$/util$/target.pmk
