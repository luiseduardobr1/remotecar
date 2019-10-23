# Carro Remoto
Carro controlado por comandos remotos via Bluetooth por meio do microcontrolador ARM Cortex-M0

# Integrantes
Luís Eduardo Pompeu de Sousa Brasil Háteras - 378772 \
Tales Araújo dos Santos - 374953 \
Manoel Rubem Amorim - 375272 \
Rômulo Gomes dos Santos - 413383

# Funcionalidade
Como o nome já deixa claro, o projeto consiste na implementação prática de um carro em que seus movimentos, tais como ir para a frente, virar e retroceder, serão controlados remotamente a partir de um aplicativo de celular (Bluetooth SPP) por meio de comandos via Bluetooth. Para isso, será utilizado o módulo HC-06 que receberá os comandos e comunicará por UART ao microcontrolador ARM Cortex-M0 para energizar as bobinas na ordem adequada a fim de movimentar o eixo do motor de passo utilizado. \
\
Para o controle de velocidade, será ajustado por um tempo de *delay* entre os acionamentos de cada bobina do motor respeitando o limite do mesmo, assim, permitindo realizar curvas adequadamente. Apesar da limitação de velocidade dos motores de passo, eles são importantes em aplicações que exigem precisão por isso o interesse em sua utilização. 

# Equipamentos Utilizados
1x ARM Cortex-M0 \
1x HC-06 \
1x ULN2803 \
2x Motores de passo de 12V
