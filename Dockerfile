#
# Dockerfile for cpuminer
#
# Usage:
#       docker run cpuminer [parameters]
#
# Examples:
#
# 1. Direct connection to node using the getblocktemplate method
#    docker run cpuminer --url http://a.paicoin.node:19566 --user user --pass password --coinbase-addr McvP9ELi7SN4rE2JU5X9E2h7txQyH7nUQd --algo paicoin
#
# 2. Connection to the mining pool via the Stratum protocol
#    docker run cpuminer --url stratum+tcp://a.paicoin.mining.pool:3052 --user user --pass password --algo paicoin
#

FROM            ubuntu:16.04

RUN             apt-get update -qq && \
                apt-get install -qqy pkg-config m4 automake autogen autoconf libcurl4-openssl-dev make gcc

# RUN             git clone https://github.com/projectpai/cpuminer
COPY            cpuminer.tar.gz /tmp/cpuminer.tar.gz

RUN             mkdir cpuminer && \
                tar xfz /tmp/cpuminer.tar.gz --strip 1 -C cpuminer && \
                cd cpuminer && \
                ./autogen.sh && \
                ./configure CFLAGS="-O3" && \
                gcc --version && \
                make

WORKDIR         /cpuminer
ENTRYPOINT      ["./minerd"]
