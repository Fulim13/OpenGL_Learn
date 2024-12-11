### Key Concepts in OpenGL Lighting:
1. **Lighting Components:**

Ambient Light: This is like background light that comes from all directions, evenly spread out. It doesn't have a specific source, like the general glow you might see in a room from overhead lights or sunlight scattered in the air. It makes sure objects are visible, even if there isn’t a clear light shining on them.

Diffuse Light: This is light that comes from a specific direction and spreads out evenly when it hits a surface. It’s like sunlight hitting a wall—it lights it up but doesn’t make it shiny. Diffuse light shows the shape and depth of objects because the brightness depends on the angle of the light. (Softness of object)

Specular Light: This is light that makes shiny spots on surfaces, like a reflection. It depends on where you’re looking from, the angle of the light, and how shiny the surface is. For example, it’s the bright spot you see on a polished car or a metal spoon when light hits them. Specular lighting gives objects a glossy or metallic appearance.

![image](https://github.com/user-attachments/assets/6ce9567c-bece-4521-bd3c-60b0b98da4e8)
![image](https://github.com/user-attachments/assets/448e8a99-61fb-4908-b16c-6e3b350e0389)



2. **Material Properties:**
   - Materials define how objects reflect light (e.g., diffuse, ambient, and specular components).

3. **Light Position:**
   - The position of a light source is affected by the current transformation matrix. To avoid unintended transformations, configure the light position after setting the appropriate matrix.

---

### **`glPushMatrix()` and `glPopMatrix()` for light sphere:**
- **Purpose:** These functions are used to isolate transformations applied to the red sphere that represents the light source (`light_position2`).

#### Breakdown:
1. **`glPushMatrix()`**: Saves the current transformation matrix. This ensures that any transformations (e.g., translations) applied to the sphere won't affect the rest of the scene.
   
2. **`glTranslatef(light_position2[0], light_position2[1], light_position2[2])`**:
   - Moves the drawing origin to the position specified by `light_position2`. This is where the light source is located.
   - `light_position2` should contain three values (`x, y, z`) that define the light’s position in the world space.

3. **`sphere = gluNewQuadric()`**:
   - Creates a new quadrics object to draw 3D shapes like spheres.
   - This sphere visually represents the light source.

4. **`glColor3f(1.0f, 0.0f, 0.0f)`**:
   - Sets the color of the sphere to red (RGB: 1.0, 0.0, 0.0).
   - Note: This color does not affect the actual light emitted by the light source; it's purely visual.

5. **`gluSphere(sphere, .05, 50, 25)`**:
   - Draws a sphere with radius `0.05` and specified resolution (`50` slices, `25` stacks).

6. **`glPopMatrix()`**:
   - Restores the previous transformation matrix (before `glPushMatrix()`). This prevents the sphere's transformation from affecting the rest of the scene.

---

### **Lighting Configuration (with `glEnable(GL_LIGHTING)`):**
This block configures two light sources (`GL_LIGHT0` and `GL_LIGHT1`).

1. **`glEnable(GL_LIGHTING)`**:
   - Enables OpenGL’s lighting calculations. Without this, light sources have no effect on the scene.

2. **Light 0 (`GL_LIGHT0`):**
   - **`GLfloat light_position[] = { .0f, 1.0f, .0f };`**:
     - Sets the position of the light in world space (above the origin at `(0, 1, 0)`).
   - **`glLightfv(GL_LIGHT0, GL_POSITION, light_position);`**:
     - Assigns the position to `GL_LIGHT0`.
   - **`GLfloat light_ambient[] = { .5f, .5f, .5f };`**:
     - Specifies ambient light intensity (dim lighting that fills the space evenly).
   - **`glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);`**:
     - Configures ambient lighting for `GL_LIGHT0`.
   - **`glEnable(GL_LIGHT0)`**:
     - Activates `GL_LIGHT0`.

3. **Light 1 (`GL_LIGHT1`):**
   - **`glLightfv(GL_LIGHT1, GL_POSITION, light_position2);`**:
     - Sets the position of `GL_LIGHT1` to `light_position2`.
   - **`GLfloat light_diff[] = { 1.0f, .0f, .0f };`**:
     - Specifies diffuse light intensity (directional light that affects surfaces based on their orientation).
   - **`glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diff);`**:
     - Configures diffuse lighting for `GL_LIGHT1`.
   - **`glEnable(GL_LIGHT1)`**:
     - Activates `GL_LIGHT1`.

---

### **Material Properties (`glMaterialfv`):**
Materials describe how an object interacts with light. These lines configure the cube's material:

1. **`GLfloat cyDiffColor[] = { 1.0f, 1.0f, 1.0f };`**:
   - Specifies the diffuse reflection color (white).
   - Diffuse reflection depends on the light's color and direction.

2. **`glMaterialfv(GL_FRONT, GL_DIFFUSE, cyDiffColor);`**:
   - Assigns the diffuse color to the front faces of polygons.

3. **`GLfloat cyAmbColor[] = { 1.0f, 1.0f, 1.0f };`**:
   - Specifies the ambient reflection color (white).
   - Ambient reflection is uniform and independent of the light's position or direction.

4. **`glMaterialfv(GL_FRONT, GL_AMBIENT, cyAmbColor);`**:
   - Assigns the ambient color to the front faces of polygons.

---

