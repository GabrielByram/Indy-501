// this is a test - gabriel
#include "Score.h"
#include "maps.h"
#include <cmath>
#include "Chat.h"
#define PI 3.14159
using namespace std;
int main() {
    // menu
    Music bgm;
    bgm.openFromFile("audio/backgroundMusic.ogg");
    bgm.setVolume(10);
    Chat chat;
    Timer timer; // creates Timer object
    int modeChoice = 0, mapChoice = 0, carChoice = 0; // variables to store menu choices
    bool hasQuit = false; // variable to determine whether playing wants to quit the game
    while (!hasQuit) {
        // menu for mode choice
        do {
            cout << "--------------INDY 501!--------------\n";
            cout << "1. Race Against the Clock\n";
            cout << "2. Time Trials\n";
            cout << "3. Game Rules\n";
            cout << "4. Network Chat\n";
            cout << "5. Quit Game\n";
            cin >> modeChoice;
        } while (modeChoice < 1 || modeChoice > 5);
        // menu for map choice
        if (modeChoice != 4 && modeChoice != 3 && modeChoice != 5) {
            do {
                system("cls");
                cout << "Select a map!\n";
                cout << "1. Grassy Grove\n";
                cout << "2. Figure Eight\n";
                cin >> mapChoice;
            } while (mapChoice < 1 || mapChoice > 2);
            // menu for car choice
            do {
                system("cls");
                cout << "Select a car!\n";
                cout << "1. Super Steven\n";
                cout << "2. Omega Oliver\n";
                cout << "3. Awesome Aayush\n";
                cout << "4. Grand Gabriel\n";
                cin >> carChoice;
            } while (carChoice < 1 || carChoice > 4);

            // create chosen car
            float baseVel = 0, maxVel = 0, friction = 0, turnSpeed = 0;
            Texture carTex;
            // steven
            if (carChoice == 1) {
                carTex.loadFromFile("textures/objects/car3.png");
                baseVel = 0.05f;
                maxVel = 8.f;
                turnSpeed = 0.045f;
            }
            // oliver
            if (carChoice == 2) {
                carTex.loadFromFile("textures/objects/car.png");
                baseVel = 0.05f;
                maxVel = 7.f;
                turnSpeed = 0.04f;
            }
            // aayush
            if (carChoice == 3) {
                carTex.loadFromFile("textures/objects/car4.png");
                baseVel = 0.04f;
                maxVel = 8.f;
                turnSpeed = 0.055f;
            }
            // gabriel
            if (carChoice == 4) {
                carTex.loadFromFile("textures/objects/car2.png");
                baseVel = 0.03f;
                maxVel = 15.f;
                turnSpeed = 0.045f;
            }

            friction = 0.008f;
            CarRender car(baseVel, maxVel, friction, turnSpeed, carTex);

            Texture bit32Circle;
            bit32Circle.loadFromFile("textures/misc/32bitCircle.png");
            Sprite carCircle(bit32Circle);
            carCircle.setScale(2, 2);

            Maps levels(car, carCircle);
            Score check;

            // launch map 1 if map 1 is chosen
            if (mapChoice == 1) {
                car.setFriction(0.008f);
                bgm.play();
                if (levels.map1(timer, modeChoice, check) == true) { // if they stay in the map the entire time in mode 1 or complete all 3 laps in mode 2
                    bgm.stop();
                    cout << "Congratulations! You win!\n";
                    system("pause");
                    if (modeChoice == 1) {
                        // print out user's stats to the console
                        if (check.getNumScore() != 1)
                            cout << "You drove " << check.getNumScore() << " laps.\n";
                        else
                            cout << "You drove " << check.getNumScore() << " lap.\n";
                        system("pause");
                        //system("pause");
                    }
                    if (modeChoice == 2) {
                        // print out user's stats to the console
                        cout << "You drove 3 laps in " << timer.getMinutes() << " minutes and " << timer.getSeconds() << " seconds.\n";
                        system("pause");
                        int totalSeconds = timer.getMinutes() * 60 + timer.getSeconds();
                        int totalMinutes = totalSeconds / 60;
                        if (totalMinutes > 0)
                            totalSeconds -= totalMinutes * 60;
                        float avgMinutes = totalMinutes / 3.0f;
                        float avgSeconds = totalSeconds / 3.0f;
                        if (avgMinutes > 0)
                            cout << "Your average lap time was " << avgMinutes << " minutes and " << avgSeconds << " seconds.\n";
                        else
                            cout << "Your average lap time was " << avgSeconds << " seconds.\n";
                        system("pause");
                    }
                    system("cls");
                }
                else
                    bgm.stop();
            }
            // launch map 2 if map 2 is chosen
            if (mapChoice == 2) {
                car.setFriction(0.008f);
                bgm.play();
                if (levels.map2(timer, modeChoice, check) == true) { // if they stay in the map the entire time in mode 1 or complete all 3 laps in mode 3
                    bgm.stop();
                    cout << "Congratulations! You win!\n";
                    system("pause");
                    if (modeChoice == 1) {
                        // print out user's stats to the console
                        cout << "You drove " << check.getNumScore() << " laps.\n";
                        system("pause");
                    }
                    if (modeChoice == 2) {
                        // print out user's stats to the console
                        cout << "You drove 3 laps in " << timer.getMinutes() << " minutes and " << timer.getSeconds() << " seconds.\n";
                        system("pause");
                        int totalSeconds = timer.getMinutes() * 60 + timer.getSeconds();
                        float avgSeconds = totalSeconds / 3.0f;
                        float avgMinutes = 0.0f;

                        if (avgSeconds >= 60) {
                            avgMinutes = avgSeconds / 60.0f;
                        }

                        if (avgMinutes >= 1)
                            cout << "Your average lap time was " << avgMinutes << " minutes and " << avgSeconds << " seconds.\n";
                        else
                            cout << "Your average lap time was " << avgSeconds << " seconds.\n";
                        cin.ignore();
                        system("pause");
                        system("cls");
                    }
                }
                else
                    bgm.stop();
            }
            
        }
        // print out rules
        else if (modeChoice == 3) {
            cout << "Indy 501 is our own take on the classic Atari title Indy 500.\n";
            cout << "Use W to move forward and use S to go in reverse.\n";
            cout << "Use A to steer to the left and use D to steer to the right.\n";
            cout << "Race against the clock: Complete as many laps as you can before the timer runs out!\n";
            cout << "Time Trials: Improve your skills by timing yourself while completing 3 laps.\n";
            cout << "Happy racing!\n";
            system("pause");
            system("cls");
        } else if (modeChoice == 4) {
            system("cls");
            chat.clearChat();
            chat.run();
            system("cls");
        }
        else // mark that the user wants to quit the game
            hasQuit = true;
    }
}