# 3D Rendering Engine

A C++ 3D rendering application built using OpenGL, GLFW, GLM and Assimp. Developed as part of computer graphics coursework at the University of Otago.

The project loads and renders 3D models with materials, textures and lighting. It includes a movable camera, multiple lighting shaders and a framebuffer-based post-processing effect that can be toggled during runtime.

The application also provides a starting point for experimenting with OpenGL rendering techniques, GLSL shaders and 3D scene management.

## Features

- **3D Model Loading:** Imports OBJ models and associated MTL material files using Assimp.
- **Camera Controls:** Supports mouse-based camera rotation and keyboard movement through the scene.
- **Materials and Textures:** Loads texture maps and material properties, including ambient, diffuse and specular colours.
- **Lighting:** Implements Phong and Blinn-Phong shading for lighting and surface reflections.
- **Scene Management:** Organises objects, meshes, materials and transformations using reusable C++ classes.
- **Post-Processing:** Uses an off-screen framebuffer and GLSL shaders to apply animated screen-space effects.
- **Multiple Models:** Supports loading multiple OBJ files through command-line arguments.

## Requirements

The project uses the following libraries:

| Library | Purpose |
|---|---|
| OpenGL 3.3+ | 3D graphics rendering |
| GLFW | Window creation and input handling |
| GLM | Vector and matrix mathematics |
| Assimp | 3D model and material importing |
| GLAD | OpenGL function loading |

To build the project, you will also need:

- CMake
- A C++14-compatible compiler
- A compatible build tool (such as MinGW Make)
- Git, for downloading dependencies through CMake

The instructions below use Windows with MinGW-w64 (w64devkit) and Git Bash. GLFW, GLM and Assimp are downloaded automatically through CMake.

## Build and Run

### 1. Clone the Repository

Clone the repository and navigate to the project directory:

```bash
git clone <repository-url>
cd otago_projects/3d_rendering_engine
```

Replace the repository URL with your own. If cloning the complete `otago_projects` repository, the final directory will be inside that repository.

### 2. Configure CMake

From the `3d_rendering_engine` directory, run:

```bash
cmake -S . -B build \
  -G "MinGW Makefiles" \
  -DCMAKE_C_COMPILER=C:/w64devkit/bin/gcc.exe \
  -DCMAKE_CXX_COMPILER=C:/w64devkit/bin/g++.exe \
  -DCMAKE_MAKE_PROGRAM=C:/w64devkit/bin/mingw32-make.exe \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5
```

This assumes w64devkit is installed at `C:/w64devkit`. Adjust the paths if your compiler is installed elsewhere.

The first configuration may take longer because CMake needs to download and configure the required libraries.

### 3. Build the Application

Run:

```bash
cmake --build build -j 4
```

This compiles the dependencies and the renderer.

Once the initial build is complete, subsequent builds generally only need to compile changed files.

### 4. Run the Renderer

The program loads shaders and model files relative to its working directory, so it should be run from `Skeleton/`.

```bash
cd Skeleton
../build/Skeleton.exe
```

On Windows, if using a build directory outside the project, run the executable using its actual path instead.

The default scene loads `person.obj`, displaying a textured 3D character in an OpenGL window.

**Note:** The application captures the mouse while running. Press Esc to close it, or use Alt + Tab to switch to another application.

## Controls

| Control | Action |
|---|---|
| Mouse movement | Rotate the camera's viewing direction |
| Up arrow | Move the camera forward |
| Down arrow | Move the camera backward |
| Left arrow | Move the camera left (strafe) |
| Right arrow | Move the camera right (strafe) |
| Space | Toggle the animated post-processing effect |
| Esc | Exit the application |

The controls move the camera rather than the 3D model itself. For example, the up and down arrows make the character appear larger or smaller as the camera moves closer or farther away.

The camera movement speed can be adjusted in `renderApp.cpp`:

```cpp
myControls->setSpeed(30);
```

