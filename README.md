# IoT-GS

# SolarTracker <img src="documentacao/solartracker.png" alt="SolarTracker" width="35" height="35" /> 

˖°☀️💡 ***Ilumine com energia solar e faça a diferença para o planeta.*** <img width="30" height="30" src="https://img.icons8.com/external-nawicon-flat-nawicon/64/external-solar-panel-energy-nawicon-flat-nawicon-2.png" alt="external-solar-panel-energy-nawicon-flat-nawicon-2"/> ࿐࿔

<br>

# Integrantes
    RM: 551401  Turma: 2TDSPF  Nome: Ana Luiza Fontes 
    RM: 86293   Turma: 2TDSA   Nome: João Vito
    RM: 550128  Turma: 2TDSA   Nome: Marco Antônio
    RM: 552408  Turma: 2TDSA   Nome: Leonardo Bruno
    RM: 99343   Turma: 2TDSA   Nome: Vinicius Andrade

<br>

# Sobre o Projeto
SolarTracker é a plataforma digital que te coloca no controle da sua energia solar, oferecendo monitoramento em tempo real para quem já possui placas solares, revelando como pode economizar e contribuir para um desenvolvimento mais sustentável através de gráficos durante os meses. Já para pessoas que ainda não possuem placas solares, terá cálculos personalizados de acordo com o consumo de kW mensal, comparando o custo da energia costumeira com a economia que você terá com placas solares e ajudar na transição para um futuro mais sustentável.

<br>

# Funcionalidade do IoT 
O arduino coleta dados de consumo de energia da residência e transmite para o aplicativo, gerando gráficos intuitivos para comparar o consumo de energia costumeira com o da energia das placas solares e veja o impacto positivo da energia solar na conta de luz.


<br>

# Instruções

Video de demonstração de como rodar no vs code [Demonstração](https://youtu.be/u3UUbkoHH0w/)

## Abrindo o projeto
1. Clone o repositorio no VS Code.
2. Instale a extensao PlatformIO e WokWi no VS Code.
3. No projeto, va para o src e abra para acessar o codigo. 
4. Com as extensoes baixadas, compile o projeto apertando no check no canto inferior esquerdo.
   <br>
   <img src="documentacao/Compilando.jpeg" alt="Compilando Projeto" />
   <br>
6. Va para o arquivo wokwi.toml.
7. Mude o que esta dentro do firmware e elf para o que apareceu no terminal com final .bin para o elf e .elf para o firmware.
   <br>
   <img src="documentacao/wokwitoml.jpeg" alt="Modificando o wokwi.toml" />
   <br>
   <img src="documentacao/modificando.jpeg" alt="wokwi.toml modificado" />
9. Aperte ctrl + shit + p e procure Wokwi Start simulation ou para mac aperte cmd + shit + p.
10. Rodar o Iot e testa-lo.




<br>
