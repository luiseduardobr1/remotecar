# Carro Remoto
Carro controlado por comandos remotos via Bluetooth por meio do microcontrolador ARM Cortex-M0

# Integrantes
Luís Eduardo Pompeu de Sousa Brasil Háteras - 378772 \
Tales Araújo dos Santos - 374953 \
Manoel Rubem Amorim - 375272 \
Rômulo Gomes dos Santos - 413383

# Funcionalidade
Como o nome já deixa claro, o projeto consiste na implementação prática de um carro em que seus movimentos, tais como ir para a frente, virar e retroceder, serão controlados remotamente a partir de um aplicativo de celular (Bluetooth SPP) por meio de comandos via Bluetooth. Para isso, será utilizado o módulo HC-06 que receberá os comandos e se comunicará via UART ao microcontrolador ARM Cortex-M0, o qual energizará as bobinas na ordem adequada a fim de movimentar o eixo dos motores de passo utilizados. \
\
Para o controle da velocidade, será ajustado um tempo de *delay* entre os acionamentos de cada bobina do motor, respeitando o limite do mesmo. Para nossa aplicação, a precisão dos movimentos é mais importante e por isso o interesse na utilização dos motores de passo uma vez que para velocidades maiores seria mais oportuno a utilização de motores DC. \
\
Além disso, utiliza-se o CI [ULN2803](http://www.ti.com/lit/ds/symlink/uln2803a.pdf) que atua como uma [configuração de Darlington](https://en.wikipedia.org/wiki/Darlington_transistor) dando um ganho na corrente de entrada de modo a ser capaz de movimentar o eixo do motor. 

# Equipamentos Utilizados
1x ARM Cortex-M0 \
1x HC-06 \
1x ULN2803 \
2x Motores de passo de 12V

# Diagrama de Blocos
![modelo](https://user-images.githubusercontent.com/56649205/67427909-7311ac80-f5b3-11e9-8e2c-abb0defb1b24.png)

# Pinagem
A1,B1, A2, B2, \A1, \B1, \A2, \B2 consistem nas entradas para a sequência de energização das bobinas, como mostrado nas figuras a seguir.

![pinagem-enviar](https://user-images.githubusercontent.com/56649205/67429677-0ac4ca00-f5b7-11e9-8249-ad337fdbcdf3.jpg)

![pinagem-uln](https://user-images.githubusercontent.com/56649205/67430034-cbe34400-f5b7-11e9-9ed2-30522354549f.PNG)

# Lógica
**Ir para frente**
Ambas as rodas devem girar em sentidos opostos para isso, considerando a energização das bobinas por passo pleno, deve-se energizar na seguinte ordem:\
Motor 1:\
A1 e B1 = 1 \
(delay)
