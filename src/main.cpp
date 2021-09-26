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
            14,
            30,
            8,
            34,
            58
    );

    playerSprite.setAnimation({0, 1, 2, 3, 4, 5, 4, 3, 2, 1});

    std::shared_ptr<Player> player = std::make_shared<Player>(0, 58, 640 - 33,  480);
    sf::RenderWindow window(sf::VideoMode(640, 480), "Robot Game");

    std::atomic<bool> stopThread{false};

    std::thread keyboardThread = std::thread([&stopThread, player](){
        while (!stopThread.load()) {
            std::this_thread::yield();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player->moveX(-1);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player->moveX(1);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player->jump();

            player->pullDown();
        }
    });

    std::stringstream ss;
    MultiTextBox debugConsole = MultiTextBox({
        {"position", Text(font, 20, sf::Color::White)},
        {"jumpStatus", Text(font, 20, sf::Color::White)}
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
        ss << "Player Grounded: " << ((player->isGrounded()) ? "True " : "False");
        debugConsole.update("jumpStatus", ss.str());

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
