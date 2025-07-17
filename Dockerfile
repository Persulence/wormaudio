FROM debian:trixie
LABEL authors="persulence"

RUN apt-get update && \
    apt-get install -y build-essential cmake pkg-config swig openjdk-21-jdk default-jdk ninja-build libfreetype-dev

COPY lib /app/lib
COPY player /app/player
COPY wormaudio-editor/src /app/src
#COPY res /app/res
#COPY CMakeLists.txt /app

WORKDIR /app/player

#ENV JAVA_HOME=/usr/lib/jvm/openjdk-17-amd64
#ENV JAVA_INCLUDE_PATH=/usr/lib/jvm/openjdk-17-amd64/include

RUN mkdir build
WORKDIR build
RUN cmake .. -G Ninja -DJUCE_MODULES_ONLY=ON -DCMAKE_CXX_FLAGS="-std=c++20 -w"
RUN ninja -j"$(nproc)"

#RUN mkdir build && cd build && \
#    cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ && \
#    ninja -j "$(nproc)" && \

#ENTRYPOINT ["ls", "-la"]

