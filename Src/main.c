/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

// Modo de operação do pino
int modo_do_pino;
	
// Equivalência de pinos
unsigned int equivalencia [21][2]={
	{0, 0}, 				// Pino 0
	{0, 0}, 			    // Pino 1
	{GPIOF, GPIO_PIN_0}, 	// Pino 2
	{GPIOF, GPIO_PIN_1}, 	// Pino 3
	{0, 0}, 				// Pino 4
	{0, 0},			    	// Pino 5
	{GPIOA, GPIO_PIN_0}, 	// Pino 6
	{GPIOA, GPIO_PIN_1}, 	// Pino 7
	{GPIOA, GPIO_PIN_2}, 	// Pino 8
	{GPIOA, GPIO_PIN_3}, 	// Pino 9
	{GPIOA, GPIO_PIN_4}, 	// Pino 10
	{GPIOA, GPIO_PIN_5}, 	// Pino 11
	{GPIOA, GPIO_PIN_6}, 	// Pino 12
	{GPIOA, GPIO_PIN_7}, 	// Pino 13
	{GPIOB, GPIO_PIN_1}, 	// Pino 14
	{0,0}, 					// Pino 15
	{0,0}, 					// Pino 16
	{GPIOA, GPIO_PIN_9}, 	// Pino 17
	{GPIOA, GPIO_PIN_10},	// Pino 18
	{0,0}, 					// Pino 19
	{0,0}, 					// Pino 20
};


GPIO_TypeDef *p1;


// Função de delay em milisegundos
void delay(unsigned long ms) {
	HAL_Delay(ms);
}


/**
 * @brief Define modos de operação para os pinos.
 * 
 * @param pino Número do pino
 * @param modo Modo de operação: 0 - output; 1 - input; 2 - input com resistor de pull-up
 */
void pinMode(int pino, int modo) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	p1 = (GPIO_TypeDef *)equivalencia[pino][0];

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	if (modo == 0) {
		HAL_GPIO_WritePin(p1, equivalencia[pino][1], GPIO_PIN_RESET);
		GPIO_InitStruct.Pin = equivalencia[pino][1];
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(p1, &GPIO_InitStruct);
		modo_do_pino = 0;
	}

	if (modo == 1) {
		GPIO_InitStruct.Pin = equivalencia[pino][1];
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(p1, &GPIO_InitStruct);
		modo_do_pino = 1;
	}
	if (modo == 2) {
		GPIO_InitStruct.Pin = equivalencia[pino][1];
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(p1, &GPIO_InitStruct);
		modo_do_pino = 2;
	}
}


/**
 * @brief Escreve o valor lógico no pino fornecido
 * 
 * @param pino Número do pino
 * @param valor Valor lógico: 0 (LOW) ou 1 (HIGH)
 */
void digitalWrite(int pino, int valor) {
	p1 = (GPIO_TypeDef *)equivalencia[pino][0];

	if (valor == 1) {
		p1->BSRR |= equivalencia[pino][1];
	}
	else {
		p1->BRR |= equivalencia[pino][1];
	}
}


/**
 * @brief Obtém o valor lógico do pino fornecido;
 * 
 * @param pino Número do pino
 * 
 * @returns Valor lógico: 0 (LOW) ou 1 (HIGH)
 */
int digitalRead(int pino) {
	int bit_lido;

	p1 = (GPIO_TypeDef *)equivalencia[pino][0];

	bit_lido = HAL_GPIO_ReadPin(p1, equivalencia[pino][1]);

	return bit_lido;
}



void rodaD(int intervalo) {
	//Começa com todas as bobinas desenergizadas
	digitalWrite(2, 0);
	digitalWrite(3, 0);
	digitalWrite(6, 0);
	digitalWrite(7, 0);

	//Pinos 2 - 7
	digitalWrite(2, 1);
	digitalWrite(7, 1);
	delay(intervalo);

	//Pinos 7 - 6
	digitalWrite(2, 0);
	digitalWrite(6, 1);
	delay(intervalo);

	//Pinos 6 - 3
	digitalWrite(7, 0);
	digitalWrite(3, 1);
	delay(intervalo);

	//Pinos 3 - 2
	digitalWrite(6, 0);
	digitalWrite(2, 1);
	delay(intervalo);
}

/**
 * @brief Define os pinos de modo a mover o carro para a frente
 * 
 * @param intervalo Valor definido para o delay de transição para a nova configuração de 
 * energização das bobinas
 */
void frente(int intervalo) {
	digitalWrite(2, 0);
	digitalWrite(3, 0);
	digitalWrite(6, 0);
	digitalWrite(7, 0);
	digitalWrite(10, 0);
	digitalWrite(11, 0);
	digitalWrite(12, 0);
	digitalWrite(13, 0);

	//Pinos ativos: 2, 7, 10, 11
	digitalWrite(2, 1);
	digitalWrite(7, 1);
	digitalWrite(10, 1);
	digitalWrite(11, 1);
	delay(intervalo);

	//Pinos ativos: 7, 6, 11, 12
	digitalWrite(2, 0);
	digitalWrite(6, 1);
	digitalWrite(10, 0);
	digitalWrite(12, 1);
	delay(intervalo);

	//Pinos ativos: 6, 3, 12, 13
	digitalWrite(7, 0);
	digitalWrite(3, 1);
	digitalWrite(11, 0);
	digitalWrite(13, 1);
	delay(intervalo);

	//Pinos ativos: 3, 2, 13, 10
	digitalWrite(6, 0);
	digitalWrite(2, 1);
	digitalWrite(12, 0);
	digitalWrite(10, 1);
	delay(intervalo);
}


