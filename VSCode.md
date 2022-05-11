# How to use VSCode with Arduino

1. Have Arduino installed.  This is straightforward on Windows and OS-X.  On Linux, download the tarball and extract it to `/opt`, e.g.,
    ```bash
    sudo tar -C /opt -xJvf arduino-1.8.19-linux64.tar.xz
    ```

2. In VS Code, hit `<Ctrl+Shift+X>`, search for, and install:
    * `vscode-arduino`

3. *Linux*: Hit `<Ctrl+,>` to load up settings, click the "Open Settings (JSON)" button at the top-right, and add the following (version number may be different for you):
    ```json
    "arduino.path": "/opt/arduino-1.8.19",
    "arduino.commandPath": "arduino"
    ```

4. Close VS Code
5. Open this sketch's directory in VS Code, then open `decombo.ino`
6. On the bottom bar, you'll see `<Select Board>`, click it and pick your board (or any board, really).
7. Verify / compile the `ino` file by pressing `<Ctrl+Alt+R>`.

At this point, VSCode should be set up to work on Arduino code.  You'll get redlines, be able to `<F2>` rename identifiers, `<F12>` lookup definitions, `<Shift+F12>` find references, auto-manage git stuff, etc.