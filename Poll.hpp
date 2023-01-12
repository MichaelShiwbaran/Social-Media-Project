//Name: Michael Shiwbaran
//Date: 10/26/2022
//CSCI 235 Professor Ligorio
//This Poll.hpp file is the interface file for implementing the Poll class' public variables and methods and private variables.

// #ifndef POLL_HPP_
// #define POLL_HPP_
#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include "Post.hpp"
using namespace std;
class Poll: public Post{
    public:
        Poll(string title, string question, string username, vector<string> options);
        /**
      Parameterized constructor.
        @param    : The title (name) of the Poll post (a string)
        @param    : The question (body) of the Poll post (a string)
        @param    : : The username of the Account that added this poll (a string)
        @param    : A vector of options for the Poll post
        @post     :Sets the title, body and username of the Poll post to the value of the parameters.
                   It will also generate the current time and store it and will initialize
                   the vectors of options and their respective number of votes.
   */

        bool votePoll(const int& n);
           /**
         @param     : a reference to int between 0 < number of options
         @return    : True if index is within range and we can vote for a poll,
                      false otherwise
         @post      : Increments the poll votes based on the index which
                      will refer to the index in the poll options
   */
        void changePollOption(const string& newPollOption, const int& g);
           /**
      Mutator function used to either add a poll or change one of the poll options
         @param     : A reference to the new poll option
         @param     : A reference to int that can either represent the index of the
                      existing option that will be replaced
                      or if choice_number > current number of options,
                      it will add this new option to the poll.
        @post       : Resets the number of votes for this option.
   */
        virtual void displayPost() const override;
           /**
      @post   : displays the whole Poll post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                0 votes for: option_1
                5 votes for: option_2
                2 votes for: option_3
                ...
                \n
                overrides the displaypost function in the post class
   */
        int getPollVotes(const int &p) const;
           /**
      Accessor function
      @param      : The index of the option
      @return     : returns the number of votes for a given option
   */
        void getPollOptions() const;
           /**
      Accessor function
        @post       : prints the reaction to the post in this format
                    (example where option_n is the string at position n in the poll options vector):
                    0 votes for: option_1
                    5 votes for: option_2
                    2 votes for: option_3
                    ...
   */
    
    private:
        vector<string> poll_options;
        //A vector of strings containing the poll options
        vector<int> number_of_votes;
        //A vector of integers containing the number of votes for each poll option
};

//#endif