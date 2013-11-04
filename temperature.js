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

forecast.get(lat_AB, long_AB, function (err, res, data) {
  if (err) throw err;
  // console.log('res: ' + util.inspect(res));
  console.log("Allison = " + util.inspect(data.currently.temperature));
});

forecast.get(lat_DM, long_DM, function (err, res, data) {
  if (err) throw err;
  // console.log('res: ' + util.inspect(res));
  console.log("Donna = " + util.inspect(data.currently.temperature));
});

forecast.get(lat_SM, long_SM, function (err, res, data) {
  if (err) throw err;
  // console.log('res: ' + util.inspect(res));
  console.log("Sergio = " + util.inspect(data.currently.temperature));
});