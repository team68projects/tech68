# tech68 - Is open-source glfw/glad based engine writen on C++

tech68 - Is a powerful engine for C++

### 1. How to create window:
```
#include "res/tech68.hpp"

int main()
{
    tech68 app;
    tech68_window root = app.make_app(640, 480, "tech68 example");
    
    while (!app.is_open(root))
    {
        app.close_on_key(root);
        app.screen_clear(shader, 0.75f, 0.3f, 0.215f);
        
        app.app_event(root);
    }
    
    app.end_app(root);
}
```

### 2. How to draw triangle:
```
#include "res/tech68.hpp"

int main()
{
    tech68 app;
    tech68_window root = app.make_app(640, 480, "tech68 example");
    tech68_shaders shader = app.get_shaders();
    
    tech68_shape shape = app.triangle();
    
    while (!app.is_open(root))
    {
        app.close_on_key(root);
        app.screen_clear(shader, 0.75f, 0.3f, 0.215f);
        
        app.draw(shape, shader);
        
        app.app_event(root);
    }
    
    app.end_app(root);
}
```

### 3. How to build game (only on arch-linux):
#### 1. Install tech68-builder.tar.zst...
Download the package, and install it using:
```
sudo pacman -U tech68-builder-x.x-1-x86_64.pkg.tar.zst
```
#### 2. Build game using:
```
tech68-build
```
and tree of project folder, need to looks something like this:
```
.
├── app.cpp
└── res
    ├── glad
    │   ├── glad.c
    │   ├── glad.h
    │   └── khrplatform.h
    ├── fragment.glsl
    ├── obj.hpp
    ├── shader.hpp
    ├── tech68.hpp
    ├── tech_things.hpp
    └── vertex.glsl
```
