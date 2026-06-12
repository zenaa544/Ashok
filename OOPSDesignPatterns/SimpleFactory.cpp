#include <iostream>
#include <string>

using namespace std;

class Notification
{
public:
    virtual void send() = 0;

    virtual ~Notification() {}
};

class EmailNotification : public Notification
{
public:
    void send() override
    {
        cout << "Sending Email Notification" << endl;
    }
};

class SMSNotification : public Notification
{
public:
    void send() override
    {
        cout << "Sending SMS Notification" << endl;
    }
};

class SlackNotification : public Notification
{
public:
    void send() override
    {
        cout << "Sending Slack Notification" << endl;
    }
};

class NotificationFactory
{
public:

    static Notification* createNotification(string type)
    {
        if(type == "email")
        {
            return new EmailNotification();
        }
        else if(type == "sms")
        {
            return new SMSNotification();
        }
        else if(type == "slack")
        {
            return new SlackNotification();
        }

        return nullptr;
    }
};

int main()
{
    string type;

    cout << "Enter notification type: ";
    cin >> type;

    Notification* notification =
        NotificationFactory::createNotification(type);

    if(notification != nullptr)
    {
        notification->send();
        delete notification;
    }

    return 0;
}
