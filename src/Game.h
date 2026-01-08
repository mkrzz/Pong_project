
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Ball.h"
#include "Bat.h"

class Game
{

 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void resetBall();
  void render();
  void keyPressed(sf::Event event);

 private:

  sf::RenderWindow& window;

  sf::Font font;
  sf::Text play_text;
  sf::Text quit_text;
  sf::Text title_text;
  sf::Text start_message;
  sf::Text player_1_score_text;
  sf::Text player_2_score_text;
  sf::Text game_over_text;
  sf::Text quit_anytime_text;

  Ball ball;
  Bat batLeft;
  Bat batRight;

  sf::Clock reset_clock;
  sf::Time reset_delay = sf::seconds(1.0f);

  int player_1_score   = 0;
  int player_2_score   = 0;

  float speed = 400;
   
  bool in_menu;
  bool play_selected = true;
  bool is_running; 
  bool game_over = false;
  

  Vector velocity;
};

#endif 
