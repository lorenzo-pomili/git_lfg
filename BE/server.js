const login = require("./login");
const events = require("./events");
const {newEvent, getEvents} = events;
const isValidToken = require("./userValidation");

const fs = require('fs');
const express = require('express');
const app = express();

const port = "8008";

const filepath = __dirname+"/mockData.json";
const filepathStorage = __dirname+"/dataStorage.json";
const filepathSuggests = __dirname+"/dataSuggests.json";

app.use("/", express.static(__dirname + '/../public'));

// curl -d '{"user":"testUser", "key2":"testPass"}' -H "Content-Type: application/json" -X POST http://localhost:8008/login
app.post('/login', (req, res) => {
  let bodyStr = "";
  req.on("data", (chunk) => {
      bodyStr += chunk.toString();
  });
  req.on("end", () => {
      const body = JSON.parse(bodyStr);
      const response = login(body.user, body.pass);
      res.send(response);
  })
});

// curl -i -H "Accept: application/json" -H "Content-Type: application/json" -X GET http://localhost:8008/getEvents
app.get('/getEvents', (req, res) => {
  res.send(getEvents());
});

// curl -d '{"token":"mockToken", "eventName":"testEvent", "eventData":{}}' -H "Content-Type: application/json" -X POST http://localhost:8008/newEvent
app.post('/newEvent', (req, res) => {
  let bodyStr = "";
  req.on("data", (chunk) => {
      bodyStr += chunk.toString();
  });
  req.on("end", () => {
      const body = JSON.parse(bodyStr);
      if(isValidToken(body.token)){
        const response = newEvent(body.eventName, body.eventData);
        res.send(response);
      }else{
        res.status(403).send({ error: "access denie" });
      }
  })
});

app.listen(port);
console.log(`App served on: http://localhost:${port}`);
