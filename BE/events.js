const newEvent = (eventName, eventData) => {
  console.log(eventName);
  console.log(JSON.stringify(eventData));
};

const getEvents = () => {
  return [
    { eventName: "test Event 0", eventData: {} },
    { eventName: "test Event 1", eventData: {} },
    { eventName: "test Event 2", eventData: {} },
    { eventName: "test Event 3", eventData: {} }
  ]
};

module.exports = {
  newEvent,
  getEvents
};
