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



package com.sun.star.lib.connections.socket;

/**
 * Helper class for <code>socketAcceptor</code> and
 * <code>socketConnector</code>.
 *
 * <p>FIXME:  Once those classes have been moved from <code>jurt</code> to
 * <code>javaunohelper</code>, they should use
 * <code>com.sun.star.lib.uno.helper.UnoUrl</code> either instead of this class
 * or underneath this class.</p>
 */
final class ConnectionDescriptor {
    public ConnectionDescriptor(String description)
        throws com.sun.star.lang.IllegalArgumentException {
        for (int i = description.indexOf(','); i >= 0;) {
            int j = description.indexOf(',', i + 1);
            int k = j < 0 ? description.length() : j;
            int l = description.indexOf('=', i + 1);
            if (l < 0 || l >= k) {
                throw new com.sun.star.lang.IllegalArgumentException(
                    "parameter lacks '='");
            }
            String key = description.substring(i + 1, l);
            String value = description.substring(l + 1, k);
            if (key.equalsIgnoreCase("host")) {
                host = value;
            } else if (key.equalsIgnoreCase("port")) {
                try {
                    port = Integer.valueOf(value).intValue();
                } catch (NumberFormatException e) {
                    throw new com.sun.star.lang.IllegalArgumentException(
                        e.toString());
                }
                if (port < 0 || port > 65535) {
                    throw new com.sun.star.lang.IllegalArgumentException(
                        "port parameter must have value between 0 and 65535,"
                        + " inclusive");
                }
            } else if (key.equalsIgnoreCase("backlog")) {
                try {
                    backlog = Integer.valueOf(value).intValue();
                } catch (NumberFormatException e) {
                    throw new com.sun.star.lang.IllegalArgumentException(
                        e.toString());
                }
            } else if (key.equalsIgnoreCase("tcpnodelay")) {
                if (value.equals("0")) {
                    tcpNoDelay = Boolean.FALSE;
                } else if (value.equals("1")) {
                    tcpNoDelay = Boolean.TRUE;
                } else {
                    throw new com.sun.star.lang.IllegalArgumentException(
                        "tcpnodelay parameter must have 0/1 value");
                }
            }
            i = j;
        }
    }

    public String getHost() {
        return host;
    }

    public int getPort() {
        return port;
    }

    public int getBacklog() {
        return backlog;
    }

    public Boolean getTcpNoDelay() {
        return tcpNoDelay;
    }

    private String host = null;
    private int port = 6001;
    private int backlog = 50;
    private Boolean tcpNoDelay = null;
}
