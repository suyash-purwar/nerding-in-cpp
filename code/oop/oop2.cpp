#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::string;
using std::list;

class YouTubeChannel {
    private:
        string platform = "YouTube";
        

    public:
        // By default, class members are private. So, it is necessary to keep them under public access modifier
        string name, ownerName;
        int subscribersCount;
        list<string> publishedVideoTitle;

        // By default, constructors are private. So, it is necessary to keep them under public access modifier
        YouTubeChannel(string n, string on) {
            name = n;
            ownerName = on;
            subscribersCount = 0;
        }

        void getInfo() {
            cout << name << endl;
            cout << ownerName << endl;
            cout << subscribersCount << endl;
            cout << "Videos:" << endl;

            for (string videoTitle: publishedVideoTitle) {
                cout << videoTitle << endl;
            }
        }

        // Methods are by default public
        void drawLine(int count) {
            for (int i = 0; i < count; i++)
                cout << "-";
            cout << endl;
        }
};

int main() {
    YouTubeChannel ytChannel("TheBasics", "Suyash");
    ytChannel.publishedVideoTitle.push_back("How to open a door?");
    ytChannel.publishedVideoTitle.push_back("Blinking eyes made easy!");
    ytChannel.publishedVideoTitle.push_back("How to poop? 3 easy steps!");

    YouTubeChannel myChannel("CookWithMe", "Sangeeta");

    ytChannel.getInfo();
    ytChannel.drawLine(30);
    myChannel.getInfo();

    return 0;
}