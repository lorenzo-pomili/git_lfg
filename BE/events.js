const newEvent = (event) => {
  console.log(JSON.stringify(event));
};

const getEvents = () => {
  return [
    { id: "0" , eventName: "test Event 0", eventData: {} },
    { id: "1" , eventName: "test Event 1", eventData: {} },
    { id: "2" , eventName: "test Event 2", eventData: {} },
    { id: "3" , eventName: "test Event 3", eventData: {} }
  ]
};

const getEventDetail = (id) => {
  return {
    id: id,
    name: "test event detail",
    partecipants: [
      {name: "partecipant 0"},
      {name: "partecipant 1"},
      {name: "partecipant 2"},
      {name: "partecipant 3"},
      {name: "partecipant 4"}
    ]
  };
}

const joinEvent = ({token, user, event}) => {
    const newPartecipant = {name: user.name};
    return {...event, partecipants: event.partecipants.concat(newPartecipant)};
};

module.exports = {
  newEvent,
  getEvents,
  joinEvent,
  getEventDetail
};
