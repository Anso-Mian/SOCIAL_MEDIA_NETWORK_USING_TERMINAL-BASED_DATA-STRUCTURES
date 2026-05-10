# 📱 Social Media Network - Terminal-Based Application

> A comprehensive terminal-based social media platform built from scratch using advanced data structures and algorithms in C++.

![Status](https://img.shields.io/badge/Status-Complete-brightgreen) ![Language](https://img.shields.io/badge/Language-C%2B%2B-blue) ![License](https://img.shields.io/badge/License-MIT-orange)

---

## 📑 Table of Contents

- [Overview](#overview)
- [Program Architecture](#program-architecture)
- [Core Data Structures](#core-data-structures)
- [Main Modules](#main-modules)
- [Key Features](#key-features)
- [What We Learned](#what-we-learned)
- [Getting Started](#getting-started)
- [How to Run](#how-to-run)
- [Project Team](#project-team)

---

## 🎯 Overview

This project implements a fully functional social media platform with a **terminal-based user interface** (TUI). Unlike traditional GUI-based applications, this platform demonstrates the power and efficiency of core data structures and algorithms, making it an educational masterpiece for understanding how real-world systems work underneath the hood.

**Key Highlights:**
- ✅ Complete user authentication system
- ✅ Social networking with friendship management
- ✅ Post creation and feed system
- ✅ Real-time notifications (queue-based)
- ✅ Direct messaging system
- ✅ User analytics and rankings
- ✅ Story features (like Instagram/WhatsApp)

---

## 🏗️ Program Architecture

```
┌─────────────────────────────────────────┐
│        MAIN MENU (User Interface)       │
├─────────────────────────────────────────┤
│  1. User Management    4. Stories       │
│  2. Social Network     5. Notifications │
│  3. Posts & Feed       6. Analytics     │
│  7. Messaging System                    │
└─────────────────────────────────────────┘
         ↓ Routes to ↓
┌─────────────────────────────────────────┐
│      Core Modules & Data Structures     │
├─────────────────────────────────────────┤
│  Module A: Hash Table (User Storage)    │
│  Module B: Graph (Friendships)          │
│  Module C: Doubly Linked List (Posts)   │
│  Module D: Singly Linked List (Stories) │
│  Module E: Queue (Notifications)        │
│  Module F: AVL Trees (Analytics)        │
│  Module G: Stack (Messaging)            │
└─────────────────────────────────────────┘
```

---

## 💾 Core Data Structures

### 🔹 Module A: Hash Table (User Management)
- **Purpose:** O(1) average-case user lookup and registration
- **Size:** 101 buckets with collision handling via chaining
- **Operations:** Register, Login, Delete, Search
- **Time Complexity:** Insert O(1), Search O(1), Delete O(1)

```cpp
User* hashTable[TABLE_SIZE]; // Stores all registered users
```

### 🔹 Module B: Graph (Social Network)
- **Structure:** Adjacency list representation
- **Purpose:** Maintain friendship relationships
- **Traversals:** BFS (Breadth-First Search), DFS (Depth-First Search)
- **Use Cases:** Find friends, mutual connections, network analysis

```cpp
Edge* friendsHead; // Linked list of friends for each user
```

### 🔹 Module C: Doubly Linked List (Posts & Feed)
- **Global Feed:** Maintains all posts in chronological order
- **User Posts:** Each user has their own post list
- **Bidirectional Navigation:** Prev/Next pointers for easier manipulation
- **Operations:** Create, Delete, Display

### 🔹 Module D: Singly Linked List (Stories)
- **Purpose:** Temporary story storage (like Instagram stories)
- **FIFO Access:** Stories displayed in order of creation
- **Structure:** Simple link-based storage

### 🔹 Module E: Queue (Notifications)
- **Implementation:** Circular queue with front and rear pointers
- **Purpose:** Queue-based notification system
- **Operations:** Enqueue (add notification), Dequeue (process), Peek
- **Behavior:** FIFO - First In, First Out

### 🔹 Module F: AVL Tree (Analytics & Ranking)
- **Self-Balancing BST** ensuring O(log n) operations
- **Two Trees:** One for user rankings, one for post popularity
- **Functions:**
  - Left/Right rotations for balancing
  - InOrder traversal for sorted display
  - Range queries for analytics
  - Top-K queries for trending content

### 🔹 Module G: Stack (Messaging)
- **Implementation:** Stack-based message storage
- **LIFO Access:** Latest message is most accessible
- **Operations:** Push (send), Pop (delete latest), Peek (view latest)

---

## 🔧 Main Functions Overview

### 👤 User Management Functions
| Function | Purpose | Complexity |
|----------|---------|-----------|
| `registerUser()` | Register new user with validation | O(1) |
| `loginUser()` | Authenticate user | O(1) |
| `deleteUser()` | Remove user and cleanup references | O(n) |
| `searchUser()` | Find user by username | O(1) |
| `displayAllUsers()` | List all registered users | O(n) |

### 🤝 Social Network Functions
| Function | Purpose | Complexity |
|----------|---------|-----------|
| `addfriend()` | Create bidirectional friendship | O(1) |
| `removeFriend()` | Remove friendship connection | O(m) |
| `displayFriends()` | Show friend list of a user | O(m) |
| `BFS()` | Breadth-first network traversal | O(V+E) |
| `DFS()` | Depth-first network traversal | O(V+E) |

### 📝 Post Management Functions
| Function | Purpose | Complexity |
|----------|---------|-----------|
| `createPost()` | Create new post | O(log n) |
| `deletePost()` | Remove post from system | O(log n) |
| `displayPost()` | Show user's posts | O(k) |
| `likePost()` | Increment post likes | O(log n) |
| `viewFeed()` | Display all posts chronologically | O(n) |

### 📢 Notification Functions
| Function | Purpose | Complexity |
|----------|---------|-----------|
| `addNotification()` | Queue new notification | O(1) |
| `viewNotification()` | Display all notifications | O(k) |
| `peekNotification()` | Preview next notification | O(1) |
| `processNotification()` | Remove and process notification | O(1) |

### 💬 Messaging Functions
| Function | Purpose | Complexity |
|----------|---------|-----------|
| `sendMessage()` | Send message to user | O(1) |
| `latestMessage()` | Peek at latest message | O(1) |
| `deleteLatestMessage()` | Remove latest message | O(1) |
| `viewConversation()` | Display chat history | O(k) |

### 📊 Analytics Functions
| Function | Purpose | Complexity |
|----------|---------|-----------|
| `getTopK()` | Get top K active users/posts | O(n log n) |
| `inorderTraversal()` | Show sorted rankings | O(n) |
| `rangeQuery()` | Query data within range | O(n) |

---

## 🎓 What We Learned

### 📚 Core Computer Science Concepts

#### 1. **Data Structure Design & Selection**
- When to use Hash Tables vs Trees vs Lists
- Trade-offs between time and space complexity
- Real-world applications of abstract data structures

#### 2. **Hash Functions & Collision Resolution**
- Designing efficient hash functions
- Handling collisions through chaining
- Load factor and performance optimization

#### 3. **Graph Theory & Traversal Algorithms**
- **BFS:** Level-order network exploration
- **DFS:** Deep exploration with recursion
- Social network analysis using graph algorithms
- Time complexity: O(V + E) for both traversals

#### 4. **Tree Structures & Balancing**
- AVL Tree self-balancing properties
- Left and Right rotations for maintaining balance
- Binary Search Tree operations
- Self-balancing ensures O(log n) for all operations
- Real-world use in databases and file systems

#### 5. **Queue & Stack Data Structures**
- FIFO vs LIFO paradigms
- Queue applications in notifications
- Stack applications in messaging
- Practical differences in system design

#### 6. **Doubly Linked Lists**
- Bidirectional navigation advantages
- Memory overhead vs. functionality trade-off
- Insert/Delete operations in O(1) with pointer reference

#### 7. **Memory Management in C++**
- Dynamic memory allocation with `new/delete`
- Avoiding memory leaks in complex structures
- Proper cleanup when deleting users and posts
- Pointer manipulation and dereferencing

#### 8. **System Design Principles**
- **Modular code organization**
- **Separation of concerns**
- **Menu-driven architecture**
- **Error handling and validation**

#### 9. **Algorithm Optimization**
- Selection sort for Top-K rankings
- Range queries on BSTs
- Efficient friend searching and removal

#### 10. **Software Engineering Practices**
- Efficient code structure
- Clear variable naming conventions
- Modular function design
- Code reusability

---

## 🚀 Getting Started

### Prerequisites
- **C++ Compiler:** g++ (GCC 7.0 or higher)
- **Git:** Version control system
- **Linux/Unix Terminal:** For running the application

### Required Packages
```bash
sudo apt-get install g++ git
```

---

## 📥 Installation & Setup

### Step 1: Clone the Repository
```bash
git clone https://github.com/Anso-Mian/SOCIAL_MEDIA_NETWORK_USING_TERMINAL-BASED_DATA-STRUCTURES.git
cd SOCIAL_MEDIA_NETWORK_USING_TERMINAL-BASED_DATA-STRUCTURES
```

### Step 2: Navigate to Project Directory
```bash
cd "Data Structures/MYCODED PROJECT"
# OR if you're already in the right location
ls -la
```

### Step 3: Compile the Program
```bash
# Compile all source files
g++ -o main main.cpp implementation.cpp structure.h

# OR use the provided compiled binary (if available)
g++ -std=c++17 -o main main.cpp implementation.cpp
```

### Step 4: Run the Application
```bash
./main
```

---

## 🎮 How to Use

### Navigation Guide

Once you run the program, you'll see the main menu:

```
================ MAIN MENU =================
1. User Management
2. Social Network
3. Posts & Feed
4. Stories
5. Notifications
6. Analytics & Ranking
7. Messaging System
8. Exit
============================================
```

### Quick Start Example

1. **Register a User:**
   - Select Option 1 → Option 1
   - Enter Username, Password, Email, Bio

2. **Login:**
   - Select Option 1 → Option 2
   - Enter Credentials

3. **Add Friends:**
   - Select Option 2 → Option 1
   - Enter two usernames

4. **Create Posts:**
   - Select Option 3 → Option 1
   - Enter post content

5. **View Feed:**
   - Select Option 3 → Option 4
   - Interact with posts

---

## 📊 File Structure

```
MYCODED PROJECT/
├── main.cpp                 # Main menu and user interface
├── implementation.cpp       # All module implementations
├── structure.h             # Data structure definitions
├── README.md              # This file
└── output/
    ├── main               # Compiled executable
    └── structure          # Compiled object file
```

---

## 🤝 Project Team

This project was developed by a dedicated team of passionate data structure enthusiasts:

| Team Member | Role | Contributions |
|-------------|------|---------------|
| **Anso Mian** 👨‍💻 | Lead Developer & Architect | System design, Hash Tables, Graph algorithms, AVL Trees |
| **Rizwan** 👨‍💻 | Developer | Post system, Feed management, Linked Lists implementation |
| **Shaheer Hayat** 👨‍💻 | Developer | Messaging system, Notifications, Queue implementation |

---

## 🎯 Features Showcase

### ✨ Highlights

- 🔐 **Secure Authentication:** Hash table-based user management with password validation
- 🌐 **Social Networking:** BFS/DFS traversal for friend network analysis
- 📰 **Dynamic Feed:** Doubly-linked list for chronological post ordering
- 🔔 **Real-time Notifications:** Queue-based notification system
- 💬 **Direct Messaging:** Stack-based message storage and retrieval
- 📊 **Advanced Analytics:** AVL tree-powered rankings and trending content
- 📱 **Story System:** Temporary content sharing like modern social platforms
- 🎯 **Range Queries:** Query users and posts within specific metrics

---

## 💡 Learning Outcomes

By studying and understanding this project, you will gain:

✅ Comprehensive understanding of 7 different data structures  
✅ Knowledge of graph algorithms (BFS, DFS)  
✅ Tree balancing and self-optimization concepts  
✅ Hash table design and collision handling  
✅ Queue and Stack applications in real systems  
✅ Time and Space complexity analysis  
✅ C++ memory management best practices  
✅ System design and modular programming  

---

## 📈 Complexity Analysis

| Operation | Data Structure | Time | Space |
|-----------|----------------|------|-------|
| User Lookup | Hash Table | O(1) | O(n) |
| Friend Distance | Graph BFS/DFS | O(V+E) | O(V) |
| Post Creation | Linked List + AVL | O(log n) | O(1) |
| Notification | Queue | O(1) | O(k) |
| Message | Stack | O(1) | O(m) |
| Top K Ranking | AVL Tree | O(n log n) | O(n) |

---

## 🔗 Useful Resources

- [C++ Reference](https://en.cppreference.com/)
- [GeeksforGeeks Data Structures](https://www.geeksforgeeks.org/data-structures/)
- [Competitive Programming Handbook](https://cses.fi/book/book.pdf)
- [Graph Algorithms Tutorial](https://www.coursera.org/learn/algorithms-on-graphs)

---

## 📝 License

This project is open source and available under the MIT License.

---

## 🙏 Acknowledgments

Special thanks to our computer science instructors for guidance in data structure implementation and system design principles.

---

## 📧 Contact & Support

For questions, improvements, or discussions about this project, feel free to reach out to any team member or create an issue on GitHub.

**GitHub Repository:** [SOCIAL_MEDIA_NETWORK_USING_TERMINAL-BASED_DATA-STRUCTURES](https://github.com/Anso-Mian/SOCIAL_MEDIA_NETWORK_USING_TERMINAL-BASED_DATA-STRUCTURES)

---

<div align="center">
  
### ⭐ If you found this project helpful, please consider giving it a star! ⭐

**Built with ❤️ by the Data Structures Team**

</div>
