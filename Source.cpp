#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const unsigned WINDOW_WIDTH = 800;  // размеры экрана
const unsigned WINDOW_HEIGHT = 600;

const Color BACKGROUND_COLOR = Color::Black;  // цвет фона

const unsigned RADIUS_DIFFERENCE = 8;  // разность радиусов
const unsigned SOURCE_RADIUS = 2;  // радиус первой окружности
const unsigned OUTLINE_THICKNESS = 2;  // толщина границы
const Vector2f CENTER_POSITION = Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);  // позиция центра

const unsigned FRAME_RATE = 32;  // частота обновления (в миллисекундах)

const unsigned CIRCLE_COUNT = 120;  // кол-во окружностий

CircleShape circles[CIRCLE_COUNT];  // массив окружностей
Color colors[CIRCLE_COUNT];  // массив цветов окружностей


int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Заставка");

    // заполняем массив цветов
    for (int i = 0; i < CIRCLE_COUNT; i++) 
        colors[i] = Color(rand() % 255, rand() % 255, rand() % 255);
    
    // заполняем массив окружностей
    for (int i = 0; i < CIRCLE_COUNT; i++) {
        int radius = SOURCE_RADIUS + i * RADIUS_DIFFERENCE;  // радиус данной окружности
        CircleShape circle(radius);             // создаём новую окружность

        circle.setOrigin(radius, radius);
        circle.setPosition(CENTER_POSITION);  // центр у всех окружностей един
        circle.setFillColor(Color::Transparent);
        circle.setOutlineThickness(OUTLINE_THICKNESS);

        circle.setOutlineColor(colors[i]);

        circles[i] = circle;
    }

    int frameNumber = 0;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(BACKGROUND_COLOR);

        for (int i = 0; i < CIRCLE_COUNT; i++) {
            // меняем цвет каждой окружности на следующий 
            int nextColorIndex = (i - frameNumber + CIRCLE_COUNT) % CIRCLE_COUNT;
            circles[i].setOutlineColor(colors[nextColorIndex]);
            window.draw(circles[i]);
        }

        window.display();

        // меняем номер кадра на следующий
        frameNumber++;
        frameNumber %= CIRCLE_COUNT;

        sleep(milliseconds(FRAME_RATE));
    }

    return 0;
}