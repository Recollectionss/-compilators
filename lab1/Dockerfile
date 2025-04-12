FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    clang-3.9 \
    g++-3.9 \
    make \
    wget \
    curl \
    file \
    zsh \
    && apt-get clean

WORKDIR /project

COPY ./dragon-tiger /project/dragon-tiger
COPY ./setup_tiger.sh /project/setup_tiger.sh

RUN chmod +x /project/setup_tiger.sh

CMD ["/bin/bash"]

