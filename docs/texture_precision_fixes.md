# Texture Precision and Sliding Fixes

**Date:** September 25, 2025  
**Project:** Cube3D Raycaster  
**Issues Resolved:** Texture sliding and pixelated texture appearance

## Overview

This document details the fixes applied to resolve two critical texture rendering issues in the cub3d raycaster:

1. **Texture Sliding Issue:** Textures appeared to slide or shift as the player moved
2. **Texture Pixelation Issue:** High-resolution textures (2487x2487) appeared blocky with only 15 distinct horizontal colors

## Root Cause Analysis

### Issue 1: Texture Sliding
**Problem:** Textures would slide/shift during player movement instead of staying fixed to wall positions.

**Root Cause:** The texture coordinate calculation was using screen-space coordinates instead of world-space coordinates:
```c
// INCORRECT (screen-space based)
wall_hit_x = (screen_x % 100) / 100.0f;
```

This created texture coordinates based on the ray's screen position rather than where the ray actually hit the wall in world space.

### Issue 2: Texture Pixelation (15-pixel limitation)
**Problem:** 2487x2487 pixel textures appeared as only 15 different colors horizontally, creating a very blocky appearance.

**Root Cause Investigation:**
1. Initially suspected texture coordinate calculation precision issues
2. Added debug prints to examine ray hit coordinates
3. **Discovery:** Ray hit coordinates were quantized to only 15 discrete values:
   ```
   Ray[100]: hit_x=0.400000, hit_y=15.000000
   Ray[200]: hit_x=0.866667, hit_y=15.000000  
   Ray[300]: hit_x=0.466667, hit_y=15.000000
   ```
4. **Root Cause:** Ray hit coordinates were stored as `int` instead of `double`, truncating precise floating-point calculations

## Technical Details

### TILE_SIZE Impact
The project uses `TILE_SIZE = 15`, which created quantization:
- Hit coordinates were truncated to integers: 0, 1, 2, ..., 14
- This gave only 15 possible texture coordinate values per tile
- Result: `0/15, 1/15, 2/15, ..., 14/15` = 15 discrete colors

### Data Flow Analysis
```
Raycasting → Precise float calculation → INTEGER TRUNCATION → Texture mapping
            (123.456, 78.891)           (123, 78)            Limited precision
```

## Solutions Implemented

### Fix 1: Correct Texture Coordinate Calculation
**File:** `/src/rendering/3d.c`

**Before:**
```c
// Screen-space based (incorrect)
wall_hit_x = (screen_x % 100) / 100.0f;
```

**After:**
```c
// World-space based (correct)
if (ray->hit_wall == 'N' || ray->hit_wall == 'S')
{
    // For North/South walls, use X coordinate with high precision
    wall_hit_x = fmod(ray->hit_x, (double)game->data->tile_size) / (double)game->data->tile_size;
}
else
{
    // For East/West walls, use Y coordinate with high precision  
    wall_hit_x = fmod(ray->hit_y, (double)game->data->tile_size) / (double)game->data->tile_size;
}
```

**Explanation:**
- Uses `fmod()` for precise floating-point modulo operations
- Calculates texture coordinates based on actual wall hit position
- Maintains sub-pixel precision throughout the calculation

### Fix 2: Preserve Floating-Point Precision in Ray Data
**File:** `/include/cub3d.h`

**Before:**
```c
typedef struct s_rays
{
    // ... other fields ...
    int     hit_x;  // INTEGER - loses precision!
    int     hit_y;  // INTEGER - loses precision!
    // ... other fields ...
} t_rays;
```

**After:**
```c
typedef struct s_rays
{
    // ... other fields ...
    double  hit_x;  // DOUBLE - preserves precision!
    double  hit_y;  // DOUBLE - preserves precision!
    // ... other fields ...
} t_rays;
```

**File:** `/src/ray_casting/ray_caster.c`

**Before:**
```c
ray->hit_x = hit.x;  // Truncated integer coordinates
ray->hit_y = hit.y;  // Truncated integer coordinates
```

**After:**
```c
// Store precise floating-point hit coordinates
ray->hit_x = start.x + hype[2].x * ray->cosine;
ray->hit_y = start.y - hype[2].x * ray->sine;
```

## Results

### Before Fixes:
- ❌ Textures slid during movement
- ❌ Only 15 horizontal colors visible (severe pixelation)
- ❌ High-resolution textures looked blocky
- ❌ Poor visual quality

### After Fixes:
- ✅ Textures remain fixed to wall positions
- ✅ Full sub-pixel precision preserved
- ✅ Smooth texture gradients
- ✅ High-resolution textures display properly
- ✅ Professional visual quality

## Testing Methodology

1. **Debug Instrumentation:** Added printf statements to examine ray coordinate precision
2. **Visual Comparison:** Before/after texture appearance
3. **Coordinate Analysis:** Verified ray hit coordinates now show full floating-point precision (e.g., 123.456789 instead of just 123.000000)
4. **Movement Testing:** Confirmed textures no longer slide during player movement

## Technical Impact

### Performance
- **Minimal impact:** Changed from integer to double storage (8 bytes vs 4 bytes per coordinate)
- **Calculation overhead:** Negligible - fmod() operations are fast
- **Memory increase:** ~8 bytes per ray × 1800 rays = ~14KB additional memory

### Compatibility
- **No breaking changes** to external interfaces
- **Internal data structure changes** only affect raycasting system
- **Maintains** all existing functionality

## Key Learnings

1. **Precision Matters:** Integer truncation in graphics can cause severe visual artifacts
2. **Debug First:** Adding instrumentation helped identify the real root cause quickly
3. **Data Flow Tracking:** Following data from calculation to display revealed the truncation point
4. **World vs Screen Space:** Texture coordinates must be based on world-space hit positions

## Files Modified

1. `/include/cub3d.h` - Changed ray hit coordinates from `int` to `double`
2. `/src/ray_casting/ray_caster.c` - Store precise floating-point coordinates
3. `/src/rendering/3d.c` - World-space texture coordinate calculation

## Future Considerations

- Monitor performance with large numbers of rays
- Consider other precision-sensitive calculations in the rendering pipeline
- Evaluate if other data structures need similar precision improvements

---

**Summary:** The fixes transform the texture system from a limited 15-color quantized appearance to full sub-pixel precision rendering, dramatically improving visual quality while maintaining performance.