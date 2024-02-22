# Use an official devcontainer base image
FROM mcr.microsoft.com/vscode/devcontainers/cpp:latest

# Install MinGW, make, and cppcheck
RUN apt-get update && apt-get install -y \
    mingw-w64 \
    && rm -rf /var/lib/apt/lists/*

# Set the default shell to bash instead of sh
SHELL ["/bin/bash", "-c"]