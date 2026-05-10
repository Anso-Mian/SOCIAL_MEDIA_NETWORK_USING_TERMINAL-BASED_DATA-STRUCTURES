#include<iostream>
#include "structure.h"
#include "implementation.cpp"

using namespace std;

int main(){
    for(int i = 0; i < TABLE_SIZE; i++) hashTable[i] = nullptr;

    int choice;
    while(true){
        if(currentUser != nullptr) { cout<<"Logged in as: "<<currentUser->userName<<endl; }
        else { cout<<"Not logged in"<<endl; }

        cout<<"================ MAIN MENU ================="<<endl;
        cout<<"1. User Management"<<endl;
        cout<<"2. Social Network"<<endl;
        cout<<"3. Posts & Feed"<<endl;
        cout<<"4. Stories"<<endl;
        cout<<"5. Notifications"<<endl;
        cout<<"6. Analytics & Ranking"<<endl;
        cout<<"7. Messaging System"<<endl;
        cout<<"8. Exit"<<endl;
        cout<<"============================================"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1:{
                int sub;
                cout<<"1. Register User"<<endl;
                cout<<"2. Login"<<endl;
                cout<<"3. Logout"<<endl;
                cout<<"4. Delete User"<<endl;
                cout<<"5. Search User"<<endl;
                cout<<"6. Display Users"<<endl;
                cout<<"7. Back"<<endl;
                cout<<"Enter choice: ";
                cin>>sub;
                cin.ignore();
                switch(sub){
                    case 1:{
                        string u, p, e, b;
                        cout<<"Username: "; getline(cin, u);
                        cout<<"Password: "; getline(cin, p);
                        cout<<"Email: "; getline(cin, e);
                        cout<<"Bio: "; getline(cin, b);
                        registerUser(u, p, e, b);
                        break;
                    }
                    case 2:{
                        string u, p;
                        cout<<"Username: "; getline(cin, u);
                        cout<<"Password: "; getline(cin, p);
                        loginUser(u, p);
                        break;
                    }
                    case 3:{
                        if(currentUser == nullptr) { cout<<"No user is logged in"<<endl; }
                        else{
                            cout<<currentUser->userName<<" logged out"<<endl;
                            currentUser = nullptr;
                        }
                        break;
                    }
                    case 4:{
                        string u;
                        cout<<"Username: "; getline(cin, u);
                        deleteUser(u);
                        break;
                    }
                    case 5:{
                        string u;
                        cout<<"Username: "; getline(cin, u);
                        User* found = searchUser(u);
                        if(found) { cout<<"User found: "<<found->userName<<endl; }
                        else { cout<<"User not found"<<endl; }
                        break;
                    }
                    case 6:
                        displayAllUsers();
                        break;
                    case 7:
                        break;
                    default:
                        cout<<"Invalid choice"<<endl;
                }
                break;
            }
            case 2:{
                int sub;
                cout<<"1. Add Friend"<<endl;
                cout<<"2. Remove Friend"<<endl;
                cout<<"3. View Friends"<<endl;
                cout<<"4. BFS Traversal"<<endl;
                cout<<"5. DFS Traversal"<<endl;
                cout<<"6. Back"<<endl;
                cout<<"Enter choice: ";
                cin>>sub;
                cin.ignore();
                switch(sub){
                    case 1:{
                        string u1, u2;
                        cout<<"User1: "; getline(cin, u1);
                        cout<<"User2: "; getline(cin, u2);
                        addfriend(u1, u2);
                        break;
                    }
                    case 2:{
                        string u1, u2;
                        cout<<"User1: "; getline(cin, u1);
                        cout<<"User2: "; getline(cin, u2);
                        removeFriend(u1, u2);
                        break;
                    }
                    case 3:{
                        string u;
                        cout<<"Username: "; getline(cin, u);
                        displayFriends(u);
                        break;
                    }
                    case 4:{
                        string u;
                        cout<<"Start User: "; getline(cin, u);
                        BFS(u);
                        break;
                    }
                    case 5:{
                        string u;
                        cout<<"Start User: "; getline(cin, u);
                        DFS(u);
                        break;
                    }
                    case 6:
                        break;
                    default:
                        cout<<"Invalid choice"<<endl;
                }
                break;
            }
            case 3:{
                int sub;
                cout<<"1. Create Post"<<endl;
                cout<<"2. Delete Post"<<endl;
                cout<<"3. View My Posts"<<endl;
                cout<<"4. View Feed"<<endl;
                cout<<"5. Like Post"<<endl;
                cout<<"6. Back"<<endl;
                cout<<"Enter choice: ";
                cin>>sub;
                cin.ignore();
                switch(sub){
                    case 1:{
                        string content;
                        cout<<"Content: "; getline(cin, content);
                        createPost(content);
                        break;
                    }
                    case 2:{
                        string id;
                        cout<<"Post ID: "; getline(cin, id);
                        deletePost(id);
                        break;
                    }
                    case 3:
                        displayPost();
                        break;
                    case 4:
                        viewFeed();
                        break;
                    case 5:{
                        string id;
                        cout<<"Post ID: "; getline(cin, id);
                        likePost(id);
                        break;
                    }
                    case 6:
                        break;
                    default:
                        cout<<"Invalid choice"<<endl;
                }
                break;
            }
            case 4:{
                int sub;
                cout<<"1. Add Story"<<endl;
                cout<<"2. View Stories"<<endl;
                cout<<"3. Back"<<endl;
                cout<<"Enter choice: ";
                cin>>sub;
                cin.ignore();
                switch(sub){
                    case 1:{
                        string content;
                        cout<<"Story: "; getline(cin, content);
                        addStory(content);
                        break;
                    }
                    case 2:
                        viewStory();
                        break;
                    case 3:
                        break;
                    default:
                        cout<<"Invalid choice"<<endl;
                }
                break;
            }
            case 5:{
                int sub;
                cout<<"1. View Notifications"<<endl;
                cout<<"2. Peek Notification"<<endl;
                cout<<"3. Process Notification"<<endl;
                cout<<"4. Back"<<endl;
                cout<<"Enter choice: ";
                cin>>sub;
                cin.ignore();
                switch(sub){
                    case 1:
                        viewNotification();
                        break;
                    case 2:
                        peekNotification();
                        break;
                    case 3:
                        processNotification();
                        break;
                    case 4:
                        break;
                    default:
                        cout<<"Invalid choice"<<endl;
                }
                break;
            }
            case 6:{
                int sub;
                cout<<"1. Show Top Active Users"<<endl;
                cout<<"2. Show Most Liked Posts"<<endl;
                cout<<"3. Display Sorted Data"<<endl;
                cout<<"4. Range Query"<<endl;
                cout<<"5. Back"<<endl;
                cout<<"Enter choice: ";
                cin>>sub;
                cin.ignore();
                switch(sub){
                    case 1:
                        getTopK(userAVLRoot, 5);
                        break;
                    case 2:
                        getTopK(postAVLRoot, 5);
                        break;
                    case 3:
                        cout<<"Users (sorted):"<<endl;
                        inorderTraversal(userAVLRoot);
                        cout<<"Posts (sorted):"<<endl;
                        inorderTraversal(postAVLRoot);
                        break;
                    case 4:{
                        int mn, mx;
                        cout<<"Min value: "; cin>>mn;
                        cout<<"Max value: "; cin>>mx;
                        cin.ignore();
                        cout<<"Users in range:"<<endl;
                        rangeQuery(userAVLRoot, mn, mx);
                        cout<<"Posts in range:"<<endl;
                        rangeQuery(postAVLRoot, mn, mx);
                        break;
                    }
                    case 5:
                        break;
                    default:
                        cout<<"Invalid choice"<<endl;
                }
                break;
            }
            case 7:{
                int sub;
                cout<<"1. Send Message"<<endl;
                cout<<"2. View Latest Message"<<endl;
                cout<<"3. Pop Message"<<endl;
                cout<<"4. View Conversation"<<endl;
                cout<<"5. Back"<<endl;
                cout<<"Enter choice: ";
                cin>>sub;
                cin.ignore();
                switch(sub){
                    case 1:{
                        string to, text;
                        cout<<"To: "; getline(cin, to);
                        cout<<"Message: "; getline(cin, text);
                        sendMessage(to, text);
                        break;
                    }
                    case 2:{
                        string u;
                        cout<<"With User: "; getline(cin, u);
                        latestMessage(u);
                        break;
                    }
                    case 3:{
                        string u;
                        cout<<"With User: "; getline(cin, u);
                        deleteLatestMessage(u);
                        break;
                    }
                    case 4:{
                        string u;
                        cout<<"With User: "; getline(cin, u);
                        viewConversation(u);
                        break;
                    }
                    case 5:
                        break;
                    default:
                        cout<<"Invalid choice"<<endl;
                }
                break;
            }
            case 8:
                return 0;
            default:
                cout<<"Invalid choice"<<endl;
        }
    }
    return 0;
}
