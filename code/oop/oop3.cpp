#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::string;
using std::list;

class YouTubeChannel {
    private:
        string name, ownerName;
        int subscribersCount;
        list<string> publishedVideoTitles;

    public:
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

            for (string videoTitle: publishedVideoTitles) {
                cout << videoTitle << endl;
            }

            cout << "--------------------------------" << endl;
        }

        string getName() {
            return name;
        }

        void setName(string channelName) {
            name = channelName;
        }

        string getOwnerName() {
            return ownerName;
        }

        void setOwnerName(string channelOwnerName) {
            ownerName = channelOwnerName;
        }

        void subscribe() {
            subscribersCount++;
        }

        void unsubscribe() {
            if (subscribersCount > 0)
                subscribersCount--;
        }

        void publishVideo(string videoTitle) {
            publishedVideoTitles.push_back(videoTitle);
        }
};

int main () {
    YouTubeChannel ytChannel("TheBasics", "Suyash");
    ytChannel.subscribe();
    ytChannel.subscribe();
    ytChannel.subscribe();
    ytChannel.subscribe();
    ytChannel.unsubscribe();
    ytChannel.setName("ShutUp");
    ytChannel.getInfo();
    return 0;
}