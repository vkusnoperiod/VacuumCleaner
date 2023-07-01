# Указываем базовый образ Linux
FROM ubuntu:latest

# Обновляем список пакетов и устанавливаем необходимые зависимости
RUN apt-get update && \
    apt-get install -y cmake libboost-all-dev libssl-dev zlib1g-dev libcurl4-openssl-dev

# Копируем исходный код проекта в контейнер
COPY . /app

# Переходим в рабочую директорию
WORKDIR /app

# Компилируем проект
RUN cmake .
RUN make

# Указываем команду для запуска бота
CMD ["./main"]

