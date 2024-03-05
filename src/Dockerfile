FROM ubuntu
WORKDIR /home
COPY test .
RUN apt update && apt install valgrind make -y
ENTRYPOINT valgrind --tool=memcheck --leak-check=yes test