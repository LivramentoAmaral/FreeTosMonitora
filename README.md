

# 📌 Controle de LED com Botão usando FreeRTOS no Raspberry Pi Pico  

## 📝 Descrição  

Este projeto implementa um sistema de controle de LED utilizando um botão no microcontrolador **Raspberry Pi Pico**. O sistema usa o **FreeRTOS** para gerenciar tarefas que monitoram o estado do botão e controlam o LED com base nas interações do usuário.  

---

## 🛠️ Componentes Utilizados  

- **🖥️ Microcontrolador:** Raspberry Pi Pico  
- **💡 LED:** Conectado ao pino **12**  
- **🔘 Botão:** Conectado ao pino **6** (com **pull-up interno** ativado)  
- **⚙️ Sistema Operacional:** FreeRTOS para gestão das tarefas  

---

## ⚡ Funcionamento  

O código implementa **três tarefas principais** para gerenciar o botão e o LED:  

### 📌 1. ButtonTask  
➡️ Monitora o estado do botão e atualiza uma variável global (`buttonState`).  

### 📌 2. LedTask  
➡️ Controla o LED, ligando-o e desligando-o quando recebe uma notificação.  

### 📌 3. ProcessTask  
➡️ Verifica o estado do botão e **envia notificações** para `LedTask` quando o botão é pressionado.  

---

## 📂 Estrutura do Código  

### 🔧 Configuração dos Pinos  

✅ **LED:** Configurado como **saída**.  
✅ **Botão:** Configurado como **entrada** com resistor de **pull-up** ativado.  

### 🔄 Tarefas FreeRTOS  

✅ **ButtonTask:** Lê continuamente o estado do botão.  
✅ **LedTask:** Liga e desliga o LED baseado em notificações.  
✅ **ProcessTask:** Verifica o estado do botão e envia notificações para `LedTask`.  

### 🚀 Execução do FreeRTOS  

O **escalonador do FreeRTOS** é iniciado para gerenciar as tarefas em tempo real.  

---

## ⚙️ CMakeLists.txt  

O arquivo `CMakeLists.txt` é utilizado para configurar o **ambiente de compilação** do projeto.  

### 🔹 Definição da Versão do CMake  

```cmake
cmake_minimum_required(VERSION 3.13)
```

### 🔹 Configuração do Projeto e do Compilador  

```cmake
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
```

### 🔹 Importação do SDK do Raspberry Pi Pico e FreeRTOS  

```cmake
include(pico_sdk_import.cmake)
include($ENV{FREERTOS_KERNEL_PATH}/home/marcos-amaral/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
```

### 🔹 Criação do Executável  

```cmake
add_executable(monitoramento_led monitoramento_led.c)
```

### 🔹 Configuração das Bibliotecas e Linkagem  

```cmake
target_link_libraries(monitoramento_led
     pico_stdlib
     FreeRTOS-Kernel
     FreeRTOS-Kernel-Heap4)
```

### 🔹 Habilita Saída via USB  

```cmake
pico_enable_stdio_usb(monitoramento_led 1)
```

---

## ▶️ Como Compilar e Executar  

1️⃣ Instale o **SDK do Raspberry Pi Pico** e o **FreeRTOS**.  
2️⃣ Compile o código usando **CMake** e **Make**:  

   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

3️⃣ Carregue o binário gerado na **Raspberry Pi Pico**.  

---

## 🚀 Possíveis Melhorias  

✅ **Implementar debounce** por software para evitar leituras instáveis do botão.  
✅ **Adicionar uma segunda entrada** para um novo botão e expandir as funcionalidades.  
✅ **Integrar com um display OLED** para exibir o estado do botão e do LED.  

---

Agora seu **README** segue um padrão bem estruturado, organizado e visualmente agradável! Se precisar de mais ajustes, é só avisar. 🚀😃
