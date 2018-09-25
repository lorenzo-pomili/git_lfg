const login = (user, pass) => {
  return {
    isValid: true,
    token: "mockToken"
  };
};
const loginWithGithub = (token) => {
  return {
    isValid: true,
    user: {
      id: "test0",
      token: "mockToken",
      name: "Test User"
    }
  };
};
module.exports = {
  login,
  loginWithGithub
};