Mouse sensitivity and camera movement behaviour are implemented in `common/Controls.cpp`.

## Loading Different Models

By default, the renderer loads `person.obj`. Other models can be supplied as command-line arguments.

The project includes three example models:

- `person.obj` — a textured 3D character
- `earthobj.obj` — a 3D Earth model
- `flower.obj` — a flower model

To load a different model, run the executable from `Skeleton/` with the filename as an argument:

```bash
../build/Skeleton.exe earthobj.obj
```

Or:

```bash
../build/Skeleton.exe flower.obj
```

Multiple models can also be loaded:

```bash
../build/Skeleton.exe person.obj earthobj.obj flower.obj
```

Models are loaded into the same scene without automatic repositioning, so they may overlap.

### Adding Custom Models

The renderer can also be used with other compatible OBJ files.

1. Place the `.obj` file and any associated `.mtl` or texture files in an accessible directory.
2. Ensure that the material references and texture paths are correct.
3. Pass the OBJ filename or path as a command-line argument.

For example:

```bash
../build/Skeleton.exe myModel.obj
```

The renderer uses Assimp to import the model geometry and material information. Compatibility will depend on the model's structure and supported material properties.

## Shaders and Lighting

The application uses GLSL vertex and fragment shaders to control how objects are displayed.

The shader files are located in `Skeleton/`.

| Shader | Purpose |
|---|---|
| `basicShader.vert/.frag` | Basic geometry rendering |
| `phongShader.vert/.frag` | Phong lighting calculations |
| `blinnPhongShader.vert/.frag` | Blinn-Phong lighting calculations |
| `postEffect.vert/.frag` | Full-screen post-processing |

### Phong and Blinn-Phong Lighting

Both lighting implementations calculate surface appearance using material and lighting information.

The main components include:

- **Ambient:** Base lighting contribution
- **Diffuse:** Lighting based on the surface orientation relative to the light
- **Specular:** Highlights caused by reflected light
- **Textures:** Surface colour sampled from the model's texture maps

Phong shading uses a reflected light vector to calculate specular highlights, whereas Blinn-Phong uses a halfway vector between the light and viewing directions.

The main shader used to load models is selected in `renderApp.cpp`:

```cpp
Group* person = new Group("phongShader");
```

To experiment with Blinn-Phong shading, change this to:

```cpp
Group* person = new Group("blinnPhongShader");
```

The same change can be made where models are loaded from command-line arguments.

This allows the lighting implementations to be compared using the same geometry and materials.

## Post-Processing Effects

The renderer includes a post-processing system that applies visual effects to the final rendered image.

Normally, the 3D scene is rendered directly to the screen. When post-processing is enabled, the scene is instead rendered into an off-screen framebuffer.

The resulting texture is then drawn onto a full-screen quad using a separate shader.

The process is:

1. Render the 3D scene into a framebuffer.
2. Store the rendered image in a texture.
3. Pass the texture to the post-processing shader.
4. Apply the effect to the image.
5. Draw the processed image to the screen.

Press **Space** to toggle between normal rendering and post-processing.

### Default Ripple Effect

The default effect is implemented in:

```text
Skeleton/postEffect.frag
```

It uses sine and cosine functions to animate the texture coordinates:

```glsl
color.rgb = texture(
    myTextureSampler,
    UV + 0.005 * vec2(
        sin(time + 1024.0 * UV.x),
        cos(time + 768.0 * UV.y)
    )
).xyz;

color.a = 1.0;
```

This produces an animated ripple or wobble across the rendered image, without changing the underlying 3D geometry.

### Creating Custom Post-Processing Effects

One of the easiest ways to experiment with the renderer is to modify `postEffect.frag`.

The shader receives:

- `UV` — the texture coordinates of the rendered image
- `myTextureSampler` — the texture containing the rendered scene
- `time` — a value that changes continuously during execution

These can be used to implement different visual effects.

**Example 1: Grayscale**

