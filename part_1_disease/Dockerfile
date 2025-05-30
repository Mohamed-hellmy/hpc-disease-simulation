FROM debian:bookworm-slim AS build

WORKDIR /src 
COPY CMakeLists.txt /src
COPY simulation /src/simulation
COPY include /src/include 
RUN apt-get update && apt-get install -y build-essential cmake && apt-get clean

WORKDIR /src/build 
RUN cmake .. && make

FROM debian:bookworm-slim AS run 

WORKDIR /app
COPY --from=build /src/build/main_exec /app
COPY --from=build /src/build/test /app
COPY --from=build /src/build/test_disease /app
COPY --from=build /src/build/test_person /app
COPY --from=build /src/build/test_population /app
COPY --from=build /src/build/test_touch /app


RUN /app/test && \
    /app/test_disease && \
    /app/test_person && \
    /app/test_population && \
    /app/test_touch

WORKDIR /scratch

ENTRYPOINT ["/app/main_exec"]