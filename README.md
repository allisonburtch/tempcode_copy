Temp Monitor
============

Monitor temperature from several locations using Arduino, and NodeJS as a server.

This project includes:

*	Arduino sketches - [setup instructions](https://github.com/sergiomajluf/Temp-Monitor/wiki/How-to-set-up-the-Arduino) on wiki page
*	Node server app

The server expects RESTful HTTP calls to trigger saving and querying events: `<server address>/save/ID/temp`