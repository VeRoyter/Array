#include "Header1.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

class User;

class Chat {
public:
    virtual void AddUser(User* user) = 0;
    virtual bool IsUserInChat(const string& username) const = 0;
    virtual void SendMessage(User* sender, const string& message) = 0;
    virtual void SendMessage(User* sender, int stickerNumber) = 0;
};

class User {
private:
    string NicName;

public:
    User(string nic) : NicName(nic) {}

    string getNicName() const {
        return NicName;
    }

    void SendMessage(Chat* chat, const string& message) {
        if (chat->IsUserInChat(getNicName())) {
            chat->SendMessage(this, message);
        }
        else {
            cout << "You are not in the chat. Cannot send message." << endl;
        }
    }

    void SendMessage(Chat* chat, int stickerNumber) {
        if (chat->IsUserInChat(getNicName())) {
            chat->SendMessage(this, stickerNumber);
        }
        else {
            cout << "You are not in the chat. Cannot send sticker." << endl;
        }
    }

    void AddUserToChat(Chat* chat, User* user) {
        chat->AddUser(user);
    }
};

class GroupChat : public Chat {
private:
    string owner;
    Container<User*> participants;

public:
    GroupChat(string owner) : owner(owner) {}

    void AddUser(User* user) {
        participants.push_back(user);
        cout << "User " << user->getNicName() << " added to the group chat by " << owner << endl;
    }

    bool IsUserInChat(const string& username) const {
        return find_if(participants.begin(), participants.end(),
            [username](User* user) { return user->getNicName() == username; }) != participants.end();
    }

    void SendMessage(User* sender, const string& message) {
        cout << "User " << sender->getNicName() << " sent a message in the group chat: " << message << endl;
    }

    void SendMessage(User* sender, int stickerNumber) {
        cout << "User " << sender->getNicName() << " sent sticker #" << stickerNumber << " in the group chat." << endl;
    }
};

class Channel : public Chat {
private:
    string owner;
    vector<User*> participants;

public:
    Channel(string owner) : owner(owner) {}

    size_t GetSubscriberCount() {
        return participants.size();
    }

    friend bool operator==(Channel& a, Channel& b);

    void AddUser(User* user) {
        participants.push_back(user);
        cout << "User " << user->getNicName() << " added to the channel by " << owner << endl;
    }

    bool IsUserInChat(const string& username) const {
        return find_if(participants.begin(), participants.end(),
            [username](User* user) { return user->getNicName() == username; }) != participants.end();
    }

    void SendMessage(User* sender, const string& message) {
        if (sender->getNicName() == owner) {
            cout << "User " << sender->getNicName() << " sent a message in the channel: " << message << endl;
        }
        else {
            cout << "Only the owner can send messages in the channel." << endl;
        }
    }

    void SendMessage(User* sender, int stickerNumber) {
        if (sender->getNicName() == owner) {
            cout << "User " << sender->getNicName() << " sent sticker #" << stickerNumber << " in the channel." << endl;
        }
        else {
            cout << "Only the owner can send stickers in the channel." << endl;
        }
    }
};

class PersonalChat : public Chat {
private:
    vector<User*> participants;

public:
    void AddUser(User* user) {
        if (participants.size() < 2) {
            participants.push_back(user);
            cout << "User " << user->getNicName() << " added to the personal chat." << endl;
        }
        else {
            cout << "Cannot add more participants to the personal chat. Maximum limit reached." << endl;
        }
    }

    bool IsUserInChat(const string& username) const {
        return find_if(participants.begin(), participants.end(),
            [username](User* user) { return user->getNicName() == username; }) != participants.end();
    }

    void SendMessage(User* sender, const string& message) {
        if (IsUserInChat(sender->getNicName())) {
            cout << "User " << sender->getNicName() << " sent a message in the personal chat: " << message << endl;
        }
        else {
            cout << "You are not in the personal chat. Cannot send message." << endl;
        }
    }

    void SendMessage(User* sender, int stickerNumber) {
        if (IsUserInChat(sender->getNicName())) {
            cout << "User " << sender->getNicName() << " sent sticker #" << stickerNumber << " in the personal chat." << endl;
        }
        else {
            cout << "You are not in the personal chat. Cannot send sticker." << endl;
        }
    }
};

bool operator==(Channel& a, Channel& b) {
    return a.participants.size() == b.participants.size();
}

int main() {
    User Karl("Karl");
    User alice("alice");
    Channel ch("Karl");
    Karl.AddUserToChat(&ch, &Karl);
    Karl.AddUserToChat(&ch, &alice);
    Channel channel1("Owner1");
    Channel channel2("Owner2");

    if (channel1 == channel2)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }

    return 0;
}
