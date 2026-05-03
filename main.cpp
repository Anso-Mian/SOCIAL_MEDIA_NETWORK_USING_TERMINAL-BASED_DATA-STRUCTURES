#include <iostream>
#include "structure.h"
#include "implementation.cpp"

using namespace std;

int main() {
    // Initial  Check
    cout << "Phase 1: Structures loaded successfully!" << endl;
    cout << "Ready to build the Social Media Platform." << endl;
    
    // Registering Users
    registerUser("Ans","123","gmail","Life");
    registerUser("Ahmed","123","gmail","Life");
    registerUser("Ak","123","gmail","Life");
    registerUser("Sheila","123","gmail","Life");

    // Logging in
    loginUser("Ans","123");

    // Just Checking lol 
    cout<<currentUser->userName<<endl;
    cout<<dummyUserListHead->userName<<endl;
    cout<<dummyUserListHead->next->userName<<endl;

    // First Post Dawg
    createPost("Hello world, this is my first post!");
    createPost("Data structures is fun!");
    displayPost();


    // Testing the Friends
    addfriend("Ans","Ahmed");
    addfriend("Ak","Ans");
    addfriend("Sheila","Ans");
    displayFriends("Ans");
    displayFriends("Ahmed");

    removeFriend("Ans","Sheila");
    displayFriends("Ans");
    
    // checking the send message function
    sendMessage("Ahmed","Hello Ahmed, how are you?");
    sendMessage("Ahmed","Are you there?");
    sendMessage("Ak","Hey Ak, what's up?");
    latestMessage("Ahmed");
    latestMessage("Ak");
    deleteLatestMessage("Ahmed");
    latestMessage("Ahmed");

    //checking notification
    addNotification("Ans","Hey Wasp");
    addNotification("Ans","LOL");
    viewNotification();
    peekNotification();
    processNotification();
    viewNotification();

    // checking the viewFeed function
    viewFeed();

    return 0;
}   