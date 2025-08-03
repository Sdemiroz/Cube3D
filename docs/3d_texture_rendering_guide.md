# 3D Textured Wall Rendering System

## Overview
This document explains the 3D textured wall rendering system implemented for the Cub3D raycasting project. The system is designed to work with static test data initially and can be easily adapted for real ray data when available.

## Current Implementation

### Files Modified
- `/src/rendering/renders.c` - Main 3D rendering functions
- `/include/cub3d.h` - Function declarations

### Key Functions

#### `render_3d_walls(t_game *game)`
Main rendering function that:
- Loops through each screen column (x = 0 to window width)
- Generates test data for wall height, texture coordinates, and texture selection
- Calls `draw_textured_wall_column_new()` for each column

#### `draw_textured_wall_column_new(game, x, wall_height, wall_hit_x, texture)`
Renders a single vertical column with:
- `x`: Screen column position
- `wall_height`: Height of wall in pixels (affects distance/perspective)
- `wall_hit_x`: Texture X coordinate (0.0-1.0) where ray hit the wall
- `texture`: Which texture to use (NO_texture, SO_texture, WE_texture, EA_texture)

#### `get_pixel_from_texture(texture, tex_x, tex_y)`
Extracts RGBA color from texture at given coordinates with bounds checking.

## Static Test Data (Current)
```c
// Varying wall heights for depth perception
wall_height = 200 + (screen_x % 300) - 150;  // Range: 50-350 pixels

// Varying texture X coordinates
wall_hit_x = (screen_x % 100) / 100.0f;      // Range: 0.0-0.99

// Cycling through textures by screen quarters
if (screen_x < width/4) texture = NO_texture;       // North (dali3.png)
else if (screen_x < width/2) texture = SO_texture;  // South (dali4.png)
else if (screen_x < 3*width/4) texture = WE_texture; // West (irises.png)
else texture = EA_texture;                           // East (pony.png)
```

## Integration with Real Ray Data

### Step 1: Prepare Ray Data Structure
Ensure your ray structure contains:
```c
typedef struct s_ray {
    float distance;        // Distance from player to wall hit
    float wall_hit_x;      // X coordinate on wall (0.0-1.0)
    int wall_direction;    // 0=NO, 1=SO, 2=WE, 3=EA (or enum)
    // ... other ray data
} t_ray;
```

### Step 2: Replace Static Data
In `render_3d_walls()`, replace the test data with:

```c
for (screen_x = 0; screen_x < game->data->wind_w; screen_x++)
{
    // Map screen column to ray index
    int ray_index = (screen_x * total_rays) / game->data->wind_w;

    // Calculate wall height from ray distance
    wall_height = calculate_wall_height_from_distance(rays[ray_index].distance);

    // Get texture hit position
    wall_hit_x = rays[ray_index].wall_hit_x;

    // Select texture based on wall direction
    texture = get_texture_from_direction(game, rays[ray_index].wall_direction);

    // Draw the column
    draw_textured_wall_column_new(game, screen_x, wall_height, wall_hit_x, texture);
}
```

### Step 3: Helper Functions to Implement
```c
int calculate_wall_height_from_distance(float distance)
{
    // Convert ray distance to screen wall height
    // Closer walls = taller on screen
    // Example: return (int)(WALL_HEIGHT_CONSTANT / distance);
}

mlx_texture_t *get_texture_from_direction(t_game *game, int direction)
{
    // Return appropriate texture based on wall direction
    // 0=North, 1=South, 2=West, 3=East
    switch(direction) {
        case 0: return game->NO_texture;
        case 1: return game->SO_texture;
        case 2: return game->WE_texture;
        case 3: return game->EA_texture;
        default: return game->NO_texture;
    }
}
```

## Visual Results
The current system shows:
- **Four distinct texture sections** across the screen width
- **Varying wall heights** creating depth perception
- **Smooth texture sampling** across each wall column
- **Proper texture scaling** and coordinate mapping

## Texture Information
- **NO (North)**: `dali3.png` (2487x2487)
- **SO (South)**: `dali4.png` (1618x1618)
- **WE (West)**: `irises.png` (699x699)
- **EA (East)**: `pony.png` (1086x1086)

## Testing
Run with: `./cub3d maps/map2.cub`

The current implementation provides a working 3D textured view that demonstrates:
1. ✅ Texture loading and management
2. ✅ 3D perspective calculation
3. ✅ Texture coordinate mapping
4. ✅ Multi-texture support
5. ✅ Efficient pixel-by-pixel rendering

## Next Steps
1. Complete raycasting implementation with your partner
2. Replace static test data with real ray results
3. Add ceiling and floor rendering (optional)
4. Optimize rendering performance if needed

The foundation is solid and ready for real ray data integration!
