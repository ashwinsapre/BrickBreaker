#include "Screen.h"

Screen::Screen() {
    // Initialize default values or load default font, etc.
    font.loadFromFile("../assets/arial.ttf"); // Change the font file as needed
    primaryText.setFont(font);
    secondaryText.setFont(font);
}

Screen::Screen(const std::string& p, const std::string& s, int psize, int ssize, const sf::Color& pcolor, const sf::Color& scolor, const sf::Vector2f& ppos, const sf::Vector2f& spos){
    font.loadFromFile("../assets/arial.ttf"); // Change the font file as needed
    primaryText.setFont(font);
    secondaryText.setFont(font);
    setPrimaryText(p);
    setSecondaryText(s);
    setPrimaryTextColor(pcolor);
    setSecondaryTextColor(scolor);
    setPrimaryTextSize(psize);
    setSecondaryTextSize(ssize);
    setPrimaryTextPosition(ppos);
    setSecondaryTextPosition(spos);
}

void Screen::setPrimaryText(const std::string& text) {
    primaryText.setString(text);
}

void Screen::setSecondaryText(const std::string& text) {
    secondaryText.setString(text);
}

void Screen::setPrimaryTextColor(const sf::Color& color) {
    primaryText.setFillColor(color);
}

void Screen::setSecondaryTextColor(const sf::Color& color) {
    secondaryText.setFillColor(color);
}

void Screen::setPrimaryTextPosition(const sf::Vector2f& position) {
    primaryText.setPosition(position);
}

void Screen::setSecondaryTextPosition(const sf::Vector2f& position) {
    secondaryText.setPosition(position);
}

void Screen::setPrimaryTextSize(unsigned int size) {
    primaryText.setCharacterSize(size);
}

void Screen::setSecondaryTextSize(unsigned int size) {
    secondaryText.setCharacterSize(size);
}

void Screen::setFont(const std::string& fontPath) {
    font.loadFromFile(fontPath);
    primaryText.setFont(font);
    secondaryText.setFont(font);
}

void Screen::draw(sf::RenderWindow& window) {
    window.draw(primaryText);
    window.draw(secondaryText);
}
