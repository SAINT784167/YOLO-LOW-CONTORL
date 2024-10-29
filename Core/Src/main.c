/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"string.h"
#include"math.h"
#include"stdio.h"
#include "stdlib.h"
#include "oled.h"
#include "syn6288.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/*#define OLED_RS_Pin GPIO_PIN_5
#define OLED_RS_GPIO_Port GPIOB
#define OLED_SCLK_Pin GPIO_PIN_4
#define OLED_SCLK_GPIO_Port GPIOB
#define OLED_SDIN_Pin GPIO_PIN_3
#define OLED_SDIN_GPIO_Port GPIOB
#define OLED_RST_Pin GPIO_PIN_15
#define OLED_RST_GPIO_Port GPIOA*/

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t buff[3];
uint16_t intbuff[3];
uint16_t changebuff[6];
uint8_t Usart_Receive;
uint8_t triggle;
double fst=0;
double sec=0;
//int flag=0;
//uint16_t test[2] = {0xC7FD, 0xC0EB};
//int range_max=50;
int x;
int y;
int receive_flag=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void servo_angle_left_right(uint16_t angle);
void servo_angle_up_down(uint16_t angle);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t SYN_StopCom[] = {0xFD, 0X00, 0X02, 0X02, 0XFD};
uint8_t SYN_SuspendCom[] = {0XFD, 0X00, 0X02, 0X03, 0XFC};
uint8_t SYN_RecoverCom[] = {0XFD, 0X00, 0X02, 0X04, 0XFB};
uint8_t SYN_ChackCom[] = {0XFD, 0X00, 0X02, 0X21, 0XDE};
uint8_t SYN_PowerDownCom[] = {0XFD, 0X00, 0X02, 0X88, 0X77};

/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//static u8 Count=0;
		//u8 Usart_Receive;
		if(huart->Instance==USART1)
		   {
			//HAL_UART_Receive_IT(&huart1,(uint8_t *)Usart_Receive,1);
			 // if(receive_flag == 0)
			 // {
				// buff[Count]=Usart_Receive;
				// if(Usart_Receive == 0x01||Count>0)
				// {
				//	 Count++;
				// }
				// else
				 //{
				//	 Count=0;
				 //}
				 //if (Count == 4)
				 //{
					// Count=0;
					// if(buff[4] == 0x02)
					// {
					//	 receive_flag = 1;
					// }
				// }
			//HAL_UART_Receive_IT(&huart1,buff,3);
			HAL_UART_Transmit(&huart1,buff,3,1000);
			//start=0;
			     //HAL_UART_Transmit_IT(&huart1,buff,3);
			  }
		    //HAL_UART_Transmit(&huart1,buff,3,1000);

}
*/

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    }
}
*/

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  OLED_Init();
  OLED_Clear();
  OLED_Display_On();
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  HAL_TIM_Base_Start_IT(&htim2);
  servo_angle_left_right(90);
  servo_angle_up_down(80);
  int orgin1=90;
  int orgin2=80;
  int step=5;
  int flag=0;
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
  //HAL_UART_Receive_IT(&huart1,buff,3);
  //HAL_UART_Receive_IT(&huart1,(uint8_t *)Usart_Receive,1);
  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	  HAL_UART_Receive(&huart3,buff,3,HAL_MAX_DELAY);

	 // HAL_UART_Receive_IT(&huart1,buff,3);
	  HAL_UART_Transmit(&huart3,buff,3,HAL_MAX_DELAY);
	  //HAL_UART_Transmit(&huart1,buff,3,1000);
	  //if(receive_flag == 1)
	  //		{
	  //			HAL_UART_Transmit(&huart1,buff[1],3,100);
	  //			receive_flag = 0;
	  //		}
	  intbuff[0]=buff[0];
	  intbuff[1]=buff[1];
	  intbuff[2]=buff[2];
	  intbuff[0]=floor(intbuff[0]/16)*10+intbuff[0]%16;
	  intbuff[1]=floor(intbuff[1]/16)*10+intbuff[1]%16;
	  intbuff[2]=floor(intbuff[2]/16)*10+intbuff[2]%16;
	  changebuff[0]=floor(intbuff[0]/10);
	  changebuff[1]=intbuff[0]-changebuff[0]*10;
	  changebuff[2]=floor(intbuff[1]/10);
	  changebuff[3]=intbuff[1]-changebuff[2]*10;
	  changebuff[4]=floor(intbuff[2]/10);
	  changebuff[5]=intbuff[2]-changebuff[4]*10;
	  //HAL_UART_Transmit(&huart1,buff,3,1000);
	  int x1=changebuff[0]*100+changebuff[1]*10+changebuff[2];
	  int y1=changebuff[3]*100+changebuff[4]*10+changebuff[5];
	  int x=changebuff[0]*100+changebuff[1]*10+changebuff[2]-320;
	  int y=-(changebuff[3]*100+changebuff[4]*10+changebuff[5]-240);
	  int x2;
	  int y2;
	  if(x<=0)
	  {
		  x2=-x;
	  }
	  else
	  {
		  x2=x;
	  }
	  if(y<=0)
	  {
	  	  y2=-y;
	  }
	  else
	  {
	      y2=y;
	  }
