# Use an official devcontainer base image
FROM devcontainers/cpp:latest

# Install MinGW, make, and cppcheck
RUN apt-get update && apt-get install -y \
    gcc-mingw-w64 \
    && rm -rf /var/lib/apt/lists/*

# Set the default shell to bash instead of sh
SHELL ["/bin/bash", "-c"]
