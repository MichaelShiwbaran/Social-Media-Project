//Name: Michael Shiwbaran
//Date: 10/26/2022
//CSCI 235 Professor Ligorio
//This Promotional.hpp file is the interface file for implementing the Promotional class' public variables and methods and private variables.

// #ifndef PROMOTIONAL_HPP_
// #define PROMOTIONAL_HPP_
#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <regex>
#include "Post.hpp"
using namespace std;

class Promotional: public Post{
    public:
        Promotional(const string& name, const string& body, const string& username, const string& link);
           /**
      Parameterized constructor.
         @param       : The name of the Promotional post (a string)
         @param       : The body of the Promotional post (a string)
         @param    : : The username of the Account that added this post (a string)
         @param       : The link of the Promotional post (a string)
        @post         : Sets the title, body, username and link (if it's a proper link otherwise "Broken Link")
                       of the Promotional to the value
                       of the parameters.
                       It will also generate the current time and store it.
   */
        string getLink() const;
           /**
      Accessor function
      @return         : Returns the post link
   */
        bool setLink(const string &link);
           /**
      @param    : A reference to the link that is in the format 'https://www.something.something'
                  or 'http://www.something.something' with the last 'something' being at least 2 characters
      @return   : true if the link is correctly formatted, false otherwise
      @post     : If the link is not correctly formatted, store "Broken Link"
                  in the link member variable, otherwise store the value of the
                  parameter (Hint: see <regex>)
   */
        virtual void displayPost() const override;
           /**
      @post      : displays the entire Promotional post (example):
                  \n
                  {post_title_} at {time_stamp_}:
                  {post_body_}
                  \n
                  {link}
                  \n
                  overrides the displaypost function in the post class
   */
    private:
        string url = "";
        //   string that represents a url
};


//#endif