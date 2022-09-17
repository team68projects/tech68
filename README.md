# tech68 - Is open-source glfw/glad based engine writen on C++

tech68 - Is a powerful engine for C++

### 1. How to create window:
```
#include "res/tech68.hpp"

int main()
{
    tech68::init();
    
    tech68_window app = tech68::make_app(640, 480, "TEST!");
    while (!tech68::is_open(app))
    {
        tech68::close_on_key(app);
        tech68::screen_clear(0.2f, 0.3f, 0.3f, 1.0f);

        tech68::app_event(app);
    }
    tech68::end_app(app);
}
```

### 2. How to build game:
```
gcc -c res_folder/glad/glad.c
g++ some_name.cpp -o app.bin glad.o -ldl -lglfw
```