Convert the rendered image to grayscale:

```glsl
vec3 rgb = texture(myTextureSampler, UV).rgb;
float gray = dot(rgb, vec3(0.299, 0.587, 0.114));
color = vec4(vec3(gray), 1.0);
```

**Example 2: Colour Inversion**

Invert the colours of the scene:

```glsl
vec3 rgb = texture(myTextureSampler, UV).rgb;
color = vec4(1.0 - rgb, 1.0);
```

**Example 3: Stronger Ripple**

Increase the ripple strength by changing the distortion multiplier:

```glsl
vec2 offset = 0.02 * vec2(
    sin(time + 1024.0 * UV.x),
    cos(time + 768.0 * UV.y)
);

color = vec4(texture(myTextureSampler, UV + offset).rgb, 1.0);
```

Other possible extensions include blur, edge detection, colour filters, pixelation and different animated distortion effects.

Changes to GLSL shader files generally do not require recompiling the C++ application. Restart the renderer to reload the modified shader.

## Project Structure

```text
3d_rendering_engine/
├── CMakeLists.txt
├── common/
│   ├── Camera.cpp / .hpp
│   ├── Controls.cpp / .hpp
│   ├── Scene.cpp / .hpp
│   ├── Object.cpp / .hpp
│   ├── Group.cpp / .hpp
│   ├── Mesh.cpp / .hpp
│   ├── Material.cpp / .hpp
│   ├── Texture.cpp / .hpp
│   ├── Shader.cpp / .hpp
│   ├── MTLShader.cpp / .hpp
│   ├── BasicMaterialShader.cpp / .hpp
│   ├── Objloader.cpp / .hpp
│   ├── Quad.cpp / .hpp
│   └── Triangle.cpp / .hpp
├── Skeleton/
│   ├── renderApp.cpp
│   ├── *.vert
│   ├── *.frag
│   ├── *.obj
│   ├── *.mtl
│   └── texture files
├── external/
│   └── glad/
├── .gitignore
└── README.md
```

### Main Components

| Component | Responsibility |
|---|---|
| `renderApp.cpp` | Application entry point, OpenGL setup, scene creation and rendering loop |
| `Camera` | View and projection transformations |
| `Controls` | Keyboard and mouse input |
| `Scene` | Collection and rendering of scene objects |
| `Object` / `Group` | Object structure, transformations and mesh grouping |
| `Mesh` | Geometry and vertex data |
| `Material` / `Texture` | Surface properties and texture handling |
| `Shader` / `MTLShader` | Shader compilation, uniforms and material-specific rendering |
| `Objloader` | Importing OBJ geometry and material information |
| `Quad` | Full-screen quad for post-processing |
| `Triangle` | Basic renderable geometry |

## Extending the Renderer

The project can be extended in several ways:

- **Custom Shaders:** Experiment with different lighting equations, surface colours and materials.
- **Post-Processing:** Modify `postEffect.frag` to create alternative effects without changing the C++ rendering pipeline.
- **Additional Models:** Import other OBJ models and test more complex scenes.
- **Camera Controls:** Change movement speed, mouse sensitivity or navigation behaviour.
- **Lighting:** Experiment with light positions and material properties to produce different shading results.
- **Scene Composition:** Modify object transformations and positions to create scenes containing multiple objects.
- **Rendering Techniques:** Extend the framebuffer system to support additional rendering passes or effects.

## Notes

- The renderer currently uses a default window size of 1024 × 768.
- Shader and model paths are relative to the working directory. Run the application from `Skeleton/`.
- The mouse is captured during normal operation; Esc exits the application.
- Model and material compatibility depends on the imported files and the renderer's supported material features.
- Generated build files and downloaded dependencies should not be committed to the repository.

## Acknowledgements

Developed as part of computer graphics coursework at the University of Otago. The project is based on a rendering framework provided by Stefanie Zollmann, with additional functionality developed as part of the coursework.