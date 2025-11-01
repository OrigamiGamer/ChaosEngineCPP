# `RenderTaskParam_Rectangle`
```cpp
struct RenderTaskParam_Rectangle {
    vec2<float> pos;
    vec2<float> size;
    bool isFilled;
    float strokeWidth;
    vec2<float> radius;
    float opacity;
    vec2<float> pivot;
    float rotation;
    vec2<float> scale;
};
```



### Parameters:



- ## `pos`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The center position of the rectangle.
    - ### Default:
    ```cpp
    {0.0f,0.0f}
    ```
    
- ## `size`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The size (width and height) of the rectangle.
    - ### Default:
    ```cpp
    {100.0f,100.0f}
    ```

- ## `isFilled`:
    - ### Type: `bool`
    - ### Description:
        Fill the rectangle with the filling brush or not.
    - ### Default:
    ```cpp
    false
    ```
    
- ## `strokeWidth`:
    - ### Type: `float`
    - ### Description:
        The width of the stroke.
    - ### Default:
    ```cpp
    1.0f  // pixel
    ```
    
- ## `radius`:
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The radius of the rounded corners of the rectangle.
    - ### Default:
    ```cpp
    {0.0f,0.0f} // No rounded corners.
    ```
    
- ## `opacity`:
    - ### Type: `float`
    - ### Range: `0.0f-1.0f`
    - ### Description:
        The opacity of the rectangle.
    - ### Default:
    ```cpp
    1.0f  // Visible
    ```
    
- ## `pivot`:
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        Any transform of the rectangle will be based on this pivot.<br>
        If length on any direction of the vector is `-1`, it will be the center position related to `pos` and `size` by default.
    - ### Default:
    ```cpp
    {-1,-1} // Center position related to "pos" and "size"
    ```
    
- ## `rotation`:
    - ### Type: `float`
    - ### Description:
        The angle to rotate the rectangle.

- ## `scale`:
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The scale to stretch the rectangle on axis X and Y.
    - ### Default:
    ```cpp
    {1.0f, 1.0f} // Normal scale
    ```
