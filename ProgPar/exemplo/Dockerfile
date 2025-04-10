FROM gcc:latest

RUN apt-get update && \
    apt-get install -y libomp-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY exemplo.c .

RUN gcc -fopenmp -o exemplo exemplo.c

ENTRYPOINT ["./exemplo"]
