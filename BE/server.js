const {login, loginWithGithub} = require("./login");
const events = require("./events");
const {newEvent, getEvents, getEventDetail} = events;
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

// curl -d '{"token":"test_token"}' -H "Content-Type: application/json" -X POST http://localhost:8008/loginWithGithub
app.post('/loginWithGithub', (req, res) => {
  let bodyStr = "";
  req.on("data", (chunk) => {
      bodyStr += chunk.toString();
  });
  req.on("end", () => {
      const body = JSON.parse(bodyStr);
      const response = loginWithGithub(body.token);
      res.send(response);
  })
});

// curl -i -H "Accept: application/json" -H "Content-Type: application/json" -X GET http://localhost:8008/getEvents
app.get('/getEvents', (req, res) => {
  res.send(getEvents());
});
// curl -i -H "Accept: application/json" -H "Content-Type: application/json" -X GET http://localhost:8008/getAllEvents
// TODO: should be consider token in some way?
// yes -> implement here
// no -> remove token when this service is used
app.get('/getAllEvents', (req, res) => {
  res.send(getEvents());
});

// curl -i -H "Accept: application/json" -H "Content-Type: application/json" -X GET http://localhost:8008/getEventDetail/42
app.get('/getEventDetail/:id', (req, res) => {
  setTimeout(() => {
    res.send(getEventDetail(req.params.id));
  }, 3000);
});

// curl -d '{"token":"mockToken", {"name":"testEvent", "partecipants":{}}}' -H "Content-Type: application/json" -X POST http://localhost:8008/newEvent
app.post('/newEvent', (req, res) => {
  let bodyStr = "";
  req.on("data", (chunk) => {
      bodyStr += chunk.toString();
  });
  req.on("end", () => {
      const body = JSON.parse(bodyStr);
      if(isValidToken(body.token)){
        const response = newEvent(body);
        res.send(response);
      }else{
        res.status(403).send({ error: "access denie" });
      }
  })
});

app.listen(port);
console.log(`App served on: http://localhost:${port}`);
