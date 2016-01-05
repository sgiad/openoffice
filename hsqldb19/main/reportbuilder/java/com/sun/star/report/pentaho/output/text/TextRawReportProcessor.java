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


package com.sun.star.report.pentaho.output.text;

import com.sun.star.report.DataSourceFactory;
import com.sun.star.report.ImageService;
import com.sun.star.report.InputRepository;
import com.sun.star.report.OutputRepository;
import com.sun.star.report.pentaho.PentahoFormulaContext;

import org.jfree.report.ReportProcessingException;
import org.jfree.report.data.ReportContextImpl;
import org.jfree.report.flow.ReportContext;
import org.jfree.report.flow.ReportJob;
import org.jfree.report.flow.ReportStructureRoot;
import org.jfree.report.flow.ReportTarget;
import org.jfree.report.flow.SinglePassReportProcessor;

import org.pentaho.reporting.libraries.resourceloader.ResourceManager;

/**
 * Creation-Date: 03.07.2006, 17:08:25
 *
 * @author Thomas Morgner
 */
public class TextRawReportProcessor extends SinglePassReportProcessor
{

    private final OutputRepository outputRepository;
    private final String targetName;
    private final InputRepository inputRepository;
    private final ImageService imageService;
    private final DataSourceFactory dataSourceFactory;

    public TextRawReportProcessor(final InputRepository inputRepository,
            final OutputRepository outputRepository,
            final String targetName,
            final ImageService imageService,
            final DataSourceFactory dataSourceFactory)
    {
        if (inputRepository == null)
        {
            throw new NullPointerException();
        }
        if (outputRepository == null)
        {
            throw new NullPointerException();
        }
        if (targetName == null)
        {
            throw new NullPointerException();
        }
        if (imageService == null)
        {
            throw new NullPointerException();
        }
        if (dataSourceFactory == null)
        {
            throw new NullPointerException();
        }

        this.targetName = targetName;
        this.inputRepository = inputRepository;
        this.outputRepository = outputRepository;
        this.imageService = imageService;
        this.dataSourceFactory = dataSourceFactory;
    }

    protected ReportTarget createReportTarget(final ReportJob job)
            throws ReportProcessingException
    {
        final ReportStructureRoot report = job.getReportStructureRoot();
        final ResourceManager resourceManager = report.getResourceManager();

        return new TextRawReportTarget(job, resourceManager, report.getBaseResource(),
                inputRepository, outputRepository, targetName, imageService, dataSourceFactory);
    }

    protected ReportContext createReportContext(final ReportJob job,
            final ReportTarget target)
    {
        final ReportContext context = super.createReportContext(job, target);
        if (context instanceof ReportContextImpl)
        {
            final ReportContextImpl impl = (ReportContextImpl) context;
            impl.setFormulaContext(new PentahoFormulaContext(impl.getFormulaContext(), job.getConfiguration()));
        }
        return context;
    }
}


