# Use Martin Storsjö's llvm-mingw Docker image as the base
FROM mstorsjo/llvm-mingw:dev as llvm-mingw

# Use an official devcontainer base image
FROM mcr.microsoft.com/vscode/devcontainers/cpp:latest

# Copy llvm-mingw from the previous stage and set up environment variables
COPY --from=llvm-mingw /llvm-mingw /opt/llvm-mingw
ENV PATH="/opt/llvm-mingw/bin:${PATH}"
