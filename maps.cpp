#include "maps.h"

// runs the selected game mode for grassy grove
// returns true if map exited when the game is finished
// returns false if game exited by escaping
bool Maps::map1(Timer &timer, int modeChoice, Score& check) {
    // set position of the track triggers to go through to score a point
    startingLine.setPosition(944, 148); //startingLine.scale(1, 2);
    midLine.setPosition(944, 682); //midLine.scale(1, 2);
    rightLine.setPosition(1522, 556); rightLine.rotate(-90);
    leftLine.setPosition(148, 556); leftLine.rotate(-90);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Indy 501!", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    // load wall texture and create wall sprite
    Texture wall;
    wall.loadFromFile("textures/maps/map1/wall.png");
    Sprite map1Border(wall);

    //map1Border.setScale(3, 2);

    // load grass texture and create grass sprite
    Texture map1GrassT;
    map1GrassT.loadFromFile("textures/maps/map1/grass_grove_grass.png");
    Sprite map1Grass(map1GrassT);
    map1Grass.setPosition(0, 0);

    // set audio for cone collision
    SoundBuffer coneB;
    coneB.loadFromFile("audio/cone.ogg");
    Sound coneS;
    coneS.setBuffer(coneB);
    // load cone texture and create sprite for cone
    Texture coneT;
    coneT.loadFromFile("textures/objects/cone.png");
    Sprite cone(coneT);
    cone.setPosition(300, 540);

    // load in full map
    Texture trackT;
    trackT.loadFromFile("textures/maps/map1/grassy_grove ver2.png");
    Sprite track(trackT);

    // set car's starting point
    car.setPosition(860.f, 280.f);
    car.setScale(2, 2);
    float v = 0.5f;
    timer.startTimer();
    while (window.isOpen())
    {
        // timer counts down if playing mode 1
        if (modeChoice == 1) {
            timer.setTimer(1, 0);
            timer.countDown();
        }
        // timer counts up if playing mode 2
        if (modeChoice == 2)
            timer.countUp();

        // quit back to menu if espace is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            system("cls");
            car.stopAudio();
            return false;
        }

        // if playing in time trials,
        // print the time and quit map if player wins (drives 3 laps)
        if (modeChoice == 2 && check.getNumScore() == 3) {
            car.stopAudio();
            return true;
        }
            

        // if playing in race against time
        if (modeChoice == 1 && timer.getMinutesLeft() <= 0 && timer.getSecondsLeft() <= 0 && timer.getMillisecondsLeft() <= 0) {
            car.stopAudio();
            return true;
        }
        // move car based on user input
        car.accelerate();
        car.drive();

        // duplicates car in CarRender class and uses the duplicate to determine collision
        hitBox.setPosition(car.getxPos() - 32, car.getyPos() - 32);

        // move cone back and forth if not hitting against the car
        if (!Collision::BoundingBoxTest(cone, hitBox)) {
            if (cone.getPosition().x <= 148)
                v = 0.5f;
            else if (cone.getPosition().x >= 398 - 32)
                v = -0.5f;
            cone.move(v, 0);
        }

        // collision knocks back car when it hits the cone
        if (Collision::CircleTest(hitBox, cone)) { 
            //std::cout << "COLLISION";
            coneS.play();
            car.setVelocity(-2 * car.getVelocity());
        }
        else {
            //std::cout << "NO COLLISION";
        }

        // slow down car if it is on the grass
        if (Collision::PixelPerfectTest(map1Grass, hitBox)) {
            if (car.getVelocity() > 0.f)
                car.setFriction(0.08f * car.getVelocity());
            else
                car.setFriction(-0.08f * car.getVelocity());
            // bounce car off wall if it is hitting the wall
            if (Collision::PixelPerfectTest(hitBox, map1Border)) {
                //car.setFriction(0.6 * car.getVelocity());
                car.setVelocity(car.getVelocity() * -1.5f);
            }
        }
        else { // set friction back to normal if back on track
            car.setFriction(0.008f);
        }

      
        //convex.rotate(1.f/20.f);
        check.checkPosition(hitBox, startingLine, midLine, rightLine, leftLine);
      
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(); // clear the window
        // draw the sprites in the window
        window.draw(track);
        window.draw(cone);
        window.draw(check);
        window.draw(timer);
        window.draw(startingLine);
        window.draw(car);
        /*window.draw(midLine);
        window.draw(rightLine);
        window.draw(leftLine);*/
        window.display(); // display the window
    }
}

