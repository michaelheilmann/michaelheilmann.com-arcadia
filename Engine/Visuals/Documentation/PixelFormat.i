<section class="cxx entity enumeration">
<h1 id="Arcadia_Visuals_PixelFormat">Arcadia_Visuals_PixelFormat</h1>
<my-signature><code>
typedef enum Arcadia_Visuals_PixelFormat Arcadia_Visuals_PixelFormat;
</code></my-signature>

<my-summary>
An enumeration of pixel formats.
</my-summary>

<section class="cxx enumeration-elements">

  <h1>Elements</h1>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_An8Ln8</code>
    </div>
    <div>
    Two Arcadia_Natural8Value values layout out consecutively in memory.
    The first value denotes the intensity of the alpha component.
    The second value denotes the intensity of the luminance component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8</code>
    </div>
    <div>
    Four Arcadia_Natural8Value values layed out consecutively in memory.
    The first value denotes the intensity of the alpha component.
    The second value denotes the intensity of the blue component,
    the third value denotes the intensity of the green component, and
    the fourth value denotes the intensity of the red component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8</code>
    </div>
    <div>
    Four Arcadia_Natural8Value values layed out consecutively in memory.
    The first value denotes the intensity of the alpha component.
    The second value denotes the intensity of the red component,
    the third value denotes the intensity of the green component, and
    the fourth value denotes the intensity of the blue component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8</code>
    </div>
    <div>
    Three Arcadia_Natural8Value values layed out consecutively in memory.
    The first value denotes the intensity of the blue component,
    the second value denotes the intensity of the green component, and
    the third value denotes the intensity of the red component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8</code>
    </div>
    <div>
    Four Arcadia_Natural8Value values layed out consecutively in memory.
    The first value denotes the intensity of the blue component,
    the second value denotes the intensity of the green component, and
    the third value denotes the intensity of the red component.
    The fourth value denotes the intensity of the alpha component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_Ln8</code>
    </div>
    <div>
    One Arcadia_Natural8Value value.
    The value denotes the intensity of the luminance component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_Ln8An8</code>
    </div>
    <div>
    Two Arcadia_Natural8Value values layout out consecutively in memory.
    The first value denotes the intensity of the luminance component.
    The second value denotes the intensity of the alpha component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8</code>
    </div>
    <div>
    Three Arcadia_Natural8Value values layed out consecutively in memory.
    The first value denotes the intensity of the red component,
    the second value denotes the intensity of the green component, and
    the third value denotes the intensity of the blue component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

  <div>
    <div>
      <code>Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8</code>
    </div>
    <div>
    Four Arcadia_Natural8Value values layed out consecutively in memory.
    The first value denotes the intensity of the red component,
    the second value denotes the intensity of the green component, and
    the third value denotes the intensity of the blue component.
    The fourth value denotes the intensity of the alpha component.
    A component value of 0 indicates least intensity.
    A component value of 255 indicates greatest intensity.
    </div>
  </div>

</section>

</section>
