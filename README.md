# Module 5: Client-Server File Transfer in C

## Problem Statement
The goal of this module is to implement a client-server application in C that allows a client to request a file from a server. The server responds with the file content if it exists and is within the allowed size limit (255 characters). The system should handle errors such as:

- File does not exist
- File size exceeds the maximum allowed
- Graceful termination of the server

## Solution Description

### Server (`server.c`)
- Listens on port `9001` for client connections.  
- Receives a filename from the client.  
- If the file exists, reads up to 255 characters and sends it to the client.  
- If the file does not exist, sends an error message: `Error: File not found.`  
- Handles multiple client requests in a loop until terminated with `Ctrl + C`.

### Client (`client.c`)
- Connects to the server.  
- Prompts the user to enter a filename.  
- Displays the response from the server.

### Error Handling
- Invalid or missing file → server sends an error message.  
- Files larger than 255 characters → server sends only the first 255 characters.  
- Server termination → server can be stopped gracefully using `Ctrl + C`.

## Pros and Cons

**Pros:**
- Handles multiple client requests in a loop.  
- Error messages for missing files improve usability.  
- Prevents crashes by limiting file size to 255 characters.  
- Clear separation of filename and file content buffers.  

**Cons:**
- Server only handles one client at a time (no multi-threading).  
- No authentication or security checks.  
- File size limit of 255 characters may be restrictive for larger files.  

## Test Cases and Screenshots

### Test 1: Normal File
- **Filename:** `test.txt`  
- **Expected:** Client receives the file content.  
- **Client Output:**

Enter filename to request: test.txt
Server response:
Hello, this is a test file!  
- **Screenshot:** `test1_screenshot.png`

### Test 2: File Does Not Exist
- **Filename:** `missing.txt`  
- **Expected:** Client receives an error message.  
- **Client Output:** Enter filename to request: missing.txt
Server response:
Error: File not found.
  
- **Screenshot:** `test2_screenshot.png`

### Test 3: File Larger Than 255 Characters
- **Filename:** `long.txt`  
- **Expected:** Client receives only the first 255 characters of the file.  
- **Client Output:** Enter filename to request: long.txt
Server response:
This is a long line. This is a long line. This is a long line. This is a long line. This is a long line. This is a long line. This is a long line. This is a long line. This is a long line. This is a long line. This is a long line. This is a lon
  
- **Screenshot:** `test3_screenshot.png`

### Test 4: Server Termination
- **Action:** Stop the server with `Ctrl + C`  
- **Expected:** Server stops gracefully without crashing.  
- **Server Output: ** ^C
Server shutting down gracefully.
  
- **Screenshot:** `test4_screenshot.png`
