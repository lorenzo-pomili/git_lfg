const login = (user, pass) => {
  return {
    isValid: true,
    token: "mockToken"
  };
};
const loginWithGithub = (token) => {
  return {
    isValid: true,
    token: "mockToken"
  };
};
module.exports = {
  login,
  loginWithGithub
};
