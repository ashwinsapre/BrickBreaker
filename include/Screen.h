// Screen.h

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen {
public:
    Screen();
    Screen(const std::string& p, const std::string& s, int psize, int ssize, const sf::Color& pcolor, const sf::Color& scolor, const sf::Vector2f& ppos, const sf::Vector2f& spos);

    void setPrimaryText(const std::string& text);
    void setSecondaryText(const std::string& text);
    void setPrimaryTextColor(const sf::Color& color);
    void setSecondaryTextColor(const sf::Color& color);
    void setPrimaryTextPosition(const sf::Vector2f& position);
    void setSecondaryTextPosition(const sf::Vector2f& position);
    void setPrimaryTextSize(unsigned int size);
    void setSecondaryTextSize(unsigned int size);
    void setFont(const std::string& fontPath);

    void draw(sf::RenderWindow& window);

private:
    sf::Text primaryText;
    sf::Text secondaryText;
    sf::Font font;
};

#endif // SCREEN_H
