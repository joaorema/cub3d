🎮 cub3D
ℹ️ About the project

This project was done in partnership with Izzytoot.

Cub3D is our own mini‑Wolfenstein‑style 3D engine using raycasting and MiniLibX.
💪 What It Does
i) Reads a .cub configuration file containing:

    Texture paths (N/S/E/W walls)
    Floor/ceiling RGB colors
    A 2D map with player start position (N/S/E/W), walls (1) and empty space (0).

ii) Validates map integrity through a thorough parsing system. It checks:

    closed walls;
    if it has exactly one player;
    if there are no invalid chars;
    if it handles padded spaces.

iii) Uses raycasting (via Digital Differential Analysis, DDA) to simulate a 3D view from a 2D map;
iv) Renders textured walls and colored floor and ceiling;
v) Allows player movement (WASD), rotation (arrow keys or mouse), and clean exit with ESC or window close.
🧠 Implementation Phases
1. Configuration & Map Parsing

    Parse config file to extract texture paths and floor/ceiling RGB values;
    Normalize map into a 2D array (pad shorter rows with 'X')
    Validate map boundaries and interior:
        All edges and spaces must be fully enclosed by walls (1);
        Only valid characters allowed: 1, 0, N, S, E, W and spaces;
        Exactly one player starting position;

2. Graphics Setup

    Initialize MiniLibX: window and image buffers;
    Load textures into memory for each wall direction;

3. Raycasting Algorithm (DDA)

    For each vertical stripe on screen:
        Cast a ray from player position along a calculated direction;
        Use DDA to step grid by grid until a wall (1) is reached;
        Compute perpendicular distance to correct fisheye effect;
        Determine wall slice height and texture offset;
        Draw textured vertical stripe accordingly

4. Rendering

    Draw ceiling and floor;
    For each stripe, render wall slice with proper texture mapping

5. Cleanup & Error Handling

   Free all allocations, clear textures and buffers;
    Handle invalid input or map errors gracefully;
    Exit cleanly when pressing ESC or closing the window;

🔥 Build, run and test
Test a valid map and play

git clone https://github.com/izzytoot/cub3d.git
cd cub3d
./cub3D maps/valid/any_map_from_folder.cub

Controls:
Key 	Action
W 	Move forward
A 	Move left
S 	Move back
D 	Move right
← 	Rotate view to left
→ 	Rotate view to right
ESC / X 	Exit
Test an invalid map

git clone https://github.com/izzytoot/cub3d.git
cd cub3d
./cub3D maps/invalid/any_map_from_folder.cub
