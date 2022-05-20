#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::string;
using std::list;

class YouTubeChannel {
    // Defaulty all the members of a class are private. Meaning they can be accessed only inside the class.
    // To make them public, we use 'access modifers' like 'public'
    public: // This access modifier will make all the class members accessible outside of the class
        string name;
        string ownerName;
        int subscribersCount;
        list<string> publishedVideoTitles;
};

int main() {
    YouTubeChannel ytChannel;
    ytChannel.name = "TheBasics";
    ytChannel.ownerName = "Your Basic Guy";
    ytChannel.subscribersCount = 100121;
    ytChannel.publishedVideoTitles = {
        "How to drink water?",
        "Tutorial on how to open a door",
        "Blinking eyes made easy!",
        "The Basics Full Course Release!!"
    };

    cout << ytChannel.name << endl;
    cout << ytChannel.ownerName << endl;
    cout << ytChannel.subscribersCount << endl;
    cout << "Video released:" << endl;

    for (string videoTitle: ytChannel.publishedVideoTitles) {
        cout << videoTitle << endl;
    }

    YouTubeChannel ytChannelCopy = ytChannel;
    cout << endl << ytChannelCopy.name << endl;
    cout << ytChannelCopy.ownerName << endl;
}