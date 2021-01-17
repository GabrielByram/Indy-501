// this is a test - gabriel
// test again
// tis another test - Oliver

#include<SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<vector>
#include<conio.h>

using namespace sf;
using namespace std;

class Chat {
    IpAddress ip = IpAddress("67.165.127.62");
    TcpSocket socket;
    bool done = false;
    string id;
    string status = "connected";
    string text = "";
    Packet packet;
    RenderWindow window;
    vector<Text> chat;
    Font font;
public:
    Chat() {

    }
    void clearChat() {
        while (!chat.empty()) {
            chat.pop_back();
        }
    }
    void run() {
        //cout << ip << endl;
        cout << "Enter online id: ";
        cin >> id;
        socket.connect(ip, 55555);
        packet << id << status;
        socket.send(packet);
        socket.setBlocking(false);
        window.create(VideoMode(800, 600, 32), id);
        font.loadFromFile("Arial.ttf");
        window.clear();
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Escape)
                    {
                        text.clear();
                    } else if (event.key.code == Keyboard::Return)
                    {
                        Packet packet;
                        packet << id + ":" + text;
                        socket.send(packet);
                        Text displaytext(text, font, 20);
                        displaytext.setFillColor(Color::Green);
                        chat.push_back(displaytext);
                        text = "";
                    }
                    break;
                case Event::TextEntered:
                    if (event.text.unicode == '\b' && text.size() > 0)
                    {
                        text.erase(text.size() - 1, 1);
                    } else
                        text += event.text.unicode;
                    break;
                }
            }

            Packet packet;
            socket.receive(packet);
            string temptext;
            if (packet >> temptext)
            {
                Text displaytext(temptext, font, 20);
                displaytext.setFillColor(Color::White);
                chat.push_back(displaytext);
            }
            int i = 0;
            for (i; i < chat.size(); i++)
            {
                chat[i].setPosition(0, i * 20);
                window.draw(chat[i]);
            }

            Text drawtext(text, font, 20);
            drawtext.setFillColor(Color::Red);
            drawtext.setPosition(0, i * 20);
            window.draw(drawtext);

            window.display();
            window.clear();
        }
    }
};

