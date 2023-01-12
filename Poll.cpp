//Name: Michael Shiwbaran
//Date: 10/26/2022
//CSCI 235 Professor Ligorio
//This Poll.cpp file is the implementation file for designing the Poll class' functions and returning the proper information that the program was made for.
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include "Poll.hpp"
using namespace std;


Poll::Poll(string title, string question, string username, vector<string> options): Post(title, question, username){
    poll_options = options;
    for (int j = 0; j < options.size(); j++){
        number_of_votes.push_back(0);
    }
}
// Sets the title, question, and username to the parameters set by the user and initializes both the poll options and number of votes vectors based off the vector options.
bool Poll::votePoll(const int& n){
    if(n >= 0 && n <= poll_options.size()){
        number_of_votes[n]++;
        return true;
    }
    return false;
}
// Checks whether or not the integer value is within the size of the poll-options vector and sets the number of votes vector to increment by 1 at that index counting as a vote.
void Poll::changePollOption(const string& newPollOption, const int& g){
    if(g > number_of_votes.size()){
        poll_options.push_back(newPollOption);
    }
    else{
        poll_options[g] = newPollOption;
    }
    number_of_votes[g] = 0;
}
// considers if a new poll being added will replace a current poll or create a new index in the vector and sets the number of votes for this new poll to 0.
int Poll::getPollVotes(const int &p) const{
    return number_of_votes[p];
}
// returns the number of votes at a certain index in the number of votes vector.
void Poll::getPollOptions() const{
    for(int i = 0; i < poll_options.size(); i++){
        cout << number_of_votes[i] << "votes for: " << poll_options[i] << endl;
    }
}
// displays the number of votes for a certain poll using both the poll options vector and number of votes vector.
void Poll::displayPost() const{
  std::cout << "\n" << getTitle() << " at ";
  getTimeStamp();
  std::cout<< getBody() << "\n"<<"\n";
  getPollOptions();
  std::cout << "\n";
}
//displays the post along with any polls and their respective votes.