// runs the selected game mode for figure eight
// returns true if map exited when the game is finished
// returns false if game exited by escaping
bool Maps::map2(Timer& timer, int modeChoice, Score& check) {
    // set position of the score
    check.setPosition(Vector2f(0, -350.f));
    // set position of the track triggers to go through to score a point
    startingLine.setPosition(968, 384); startingLine.rotate(-52); startingLine.scale(Vector2f(1.f, 22.f / 25.f));
    midLine.setPosition(928, 356); midLine.rotate(50); midLine.scale(Vector2f(1.f, 22.f / 25.f));
    rightLine.setPosition(1624, 526 + 16); rightLine.rotate(-90); rightLine.scale(Vector2f(1.f, 22.f / 25.f));
    leftLine.setPosition(74, 514 + 16); leftLine.rotate(-90); leftLine.scale(Vector2f(1.f, 22.f / 25.f));

    // set window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Indy 501!", sf::Style::Default, settings);
    window.setFramerateLimit(120);

    // load wall texture and create wall sprite
    Texture wall;
    wall.loadFromFile("textures/maps/wall.png");
    Sprite map1Border(wall);

    //map1Border.setScale(3, 2);

    // load grass texture and create grass sprite
    Texture map1GrassT;
    map1GrassT.loadFromFile("textures/maps/Fig_8_grass.png");
    Sprite map1Grass(map1GrassT);
    map1Grass.setPosition(0, 0);

    // load audio for cone collision
    SoundBuffer coneB;
    coneB.loadFromFile("audio/cone.ogg");
    Sound coneS;
    coneS.setBuffer(coneB);
    // load cone texture and create cone sprite
    Texture coneT;
    coneT.loadFromFile("textures/objects/cone.png");
    Sprite cone(coneT);
    cone.setPosition(778, 508);

    // load the full track texture and create its sprite
    Texture trackT;
    trackT.loadFromFile("textures/maps/Fig_8.png");
    Sprite track(trackT);
    //track.setScale(3, 2);

    // place car in correct starting position
    car.setxPos(963.f);
    car.setyPos(511.f);
    car.setDirection(-50.f*3.14159f/180.f);
    car.setScale(2, 2);
    float v = 0.5f;

    timer.startTimer(); // starts the timer for the mode selected
    
    while (window.isOpen()) // open window to play level until window is closed
    {
        // timer counts down if playing mode 1
        if (modeChoice == 1) {
            timer.setTimer(1, 0);
            timer.countDown();
        }
        // timer counts up if playing mode 2
        if (modeChoice == 2)
            timer.countUp();

        // quit back to menu if espace is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            system("cls");
            car.stopAudio();
            return false;
        }

        // if playing in time trials
        // print the time and quit map if player wins (drives 3 laps)
        if (modeChoice == 2 && check.getNumScore() == 3) {
            car.stopAudio();
            return true;
        }

        // if playing in race against time
        if (modeChoice == 1 && timer.getMinutesLeft() <= 0 && timer.getSecondsLeft() <= 0 && timer.getMillisecondsLeft() <= 0) {
            car.stopAudio();
            return true;
        }
        // move car based on user input
        car.accelerate();
        car.drive();

        // duplicates car in CarRender class and uses the duplicate to determine collision
        hitBox.setPosition(car.getxPos() - 32, car.getyPos() - 32);

        // move cone back and forth if not hitting against the car
        if (!Collision::BoundingBoxTest(cone, hitBox)) {
            if (cone.getPosition().x <= 778)
                v = 0.5f;
            else if (cone.getPosition().x >= 1142 - 32)
                v = -0.5f;
            cone.move(v, 0);
        }

        // collision knocks back car when it hits the cone
        if (Collision::CircleTest(hitBox, cone)) {
            //std::cout << "COLLISION";
            coneS.play();
            car.setVelocity(-2 * car.getVelocity());
        } else {
            //std::cout << "NO COLLISION";
        }

        // slow down car if it is on the grass
        if (Collision::PixelPerfectTest(map1Grass, hitBox)) {
            if (car.getVelocity() > 0)
                car.setFriction(0.08f * car.getVelocity());
            else
                car.setFriction(-0.08f * car.getVelocity());
            // bounce car off wall if it is hitting the wall
            if (Collision::PixelPerfectTest(hitBox, map1Border)) {
                car.setVelocity(car.getVelocity() * -1.5f);
            }
        } else { // set friction back to normal
            car.setFriction(0.008f);
        }

        // update values determining what triggers the car has passed
        check.checkPosition(hitBox, startingLine, midLine, rightLine, leftLine);

        sf::Event event;
        // close window if window exed out
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(); // clear the window
        // draw the sprites in the window
        window.draw(track);
        window.draw(cone);
        window.draw(check);
        window.draw(timer);
        window.draw(startingLine);
        window.draw(car);
        /*window.draw(midLine);
        window.draw(rightLine);
        window.draw(leftLine);*/
        window.display(); // display the window
    }
}

