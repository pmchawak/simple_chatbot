# Simple C++ Chatbot

This is the simple Chatbot for Udacity capstone project
### Version
1.0.0 -first and last XD
### Note
There may be some errors in the code
### Simple Usage
```sh
cd simple-cpp-chatbot-capstone
g++ chatbot.cpp && ./a.out
```
###Working
/**
 * Generate Reply
 *
 * Routine :
 * (1) Compare user's message to each element in the vector
 * (2) If the user's message is somehow similar
 *        -> Push a probable reply to a temporary vector
 * (3a) If there is any reply candidate,
 *        Select a reply randomly (to allow variation)
 * (3b) If there is none,
 *        Echo user's message and learn from his reply
 *        and then divert. (To start a new topic) 
 *
 * @param {string} The user's message
 * @return {string} Bot's Reply

