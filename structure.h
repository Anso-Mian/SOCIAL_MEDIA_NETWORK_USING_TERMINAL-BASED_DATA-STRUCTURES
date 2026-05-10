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

struct User {
    string userName; 
    string password;
    string email;
    string bio;
    string lastActive;
    
    Post* postsHead = nullptr;
    User* next;
    
    Edge* friendsHead = nullptr; 
    Conversation* conversationsHead = nullptr;
    Notification* notificationsFront = nullptr;
    Notification* notificationsRear = nullptr;
};

// ==========================================
// GLOBAL VARIABLES
// ==========================================
const int TABLE_SIZE = 10;
extern User* hashTable[TABLE_SIZE];
extern User* currentUser;
extern string PostIDCounter;
extern Post* globalFeedHead; 
extern Post* globalFeedTail;
extern Story* storiesHead;
extern AVLNode* userAVLRoot;
extern AVLNode* postAVLRoot;

// ==========================================
// FUNCTION PROTOTYPES
// ==========================================

int hashFunction(string key);
void registerUser(string userName, string pass, string email, string bio);
bool loginUser(string userName, string pass);
User* searchUser(string userName);
void deleteUser(string userName);
void displayAllUsers();

void createPost(string content);
void deletePost(string targetID);
void displayPost();
void likePost(string postID);
void displayTrendingPosts();

void addfriend(string User1, string User2);
void displayFriends(string userName);
void removeFriend(string User1, string User2);
void BFS(string startUser);
void DFS(string startUser);

void sendMessage(string toUser, string text);
void latestMessage(string withUser);
void deleteLatestMessage(string withUser);
void viewConversation(string withUser);

void addNotification(string userName, string message);
void viewNotification();
void peekNotification();
void processNotification();

void viewFeed();

void addStory(string content);
void viewStory();

AVLNode* avlInsert(AVLNode* node, string key, int value);
AVLNode* avlDelete(AVLNode* node, string key);
AVLNode* avlSearch(AVLNode* node, string key);
void avlUpdateValue(AVLNode* node, string key, int value);
void inorderTraversal(AVLNode* node);
void getTopK(AVLNode* root, int k);
void rangeQuery(AVLNode* node, int minVal, int maxVal);

#endif
