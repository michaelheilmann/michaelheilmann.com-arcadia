  <h2>Further references</h2>
  <p>There is a demo available showing-off how to use R1</p>
  <ul>
    <li><a href="https://michaelheilmann.com/repository/r1/demos/helloworld/configure.h.i">demos/r1/demos/helloworld/configure.h.i</a></li>
    <li><a href="https://michaelheilmann.com/repository/r1/demos/helloworld/main.c">demos/r1/demos/helloworld/main.c</a></li>
    <li><a href="https://michaelheilmann.com/repository/r1/demos/helloworld/CMakeLists.txt">demos/r1/demos/helloworld/CMakeLists.txt</a></li>
  </ul>
  <p>
  which compiles and runs under various platforms (including but not restricted to Windows, Linux, and many more).
  To build the demo, simply download the files of the demo to some directory (called the demo directory).
  Download the files of <a href="https://michaelheilmann.com/repository/arms1">ARMS1</a> to a directory (called the ARMS1 directory).
  Download the files of R1 to a directory (called the R1 directory).
  Invoke from the demo directory</p>
  <p><code>
  cmake -R1-Source-Dir=<my-mv>r1 source directory</my-mv> -DArms1-Source-Dir=<my-mv>arms1 source directory</my-mv> .
  </code></p>
  <p>where</p>
  <ul>
    <li><my-mv>r1 source directory</my-mv> is the path to the R1 directory</li>
    <li><my-mv>arms1 source directory</my-mv> is the path to a the ARMS1 directory</li>
  </ul>
  <p>Note that relative paths are interpreted relative to <code>${CMAKE_CURRENT_BINARY_DIR}</code>.</p>
