#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            switch(event.type){
            	case sf::Event::KeyPressed:
            	std::cout<<"pressed"<<std::endl;
            	break;
            	case sf::Event::KeyReleased:
            	std::cout<<"released"<<std::endl;
            	break;
            	default:
            	break;
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
