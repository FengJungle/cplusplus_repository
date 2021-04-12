#ifndef _FOLDER_H_
#define _FOLDER_H_

#include <iostream>
#include <set>
using namespace std;

class Message;

class Folder
{
public:
    Folder()
    {
    }
    ~Folder()
    {
    }
    void addMsg(Message *message)
    {
        messages.insert(message);
    }
    void remMsg(Message *message)
    {
        messages.erase(message);
    }

private:
    std::set<Message*> messages;
};

#endif