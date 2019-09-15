#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
/**
 * Enumerate Functions to be Used
 */
void loadBrain();
void saveToBrain(string message);
string userInput();
string botOutput(string mes);
void replyWith(string message);
unsigned int levenshtein_distance(string s1, string s2);

/* Bot's Memory */
vector<string> memory;

/* Main Function */
int main()
{
  string message, reply;
  /* Initialize Brain */
  loadBrain();
  while(1) // Loop Indefinitely
  {
    /* Ask for user input */
    message = userInput();

    /* Get a reply from bot */
    reply = botOutput(message);

    /* Send the Bot's Reply */
    replyWith(reply);
  }
}

/**
 * Loads the brain from file
 * and pushes it to memory
 *
 * @param NONE
 * @return NONE
 */
void loadBrain()
{
  cout << "[BOT CONSOLE] > INITIALIZING BRAIN FILE\n";
  string tmp;
  /* Load the file itself */
  ifstream brainFile("brain.txt");
  /* Read the file line by line */
  while(getline(brainFile, tmp))
    memory.push_back(tmp);
  /* Close the file after reading */
  brainFile.close();
  cout << "[BOT CONSOLE] > Brain File loaded!\n"
       << "@exit to end chat session :)\n"
       << "BOT: Hi!~\n"; //"hi!"
}

/**
 * Appends the message into the file
 * @param {string} message to append
 */
void saveToBrain(string message)
{
  /* Append the message to the local file */
  ofstream brainFile("brain.txt", ios::app);
  brainFile << message << "\n";
  brainFile.close();

  /**
   * Push the message to the memory
   * To prevent Segmentation fault
   * if memory is undefined
   */
  memory.push_back(message);
}

/**
 * Ask for user input
 * @param NONE
 * @return {string} User's input
 */
string userInput()
{
  string mes;
  do {
    cout << "YOU: ";
    getline(cin, mes);
    if(mes == "@exit") exit(0);
  } while(mes == "");
  return mes;
}

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
 */
string botOutput(string mes)
{
  /* Configuration */
  float errorRate, errorThreshold = 0.40; // 40% Allowable Error
  int dist;
  vector<string> replies;
  /* Step 1: Generate Replies */
  for(int i=0; i< memory.size(); i++)
  {
    dist = levenshtein_distance(mes, memory[i]);
    errorRate = (float)dist / (float)mes.size();

    /**
     * Nesting If(s) instead of using logical operator
     * to prevent errors if memory reached its last element
     */
    if(errorRate <= errorThreshold) { // Push reply candidates
      if(memory.size() > i+1) { // Check if the next line is the end of file
        if(memory[i+1] != "") { // Check if the next line is not empty
          replies.push_back(memory[i+1]); // OKAY!
        }
      }
    }
  }

  /* Step 2: Validate Replies */
  srand(time(NULL));
  if(replies.size() == 0) // ERROR: No Reply Candidate found!
  {

    /* Step 0: Learn from the user */
      saveToBrain(mes);
    /* Step 1: Return the user's input */
      replyWith(mes+"?");
    /* Step 2: Learn from the user's reply */
      string reply = userInput();
    /* Step 3: Save it to the file */
      saveToBrain(reply);
    /* Step 4: Divert! If Possible! :) */
    if(memory.size() > 0) {
      int randomNumber = rand() % memory.size();
      saveToBrain(memory[randomNumber]);
      return memory[randomNumber];
    }
  } else {

    /* Action: Reply */
    int randomNumber = rand() % replies.size();
    return(replies[randomNumber]);

  }
}

/**
* Send Message
* @param {string} Message to Send
* @return NONE
*/
void replyWith(string message)
{
  cout << "BOT: " << message << "\n";
}


unsigned int levenshtein_distance(string s1, string s2)
{
	const size_t len1 = s1.size(), len2 = s2.size();
	vector<unsigned int> col(len2+1), prevCol(len2+1);
	for (unsigned int i = 0; i < prevCol.size(); i++)
		prevCol[i] = i;
	for (unsigned int i = 0; i < len1; i++) {
		col[0] = i+1;// height
    for (unsigned int j = 0; j < len2; j++)
			col[j+1] = min(min(prevCol[j + 1] + 1, col[j] + 1), prevCol[j] + (s1[i]==s2[j] ? 0 : 1));
		col.swap(prevCol);
	}
	return prevCol[len2];
}
