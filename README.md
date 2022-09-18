# tech68 - Is open-source glfw/glad based engine writen on C++

tech68 - Is a powerful engine for C++

### 1. How to create window:
```
#include "res/tech68.hpp"

int main()
{
    tech68 app;
    tech68_window root = app.make_app(640, 480, "tech68 example");
    
    while (!root.is_open())
    {
        root.close_on_key();
        root.screen_clear(shader, app.black);
        
        root.app_event();
    }
    
    app.end_app();
}
```

### 2. How to draw triangle:
```
#include "res/tech68.hpp"

int main()
{
    tech68 app;
    tech68_window root = app.make_app(640, 480, "tech68 example");
    tech68_shader shader = app.get_shaders();
    
    tech68_shape shape = app.triangle();
    
    while (!root.is_open())
    {
        root.close_on_key();
        root.screen_clear(shader, app.black);
        
        root.draw(shape, shader, app.white);
        
        root.app_event();
    }
    
    root.end_app();
}
```

### 3. How to build game (only on arch-linux):
#### 1. Install tech68-builder.tar.zst...
Download the package, and install it using:
```
sudo pacman -U tech68-builder-x.x-1-x86_64.pkg.tar.zst
```
#### 2. Build game using:
###### !IMPORTANT!
Tree of project folder, need to looks something like this:
```
.
├── app.cpp
├── res
│   ├── glad
│   │   ├── glad.c
│   │   ├── glad.h
│   │   └── khrplatform.h
│   ├── fragment.glsl
│   ├── shader.hpp
│   ├── stb_image.h
│   ├── tech68.hpp
│   ├── tech_things.hpp
│   └── vertex.glsl

```

To build game use command
```
tech68-build
```
