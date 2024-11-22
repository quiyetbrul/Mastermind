# Mastermind Game

![Mastermind Main Menu](/assets/main_menu.png)

## Table of Contents

- [Introduction](#introduction)
- [What I Used](#what-i-used)
- [Setup and Run](#setup-and-run)
- [Features](#features)
- [Development and Design](#development-and-design)

## Introduction

This Mastermind clone is a console-based puzzle game where players attempt to decipher a secret code within a limited number of guesses. The game tests and hones deductive reasoning skills, making it both a mental workout and a fun pastime.

## What I Used

### Operating System

- macOS Sequoia 15.1

### Dependencies

- [CMake](https://cmake.org/)
- [cURL](https://curl.se/libcurl/c/)
- [SQLite](https://www.sqlite.org/index.html)
- [SQLiteCPP](https://github.com/SRombauts/SQLiteCpp)
- [NCurses](https://invisible-island.net/ncurses/)
- [Nlohmann JSON](https://github.com/nlohmann/json)

### Others

- [VS Code](https://code.visualstudio.com/)
- [Docker](https://www.docker.com/)
- [SonarCloud](https://sonarcloud.io/)
- [Doxygen](https://www.doxygen.nl/index.html)
- [ASCIIDecorator](https://marketplace.visualstudio.com/items?itemName=helixquar.asciidecorator)
- [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [Random Integer Generator](https://www.random.org/clients/http/api/)

## Setup and Run

### Using Repository

- Ensure all dependencies are installed.

- Clone the repository.

- Run the following script:

```bash
sh makerun.sh
```

- If running the script fails, run the following commands:

  <ul>
    <li>
      Create a build directory:
    </li>
    <pre><code>cmake -S . -B build/</code></pre>
    <li>
      Build the project:
    </li>
    <pre><code>cd build && make</code></pre>
    <li>
    Run the project:
    </li>
    <pre><code>./Mastermind</code></pre>
  </ul>

### Using Docker

- Ensure Docker is installed, and you are logged in.
- Pull the Docker image using the command.

```bash
docker pull quiyetbrul/mastermind-game:latest
```

- Run the Docker container using the command.

```bash
# For temporary data persistent game
docker run --rm -it -e TERM=xterm-256color quiyetbrul/mastermind-game:latest
# For data persistent game using volume
docker run --rm -it -v $(pwd)/data:/app/build/src/data -e TERM=xterm-256color quiyetbrul/mastermind-game:latest
```

## Features

- Single-player mode.
- AI Codebreaker using Donald Knuth's 5-guess algorithm.
- Configurable difficulty levels.
- Codebreaker hints.
- Top 10 leaderboard.
- Save/load game functionality.
- Random number generation via Random API using cURL.
- Logging system.
- Input validation.
- Interactive terminal UI using ncurses.

### Activity Diagram

![Activity Diagram](/assets/activity_diagram.png)

## Development and Design

I began by creating an MVP with a basic main menu for starting or exiting the game, featuring a singleton logger for event tracking and initial input validation. Random number generation initially relied on pseudo-random methods but later used an external API integrated via cURL.

To enhance structure with OOP principles, I added a GameState class, an abstract Player class, and a SinglePlayer class, enabling the integration of Donald Knuth's 5-guess algorithm for an AI Codebreaker using a minimax strategy to efficiently solve the code.

Additional features included a Codebreaker Hint system and customizable difficulty settings for improved player engagement. I implemented a leaderboard to track top scores and game progress persistence using SQLiteCpp, employing an MVC architecture to ensure clean separation of concerns.

Finally, I utilized ncurses to create a robust terminal-based UI, enhancing the interactive console experience for players.

## Links

- [Using cURL with C++](https://terminalroot.com/using-curl-with-cpp/)
- [Mastermind Game](https://en.wikipedia.org/wiki/Mastermind_(board_game))
- [MiniMax Algorithm](https://en.wikipedia.org/wiki/Minimax)
- [RubyConf 2018 - Beating Mastermind: Winning with the help of Donald Knuth by Adam Forsyth](https://www.youtube.com/watch?v=Okm_t5T1PiA&ab_channel=Confreaks)
