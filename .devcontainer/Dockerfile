# Use an official devcontainer base image
FROM mcr.microsoft.com/vscode/devcontainers/cpp:latest

# Download and extract llvm-mingw in one RUN command
RUN curl -L https://github.com/mstorsjo/llvm-mingw/releases/download/20231128/llvm-mingw-20231128-ucrt-ubuntu-20.04-x86_64.tar.xz | tar -xJ -C /opt

# Set up environment variables
ENV PATH="/opt/llvm-mingw-20231128-ucrt-ubuntu-20.04-x86_64/bin:${PATH}"
