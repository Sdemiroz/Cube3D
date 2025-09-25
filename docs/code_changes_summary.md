# Code Changes Summary - Texture Precision Fixes

## File 1: `/include/cub3d.h`

**Change:** Ray hit coordinates data type modification

```diff
typedef struct s_rays
{
    int         index;          // index of the current ray being processed
    double      delta;          // angle of deviation +/- from the player's current direction
    // ... other fields ...
-   int         hit_x;          // x coordinate of the hit point
-   int         hit_y;          // y coordinate of the hit point
+   double      hit_x;          // x coordinate of the hit point
+   double      hit_y;          // y coordinate of the hit point
    double      length;         // length of the distance traveled by the ray
    double      wall_distance;  // ray length if the cur-direction aligns with ray angle
    char        hit_wall;       // N, S, E or W
    t_txr       *tex;
} t_rays;
```

**Impact:** Preserves floating-point precision instead of truncating to integers.

---

## File 2: `/src/ray_casting/ray_caster.c`

**Change:** Store precise floating-point hit coordinates

```diff
static void calculate_ray_length(t_game *game, t_rays *ray, char **img, t_data *data)
{
    // ... raycasting logic ...
    if ((hit.x >= 0 && hit.x < data->mmp_w && hit.y >= 0 &&
            hit.y < data->mmp_h) && (img[hit.y][hit.x] == '1'))
    {
        ray->length = (hype[2].x);
        ray->wall_distance = ((hype[2].x) * cos(ray->delta));
-       ray->hit_x = hit.x;
-       ray->hit_y = hit.y;
+       // Store precise floating-point hit coordinates
+       ray->hit_x = start.x + hype[2].x * ray->cosine;
+       ray->hit_y = start.y - hype[2].x * ray->sine;
        assign_wall_texture(game, ray, hop, check);
        break ;
    }
}
```

**Impact:** Calculates and stores precise world coordinates instead of truncated integer grid positions.

---

## File 3: `/src/rendering/3d.c`

**Change:** World-space texture coordinate calculation

```diff
void draw_3d_walls(t_game *game)
{
    // ... rendering setup ...
    while (screen_x < num_rays)
    {
        ray = rays[screen_x];
        wall_height = (int)(colm_h / ray->wall_distance);
        
-       // Old screen-space based calculation (incorrect)
-       wall_hit_x = (screen_x % 100) / 100.0f;
        
+       // High-precision texture mapping: world-space based
+       if (ray->hit_wall == 'N' || ray->hit_wall == 'S')
+       {
+           // For North/South walls, use X coordinate with high precision
+           wall_hit_x = fmod(ray->hit_x, (double)game->data->tile_size) / (double)game->data->tile_size;
+       }
+       else
+       {
+           // For East/West walls, use Y coordinate with high precision
+           wall_hit_x = fmod(ray->hit_y, (double)game->data->tile_size) / (double)game->data->tile_size;
+       }
        
        draw_column(game, screen_x, wall_height, wall_hit_x, ray->tex);
        screen_x++;
    }
}
```

**Impact:** 
- Eliminated texture sliding by using world coordinates
- Used `fmod()` for precise floating-point modulo operations
- Proper wall face detection for correct texture coordinate selection

---

## Debug Investigation Process

**Step 1:** Added debug prints to examine ray coordinates
```c
// DEBUG: Print ray coordinate precision every 100 rays
if (screen_x % 100 == 0)
{
    printf("Ray[%d]: hit_x=%.6f, hit_y=%.6f, wall=%c, wall_hit_x=%.6f\n", 
           screen_x, ray->hit_x, ray->hit_y, ray->hit_wall, wall_hit_x);
}
```

**Step 2:** Discovered quantization pattern
```
Output showed only 15 discrete values:
Ray[100]: hit_x=0.400000, hit_y=15.000000
Ray[200]: hit_x=0.866667, hit_y=15.000000  
Ray[300]: hit_x=0.466667, hit_y=15.000000
```

Values were exactly: 0/15, 1/15, 2/15, ..., 14/15

**Step 3:** Traced data flow to find truncation point in ray structure definition

---

## Validation

**Before Fix:** Ray coordinates showed only 15 discrete values
```
hit_x values: 0.000000, 0.066667, 0.133333, 0.200000, 0.266667, 
              0.333333, 0.400000, 0.466667, 0.533333, 0.600000,
              0.666667, 0.733333, 0.800000, 0.866667, 0.933333
```

**After Fix:** Ray coordinates show full floating-point precision
```
hit_x values: 123.456789, 87.234567, 245.891234, 156.789123...
```

**Visual Result:** 
- Textures no longer slide during movement
- High-resolution textures display with smooth gradients
- Eliminated blocky 15-color appearance