//Name: Michael Shiwbaran
//Date: 10/26/2022
//CSCI 235 Professor Ligorio
//This Promotional.cpp file is the implementation file for designing the Promotional class' functions and returning the proper information that the program was made for.
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include "Promotional.hpp"
using namespace std;

Promotional::Promotional(const string& name, const string& body, const string& username, const string& link): Post(name, body, username){
    setLink(link);
}

// sets the name, body, username, and link to the parameters passed by the user and sets the url private member to the link parameter.
string Promotional::getLink() const{
    return url;
}
// returns the url link

bool Promotional::setLink(const string &link){
    regex pattern("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,256}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    if(regex_match(link,pattern)){
        url = link;
        return true;
    }
    else{
        url = "Broken Link";
        return false;
    }
}
// uses regex to determine if the linnk inputted by the user is a valid link and returns true. If not valid it sets the url to a broken link string.
void Promotional::displayPost() const{
  std::cout << "\n" << getTitle() << " at ";
  getTimeStamp();
  std::cout << getBody() << "\n"
            << "\n"
            << getLink() << "\n";
}
// displays the title, body, and username along with the url link if it's valid.