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


package com.sun.star.wizards.web.data;

import com.sun.star.wizards.common.ConfigGroup;
import com.sun.star.wizards.common.PropertyNames;

/**
 *
 * A Class which describes the publishing arguments
 * in a session.
 * Each session can contain different publishers, which are configured
 * through such a CGPublish object.
 */
public class CGPublish extends ConfigGroup
{

    public boolean cp_Publish;
    public String cp_URL;
    public String cp_Username;
    public String password;
    /**
     * cp_URL is the url given by the user
     * for this publisher. (in UCB URL form)
     * This one will be edited to result the "url"
     * field, which is the true url, ucb uses to publish.
     * It is used for example to add ftp username and password, or zip url
     */
    public String url;
    /**
     * if the user approved overwriting files in this publisher target
     */
    public boolean overwriteApproved;

    /**
     * here I get an URL from user input, and parse it to
     * a UCB url...
     * @param url
     */
    public void setURL(String path)
    {
        try
        {
            this.cp_URL = ((CGSettings) this.root).getFileAccess().getURL(path);
            overwriteApproved = false;
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }

    public String getURL()
    {
        try
        {
            return ((CGSettings) this.root).getFileAccess().getPath(cp_URL, null);
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return PropertyNames.EMPTY_STRING;
        }
    }

    private String ftpURL()
    {
        return "ftp://" + cp_Username +
                ((password != null && password.length() > 0) ? ":" + password : PropertyNames.EMPTY_STRING) + "@" + cp_URL.substring(7);
    }
}
