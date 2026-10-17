
/**
 * ProxyCache.java - Simple caching proxy
 *
 */

import java.net.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class ProxyCache {
    /** Port for the proxy */
    private static int port;
    /** Socket for client connections */
    private static ServerSocket socket;
    private static Map<String, byte[]> webcache;

    /** Create the ProxyCache object and the socket */
    public static void init(int p) {
        port = p;
        try {
            socket = new ServerSocket(port);
            webcache = new HashMap<String, byte[]>();
        } catch (IOException e) {
            System.out.println("Error creating socket: " + e);
            System.exit(-1);
        }
    }

    public static void handle(Socket client) {
        Socket server = null;
        HttpRequest request = null;
        HttpResponse response = null;

        /*
         * Process request. If there are any exceptions, then simply
         * return and end this request. This unfortunately means the
         * client will hang for a while, until it timeouts.
         */

        /* Read request */
        try {
            BufferedReader fromClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
            request = new HttpRequest(fromClient);
            System.out.println("Request received from client: " + request.URI);
            /*
             * // if method is not GET, simply do nothing
             * if (!(request.method.equals("GET"))) {
             * return;
             * }
             */
        } catch (IOException e) {
            System.out.println("Error reading request from client: " + e);
            return;
        }

        /* response: cached or not cached */
        if (webcache.containsKey(request.URI)) {
            /* send the response from cache */
            System.out.println("Find a cached version, respond to client with the Cached version");
            try {
                DataOutputStream toClient = new DataOutputStream(client.getOutputStream());
                byte[] cachedWebObject = webcache.get(request.URI);
                toClient.write(cachedWebObject);
                client.close();
            } catch (IOException e) {
                System.out.println("Error writing response to client: " + e);
            }

        } else {
            /* Send request to the origin server */
            System.out.println("Can't find a cached version in the proxy");
            try {
                /* Open socket and write request to socket */
                server = new Socket(request.getHost(), request.getPort());
                DataOutputStream toServer = new DataOutputStream(server.getOutputStream());
                toServer.writeBytes(request.toString());
                System.out.println("Proxy requests the origin server for: " + request.URI);
            } catch (UnknownHostException e) {
                System.out.println("Unknown host: " + request.getHost());
                System.out.println(e);
                return;
            } catch (IOException e) {
                System.out.println("Error writing request to server: " + e);
                return;
            }

            /* Read response from the origin server and forward it to client */
            try {
                DataInputStream fromServer = new DataInputStream(server.getInputStream());
                response = new HttpResponse(fromServer);
                System.out.println("Proxy receives the response from Origin server for: " + request.URI);

                DataOutputStream toClient = new DataOutputStream(client.getOutputStream());

                /* Write response to the client. First headers, then body */
                toClient.write(response.toString().getBytes(StandardCharsets.ISO_8859_1));
                toClient.write(response.body);
                System.out.println("Proxy forwards the received response to client");
                client.close();
                server.close();

                // Insert into the cache
                ByteArrayOutputStream cachedResponse = new ByteArrayOutputStream();
                cachedResponse.write(response.toString().getBytes(StandardCharsets.ISO_8859_1));
                cachedResponse.write(response.body);
                webcache.put(request.URI, cachedResponse.toByteArray());

                System.out.println("Proxy caches for: " + request.URI);
            } catch (IOException e) {
                System.out.println("Error writing response to client: " + e);
            }
        }
    }

    /** Read command line arguments and start proxy */
    public static void main(String args[]) {
        int myPort = 0;

        try {
            myPort = Integer.parseInt(args[0]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Need port number as argument");
            System.exit(-1);
        } catch (NumberFormatException e) {
            System.out.println("Please give port number as integer.");
            System.exit(-1);
        }

        init(myPort);

        /**
         * Main loop. Listen for incoming connections and spawn a new
         * thread for handling them
         */
        Socket client = null;

        while (true) {
            try {
                client = socket.accept();/* COMPLETE ME: accept an incoming request to the socket */
                System.out.println("");
                System.out.println("Got connection " + client);
                handle(client);
            } catch (IOException e) {
                System.out.println("Error reading request from client: " + e);
                /*
                 * Definitely cannot continue processing this request,
                 * so skip to next iteration of while loop.
                 */
                continue;
            }
        }

    }
}