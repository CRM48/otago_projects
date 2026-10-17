
/**
 * HttpRequest - HTTP request container and parser
 *
 */

import java.io.*;
import java.net.*;
import java.util.*;

public class HttpRequest {
    /** Help variables */
    final static String CRLF = "\r\n";
    final static int HTTP_PORT = 80;

    /** Store the request parameters */
    String method;
    String URI;
    String version;
    String headers = "";

    /** Server and port */
    private String host;
    private int port;

    /** Create HttpRequest by reading it from the client socket */
    public HttpRequest(BufferedReader from) {
        String firstLine = "";
        try {
            firstLine = from.readLine();
        } catch (IOException e) {
            System.out.println("Error reading request line: " + e);
        }

        String[] tmp = firstLine.split(" ");
        method = tmp[0];
        URI = tmp[1];
        version = tmp[2];

        if (!method.equals("GET")) {
            System.out.println("Error: Method not GET");
        }

        try {
            String line = from.readLine();
            while (line != null && line.length() != 0) {
                headers += line + CRLF;
                if (line.split(":")[0].equals("Host")) {
                    String[] hostElements = line.split(":");
                    host = hostElements[1].trim();
                    if (hostElements.length > 2) {
                        try {
                            port = Integer.parseInt(hostElements[2].trim());
                        } catch (NumberFormatException e) {
                            System.out.println("Invalid port Number");
                        }
                    } else {
                        port = HTTP_PORT;
                    }
                }

                line = from.readLine();
            }
        } catch (IOException e) {
            System.out.println("Error reading from socket: " + e);
            return;
        }
    }

    /** Return host for which this request is intended */
    public String getHost() {
        return host;
    }

    /** Return port for server */
    public int getPort() {
        return port;
    }

    /**
     * Convert request into a string for easy re-sending.
     */
    public String toString() {
        String path = URI;

        try {
            URL url = java.net.URI.create(URI).toURL();
            path = url.getFile();

            if (path.isEmpty()) {
                path = "/";
            }
        } catch (Exception e) {
            // URI is already a relative path
        }

        String req = method + " " + path + " " + version + CRLF;
        req += headers;
        req += "Connection: close" + CRLF;
        req += CRLF;

        return req;
    }
}