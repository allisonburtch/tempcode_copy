var express = require('express');
 
var app = express();
 
app.get('/', function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end('Hello World\n');
});

app.get('/save', function(req, res) {
    res.send("Incomplete request. Missing the User & Temp");
});
app.get('/save/:id', function(req, res) {
    res.send("Incomplete request. Missing Temp");
});
app.get('/save/:id/:temp', function(req, res) {
    res.send({user:(req.params.id).toUpperCase(), temp: req.params.temp});
    console.log({user:(req.params.id).toUpperCase(), temp: req.params.temp});
});
 
app.listen(8888);
console.log('Listening on port 8888...');