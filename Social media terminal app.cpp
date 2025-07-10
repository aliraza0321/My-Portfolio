#include <iostream>
#include <string>
using namespace std;
//// Forward declarations because we want to use obj or ptr of classes  in their base classes 
//class Page;
//class Post;
//class Comment;
//class Activity;
//class Memory;
class Commenter //for comments
{  //this class will become abstract class therefore we can't create obj of this class 
public:
    virtual string getName() = 0;
};

// ------------------ Activity Class ------------------
class Activity
{
    int type;
    string value;
public:
    Activity(int t = 0, string v = "") : type(t), value(v)
    {
        //this class receive activity and store in posts or pages
    }

    void display() const// Displays the activity type with its value
    {
        if (type == 1)
        {
            cout << "Activity: " << "feeling" << " " << value << endl;
        }
        else if (type == 2)
        {
            cout << "Activity: " << "thinking about" << " " << value << endl;

        }
        else if (type == 3)
        {
            cout << "Activity: " << "making" << " " << value << endl;

        }
        else if (type == 4)
        {
            cout << "Activity: " << "celebraing" << " " << value << endl;

        }
        else
            cout << "Activity: " << "unknown" << " " << value << endl;

    }
};

// ------------------ Comment Class ------------------
class Comment
{
    string text;
    Commenter* by;
public:
    Comment(string t, Commenter* c) : text(t), by(c) {}

    void display() const  // Displays the comment along with the name of the commenter
    {   //get name is function that override in page class
        cout << by->getName() << " commented: " << text << endl;
    }
};

// ------------------ Post Class ------------------
class Post
{
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
        : id(i), text(t), date(d), activity(a), likeIndex(0), commentIndex(0), likeCount(0)
    {
    }

    virtual void display() const // Displays the post content activity like count and comments
    {
        cout << "Post ID: " << id << "\nText: " << text << "\nDate: " << date << endl;
        if (activity)
            activity->display();
        cout << "Likes: " << likeCount << endl;
        for (int i = 0; i < commentIndex; i++)
            comments[i]->display();
    }

    virtual void addLike(Commenter* c)// Adds a like to the post from a user or page

    {
        if (likeIndex < 10)
        {
            likedBy[likeIndex++] = c;
            likeCount++;
        }
    }

    void addComment(Comment* c)// Adds a comment to the post
    {
        if (commentIndex < 10)
            comments[commentIndex++] = c;
    }

    int getId() const
    {
        return id;
    }
    int getLikeCount() const// Displays all users/pages who liked the post
    {
        return likeCount;
    }

    void displayLikes() const
    {
        cout << "\n===================================\n";
        cout << "  Likes for Post ID: " << id << "\n";
        cout << "===================================\n\n";;
        for (int i = 0; i < likeIndex; i++)
            cout << "- " << likedBy[i]->getName() << endl << endl;
    }
};

// ------------------ Memory Class ------------------
class Memory : public Post
{
    Post* original;
public:
    Memory(int id, string t, string d, Post* o)
        : Post(id, t, d), original(o)
    {
    }

    void display() const override // Displays the original post (used as a memory)
    {
        cout << "Original post:\n";
        original->display();
    }
};

// ------------------ Page Class ------------------
class Page : public Commenter
{
    int id;
    string title;
    Post* posts[10];  //array of 10 obj pointer of post class
    int postIndex;
    int totalLikes;
public:
    Page(int i, string t) : id(i), title(t), postIndex(0), totalLikes(0) {}

    void addPost(Post* p)
    {
        if (postIndex < 10)
            posts[postIndex++] = p;
    }

    void display() const //Displays the page title and all posts made on the page
    {
        cout << "Page: " << title << " (ID: " << id << ")\nPosts:\n\n";
        for (int i = 0; i < postIndex; i++)
            posts[i]->display();
    }

    string getName()override // Returns the page title

    {
        return title;
    }
};

