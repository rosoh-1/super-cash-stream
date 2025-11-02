FROM gcc:13

WORKDIR /app
COPY simulator.cpp .

RUN g++ -std=c++17 -O2 simulator.cpp -o simulator

RUN mkdir -p /data && chmod 777 /data

CMD ["./simulator"]

