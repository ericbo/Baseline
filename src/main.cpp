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

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int main(int argc, char *argv[]) {
    XInitThreads();
    const std::string &characterSheet = "Textures/minotaur.png";
    const std::string &fonts = "Fonts/Roboto-Thin.ttf";
    const auto &appStartTime = std::chrono::steady_clock::now();
    auto lastRenderTime = std::chrono::steady_clock::now();
    auto fpsLastDisplayTime = std::chrono::steady_clock::now();
    uint64_t totalFrames = 1;

    sf::Font font;
    if (!font.loadFromFile(fonts)) {
        return 1;
    }

    int playerWidth = 76;
    int playerHeight = 68;

    Sprite playerSprite(
            characterSheet,
            1024,
            1920,
            0,
            30,
            0,
            14,
            20,
            28,
            playerWidth,
            playerHeight
    );


    std::shared_ptr<Player> player = std::make_shared<Player>(0, playerHeight, WIDTH - playerWidth,   HEIGHT);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Robit");

    std::atomic<bool> stopThread{false};

    MultiTextBox debugConsole = MultiTextBox({
             {"title", Text(font, 20, sf::Color::White)},
             {"position", Text(font, 18, sf::Color::White)},
             {"jumpStatus", Text(font, 18, sf::Color::White)},
             {"state", Text(font, 18, sf::Color::White)},
             {"fps", Text(font, 18, sf::Color::White)}
     });
    debugConsole.update("title", "Debug");
    debugConsole.hide();

    auto lastKeyCheck = std::chrono::steady_clock::now();

    std::thread keyboardThread = std::thread([&stopThread, player, &playerSprite, &debugConsole, &lastKeyCheck](){
        Player::state lastDirection = Player::LEFT;
        while (!stopThread.load()) {
            std::this_thread::yield();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));

            player->updateState();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                player->attack();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player->moveX(-1);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player->moveX(1);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player->jump();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastKeyCheck).count();
                if (elapsed > 200 && debugConsole.isHidden()) {
                    debugConsole.show();
                    lastKeyCheck = std::chrono::steady_clock::now();
                } else if (elapsed > 200) {
                    debugConsole.hide();
                    lastKeyCheck = std::chrono::steady_clock::now();
                }
            }

            switch (player->getState()) {
                case Player::IDEL:
                    if (lastDirection == Player::IDEL) {
                        break;
                    }
                    playerSprite.setAnimation({0, 1, 2, 3, 4}, 200);
                    break;
                case Player::LEFT:
                    if (lastDirection == Player::LEFT) {
                        break;
                    }
                    playerSprite.setAnimation({21, 22, 23, 24 , 25});
                    playerSprite.mirror();
                    break;
                case Player::RIGHT:
                    if (lastDirection == Player::RIGHT) {
                        break;
                    }
                    playerSprite.setAnimation({21, 22, 23, 24 , 25});
                    playerSprite.restore();
                    break;
                case Player::JUMPING:
                    if (lastDirection == Player::JUMPING) {
                        break;
                    }
                    playerSprite.setAnimation({32, 33, 34, 35}, Sprite::Animation::SINGLE);
                    break;
                case Player::ATTACK:
                    if (playerSprite.isAnimationDone()) {
                        player->idle();
                    }
                    if (lastDirection == Player::ATTACK) {
                        break;
                    }
                    playerSprite.setAnimation({60, 61, 62, 63, 64, 64, 67, 68}, Sprite::Animation::SINGLE);
                    break;
            }

            lastDirection = player->getState();

            player->pullDown();
        }
    });

    std::stringstream ss;

    window.setFramerateLimit(60);

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
        ss << "Grounded : " << ((player->isGrounded()) ? "True " : "False");
        debugConsole.update("jumpStatus", ss.str());

        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(lastRenderTime - appStartTime).count();
        auto lastDisplay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - fpsLastDisplayTime).count();
        if (elapsed > 0 && lastDisplay > 200) {
            ss.str("");
            ss << "FPS: " << totalFrames / elapsed;
            debugConsole.update("fps", ss.str());
            fpsLastDisplayTime = std::chrono::steady_clock::now();
        }

        ss.str("");
        ss << "State :";

        Player::state playerDirection = player->getState();

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
            case Player::JUMPING:
                ss << " JUMP";
                break;
            case Player::ATTACK:
                ss << " ATCK";
                break;
        }

        debugConsole.update("state", ss.str());

        window.clear();
        playerSprite.draw(window, player->getX(), player->getY());
        debugConsole.draw(window, WIDTH, 0);
        window.display();
        lastRenderTime = std::chrono::steady_clock::now();
        totalFrames++;
    }

    stopThread.store(true);

    if (keyboardThread.joinable()) {
        keyboardThread.join();
    }

    return 0;
}
