#include<iostream>
using namespace std;
#include "structure.h"

User* dummyUserListHead = nullptr;
User* currentUser = nullptr;
string PostIDCounter = "0";
Post* globalFeedHead=nullptr;
Post* globalFeedTail=nullptr;
Story* storiesHead = nullptr;

User* searchUser(string userName){
    User* temp = dummyUserListHead;
    while(temp!=nullptr){
        if(temp->userName==userName){
            return temp;
        }
        else{
            temp=temp->next;
        }
    }
    return nullptr;
}

void registerUser(string userName, string password, string email, string bio){
    if (searchUser(userName)==nullptr){
        cout<<"The User Name is available"<<endl;
        User* newUser=new User;
        newUser->userName=userName;
        newUser->password=password;
        newUser->email=email;
        newUser->bio=bio; 
        if(dummyUserListHead==nullptr){
            dummyUserListHead=newUser;
            dummyUserListHead->next=nullptr;
        }
        else{
        newUser->next=dummyUserListHead;
        dummyUserListHead=newUser;
        }
    }
    else{
        cout<<"The User Name is already taken"<<endl;
        return;
    }
}

bool loginUser(string userName,string pass){
    User *foundUser = searchUser(userName);

    if(foundUser == nullptr){
        cout<<"The user does not exist"<<endl;
        return false;
        }
        else{
            if(pass==foundUser->password){
            currentUser=foundUser;
            cout<<"The User "<<userName<<" has been successfully logged in"<<endl;
            return true;
            }
            else{
                cout<<"The password is incorrect"<<endl;
                return false;
            }
        }
}
void createPost(string content){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    
    Post* newGlobalPost = new Post;
    newGlobalPost->postID = to_string(stoi(PostIDCounter) + 1);
    PostIDCounter = newGlobalPost->postID;
    newGlobalPost->content = content;
    newGlobalPost->owner = currentUser->userName;
    newGlobalPost->likes = 0;
    
    newGlobalPost->prev = nullptr;
    newGlobalPost->next = globalFeedHead;

    if(globalFeedHead == nullptr){
        globalFeedHead = newGlobalPost;
        globalFeedTail = newGlobalPost; 
    }
    else{
        globalFeedHead->prev = newGlobalPost;
        globalFeedHead = newGlobalPost; 
    }

    Post* newUserPost = new Post;
    newUserPost->postID = newGlobalPost->postID; 
    newUserPost->owner = currentUser->userName;
    newUserPost->likes = 0;

    newUserPost->prev = nullptr;
    newUserPost->next = currentUser->postsHead;

    if(currentUser->postsHead != nullptr){
        currentUser->postsHead->prev = newUserPost;
    }
    currentUser->postsHead = newUserPost;
    
    cout << "Post created successfully! (ID: " << newGlobalPost->postID << ")" << endl;
}

void deletePost(string targetID){
    if(currentUser==nullptr){
        cout<<"THe user is not logged in"<<endl;
        return;
    }

    Post* temp=currentUser->postsHead;

    while(temp!=nullptr){
        if(temp->postID==targetID){
            break;
        }
        temp=temp->next;
    }

    if(temp==nullptr){
        cout<<"No such post with ID found"<<endl;
        return;
    }
    else if(temp==currentUser->postsHead){
        currentUser->postsHead=currentUser->postsHead->next;

        if(currentUser->postsHead!=nullptr){
        currentUser->postsHead->prev=nullptr;
        }
    }
    else{
        temp->prev->next=temp->next;
        if(temp->next!=nullptr){
            temp->next->prev=temp->prev;
        }
    }

    Post* globalTemp=globalFeedHead;
        while(globalTemp!=nullptr){
        if(globalTemp->postID==targetID){
            break;
        }
        globalTemp=globalTemp->next;
    }

    if(globalTemp==globalFeedHead){
        globalFeedHead=globalFeedHead->next;

        if(globalFeedHead!=nullptr){
        globalFeedHead->prev=nullptr;
        }
        else{
            globalFeedTail=nullptr;
        }
    }
    else{
        globalTemp->prev->next=globalTemp->next;

        if(globalTemp->next!=nullptr){
            globalTemp->next->prev=globalTemp->prev;
        }
        if(globalTemp==globalFeedTail){
            globalFeedTail=globalTemp->prev;
        }
    }

    delete temp;
    delete globalTemp;

    cout << "Post " << targetID << " has been deleted." << endl;
}

