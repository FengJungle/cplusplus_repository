#include <iostream>
#include <set>
using namespace std;

#include "Folder.h"

class Message
{
public:
    // 默认构造函数：显示的
    explicit Message(const string& str = ""):content(str)
    {
        cout<<"Message Default Constructor"<<endl;
    }

    // 拷贝构造函数
    Message(const Message& message);
    // 拷贝赋值运算符
    Message& operator=(const Message& message);
    // 析构函数
    ~Message();

    // 将message添加到指定Folder集合中
    void save(Folder&);
    // 从指定Folder集合中删除message
    void remove(Folder&);

private:
    friend class Folder;
    
    // 保存消息文本
    string content;
    // 包含此message的Folder集合
    std::set<Folder*>folders;

    // 将此message添加到指定Folder中
    void add_to_Folders(const Message&);
    // 从Folder集合中的每个folder中删除此message
    void remove_from_Folders();
};

// 拷贝构造函数
Message::Message(const Message &message) : content(message.content), folders(message.folders)
{
    cout<<"Message::Copy Constructor"<<endl;
    add_to_Folders(message);
}

// 拷贝赋值运算符
Message& Message::operator=(const Message& message)
{
    // messageA(this) = messageB

    // 从Folder集合中的每个folder中删除此message
    remove_from_Folders();
    this->content= message.content;
    this->folders = message.folders;
    add_to_Folders(message);
    return *this;
}

// 析构函数
Message::~Message()
{
    remove_from_Folders();
}

void Message::add_to_Folders(const Message& message)
{
    for(auto folder:message.folders)
    {
        folder->addMsg(this);
    }
}

void Message::remove_from_Folders()
{
    for(auto folder:this->folders)
    {
        folder->remMsg(this);
    }
}

void Message::save(Folder& folder)
{
    // 将指定folder添加到包含此message的文件夹列表中
    this->folders.insert(&folder);
    // 将此message添加到folder的message集合中
    folder.addMsg(this);
}

void Message::remove(Folder& folder)
{
    // 从包含此message的文件夹列表中移除指定folder
    this->folders.erase(&folder);
    // 从folder的message集合中将此message移除
    folder.remMsg(this);
}