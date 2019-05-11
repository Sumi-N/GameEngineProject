The game playe is simple. You just need to keep avoiding the enemy who chases you. If you get caught up, you lose and the game ends. While you are alive, the timer count is increasing.

What I specifically pround of is that I made the lua reader class to be a template class, so that I can make a derived class from Object3D or Physics Component in a game programming level.
By doing so, I just need to overide init() and update() function of each derived classes to determin logics and collision responces like what Unity do, and be able to keep the game programming code to be organized. 

Also I made Keyboard input class where track keyboard inputs in every frame using underordered map.
By dooing so, I just need to accessing the class to control the logic related to keyboard input instead of using delegate to register everytime. 