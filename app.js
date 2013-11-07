// Set up server
var express = require('express');
var app = express();
var net = require('net');
var mongoose = require ("mongoose");

// Set up Forecast.io
var Forecast = require('forecast.io');
var util = require('util')
var options = {
	APIKey: "49f769efb11fc808363e17f9d04c428f"
},
	lat_AB = 40.696963,
	long_AB = -73.974601,
	lat_DM = 40.723389,
	long_DM = -73.985746
	lat_SM = 40.771369,
	long_SM = -73.930970,
	forecast = new Forecast(options);


// Run Server 
app.get('/', function(req, res) {
	res.writeHead(200, {
		'Content-Type': 'text/plain'
	});
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
	var timestamp = (new Date()).getTime();
	var currentTime = (new Date()).getHours();

	var currentUser = req.params.id.toUpperCase();
	var currentTemp = req.params.temp;
	// call function to API, and store in local value
	var forecastTemp = null; 
	
	getWeatherApi(currentUser, function(myTempForecast) {
		//console.log("my api temp is " + myTempForecast);
		forecastTemp = myTempForecast;
		console.log("Forecast Temp is: " + forecastTemp);
		
		console.log(currentTime);

		if (currentTime > 6 && currentTime < 22 && forecastTemp < 55 && currentTemp > 68) {
			console.log("daytime: your house is sufficiently heated");
		}

		else if (currentTime > 6 && currentTime < 22 && forecastTemp < 55 && currentTemp < 68) {
			console.log("daytime: your house is cold");
		}

		else if (currentTime > 22 && currentTime < 6 && forecastTemp < 40 && currentTemp > 55) {
			console.log("nightime: your house is sufficiently heated");
		}

		else if (currentTime > 22 && currentTime < 6 && forecastTemp < 40 && currentTemp < 55) {
			console.log("nightime: your house is cold");
		}


	});
	
	
	// run the comparison function
	//evalTemperature (currentTime, currentTemp, forecastTemp);
	
	// if possible, store results in db or array for later viz
	
	// Testing purposes only, send a visual response to browser and console 
	res.send({timestamp: currentTime,user: (req.params.id).toUpperCase(),temp: req.params.temp});
	console.log({timestamp: currentTime,user: (req.params.id).toUpperCase(),temp: req.params.temp});
	
});

var port = process.env.PORT || 5000;
app.listen(port, function() {
	console.log("Listening on " + port);
});

function getWeatherApi(userID, callback) {

	switch (userID) {
	case "AB":
		forecast.get(lat_AB, long_AB, function(err, res, data) {
			if (err) throw err;
			myTempForecast = util.inspect(data.currently.temperature);
			callback(myTempForecast);
		});

		break;
	case "DM":
		forecast.get(lat_DM, long_DM, function(err, res, data) {
			if (err) throw err;
			myTempForecast = util.inspect(data.currently.temperature);
			callback(myTempForecast);
		});
		break;
	case "SM":
		forecast.get(lat_SM, long_SM, function(err, res, data) {
			if (err) throw err;
			myTempForecast = util.inspect(data.currently.temperature);
			callback(myTempForecast);
		});
		break;
	default:
		console.log("User unkown");
	}
}