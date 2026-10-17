# HTTP Proxy Cache

A basic HTTP caching proxy written in Java for COSC203 at the University of Otago (2023).

The proxy sits between a client and a web server, forwarding HTTP requests and caching responses in memory. When the same resource is requested again, the cached response is returned without contacting the original server.

## Features

- HTTP request forwarding using Java sockets.
- In-memory caching of HTTP responses.
- Cache lookup to avoid repeated requests to the origin server.
- Support for text and binary responses, including images.
- Dynamic response buffering to handle larger files.

## How It Works

1. The proxy listens for client connections on a specified port.
2. It reads the HTTP request and checks whether the requested URL exists in its cache.
3. If cached, the stored response is returned directly to the client.
4. Otherwise, the proxy connects to the origin server and retrieves the response.
5. The response is forwarded to the client and stored in the cache for future requests.

The cache is stored in memory and is cleared when the proxy stops.

## Requirements

- Java JDK

No external libraries are required.

## Running the Proxy

From the project directory, compile the Java files:

```bash
javac ProxyCache.java HttpRequest.java HttpResponse.java
```

Start the proxy on port 8888:

```bash
java ProxyCache 8888
```

The proxy will continue running and listening for HTTP requests until stopped with `Ctrl + C`.

## Testing

You can test the proxy using an HTTP website or a local web server.

For example, start a local Python web server on port 8000 in a directory containing `hello.txt`:

```bash
python -m http.server 8000
```

In another terminal, request the file through the proxy:

```bash
curl --noproxy "" -x http://127.0.0.1:8888 http://127.0.0.1:8000/hello.txt
```

Run the command again to test caching. The proxy terminal should indicate that the response was retrieved from its cache rather than the origin server.

## Limitations

This is a basic coursework implementation rather than a production-ready proxy.

- Supports basic HTTP requests, not HTTPS tunnelling.
- Processes client connections sequentially.
- Does not implement cache expiration or validation.
- Does not fully support all HTTP features, such as chunked transfer encoding.
- Cached responses are lost when the program stops.

## Concepts Demonstrated

- TCP socket programming in Java.
- HTTP request and response processing.
- Client-server communication.
- In-memory caching using hash maps.
- Binary data handling and stream processing.