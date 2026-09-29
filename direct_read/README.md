# Считывание прошивки напрямую с Flash-памяти
![подключение](https://github.com/trimesh33/r3dc4t/blob/main/direct_read/img1.jpg)

Выпаяли флешку W25Q16JV с платы и припаяли лакированным проводом 0.2мм к Arduino.
![кишки](https://github.com/trimesh33/r3dc4t/blob/main/direct_read/img2.jpg)

[Исходный код](https://github.com/trimesh33/r3dc4t/blob/main/direct_read/direct_read.ino)

# Подключение
Используются делители напряжения для согласования уровней 5в-3.3в. 
![схема](https://github.com/trimesh33/r3dc4t/blob/main/direct_read/schematic.jpg)

# Итоги
С baud rate 115200 весь бинарник передается примерно за минуту. Был получен бинарник, идентичный слитому через pico-tools.