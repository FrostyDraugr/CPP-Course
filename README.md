# CPP-Course#
First Release of the Project, Includes the following:

Controllable Player:
- 2D Movement
- Fire Action
- Health & Death

Generated level:
-Destructible Obstacles, that spawn within a changable area
-Difficulty over time
-Score based on Distance Traveled
-Dynamic Map Size (Allowed Player Area, Distance Between Obstacles)

Known Bugs:
- Collision between Player and Obstacle is super wonky at the moment, this isn't a code issue but rather an issue of me not fully understanding how collisions works within Unreal Engine.
- Highscore not sorting in the correct order until the list is full
-Player will get knocked back off the allowed play area due to collisions with objects.
(The mesh the player uses is a cone that was added through the BP not the code, forgot to change it and I'm sure it's the biggest reasons for my issues)

Known Issues:
-No pause menu for easy restart.
-No Death Screen to showcase score/new Highscore.
-Obstacles don't use sweeping when moving.
-Player Character isn't sweeping when input is null.
-Really Hard to die later in the game due to collision issue.

Planned Features:
-GamePad functionality.
-Boost Action.
-Pickups.
-Hostile NPC's.
-Player Will Use Projectile instead of Line Trace.
