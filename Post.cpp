// Name: Michael Shiwbaran
// Date: 11/28/2022
// CSCI 235 Professor Ligorio
// This Post.cpp file is the implementation file for designing the Post class'
// functions and returning the proper information that the program was made for.



#include "Post.hpp"


/**
   Parameterized constructor.
   @param      : The title of the post (a string)
   @param      : The body content of the post (a string)
   @param      : The username of the Account that added this post (a string)
   @post         : Sets the title, body and username to the value of the parameters
                   It will also generate the current time and store it
*/
Post::Post(std::string title, std::string body, std::string username) {
    post_title_ = title;
    post_body_ = body;
    time_stamp_ = time(NULL);
    username_ = username;
}


/**
   @return : the title of the Post
*/
std::string Post::getTitle() const {
    return post_title_;
}


/**
  @param  : a reference to title of the Post
  @post   : sets the private data member to the value of the parameter
*/
void Post::setTitle(const std::string& title) {
    post_title_ = title;
}


/**
   @return : the body of the Post
*/
std::string Post::getBody() const {
    return post_body_;
}


/**
   @param  : a reference to body of the Post
   @post   : sets the private data member to the value of the parameter
*/
void Post::setBody(const std::string& body) {
    post_body_ = body;
}


/*
   Accessor Function
   @return       : username associated with this Post
*/
std::string Post::getUsername() const {
    return username_;
}


/*
   Mutator Function
   @param        : a reference to the username associated with this Post
   @post   : sets the private data member to the value of the parameter
*/
void Post::setUsername(const std::string& username) {
    username_ = username;
}


/**
    @post:  prints out the post in the following format:
    \n
    {post_title_} at {time_stamp_}:
    {post_body_}
    \n
*/
void Post::getTimeStamp() const {
    std::cout << asctime(localtime(&time_stamp_));
}



/*
   Mutator Function
   @post   : sets the private data member to the current time
*/
void Post::updateTimeStamp() {
    time_stamp_ = time(0);
}


/*
    @param            :   The Post object to compare
    @return           :   true if this Post's username is less than the parameter
                          Post username, false otherwise
*/
bool Post::operator< (const Post &another_Post) const{
    if(username_ < another_Post.getUsername()){
        return true;
    }
    return false;
}

/*
    @param            :   The Post object to compare
    @return           :   true if this Post's username is greater than the
                          parameter Post username, false otherwise
*/
bool Post::operator> (const Post &another_Post) const{
    if(username_ > another_Post.getUsername()){
        return true;
    }
    return false;
}

/*
 @post             :  increments the likes_ private member
*/
void Post::like(){
    likes_++;
}

/*
  @return             : the value of the likes_ private member
*/
int Post::getLikes() const{
    return likes_;
}


/*
  @param           :  a priority value
  @post             :  sets the priority_id_ to the value of the parameter
*/
void Post::setPriority(priority set_priority_id){
    priority_id_ = set_priority_id;
}


/*
@return             :  the value of the priority_id_ data member
*/
enum Post::priority Post::getPriority() const{
    return priority_id_;
}
