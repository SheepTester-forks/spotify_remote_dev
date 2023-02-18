<!------------------------------------------ TITLE BLOCK --------------------------------------------------------------->
<h1 align="center"> Spotify Remote </h1>


<!------------------------------------------ TABLE OF CONTENTS ---------------------------------------------------------->
<details open="open">
  <summary><h2 style="display: inline-block"> Table of Contents </h2></summary>
  <ol>
    <li>
      <a href="#about-the-project"> About The Project </a>
      <ul>
        <li><a href="#technologies"> Technologies </a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started"> Getting Started </a>
      <ul>
        <li><a href="#prerequisites"> Prerequisites </a></li>
        <li><a href="#installation"> Installation </a></li>
      </ul>
    </li>
    <li><a href="#usage"> Usage </a></li>
  </ol>
</details>


<!------------------------------------------ ABOUT THE PROJECT ---------------------------------------------------------->
## About The Project
See our [Project Charter](https://docs.google.com/document/d/1Ot3jMBS96P4pptXHAh-5pquK0DeCbHlZKEKW69NrF_Q/edit)

This is an introductory project/workshop on IoT hardware where students can create a WiFi-enabled remote for Spotify. By the end of the day, students will gain a broader understanding of embedded development and API services.

### Technologies
* [ESP8266](https://www.espressif.com/en/products/socs/esp8266)
* [PlatformIO](https://platformio.org/)
* [Spotify API](https://developer.spotify.com/documentation/web-api/)


<!------------------------------------------ GETTING STARTED ---------------------------------------------------------->
## Getting Started
To get a local copy up and running follow these steps.

### Prerequisites
[Visual Studio Code](https://code.visualstudio.com/download):
  * Download Visual Studio Code on their website. VSCode is a powerful code editor that offers rich integrations, error checking, and code completion. It supports hundreds of languages, including Arduino C/C++ which we will heavily use for this project.
  
  * Requirements:
    * Operating systems: macOS, Linux, and Windows
    * At least 300 MB of space

[Python](https://www.python.org/downloads/):
  * Download the latest version of Python on their website. We will not be programming anything in Python, but PlatformIO, which we will discuss later below, requires Python for it to be installed.

  * Requirements:
    * At least 100 MB of space

[PlatformIO](https://platformio.org/) (Visual Studio Code Extension):
  * Open VSCode and head to the ‘Extensions’ menu. Search for ‘PlatformIO’ and install it. PlatformIO is a neat integration for embedded development, and we will be using it to program/upload code to our IoT boards. Unlike the Arduino IDE that we are traditionally familiar with, PlatformIO offers convenient features, such as port detection, larger boards selection, pre-loaded libraries, and all other features offered already in VSCode.

  * Requirements:
    * Visual Studio Code installed
    * Python 3.x or the latest version

Additionally see here for [Prerequisites](https://docs.google.com/document/d/1ayXbvKg1j7JOZCThSJutbCrCwtTU6byMtOS7RLs7JzM/edit)

### Installation
  1. Clone the repo:
  ```
    git clone https://github.com/Project-in-a-Box-JSOE/spotify_remote_dev
  ```
  2. Open the repo as a PlatformIO project

<!------------------------------------------ USAGE EXAMPLES -------------------------------------------------------------->
## Usage
Follow along through our [workshop slides](https://docs.google.com/presentation/d/1-BmdbKempxMLJTgQfdcMZBaUyBUgbPFwDdZr1YG0QO4/edit?usp=sharing)


<!------------------------------------------ HIGH LEVEL ARCHITECTURE ----------------------------------------------------->
## High Level Architecture
<p align="center">
  <img src="high_level_arch.png" />
</p>