// ------------------ User Class ------------------
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
    User(int i = 0, string n = " ") : id(i), name(n), friendIndex(0), pageIndex(0), postIndex(0)
    {

    }

    void addFriend(User* u)
    {
        if (friendIndex < 10)
            friends[friendIndex++] = u;
    }

    void likePage(Page* p)
    {
        if (pageIndex < 10)
            likedPages[pageIndex++] = p;
    }

    void addPost(Post* p) // Adds a post to the page timeline
    {
        if (postIndex < 10)
            timeline[postIndex++] = p;
    }

    string getName()override// Displays the page title and all posts made on the page
    {
        return name;
    }

    void viewTimeline() const // Displays all posts on the user's timeline
    {
        cout << "\n===================================\n";
        cout << "         Timeline of " << name << "\n";
        cout << "===================================\n\n";
        for (int i = 0; i < postIndex; i++)
            timeline[i]->display();
    }

    void viewFriends() const // Displays the names of the user's friends
    {
        cout << "\n===================================\n";
        cout << "         " << name << "'s Friends\n";
        cout << "===================================\n\n";
        for (int i = 0; i < friendIndex; i++)
            cout << "- " << friends[i]->name << endl << endl;
    }

    void viewHome() const // Displays all posts from friends and liked pages
    {
        cout << "\n===================================\n";
        cout << "\nHome for " << name << endl;
        cout << "\n===================================\n";
        cout << "----------- Posts from Friends -----------\n";
        for (int i = 0; i < friendIndex; i++)
        {
            friends[i]->viewTimeline();
        }
        cout << "\n----------- Posts from Liked Pages -----------\n";
        for (int i = 0; i < pageIndex; i++)
        {
            likedPages[i]->display();
        }
    }
};

// ------------------ Main Program ------------------

int main() {
    // Users
    User* u1 = new User(1, "Usman");
    User* u2 = new User(2, "Areeb");
    User* u3 = new User(3, "Haseeb");
    User* u4 = new User(4, "Ali");
    User* u5 = new User(5, "Zain");

    // Friendships
    u1->addFriend(u2);
    u1->addFriend(u3);
    u1->addFriend(u4);
    u1->addFriend(u5);
    u2->addFriend(u1); 
    u3->addFriend(u1);

    // Pages
    Page* p1 = new Page(101, "Geo News");
    Page* p2 = new Page(102, "Apna College");

    u1->likePage(p1);
    u1->likePage(p2);
    u4->likePage(p1);  // More people liking page

    // Activities
    Activity* a1 = new Activity(1, "Happy");
    Activity* a2 = new Activity(2, "about Future");
    Activity* a3 = new Activity(4, "Birthday");

    // Posts
    Post* post1 = new Post(201, "My first post!", "25 Oct 2017", a1);
    Post* post2 = new Post(202, "News Update: New PM elected!", "26 Oct 2017", nullptr);
    Post* post3 = new Post(203, "College Tips for Freshers", "27 Oct 2017", a2);
    Post* post4 = new Post(204, "Enjoying Birthday Party!", "28 Oct 2017", a3);

    u2->addPost(post1);     // friend’s post
    p1->addPost(post2);     // page post
    p2->addPost(post3);     // another page
    u4->addPost(post4);     // another friend’s post

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

    // Memory post
    Memory* mem = new Memory(205, "Throwback to old post", "29 Oct 2018", post1);
    u1->addPost(mem);

    // Simulate functionality
    u1->viewHome();

    cout << "\n\nViewing Likes of Post 202:\n";
    post2->displayLikes();

    cout << "\n\nViewing Post 202:\n";
    post2->display();

    cout << "\n\nViewing Usman's Timeline:\n";
    u1->viewTimeline();
    delete u1;
    delete u2;
    delete u3;
    delete u4;
    delete u5;
    delete p1;
    delete p2;
    delete a1;
    delete a2;
    delete post1;
    delete post2;
    delete post3;
    delete post4;
    delete mem;
    u1 = nullptr;
    u2 = nullptr;
    u3 = nullptr;
    u4 = 0;
    u5 = 0;
    p1 = 0;
    p2 = 0;
    a1 = 0;
    a2 = 0;
    post1 = 0;
    post2 = 0;
    post3 = 0;
    post4 = 0;
    mem = 0;



}