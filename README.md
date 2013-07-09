v4l-diagnostics
===============

V4L testing/diagnosing tools

Building
--------

From the top-level directory type `make`.

Assumption is that OpenCV headers are installed in

    /usr/include/opencv
    /usr/include/opencv2

And OpenCV libraries are in the default library search path.

OpenCV Dependency
-----------------

### Ubuntu Package ###

```Shell
sudo add-apt-repository ppa:gijzelaar/opencv2.4
sudo apt-get update
sudo apt-get install libopencv-dev
```
