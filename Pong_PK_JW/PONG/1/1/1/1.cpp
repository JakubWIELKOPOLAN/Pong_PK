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

    if (ball.getPosition().y > paddle.getPosition().y)
        ball.moveDown();

    else if (ball.getPosition().y < paddle.getPosition().y)
        ball.moveUp();

    if (ball.getPosition().x < paddle.getPosition().x)
        ball.moveLeft();

    else if (ball.getPosition().x > paddle.getPosition().x)
        ball.moveRight();
}

Text score, roundText, labelPaddle1, labelPaddle2; // Dodajemy nowe obiekty Text dla etykiet
Font font;
int wynik1{}, wynik2{};
int wynikiRundy[3][2] = { 0 }; // Tablica na wyniki rund
int currentRound = 1;
int maxScores[3] = { 10, 5, 1 }; // Maksymalne punkty dla każdej rundy

bool checkRoundEnd(int score, int maxScore) {
    return score >= maxScore;
}

int main()
{
    font.loadFromFile("Fonts\\gotham-black-italic.ttf");
    score.setFont(font);
    score.setCharacterSize(24);
    score.setFillColor(Color::Green);

    roundText.setFont(font); // Ustawienia dla tekstu z informacją o rundzie
    roundText.setCharacterSize(24);
    roundText.setFillColor(Color::White);
    roundText.setString("Round: 1"); // Ustawienie początkowej wartości
    roundText.setPosition(650, 10); // Ustawienie pozycji tekstu w prawym górnym rogu

    labelPaddle1.setFont(font); // Ustawienia dla tekstu etykiety dla paletki 1
    labelPaddle1.setCharacterSize(20);
    labelPaddle1.setFillColor(Color::White);
    labelPaddle1.setString("Paddle 1");
    labelPaddle1.setPosition(400 - labelPaddle1.getGlobalBounds().width / 2, 10); // Ustawienie na środku górnego marginesu

    labelPaddle2.setFont(font); // Ustawienia dla tekstu etykiety dla paletki 2
    labelPaddle2.setCharacterSize(20);
    labelPaddle2.setFillColor(Color::White);
    labelPaddle2.setString("Paddle 2");
    labelPaddle2.setPosition(400 - labelPaddle2.getGlobalBounds().width / 2, 590 - labelPaddle2.getGlobalBounds().height); // Ustawienie na środku dolnego marginesu

    Ball ball(400, 300);
    Paddle paddle1(550, 500, Keyboard::Key::Up, Keyboard::Key::Down); // Paletka 1 - sterowanie strzałkami
    Paddle paddle2(150, 100, Keyboard::Key::A, Keyboard::Key::D); // Paletka 2 - sterowanie A i D
    RenderWindow window{ VideoMode{800,600}, "PONG GAME" };
    window.setFramerateLimit(60);
    Event event;

    while (true)
    {
        score.setString(to_string(wynik1) + " : " + to_string(wynik2));
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
        window.draw(roundText); // Dodajemy rysowanie tekstu z informacją o rundzie
        window.draw(labelPaddle1); // Dodajemy etykietę paletki 1
        window.draw(labelPaddle2); // Dodajemy etykietę paletki 2
        window.display();

        if (checkRoundEnd(wynik1, maxScores[currentRound - 1]) || checkRoundEnd(wynik2, maxScores[currentRound - 1])) {
            if (currentRound == 1) {
                wynikiRundy[0][0] = wynik1;
                wynikiRundy[0][1] = wynik2;
                currentRound++;
                wynik1 = wynik2 = 0;
                roundText.setString("Round: 2"); // Aktualizujemy tekst z informacją o rundzie
            }
            else if (currentRound == 2) {
                wynikiRundy[1][0] = wynik1;
                wynikiRundy[1][1] = wynik2;
                currentRound++;
                wynik1 = wynik2 = 0;
                roundText.setString("Round: 3"); // Aktualizujemy tekst z informacją o rundzie
            }
            else if (currentRound == 3) {
                wynikiRundy[2][0] = wynik1;
                wynikiRundy[2][1] = wynik2;

                // Tabela wyników
                window.clear(Color::Black);
                Text endGameText;
                endGameText.setFont(font);
                endGameText.setCharacterSize(24);
                endGameText.setFillColor(Color::White);
                endGameText.setString("End of Game\n\nRound 1\nPaddle 1: " + to_string(wynikiRundy[0][0]) + "\nPaddle 2: " + to_string(wynikiRundy[0][1]) +
                    "\n\nRound 2\nPaddle 1: " + to_string(wynikiRundy[1][0]) + "\nPaddle 2: " + to_string(wynikiRundy[1][1]) +
                    "\n\nRound 3\nPaddle 1: " + to_string(wynikiRundy[2][0]) + "\nPaddle 2: " + to_string(wynikiRundy[2][1]));
                endGameText.setPosition(50, 50); // Ustawienie pozycji tekstu

                Text restartText;
                restartText.setFont(font);
                restartText.setCharacterSize(24);
                restartText.setFillColor(Color::White);
                restartText.setString("Do you want to play again?\n (Press Enter to play again, Press Esc to exit)");
                restartText.setPosition(50, 400); // Ustawienie pozycji tekstu

                window.draw(endGameText);
                window.draw(restartText);
                window.display();

                // Oczekiwanie na decyzję graczy
                bool playAgain = false;
                while (true) {
                    if (Keyboard::isKeyPressed(Keyboard::Return)) {
                        playAgain = true;
                        break;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        playAgain = false;
                        break;
                    }
                }

                if (playAgain) {
                    currentRound = 1;
                    wynik1 = wynik2 = 0;
                    roundText.setString("Round: 1");
                }
                else {
                    window.close();
                    break;
                }
            }
        }
    }
    return 0;
}
