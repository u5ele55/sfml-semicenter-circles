#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const unsigned WINDOW_WIDTH = 800;  // ������� ������
const unsigned WINDOW_HEIGHT = 600;

const Color BACKGROUND_COLOR = Color::Black;  // ���� ����

const unsigned RADIUS_DIFFERENCE = 8;  // �������� ��������
const unsigned SOURCE_RADIUS = 2;  // ������ ������ ����������
const unsigned OUTLINE_THICKNESS = 2;  // ������� �������
const Vector2f CENTER_POSITION = Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);  // ������� ������

const unsigned FRAME_RATE = 32;  // ������� ���������� (� �������������)

const unsigned CIRCLE_COUNT = 120;  // ���-�� �����������

CircleShape circles[CIRCLE_COUNT];  // ������ �����������
Color colors[CIRCLE_COUNT];  // ������ ������ �����������


int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "��������");

    // ��������� ������ ������
    for (int i = 0; i < CIRCLE_COUNT; i++) 
        colors[i] = Color(rand() % 255, rand() % 255, rand() % 255);
    
    // ��������� ������ �����������
    for (int i = 0; i < CIRCLE_COUNT; i++) {
        int radius = SOURCE_RADIUS + i * RADIUS_DIFFERENCE;  // ������ ������ ����������
        CircleShape circle(radius);             // ������ ����� ����������

        circle.setOrigin(radius, radius);
        circle.setPosition(CENTER_POSITION);  // ����� � ���� ����������� ����
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
            // ������ ���� ������ ���������� �� ��������� 
            int nextColorIndex = (i - frameNumber + CIRCLE_COUNT) % CIRCLE_COUNT;
            circles[i].setOutlineColor(colors[nextColorIndex]);
            window.draw(circles[i]);
        }

        window.display();

        // ������ ����� ����� �� ���������
        frameNumber++;
        frameNumber %= CIRCLE_COUNT;

        sleep(milliseconds(FRAME_RATE));
    }

    return 0;
}