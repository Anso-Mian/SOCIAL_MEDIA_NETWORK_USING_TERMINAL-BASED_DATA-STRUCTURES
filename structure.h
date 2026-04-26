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
    
    User* next; // For Hash Table chaining (and temporary Phase 2 linked list)
    
    Post* postsHead = nullptr; 
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
// ==========================================
// FUNCTION PROTOTYPES (Declarations)
// ==========================================
// User Management
void registerUser(string userName, string pass, string email, string bio);
bool loginUser(string userName, string pass);
User* searchUser(string userName);

// (You will add more prototypes here as you build Modules B, C, D, etc.)

void createPost(string content);
void displayPost();

void addFriend(string User1, string User2);
void displayFriends(string userName);

#endif