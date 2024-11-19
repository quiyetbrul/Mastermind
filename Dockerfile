# Use an official Ubuntu as a parent image
FROM ubuntu:20.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
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

# Clone SQLiteCpp repository and install it
RUN git clone https://github.com/SRombauts/SQLiteCpp.git \
    && cd SQLiteCpp \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install

# Set the working directory
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY src/ ./src/
COPY makerun.sh .
COPY CMakeLists.txt .

# Make the script executable
RUN chmod +x makerun.sh

# Run the script to build and run the project
CMD ["./makerun.sh"]