/*
	  int angx;
	  int angy;
	  int l=900;
	  angx=atan2(x2,l)*180/3.1416;
	  angy=atan2(y2,l)*180/3.1416;
*/
	  //
	  /*
	  OLED_ShowString(0,5,"orgin:");
	  OLED_ShowNumber(40,5,x1,6,12);
	  OLED_ShowNumber(80,5,y1,6,12);
	  OLED_ShowString(0,40,"trans:");
	  OLED_ShowNumber(40,40,x2,6,12);
	  OLED_ShowNumber(80,40,y2,6,12);
	  HAL_Delay(50);
	  OLED_Refresh_Gram();
	  */
	  /*
	  if(orgin1<130&&flag==0)
	  {
		  orgin1=orgin1+10;
		  servo_angle_left_right(orgin1);
		  HAL_Delay(200);
		  if(orgin1==130)
		  {
			  flag=1;
		  }
	  }
	  if(orgin1>50&&flag==1)
	  {
		  orgin1=orgin1-10;
		  servo_angle_left_right(orgin1);
		  HAL_Delay(200);
		  if(orgin1==50)
		  {
			  flag=0;
		  }
	  }
	 */
//calculate  the answer
	/*  int angx;
	  int angy;
	  int l=933;
	  angx=atan2(x2,l)*180/3.1416;
	  angy=atan2(y2,l)*180/3.1416;
	  */
	  /*
	  if(x>0)
	  {

		  servo_angle_left_right(90-floor(angx));

	  }
	  else if(x<=0)
	  {
	  	  servo_angle_left_right(90+floor(angx));

	  }

	  if(y>0)
	  {
		  //servo_angle_up_down(90-angy);
	  }
	  if(y<=0)
	  {
		 // servo_angle_up_down(90+angy);
	  }

*/
	 // HAL_Delay(50);
/*	  if(start==0)
	  {
    	if(orgin1<120&&flag==0)
    		{
    			orgin1=orgin1+step;
    			servo_angle_left_right(orgin1);
    			//HAL_Delay(50);
    			if(abs(x)<300&&abs(y)<300)
    			{
    				servo_angle_left_right(orgin1-step);
    				SYN_FrameInfo(0,"[v15][m1][t5]ЗэАл");
    				HAL_Delay(1000);
    			}
    		}
    	else
    	    {
    		    orgin1=orgin1-step;
    		    servo_angle_left_right(orgin1);
    		    //HAL_Delay(50);
    		    flag=1;
    		    if(orgin1==30)
    		    {
    		    	flag=0;
    		    }
    		    if(abs(x)<300&&abs(y)<300)
    		     {
    		    	servo_angle_left_right(orgin1+step);
    		        SYN_FrameInfo(0,"[v15][m1][t5]ЗэАл");
    		        HAL_Delay(1000);
    		     }
    	    }

	  }
	  */

	  int quadrant;
	  if(x>0&&y>0)
	  {
	   quadrant=1;
	  }
	  else if(x<0&&y>0)
	  {
	   quadrant=2;
	  }
	  else if(x<0&&y<0)
	  {
	   quadrant=3;
	  }
	  else if(x>0&&y<0)
	  {
	   quadrant=4;
	  }

	  int change_angle=5;
	  int change_angle1=1;
	  int range_max=100;
	  int range_min=50;
	  if(abs(x)>50)
	  {
	   if(abs(x)>120)
	   {
	   if(quadrant==1||quadrant==4)
	     {
	       orgin1=orgin1-change_angle;
	       if(orgin1>=180)
	       {
	    	   orgin1=180;
	       }
	       if(orgin1<5)
	       {
	      	   orgin1=5;
	       }
	       servo_angle_left_right(orgin1);
	     }
	   if(quadrant==2||quadrant==3)
	     {
	       orgin1=orgin1+change_angle;
	       if(orgin1>=180)
	       {
	       	   orgin1=180;
	       }
	       if(orgin1<5)
	       {
	       	   orgin1=5;
	       }
	       servo_angle_left_right(orgin1);
	     }
	   if(quadrant==1||quadrant==2)
	     {
	       orgin2=orgin2+change_angle;																																																		change_angle;
	       if(orgin2>=180)
		 {
			   orgin2=180;
	     }
		   if(orgin2<5)
		 {
			   orgin2=5;
		 }
	       //servo_angle_up_down(orgin2);
	     }
	   if(quadrant==3||quadrant==4)
	     {
	       orgin2=orgin2-change_angle;
	       if(orgin2>=180)
	     {
			   orgin2=180;
	     }
		   if(orgin2<5)
	     {
			   orgin2=5;
	     }
	       //servo_angle_up_down(orgin2);
	     }
	   }
	   else
	   {
		   if(quadrant==1||quadrant==4)
		   	     {
		   	       orgin1=orgin1-change_angle1;
		   	       if(orgin1>=180)
		   	       {
		   	    	   orgin1=180;
		   	       }
		   	       if(orgin1<5)
		   	       {
		   	      	   orgin1=5;
		   	       }
		   	       servo_angle_left_right(orgin1);
		   	     }
		   	   if(quadrant==2||quadrant==3)
		   	     {
		   	       orgin1=orgin1+change_angle1;
		   	       if(orgin1>=180)
		   	       {
		   	       	   orgin1=180;
		   	       }
		   	       if(orgin1<5)
		   	       {
		   	       	   orgin1=5;
		   	       }
		   	       servo_angle_left_right(orgin1);
		   	     }
	   }

	  }


	 /*servo_angle_up_down(intbuff[3]*100+intbuff[4]*10+intbuff[5]);
	 servo_angle_left_right(intbuff[0]*100+intbuff[1]*10+intbuff[2]);
     */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void servo_angle_left_right(uint16_t angle)
{
	uint16_t pulse;
	if(angle<=0)
	{
		angle=5;
	}
	if(angle>=180)
	{
		angle=180;
	}
	pulse=(uint32_t)(50+angle*100/90);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,pulse);
}
void servo_angle_up_down(uint16_t angle)
{
	uint32_t pulse;
	if(angle<=0)
	{
		angle=5;
	}
	if(angle>=180)
	{
		angle=180;
	}
	pulse=(uint32_t)(50+angle*100/90);
	//__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,pulse);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,pulse);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
