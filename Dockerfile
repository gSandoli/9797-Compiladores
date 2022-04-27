FROM ubuntu:latest

COPY . /code/

USER root

RUN apt-get update && apt install -y flex bison make cmake clang-format clang-tidy clang-tools clang clangd libc++-dev libc++1 libc++abi-dev libc++abi1 libclang-dev libclang1 liblldb-dev libllvm-ocaml-dev libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm python3-clang

ENTRYPOINT ["tail"]

CMD ["-f","/dev/null"]