# Cub3D - 42 School Project

A 3D game engine implementation using raycasting techniques, built with the MLX42 graphics library.

## Performance Optimizations

### Circle Rendering System (July 2025)
- **Implementation**: Separate image instance approach for moving objects
- **Performance Gain**: ~100x improvement for player movement updates
- **Documentation**: See [docs/circle_analysis.md](docs/circle_analysis.md)

#### Key Features
- **Anti-aliased rendering**: Smooth circle edges using alpha blending
- **Instance-based movement**: O(1) position updates vs. O(radius²) pixel operations
- **Quality scaling**: High-quality rendering for important elements

#### Usage
```c
// Initialize once
init_player_circle(game);

// Move efficiently (2 integer assignments)
move_player_circle(game, new_x, new_y);
```

## Performance Analysis Results

| Approach | Movement Cost | Quality | Recommendation |
|----------|---------------|---------|----------------|
| Traditional redrawing | ~242 pixel operations | Variable | ❌ Avoid |
| Separate instance + smooth | 2 assignments | Excellent | ✅ **Recommended** |
| Separate instance + improved | 2 assignments | Good | ✅ Alternative |

## Documentation

### Analysis Documents
- `docs/circle_analysis.md` - Comprehensive performance analysis
- `src/circles.c` - Implementation with performance comments
- `src/player_rendering.c` - Separate instance system

### Key Insights
1. **Paradigm shift**: From pixel manipulation to instance manipulation
2. **Quality vs. performance**: Separate instances eliminate the trade-off
3. **MLX42 optimization**: Instance system provides significant opportunities

## Implementation Status

### Completed ✅
- [x] Circle rendering method comparison
- [x] Performance analysis and benchmarking
- [x] Separate image instance implementation
- [x] Anti-aliasing system with alpha blending

### Next Steps 📋
- [ ] Implement separate image instance for player movement
- [ ] Extend approach to other moving objects (enemies, projectiles)
- [ ] Add rotation/scaling support using instance transformations
- [ ] Implement level-of-detail system for distant objects

## Build and Run

```bash
# Build
make

# Run with map
./cub3d maps/map3.cub

# Run in Docker
make docker

# Performance testing
make debug
```

## Technical Specifications

- **Graphics Library**: MLX42
- **Language**: C (C99 standard)
- **Platform**: macOS, Linux
- **Memory Management**: Custom garbage collector
- **Performance**: Optimized for 60+ FPS gameplay

## References

- **Circle Analysis**: Based on comprehensive method comparison (July 2025)
- **MLX42 Documentation**: [MLX42 GitHub](https://github.com/codam-coding-college/MLX42)
- **Raycasting Theory**: Based on classic game development techniques

---

*Analysis conducted July 10, 2025 - Branch: Pranuj*