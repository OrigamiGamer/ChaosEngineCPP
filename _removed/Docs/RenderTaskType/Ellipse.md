# `RenderTaskParam_Ellipse`
```cpp
struct RenderTaskParam_Ellipse {
    vec2<float> pos;
    vec2<float> radius;
    bool isFilled;
    float strokeWidth;
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
        The center position of the ellipse.
    - ### Default:
    ```cpp
    {0.0f, 0.0f}
    ```
    
- ## `radius`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The radius of the ellipse on axis X and Y.
    - ### Default:
    ```cpp
    {100.0f, 100.0f}
    ```

- ## `isFilled`:
    - ### Type: `bool`
    - ### Description:
        Fill the ellipse with the filling brush or not.
    - ### Default:
    ```cpp
    false // Unfilled
    ```

- ## `strokeWidth`:
    - ### Type: `float`
    - ### Description:
        The width of stroke to the border.
    - ### Default:
    ```cpp
    1.0f  // pixel
    ```

- ## `opacity`:
    - ### Type: `float`
    - ### Range: `0.0f-1.0f`
    - ### Description:
        The opacity of the ellipse.
    - ### Default:
    ```cpp
    1.0f  // Visible
    ```

- ## `pivot`:
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        Any transform of the ellipse will be based on this pivot.<br>
        If length on any direction of the vector is `-1`, it will be the center position related to `pos` by default.
    - ### Default:
    ```cpp
    {-1,-1} // Center position related to "pos"
    ```

- ## `rotation`:
    - ### Type: `float`
    - ### Description:
        The angle to rotate the ellipse.

- ## `scale`:
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The scale to stretch the ellipse on axis X and Y.
    - ### Default:
    ```cpp
    {1.0f, 1.0f} // Normal scale
    ```
