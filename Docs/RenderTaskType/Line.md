# `RenderTaskParam_Line`
```cpp
struct RenderTaskParam_Line {
    vec2<float> pos1;
    vec2<float> pos2;
    float strokeWidth;
    float opacity;
    vec2<float> pivot;
    float rotation;
    vec2<float> scale;
};
```



### Parameters:



- ### `pos1`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
    The first point of the line.

- ### `pos1`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
    The second point of the line.

- ### `strokeWidth`:
    - ### Type: `float`
    - ### Description:
    The width of stroke of the line.
    - ### Default:
    ```cpp
    1.0f  // pixel
    ```

- ### `opacity`:
    - ### Type: `float`
    - ### Range: `0.0f-1.0f`
    - ### Description:
    The opacity of the line.
    
    - ### Default:
    ```cpp
    1.0f  // Visible
    ```

- ### `pivot`:
    - ### Type: `Chaos::vec<float>`
    - ### Description:
    Any transform of the line will be based on this pivot.<br>
    If length on any direction of the vector is `-1`, it will be the center position related to `pos1` and `pos2` by default.
    - ### Default:
    ```cpp
    {-1,-1} // Center position related to "pos1" and "pos2"
    ```

- ### `rotation`:
    - ### Type: `float`
    - ### Description:
    The angle to rotate the line.

- ### `scale`:
    - ### Type: `Chaos::vec<float>`
    - ### Description:
    The scale to strech the line on axis X and Y.
