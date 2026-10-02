Package: libsystemd:x64-linux@260.2#1

**Host Environment**

- Host: x64-linux
- Compiler: GNU 15.2.0
- CMake Version: 4.4.3
-    vcpkg-tool version: 2026-07-27-98d7cb0cf1f4686a3e43aa5672b6230c1d56bce8
    vcpkg-scripts version: unknown

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Found Python version '3.14.4 at /usr/bin/python3'
-- Using meson: /opt/vcpkg/downloads/tools/meson-1.9.0-633807/meson.py
-- Using cached systemd-systemd-v260.2.tar.gz
-- Cleaning sources at /opt/vcpkg/buildtrees/libsystemd/src/v260.2-1a875e5b45.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source /opt/vcpkg/downloads/systemd-systemd-v260.2.tar.gz
-- Applying patch disable-warning-nonnull.patch
-- Applying patch only-libsystemd.patch
-- Applying patch pkgconfig.patch
-- Applying patch fix-2604-build.patch
-- Using source at /opt/vcpkg/buildtrees/libsystemd/src/v260.2-1a875e5b45.clean
-- Setting up python virtual environment...
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: /usr/bin/python3 -I -m venv --symlinks /opt/vcpkg/buildtrees/libsystemd/x64-linux-venv
    Working Directory: /opt/vcpkg/buildtrees/libsystemd
    Error code: 1
    See logs for more information:
      /opt/vcpkg/buildtrees/libsystemd/venv-setup-x64-linux-out.log

Call Stack (most recent call first):
  /home/nux/Developer/study/cpp/school-physics-project/vcpkg_installed/x64-linux/share/vcpkg-get-python-packages/x_vcpkg_get_python_packages.cmake:94 (vcpkg_execute_required_process)
  ports/libsystemd/portfile.cmake:19 (x_vcpkg_get_python_packages)
  scripts/ports.cmake:209 (include)



```

<details><summary>/opt/vcpkg/buildtrees/libsystemd/venv-setup-x64-linux-out.log</summary>

```
The virtual environment was not created successfully because ensurepip is not
available.  On Debian/Ubuntu systems, you need to install the python3-venv
package using the following command.

    apt install python3.14-venv

You may need to use sudo with that command.  After installing the python3-venv
package, recreate your virtual environment.

Failing command: /opt/vcpkg/buildtrees/libsystemd/x64-linux-venv/bin/python3
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "school-physics-project",
  "version": "0.1.0",
  "dependencies": [
    "gtest",
    "opencv"
  ]
}

```
</details>
