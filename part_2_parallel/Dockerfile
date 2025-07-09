# Build stage
FROM debian:bookworm-slim AS build

WORKDIR /src

# Copy project files
COPY CMakeLists.txt .
COPY src ./src

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype6-dev \
    libopenal-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libopenmpi-dev \
    libx11-dev \
    libflac-dev \
    libeigen3-dev && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Enable debug build + fix Eigen3 path without modifying CMakeLists.txt
ENV CMAKE_BUILD_TYPE=Debug

RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_PREFIX_PATH=/usr/include/eigen3 -DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG=on .. && \
    make

# Runtime stage
FROM debian:bookworm-slim AS run

WORKDIR /app

# Copy only the binary
COPY --from=build /src/build/game_of_life /app/game_of_life

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libxrandr2 \
    libxcursor1 \
    libxi6 \
    libudev1 \
    libfreetype6 \
    libvorbis0a \
    libgl1 \
    libegl1 \
    libopenmpi3 \
    openmpi-bin && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /data

# Run the program with MPI (can be overridden in docker run)
ENTRYPOINT ["mpirun", "-n", "2", "/app/game_of_life", "-n", "-r", "16", "-c", "16", "-i", "10"]