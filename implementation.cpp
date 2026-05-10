#include<iostream>
using namespace std;
#include "structure.h"

User* hashTable[TABLE_SIZE] = {nullptr};
User* currentUser = nullptr;
string PostIDCounter = "0";
Post* globalFeedHead = nullptr;
Post* globalFeedTail = nullptr;
Story* storiesHead = nullptr;
AVLNode* userAVLRoot = nullptr;
AVLNode* postAVLRoot = nullptr;

// ==========================================
// AVL TREE HELPERS
// ==========================================

int getHeight(AVLNode* node){
    if(node == nullptr) { return 0; }
    return node->height;
}

int getBalance(AVLNode* node){
    if(node == nullptr) { return 0; }
    return getHeight(node->left) - getHeight(node->right);
}

int maxVal(int a, int b){
    return (a > b) ? a : b;
}

AVLNode* rightRotate(AVLNode* y){
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = maxVal(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maxVal(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* leftRotate(AVLNode* x){
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = maxVal(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maxVal(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLNode* minValueNode(AVLNode* node){
    AVLNode* current = node;
    while(current->left != nullptr) { current = current->left; }
    return current;
}

AVLNode* avlInsert(AVLNode* node, string key, int value){
    if(node == nullptr){
        AVLNode* newNode = new AVLNode;
        newNode->key = key;
        newNode->value = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }
    if(key < node->key) { node->left = avlInsert(node->left, key, value); }
    else if(key > node->key) { node->right = avlInsert(node->right, key, value); }
    else{
        node->value = value;
        return node;
    }
    node->height = maxVal(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalance(node);
    if(balance > 1 && key < node->left->key) { return rightRotate(node); }
    if(balance < -1 && key > node->right->key) { return leftRotate(node); }
    if(balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

AVLNode* avlDelete(AVLNode* node, string key){
    if(node == nullptr) { return nullptr; }
    if(key < node->key) { node->left = avlDelete(node->left, key); }
    else if(key > node->key) { node->right = avlDelete(node->right, key); }
    else{
        if(node->left == nullptr || node->right == nullptr){
            AVLNode* temp = node->left ? node->left : node->right;
            if(temp == nullptr){
                temp = node;
                node = nullptr;
            }
            else { *node = *temp; }
            delete temp;
        }
        else{
            AVLNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = avlDelete(node->right, temp->key);
        }
    }
    if(node == nullptr) { return nullptr; }
    node->height = maxVal(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalance(node);
    if(balance > 1 && getBalance(node->left) >= 0) { return rightRotate(node); }
    if(balance > 1 && getBalance(node->left) < 0){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && getBalance(node->right) <= 0) { return leftRotate(node); }
    if(balance < -1 && getBalance(node->right) > 0){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

AVLNode* avlSearch(AVLNode* node, string key){
    if(node == nullptr || node->key == key) { return node; }
    if(key < node->key) { return avlSearch(node->left, key); }
    return avlSearch(node->right, key);
}

void avlUpdateValue(AVLNode* node, string key, int value){
    AVLNode* found = avlSearch(node, key);
    if(found != nullptr) { found->value = value; }
}

void inorderTraversal(AVLNode* node){
    if(node == nullptr) { return; }
    inorderTraversal(node->left);
    cout<<node->key<<" : "<<node->value<<endl;
    inorderTraversal(node->right);
}

int collectNodes(AVLNode* node, AVLNode* arr[], int idx){
    if(node == nullptr) { return idx; }
    idx = collectNodes(node->left, arr, idx);
    arr[idx++] = node;
    idx = collectNodes(node->right, arr, idx);
    return idx;
}

void getTopK(AVLNode* root, int k){
    if(root == nullptr){
        cout<<"No data available"<<endl;
        return;
    }
    AVLNode* arr[200];
    int count = collectNodes(root, arr, 0);
    for(int i = 0; i < count - 1; i++){
        int maxIdx = i;
        for(int j = i + 1; j < count; j++){
            if(arr[j]->value > arr[maxIdx]->value) { maxIdx = j; }
        }
        AVLNode* temp = arr[i];
        arr[i] = arr[maxIdx];
        arr[maxIdx] = temp;
    }
    cout<<"Top "<<k<<" Rankings:"<<endl;
    for(int i = 0; i < k && i < count; i++){
        cout<<i+1<<". "<<arr[i]->key<<" - "<<arr[i]->value<<endl;
    }
}

void rangeQuery(AVLNode* node, int minVal, int maxVal){
    if(node == nullptr) { return; }
    rangeQuery(node->left, minVal, maxVal);
    if(node->value >= minVal && node->value <= maxVal){
        cout<<node->key<<" : "<<node->value<<endl;
    }
    rangeQuery(node->right, minVal, maxVal);
}

// ==========================================
// MODULE A - HASH TABLE
// ==========================================

int hashFunction(string key){
    int sum = 0;
    for(int i = 0; i < (int)key.length(); i++){
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

User* searchUser(string userName){
    int index = hashFunction(userName);
    User* temp = hashTable[index];
    while(temp != nullptr){
        if(temp->userName == userName) { return temp; }
        temp = temp->next;
    }
    return nullptr;
}

void registerUser(string userName, string password, string email, string bio){
    if(searchUser(userName) != nullptr){
        cout<<"The User Name is already taken"<<endl;
        return;
    }
    cout<<"The User Name is available"<<endl;
    User* newUser = new User;
    newUser->userName = userName;
    newUser->password = password;
    newUser->email = email;
    newUser->bio = bio;
    newUser->postsHead = nullptr;
    newUser->friendsHead = nullptr;
    newUser->conversationsHead = nullptr;
    newUser->notificationsFront = nullptr;
    newUser->notificationsRear = nullptr;

    int index = hashFunction(userName);
    newUser->next = hashTable[index];
    hashTable[index] = newUser;

    userAVLRoot = avlInsert(userAVLRoot, userName, 0);
}

bool loginUser(string userName, string pass){
    User* foundUser = searchUser(userName);
    if(foundUser == nullptr){
        cout<<"The user does not exist"<<endl;
        return false;
    }
    if(pass == foundUser->password){
        currentUser = foundUser;
        cout<<"The User "<<userName<<" has been successfully logged in"<<endl;
        return true;
    }
    else{
        cout<<"The password is incorrect"<<endl;
        return false;
    }
}

void deleteUser(string userName){
    User* user = searchUser(userName);
    if(user == nullptr){
        cout<<"User not found"<<endl;
        return;
    }

    Post* userPost = user->postsHead;
    while(userPost != nullptr){
        string pid = userPost->postID;
        Post* gTemp = globalFeedHead;
        while(gTemp != nullptr){
            if(gTemp->postID == pid){
                if(gTemp->prev != nullptr) { gTemp->prev->next = gTemp->next; }
                else { globalFeedHead = gTemp->next; }
                if(gTemp->next != nullptr) { gTemp->next->prev = gTemp->prev; }
                else { globalFeedTail = gTemp->prev; }
                postAVLRoot = avlDelete(postAVLRoot, pid);
                delete gTemp;
                break;
            }
            gTemp = gTemp->next;
        }
        Post* toDeletePost = userPost;
        userPost = userPost->next;
        delete toDeletePost;
    }

    for(int i = 0; i < TABLE_SIZE; i++){
        User* temp = hashTable[i];
        while(temp != nullptr){
            if(temp->userName != userName){
                Edge* prev = nullptr;
                Edge* curr = temp->friendsHead;
                while(curr != nullptr){
                    if(curr->friendUserName == userName){
                        if(prev == nullptr) { temp->friendsHead = curr->next; }
                        else { prev->next = curr->next; }
                        delete curr;
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
            }
            temp = temp->next;
        }
    }

    int index = hashFunction(userName);
    User* prev = nullptr;
    User* curr = hashTable[index];
    while(curr != nullptr){
        if(curr->userName == userName) { break; }
        prev = curr;
        curr = curr->next;
    }
    if(curr != nullptr){
        if(prev == nullptr) { hashTable[index] = curr->next; }
        else { prev->next = curr->next; }
    }

    userAVLRoot = avlDelete(userAVLRoot, userName);

    if(currentUser == user) { currentUser = nullptr; }

    delete user;
    cout<<userName<<" deleted"<<endl;
}

void displayAllUsers(){
    cout<<"=== ALL USERS ==="<<endl;
    bool any = false;
    for(int i = 0; i < TABLE_SIZE; i++){
        User* temp = hashTable[i];
        while(temp != nullptr){
            cout<<"- "<<temp->userName<<endl;
            any = true;
            temp = temp->next;
        }
    }
    if(!any) { cout<<"No users registered"<<endl; }
}

// ==========================================
// MODULE C - POSTS
// ==========================================

void createPost(string content){
    if(currentUser == nullptr){
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
    newUserPost->content = content;
    newUserPost->owner = currentUser->userName;
    newUserPost->likes = 0;
    newUserPost->prev = nullptr;
    newUserPost->next = currentUser->postsHead;

    if(currentUser->postsHead != nullptr){
        currentUser->postsHead->prev = newUserPost;
    }
    currentUser->postsHead = newUserPost;

    postAVLRoot = avlInsert(postAVLRoot, newGlobalPost->postID, 0);

    AVLNode* userNode = avlSearch(userAVLRoot, currentUser->userName);
    if(userNode != nullptr) { avlUpdateValue(userAVLRoot, currentUser->userName, userNode->value + 1); }

    cout<<"Post created successfully! (ID: "<<newGlobalPost->postID<<")"<<endl;
}

void deletePost(string targetID){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }

    Post* temp = currentUser->postsHead;
    while(temp != nullptr){
        if(temp->postID == targetID) { break; }
        temp = temp->next;
    }

    if(temp == nullptr){
        cout<<"No such post with ID found"<<endl;
        return;
    }
    else if(temp == currentUser->postsHead){
        currentUser->postsHead = currentUser->postsHead->next;
        if(currentUser->postsHead != nullptr) { currentUser->postsHead->prev = nullptr; }
    }
    else{
        temp->prev->next = temp->next;
        if(temp->next != nullptr) { temp->next->prev = temp->prev; }
    }

    Post* globalTemp = globalFeedHead;
    while(globalTemp != nullptr){
        if(globalTemp->postID == targetID) { break; }
        globalTemp = globalTemp->next;
    }

    if(globalTemp != nullptr){
        if(globalTemp == globalFeedHead){
            globalFeedHead = globalFeedHead->next;
            if(globalFeedHead != nullptr) { globalFeedHead->prev = nullptr; }
            else { globalFeedTail = nullptr; }
        }
        else{
            globalTemp->prev->next = globalTemp->next;
            if(globalTemp->next != nullptr) { globalTemp->next->prev = globalTemp->prev; }
            if(globalTemp == globalFeedTail) { globalFeedTail = globalTemp->prev; }
        }
        delete globalTemp;
    }

    postAVLRoot = avlDelete(postAVLRoot, targetID);

    delete temp;
    cout<<"Post "<<targetID<<" has been deleted."<<endl;
}

void displayPost(){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    
    if(currentUser->postsHead == nullptr){
        cout<<"You have no posts yet!"<<endl;
        return;
    }

    Post* temp = currentUser->postsHead;
    cout<<"=== YOUR POSTS ==="<<endl;
    while(temp != nullptr){
        cout<<"Post ID: "<<temp->postID<<endl;
        cout<<"Content: "<<temp->content<<endl;
        cout<<"Likes: "<<temp->likes<<endl;
        cout<<"------------------"<<endl;
        temp = temp->next; 
    }
}

void likePost(string postID){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    Post* temp = globalFeedHead;
    while(temp != nullptr){
        if(temp->postID == postID) { break; }
        temp = temp->next;
    }
    if(temp == nullptr){
        cout<<"Post not found"<<endl;
        return;
    }
    temp->likes++;
    postAVLRoot = avlInsert(postAVLRoot, postID, temp->likes);
    addNotification(temp->owner, currentUser->userName + " liked your post!");
    cout<<"Post liked!"<<endl;
}

void displayTrendingPosts(){
    getTopK(postAVLRoot, 5);
}

// ==========================================
// MODULE B - GRAPH
// ==========================================

void addfriend(string User1, string User2){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* user1 = searchUser(User1);
    User* user2 = searchUser(User2);

    if(user1 == nullptr && user2 == nullptr){
        cout<<"The user "<<User1<<" and "<<User2<<" do not exist"<<endl;
        return;
    }
    else if(user1 == nullptr){
        cout<<"The user "<<User1<<" does not exist"<<endl;
        return;
    }
    if(user2 == nullptr){
        cout<<"The user "<<User2<<" does not exist"<<endl;
        return;
    }

    Edge* temp = user1->friendsHead;
    while(temp != nullptr){
        if(temp->friendUserName == user2->userName){
            cout<<"The user "<<User2<<" is already a friend of "<<User1<<endl;
            return;
        }
        temp = temp->next;
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
}

void displayFriends(string userName){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* user = searchUser(userName);
    if(user == nullptr){
        cout<<"The user "<<userName<<" does not exist"<<endl;
        return;
    }
    if(user->friendsHead == nullptr){
        cout<<"The user has no friends"<<endl;
        return;
    }
    Edge* temp = user->friendsHead;
    int i = 0;
    cout<<"The friends of "<<userName<<" are: "<<endl;
    while(temp != nullptr){
        cout<<"FRIEND "<<++i<<" : "<<temp->friendUserName<<endl;
        temp = temp->next;
    }
}

void removeFriend(string User1, string User2){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* user1 = searchUser(User1);
    User* user2 = searchUser(User2);

    if(user1 == nullptr && user2 == nullptr){
        cout<<"The user "<<User1<<" and "<<User2<<" do not exist"<<endl;
        return;
    }
    else if(user1 == nullptr){
        cout<<"The user "<<User1<<" does not exist"<<endl;
        return;
    }
    else if(user2 == nullptr){
        cout<<"The user "<<User2<<" does not exist"<<endl;
        return;
    }

    Edge* toDelete1 = user1->friendsHead;
    if(toDelete1 != nullptr && toDelete1->friendUserName == User2){
        user1->friendsHead = user1->friendsHead->next;
        delete toDelete1;
    }
    else{
        Edge* current = user1->friendsHead;
        Edge* previous = nullptr;
        while(current != nullptr && current->friendUserName != User2){
            previous = current;
            current = current->next;
        }
        if(current == nullptr){
            cout<<"The users are not friends"<<endl;
            return;
        }
        else{
            previous->next = current->next;
            delete current;
        }
    }

    Edge* toDelete2 = user2->friendsHead;
    if(toDelete2 != nullptr && toDelete2->friendUserName == User1){
        user2->friendsHead = user2->friendsHead->next;
        delete toDelete2;
    }
    else{
        Edge* current = user2->friendsHead;
        Edge* previous = nullptr;
        while(current != nullptr && current->friendUserName != User1){
            previous = current;
            current = current->next;
        }
        if(current == nullptr){
            cout<<"The users are not friends"<<endl;
            return;
        }
        else{
            previous->next = current->next;
            delete current;
        }
    }

    cout<<"The "<<User1<<" and "<<User2<<" are not friends."<<endl;
}

void BFS(string startUser){
    if(searchUser(startUser) == nullptr){
        cout<<"User not found"<<endl;
        return;
    }
    string queue[200];
    string visited[200];
    int front = 0, rear = 0, visitedCount = 0;

    queue[rear++] = startUser;
    visited[visitedCount++] = startUser;

    cout<<"BFS from "<<startUser<<": ";
    while(front < rear){
        string current = queue[front++];
        cout<<current<<" ";
        User* user = searchUser(current);
        if(user == nullptr) { continue; }
        Edge* edge = user->friendsHead;
        while(edge != nullptr){
            bool alreadyVisited = false;
            for(int i = 0; i < visitedCount; i++){
                if(visited[i] == edge->friendUserName){
                    alreadyVisited = true;
                    break;
                }
            }
            if(!alreadyVisited){
                visited[visitedCount++] = edge->friendUserName;
                queue[rear++] = edge->friendUserName;
            }
            edge = edge->next;
        }
    }
    cout<<endl;
}

string dfsVisited[200];
int dfsVisitedCount = 0;

void DFSHelper(string userName){
    dfsVisited[dfsVisitedCount++] = userName;
    cout<<userName<<" ";
    User* user = searchUser(userName);
    if(user == nullptr) { return; }
    Edge* edge = user->friendsHead;
    while(edge != nullptr){
        bool found = false;
        for(int i = 0; i < dfsVisitedCount; i++){
            if(dfsVisited[i] == edge->friendUserName){
                found = true;
                break;
            }
        }
        if(!found) { DFSHelper(edge->friendUserName); }
        edge = edge->next;
    }
}

void DFS(string startUser){
    if(searchUser(startUser) == nullptr){
        cout<<"User not found"<<endl;
        return;
    }
    dfsVisitedCount = 0;
    cout<<"DFS from "<<startUser<<": ";
    DFSHelper(startUser);
    cout<<endl;
}

// ==========================================
// MODULE G - MESSAGING
// ==========================================

void sendMessage(string toUser, string text){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    bool found = false;
    User* touser = searchUser(toUser);
    if(touser == nullptr){
        cout<<"Error: User does not exist."<<endl;
        return;
    }
    Conversation* foundConversion = nullptr;
    Conversation* temp = currentUser->conversationsHead;
    while(temp != nullptr){
        if(temp->withUser == toUser){
            found = true;
            foundConversion = temp;
            break;
        }
        temp = temp->next;
    }
    if(!found && foundConversion == nullptr){
        Conversation* newConversation = new Conversation;
        newConversation->withUser = toUser;
        newConversation->messageStackTop = nullptr;
        newConversation->next = currentUser->conversationsHead;
        currentUser->conversationsHead = newConversation;
        foundConversion = newConversation;
    }
    Message* newMessage = new Message;
    newMessage->fromUser = currentUser->userName;
    newMessage->toUser = toUser;
    newMessage->text = text;
    newMessage->next = foundConversion->messageStackTop;
    foundConversion->messageStackTop = newMessage;

    foundConversion = nullptr;
    temp = touser->conversationsHead;
    found = false;
    while(temp != nullptr){
        if(temp->withUser == currentUser->userName){
            found = true;
            foundConversion = temp;
            break;
        }
        temp = temp->next;
    }
    if(!found && foundConversion == nullptr){
        Conversation* receiverConv = new Conversation;
        receiverConv->withUser = currentUser->userName;
        receiverConv->messageStackTop = nullptr;
        receiverConv->next = touser->conversationsHead;
        touser->conversationsHead = receiverConv;
        foundConversion = receiverConv;
    }
    Message* receiverMessage = new Message;
    receiverMessage->fromUser = currentUser->userName;
    receiverMessage->toUser = touser->userName;
    receiverMessage->text = text;
    receiverMessage->next = foundConversion->messageStackTop;
    foundConversion->messageStackTop = receiverMessage;

    addNotification(toUser, currentUser->userName + " sent you a message!");
    cout<<"Message sent successfully to "<<toUser<<endl;
}

void latestMessage(string withUser){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* touser = searchUser(withUser);
    if(touser == nullptr){
        cout<<"Error: User does not exist."<<endl;
        return;
    }
    Conversation* temp = currentUser->conversationsHead;
    Conversation* targetConv = nullptr;
    while(temp != nullptr){
        if(temp->withUser == withUser){
            targetConv = temp;
            break;
        }
        temp = temp->next;
    }
    if(targetConv == nullptr){
        cout<<"No conversation found."<<endl;
        return;
    }
    if(targetConv->messageStackTop == nullptr){
        cout<<"No messages in this conversation yet."<<endl;
        return;
    }
    cout<<"From: "<<targetConv->messageStackTop->fromUser<<" - "<<targetConv->messageStackTop->text<<endl;
}

void deleteLatestMessage(string withUser){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* touser = searchUser(withUser);
    if(touser == nullptr){
        cout<<"Error: User does not exist."<<endl;
        return;
    }
    Conversation* temp = currentUser->conversationsHead;
    Conversation* targetConv = nullptr;
    while(temp != nullptr){
        if(temp->withUser == withUser){
            targetConv = temp;
            break;
        }
        temp = temp->next;
    }
    if(targetConv == nullptr){
        cout<<"No conversation found."<<endl;
        return;
    }
    if(targetConv->messageStackTop == nullptr){
        cout<<"No messages in this conversation yet."<<endl;
        return;
    }
    Message* toDelete = targetConv->messageStackTop;
    targetConv->messageStackTop = targetConv->messageStackTop->next;
    delete toDelete;
    cout<<"The latest message has been deleted."<<endl;
}

void viewConversation(string withUser){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    User* targetUser = searchUser(withUser);
    if(targetUser == nullptr){
        cout<<"No such user exists"<<endl;
        return;
    }
    Conversation* temp = currentUser->conversationsHead;
    while(temp != nullptr){
        if(temp->withUser == targetUser->userName) { break; }
        temp = temp->next;
    }
    if(temp == nullptr){
        cout<<"No such chat with user found"<<endl;
        return;
    }
    Message* messages = temp->messageStackTop;
    if(messages == nullptr){
        cout<<"No messages in this conversation."<<endl;
        return;
    }
    cout<<"=== Chat History with "<<withUser<<" ==="<<endl;
    while(messages != nullptr){
        cout<<"- Sent by: "<<messages->fromUser<<endl;
        cout<<"- Sent to: "<<messages->toUser<<endl;
        cout<<"- Text: "<<messages->text<<endl;
        messages = messages->next;
    }
}

// ==========================================
// MODULE E - NOTIFICATIONS
// ==========================================

void addNotification(string userName, string message){
    User* targetUser = searchUser(userName);
    if(targetUser == nullptr){
        cout<<"The user does not exist"<<endl;
        return;
    }
    Notification* newNotification = new Notification;
    newNotification->message = message;
    newNotification->next = nullptr;
    if(targetUser->notificationsFront == nullptr){
        targetUser->notificationsFront = newNotification;
        targetUser->notificationsRear = newNotification;
    }
    else{
        targetUser->notificationsRear->next = newNotification;
        targetUser->notificationsRear = newNotification;
    }
}

void viewNotification(){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    Notification* temp = currentUser->notificationsFront;
    if(temp == nullptr){
        cout<<"You have no notifications"<<endl;
        return;
    }
    while(temp != nullptr){
        cout<<"- "<<temp->message<<endl;
        temp = temp->next;
    }
}

void peekNotification(){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    if(currentUser->notificationsFront == nullptr){
        cout<<"You have no new notifications."<<endl;
        return;
    }
    cout<<"Next Notification: "<<currentUser->notificationsFront->message<<endl;
}

void processNotification(){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    if(currentUser->notificationsFront == nullptr){
        cout<<"You have no notifications to process"<<endl;
        return;
    }
    Notification* toDelete = currentUser->notificationsFront;
    cout<<"Processing Notification: "<<toDelete->message<<endl;
    currentUser->notificationsFront = currentUser->notificationsFront->next;
    if(currentUser->notificationsFront == nullptr) { currentUser->notificationsRear = nullptr; }
    delete toDelete;
    cout<<"Notification removed from queue."<<endl;
}

// ==========================================
// MODULE C - FEED
// ==========================================

void viewFeed(){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    if(globalFeedHead == nullptr){
        cout<<"The feed is currently empty!"<<endl;
        return;
    }
    Post* currentPost = globalFeedHead;
    while(true){
        int choice;
        cout<<"- Owner: "<<currentPost->owner<<endl;
        cout<<"- Content: "<<currentPost->content<<endl;
        cout<<"- Likes: "<<currentPost->likes<<endl;
        label:
        cout<<"----------- FEED ACTIONS -----------"<<endl;
        cout<<"[1] Next, [2] Previous, [3] Like, [4] Quit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice < 1 || choice > 4){
            cout<<"Wrong choice"<<endl;
            goto label;
        }
        switch(choice){
            case 1:
                if(currentPost->next != nullptr) { currentPost = currentPost->next; }
                else { cout<<"You have reached the bottom"<<endl; }
                break;
            case 2:
                if(currentPost->prev != nullptr) { currentPost = currentPost->prev; }
                else { cout<<"You are at the top"<<endl; }
                break;
            case 3:
                currentPost->likes++;
                postAVLRoot = avlInsert(postAVLRoot, currentPost->postID, currentPost->likes);
                addNotification(currentPost->owner, currentUser->userName + " liked your post!");
                cout<<"Post liked!"<<endl;
                break;
            case 4:
                return;
        }
    }
}

// ==========================================
// MODULE D - STORIES
// ==========================================

void addStory(string content){
    if(currentUser == nullptr){
        cout<<"The user is not logged in."<<endl;
        return;
    }
    Story* newStory = new Story;
    newStory->userName = currentUser->userName;
    newStory->storyContent = content;
    if(storiesHead == nullptr){
        storiesHead = newStory;
        newStory->next = storiesHead;
    }
    else{
        Story* temp = storiesHead;
        while(temp->next != storiesHead) { temp = temp->next; }
        temp->next = newStory;
        newStory->next = storiesHead;
    }
}

void viewStory(){
    if(currentUser == nullptr){
        cout<<"The user is not logged in"<<endl;
        return;
    }
    if(storiesHead == nullptr){
        cout<<"There are no stories"<<endl;
        return;
    }
    Story* temp = storiesHead;
    while(true){
        int choice;
        cout<<"------- Story ----------"<<endl;
        cout<<"- User Name: "<<temp->userName<<endl;
        cout<<"- Story Content: "<<temp->storyContent<<endl;
        label2:
        cout<<"----------- STORY ACTIONS -----------"<<endl;
        cout<<"[1] Next, [2] Quit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice < 1 || choice > 2){
            cout<<"Wrong choice"<<endl;
            goto label2;
        }
        switch(choice){
            case 1:
                temp = temp->next;
                break;
            case 2:
                return;
        }
    }
}
