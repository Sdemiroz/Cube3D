# Step-by-Step 3D Textured Wall Rendering Implementation Guide

## Overview
This guide will help you implement 3D textured wall rendering from scratch. All the working code has been commented out in `src/rendering/renders.c`, and you'll implement each function step by step.

## Prerequisites
- Your textures are already loaded (NO_texture, SO_texture, WE_texture, EA_texture)
- MLX42 library is properly linked
- `img3D` image buffer is created for 3D rendering

## Implementation Steps

### Step 1: Implement `get_pixel_from_texture()`
**Location:** `src/rendering/renders.c` around line 321
**Goal:** Extract a single pixel color from a texture at given coordinates

```c
static uint32_t	get_pixel_from_texture(mlx_texture_t *texture, int x, int y)
{
	// TODO: Implement pixel extraction
	// 1. Check bounds (x < texture->width, y < texture->height)
	// 2. Calculate pixel index: index = (y * texture->width + x) * 4 (RGBA)
	// 3. Extract RGBA values from texture->pixels[index]
	// 4. Convert to uint32_t format: (R << 24) | (G << 16) | (B << 8) | A
	// 5. Return the color
}
```

**Test:** Add debug prints to verify pixel colors are being extracted correctly.

### Step 2: Implement `get_wall_texture()`
**Location:** `src/rendering/renders.c` around line 345
**Goal:** Return the correct texture based on wall direction

```c
static mlx_texture_t	*get_wall_texture(t_game *game, int ray_index)
{
	// TODO: Implement texture selection
	// 1. For now, use test data: int wall_direction = ray_index % 4;
	// 2. Use switch statement to return correct texture:
	//    - case 0: return game->NO_texture (North)
	//    - case 1: return game->SO_texture (South)
	//    - case 2: return game->WE_texture (West)
	//    - case 3: return game->EA_texture (East)
	// 3. Later replace with: game->rays[ray_index].wall_direction
}
```

**Test:** Verify different textures are being selected as you move across the screen.

### Step 3: Implement `calculate_wall_height()`
**Location:** `src/rendering/renders.c` around line 370
**Goal:** Calculate wall height based on distance

```c
static int	calculate_wall_height(t_game *game, int ray_index)
{
	// TODO: Implement wall height calculation
	// 1. For now, use test data to create varied heights:
	//    int base_height = game->data->wind_h / 3;
	//    int variation = (ray_index % 200) - 100;
	//    return (base_height + variation);
	// 2. Later replace with real formula:
	//    return (int)(game->data->wind_h / game->rays[ray_index].distance);
}
```

**Test:** You should see walls of different heights across the screen.

### Step 4: Implement `calculate_wall_hit_x()`
**Location:** `src/rendering/renders.c` around line 381
**Goal:** Calculate where on the wall texture to sample (0.0-1.0)

```c
static float	calculate_wall_hit_x(int ray_index)
{
	// TODO: Implement wall hit position
	// 1. For now, use test data: return ((float)(ray_index % 64) / 64.0f);
	// 2. This creates texture coordinate cycling from 0.0 to 1.0
	// 3. Later replace with: return game->rays[ray_index].wall_hit_x;
}
```

**Test:** Texture should appear to "slide" across the wall as you look at different columns.

### Step 5: Implement `draw_textured_wall_column_new()`
**Location:** `src/rendering/renders.c` around line 395
**Goal:** Draw a single textured wall column

```c
static void	draw_textured_wall_column_new(t_game *game, int screen_x, int wall_height, float wall_hit_x, mlx_texture_t *texture)
{
	// TODO: Implement column drawing
	// 1. Check parameters: if (!texture || !game->img3D) return;
	// 2. Calculate wall boundaries:
	//    wall_start_y = (game->data->wind_h - wall_height) / 2;
	//    wall_end_y = wall_start_y + wall_height;
	// 3. Clamp to screen: if (wall_start_y < 0) wall_start_y = 0; etc.
	// 4. Calculate texture sampling:
	//    tex_x = (int)(wall_hit_x * texture->width) % texture->width;
	//    step = (double)texture->height / wall_height;
	// 5. Loop through wall pixels:
	//    for (y = wall_start_y; y < wall_end_y; y++)
	//    {
	//        tex_y = (int)((y - wall_start_y) * step);
	//        color = get_pixel_from_texture(texture, tex_x, tex_y);
	//        mlx_put_pixel(game->img3D, screen_x, y, color);
	//    }
}
```