/**
 * @brief Define os pinos de modo a mover o carro para trás
 * 
 * @param intervalo Valor definido para o delay de transição para a nova configuração de 
 * energização das bobinas
 */
void tras(int intervalo) {
	digitalWrite(2, 0);
	digitalWrite(3, 0);
	digitalWrite(6, 0);
	digitalWrite(7, 0);
	digitalWrite(10, 0);
	digitalWrite(11, 0);
	digitalWrite(12, 0);
	digitalWrite(13, 0);

	//Pinos 2, 3, 10, 13
	digitalWrite(2, 1);
	digitalWrite(3, 1);
	digitalWrite(10, 1);
	digitalWrite(13, 1);
	delay(intervalo);

	//Pinos 3, 6, 13, 12
	digitalWrite(2, 0);
	digitalWrite(6, 1);
	digitalWrite(10, 0);
	digitalWrite(12, 1);
	delay(intervalo);

	//Pinos 6, 7, 12, 11
	digitalWrite(3, 0);
	digitalWrite(7, 1);
	digitalWrite(13, 0);
	digitalWrite(11, 1);
	delay(intervalo);

	//Pinos 7, 2, 11, 10
	digitalWrite(6, 0);
	digitalWrite(2, 1);
	digitalWrite(12, 0);
	digitalWrite(10, 1);
	delay(intervalo);
}


/**
 * @brief Define os pinos de modo a mover o carro para a direita.
 * 
 * @param intervalo Valor definido para o delay de transição para a nova configuração de 
 * energização das bobinas
 */
void virarD(int intervalo) {
	digitalWrite(2,0);
	digitalWrite(3,0);
	digitalWrite(6,0);
	digitalWrite(7,0);
	digitalWrite(10,0);
	digitalWrite(11,0);
	digitalWrite(12,0);
	digitalWrite(13,0);

	//Pino 10-13
	digitalWrite(10, 1);
	digitalWrite(13, 1);
	delay(intervalo);

	//Pinos 13-12
	digitalWrite(10, 0);
	digitalWrite(12, 1);
	delay(intervalo);

	//Pinos 12-11
	digitalWrite(13, 0);
	digitalWrite(11, 1);
	delay(intervalo);

	//Pinos 11-10
	digitalWrite(12, 0);
	digitalWrite(10, 1);
	delay(intervalo);
}


/**
 * @brief Define os pinos de modo a mover o carro para a esquerda
 * 
 * @param intervalo Valor definido para o delay de transição para a nova configuração de 
 * energização das bobinas
 */
void virarE(int intervalo) {
	digitalWrite(2, 0);
	digitalWrite(3, 0);
	digitalWrite(6, 0);
	digitalWrite(7, 0);
	digitalWrite(10, 0);
	digitalWrite(11, 0);
	digitalWrite(12, 0);
	digitalWrite(13, 0);

	//Pinos 2, 3, 10, 13
	digitalWrite(2, 1);
	digitalWrite(3, 1);
	delay(intervalo);

	//Pinos 3, 6, 13, 12
	digitalWrite(2, 0);
	digitalWrite(6, 1);
	delay(intervalo);

	//Pinos 6, 7, 12, 11
	digitalWrite(3, 0);
	digitalWrite(7, 1);
	delay(intervalo);

	//Pinos 7, 2, 11, 10
	digitalWrite(6, 0);
	digitalWrite(2, 1);
	delay(intervalo);
}



/* Private user code ---------------------------------------------------------*/
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

 // MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /*
  	Inicia o ponteiro com um endereço de memória que será
  	alterado pela transmissão UART
  */
  char valor;
  char comando[] = "b";
  unsigned char *p2;
  p2 = &comando;
  int bitlido;
  int precisao;

  // Configurando os pinos - output

  // Roda direita - pinos 2, 3, 6 e 7
  pinMode(2, 0);
  pinMode(17, 0);
  pinMode(3, 0);
  pinMode(6, 0);
  pinMode(7, 0);

  // Roda esquerda - pinos 10, 11, 12 e 13
  pinMode(10, 0);
  pinMode(11, 0);
  pinMode(12, 0);
  pinMode(13, 0);
  pinMode(18, 0);
  pinMode(14, 0);

  precisao = 25;

  while (1)
  {
	  HAL_UART_Receive(&huart1, p2, 1, 10);
	  valor = *p2;

	  if (valor == '1') {
		//frente(5);
		tras(5);
		// for (int i=0;i<=precisao;i++)
		//{
		//rodaD(5);
		//	  frente(1);
		// }
	  }
	  if (valor == '2') {
		// for (int i=0;i<=precisao;i++)
		//{
		//rodaD(5);
		virarD(5);
		//}
	  }
	  if (valor == '3') {
		//for (int i=0;i<=precisao;i++)
		//{
		//rodaD(5);
		frente(5);
		//}
	  }
	  if (valor == '4') {
		// for (int i=0;i<=precisao;i++)
		//	  {
		//rodaD(5);
		virarE(5);
		//}
	  }
	  if (valor == '5') {
	  	digitalWrite(2, 0);
		digitalWrite(3, 0);
		digitalWrite(6, 0);
		digitalWrite(7, 0);
		digitalWrite(10,0);
		digitalWrite(11, 0);
		digitalWrite(12, 0);
		digitalWrite(13, 0);
		digitalWrite(18, 0);
	  }
	  if (valor=='6') {
		digitalWrite(18, 1);
		delay(500);
		digitalWrite(18, 0);
	  }

	  //if (*p2=='1')
	  //{
	//	  HAL_UART_Transmit ( &huart1, p2, 1, HAL_MAX_DELAY);
	//  }
	//  HAL_UART_Transmit (&huart1, p2, 1, HAL_MAX_DELAY);
  }

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
