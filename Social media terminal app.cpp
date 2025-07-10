 #include <iostream>
#include <string>
using namespace std;

// Abstract base class for Commenter
class Commenter {
public:
    virtual string getName() = 0;
};

// Activity Class
class Activity {
    int type;
    string value;

public:
    Activity(int t = 0, string v = "") : type(t), value(v) {}

    void display() const {
        cout << "Activity: ";
        switch (type) {
        case 1: cout << "feeling "; break;
        case 2: cout << "thinking about "; break;
        case 3: cout << "making "; break;
        case 4: cout << "celebrating "; break;
        default: cout << "unknown "; break;
        }
        cout << value << endl;
    }
};

// Comment Class
class Comment {
    string text;
    Commenter* by;

public:
    Comment(string t, Commenter* c) : text(t), by(c) {}

    void display() const {
        cout << by->getName() << " commented: " << text << endl;
    }
};

// Post Class
class Post {
    int id;
    string text;
    string date;
    int likeCount;
    Commenter* likedBy[10];
    int likeIndex;
    Comment* comments[10];
    int commentIndex;
    Activity* activity;

public:
    Post(int i, string t, string d, Activity* a = nullptr)
        : id(i), text(t), date(d), activity(a), likeIndex(0), commentIndex(0), likeCount(0) {}

    virtual void display() const {
        cout << "Post ID: " << id << "\nText: " << text << "\nDate: " << date << endl;
        if (activity) activity->display();
        cout << "Likes: " << likeCount << endl;
        for (int i = 0; i < commentIndex; i++)
            comments[i]->display();
    }

    virtual void addLike(Commenter* c) {
        if (likeIndex < 10) {
            likedBy[likeIndex++] = c;
            likeCount++;
        }
    }

    void addComment(Comment* c) {
        if (commentIndex < 10)
            comments[commentIndex++] = c;
    }

    int getId() const { return id; }

    void displayLikes() const {
        cout << "\n===== Likes for Post ID: " << id << " =====\n";
        for (int i = 0; i < likeIndex; i++)
            cout << "- " << likedBy[i]->getName() << endl;
    }
};

// Memory Class (inherits from Post)
class Memory : public Post {
    Post* original;

public:
    Memory(int id, string t, string d, Post* o)
        : Post(id, t, d), original(o) {}

    void display() const override {
        cout << "Memory Post:\n";
        original->display();
    }
};

// Page Class
class Page : public Commenter {
    int id;
    string title;
    Post* posts[10];
    int postIndex;

public:
    Page(int i, string t) : id(i), title(t), postIndex(0) {}

    void addPost(Post* p) {
        if (postIndex < 10)
            posts[postIndex++] = p;
    }

    void display() const {
        cout << "\nPage: " << title << " (ID: " << id << ")\nPosts:\n";
        for (int i = 0; i < postIndex; i++)
            posts[i]->display();
    }

    string getName() override {
        return title;
    }
};

// User Class
class User : public Commenter {
    int id;
    string name;
    User* friends[10];
    int friendIndex;
    Page* likedPages[10];
    int pageIndex;
    Post* timeline[10];
    int postIndex;

public:
    User(int i = 0, string n = "") : id(i), name(n), friendIndex(0), pageIndex(0), postIndex(0) {}

    void addFriend(User* u) {
        if (friendIndex < 10)
            friends[friendIndex++] = u;
    }

    void likePage(Page* p) {
        if (pageIndex < 10)
            likedPages[pageIndex++] = p;
    }

    void addPost(Post* p) {
        if (postIndex < 10)
            timeline[postIndex++] = p;
    }

    string getName() override {
        return name;
    }

    void viewTimeline() const {
        cout << "\n===== Timeline of " << name << " =====\n";
        for (int i = 0; i < postIndex; i++)
            timeline[i]->display();
    }

    void viewFriends() const {
        cout << "\n===== " << name << "'s Friends =====\n";
        for (int i = 0; i < friendIndex; i++)
            cout << "- " << friends[i]->name << endl;
    }

    void viewHome() const {
        cout << "\n===== Home for " << name << " =====\n";
        cout << "\n--- Posts from Friends ---\n";
        for (int i = 0; i < friendIndex; i++)
            friends[i]->viewTimeline();

        cout << "\n--- Posts from Liked Pages ---\n";
        for (int i = 0; i < pageIndex; i++)
            likedPages[i]->display();
    }
};

// Main Function
int main() {
    // Users
    User* u1 = new User(1, "Usman");
    User* u2 = new User(2, "Areeb");
    User* u3 = new User(3, "Haseeb");
    User* u4 = new User(4, "Ali");
    User* u5 = new User(5, "Zain");

    u1->addFriend(u2);
    u1->addFriend(u3);
    u1->addFriend(u4);
    u1->addFriend(u5);

    // Pages
    Page* p1 = new Page(101, "Geo News");
    Page* p2 = new Page(102, "Apna College");

    u1->likePage(p1);
    u1->likePage(p2);
    u4->likePage(p1);

    // Activities
    Activity* a1 = new Activity(1, "Happy");
    Activity* a2 = new Activity(2, "about Future");
    Activity* a3 = new Activity(4, "Birthday");

    // Posts
    Post* post1 = new Post(201, "My first post!", "25 Oct 2017", a1);
    Post* post2 = new Post(202, "News Update: New PM elected!", "26 Oct 2017");
    Post* post3 = new Post(203, "College Tips for Freshers", "27 Oct 2017", a2);
    Post* post4 = new Post(204, "Enjoying Birthday Party!", "28 Oct 2017", a3);

    u2->addPost(post1);
    p1->addPost(post2);
    p2->addPost(post3);
    u4->addPost(post4);

    // Likes
    post1->addLike(u1);
    post1->addLike(u3);
    post1->addLike(u4);

    post2->addLike(u1);
    post2->addLike(u5);

    post3->addLike(u1);
    post3->addLike(u3);

    post4->addLike(u1);
    post4->addLike(u2);
    post4->addLike(u3);
    post4->addLike(u5);

    // Comments
    post1->addComment(new Comment("Awesome!", u1));
    post1->addComment(new Comment("Well done!", u4));
    post2->addComment(new Comment("Great news!", u1));
    post2->addComment(new Comment("Hope it's good for the country.", u3));
    post3->addComment(new Comment("Thanks for the tips!", u5));
    post4->addComment(new Comment("Happy Birthday!", u1));
    post4->addComment(new Comment("Looks fun!", u2));
    post4->addComment(new Comment("Party hard!", u5));

    // Memory
    Memory* mem = new Memory(205, "Throwback to old post", "29 Oct 2018", post1);
    u1->addPost(mem);

    // Display
    u1->viewHome();
    cout << "\n\nViewing Likes of Post 202:\n";
    post2->displayLikes();

    cout << "\n\nViewing Post 202:\n";
    post2->display();

    cout << "\n\nViewing Usman's Timeline:\n";
    u1->viewTimeline();

    // Cleanup
    delete u1; delete u2; delete u3; delete u4; delete u5;
    delete p1; delete p2;
    delete a1; delete a2; delete a3;
    delete post1; delete post2; delete post3; delete post4; delete mem;

    return 0;
}
