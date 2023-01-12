// Name: Michael Shiwbaran
// Date: 11/28/2022
// CSCI 235 Professor Ligorio
// This Account.cpp file is the implementation file for designing the Account
// class' functions and returning the proper information that the program was
// made for.

#include "Account.hpp"

// default constructor
//@post:  set username and password to ""
//        creates an empty vector of post objects to store into feed_
Account::Account() {
  username_ = "";
  password_ = "";
  posts_ = LinkedList<Post *>();
  following_ = {};
}

/**
    Parameterized Constructor
    @param username  : username of the account, stored into username_
    @param password  : password of the account, stored into password_
    @post:             sets the private members to the value of the parameters
*/
Account::Account(std::string username, std::string password)
    : username_(username), password_(password), posts_(LinkedList<Post *>()),
      following_({}), net_(nullptr) {}

/**
  @return:     the username of the Account
*/
std::string Account::getUsername() const { return username_; }

/**
  @param:     a reference to the username of the Account
  @psot:      sets the parameter to the value of the private member
*/
void Account::setUsername(const std::string &username) { username_ = username; }

/**
  @return:     the password of the Account
*/
std::string Account::getPassword() const { return password_; }

/**
  @param a reference to the password of the Account
  @post:      sets the private member to the value of the parameter
*/
void Account::setPassword(const std::string &password) { password_ = password; }

/**
      Accessor function
      @return           :   the pointer to the Network the account is in
   */
Network<Account> *Account::getNetwork() const { return net_; }

/**
      Mutator function
      @param            :   a pointer to a Network
      @post             :   the Network pointer private member points to the
   input Network
   */
void Account::setNetwork(Network<Account> *network) { net_ = network; }

/**
    @param newPost   : The pointer to the Post object that will be added to its
   list
    @return          : Will return true if a post gets added sucesfully to the
   vector
    @post:           " Adds post to posts_ and its Networks feed_
*/
bool Account::addPost(Post *newPost) {
  posts_.insert(newPost, 0);
  net_->addToFeed(newPost);

  if (min_like_post.empty()) {
    min_like_post.push(newPost);
  } else if (newPost->getLikes() <= min_like_post.top()->getLikes()) {
    min_like_post.push(newPost);
  }

  if (max_like_post.empty()) {
    max_like_post.push(newPost);
  } else if (newPost->getLikes() >= max_like_post.front()->getLikes()) {
    max_like_post.pop();
    max_like_post.push(newPost);
  }

  return true;
}

/*
    @post:      Prints the feed_ that contains the post objects by calling their
   display function
*/
void Account::viewPosts() const {

  Node<Post *> *itt = posts_.getHeadPtr();

  while (itt != nullptr) {
    itt->getItem()->displayPost();
    itt = itt->getNext();
  }
}

/**
      @param            :   the username of the Account to follow
      @return           :   true if the account was successfully able to follow,
   false otherwise
      @post             :   adds the username to the vector of following
   accounts only if it is affiliated to a Network AND it is not already
   following an account with the same username.
   */
bool Account::followAccount(const std::string username) {

  bool exists = false;

  for (std::string un : following_) {
    if (un == username) {
      exists = true;
    }
  }

  if (!exists && net_ != nullptr) {
    following_.push_back(username);
    return true;
  }

  return false;
}

/**
      @return           :   the vector of usernames the Account is following
   */
std::vector<std::string> Account::viewFollowing() const { return following_; }

/**
  @return           :  true if account has same private members as parameter,
                       false otherwise
*/
bool Account::operator==(const Account &acc) const {
  if (acc.getUsername() == this->username_ &&
      acc.getPassword() == this->password_) {
    return true;
  }

  return false;
}

/*
@param            :   A pointer to a Post
@return           :   True iff the Post was successfully found and removed,
                      false othewise.
@post             :   Removes the given Post from its list
                      as well as from the Network's feed.
*/
bool Account::removePost(Post *post) {
  int postPosition = posts_.getIndexOf(post);

  if (postPosition > -1) {
    posts_.remove(postPosition);
    net_->removePostFromFeed(post);
    return true;
  }
  return false;
}

/*
@param            :   Pointer to a Post object
@param            :   The new title of the Post (or an empty string if you do
not want to change it)
@param            :   The new body of the Post (or an empty string if you do not
                      want to change it)
@post            :   This function will take the Post and given the new title
and body, update the Posts title and body as appropriate. It will also update
                     the `timestamp_` to the current time of the update. This
function should then update the location of the Post in its list of `posts_` to
the front of the list as well as utilizing its Network pointer to do the same in
the `feed_`.
*/
bool Account::updatePost(Post *post, std::string new_title,
                         std::string new_body) {
  if (new_title != "") {
    post->setTitle(new_title);
  }

  if (new_body != "") {
    post->setBody(new_body);
  }

  post->updateTimeStamp();

  this->removePost(post);
  this->addPost(post);
  return net_->updateFeed(post);

}

/*
    @return           :  a pointer to the Post with least likes
    NOTE: YOU MUST DO THIS IN O(1) TIME. Use stack and or queue and add as
    many private members as you need and modify the necessary functions
    and/or add helper functions to do this in O(1) time.
    Note: If multiple Posts have the same amount of likes then it should be
   sorted from Newest to Oldest Where in this case it would be the Newest Post
   with the least amount of likes returned.
*/
Post *Account::getMinLikes() const { return min_like_post.top(); }

