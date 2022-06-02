#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

void startAliens(sf::Sprite alienArray[55]) {
    int num = 0;
    for (int i=0; i<5; i++) {
        for (int j=0; j<11; j++) {
            alienArray[num].setPosition(j*75+15, i*50);
            num++;
        }
    }

}


int main()
{

    //create the main window
    sf::RenderWindow app(sf::VideoMode(1200,800), "SFML window");
    double speed = .05;
    double speed2 = .07;
    int counter = 0;
    bool check = false;
    bool check2 = false;
    bool check3 = false;
    bool shoot = true;
    bool explode = true;
    bool start = true;
    bool lose = false;
    bool bob = true;
    bool moving = true;
    bool moving2 = true;

    int s = 0;

    sf:: Texture texture;
    texture.loadFromFile("spaceInvadersSpriteSheet.png");

    sf::IntRect rectSource(75,320,45,35);
    sf::IntRect rectSource1(0,0,75,50);
    sf::IntRect rectSource2(0,60,75,50);
    sf::IntRect rectSource3(155,0,50,50);
    sf::IntRect rectSourceExplosion(186,325,45,35);



    //load audio
    sf::SoundBuffer bgSoundBuff;
    bgSoundBuff.loadFromFile("backgroundSong.wav");
    sf::Sound bgSound;
    bgSound.setBuffer(bgSoundBuff);
    bgSound.play();
    bgSound.setLoop(true);


    sf::SoundBuffer shotBuff;
    shotBuff.loadFromFile("shoot.wav");
    sf::Sound shotSound;
    shotSound.setBuffer(shotBuff);

    sf::SoundBuffer explosionBuff;
    explosionBuff.loadFromFile("explosion.wav");
    sf::Sound explosionSound;
    explosionSound.setBuffer(explosionBuff);



    //load ship
    sf::Texture shipTexture;
    shipTexture.loadFromFile("spaceInvadersSpriteSheet.png");

    sf::Sprite ship(shipTexture);
    ship.setTextureRect(rectSource);
    ship.setOrigin(22, 18);
    ship.setPosition(-600, 750);



    sf:: Texture bigBoy;
    bigBoy.loadFromFile("alien.png");
    sf::Sprite gigaAlien(bigBoy);
    gigaAlien.setOrigin(50, 50);
    gigaAlien.setPosition(-70, 30);
    gigaAlien.setScale(.05,.05);



    //load bullet
    sf::RectangleShape bullet;
    bullet.setSize(sf::Vector2f(5, 20));
    bullet.setOrigin(2.5, 10);
    bullet.setPosition(-50, 0);

    //explosion
    sf::Sprite explosion(texture);
    explosion.setTextureRect(rectSourceExplosion);
    explosion.setOrigin(22, 18);
    explosion.setPosition(3000,500);

    //start screen
    sf::IntRect rectSourceOpen(230,250,60,50);
    sf::Sprite welcome(texture);
    welcome.setTextureRect(rectSourceOpen);
    welcome.setOrigin(30, 25);
    welcome.setPosition(600,200);
    welcome.setScale(7.f,7.f);


    sf::Font siFont;
    siFont.loadFromFile("space_invaders.ttf");

    sf::Text welcomeText;
    welcomeText.setFont(siFont);
    welcomeText.setString("Play Space Invaders");
    welcomeText.setCharacterSize(32);
    welcomeText.setPosition(400, 500);

    sf::Text pressStart;
    pressStart.setFont(siFont);
    pressStart.setString("(Press the space bar to start)");
    pressStart.setCharacterSize(20);
    pressStart.setPosition(400, 700);

    sf::Text loser;
    loser.setFont(siFont);
    loser.setString("YOU LOSE!");
    loser.setCharacterSize(100);
    loser.setPosition(350, 200);

    sf::Text winner;
    winner.setFont(siFont);
    winner.setString("YOU WIN!");
    winner.setCharacterSize(100);
    winner.setPosition(375,200);

    sf::Text score;
    score.setFont(siFont);
    score.setString("Score: " + std::to_string(s));
    score.setCharacterSize(20);
    score.setPosition(-150, 725);




    sf::Sprite alienArray[55];
    int num = 0;
    for(int i= 0; i < 5; i ++) {
        for(int j = 0;j < 11;j++ ) {
            if (i==2 || i==1){

                alienArray[num].setTexture(texture);
                alienArray[num].setTextureRect(rectSource1);
                alienArray[num].setOrigin(75/2,50/2);
                alienArray[num].setPosition(j*75+15, i*50-1000);
            } else if (i == 3 || i == 4) {
                alienArray[num].setTexture(texture);
                alienArray[num].setTextureRect(rectSource2);
                alienArray[num].setOrigin(75/2,50/2);
                alienArray[num].setPosition(j*75+15, i*50-1000);
            } else {
                alienArray[num].setTexture(texture);
                alienArray[num].setTextureRect(rectSource3);
                alienArray[num].setOrigin(50/2,50/2);
                alienArray[num].setPosition(j*75+15, i*50-1000);
            }
            alienArray[num].setTexture(texture);


            num ++;
        }
    }



    sf::Clock clock;
    int fnum = 0;

    //Game loop
    while (app.isOpen())
    {
        //Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            //Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }
        explosion.move(speed,0);


        //checking to see if game is ended
        if (bob == true){

            //start screen
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ) {
                if (start == true) {
                    welcome.move(-1200, 0);
                    welcomeText.move(-1200, 0);
                    pressStart.move(-1200, 0);
                    start = false;
                    startAliens(alienArray);
                    ship.setPosition(600, 750);
                    score.setPosition(50, 725);


                    speed = .01;
                }


            }

            //move ship
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shoot == true) {
                shotSound.play();
                bullet.setPosition(sf::Vector2f(ship.getPosition().x, ship.getPosition().y));
                shoot = false;


            }

            //blocking the ship from off the screen
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ship.getPosition().x > 22) {
                ship.move(-.5,0);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& ship.getPosition().x < 1180) {
                ship.move(.5,0);
            }



            //if  bullet hits array
            for ( int i =0; i < 55; i ++) {
                alienArray[i].move(speed,0);
                if (alienArray[i].getGlobalBounds().intersects(bullet.getGlobalBounds())){
                    explosion.setPosition(sf::Vector2f(alienArray[i].getPosition().x, alienArray[i].getPosition().y + 5));
                    alienArray[i].move(0,-2000);
                    bullet.move(0,-800);
                    shoot = true;
                    explode = false;
                    explosionSound.play();


                            //score for each alien hit
                            if (i > 32 && i <= 55) {
                                s = s + 10;
                            }
                            else if (i > 10 && i <= 32){
                                s = s + 20;

                            }
                            else if (i <=10){
                                s = s + 40;

                            }
                            score.setString("Score: " + std::to_string(s));
                            break;

                }

                //checks if array reaches the end so that it can move down
                if (alienArray[i].getPosition().x >1180 || alienArray[i].getPosition().x < 15 ){
                    if (alienArray[i].getPosition().y > 0) {
                        check = true;
                    }
                }
            }

            std::cout <<counter;
            // || gigaAlien.getPosition().x > -70
            // checks to see when to send out the big alien
            //if (gigaAlien.getPosition().x >= 1120 && gigaAlien.getPosition().x >= -70){

            if (counter == 3) {
                if (moving2){
                    gigaAlien.setPosition(-70, 30);
                    moving2 = false;
                }
                gigaAlien.move(speed2,0);
            }
            else if (counter == 4) {

                if(moving) {
                    gigaAlien.setPosition(1130, 30);
                    moving = false;
                }

                speed2 = -0.07;
                gigaAlien.move(speed2,0);
            }

            if (gigaAlien.getGlobalBounds().intersects(bullet.getGlobalBounds())) {
                explosion.setPosition(sf::Vector2f(gigaAlien.getPosition().x, gigaAlien.getPosition().y + 5));
                gigaAlien.setPosition(0, -100);
                bullet.move(0,-800);
                shoot = true;
                explode = false;
                explosionSound.play();
                std::cout << "bob";
                s = s + 100;
                score.setString("Score: " + std::to_string(s));


            }







            // makes array move down

            if (check) {
                speed *= -1;

                for(int i = 0; i < 55;i++){
                    alienArray[i].move (0,40);
                }
                check = false;
                counter++;
            }


            //check to see if spaceships reach the bottom for player to lose
            if (counter == 13) {
                lose = true;
                bob = false;
            }

            // checks if i can shoot
            if (shoot == false){
                bullet.move(0,-.2);
                if (bullet.getPosition().y <-25 ){
                   shoot = true;
                }

            }


            //cycles the sprite textures
            if (clock.getElapsedTime().asSeconds() > .50f) {
                    if(explode == false) {
                        explosion.move(0,-800);
                        explode = true;
                    }
                if (fnum == 0) {
                    rectSource1.left += 75;
                    rectSource2.left += 75;
                    rectSource3.left += 55;
                    fnum = 1;
                } else if (fnum ==1 ) {
                    rectSource1.left -= 75;
                    rectSource2.left -= 75;
                    rectSource3.left -= 55;
                    fnum = 0;
                }
                for ( int i = 0;i < 55; i ++) {
                    if (i < 11) {
                        alienArray[i].setTextureRect(rectSource3);
                    }else if (i > 10 && i < 33) {
                        alienArray[i].setTextureRect(rectSource2);
                    } else {
                        alienArray[i].setTextureRect(rectSource1);
                    }
                }
                clock.restart();

            }
        }






        app.clear();
        if (s < 1100 && lose != true){
            for (int i = 0; i <55; i ++){
                app.draw(alienArray[i]);
            }
            app.draw(ship);
            app.draw(bullet);
            app.draw(explosion);
            app.draw(score);
            app.draw(gigaAlien);


        } else {

            pressStart.setPosition(400, 700);
            welcomeText.setPosition(400, 500);

            if (lose == true) {
                app.draw(loser);
            } else {
                app.draw(winner);
            }

            if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                for (int i = 0; i <55; i ++){
                    app.draw(alienArray[i]);
                }
                welcomeText.move(-1200, 0);
                pressStart.move(-1200, 0);


                bob = true;
                s = 0;
                counter = 0;
                start = true;
                lose = false;
                moving = true;
                moving2 = true;
                score.setString("Score: " + std::to_string(s));
                app.draw(ship);
                app.draw(bullet);
                app.draw(explosion);
                app.draw(score);
                startAliens(alienArray);
                ship.setPosition(600, 750);
                score.setPosition(50, 725);

                }

            }


        app.draw(welcome);
        app.draw(welcomeText);
        app.draw(pressStart);


        app.display();
    }

    return 0;
}
