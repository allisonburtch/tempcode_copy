// Set up server
var express = require('express');
var app = express();
var net = require('net');


// Run Server 
app.get('/', function(req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end('Temperature Monitor App');
});

app.get('/save', function(req, res) {
    res.send("Incomplete request. Missing the User & Temp");
});

app.get('/save/:id', function(req, res) {
    res.send("Incomplete request. Missing Temp");
});

app.get('/save/:id/:temp', function(req, res) {
	
	// set variables for current request
	var currentTime = (new Date()).getTime();
	var currentUser = req.params.id.toUpperCase();
	var currentTemp = req.params.temp;

	// call function to API, and store in local value
	var forecastTemp = getWeaterApi(currentUser);

	// run the comparison function
	//evalTemperature (currentTime, currentTemp, forecastTemp);

	// if possible, store results in db or array for later viz

    // Testing purposes only, send a visual response to browser and console 
    res.send({timestamp: currentTime, user:(req.params.id).toUpperCase(), temp: req.params.temp});
    console.log({timestamp: currentTime, user:(req.params.id).toUpperCase(), temp: req.params.temp});

	

});
 
var port = process.env.PORT || 5000;
app.listen(port, function() {
  console.log("Listening on " + port);
});

function getWeaterApi (userID) {
// within this function we should call the code in temperature.js
// the case statements allow running only the appropiate function.

	switch (userID){
		case "AB": 
		console.log("Allison")
		break;
		case "DM": 
		console.log("Donna")
		break;
		case "SM": 
		console.log("Sergio")
		break;
		default : console.log("User unkown");
	}

}
