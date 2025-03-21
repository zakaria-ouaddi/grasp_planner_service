# Grasp Planner Service

This service node is responsible for generating grasp poses for a given object. It uses the [Simox](https://git.h2t.iar.kit.edu/sw/simox/simox) library provided by the Hochperformante Humanoide Technologien (H²T) group at the Karlsruhe Institute of Technology (KIT) to generate the grasp poses -- or rather this fork [here](https://github.com/cram2/Simox).

## Installation

The grasp planner service is written for ROS 2 Jazzy running on Ubuntu 24.04 and requires the Simox library installed and the path to the library set in the `Simox_DIR` environment variable. To install Simox follow the instructions in the [Simox fork repository](https://github.com/cram2/Simox) and set the environment variable in your `.bashrc` or `.zshrc` file.

```bash
export Simox_DIR=${HOME}/local/src/simox/build
```

Since Simox isn't written for Ubuntu 24.04 there is a dependency conflict in `liburdfdom_model`, because Simox uses `liburdfdom_model.so.1.0` and ROS 2 uses `liburdfdom_model.so.4.0`. To resolve this conflict, the `liburdfdom_model.so.1.0` can be installed from source. When it's installed in `/usr/local/lib` create a symlink to it in the directory `/usr/lib/x86_64-linux-gnu/`.

```bash
sudo ln -s /usr/local/lib/liburdfdom_model.so /usr/lib/x86_64-linux-gnu/liburdfdom_model.so
```
