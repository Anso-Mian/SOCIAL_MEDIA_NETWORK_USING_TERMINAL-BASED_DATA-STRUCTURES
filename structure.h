#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// NODE STRUCTURES
// ==========================================

struct Post {
    string postID;
    string content;
    string owner;
    int likes;
    Post* next;
    Post* prev; 
};

struct Edge {
    string friendUserName;
    Edge* next;
};

struct Message {
    string fromUser;
    string toUser;
    string text;
    string timestamp;
    Message* next;
};

struct Conversation {
    string withUser;
    Message* messageStackTop; 
    Conversation* next;
};

struct Story {
    string userName;
    string storyContent;
    Story* next;
};

struct Notification {
    string message;
    string userName;
    string timestamp;
    Notification* next;
};

struct AVLNode {
    string key; 
    int value;  
    AVLNode* left;
    AVLNode* right;
    int height;
};

// --- THE CENTRAL HUB ---
struct User {
    string userName; 
    string password;
    string email;
    string bio;
    string lastActive;
    
    Post* postsHead = nullptr;
    User* next; // For Hash Table chaining (and temporary Phase 2 linked list)
    
    Edge* friendsHead = nullptr; 
    Conversation* conversationsHead = nullptr;
    Notification* notificationsFront = nullptr;
    Notification* notificationsRear = nullptr;
};

// ==========================================
// GLOBAL VARIABLES
// ==========================================
extern User* currentUser;          // Tracks who is logged in
extern User* dummyUserListHead;    // Temporary list for Phase 2 before Hash Table
extern string PostIDCounter; // Global counter for unique Post IDs
extern Post* globalFeedHead; 
extern Post* globalFeedTail;
extern Story* storiesHead;
// ==========================================
// FUNCTION PROTOTYPES (Declarations)
// ==========================================
// User Management
void registerUser(string userName, string pass, string email, string bio);
bool loginUser(string userName, string pass);
User* searchUser(string userName);

// (You will add more prototypes here as you build Modules B, C, D, etc.)

void createPost(string content);
void deletePost(string targetID);
void displayPost();

void addFriend(string User1, string User2);
void displayFriends(string userName);
void removeFriend(string User1, string User2);

void sendMessage(string toUser,string text);
void latestMessage(string withUser);
void deleteLatestMessage(string withUser);
void viewConversation(string withUser);

void addNotification(string userName, string message);
void viewNotification();
void peekNotification();
void processNotification();

void viewFeed();
void displayTrendingPosts();

void addStory(string content);
void viewStory();

#endif