var mongoose = require('mongoose');
var Schema = mongoose.Schema;

// define a new schema
var tempSchema = new Schema({
    currentUser : String,
    currentTime : Date,
    currentTemp : String,
    forecastTemp : String,
});

// export 'Astronaut' model
module.exports = mongoose.model('userTemp',tempSchema);
