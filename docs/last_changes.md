Player Precision

Added double-precision fields for the player’s position/center so movement and ray casting can avoid cumulative rounding and then sync back to ints (include/cub3d.h:212, src/initialization/init_game.c:98, src/parsing/check_map.c:90).
Collision / Movement

Introduced wall_collision_circle to sample multiple offsets around the player’s circular hitbox, catching corner collisions before committing to the move (src/coordinates/collisions.c:69, include/cub3d.h:384).
Rewrote the movement resolvers to accumulate intended motion as doubles, probe X and Y separately with the new circle test, and only update the shared state when safe (src/events_bak.c:124, src/start.c:108).
Ray Casting

Rays now read the double-based player center so DDA stepping uses the precise start point and records high-precision wall hits (src/initialization/init_rays.c:33, src/ray_casting/ray_caster.c:84, src/ray_casting/ray_caster_utils.c:51).
Rendering

draw_column/erase_column clamp draw ranges, guard zero-height walls, and step through textures with floating increments to eliminate gaps; also muted the noisy OOB texture log (src/rendering/3d.c:129, src/rendering/3d.c:180, src/rendering/3d.c:219, mirrored in the backup variants).
Maps & Misc

Tuned asset references for testing: adjusted the cheese maze ceiling tint and pointed map2 at new art (file mode flipped to executable) (maps/good/cheese_maze.cub:7, maps/map2.cub:1).
Next Steps

Run the game and stress-test diagonal moves near walls to confirm the circular collision sampling behaves as expected.
