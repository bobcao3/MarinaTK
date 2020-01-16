# Design of MarinaTK

## Types

`enum Units` contains all the basic units. Derived units are converted directly into one of the basic units.
-   `None`: Value with no unit
-   `Pixel`: NDC pixel
-   `Dot`: Device indepent pixel
-   `Percent`: A percentage value
-   `Milimeter`: Milimeter

`Value` represents a numeric value with unit.
-   `float` value
-   `Units` unit
-   `void norm()`: mutator, limits the value to the proper range

## Component - View - Render Layer model

### Component

`Component` describes a logical component in the user interface. This could be a button, a text field, a web view, etc. Component could contain other components, and a single component can be made up with different components. Numeric values in component is always represented with units.

Each component could have none or one parent. Parent "owns" the component.

`Component` class contains:

Properties
-   `vector<weak_ptr<Component>> children`: get

Methods
-   `void insert_children(unique_ptr<Component>)`: moves the child node
-   `unique_ptr<View> get_view()`: converts this object into View model

### View

`View` describes a laid out object that is being displayed. View model is a bijection of `Component` model. `View` model is non-mutable, once a `View` tree is not up-to-date, it should be regenerated from `Component` tree. All values in `View` is converted into NDC pixel.

`View` class contains:

Properties
-   `weak_ptr<Component> component`: get
-   `vector<weak_ptr<View>> children`: get
-   `AABB bbox`: get, bounding box in NDC pixels

### Render Layer

`RenderLayer` describes a renderable primitive.

Methods
-   `void render(RasterSurface&)`: Renders the layer on the `RasterSurface`

## Backend System

`Backend` describes a backend.

Methods
-   `shared_ptr<RasterSurface> createRasterSurface(string name, int w, int h)`: Create a surface (window) for drawing the interface with name, width, and height.

`RasterSurface` describes a drawable surface.

Properties
-   `ivec2 size`: get / set
-   `SkCanvas& canvas`: get