/*
    @return           :  a pointer to the Post with most likes
    NOTE: YOU MUST DO THIS IN O(1) TIME. Use stack and or queue and add as
    many private members as you need and modify the necessary functions
    and/or add helper functions to do this in O(1) time.
    Note: If multiple Posts have the same amount of likes then it should be
   sorted from Newest to Oldest Where in this case it would be the Oldest Post
   with the most amount of likes returned.
*/
Post *Account::getMaxLikes() const { return max_like_post.front(); }

/*
    @return           :  a vector of pointers to Post
    @post             :  the order of the Posts in the vector is by increasing
                         priority, and within each priority class, from oldest
                         to newest
    NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::increasingPriorityOldestToNewest() {
  std::vector<Post *> return_posts;
  Node<Post *> *current_post = posts_.getHeadPtr();
  std::stack<Post *> high_posts_;
  std::stack<Post *> mid_posts_;
  std::stack<Post *> low_posts_;

  while (current_post != nullptr) {
    if (current_post->getItem()->getPriority() == Post::HIGH) {
      high_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::MEDIUM) {
      mid_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::LOW) {
      low_posts_.push(current_post->getItem());
    }
    current_post = current_post->getNext();
  }
  while (!low_posts_.empty()) {
    return_posts.push_back(low_posts_.top());
    low_posts_.pop();
  }
  while (!mid_posts_.empty()) {
    return_posts.push_back(mid_posts_.top());
    mid_posts_.pop();
  }
  while (!high_posts_.empty()) {
    return_posts.push_back(high_posts_.top());
    high_posts_.pop();
  }

  return return_posts;
}

/*
@return           :  a vector of pointers to Post
@post             :  the order of the Posts in the vector is by increasing
                     priority, and within each priority class, from newest
                     to oldest
NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::increasingPriorityNewestToOldest() {
  std::vector<Post *> return_posts;
  Node<Post *> *current_post = posts_.getHeadPtr();
  std::queue<Post *> high_posts_;
  std::queue<Post *> mid_posts_;
  std::queue<Post *> low_posts_;

  while (current_post != nullptr) {
    if (current_post->getItem()->getPriority() == Post::HIGH) {
      high_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::MEDIUM) {
      mid_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::LOW) {
      low_posts_.push(current_post->getItem());
    }
    current_post = current_post->getNext();
  }
  while (!low_posts_.empty()) {
    return_posts.push_back(low_posts_.front());
    low_posts_.pop();
  }
  while (!mid_posts_.empty()) {
    return_posts.push_back(mid_posts_.front());
    mid_posts_.pop();
  }
  while (!high_posts_.empty()) {
    return_posts.push_back(high_posts_.front());
    high_posts_.pop();
  }

  return return_posts;
}

/*
    @return           :  a vector of pointers to Post
    @post             :  the order of the Posts in the vector is by decreasing
                         priority, and within each priority class, from oldest
                         to newest
    NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::decreasingPriorityOldestToNewest() {
  std::vector<Post *> return_posts;
  Node<Post *> *current_post = posts_.getHeadPtr();
  std::stack<Post *> high_posts_;
  std::stack<Post *> mid_posts_;
  std::stack<Post *> low_posts_;

  while (current_post != nullptr) {
    if (current_post->getItem()->getPriority() == Post::HIGH) {
      high_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::MEDIUM) {
      mid_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::LOW) {
      low_posts_.push(current_post->getItem());
    }
    current_post = current_post->getNext();
  }

  while (!high_posts_.empty()) {
    return_posts.push_back(high_posts_.top());
    high_posts_.pop();
  }
  while (!mid_posts_.empty()) {
    return_posts.push_back(mid_posts_.top());
    mid_posts_.pop();
  }

  while (!low_posts_.empty()) {
    return_posts.push_back(low_posts_.top());
    low_posts_.pop();
  }
  return return_posts;
}

/*
@return           :  a vector of pointers to Post
@post             :  the order of the Posts in the vector is by decreasing
                     priority, and within each priority class, from newest
                     to oldest
NOTE: use stacks and queues to do this in O(n) time
*/
std::vector<Post *> Account::decreasingPriorityNewestToOldest() {
  std::vector<Post *> return_posts;
  Node<Post *> *current_post = posts_.getHeadPtr();
  std::queue<Post *> high_posts_;
  std::queue<Post *> mid_posts_;
  std::queue<Post *> low_posts_;

  while (current_post != nullptr) {
    if (current_post->getItem()->getPriority() == Post::HIGH) {
      high_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::MEDIUM) {
      mid_posts_.push(current_post->getItem());
    }
    if (current_post->getItem()->getPriority() == Post::LOW) {
      low_posts_.push(current_post->getItem());
    }
    current_post = current_post->getNext();
  }

  while (!high_posts_.empty()) {
    return_posts.push_back(high_posts_.front());
    high_posts_.pop();
  }
  while (!mid_posts_.empty()) {
    return_posts.push_back(mid_posts_.front());
    mid_posts_.pop();
  }

  while (!low_posts_.empty()) {
    return_posts.push_back(low_posts_.front());
    low_posts_.pop();
  }

  return return_posts;
}
