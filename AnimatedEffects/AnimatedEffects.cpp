#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
using namespace std;
using namespace sf;

class AnimatedEffect {
private:
    static Texture texture;
    Sprite sprite;
    IntRect frameLocation;
    Vector2f position;

    int spriteSize;
    int rows;
    int columns;
    bool finished;
public:
    AnimatedEffect(string path, Vector2f position, int scaleValue, int spriteSize,
        int rows, int columns) {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
        sprite.scale(scaleValue, scaleValue);
        sprite.setOrigin(spriteSize / 2, spriteSize / 2);
        sprite.setPosition(position);

        this->spriteSize = spriteSize;
        this->rows = rows;
        this->columns = columns;

        frameLocation = IntRect(0, 0, spriteSize, spriteSize);
        sprite.setTextureRect(frameLocation);

        finished = false;
    }

    bool isFinished() {
        return finished;
    }

    void playAnimation() {
        if (!finished) {
            frameLocation.left += spriteSize;
            if (frameLocation.left >= columns * spriteSize) {
                frameLocation.left = 0;
                frameLocation.top += spriteSize;
                if (frameLocation.top >= (rows - 1) * spriteSize) {
                    frameLocation.top = (rows - 1) * spriteSize;
                    finished = true;
                }
            }
            sprite.setTextureRect(frameLocation);
        }
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
};
Texture AnimatedEffect::texture;

int main() {
    RenderWindow window(VideoMode(800, 800), "Animated Effects!");
    vector<AnimatedEffect> effects;
    effects.push_back(AnimatedEffect("./sprites/explosion1.png", Vector2f(200, 200), 4, 46, 4, 3));
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        for (auto& effect : effects) {
            if (!effect.isFinished()) {
                effect.playAnimation();
                effect.draw(window);
            }
            else effects.pop_back();
        }
        window.display();
        Sleep(75);
    }
}