// 1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Ball.h"
#include "Paddle.h"
using namespace sf;
using namespace std;

template <class T1, class T2> bool isIntersecting(T1& A, T2& B)
{
    return A.right() >= B.left() && A.left() <= B.right()
        && A.bottom() >= B.top() && A.top() <= B.bottom();
}

bool collisionTest(Paddle& paddle, Ball& ball)
{
    if (!isIntersecting(paddle, ball)) return false;

    if(ball.getPosition().y > paddle.getPosition().y)
    ball.moveDown();

    else if (ball.getPosition().y < paddle.getPosition().y)
    ball.moveUp();

    if (ball.getPosition().x < paddle.getPosition().x)
        ball.moveLeft();

    else if (ball.getPosition().x > paddle.getPosition().x)
        ball.moveRight();
}
    Text score;
    Font font;
    int wynik1{}, wynik2{};
    

int main()
{ 
        font.loadFromFile("Fonts\\gotham-black-italic.ttf");
        score.setFont(font);
        score.setCharacterSize(24);
        score.setFillColor(Color::Green);

        Ball ball(400, 300);
        Paddle paddle1(550, 500, Keyboard::Key::Left, Keyboard::Key::Right);
        Paddle paddle2(150, 100, Keyboard::Key::A, Keyboard::Key::D);
        RenderWindow window{ VideoMode{800,600}, "PONG GAME" };
        window.setFramerateLimit(60);
        Event event;
        int i = 0;
        while (true)
        {
            score.setString( to_string(wynik1) + " : " + to_string(wynik2));
            window.clear(Color::Black);
            window.pollEvent(event);

            if (event.type == Event::Closed)
            {
                window.close();
                break;
            }
            ball.update();
            paddle1.update();
            paddle2.update();
            collisionTest(paddle1, ball);
            collisionTest(paddle2, ball);
            window.draw(ball);
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(score);
            window.display();
    }
    return 0;
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