**Test:** You should see textured wall columns being drawn.

### Step 6: Implement `render_3d_walls()`
**Location:** `src/rendering/renders.c` around line 477
**Goal:** Main function that renders the entire 3D view

```c
void	render_3d_walls(t_game *game)
{
	// TODO: Implement main rendering loop
	// 1. Check parameters: if (!game || !game->img3D) return;
	// 2. For each screen column (screen_x = 0; screen_x < wind_w; screen_x++):
	//    a. Calculate wall_height using your function
	//    b. Calculate wall_hit_x using your function
	//    c. Get texture using your function
	//    d. Call draw_textured_wall_column_new()
	// 3. For test data, divide screen into 4 sections with different textures:
	//    - First quarter: NO_texture
	//    - Second quarter: SO_texture
	//    - Third quarter: WE_texture
	//    - Last quarter: EA_texture
}
```

**Test:** You should see a complete 3D view with 4 different textured sections.

### Step 7: Uncomment Function Declaration
**Location:** `include/cub3d.h`
**Goal:** Enable the function to be called

```c
// In the function declarations section, uncomment:
void	render_3d_walls(t_game *game);
```

### Step 8: Call the Function
**Location:** Find where you want to render (probably in `src/rendering/renders.c` in the main render function)

```c
// Add this call where you want 3D rendering:
render_3d_walls(game);
```

## Testing Strategy

### Phase 1: Basic Functionality
1. Implement steps 1-2, compile and test
2. You should see solid colored regions where walls should be

### Phase 2: Height Variation
1. Implement step 3
2. You should see walls of different heights

### Phase 3: Texture Positioning
1. Implement step 4
2. Textures should appear to slide/shift across walls

### Phase 4: Complete Rendering
1. Implement steps 5-6
2. You should see full textured 3D view

### Phase 5: Integration
1. Implement steps 7-8
2. Call your function from the main render loop

## Debug Tips

1. **Add debug prints** in each function to verify values:
   ```c
   printf("Wall height: %d, Hit X: %f\n", wall_height, wall_hit_x);
   ```

2. **Test with simple colors first** before textures:
   ```c
   mlx_put_pixel(game->img3D, screen_x, y, 0xFF0000FF); // Red
   ```

3. **Check texture loading**:
   ```c
   printf("Texture loaded: %p, Size: %dx%d\n", texture, texture->width, texture->height);
   ```

4. **Verify screen boundaries**:
   ```c
   if (screen_x >= game->data->wind_w || y >= game->data->wind_h)
       printf("Out of bounds: x=%d, y=%d\n", screen_x, y);
   ```

## Integration with Real Ray Data

Once your partner completes the raycasting system, replace the test data:

1. **In `get_wall_texture()`**:
   ```c
   return get_texture_by_direction(game->rays[ray_index].wall_direction);
   ```

2. **In `calculate_wall_height()`**:
   ```c
   return (int)(game->data->wind_h / game->rays[ray_index].distance);
   ```

3. **In `calculate_wall_hit_x()`**:
   ```c
   return game->rays[ray_index].wall_hit_x;
   ```

4. **In `render_3d_walls()`**:
   ```c
   // Replace the test texture selection with:
   texture = get_wall_texture(game, screen_x);
   ```

## Expected Visual Results

- **After Step 3**: Walls of varying heights (like a city skyline)
- **After Step 4**: Textures that shift horizontally as you scan across
- **After Step 6**: Four distinct texture sections with proper 3D perspective
- **Final Result**: A complete 3D textured view ready for real ray data

## Common Issues

1. **Black screen**: Check texture loading and pixel extraction
2. **Weird colors**: Verify RGBA conversion in `get_pixel_from_texture()`
3. **Distorted textures**: Check texture coordinate calculations
4. **Crashes**: Add bounds checking in all functions

Good luck with your implementation! Take it step by step and test frequently.
