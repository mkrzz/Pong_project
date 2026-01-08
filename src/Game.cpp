
#include "Game.h"
#include <iostream>
#include "Vector.h"
#include "Ball.h"
#include "Bat.h"


Game::Game(sf::RenderWindow& game_window) :
  window(game_window), is_running(false)//velocity(1.0f, -1.0f)
{
  //starting positions of bats
  batLeft.setPosition(50.0f, 300.0f);
  batRight.setPosition(1050.0f, 300.0f);
  
  //starting position of ball
  ball.setPosition(
    window.getSize().x / 2.0f - ball.getBounds().width / 2.0f,
    window.getSize().y / 2.0f - ball.getBounds().height / 2.0f);

  velocity.normalise();
  srand(time(NULL));
  
}

Game::~Game()
{

}

//when we only want something once
bool Game::init()
{
  in_menu = true;

  if (!font.loadFromFile("../Data/Fonts/DS-DIGI.ttf"))
  {
    std::cout << "Font did not load";
  }

  //quit anytime text 

  quit_anytime_text.setFont(font);
  quit_anytime_text.setString("Press Esc to quit");
  quit_anytime_text.setCharacterSize(20);
  quit_anytime_text.setFillColor(sf::Color::Green);
  quit_anytime_text.setPosition(
    window.getSize().x / 2 - quit_anytime_text.getGlobalBounds().width / 2,
    window.getSize().y - 60);

  //play text 

  play_text.setString("> play <");
  play_text.setFont(font);
  play_text.setCharacterSize(40);
  play_text.setFillColor(sf::Color::Green);
  play_text.setPosition(
    window.getSize().x / static_cast<float>(2) - 150 -
      play_text.getGlobalBounds().width / 2,
    window.getSize().y / static_cast<float>(2) - 70);


  //quit text 

  quit_text.setString("quit");
  quit_text.setFont(font);
  quit_text.setCharacterSize(40);   
  quit_text.setFillColor(sf::Color::Green);
  quit_text.setPosition(
    window.getSize().x / static_cast<float>(2) + 150 -
      quit_text.getGlobalBounds().width / 2,
    window.getSize().y / static_cast<float>(2) - 70);

  //title text 

  title_text.setString("pong");
  title_text.setFont(font);
  title_text.setCharacterSize(50);  
  title_text.setFillColor(sf::Color::Green);
  title_text.setPosition(
    window.getSize().x / static_cast<float>(2) -
      title_text.getGlobalBounds().width / 2,
    180);
  
  //player 1 score text 

  player_1_score_text.setFont(font);
  player_1_score_text.setCharacterSize(30);
  player_1_score_text.setFillColor(sf::Color::Green);
  player_1_score_text.setPosition(10, 10);
  player_1_score_text.setString("0");

  // player 2 score text

  player_2_score_text.setFont(font);
  player_2_score_text.setCharacterSize(30);
  player_2_score_text.setFillColor(sf::Color::Green);
  player_2_score_text.setPosition(1040, 10);
  player_2_score_text.setString("0");
 
  return true;
}

void Game::update(float dt)
{
  if (is_running && !game_over)
  {
    if (reset_clock.getElapsedTime() >= reset_delay)
    {
      // update ball position
      ball.update(dt);
      ball.handleCollisions(window);

      sf::FloatRect ballBounds = ball.getBounds();

      //add 1 score if ball hits sides + reset ball
      if (ballBounds.left <= 0)
      {
        resetBall();
        player_2_score += 1;

        if (player_2_score >= 5)
        {
          game_over = true;
          is_running = false;
        }
      }

      if (ballBounds.left + ballBounds.width >= window.getSize().x)
      {
        resetBall();
        player_1_score += 1;

        if (player_1_score >= 5)
        {
          game_over = true;
          is_running = false;
        }
      }

      //check collision with left bat
      if (ball.getBounds().intersects(batLeft.getBounds()))
      {
        //reverse ball velocity
        ball.setVelocity(-ball.getVelocity().getX(), ball.getVelocity().getY());
      }

      //check collision with right bat
      if (ball.getBounds().intersects(batRight.getBounds()))
      {
        //reverse ball velocity
        ball.setVelocity(-ball.getVelocity().getX(), ball.getVelocity().getY());
      }
    }
  }
  //display score to screen
  player_1_score_text.setString("0" + std::to_string(player_1_score));
  player_2_score_text.setString("0" + std::to_string(player_2_score));
}
  
