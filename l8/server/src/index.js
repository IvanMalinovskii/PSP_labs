const MONGO_URL = 'mongodb+srv://admin:admin@learncluster.v8kxb.mongodb.net/repair?retryWrites=true&w=majority';
const mongoose = require('mongoose');
const app = require('express')();
const Info = require('./Info').Info;

mongoose.connect(MONGO_URL, { useNewUrlParser: true, useCreateIndex: true, useUnifiedTopology: true }, (err) => {
    if (err) process.exit(1);
    app.listen(process.env.PORT || 5050, err => {
        if (err) process.exit(1);
        console.log('app started...');
    })
});

app.use(require('express').json());
app.use(require('cors')());
app.get('/', (req, resp) => {
    return resp.status(200).json({ message: 'hello you' });
});

app.get('/repair/get', async (req, resp) => {
    const data = await Info.find();

    return resp.status(200).json({
        message: 'get data',
        data: data
    });
});

app.post('/repair/put', async (req, resp) => {
    const toSave = new Info({
        name: req.body.name,
        date: req.body.date,
        employeeName: req.body.employeeName,
        difficulty: req.body.difficulty,
        cost: req.body.cost
    });

    const saved = await toSave.save();
    if (!saved) return resp.status(401).json({ message: 'wrong data' });
    return resp.status(200).json({
        message: 'save data',
        data: saved
    });
});

app.put('/repair/update', async (req, resp) => {
    const updated = await Info.updateOne({ _id: req.body._id }, {
        $set: {
            name: req.body.name,
            date: req.body.date,
            employeeName: req.body.employeeName,
            difficulty: req.body.difficulty,
            cost: req.body.cost
        }
    });

    if (!updated) return resp.status(401).json({message: 'bad request'});
    return resp.status(200).json({
        message: 'update data',
        data: updated
    });
});

app.delete('/repair/delete', async (req, resp) => {
    const deleted = await Info.deleteOne({_id: req.body._id});
    if (!deleted) return resp.status(401).json({message: 'bad request'});
    return resp.status(200).json({message: 'delete data', data: deleted});
});