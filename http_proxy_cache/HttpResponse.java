
/**
 * HttpResponse - Handle HTTP replies
 *
 * $Id: HttpResponse.java,v 1.2 2003/11/26 18:12:42 kangasha Exp $
 *
 */

import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class HttpResponse {
    final static String CRLF = "\r\n";

    /** How big is the buffer used for reading the object */
    final static int BUF_SIZE = 8192;

    /** Reply status and headers */
    String version;
    int status;
    String statusLine = "";
    String headers = "";

    /* Body of reply */
    byte[] body = new byte[0];

    /**
     * Read response from server.
     * use wireshard to capture an http response message and inspect its structure
     */
    public HttpResponse(DataInputStream fromServer) {
        /* Length of the object */
        int length = -1;
        boolean gotStatusLine = false;

        /* First read status line and response headers */
        try {
            String line = fromServer.readLine();

            while (line != null && line.length() != 0) {
                if (!gotStatusLine) {
                    statusLine = line;
                    gotStatusLine = true;
                } else {
                    headers += line + CRLF;
                }

                if (line.contains("Content-length") || line.contains("Content-Length")) {
                    try {
                        length = Integer.parseInt(line.split(":")[1].trim());
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid length input");
                    }
                }

                line = fromServer.readLine();
            }
        } catch (IOException e) {
            System.out.println("Error reading headers from server: " + e);
            return;
        }

        try {
            ByteArrayOutputStream buffer = new ByteArrayOutputStream();
            byte[] chunk = new byte[BUF_SIZE];
            int bytesRead = 0;

            while (length == -1 || bytesRead < length) {
                int bytesToRead = (length == -1) ? chunk.length : Math.min(chunk.length, length - bytesRead);
                int count = fromServer.read(chunk, 0, bytesToRead);

                if (count == -1) {
                    break;
                }

                buffer.write(chunk, 0, count);
                bytesRead += count;
            }

            body = buffer.toByteArray();

        } catch (IOException e) {
            System.out.println("Error reading response body: " + e);
            return;
        }

    }

    /**
     * Convert response into a string for easy re-sending. Only
     * converts the response headers, body is not converted to a
     * string.
     */
    public String toString() {
        String res = "";

        res = statusLine + CRLF;
        res += headers;
        res += CRLF;

        return res;
    }
}