void displayPost(){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    
    if(currentUser->postsHead == nullptr){
        cout<<"You have no posts yet!"<<endl;
        return;
    }

    Post* temp = currentUser->postsHead;
    cout << "=== YOUR POSTS ===" << endl;

    while(temp != nullptr){
        cout<<"Post ID: "<<temp->postID<<endl;
        cout<<"Content: "<<temp->content<<endl;
        cout<<"Likes: "<<temp->likes<<endl;
        cout<<"------------------"<<endl;
        temp = temp->next; 
    }
}

void addfriend(string User1, string User2){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
        User* user1=searchUser(User1);
        User* user2=searchUser(User2);

        if(user1==nullptr && user2==nullptr){
            cout<<"The user "<<User1<<" and "<<User2<<" do not exist"<<endl;
            return;
        }
        else if(user1==nullptr){
        cout<<"The user "<<User1<<" does not exist"<<endl;
        return;
        }

        if(user2==nullptr){
        cout<<"The user "<<User2<<" does not exist"<<endl;
        return;
        }

       

        Edge* temp=user1->friendsHead;
        while(temp!=nullptr){
            if(temp->friendUserName==user2->userName){
                cout<<"The user "<<User2<<" is already a friend of "<<User1<<endl;
                return;
                }
                temp=temp->next;
            }

        Edge* newEdge1 = new Edge;
        newEdge1->friendUserName = user2->userName;
        newEdge1->next = user1->friendsHead; 

        user1->friendsHead = newEdge1;

        
        Edge* newEdge2 = new Edge;
        newEdge2->friendUserName = user1->userName;

        newEdge2->next = user2->friendsHead;
        user2->friendsHead = newEdge2;

        cout<<"The user "<<User1<<" and "<<User2<<" are now friends"<<endl;
        return; 

    }

void displayFriends(string userName){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }

    User* user=searchUser(userName);
    if(user==nullptr){
        cout<<"The user "<<userName<<" does not exist"<<endl;
        return;
        }
    else{
        if(user->friendsHead==nullptr){
                cout<<"The user has no friends"<<endl;
                return;
        }
        Edge* temp=user->friendsHead;
        int i=0;
        cout<<"The friends of "<<userName<<" are: "<<endl;
        while(temp!=nullptr){
            cout<<"FRIEND "<<++i<<" : "<< temp->friendUserName<<endl;
            temp=temp->next;
        }
    }
}

void removeFriend(string User1, string User2){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }

    User* user1=searchUser(User1);
    User* user2=searchUser(User2);

        if(user1==nullptr && user2==nullptr){
            cout<<"The user "<<User1<<" and "<<User2<<" do not exist"<<endl;
            return;
        }
        else if(user1==nullptr){
        cout<<"The user "<<User1<<" does not exist"<<endl;
        return;
        }

        else if(user2==nullptr){
        cout<<"The user "<<User2<<" does not exist"<<endl;
        return;
        }

        Edge* toDelete1=user1->friendsHead;

        if(toDelete1!=nullptr && toDelete1->friendUserName==User2){
            user1->friendsHead=user1->friendsHead->next;
            delete toDelete1;
        }
        else{
            Edge* current=user1->friendsHead;
            Edge* previous=nullptr;

            while(current!=nullptr && current->friendUserName== User2){
                previous=current;
                current=current->next;
            }

            if(current==nullptr){
                cout<<"The users are not friends"<<endl;
                return;
            }
            else{
                previous->next=current->next;
                delete current;
            }
        }

        Edge* toDelete2=user2->friendsHead;
        if(toDelete2!=nullptr && toDelete2->friendUserName==User1){
            user2->friendsHead=user2->friendsHead->next;
            delete toDelete2;
        }
        else{
            Edge* current=user2->friendsHead;
            Edge* previous=nullptr;
            
            while(current!=nullptr && current->friendUserName==User1){
                previous=current;
                current=current->next;
            }
            if(current==nullptr){
                cout<<"The users are not friends"<<endl;
                return;
            }
            else{
                previous->next=current->next;
                delete current;
            }
        }

        cout<<"The "<<User1<<" and "<<User2<<" are not friends."<<endl;
}

