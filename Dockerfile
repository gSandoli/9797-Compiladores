FROM ubuntu:latest

COPY . /code/

USER root

RUN apt update && apt install -y flex bison make cmake clang

ENTRYPOINT ["tail"]

CMD ["-f","/dev/null"]