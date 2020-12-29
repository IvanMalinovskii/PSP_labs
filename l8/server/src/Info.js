const mongoose = require('mongoose');

const infoSchema = new mongoose.Schema({
    name: {
        type: String,
        required: true
    },
    date: {
        type: Date,
        default: Date.now()
    },
    employeeName: {
        type: String,
        required: true
    },
    difficulty: {
        type: Number,
        required: true,
        max: 10,
        min: 1
    },
    cost: {
        type: Number,
        required: true,
        min: 5
    }
});

exports.Info = mongoose.model('Info', infoSchema);