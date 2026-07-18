# `RenderTaskParam_Texture`
```cpp
struct RenderTaskParam_Texture {
    vec2<float> pos;
    vec2<float> size;
    vec2<float> texturePos;
    vec2<float> textureSize;
    Texture* texture;
    float opacity;
    vec2<float> pivot;
    float rotation;
    vec2<float> scale;
}
```



### Parameters:



- ## `pos`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The position on the canvas where the texture should be drawn.
    - ### Default:
    ```cpp
    {0.0f, 0.0f}
    ```

- ## `size`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The size of the texture on the canvas.<br>
    If any direction of the vector is `-1`, it will use the texture's original size by default.
    - ### Default:
    ```cpp
    {-1, -1} // Use texture's original size
    ```

- ## `texturePos`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The position within the texture to start drawing from.
    - ### Default:
    ```cpp
    {0.0f, 0.0f}
    ```

- ## `textureSize`: 
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The size of the texture region to draw.<br>
        If any direction of the vector is `-1`, it will use the texture's original size by default.
    - ### Default:
    ```cpp
    {-1, -1} // Use texture's original size
    ```

- ## `texture`:
    - ### Type: `Texture *`
    - ### Description:
        A pointer to the `Texture` resource.

- ## `opacity`:
    - ### Type: `float`
    - ### Range: `0.0f-1.0f`
    - ### Description:
        The opacity of the texture.
    - ### Default:
    ```cpp
    1.0f  // Visible
    ```

- ## `pivot`:
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        Any transform of the texture will be    based on this pivot.<br>
        If length on any direction of the vector is `-1`, it will be the center position related to `pos` and `size` by default.
    - ### Default:
    ```cpp
    {-1,-1} // Center position related to "pos" and "size"
    ```

- ## `rotation`:
    - ### Type: `float`
    - ### Description:
        The angle to rotate the texture.

- ## `scale`:
    - ### Type: `Chaos::vec2<float>`
    - ### Description:
        The scale to stretch the texture on axis X and Y.
    - ### Default:
    ```cpp
    {1.0f, 1.0f} // Normal scale
    ```
