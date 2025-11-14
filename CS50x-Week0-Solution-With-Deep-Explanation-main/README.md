# CS50x-Week0-my-solution-and-notes
### ⭐️ **Star this repository! It really motivates me to make better explanations and produce more work!!** ⭐️

# Introduction
Space Adventures is an interactive Scratch game where players control a spaceship, avoiding obstacles and collecting points to achieve high scores. Experience thrilling gameplay with intuitive controls and dynamic challenges in this engaging space-themed adventure. This game is hard and consists of 2 phases, will you try to beat it?

## Features
- **Interactive Gameplay:** Players control a spaceship navigating through space using intuitive controls.
- **Obstacle Avoidance:** Players must avoid various obstacles to survive, adding dynamic challenges to the game.
- **Point Collection:** Points are collected by destroying obstacles, encouraging skillful play.
- **Score Tracking:** The game keeps track of the highest score achieved, motivating players to beat their previous records.
- **High-Quality Musical Accompaniment:** Various musical compositions enhance the gameplay experience, triggered by special events.
- **Enemy Spaceship:** In the second stage, a special enemy spaceship appears and glides towards the player, adding an additional layer of challenge.
- **Super Fire:** Every 10 shots, a super fire is launched that can destroy all objects in its path quickly and efficiently.
  
## How to Play
1. **Start the Game:** Open the Space Adventures project in Scratch.
2. **Controls:** Use the arrow keys to move the spaceship up, down, left, and right.
3. **Objective:** Avoid obstacles and collect points to achieve the highest score.
4. **End of Game:** The game ends when the spaceship crashes into an obstacle. The final score is displayed.
5. **How to win** To win the game 100 points should be obtained.