void Game::resetBall()
{
  //reset ball position to the center
  ball.setPosition(
    window.getSize().x / 2.0f - ball.getBounds().width / 2.0f,
    window.getSize().y / 2.0f - ball.getBounds().height / 2.0f);
 
  reset_clock.restart();
}


void Game::render()
{
    
    if (in_menu)
    {
      window.draw(play_text);
      window.draw(quit_text);
      window.draw(title_text);
    }
    else
    {
        if (!game_over)
        {
          ball.render(window);
          batLeft.render(window);
          batRight.render(window);
          window.draw(player_1_score_text);
          window.draw(player_2_score_text);

          window.draw(quit_anytime_text);

          if (!is_running)
          {
            start_message.setFont(font);
            start_message.setString("Press P to Play");
            start_message.setCharacterSize(30);
            start_message.setFillColor(sf::Color::Green);
            start_message.setPosition(
              window.getSize().x / 2 -
                start_message.getGlobalBounds().width / 2,
              window.getSize().y / 2 -
                start_message.getGlobalBounds().height / 2 - 100);

            window.draw(start_message);
          }
        }
        else
        {
          game_over_text.setFont(font);
          game_over_text.setString(
          player_1_score >= 5 ? "Player 1 Wins\nPlay again...? \nY/N "
                                : "Player 2 Wins\nPlay again...? \nY/N "
                                  );
          game_over_text.setCharacterSize(40);
          game_over_text.setFillColor(sf::Color::Green);
          game_over_text.setPosition(
            window.getSize().x / 2 - game_over_text.getGlobalBounds().width / 2,
            window.getSize().y / 2 -
              game_over_text.getGlobalBounds().height / 2);
          window.draw(game_over_text);
        }
      
      

    }
    
    
    
   
}

//menu options
void Game::keyPressed(sf::Event event)

{

  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close(); //close the game window
  }
  if (game_over)
  {
    

    if (event.key.code == sf::Keyboard::Y)
    {
      player_1_score = 0;
      player_2_score = 0;
      game_over      = false;
      is_running     = true;
      resetBall();
    }
    else if (event.key.code == sf::Keyboard::N)
    {
      window.close();
    }
  }

  else if (event.key.code == sf::Keyboard::P && !is_running)
  {
    is_running = true;
  }

  if (in_menu)
  {
    {
      if (
        (event.key.code == sf::Keyboard::Left) ||
        (event.key.code == sf::Keyboard::Right))
      {
        play_selected = !play_selected;
        if (play_selected)
        {
          play_text.setString("> play <");
          quit_text.setString("quit");
        }
        else
        {
          play_text.setString("play");
          quit_text.setString("> quit <");
        }
      }
      else if (event.key.code == sf::Keyboard::Enter)
      {
        if (play_selected)
        {
          in_menu = false;
        }
        else
        {
          window.close();
        }
      }
    }
  }
  
  const float batSpeed = 30.0f;

  //control both bats using keybinds
  if (event.key.code == sf::Keyboard::W)
  {
    batLeft.moveUp(batSpeed); 
  }
  else if (event.key.code == sf::Keyboard::S)
  {
    batLeft.moveDown(batSpeed, window.getSize().y); 
  }

  if (event.key.code == sf::Keyboard::Up)
  {
    batRight.moveUp(batSpeed);
  }
  else if (event.key.code == sf::Keyboard::Down)
  {
    batRight.moveDown(batSpeed, window.getSize().y);
  }
}

  


