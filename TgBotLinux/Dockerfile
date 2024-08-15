# Использование официального образа Ubuntu
FROM ubuntu:latest

# Установка необходимых пакетов и зависимостей
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    ninja-build \
    libcurl4-openssl-dev \
    libboost-all-dev \
    libssl-dev \
    libjsoncpp-dev \
    git

# Клонирование и сборка tgbot-cpp
RUN git clone https://github.com/reo7sp/tgbot-cpp.git \
    && cd tgbot-cpp \
    && cmake -GNinja . \
    && ninja install

# Копирование исходного кода вашего приложения
COPY . /app

# Переход в директорию приложения
WORKDIR /app

# Создание директории build и сборка вашего приложения с использованием ninja
RUN mkdir build && cd build \
    && cmake -GNinja .. \
    && ninja

# Команда для запуска вашего приложения
CMD ["./build/MyTgBotNew"]
