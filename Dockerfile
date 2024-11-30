# Stage 1: Build stage
FROM ubuntu:20.04 AS builder

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    g++ \
    curl \
    libcurl4-openssl-dev \
    nlohmann-json3-dev \
    libncurses5-dev \
    git \
    sqlite3 \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Clone and build SQLiteCpp
RUN git clone https://github.com/SRombauts/SQLiteCpp.git \
    && cd SQLiteCpp \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install

# Set the working directory for the build
WORKDIR /app

# Copy project files into the build stage
COPY src/ ./src/
COPY CMakeLists.txt .

# Build the project
RUN cmake -S . -B build/
RUN cd build && make

# Stage 2: Runtime stage
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libcurl4-openssl-dev \
    libncurses5-dev \
    sqlite3 \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy built artifacts from the builder stage
WORKDIR /app
COPY --from=builder /app/build/src /app/build/src
COPY --from=builder /app/build/Mastermind /app/build/Mastermind

# Define the volume for persistent data
VOLUME /app/build/src/data

# Default command
WORKDIR /app/build
CMD ["./Mastermind"]
