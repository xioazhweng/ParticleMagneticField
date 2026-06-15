# ParticleMagneticField

Небольшая программа, которая моделирует движение заряженной частицы в трёхмерном магнитном поле. Написана на C++ с использованием OpenGL и ImGui.

![view](https://github.com/xioazhweng/ParticleMagneticField/blob/main/preview/1.png?raw=true)



## Зависимости

Для сборки проекта необходимы:

- **CMake** ≥ 3.10
- **Компилятор с поддержкой C++17**
- **OpenGL**
- **GLFW3**
- **GLEW** 
- **ImGui** 


## Сборка

```bash
# Клонируем репозиторий
git clone https://github.com/xioazhweng/ParticleMagneticField.git
cd ParticleMagneticField

# Создаём директорию для сборки
mkdir build
cd build

# Конфигурируем проект
cmake ..

# Собираем
make 
```

## Запуск

После успешной сборки исполняемый файл находится в `build/`. Запуск:

```bash
./app
```

## Управление

Программа использует ImGui для отображения интерфейса. В окне можно настраивать параметры магнитного поля и наблюдать за траекторией частицы в реальном времени.

