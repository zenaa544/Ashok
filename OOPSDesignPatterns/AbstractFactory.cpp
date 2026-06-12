#include <iostream>
#include <string>



using namespace std;



//Abstract products ------------------------

class Button
{
public:
    virtual void drawButton() = 0;

    virtual ~Button() {}
};

class CheckBox
{
public:
    virtual void drawCheckBox() = 0;

    virtual ~CheckBox() {}
};

//Concrete Prodcuts Windows-------------------
class WindowsButton : public Button
{
public:
    void drawButton() override
    {
        cout << "Windows Button" << endl;
    }
};

class WindowsCheckBox : public CheckBox
{
public:
    void drawCheckBox() override
    {
        cout << "Windows CheckBox" << endl;
    }
};


//Concrete Products Linux--------------------
class LinuxButton : public Button
{
public:
    void drawButton() override
    {
        cout << "Linux Button" << endl;
    }
};

class LinuxCheckBox : public CheckBox
{
public:
    void drawCheckBox() override
    {
        cout << "Linux CheckBox" << endl;
    }
};

// Abstract Factory ---------------------------

class GUIFactory
{
public:

    virtual Button* createButton() = 0;

    virtual CheckBox* createCheckBox() = 0;

    virtual ~GUIFactory() {}
};


//Concrete Factories------------------------------

class WindowsFactory : public GUIFactory
{
public:

    Button* createButton() override
    {
        return new WindowsButton();
    }

    CheckBox* createCheckBox() override
    {
        return new WindowsCheckBox();
    }
};

class LinuxFactory : public GUIFactory
{
public:

    Button* createButton() override
    {
        return new LinuxButton();
    }

    CheckBox* createCheckBox() override
    {
        return new LinuxCheckBox();
    }
};

//Factory Selector--------------------------------------------

class AbstractGUIFactory
{
public:

    static GUIFactory* getFactory(string osType)
    {
        if(osType == "windows")
        {
            return new WindowsFactory();
        }
        else if(osType == "linux")
        {
            return new LinuxFactory();
        }

        return nullptr;
    }
};

// Client Code----

int main()
{
    string osType;

    cout << "Enter OS Type: ";
    cin >> osType;

    GUIFactory* factory =
        AbstractGUIFactory::getFactory(osType);

    if(factory == nullptr)
    {
        cout << "Invalid OS" << endl;
        return 0;
    }

    Button* button =
        factory->createButton();

    CheckBox* checkBox =
        factory->createCheckBox();

    button->drawButton();

    checkBox->drawCheckBox();

    delete button;
    delete checkBox;
    delete factory;

    return 0;
}