## Installation
To play Space Adventures, follow these steps:
1. **Download Scratch:** If you haven't already, download and install Scratch from [Scratch's official website](https://scratch.mit.edu/download).
2. **Open the Project:** Download the Space Adventures project file (`Space Adventures.sb3`) and open it in Scratch.

## Gameplay Mechanics
- **Spaceship Movement:** Use the arrow keys to move the spaceship up, down, left, and right.
- **Obstacle Generation:** Obstacles appear randomly with varying sizes and move towards the spaceship, requiring quick reflexes.
- **Enemy Spaceship:** The enemy spaceship appears in the second stage and steadily moves towards the player's spaceship, forcing evasive maneuvers.
- **Super Fire:** After every 10 shots, a powerful super fire is activated, passing through and destroying all obstacles rapidly.
- **Point System:** Points are awarded for each obstacle destroyed and for the distance traveled, encouraging players to stay alive as long as possible.

## Project Structure

### Stage
- **Role:** Manages the overall game environment, including backgrounds and game states. It also tracks the score and handles game start and end events. The stage controls the transitions between different phases of the game.
- **Costumes:** The stage has different costumes to represent various backgrounds and game states. These may include:
  - **Background 1:** The initial space background for the first phase of the game.
  - **Background 2:** A different background or a more intense space scene for the second phase when the enemy spaceship appears.

### Sprite1 (Spaceship)
- **Role:** The player's controllable spaceship. Handles movement using arrow keys and shooting projectiles to destroy obstacles. It is the primary element the player interacts with.

### Rocks
- **Role:** Represents the obstacles in the game. These rocks appear randomly and move towards the player's spaceship. The player must avoid or destroy these rocks to survive.

### Enemy Spaceship
- **Role:** A special enemy that appears in the second phase of the game. It steadily moves towards the player's spaceship, adding an additional layer of challenge that the player must evade.

### Letter Sprites
- **Role:** Display messages indicating game status, such as win/loss, game over, or instructional text. These sprites are shown at various points during the game.
- **Costumes:** Each letter sprite has a costume that displays a specific letter or message component. For example:
  - **Y, O, U, W, O, N:** Sprites that spell out "YOU WON" when the winning condition is met.
  - **G, A, M, E, O, V, E, R:** Sprites that spell out "GAME OVER" at the end of the game.
 
### Button1 (Bullets)
- **Role:** Represents the bullets fired by the player's spaceship. These bullets are used to destroy obstacles (rocks) and enemy spaceships. The `Button1` sprite handles the shooting mechanics, including bullet movement and collision detection.

### Super Fire
- **Role:** A powerful shot that the player's spaceship can fire every 10 shots. It passes through and destroys all obstacles in its path, providing a temporary advantage.

### Game Phases
- **Phase 1:** The game starts with the player controlling the spaceship and avoiding rocks that appear randomly. The main objective is to survive and collect points by destroying obstacles.
- **Phase 2:** After a certain score threshold is reached, the game transitions to the second phase. In this phase, the enemy spaceship appears and starts gliding towards the player's spaceship. The player must continue avoiding rocks while also evading the enemy spaceship, increasing the difficulty of the game.

## Technical Details

### Techniques Used
- **Event-Driven Programming:** The game heavily relies on event-driven programming, using Scratch's broadcasting and event listening features to manage game states and transitions.
- **Randomization:** Random functions are used to generate obstacles at random positions and with random sizes to ensure the game remains unpredictable and challenging.
- **Collision Detection:** Scratch's built-in collision detection is used to manage interactions between the spaceship, bullets, and obstacles.
- **State Management:** Variables are used to keep track of game states such as score, game phase, and bullet count.
- **Message Broadcasting:** Scratch's message broadcasting system is used to trigger changes between game phases and to handle the appearance of messages like "Game Over" and "You Won".

### Implementation of Mechanics

#### Spaceship Movement
The spaceship is controlled using the arrow keys. The scripts attached to the spaceship sprite listen for key press events and move the spaceship accordingly:
- **Up Arrow:** Moves the spaceship up.
- **Down Arrow:** Moves the spaceship down.
- **Left Arrow:** Moves the spaceship left.
- **Right Arrow:** Moves the spaceship right.

#### Shooting Bullets
The player can shoot bullets by pressing the spacebar. Each time the spacebar is pressed, a bullet sprite (`Button1`) is cloned and set to move forward from the spaceship's position:
- **Bullet Creation:** A new clone of the `Button1` sprite is created.
- **Bullet Movement:** The cloned bullet moves forward until it collides with an obstacle or goes off-screen.
- **Collision Handling:** When a bullet collides with an obstacle, both the bullet and the obstacle are destroyed, and the player earns points.

#### Super Fire Mechanism
Every 10 shots, a super fire is activated which destroys all obstacles in its path:
- **Super Fire Activation:** A counter keeps track of the number of bullets fired. When it reaches 10, a super fire is triggered.
- **Super Fire Behavior:** The super fire moves quickly across the screen, destroying any obstacles it touches.

#### Obstacle Generation
Obstacles (rocks) are generated at random intervals and positions:
- **Random Positioning:** Obstacles appear at random positions on the right edge of the screen.
- **Random Sizes:** Obstacles are assigned random sizes to add variety and difficulty.
- **Movement:** Obstacles move leftward towards the spaceship, increasing the challenge for the player.

#### Enemy Spaceship
In the second phase of the game, an enemy spaceship appears and glides towards the player’s spaceship:
- **Appearance Trigger:** The enemy spaceship appears once a certain score threshold is reached.
- **Movement:** The enemy spaceship steadily moves towards the player’s spaceship, forcing the player to evade it while still avoiding obstacles.

## Explanation of the code

### Sound, end-game events
<table>
  <tr>
    <td><img src="images/broadcast_events.png" alt="Sound Events" width="1500" height="600"></td>
    <td>
      <ol>
        <li><strong>Event: "Congratulations, you won!"</strong>
          <ul>
            <li><strong>Actions:</strong> Stops all current sounds. Plays the "Dubstep" sound until it is completed.</li>
            <li><strong>Purpose:</strong> To provide a celebratory audio cue when the player wins the game.</li>
          </ul>
        </li>
        <li>Event: "Game Over"
          <ul>
            <li>Actions:
              <ul>
                <li>Stops all current sounds.</li>
                <li>Plays the "Cave" sound until it is completed.</li>
              </ul>
            </li>
            <li>Purpose: To signal to the player that the game has ended with a distinct sound.</li>
          </ul>
        </li>
        <li>Event: "SECOND PHASE"
          <ul>
            <li>Actions:
              <ul>
                <li>Plays the "Alert" sound until it is completed.</li>
                <li>Plays the "Alien Creak1" sound until it is completed.</li>
              </ul>
            </li>
            <li>Purpose: To indicate the start of a new phase in the game with a combination of alerting and eerie sounds.</li>
          </ul>
        </li>
        <li>Event: When the green flag is clicked
          <ul>
            <li>Actions:
              <ul>
                <li>Repeatedly plays the "Space Ambience" sound.</li>
              </ul>
            </li>
            <li>Purpose: To provide continuous background ambiance, immersing the player in a space-themed environment throughout the game. The syntax is simple, when the signal about event is gone, other actions will be played. Something like If condition is met, do this. And songs will start playing. Forever loop means, it will always launch the music another time, when it meets it's end.</li>
          </ul>
        </li>
        <p>The syntax is simple, when the sygnal about event will gone, other actions will be played. Something like If condition is met, do this. And songs will start playing. Forever loop means, it will always launch the music another time, when it meets it's end.</p>
      </ol>
    </td>
  </tr>
</table>

### Enemy Spaceship Base
<table>
  <tr>
    <td><img src="images/enemy_spaceship_base.png" alt="Enemy Spaceship Base" width="700" height="300""></td>
    <td>
      <p>This image shows the setup process for initializing the enemy spaceship in the game. The blocks are designed to position the spaceship correctly and hide it at the start of the game. Here's what each block does:</p>
      <ol>
        <li><strong>Event: When the green flag is clicked</strong>
          <ul>
            <li><strong>Purpose:</strong> This block is triggered when the game starts (or is restarted). It ensures that the following actions happen right at the beginning of the game.</li>
          </ul>
        </li>
        <li><strong>Block: Go to x: 180 y: 150</strong>
          <ul>
            <li><strong>Action:</strong> This block moves the enemy spaceship to a specific position on the screen, with coordinates (180, 150).</li>
            <li><strong>Purpose:</strong> Setting the initial position of the spaceship so that it starts from a predefined location, ensuring consistent gameplay each time the game begins.</li>
          </ul>
        </li>
        <li><strong>Block: Hide</strong>
          <ul>
            <li><strong>Action:</strong> This block makes the enemy spaceship invisible.</li>
            <li><strong>Purpose:</strong> Initially hiding the spaceship until it's needed in the game. This can be useful for setting up the game environment without showing all elements right away, creating a more controlled and engaging experience for the player.</li>
          </ul>
        </li>
      </ol>
      <p>Together, these blocks ensure that the enemy spaceship is placed correctly and hidden when the game starts, ready to be revealed at the appropriate moment in the gameplay.</p>
    </td>
  </tr>
</table>

### Enemy Spaceship Movements
<table>
  <tr>
    <td><img src="images/enemy_spaceship_movements.png" alt="Enemy Spaceship Movements" width="800" height="300"></td>
    <td>
      <p>This image shows how the enemy spaceship behaves during the second phase of the game. Each block in the script plays a crucial role in creating a dynamic and engaging challenge for the player. Here's what each part does:</p>
      <ol>
        <li><strong>Event: When I receive "SECOND PHASE"</strong>
          <ul>
            <li><strong>Purpose:</strong> This block is triggered when the game reaches the second phase. It ensures that the following actions start specifically at this stage of the game.</li>
          </ul>
        </li>
        <li><strong>Block: Show</strong>
          <ul>
            <li><strong>Action:</strong> This block makes the enemy spaceship visible.</li>
            <li><strong>Purpose:</strong> To reveal the enemy spaceship at the beginning of the second phase, adding an element of surprise and increasing the difficulty.</li>
          </ul>
        </li>
        <li><strong>Repeat Until: touching "Sprite1"</strong>
          <ul>
            <li><strong>Action:</strong> This block repeats the enclosed actions until the enemy spaceship touches "Sprite1" (which could be the player's spaceship or another target).</li>
            <li><strong>Purpose:</strong> To keep the enemy spaceship moving towards its target until it makes contact, creating a continuous challenge for the player.</li>
          </ul>
        </li>
        <li><strong>Block: Glide 8 secs to "Sprite1"</strong>
          <ul>
            <li><strong>Action:</strong> This block moves the enemy spaceship towards "Sprite1" over a period of 8 seconds.</li>
            <li><strong>Purpose:</strong> To create a smooth, gliding motion towards the target, making the enemy's movement predictable yet challenging to avoid.</li>
          </ul>
        </li>
        <li><strong>Block: Broadcast "Game Over"</strong>
          <ul>
            <li><strong>Action:</strong> This block sends a "Game Over" message when the enemy spaceship touches "Sprite1".</li>
            <li><strong>Purpose:</strong> To trigger the end of the game, indicating that the player has been caught by the enemy spaceship.</li>
          </ul>
        </li>
        <li><strong>Block: Stop all</strong>
          <ul>
            <li><strong>Action:</strong> This block stops all scripts in the game.</li>
            <li><strong>Purpose:</strong> To halt all game activities immediately after the game is over, ensuring a clear and definitive end to the game session.</li>
          </ul>
        </li>
      </ol>
      <p>This script ensures that the enemy spaceship appears and actively targets the player during the second phase, creating a tense and exciting gameplay experience.</p>
    </td>
  </tr>
</table>

### Letters Visibility 
<table>
  <tr>
    <td><img src="images/letters_base.png" alt="Letters Visibility" width="1200" height="200"></td>
    <td>
      <p>This image shows two separate scripts that control the visibility of letters in the game, both when the game starts and when it ends. Here's what each block does:</p>
      <ol>
        <li><strong>Event: When I receive "Game Over"</strong>
          <ul>
            <li><strong>Action:</strong> This block is triggered when the game sends a "Game Over" message.</li>
            <li><strong>Block: Show</strong>
              <ul>
                <li><strong>Action:</strong> Makes the letters visible.</li>
                <li><strong>Purpose:</strong> To display the letters on the screen when the game ends, possibly to spell out a "Game Over" message for the player.</li>
              </ul>
            </li>
          </ul>
        </li>
        <li><strong>Event: When the green flag is clicked</strong>
          <ul>
            <li><strong>Action:</strong> This block is triggered when the game starts (or is restarted).</li>
            <li><strong>Block: Hide</strong>
              <ul>
                <li><strong>Action:</strong> Hides the letters.</li>
                <li><strong>Purpose:</strong> To ensure that the letters are not visible when the game starts, keeping the screen clear until they are needed (like when the game ends).</li>
              </ul>
            </li>
          </ul>
        </li>
      </ol>
      <p>These scripts manage the visibility of the letters in the game, ensuring they only appear at the appropriate times to communicate the game status effectively to the player.</p>
    </td>
  </tr>
</table>

### Spaceship Movements
<table>
  <tr>
    <td><img src="images/move_spaceship.png" alt="Spaceship Movement" width="1000" height="500"></td>
    <td>
      <p>This image shows a script that allows the player to control the movement of a spaceship using the keyboard. Each block checks for a specific key press and moves the spaceship accordingly. Here's how it works:</p>
      <ol>
        <li><strong>Event: When the green flag is clicked</strong>
          <ul>
            <li><strong>Action:</strong> This block is triggered when the game starts (or is restarted).</li>
            <li><strong>Purpose:</strong> To initialize the control script, making sure the spaceship can be moved as soon as the game begins.</li>
          </ul>
        </li>
        <li><strong>Forever Loop</strong>
          <ul>
            <li><strong>Action:</strong> This block continuously checks for key presses.</li>
            <li><strong>Purpose:</strong> To allow continuous movement of the spaceship as long as the game is running.</li>
          </ul>
        </li>
        <li><strong>If key "w" pressed?</strong>
          <ul>
            <li><strong>Action:</strong> Checks if the "w" key is pressed.</li>
            <li><strong>Block: Change y by 5</strong>
              <ul>
                <li><strong>Action:</strong> Moves the spaceship up by 5 units.</li>
                <li><strong>Purpose:</strong> To move the spaceship up when the "w" key is pressed, simulating forward movement.</li>
              </ul>
            </li>
          </ul>
        </li>
        <li><strong>If key "a" pressed?</strong>
          <ul>
            <li><strong>Action:</strong> Checks if the "a" key is pressed.</li>
            <li><strong>Block: Change x by -5</strong>
              <ul>
                <li><strong>Action:</strong> Moves the spaceship left by 5 units.</li>
                <li><strong>Purpose:</strong> To move the spaceship left when the "a" key is pressed, simulating leftward movement.</li>
              </ul>
            </li>
          </ul>
        </li>
        <li><strong>If key "s" pressed?</strong>
          <ul>
            <li><strong>Action:</strong> Checks if the "s" key is pressed.</li>
            <li><strong>Block: Change y by -5</strong>
              <ul>
                <li><strong>Action:</strong> Moves the spaceship down by 5 units.</li>
                <li><strong>Purpose:</strong> To move the spaceship down when the "s" key is pressed, simulating backward movement.</li>
              </ul>
            </li>
          </ul>
        </li>
        <li><strong>If key "d" pressed?</strong>
          <ul>
            <li><strong>Action:</strong> Checks if the "d" key is pressed.</li>
            <li><strong>Block: Change x by 5</strong>
              <ul>
                <li><strong>Action:</strong> Moves the spaceship right by 5 units.</li>
                <li><strong>Purpose:</strong> To move the spaceship right when the "d" key is pressed, simulating rightward movement.</li>
              </ul>
            </li>
          </ul>
        </li>
      </ol>
      <p>This script provides basic but effective keyboard controls for moving the spaceship in four directions, enhancing the player's ability to navigate the game environment.</p>
    </td>
  </tr>
</table>

### Rocks Function
<table>
  <tr>
    <td><img src="images/rocks_function.png" alt="Rocks Function" width="1800" height="500"></td>
    <td>
      <p>This image shows a custom function called "rocks" that manages the behavior of rocks in the game. This function handles their movement, interactions with the edges of the screen, and interactions with buttons. Here's a breakdown of what each part does:</p>
      <ol>
        <li><strong>Define "rocks"</strong>
          <ul>
            <li><strong>Purpose:</strong> This block defines a custom function named "rocks." The actions within this function can be reused whenever this function is called in the game.</li>
          </ul>
        </li>
        <li><strong>If touching edge?</strong>
          <ul>
            <li><strong>Action:</strong> Checks if a rock is touching the edge of the screen.</li>
            <li><strong>Block: Go to x: (pick random -220 to 220) y: 150</strong>
              <ul>
                <li><strong>Action:</strong> Moves the rock to a random horizontal position at the top of the screen.</li>
                <li><strong>Purpose:</strong> To reset the rock's position when it touches the edge, making it appear at the top again to fall down.</li>
              </ul>
            </li>
          </ul>
        </li>
        <li><strong>If touching Button2 or touching Button3?</strong>
          <ul>
            <li><strong>Action:</strong> Checks if a rock is touching either Button2 or Button3.</li>
            <li><strong>Block: Go to x: (pick random -220 to 220) y: 150</strong>
              <ul>
                <li><strong>Action:</strong> Moves the rock to a random horizontal position at the top of the screen.</li>
                <li><strong>Purpose:</strong> To reset the rock's position when it touches a button, making it appear at the top again to fall down.</li>
              </ul>
            </li>
          </ul>
        </li>
        <li><strong>Set pitch effect to (pick random 1 to 100)</strong>
          <ul>
            <li><strong>Action:</strong> Changes the pitch effect to a random value between 1 and 100.</li>
            <li><strong>Purpose:</strong> To create a variety of sound effects when the rock interacts with a button, adding auditory interest to the game.</li>
          </ul>
        </li>
        <li><strong>Start sound "pop"</strong>
          <ul>
            <li><strong>Action:</strong> Plays the "pop" sound.</li>
            <li><strong>Purpose:</strong> To provide immediate audio feedback when the rock touches a button, enhancing the player's experience.</li>
          </ul>
        </li>
        <li><strong>Change whirl effect by 25</strong>
          <ul>
            <li><strong>Action:</strong> Applies a whirl effect to the rock, increasing the effect by 25.</li>
            <li><strong>Purpose:</strong> To visually indicate the interaction, making the game more visually engaging.</li>
          </ul>
        </li>
        <li><strong>Change score by 1</strong>
          <ul>
            <li><strong>Action:</strong> Increases the player's score by 1.</li>
            <li><strong>Purpose:</strong> To reward the player for successful interactions with the buttons, providing a sense of achievement and progress.</li>
          </ul>
        </li>
      </ol>
      <p>This function ensures that rocks in the game have dynamic interactions with the screen edges and buttons, providing both visual and auditory feedback while also contributing to the game's scoring system.</p>
    </td>
  </tr>
</table>

### Shooting Mechanism
<table>
  <tr>
    <td><img src="images/spawning_bullets.png" alt="Shooting Mechanism" width="1700" height="700"></td>
    <td>
      <h3>Shooting Mechanism Code Explanation</h3>
      <p>This code block manages the shooting mechanism for a sprite in a game. It defines the behavior when the green flag is clicked and continuously monitors for the space key to be pressed, triggering the shooting action.</p>
      <ul>
        <li><strong>Event: When the green flag is clicked</strong>
          <ul>
            <li><strong>Block: Hide</strong>
              <ul>
                <li><strong>Action:</strong> Initially hides the sprite to manage its visibility during gameplay.</li>
                <li><strong>Purpose:</strong> Ensures the sprite is only visible when it should be active.</li>
              </ul>
            </li>
            <li><strong>Forever Loop</strong>
              <ul>
                <li><strong>Block: Go to Sprite1</strong>
                  <ul>
                    <li><strong>Action:</strong> Positions the sprite at the location of Sprite1.</li>
                    <li><strong>Purpose:</strong> Aligns the shooting sprite with the main sprite for accurate shooting.</li>
                  </ul>
                </li>
                <li><strong>Block: Change y by 5</strong>
                  <ul>
                    <li><strong>Action:</strong> Moves the sprite upward by 5 units.</li>
                    <li><strong>Purpose:</strong> Simulates the upward movement of the bullet when fired.</li>
                  </ul>
                </li>
                <li><strong>Condition: If key space pressed?</strong>
                  <ul>
                    <li><strong>Block: Wait 0.1 seconds</strong>
                      <ul>
                        <li><strong>Action:</strong> Introduces a brief delay between shots.</li>
                        <li><strong>Purpose:</strong> Prevents continuous firing, simulating a realistic shooting rate.</li>
                      </ul>
                    </li>
                    <li><strong>Block: Create clone of myself</strong>
                      <ul>
                        <li><strong>Action:</strong> Creates a clone of the current sprite.</li>
                        <li><strong>Purpose:</strong> Simulates firing a bullet by creating a clone of the sprite.</li>
                      </ul>
                    </li>
                    <li><strong>Block: Play sound Laser2</strong>
                      <ul>
                        <li><strong>Action:</strong> Plays the "Laser2" sound effect to simulate shooting.</li>
                        <li><strong>Purpose:</strong> Provides auditory feedback for the shooting action.</li>
                      </ul>
                    </li>
                    <li><strong>Block: Change firesuntilmegafire by -1</strong>
                      <ul>
                        <li><strong>Action:</strong> Decrements the counter for shots until the mega fire mode is triggered.</li>
                        <li><strong>Purpose:</strong> Tracks the number of shots fired to trigger a special action after a set number of shots.</li>
                      </ul>
                    </li>
                    <li><strong>Condition: If firesuntilmegafire = 0</strong>
                      <ul>
                        <li><strong>Block: Create clone of Button3</strong>
                          <ul>
                            <li><strong>Action:</strong> Creates a clone of Button3, possibly for a special shooting action or power-up.</li>
                            <li><strong>Purpose:</strong> Activates a special power-up or action when the counter reaches zero.</li>
                          </ul>
                        </li>
                        <li><strong>Block: Set shots to 10</strong>
                          <ul>
                            <li><strong>Action:</strong> Resets the counter to 10 for the next cycle of shots.</li>
                            <li><strong>Purpose:</strong> Prepares for the next cycle of tracking shots for the mega fire action.</li>
                          </ul>
                        </li>
                      </ul>
                    </li>
                  </ul>
                </li>
              </ul>
            </li>
          </ul>
        </li>
      </ul>
    </td>
  </tr>
</table>

### Bullet Clone Initialization Code
<table>
  <tr>
    <td><img src="images/start_as_clone.png" alt="Clone Initialization Code" width="1600" height="600"></td>
    <td>
      <h3>Clone Initialization Code Explanation</h3>
      <p>This code block defines the behavior for a sprite when it starts as a clone. It manages the movement, interactions, and events triggered by the clone during the game.</p>
      <ul>
        <li><strong>Event: When I start as a clone</strong>
          <ul>
            <li><strong>Block: Show</strong>
              <ul>
                <li><strong>Action:</strong> Makes the clone visible.</li>
                <li><strong>Purpose:</strong> Ensures the clone can be seen when it is active.</li>
              </ul>
            </li>
            <li><strong>Block: Go to x: (pick random -220 to 220) y: 150</strong>
              <ul>
                <li><strong>Action:</strong> Positions the clone at a random x-coordinate within the range -220 to 220 and at y-coordinate 150.</li>
                <li><strong>Purpose:</strong> Randomizes the initial position of the clone to add variety to its spawning.</li>
              </ul>
            </li>
            <li><strong>Block: Set speed to (pick random -1 to -10)</strong>
              <ul>
                <li><strong>Action:</strong> Sets the speed of the clone to a random value between -1 and -10.</li>
                <li><strong>Purpose:</strong> Adds variability to the speed of the clone, making the game more challenging.</li>
              </ul>
            </li>
            <li><strong>Loop: Repeat until touches sprite1</strong>
                      <ul>
                        <li><strong>Action:</strong> Loop continues until rock will touch the spaceship.</li>
                        <li><strong>Purpose:</strong> To set an action to avoid rocks.</li>
                      </ul>
                    </li>
                    <li><strong>Block: Broadcast game over</strong>
                      <ul>
                        <li><strong>Action:</strong> Sends a broadcast message indicating that the game is over.</li>
                        <li><strong>Purpose:</strong> Provides feedback to the player that the game has ended.</li>
                      </ul>
                    </li>
              <ul>
                <li><strong>Block: Change y by speed</strong>
                  <ul>
                    <li><strong>Action:</strong> Moves the clone downward by the set speed value.</li>
                    <li><strong>Purpose:</strong> Simulates the falling movement of the clone.</li>
                  </ul>
                </li>
                <li><strong>Block: rocks</strong>
                  <ul>
                    <li><strong>Action:</strong> Executes the custom "rocks" function, which defines additional behaviors (not fully shown in this block).</li>
                    <li><strong>Purpose:</strong> Adds complex behaviors to the clone, defined in the "rocks" function.</li>
                  </ul>
                </li>
                <li><strong>Condition: If score = 50</strong>
                  <ul>
                    <li><strong>Block: Switch backdrop to Galaxy</strong>
                      <ul>
                        <li><strong>Action:</strong> Changes the backdrop to "Galaxy".</li>
                        <li><strong>Purpose:</strong> Indicates a transition to a new phase of the game.</li>
                      </ul>
                    </li>
                    <li><strong>Block: Broadcast phase 2</strong>
                      <ul>
                        <li><strong>Action:</strong> Sends a broadcast message to initiate the second phase of the game.</li>
                        <li><strong>Purpose:</strong> Coordinates the transition to the next phase with other sprites and scripts.</li>
                      </ul>
                    </li>
                  </ul>
                </li>
                <li><strong>Condition: If score > 150</strong>
                  <ul>
                    <li><strong>Block: Broadcast you win</strong>
                      <ul>
                        <li><strong>Action:</strong> Sends a broadcast message indicating that the player has won the game.</li>
                        <li><strong>Purpose:</strong> Provides feedback to the player for winning the game.</li>
                      </ul>
                    </li>
                    <li><strong>Block: Stop all</strong>
                      <ul>
                        <li><strong>Action:</strong> Stops all scripts, effectively ending the game.</li>
                        <li><strong>Purpose:</strong> Concludes the game when the winning condition is met.</li>
                      </ul>
                    </li>
                  </ul>
                </li>
                    <li><strong>Block: Stop all</strong>
                      <ul>
                        <li><strong>Action:</strong> Stops all scripts, effectively ending the game.</li>
                        <li><strong>Purpose:</strong> Ensures the game concludes properly when the game over condition is met.</li>
                      </ul>
                    </li>
                  </ul>
                </li>
              </ul>
            </li>
          </ul>
        </li>
      </ul>
    </td>
  </tr>
</table>

### Rock Clones Behavior
<table>
  <tr>
    <td><img src="images/start_as_clone_for_rock.png" alt="Rock Clones Behavior" width="1200" height="400"></td>
    <td>
      <h3>Rock Clones Behavior Code Explanation</h3>
      <p>This code block defines the behavior for a sprite when it starts as a clone. It manages the movement and interactions of the clone in the game.</p>
      <ol>
        <li><strong>Event: When I start as a clone</strong>
          <ul>
            <li><strong>Block: show</strong>
              <ul>
                <li><strong>Action:</strong> Makes the clone visible.</li>
                <li><strong>Purpose:</strong> Ensures the clone can be seen when it is active.</li>
              </ul>
            </li>
            <li><strong>Block: repeat until touching edge or touching Rocks</strong>
              <ul>
                <li><strong>Action:</strong> Moves the clone downward by 5 units continuously until it touches the edge of the screen or another sprite named "Rocks".</li>
                <li><strong>Purpose:</strong> Simulates the falling movement of the clone, adding interaction with the game environment.</li>
              </ul>
            </li>
            <li><strong>Block: hide</strong>
              <ul>
                <li><strong>Action:</strong> Hides the clone once the repeat condition is met.</li>
                <li><strong>Purpose:</strong> Removes the clone from view once it has completed its movement or interaction.</li>
              </ul>
            </li>
          </ul>
        </li>
      </ol>
    </td>
  </tr>
</table>

### Game Start
<table>
  <tr>
    <td><img src="images/start_of_the_game_for_rocks.png" alt="Game Start Code" width="900" height="400"></td>
    <td>
      <h3>Game Start Code Explanation</h3>
      <p>This code block defines the actions that occur when the green flag is clicked, typically indicating the start of the game.</p>
      <ol>
        <li><strong>Event: When green flag clicked</strong>
          <ul>
            <li><strong>Block: play sound [Space Ripple] until done</strong>
              <ul>
                <li><strong>Action:</strong> Plays the "Space Ripple" sound effect completely before moving to the next block.</li>
                <li><strong>Purpose:</strong> Provides an auditory cue to signal the start of the game.</li>
              </ul>
            </li>
            <li><strong>Block: switch backdrop to [Stars]</strong>
              <ul>
                <li><strong>Action:</strong> Changes the background of the stage to "Stars".</li>
                <li><strong>Purpose:</strong> Sets the initial scene for the game environment.</li>
              </ul>
            </li>
            <li><strong>Block: hide</strong>
              <ul>
                <li><strong>Action:</strong> Hides the sprite executing this script.</li>
                <li><strong>Purpose:</strong> Ensures the sprite is not visible until it is needed.</li>
              </ul>
            </li>
            <li><strong>Block: set [score] to [0]</strong>
              <ul>
                <li><strong>Action:</strong> Initializes the score to 0 at the start of the game.</li>
                <li><strong>Purpose:</strong> Resets the game score for a new playthrough.</li>
              </ul>
            </li>
            <li><strong>Block: repeat [7]</strong>
              <ul>
                <li><strong>Block: set size to [pick random 30 to 60] %</strong>
                  <ul>
                    <li><strong>Action:</strong> Randomly sets the size of the sprite to a value between 30% and 60%.</li>
                    <li><strong>Purpose:</strong> Adds variety to the size of the clones, making the game more interesting.</li>
                  </ul>
                </li>
                <li><strong>Block: create clone of [myself]</strong>
                  <ul>
                    <li><strong>Action:</strong> Creates a clone of itself.</li>
                    <li><strong>Purpose:</strong> Continuously generates new clones to simulate ongoing action in the game.</li>
                  </ul>
                </li>
              </ul>
            </li>
          </ul>
        </li>
      </ol>
    </td>
  </tr>
</table>

### Super Bullet Base
<table>
  <tr>
    <td><img src="images/super_bullet_base.png" alt="Super Bullet Base Code" height="200" width="200"></td>
    <td>
      <h3>Super Bullet Base Code Explanation</h3>
      <p>This code block defines the base behavior of the super bullet sprite, ensuring it follows another sprite continuously.</p>
      <ul>
        <li><strong>Event: When green flag clicked</strong>
          <ul>
            <li><strong>Block: Hide</strong>
              <ul>
                <li><strong>Action:</strong> Hides the sprite executing this script.</li>
                <li><strong>Purpose:</strong> Ensures the sprite is not visible until needed.</li>
              </ul>
            </li>
            <li><strong>Forever Loop</strong>
              <ul>
                <li><strong>Block: Go to (Sprite1)</strong>
                  <ul>
                    <li><strong>Action:</strong> Continuously moves the sprite to the location of "Sprite1".</li>
                    <li><strong>Purpose:</strong> Keeps the sprite aligned with "Sprite1" for accurate positioning.</li>
                  </ul>
                </li>
              </ul>
            </li>
          </ul>
        </li>
      </ul>
    </td>
  </tr>
</table>

### Super Bullet Movement
<table>
  <tr>
    <td><img src="images/super_bullet_movement.png" alt="Super Bullet Movement Code" height="300" width="500"></td>
    <td>
      <h3>Super Bullet Movement Code Explanation</h3>
      <p>This code block defines the behavior of a cloned sprite, likely a bullet, that moves vertically until it touches the edge of the screen.</p>
      <ul>
        <li><strong>Event: When I start as a clone</strong>
          <ul>
            <li><strong>Block: Show</strong>
              <ul>
                <li><strong>Action:</strong> Makes the cloned sprite visible.</li>
                <li><strong>Purpose:</strong> Ensures the clone can be seen when active.</li>
              </ul>
            </li>
            <li><strong>Repeat Until Loop: Touching Edge</strong>
              <ul>
                <li><strong>Block: Change y by 15</strong>
                  <ul>
                    <li><strong>Action:</strong> Moves the sprite upward by 15 units each iteration.</li>
                    <li><strong>Purpose:</strong> Simulates the upward movement of the bullet.</li>
                  </ul>
                </li>
              </ul>
            </li>
            <li><strong>Block: Hide</strong>
              <ul>
                <li><strong>Action:</strong> Hides the sprite once it touches the edge of the screen.</li>
                <li><strong>Purpose:</strong> Removes the sprite from view after it has completed its movement.</li>
              </ul>
            </li>
          </ul>
        </li>
      </ul>
    </td>
  </tr>
</table>

## Credits
<table>
  <tr>
    <td><img src="images/CS50x_logo.png" alt="CS50 Logo" width="800" height="300"></td>
    <td>
      <h3>Credits to CS50x</h3>
      <p>This project was inspired by and developed as part of the CS50x course offered by Harvard University. CS50x is Harvard University's introduction to the intellectual enterprises of computer science and the art of programming for majors and non-majors alike, with or without prior programming experience.</p>
      <ul>
        <li><strong>Course:</strong> CS50x: Introduction to Computer Science</li>
        <li><strong>Institution:</strong> Harvard University</li>
        <li><strong>Instructor:</strong> David J. Malan</li>
        <li><strong>Website:</strong> <a href="https://cs50.harvard.edu/x/2024/">CS50x Official Site</a></li>
      </ul>
      <p>Thank you to the CS50x team for providing such a comprehensive and engaging introduction to computer science.</p>
    </td>
  </tr>
</table>
