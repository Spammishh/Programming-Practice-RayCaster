#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#define map_h 24
#define map_w 24

std::string ConvertToString(int number) {
  std::ostringstream buff;
  buff << number;
  return buff.str();
}

int level[map_w][map_h] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// WINDOW PROCESS
int main() {

  int h = 576, w = 1024;
  double start_x = 22, start_y = 12; // where the player is
  double dir_x = -1, dir_y = 0;
  double plane_x = 0, plane_y = 0.66;

  double time = 0;
  double oldTime = 0; // set framerate
                      //
  sf::RenderWindow window(sf::VideoMode(w, h), "RAYCAST");

  window.setFramerateLimit(60);
  sf::Clock clock = sf::Clock();
  sf::Time fps;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if ((event.type == sf::Event::KeyPressed) &&
          (event.key.code == sf::Keyboard::Escape))
        window.close();
    }
    window.clear();

    for (int r = 0; r < w; r++) {
      double camera_x = 2 * r / double(w) - 1;
      double raypos_x = start_x;
      double raypos_y = start_y;
      double raydir_x = dir_x + plane_x * camera_x;
      double raydir_y = dir_y + plane_y * camera_x;

      int mapx = int(raypos_x);
      int mapy = int(raypos_y);

      double sideDist_x;
      double sideDist_y;

      double deltaDist_x = (raydir_x == 0) ? INFINITY : std::abs(1 / raydir_x);
      double deltaDist_y = (raydir_y == 0) ? INFINITY : std::abs(1 / raydir_y);
      double perpWallDist;

      int step_x;
      int step_y;

      int hit = 0;
      int side;

      if (raydir_x < 0) {
        step_x = -1;
        sideDist_x = (raypos_x - mapx) * deltaDist_x;
      } else {
        step_x = 1;
        sideDist_x = (mapx + 1.0 - raypos_x) * deltaDist_x;
      }
      if (raydir_y < 0) {
        step_y = -1;
        sideDist_y = (start_y - mapy) * deltaDist_y;
      }

      else {
        step_y = 1;
        sideDist_y = (mapy + 1.0 - raypos_y) * deltaDist_y;
      }
      // perform DDA algorithm
      while (hit == 0) { // Jump to next square or in x or y direction
        if (sideDist_x < sideDist_y) {
          sideDist_x += deltaDist_x;
          mapx += step_x;
          side = 0;
        } else {
          sideDist_y += deltaDist_y;
          mapy += step_y;
          side = 1;

        } // check if ray hit wall
        if (level[mapx][mapy] > 0)
          hit = 1;
      }
      // calculate highest and lowest pixels to fill in as columns
      if (side == 0)
        perpWallDist = (sideDist_x - deltaDist_x);
      else
        perpWallDist = (sideDist_y - deltaDist_y);
      int lineHeight = abs(int(h / perpWallDist));

      int drawStart = -lineHeight / 2 + h / 2;
      if (drawStart < 0)
        drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if (drawEnd >= h)
        drawEnd = h - 1;
      sf::Color color;
      switch (level[mapx][mapy]) {
      case 1:
        color = sf::Color::Red;
        break;
      case 2:
        color = sf::Color::Green;
        break;
      case 3:
        color = sf::Color::Blue;
        break;
      case 4:
        color = sf::Color::White;
        break;
      default:
        color = sf::Color::Yellow;
        break;
      }
      if (side == 1) {
        color = sf::Color(color.r / 2, color.g / 2, color.b / 2);
      }

      sf::Vertex line[2] = {sf::Vertex(sf::Vector2f(r, drawStart), color),
                            sf::Vertex(sf::Vector2f(r, drawEnd), color)};
      window.draw(line, 2, sf::Lines);
    }

    fps = clock.getElapsedTime();
    float frametime = 1000000 / fps.asMicroseconds();
    clock.restart();

    double movespeed = fps.asSeconds() * 5.0; // squares/second
    double rotspeed = fps.asSeconds() * 3.0;  // radians per second
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      // both camera direction and camera plane must be rotated
      double oldDirX = dir_x;
      dir_x = dir_x * cos(rotspeed) - dir_y * sin(rotspeed);
      dir_y = oldDirX * sin(rotspeed) + dir_y * cos(rotspeed);
      double oldPlaneX = plane_x;
      plane_x = plane_x * cos(rotspeed) - plane_y * sin(rotspeed);
      plane_y = oldPlaneX * sin(rotspeed) + plane_y * cos(rotspeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      // both camera direction and camera plane must be rotated
      double oldDirX = dir_x;
      dir_x = dir_x * cos(-rotspeed) - dir_y * sin(-rotspeed);
      dir_y = oldDirX * sin(-rotspeed) + dir_y * cos(-rotspeed);
      double oldPlaneX = plane_x;
      plane_x = plane_x * cos(-rotspeed) - plane_y * sin(-rotspeed);
      plane_y = oldPlaneX * sin(-rotspeed) + plane_y * cos(-rotspeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      if (level[int(start_x + dir_x * movespeed)][int(start_y)] == false)
        start_x += dir_x * movespeed;
      if (level[int(start_x)][int(start_y + dir_y * movespeed)] == false)
        start_y += dir_y * movespeed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      if (level[int(start_x - dir_x * movespeed)][int(start_y)] == false)
        start_x -= dir_x * movespeed;
      if (level[int(start_x)][int(start_y - dir_y * movespeed)] == false)
        start_y -= dir_y * movespeed;
    }

    window.display();
    window.clear();
  }

  return EXIT_SUCCESS;
}
