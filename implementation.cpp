#include<iostream>
using namespace std;
#include "structure.h"

User* dummyUserListHead = nullptr;
User* currentUser = nullptr;
string PostIDCounter = "0";

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
    else{
        Post* newPost=new Post;
        newPost->postID=to_string(stoi(PostIDCounter) + 1);
        PostIDCounter = newPost->postID;
        newPost->content=content;
        newPost->owner=currentUser->userName;
        newPost->likes=0;
        newPost->next=nullptr;
        newPost->prev=nullptr;

        if(currentUser->postsHead==nullptr){
            currentUser->postsHead=newPost;
        }
        else{
            newPost->next=currentUser->postsHead;
            currentUser->postsHead->prev=newPost;
            currentUser->postsHead=newPost;
        }
    }
}

void displayPost(){
    if(currentUser==nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    else if(currentUser->postsHead==nullptr){
        cout<<"The user has no posts yet"<<endl;
        return;
    }
    else{
        Post* temp=currentUser->postsHead;
        while(temp!=nullptr){
            cout<<"Post ID: "<<temp->postID<<endl;
            cout<<"Content: "<<temp->content<<endl;
            cout<<"Owner: "<<temp->owner<<endl;
            cout<<"Likes: "<<temp->likes<<endl;
            temp=temp->next;
            cout<<endl;
        }
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
                cout<<"The user has no freinds"<<endl;
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
        Conversation* recieverConv=new Conversation;
        recieverConv->withUser=currentUser->userName;
        recieverConv->messageStackTop=nullptr;

        recieverConv->next=touser->conversationsHead;
        touser->conversationsHead=recieverConv;
        foundConversion=recieverConv;
    }
    Message* recieverMessage=new Message;
    recieverMessage->fromUser=currentUser->userName;
    recieverMessage->toUser=touser->userName;
    recieverMessage->text=text;
    recieverMessage->next=foundConversion->messageStackTop;
    foundConversion->messageStackTop=recieverMessage;

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