void sendMessage(string toUser,string text){
      if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    bool found=false;
    User* touser=searchUser(toUser);
    if (touser == nullptr) {
        cout << "Error: User does not exist." << endl;
        return;
    }
    Conversation* foundConversion=nullptr;
    Conversation* temp=currentUser->conversationsHead;
    while(temp!=nullptr){
        if(temp->withUser==toUser){
            found=true;
            foundConversion=temp;
            break;
        }
        temp = temp->next;
    }
    if(!found && foundConversion==nullptr){
        Conversation* newConversation=new Conversation;
        newConversation->withUser=toUser;
        newConversation->messageStackTop=nullptr;

        newConversation->next=currentUser->conversationsHead;
        currentUser->conversationsHead=newConversation;

        foundConversion=newConversation;
    }
    Message* newMessage=new Message;
    newMessage->fromUser=currentUser->userName;
    newMessage->toUser=toUser;
    newMessage->text=text;
    
    newMessage->next=foundConversion->messageStackTop;
    foundConversion->messageStackTop=newMessage;

    foundConversion=nullptr;
    temp=touser->conversationsHead;
    found=false;
    
    while(temp!=nullptr){
        if(temp->withUser==currentUser->userName){
            found=true;
            foundConversion=temp;
            break;
        }
        temp=temp->next;
    }

    if(!found && foundConversion==nullptr){
        Conversation* receiverConv=new Conversation;
        receiverConv->withUser=currentUser->userName;
        receiverConv->messageStackTop=nullptr;

        receiverConv->next=touser->conversationsHead;
        touser->conversationsHead=receiverConv;
        foundConversion=receiverConv;
    }
    Message* receiverMessage=new Message;
    receiverMessage->fromUser=currentUser->userName;
    receiverMessage->toUser=touser->userName;
    receiverMessage->text=text;
    receiverMessage->next=foundConversion->messageStackTop;
    foundConversion->messageStackTop=receiverMessage;

    cout << "Message sent successfully to " << toUser<< endl;
}

void latestMessage(string withUser){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* touser=searchUser(withUser);
    if(touser==nullptr){
        cout << "Error: User does not exist." << endl;
        return;
    }
    Conversation* temp=currentUser->conversationsHead;
    Conversation* targetConv=nullptr;
    while(temp!=nullptr){
        if(temp->withUser==withUser){
            targetConv=temp;
            break;
        }
        temp=temp->next;
    }

    if(targetConv==nullptr){
        cout<<"No conversation found."<<endl;
        return;
    }
    else if(targetConv){
        if(targetConv->messageStackTop==nullptr){
            cout<<"No messages in this conversation yet."<<endl;
            return;
        }
        else{
            cout << "From: " << targetConv->messageStackTop->fromUser << " - " << targetConv->messageStackTop->text << endl;
        }
    }
}

void deleteLatestMessage(string withUser){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* touser=searchUser(withUser);
    if(touser==nullptr){
        cout << "Error: User does not exist." << endl;
        return;
    }
    Conversation* temp=currentUser->conversationsHead;
    Conversation* targetConv=nullptr;
    while(temp!=nullptr){
        if(temp->withUser==withUser){
            targetConv=temp;
            break;
        }
        temp=temp->next;
    }

    if(targetConv==nullptr){
        cout<<"No conversation found."<<endl;
        return;
    }
    else if(targetConv){
        if(targetConv->messageStackTop==nullptr){
            cout<<"No messages in this conversation yet."<<endl;
            return;
        }
        else{
            Message* toDelete=targetConv->messageStackTop;
            targetConv->messageStackTop=targetConv->messageStackTop->next;
            delete toDelete;
            cout<<"The latest message has been deleted."<<endl;
        }
    }
}

void viewConversation(string withUser){
    if(currentUser==nullptr){
        cout<<"THe user is not logged in"<<endl;
        return;
    }

    User* targetUser=searchUser(withUser);
    if(targetUser==nullptr){
        cout<<"No such user exists"<<endl;
        return;
    }

    Conversation* temp= currentUser->conversationsHead;

    while(temp!=nullptr){
        if(temp->withUser==targetUser->userName){
            break;
        }
        temp=temp->next;
    }
    if(temp==nullptr){
        cout<<"No such chat with user found"<<endl;
        return;
    }
    Message* messages=temp->messageStackTop;
    if(messages==nullptr){
        cout << "No messages in this conversation." << endl;
        return;
    }

    cout << "=== Chat History with " << withUser << " ===" << endl;
    while(messages!=nullptr){
        cout<<"- Sent by: "<<messages->fromUser<<endl;
        cout<<"- Sent to: "<<messages->toUser<<endl;
        cout<<"- Text: "<<messages->text<<endl;

        messages=messages->next;
    }
}

void addNotification(string userName, string message){
    User* targetUser=searchUser(userName);
    if(targetUser==nullptr){
        cout<<"The user does not exist"<<endl;
        return;
    }
    
    Notification* newNotification=new Notification;
    newNotification->message=message;
    newNotification->next=nullptr;

    if(targetUser->notificationsFront==nullptr){
        targetUser->notificationsFront=newNotification;
        targetUser->notificationsRear=newNotification;
    }
    else{
        targetUser->notificationsRear->next=newNotification;
        targetUser->notificationsRear = newNotification;
    }
}

