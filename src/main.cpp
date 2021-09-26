#include <SFML/Graphics.hpp>

#include <Domain/Player.h>
#include <Domain/Sprite.h>
#include <Domain/MultiTextBox.h>

#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <sstream>
#include <Domain/Text.h>

int main(int argc, char *argv[]) {
    XInitThreads();
    const std::string &file = "/home/eric/Documents/Baseline/src/textures/spritesheet.png";
    const std::string &fonts = "/home/eric/Documents/Baseline/src/fonts/Roboto-Thin.ttf";

    sf::Font font;
    if (!font.loadFromFile(fonts))
    {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    Sprite playerSprite(
            file,
            512,
            512,
            6,
            12,
            0,
            2,
            12,
            8,
            52,
            56
    );

    playerSprite.setAnimation({40, 41, 42, 43, 44, 45, 46, 47});

    std::shared_ptr<Player> player = std::make_shared<Player>(0, 56, 640 - 52,  480);
    sf::RenderWindow window(sf::VideoMode(640, 480), "Robot Game");

    std::atomic<bool> stopThread{false};

    std::thread keyboardThread = std::thread([&stopThread, player, &playerSprite](){
        Player::direction lastDirection = Player::LEFT;
        while (!stopThread.load()) {
            std::this_thread::yield();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));

            player->updateDirection();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player->moveX(-1);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player->moveX(1);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player->jump();
            }

            switch (player->getDirection()) {
                case Player::IDEL:
                    if (lastDirection == Player::IDEL) {
                        break;
                    }
                    playerSprite.setAnimation({8, 9, 10, 11, 12});
                    playerSprite.restore();
                    break;
                case Player::LEFT:
                    if (lastDirection == Player::LEFT) {
                        break;
                    }
                    playerSprite.setAnimation({40, 41, 42, 43, 44, 45, 46, 47});
                    playerSprite.restore();
                    break;
                case Player::RIGHT:
                    if (lastDirection == Player::RIGHT) {
                        break;
                    }
                    playerSprite.setAnimation({40, 41, 42, 43, 44, 45, 46, 47});
                    playerSprite.mirror();
                    break;
            }

            lastDirection = player->getDirection();

            player->pullDown();
        }
    });

    std::stringstream ss;
    MultiTextBox debugConsole = MultiTextBox({
        {"position", Text(font, 20, sf::Color::White)},
        {"jumpStatus", Text(font, 20, sf::Color::White)},
        {"direction", Text(font, 20, sf::Color::White)}
    });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ss.str("");
        ss << "(" << player->getX() << ", " << player->getY() << ")";
        debugConsole.update("position", ss.str());

        ss.str("");
        ss << "Grounded: " << ((player->isGrounded()) ? "True " : "False");
        debugConsole.update("jumpStatus", ss.str());

        ss.str("");
        ss << "Direction :";

        Player::direction playerDirection = player->getDirection();

        switch(playerDirection) {
            case Player::IDEL:
                ss << " IDLE";
                break;
            case Player::LEFT:
                ss << " LEFT";
                break;
            case Player::RIGHT:
                ss << " RIGHT";
                break;
        }

        debugConsole.update("direction", ss.str());

        window.clear();
        playerSprite.draw(window, player->getX(), player->getY());
        debugConsole.draw(window, 640, 0);
        window.display();
    }

    stopThread.store(true);

    if (keyboardThread.joinable()) {
        keyboardThread.join();
    }

    return 0;
}
