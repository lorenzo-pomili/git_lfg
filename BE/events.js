const newEvent = (eventName, eventData) => {
  console.log(eventName);
  console.log(JSON.stringify(eventData));
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
    name: "test event detail"
  };
}

module.exports = {
  newEvent,
  getEvents,
  getEventDetail
};