void viewNotification(){

    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }

    Notification* temp=currentUser->notificationsFront;
    
    if(temp==nullptr){
        cout<<"You have no notifications"<<endl;
        return;
    }
    else{
        while(temp !=nullptr){
            cout<<"- "<<temp->message<<endl;
            temp=temp->next;
        }
    }
}

void peekNotification() {
    if(currentUser == nullptr){
        cout << "The user is not logged in" << endl;
        return;
    }
    
    if(currentUser->notificationsFront == nullptr) {
        cout << "You have no new notifications." << endl;
        return;
    }
    
    cout << "Next Notification: " << currentUser->notificationsFront->message << endl;
}

void processNotification(){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }

    if(currentUser->notificationsFront == nullptr){
        cout<<"You have no notifications to process"<<endl;
        return;
    }

    Notification* toDelete = currentUser->notificationsFront;

    cout << "Processing Notification: " << toDelete->message << endl;

    currentUser->notificationsFront = currentUser->notificationsFront->next;

    // 6. SAFETY CATCH: If that was the last notification, reset the rear pointer too
    if(currentUser->notificationsFront == nullptr){
        currentUser->notificationsRear = nullptr;
    }

    delete toDelete;
    cout << "Notification removed from queue." << endl;
}

void viewFeed(){

    if(currentUser==nullptr){
        cout<<"THe user is not logged in"<<endl;
        return;
    }

    Post* currentPost=globalFeedHead;

    if(globalFeedHead!=nullptr){
        while(true){
            int choice;
            cout<<"- Owner: "<<currentPost->owner<<endl;
            cout<<"- Content: "<<currentPost->content<<endl;
            cout<<"- Likes: "<<currentPost->likes<<endl;

            label:
            cout<<"----------- FEED ACTIONS -----------"<<endl;
            cout<<"[1] Next, "<<"[2] Previous, "<<"[3] Like, "<<"[4] Quit"<<endl;

            cout<<"Enter your choice:";
            cin>>choice;
            
            if(choice < 1 || choice > 4){
                cout<<"The wrong choice"<<endl;
                goto label;
            }
            else{
                switch(choice){
                    case 1:
                        if(currentPost->next!=nullptr){
                            currentPost=currentPost->next;
                        }
                        else{
                            cout<<"You have reached the bottom"<<endl;
                        }
                        break;
                    case 2:
                        if(currentPost->prev!=nullptr){
                            currentPost=currentPost->prev;
                        }
                        else{
                            cout<<"You are the at the top"<<endl;
                        }
                        break;
                    case 3:
                        ++currentPost->likes;
                        break;
                    case 4:
                        return;
                    default:
                        cout<<"Error Occurred"<<endl;
                        return;
                }
            }   
        }
    }
    else{
        cout << "The feed is currently empty!" << endl;
        return;
    }
}

void addStory(string content){
    if(currentUser==nullptr){
        cout<<"THe user is not logged in."<<endl;
        return;
    }
    Story* newStory=new Story;
    newStory->userName=currentUser->userName;
    newStory->storyContent=content;

    if(storiesHead==nullptr){
        storiesHead=newStory;
        newStory->next=storiesHead;
    }
    else{
        Story* temp=storiesHead;
        while(temp->next!=storiesHead){
            temp= temp->next;
        }

        temp->next=newStory;
        newStory->next=storiesHead;
    }
}

void viewStory(){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }

    else if(storiesHead==nullptr){
        cout<<"There are no stories"<<endl;
        return;
    }
    else{
        Story* temp = storiesHead;
        while(true){
            int choice;
            cout<<"------- Story ----------"<<endl;
            cout<<"- User Name: "<<temp->userName<<endl;
            cout<<"- Story Content: "<<temp->storyContent<<endl;

            label:
            cout<<"----------- FEED ACTIONS -----------"<<endl;
            cout<<"[1] Next, "<<"[2] Quit"<<endl;

            cout<<"Enter your choice:";
            cin>>choice;
            
            if(choice < 1 || choice > 2){
                cout<<"The wrong choice"<<endl;
                goto label;
            }

            switch(choice){
                case 1:
                    temp=temp->next;
                    break;
                case 2:
                    return;
                default:
                    cout<<"Some Error occurred"<<endl;
                    return;
            }
        }
    }
}
