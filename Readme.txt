This game engine is the game engine I made from the scrach.
It is currently implemented components such as

    Entity Component System
    Heap manager and Smart pointers for memory management
    Basic math libraries such as Matrix and Vector 
    Platform independent input system
    Assertion and Debug log for a debug purpose
    Multi threads by separating game logic and render logic
    Open GL renderer



TODO List

.  Implement and switch the file loader to my original
.  Add directi light and direct light shadow map 
.  Change point light shadow map to cube map
.  Refactor Entity system
.  Simple asset loader written in Lua
.  Multicast delegate messaging system
.  Finish TBN matrix for normal mapping
.  Separate the density between graphics and parts module
.  Add default setting for each componetns such as shader
.  Fix skybox to correct dependency




Done

.  Make a query function for scene entity to ba able to query specific scene format
.  Organize displace mapping and related functions such as render and shader structures.


Unsolved

.  Make skybox loading process to multi threading