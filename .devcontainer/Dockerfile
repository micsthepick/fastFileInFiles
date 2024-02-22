# Use an official devcontainer base image
FROM devcontainers/cpp:latest

# Install MinGW, make, and cppcheck
RUN apt-get update && apt-get install -y \
    gcc-mingw-w64 \
    && rm -rf /var/lib/apt/lists/*

# Set the default shell to bash instead of sh
SHELL ["/bin/bash", "-c"]

# Create a 'vscode' user to match the expected user by the devcontainer configuration
# Replace '1000' with the desired UID and GID to match your host system if necessary
RUN groupadd --gid 1000 vscode \
    && useradd --uid 1000 --gid vscode --shell /bin/bash --create-home vscode

# Optionally, set the user to 'vscode' to avoid running commands as root
USER vscode